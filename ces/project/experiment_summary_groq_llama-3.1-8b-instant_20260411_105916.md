# HumanEval LLM Experiment Summary

- Dataset: `openai/openai_humaneval`
- Split: `test[:15]` (first 15 tasks)
- Provider: `groq`
- Requested model: `llama-3.1-8b-instant`
- Tested model(s): `llama-3.1-8b-instant`
- Correct generated solutions: **14/15** (93.33%)
- Average runtime ratio (generated/canonical): **1.053x**
- Median runtime ratio (generated/canonical): **0.974x**

## Notes

- Correctness is evaluated using each HumanEval task's provided `check(candidate)` tests.
- Runtime is measured as the median execution time of `check(candidate)` over 5 runs.
- Timeouts are treated as failures.

## Output Files

- `experiment_results_groq_llama-3.1-8b-instant_20260411_105916.csv`
- `experiment_summary_groq_llama-3.1-8b-instant_20260411_105916.md`