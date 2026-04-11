import json
import multiprocessing as mp
import os
import re
import statistics
import time
from dataclasses import dataclass
from datetime import datetime
from typing import Any

import pandas as pd
import requests
from datasets import load_dataset
from dotenv import load_dotenv


DATASET_NAME = "openai/openai_humaneval"
SPLIT = "test[:15]"
DEFAULT_PROVIDER = "groq"
DEFAULT_MODEL = "llama-3.1-8b-instant"
REQUEST_TIMEOUT_SECONDS = 60
EXEC_TIMEOUT_SECONDS = 6
BENCHMARK_REPEATS = 5


@dataclass
class EvalResult:
	ok: bool
	elapsed_seconds: float | None
	error: str | None


def sanitize_completion(raw_text: str, prompt: str) -> str:
	text = raw_text.strip()

	code_block_match = re.search(r"```(?:python)?\s*(.*?)```", text, flags=re.DOTALL | re.IGNORECASE)
	if code_block_match:
		text = code_block_match.group(1).strip()

	if text.startswith(prompt):
		text = text[len(prompt) :]

	marker = "Here is"
	marker_index = text.find(marker)
	if marker_index == 0:
		lines = text.splitlines()
		text = "\n".join(lines[1:]).strip()

	return text


def call_groq(api_key: str, model: str, prompt_text: str) -> tuple[str, str, str]:
	url = "https://api.groq.com/openai/v1/chat/completions"
	headers = {
		"Authorization": f"Bearer {api_key}",
		"Content-Type": "application/json",
	}
	payload = {
		"model": model,
		"temperature": 0.2,
		"max_tokens": 1024,
		"messages": [
			{
				"role": "system",
				"content": "You solve Python coding tasks. Return code only, no markdown.",
			},
			{"role": "user", "content": prompt_text},
		],
	}

	try:
		response = requests.post(url, headers=headers, json=payload, timeout=REQUEST_TIMEOUT_SECONDS)
		response.raise_for_status()
	except requests.HTTPError as exc:
		status_code = exc.response.status_code if exc.response is not None else "unknown"
		body_preview = ""
		if exc.response is not None:
			body_preview = exc.response.text[:220].replace("\n", " ")
		raise RuntimeError(f"Groq request failed with HTTP {status_code}: {body_preview}") from exc
	except requests.RequestException as exc:
		raise RuntimeError(f"Groq request exception: {type(exc).__name__}: {exc}") from exc

	data = response.json()
	choices = data.get("choices", [])
	if not choices:
		raise RuntimeError(f"No choices returned by Groq. Raw response: {json.dumps(data)[:500]}")

	message = choices[0].get("message", {})
	text = message.get("content", "")
	if not text.strip():
		raise RuntimeError("Groq returned an empty completion.")

	return text, model, "openai-compatible-v1"


def _exec_and_check(
	code: str,
	test_code: str,
	entry_point: str,
	queue: mp.Queue,
) -> None:
	try:
		namespace: dict[str, Any] = {}
		exec(code, namespace)
		exec(test_code, namespace)

		candidate = namespace[entry_point]
		check_fn = namespace["check"]

		start = time.perf_counter()
		check_fn(candidate)
		elapsed = time.perf_counter() - start
		queue.put(EvalResult(ok=True, elapsed_seconds=elapsed, error=None))
	except Exception as exc:  # noqa: BLE001
		queue.put(EvalResult(ok=False, elapsed_seconds=None, error=f"{type(exc).__name__}: {exc}"))


def run_single_eval(code: str, test_code: str, entry_point: str, timeout_seconds: int) -> EvalResult:
	queue: mp.Queue = mp.Queue()
	process = mp.Process(target=_exec_and_check, args=(code, test_code, entry_point, queue))
	process.start()
	process.join(timeout_seconds)

	if process.is_alive():
		process.terminate()
		process.join()
		return EvalResult(ok=False, elapsed_seconds=None, error=f"Timeout after {timeout_seconds}s")

	if queue.empty():
		return EvalResult(ok=False, elapsed_seconds=None, error="No evaluation result returned.")

	return queue.get()


def benchmark(code: str, test_code: str, entry_point: str, timeout_seconds: int, repeats: int) -> tuple[bool, float | None, str | None]:
	timings: list[float] = []
	for _ in range(repeats):
		result = run_single_eval(code, test_code, entry_point, timeout_seconds)
		if not result.ok or result.elapsed_seconds is None:
			return False, None, result.error
		timings.append(result.elapsed_seconds)
	return True, statistics.median(timings), None


def build_generation_prompt(prompt: str, entry_point: str) -> str:
	return (
		"You are solving a Python programming task from HumanEval.\n"
		"Return only valid Python code that completes the function.\n"
		"Do not include Markdown, explanations, or tests.\n"
		f"The function entry point is: {entry_point}\n\n"
		"Complete this prompt:\n"
		f"{prompt}"
	)


def sanitize_for_filename(value: str) -> str:
	sanitized = re.sub(r"[^a-zA-Z0-9._-]+", "_", value.strip())
	return sanitized.strip("_") or "model"


