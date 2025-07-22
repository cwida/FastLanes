#!/usr/bin/env python3
"""Benchmark visualisation helper (combined float & dbl subplots, new vs old).

*   Accepts CSVs (with or without header) in new or legacy format.
*   Extracts exception counts from trailing digits in names.
*   Classifies each entry as float vs dbl based on name suffix.
*   Plots both float and dbl benchmarks side-by-side in a single figure.
*   Only compares "new" vs "old" variants, dropping "try" entries.
*   Prints average cycles per run and speedup factor of new over old.
*   Saves the combined figure as a PNG file.

Usage::
    python plot.py path/to/patch.csv
    # Plot will be saved as benchmark_new_vs_old.png
"""

from __future__ import annotations
import sys
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


def _canonicalise_columns(df: pd.DataFrame) -> pd.DataFrame:
    col_map = {"benchmark_number": "id", "cycles_per_tuple": "cycles"}
    df = df.rename(columns=col_map, errors="ignore")
    required = {"id", "name", "iterations", "cycles"}
    missing = required.difference(df.columns)
    if missing:
        raise ValueError(f"Missing required columns: {', '.join(sorted(missing))}")
    return df


def load_and_prepare(path: str | Path = "patch.csv") -> pd.DataFrame:
    """Load CSV and return DataFrame with exceptions, cycles, version, and type."""
    df = pd.read_csv(path)
    if "benchmark_number" not in df.columns:
        df = pd.read_csv(
            path,
            header=None,
            names=["benchmark_number", "name", "iterations", "cycles_per_tuple"],
        )
    df = _canonicalise_columns(df)

    # Ensure id is integer
    df["id"] = pd.to_numeric(df["id"], errors="coerce").astype(pd.Int64Dtype())
    df = df.dropna(subset=["id"])
    df["id"] = df["id"].astype(int)

    # Extract exception count (trailing digits)
    df["exceptions"] = (
        df["name"].str.extract(r"(\d+)$")[0]
        .astype(pd.Int64Dtype())
    )
    df = df.dropna(subset=["exceptions"])
    df["exceptions"] = df["exceptions"].astype(int)

    # Extract version prefix (new/old), drop 'try'
    df["version"] = df["name"].str.extract(r"^(new|old)")[0]
    df = df.dropna(subset=["version"])

    # Classify type by name suffix: 'float' or 'dbl'
    df["type"] = df["name"].apply(
        lambda s: "float" if "float" in s else ("dbl" if "dbl" in s else None)
    )
    df = df.dropna(subset=["type"])

    # Convert cycles to numeric
    df["cycles"] = pd.to_numeric(df["cycles"], errors="coerce")

    return df


def plot_benchmarks(df: pd.DataFrame, save_path: Path = Path("benchmark_new_vs_old.png")) -> None:
    """Plot float and dbl benchmarks in a single figure with two subplots and save."""
    color_map = {"new": "green", "old": "red"}
    types = ["float", "dbl"]

    fig, axes = plt.subplots(1, 2, figsize=(16, 5), sharey=True)
    for ax, typ in zip(axes, types):
        sub = df[df["type"] == typ]
        if sub.empty:
            ax.set_visible(False)
            continue
        pivot = (
            sub.pivot_table(
                index="exceptions", columns="version", values="cycles", aggfunc="mean"
            )
            .sort_index()
        )
        for version in ["new", "old"]:
            if version in pivot.columns:
                series = pivot[version]
                ax.plot(
                    series.index,
                    series.values,
                    marker="o",
                    label=version,
                    color=color_map.get(version),
                )
        ax.set_xticks(pivot.index)
        ax.set_xlabel("Number of Exceptions")
        ax.set_title(f"{typ.capitalize()} benchmarks: new vs old")
        ax.grid(True, linestyle="--", alpha=0.5)
        ax.legend(title="Version")

    axes[0].set_ylabel("Cycles per Run")
    fig.suptitle("Benchmark: new vs old (float & dbl)")
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    # Save figure
    fig.savefig(save_path)
    print(f"Plot saved to {save_path}")
    plt.show()


def main(argv: list[str] | None = None) -> None:
    import argparse
    parser = argparse.ArgumentParser(description="Plot float and dbl benchmark results.")
    parser.add_argument("csv", nargs="?", default="patch.csv", help="CSV file to read")
    parser.add_argument("--out", help="Output PNG path", default="benchmark_new_vs_old.png")
    ns = parser.parse_args(argv)
    path = Path(ns.csv)
    if not path.exists():
        parser.error(f"CSV not found: {path}")
    df = load_and_prepare(path)
    if df.empty:
        parser.error("No valid data to plot.")

    # Compute and print average cycles and speedup factor of new over old
    for typ in ["float", "dbl"]:
        sub = df[df["type"] == typ]
        if sub.empty:
            continue
        pivot = (
            sub.pivot_table(
                index="exceptions", columns="version", values="cycles", aggfunc="mean"
            ).sort_index()
        )
        if "new" in pivot.columns and "old" in pivot.columns:
            old = pivot["old"]
            new = pivot["new"]
            avg_new = new.mean()
            avg_old = old.mean()
            times = old / new
            avg_times = times.mean()
            print(f"{typ.capitalize()}: average cycles per run — new: {avg_new:.1f}, old: {avg_old:.1f}.")
            print(f"{typ.capitalize()}: new is on average {avg_times:.2f}× faster than old.")

    plot_benchmarks(df, Path(ns.out))


if __name__ == "__main__":
    main(sys.argv[1:])
