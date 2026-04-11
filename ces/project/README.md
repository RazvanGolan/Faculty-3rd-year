# HumanEval LLM Experiment (First 15 Tasks)

This project runs an experiment on the first 15 problems from the HumanEval test set:
- Dataset: `openai/openai_humaneval`
- Split used: `test[:15]`

For each task, it:
1. Generates a solution with Groq (LLaMA).
2. Evaluates correctness using the task's built-in `check(candidate)` tests.
3. Measures runtime and compares it with the canonical solution from the dataset.

## Setup

1. Create a virtual environment (optional but recommended):

```bash
python3 -m venv .venv
source .venv/bin/activate
```

2. Install dependencies:

```bash
pip install -r requirements.txt
```

3. Create `.env` from the example and add your API key:

```bash
cp .env.example .env
```

Then edit `.env`:

```env
LLM_PROVIDER=groq

GROQ_API_KEY=your_real_groq_key_here
GROQ_MODEL=llama-3.1-8b-instant
```

## Run

```bash
python experiment.py
```

## Outputs

After execution, two files are generated per run:
- `experiment_results_<provider>_<model>_<timestamp>.csv`: per-task detailed results
- `experiment_summary_<provider>_<model>_<timestamp>.md`: aggregated metrics and notes

## Visual Report

To generate charts and an easier-to-read per-problem report from a CSV:

```bash
python visualize_results.py --csv experiment_results_groq_llama-3.1-8b-instant_<timestamp>.csv
```

If you omit `--csv`, the latest `experiment_results_*.csv` file is used.

The script creates a folder named `report_<csv_name>/` containing:
- `correctness_per_task.png`
- `runtime_ratio_per_task.png`
- `runtime_scatter.png`
- `report.md` (overall metrics + per-task table)

## Evaluation Method

- Correctness:
  - A generated solution is considered correct if it passes the provided `check(candidate)` assertions for that task.
- Runtime:
  - Runtime is measured as the median time of `check(candidate)` over 5 runs.
  - The same measurement is done for the canonical solution.
  - Comparison metric: `generated_time / canonical_time`.

## Important Notes

- The script executes generated Python code locally (inside subprocesses with timeout). Use only in trusted environments.
- If model output includes extra text or markdown, the script attempts to sanitize it automatically.
