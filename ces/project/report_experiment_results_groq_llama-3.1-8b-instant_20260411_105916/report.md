# Visual Report

- Source CSV: `experiment_results_groq_llama-3.1-8b-instant_20260411_105916.csv`
- Total tasks: **15**
- Generated correctness: **14/15** (93.33%)
- Canonical correctness: **15/15** (100.00%)
- Average runtime ratio: **1.053x**
- Median runtime ratio: **0.974x**
- Faster than canonical: **8** tasks
- Slower than canonical: **6** tasks

## Charts

- correctness_per_task.png
- runtime_ratio_per_task.png
- runtime_scatter.png

## Per-Problem Snapshot

| Task | Correct | Ratio | Gen Time (s) | Canon Time (s) | Error |
|---|---:|---:|---:|---:|---|
| HumanEval/0 | Yes | 0.847 | 0.00001496 | 0.00001767 | - |
| HumanEval/1 | Yes | 0.971 | 0.00001562 | 0.00001608 | - |
| HumanEval/2 | Yes | 1.020 | 0.00000221 | 0.00000217 | - |
| HumanEval/3 | Yes | 0.964 | 0.00000450 | 0.00000467 | - |
| HumanEval/4 | No | - | - | 0.00000808 | AssertionError:  |
| HumanEval/5 | Yes | 1.435 | 0.00000646 | 0.00000450 | - |
| HumanEval/6 | Yes | 1.069 | 0.00001621 | 0.00001517 | - |
| HumanEval/7 | Yes | 0.977 | 0.00000521 | 0.00000533 | - |
| HumanEval/8 | Yes | 0.949 | 0.00000383 | 0.00000404 | - |
| HumanEval/9 | Yes | 1.274 | 0.00000833 | 0.00000654 | - |
| HumanEval/10 | Yes | 1.762 | 0.00001204 | 0.00000683 | - |
| HumanEval/11 | Yes | 0.867 | 0.00000733 | 0.00000846 | - |
| HumanEval/12 | Yes | 0.608 | 0.00000317 | 0.00000521 | - |
| HumanEval/13 | Yes | 1.067 | 0.00000200 | 0.00000187 | - |
| HumanEval/14 | Yes | 0.932 | 0.00000625 | 0.00000671 | - |

## Failed Tasks

- HumanEval/4: AssertionError: 