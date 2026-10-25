#!/usr/bin/env python3
"""Regenerate the FFI export manifest and compare it with the committed snapshot.

`kwxgen exports` writes three views of the same symbol set (.def for Windows,
.map for ELF, .exp for Mach-O). Cross-checking all three catches a generator
change that forgets one of the writers; diffing the set against
`tests/expected/symbols.txt` turns any parser regression into a reviewable diff.

Exit codes: 0 when the snapshot matches, 1 on any mismatch or generator failure.
"""

from __future__ import annotations

import argparse
import subprocess
import sys
import tempfile
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_ROOT = SCRIPT_DIR.parent.parent

DEF_FILE_NAME = "kwxffi_exports.def"
MAP_FILE_NAME = "kwxffi_exports.map"
EXP_FILE_NAME = "kwxffi_exports.exp"


def parse_arguments(argv: list[str] | None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Regenerate the kwxFFI export manifest and compare it with the snapshot."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=DEFAULT_ROOT,
        help="Repository root (default: the parent of this script's directory)",
    )
    parser.add_argument(
        "--kwxgen",
        required=True,
        help="Path to the kwxgen executable",
    )
    parser.add_argument(
        "--update",
        action="store_true",
        help="Rewrite tests/expected/symbols.txt instead of comparing against it",
    )
    return parser.parse_args(argv)


def run_exports(kwxgen: Path, root: Path, out_dir: Path) -> int:
    """Run `kwxgen exports`; return its exit code (output is streamed unchanged)."""
    command = [
        str(kwxgen),
        "exports",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--out",
        str(out_dir),
    ]
    print(f"--- {' '.join(command)}")
    completed = subprocess.run(command, cwd=str(root), check=False)
    return completed.returncode


def read_text_lines(path: Path) -> list[str]:
    # splitlines() strips both LF and CRLF, which matters because
    # .gitattributes sets `* text=auto` and the snapshot is CRLF on Windows.
    return path.read_text(encoding="utf-8", errors="replace").splitlines()


def read_def_symbols(path: Path) -> list[str]:
    """Parse a Windows module-definition file: drop comments and the header."""
    symbols: list[str] = []
    for raw_line in read_text_lines(path):
        line = raw_line.strip()
        if not line or line.startswith(";") or line == "EXPORTS":
            continue
        symbols.append(line)
    return symbols


def read_map_symbols(path: Path) -> list[str]:
    """Parse an ELF linker version script: drop the comment and block syntax."""
    symbols: list[str] = []
    for raw_line in read_text_lines(path):
        line = raw_line.strip()
        if not line or line.startswith("/*") or line.startswith("//"):
            continue
        # Drop the block punctuation (`{`, `}`, `};`) and the section labels.
        line = line.rstrip(";").strip()
        if line in {"{", "}"} or line.startswith("global:") or line.startswith("local:"):
            continue
        if line:
            symbols.append(line)
    return symbols


def read_exp_symbols(path: Path) -> list[str]:
    """Parse a Mach-O exported symbols list: drop comments and the leading `_`."""
    symbols: list[str] = []
    for raw_line in read_text_lines(path):
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("_"):
            line = line[1:]
        symbols.append(line)
    return symbols


def read_snapshot(path: Path) -> list[str]:
    return [line.strip() for line in read_text_lines(path) if line.strip()]


def report_file_mismatch(label: str, symbols: list[str], reference: set[str]) -> bool:
    """Print a + / - diff for one generated file against the reference set."""
    actual = set(symbols)
    added = sorted(actual - reference)
    removed = sorted(reference - actual)
    if not added and not removed:
        return True
    print(f"error: {label} does not match the .def symbol set", file=sys.stderr)
    for symbol in added:
        print(f"  + {symbol}", file=sys.stderr)
    for symbol in removed:
        print(f"  - {symbol}", file=sys.stderr)
    return False


def write_snapshot(path: Path, symbols: list[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as snapshot_file:
        for symbol in symbols:
            snapshot_file.write(f"{symbol}\n")


def main(argv: list[str] | None = None) -> int:
    options = parse_arguments(argv)
    root = options.root.resolve()
    kwxgen = Path(options.kwxgen)
    if not kwxgen.is_absolute():
        kwxgen = root / kwxgen
    kwxgen = kwxgen.resolve()

    if not kwxgen.is_file():
        print(f"error: kwxgen executable not found at {kwxgen}", file=sys.stderr)
        return 1

    snapshot_path = root / "tests" / "expected" / "symbols.txt"

    with tempfile.TemporaryDirectory(prefix="kwxffi_exports_") as temp_dir_name:
        out_dir = Path(temp_dir_name)
        return_code = run_exports(kwxgen, root, out_dir)
        if return_code != 0:
            print(f"error: kwxgen exports failed with exit {return_code}", file=sys.stderr)
            return 1

        def_path = out_dir / DEF_FILE_NAME
        map_path = out_dir / MAP_FILE_NAME
        exp_path = out_dir / EXP_FILE_NAME
        for generated_path in (def_path, map_path, exp_path):
            if not generated_path.is_file():
                print(f"error: {generated_path.name} was not generated", file=sys.stderr)
                return 1

        def_symbols = read_def_symbols(def_path)
        map_symbols = read_map_symbols(map_path)
        exp_symbols = read_exp_symbols(exp_path)

    if not def_symbols:
        print("error: the generated export manifest is empty", file=sys.stderr)
        return 1

    reference = set(def_symbols)
    consistent = report_file_mismatch(MAP_FILE_NAME, map_symbols, reference)
    consistent = report_file_mismatch(EXP_FILE_NAME, exp_symbols, reference) and consistent
    if not consistent:
        return 1

    generated = sorted(reference)

    if options.update:
        write_snapshot(snapshot_path, generated)
        print(f"Wrote {len(generated)} symbols to {snapshot_path}")
        return 0

    if not snapshot_path.is_file():
        print(
            f"error: snapshot {snapshot_path} is missing; re-run with --update",
            file=sys.stderr,
        )
        return 1

    expected = read_snapshot(snapshot_path)
    if expected == generated:
        print(f"OK: {len(generated)} symbols match {snapshot_path}")
        return 0

    expected_set = set(expected)
    generated_set = set(generated)

    for symbol in sorted(generated_set - expected_set):
        print(f"+ {symbol}")
    for symbol in sorted(expected_set - generated_set):
        print(f"- {symbol}")

    if expected_set == generated_set:
        print("error: the snapshot has the right symbols but the wrong order", file=sys.stderr)
    if len(expected) != len(expected_set):
        print("error: the snapshot contains duplicate entries", file=sys.stderr)

    print(
        f"MISMATCH: {len(generated_set - expected_set)} added, "
        f"{len(expected_set - generated_set)} removed "
        f"({len(expected)} snapshot symbols, {len(generated)} generated symbols)"
    )
    print("Re-run with --update to accept the new manifest.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
