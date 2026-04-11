import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


def to_bool(series: pd.Series) -> pd.Series:
    return series.astype(str).str.lower().map({"true": True, "false": False})


def load_latest_csv(base_dir: Path) -> Path:
    candidates = sorted(base_dir.glob("experiment_results_*.csv"))
    if not candidates:
        raise FileNotFoundError("No experiment_results_*.csv files found in current folder.")
    return candidates[-1]


def ensure_output_dir(base_name: str) -> Path:
    output_dir = Path(f"report_{base_name}")
    output_dir.mkdir(parents=True, exist_ok=True)
    return output_dir


def plot_correctness(df: pd.DataFrame, output_dir: Path) -> None:
    fig, ax = plt.subplots(figsize=(12, 5))
    x = df["task_id"]
    y = to_bool(df["generated_correct"]).fillna(False).astype(int)

    colors = ["#1f77b4" if val == 1 else "#d62728" for val in y]
    ax.bar(x, y, color=colors)
    ax.set_title("Generated Solution Correctness by Task")
    ax.set_ylabel("Correct (1=True, 0=False)")
    ax.set_xlabel("Task")
    ax.set_ylim(0, 1.1)
    ax.tick_params(axis="x", rotation=45)
    ax.grid(axis="y", linestyle="--", alpha=0.35)

    fig.tight_layout()
    fig.savefig(output_dir / "correctness_per_task.png", dpi=180)
    plt.close(fig)


def plot_runtime_ratio(df: pd.DataFrame, output_dir: Path) -> None:
    ratio_df = df.dropna(subset=["generated_vs_canonical_ratio"]).copy()
    if ratio_df.empty:
        return

    fig, ax = plt.subplots(figsize=(12, 5))
    x = ratio_df["task_id"]
    y = ratio_df["generated_vs_canonical_ratio"].astype(float)

    colors = ["#2ca02c" if val < 1.0 else "#ff7f0e" for val in y]
    ax.bar(x, y, color=colors)
    ax.axhline(1.0, color="black", linestyle="--", linewidth=1, label="Parity (1.0x)")
    ax.set_title("Runtime Ratio by Task (Generated / Canonical)")
    ax.set_ylabel("Ratio")
    ax.set_xlabel("Task")
    ax.tick_params(axis="x", rotation=45)
    ax.grid(axis="y", linestyle="--", alpha=0.35)
    ax.legend()

    fig.tight_layout()
    fig.savefig(output_dir / "runtime_ratio_per_task.png", dpi=180)
    plt.close(fig)


def plot_time_scatter(df: pd.DataFrame, output_dir: Path) -> None:
    scatter_df = df.dropna(subset=["generated_time_s_median", "canonical_time_s_median"]).copy()
    if scatter_df.empty:
        return

    x = scatter_df["canonical_time_s_median"].astype(float)
    y = scatter_df["generated_time_s_median"].astype(float)

    fig, ax = plt.subplots(figsize=(7, 6))
    ax.scatter(x, y, color="#1f77b4", alpha=0.85)

    min_v = min(x.min(), y.min())
    max_v = max(x.max(), y.max())
    ax.plot([min_v, max_v], [min_v, max_v], linestyle="--", color="black", linewidth=1, label="y = x")

    for _, row in scatter_df.iterrows():
        ax.annotate(row["task_id"], (row["canonical_time_s_median"], row["generated_time_s_median"]), fontsize=7)

    ax.set_title("Generated vs Canonical Runtime")
    ax.set_xlabel("Canonical Median Time (s)")
    ax.set_ylabel("Generated Median Time (s)")
    ax.grid(linestyle="--", alpha=0.35)
    ax.legend()

    fig.tight_layout()
    fig.savefig(output_dir / "runtime_scatter.png", dpi=180)
    plt.close(fig)