def main() -> None:
	load_dotenv()

	provider = os.getenv("LLM_PROVIDER", DEFAULT_PROVIDER).strip().lower()
	requested_model = os.getenv("GROQ_MODEL", DEFAULT_MODEL)
	groq_api_key = os.getenv("GROQ_API_KEY")

	if provider != "groq":
		raise RuntimeError("Unsupported LLM_PROVIDER. Only 'groq' is supported in this project.")

	if not groq_api_key:
		raise RuntimeError("GROQ_API_KEY is missing. Add it to your .env file.")

	run_timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")

	print("Loading dataset...")
	dataset = load_dataset(DATASET_NAME, split=SPLIT)
	print(f"Loaded {len(dataset)} tasks from {DATASET_NAME} ({SPLIT}).")
	print(f"Using provider={provider}, requested_model={requested_model}")

	rows: list[dict[str, Any]] = []

	for idx, sample in enumerate(dataset, start=1):
		task_id = sample["task_id"]
		prompt = sample["prompt"]
		canonical_solution = sample["canonical_solution"]
		test_code = sample["test"]
		entry_point = sample["entry_point"]

		print(f"[{idx}/15] Generating for {task_id}...")

		generation_error = None
		completion = ""
		resolved_model = requested_model
		api_version_used = ""
		try:
			llm_prompt = build_generation_prompt(prompt, entry_point)
			raw_completion, resolved_model, api_version_used = call_groq(
				api_key=groq_api_key,
				model=requested_model,
				prompt_text=llm_prompt,
			)
			completion = sanitize_completion(raw_completion, prompt)
		except Exception as exc:  # noqa: BLE001
			generation_error = f"{type(exc).__name__}: {exc}"

		generated_code = f"{prompt}{completion}" if completion else ""
		canonical_code = f"{prompt}{canonical_solution}"

		generated_ok = False
		generated_time = None
		generated_eval_error = generation_error

		if generated_code and not generation_error:
			generated_ok, generated_time, generated_eval_error = benchmark(
				generated_code,
				test_code,
				entry_point,
				timeout_seconds=EXEC_TIMEOUT_SECONDS,
				repeats=BENCHMARK_REPEATS,
			)

		canonical_ok, canonical_time, canonical_eval_error = benchmark(
			canonical_code,
			test_code,
			entry_point,
			timeout_seconds=EXEC_TIMEOUT_SECONDS,
			repeats=BENCHMARK_REPEATS,
		)

		time_ratio = None
		if generated_time is not None and canonical_time and canonical_time > 0:
			time_ratio = generated_time / canonical_time

		rows.append(
			{
				"task_id": task_id,
				"provider": provider,
				"requested_model": requested_model,
				"tested_model": resolved_model,
				"api_version": api_version_used,
				"run_timestamp": run_timestamp,
				"entry_point": entry_point,
				"generated_correct": generated_ok,
				"canonical_correct": canonical_ok,
				"generated_time_s_median": generated_time,
				"canonical_time_s_median": canonical_time,
				"generated_vs_canonical_ratio": time_ratio,
				"generation_or_eval_error": generated_eval_error,
				"canonical_eval_error": canonical_eval_error,
			}
		)

		time.sleep(1.0)

	df = pd.DataFrame(rows)
	provider_slug = sanitize_for_filename(provider)
	model_slug = sanitize_for_filename(requested_model)
	results_filename = f"experiment_results_{provider_slug}_{model_slug}_{run_timestamp}.csv"
	summary_filename = f"experiment_summary_{provider_slug}_{model_slug}_{run_timestamp}.md"

	df.to_csv(results_filename, index=False)

	total_tasks = len(df)
	generated_correct = int(df["generated_correct"].sum())
	correctness_rate = generated_correct / total_tasks if total_tasks else 0.0

	ratio_series = df["generated_vs_canonical_ratio"].dropna()
	avg_ratio = ratio_series.mean() if not ratio_series.empty else None
	median_ratio = ratio_series.median() if not ratio_series.empty else None

	summary_lines = [
		"# HumanEval LLM Experiment Summary",
		"",
		f"- Dataset: `{DATASET_NAME}`",
		f"- Split: `{SPLIT}` (first 15 tasks)",
		f"- Provider: `{provider}`",
		f"- Requested model: `{requested_model}`",
		f"- Tested model(s): `{', '.join(sorted(set(df['tested_model'].dropna().astype(str))))}`",
		f"- Correct generated solutions: **{generated_correct}/{total_tasks}** ({correctness_rate:.2%})",
	]

	if avg_ratio is not None and median_ratio is not None:
		summary_lines.append(f"- Average runtime ratio (generated/canonical): **{avg_ratio:.3f}x**")
		summary_lines.append(f"- Median runtime ratio (generated/canonical): **{median_ratio:.3f}x**")
	else:
		summary_lines.append("- Runtime ratio could not be computed for any task.")

	summary_lines.extend(
		[
			"",
			"## Notes",
			"",
			"- Correctness is evaluated using each HumanEval task's provided `check(candidate)` tests.",
			"- Runtime is measured as the median execution time of `check(candidate)` over 5 runs.",
			"- Timeouts are treated as failures.",
			"",
			"## Output Files",
			"",
			f"- `{results_filename}`",
			f"- `{summary_filename}`",
		]
	)

	with open(summary_filename, "w", encoding="utf-8") as file:
		file.write("\n".join(summary_lines))

	print("Experiment completed.")
	print(f"Saved: {results_filename}")
	print(f"Saved: {summary_filename}")


if __name__ == "__main__":
	main()
