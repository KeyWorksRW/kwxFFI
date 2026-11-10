#!/usr/bin/env python3
"""Fail when a kwxgen backend wraps less of the FFI surface than TypeScript.

Runs `kwxgen coverage --profile full --require-parity`, which compares every
backend with the TypeScript reference: each TypeScript-wrapped class must be
wrapped (or explicitly consumer-provided) in every other backend, and each
class must expose at least as many valid methods as the parsed model declares,
including mixin methods. Free-function, event, key and constant counts are
checked against the model too.

Exit codes: 0 when parity holds, 1 when any backend lags the reference, and 77
when no kwxgen binary is available (CTest treats 77 as a skip).
"""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_ROOT = SCRIPT_DIR.parent.parent

# Reuse the discovery rules from run_checks.py so both entry points agree on
# which kwxgen binary is "newest".
if str(SCRIPT_DIR.parent) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR.parent))

from run_checks import SKIP_RETURN_CODE, discover_kwxgen


def parse_arguments(argv: list[str] | None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Check that every kwxgen backend covers the TypeScript surface."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=DEFAULT_ROOT,
        help="Repository root (default: the parent of this script's directory)",
    )
    parser.add_argument(
        "--kwxgen",
        default=None,
        help="Path to a kwxgen executable (default: auto-discover under bin/ or build/)",
    )
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    options = parse_arguments(argv)
    root = options.root.resolve()

    kwxgen = discover_kwxgen(root, options.kwxgen)
    if kwxgen is None:
        print("SKIP: no kwxgen binary found; build kwxgen first", file=sys.stderr)
        return SKIP_RETURN_CODE

    headers_dir = root / "include"
    defs_file = root / "src" / "kwx_defs.cpp"
    for required_path in (headers_dir, defs_file):
        if not required_path.exists():
            print(f"error: required input not found at {required_path}", file=sys.stderr)
            return 1

    command = [
        str(kwxgen),
        "coverage",
        "--headers",
        str(headers_dir),
        "--defs",
        str(defs_file),
        "--profile",
        "full",
        "--require-parity",
    ]
    print(f"running {' '.join(command)}")
    try:
        completed = subprocess.run(command, cwd=str(root), check=False)
    except OSError as launch_error:
        print(f"error: cannot run {kwxgen}: {launch_error}", file=sys.stderr)
        return 1

    if completed.returncode != 0:
        print(
            f"error: binding coverage parity failed (kwxgen exit {completed.returncode})",
            file=sys.stderr,
        )
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