def build_markdown_report(df: pd.DataFrame, csv_name: str, output_dir: Path) -> None:
    generated_correct = to_bool(df["generated_correct"]).fillna(False)
    canonical_correct = to_bool(df["canonical_correct"]).fillna(False)

    total_tasks = len(df)
    generated_pass = int(generated_correct.sum())
    canonical_pass = int(canonical_correct.sum())

    ratio_series = pd.to_numeric(df["generated_vs_canonical_ratio"], errors="coerce").dropna()
    avg_ratio = ratio_series.mean() if not ratio_series.empty else None
    median_ratio = ratio_series.median() if not ratio_series.empty else None

    faster_count = int((ratio_series < 1.0).sum()) if not ratio_series.empty else 0
    slower_count = int((ratio_series > 1.0).sum()) if not ratio_series.empty else 0

    failed_df = df[~generated_correct].copy()

    lines = [
        "# Visual Report",
        "",
        f"- Source CSV: `{csv_name}`",
        f"- Total tasks: **{total_tasks}**",
        f"- Generated correctness: **{generated_pass}/{total_tasks}** ({(generated_pass / total_tasks):.2%})",
        f"- Canonical correctness: **{canonical_pass}/{total_tasks}** ({(canonical_pass / total_tasks):.2%})",
    ]

    if avg_ratio is not None and median_ratio is not None:
        lines.append(f"- Average runtime ratio: **{avg_ratio:.3f}x**")
        lines.append(f"- Median runtime ratio: **{median_ratio:.3f}x**")
        lines.append(f"- Faster than canonical: **{faster_count}** tasks")
        lines.append(f"- Slower than canonical: **{slower_count}** tasks")

    lines.extend(
        [
            "",
            "## Charts",
            "",
            "- correctness_per_task.png",
            "- runtime_ratio_per_task.png",
            "- runtime_scatter.png",
            "",
            "## Per-Problem Snapshot",
            "",
            "| Task | Correct | Ratio | Gen Time (s) | Canon Time (s) | Error |",
            "|---|---:|---:|---:|---:|---|",
        ]
    )

    for _, row in df.iterrows():
        ratio = row.get("generated_vs_canonical_ratio")
        gen_t = row.get("generated_time_s_median")
        can_t = row.get("canonical_time_s_median")
        err = row.get("generation_or_eval_error")

        ratio_str = f"{float(ratio):.3f}" if pd.notna(ratio) else "-"
        gen_str = f"{float(gen_t):.8f}" if pd.notna(gen_t) else "-"
        can_str = f"{float(can_t):.8f}" if pd.notna(can_t) else "-"
        err_str = err if pd.notna(err) and str(err).strip() else "-"
        correct_str = "Yes" if str(row.get("generated_correct")).lower() == "true" else "No"

        lines.append(
            f"| {row['task_id']} | {correct_str} | {ratio_str} | {gen_str} | {can_str} | {err_str} |"
        )

    if not failed_df.empty:
        lines.extend(["", "## Failed Tasks", ""])
        for _, row in failed_df.iterrows():
            lines.append(f"- {row['task_id']}: {row.get('generation_or_eval_error') or 'Unknown error'}")

    report_path = output_dir / "report.md"
    report_path.write_text("\n".join(lines), encoding="utf-8")


def main() -> None:
    parser = argparse.ArgumentParser(description="Generate easy-to-read charts and report from experiment CSV.")
    parser.add_argument("--csv", type=str, default=None, help="Path to experiment_results CSV file.")
    args = parser.parse_args()

    base_dir = Path.cwd()
    csv_path = Path(args.csv) if args.csv else load_latest_csv(base_dir)

    if not csv_path.exists():
        raise FileNotFoundError(f"CSV file not found: {csv_path}")

    df = pd.read_csv(csv_path)

    base_name = csv_path.stem
    output_dir = ensure_output_dir(base_name)

    plot_correctness(df, output_dir)
    plot_runtime_ratio(df, output_dir)
    plot_time_scatter(df, output_dir)
    build_markdown_report(df, csv_path.name, output_dir)

    print(f"Report generated in: {output_dir}")
    print(f"- {output_dir / 'correctness_per_task.png'}")
    print(f"- {output_dir / 'runtime_ratio_per_task.png'}")
    print(f"- {output_dir / 'runtime_scatter.png'}")
    print(f"- {output_dir / 'report.md'}")


if __name__ == "__main__":
    main()
