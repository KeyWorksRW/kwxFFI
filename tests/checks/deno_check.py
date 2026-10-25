#!/usr/bin/env python3
"""Type-check the generated TypeScript bindings through `kwxgen check`.

`kwxgen check` regenerates the bindings into a temp directory and runs
`deno check` on them, so a generator change that emits invalid TypeScript is
caught without touching the caller's tree.

Exit codes: 77 when deno is unavailable (CTest treats this as a skip),
otherwise the exit code of `kwxgen check`.
"""

from __future__ import annotations

import argparse
import shutil
import subprocess
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_ROOT = SCRIPT_DIR.parent.parent

SKIP_RETURN_CODE = 77


def parse_arguments(argv: list[str] | None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Run `kwxgen check`, skipping when deno is not installed."
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
        "--deno",
        default=None,
        help="Path or command name for deno (default: discover via PATH)",
    )
    return parser.parse_args(argv)


def find_deno(explicit: str | None) -> str | None:
    """Return a usable deno command, or None when deno is not installed."""
    if explicit:
        candidate = Path(explicit)
        if candidate.is_file():
            return str(candidate)
        return shutil.which(explicit)
    return shutil.which("deno")


def resolve_path(root: Path, path: Path) -> Path:
    if not path.is_absolute():
        path = root / path
    return path.resolve()


def main(argv: list[str] | None = None) -> int:
    options = parse_arguments(argv)
    root = options.root.resolve()
    kwxgen = resolve_path(root, Path(options.kwxgen))

    deno = find_deno(options.deno)
    if deno is None:
        print("SKIP: deno executable not found", file=sys.stderr)
        return SKIP_RETURN_CODE

    if not kwxgen.is_file():
        print(f"error: kwxgen executable not found at {kwxgen}", file=sys.stderr)
        return 1

    command = [
        str(kwxgen),
        "check",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--deno",
        deno,
    ]
    print(f"--- {' '.join(command)}")
    completed = subprocess.run(command, cwd=str(root), check=False)
    return completed.returncode


if __name__ == "__main__":
    sys.exit(main())
