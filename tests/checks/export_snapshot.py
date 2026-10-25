#!/usr/bin/env python3
"""Verify the FFI export surface against a committed count+sha256 digest.

`kwxgen exports` writes three views of the same symbol set (.def for Windows,
.map for ELF, .exp for Mach-O). Cross-checking all three catches a generator
change that forgets one of the writers. The resulting set is then reduced to a
count and a sha256 digest and compared with `tests/expected/symbols.sha256`: a
200 KB sorted list is unreviewable in a pull request, while a digest mismatch
still tells CI that the exported FFI surface changed.

The digest normalizes the symbol set first -- sorted, deduplicated, joined with
LF, plus a trailing LF, encoded UTF-8 -- so it does not depend on the platform
that generated it or on the file's line endings.

Exit codes: 0 when the digest matches, 1 on any mismatch or generator failure.
"""

from __future__ import annotations

import argparse
import hashlib
import sys
import tempfile
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from _exports import (
    DEF_FILE_NAME,
    EXP_FILE_NAME,
    MAP_FILE_NAME,
    generate,
    read_def_symbols,
    read_text_lines,
)

DEFAULT_ROOT = SCRIPT_DIR.parent.parent
DIGEST_FILE_NAME = "symbols.sha256"
GENERATED_LIST_PATH = Path("build") / "tests" / "exports" / "symbols.generated.txt"


def parse_arguments(argv: list[str] | None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Verify the kwxFFI export surface against the digest baseline."
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
        help=f"Rewrite tests/expected/{DIGEST_FILE_NAME} instead of comparing",
    )
    parser.add_argument(
        "--write-list",
        type=Path,
        default=None,
        help="Write the sorted symbol list to this path and exit",
    )
    return parser.parse_args(argv)


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


def normalize(symbols: list[str]) -> list[str]:
    """Return the sorted, deduplicated symbol list the digest is built from."""
    return sorted(set(symbols))


def compute_digest(symbols: list[str]) -> tuple[int, str]:
    """Return ``(count, sha256)`` for the normalized symbol list."""
    normalized = normalize(symbols)
    payload = "\n".join(normalized) + "\n"
    return len(normalized), hashlib.sha256(payload.encode("utf-8")).hexdigest()


def write_symbol_list(path: Path, symbols: list[str]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as symbol_file:
        for symbol in symbols:
            symbol_file.write(f"{symbol}\n")


def write_digest(path: Path, count: int, digest: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as digest_file:
        digest_file.write("# kwxFFI FFI export surface digest.\n")
        digest_file.write("# Regenerate with tests/checks/export_snapshot.py --update.\n")
        digest_file.write(f"count {count}\n")
        digest_file.write(f"sha256 {digest}\n")


def read_digest(path: Path) -> tuple[int, str]:
    """Read a ``count <n>`` / ``sha256 <hex>`` baseline; raise ``ValueError``."""
    count = -1
    digest = ""
    for number, raw_line in enumerate(read_text_lines(path), 1):
        line = raw_line.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split()
        if len(parts) != 2:
            raise ValueError(f"{path}:{number}: expected '<key> <value>'")
        key, value = parts
        if key == "count":
            count = int(value)
        elif key == "sha256":
            digest = value
        else:
            raise ValueError(f"{path}:{number}: unknown key '{key}'")
    if count < 0 or not digest:
        raise ValueError(f"{path}: missing 'count' or 'sha256'")
    return count, digest


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

    digest_path = root / "tests" / "expected" / DIGEST_FILE_NAME

    with tempfile.TemporaryDirectory(prefix="kwxffi_exports_") as temp_dir_name:
        out_dir = Path(temp_dir_name)
        return_code = generate(kwxgen, root, out_dir)
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

    generated = normalize(def_symbols)
    count, digest = compute_digest(generated)

    if options.write_list is not None:
        list_path = options.write_list
        if not list_path.is_absolute():
            list_path = root / list_path
        write_symbol_list(list_path, generated)
        print(f"Wrote {count} symbols to {list_path}")
        if not options.update:
            return 0

    if options.update:
        write_digest(digest_path, count, digest)
        print(f"Wrote digest to {digest_path}: count {count}, sha256 {digest}")
        return 0

    if not digest_path.is_file():
        print(
            f"error: digest baseline {digest_path} is missing; re-run with --update",
            file=sys.stderr,
        )
        return 1

    try:
        expected_count, expected_digest = read_digest(digest_path)
    except ValueError as digest_error:
        print(f"error: {digest_error}", file=sys.stderr)
        return 1

    if expected_count == count and expected_digest == digest:
        print(f"OK: count {count}, sha256 {digest} match {digest_path}")
        return 0

    generated_list_path = root / GENERATED_LIST_PATH
    write_symbol_list(generated_list_path, generated)
    print(
        f"error: export digest mismatch: expected count {expected_count}, "
        f"sha256 {expected_digest}; got count {count}, sha256 {digest}",
        file=sys.stderr,
    )
    print("The exported FFI surface changed. Compare it with the merge base:")
    print("  git worktree add ../kwxFFI-base <merge-base>")
    print(
        f"  python tests/checks/export_snapshot.py --root ../kwxFFI-base "
        f"--kwxgen {kwxgen} --write-list /tmp/base-symbols.txt"
    )
    print(f"  diff -u /tmp/base-symbols.txt {GENERATED_LIST_PATH.as_posix()}")
    return 1


if __name__ == "__main__":
    sys.exit(main())
