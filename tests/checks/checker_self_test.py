#!/usr/bin/env python3
"""Self-test for the guard checkers.

``guard_lint`` and ``guard_parity`` are the only thing standing between a
platform-guarded declaration and a binding that fails to link, so they get their
own test. ``tests/fixtures/lint_tree`` holds four guard shapes:

1. a platform-guarded declaration with no definition,
2. a multi-line unguarded declaration whose definition is guarded,
3. a declaration/definition pair with matching guards,
4. a ``wxUSE_GUI``-only feature guard.

Every assertion runs both checkers against that tree and compares exit codes and
severities. This is what pins the multi-line detector: without it, shape 2 is
invisible and assertion 4 fails.

Exit codes: 0 = every assertion passed, 1 = at least one mismatch.
Python standard library only; Python 3.9+.
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
FIXTURE_ROOT = SCRIPT_DIR.parent / "fixtures" / "lint_tree"


def run_checker(name: str) -> tuple[int, str]:
    """Run one checker against the fixture tree; return (exit_code, output)."""
    command = [
        sys.executable,
        str(SCRIPT_DIR / f"{name}.py"),
        "--root",
        str(FIXTURE_ROOT),
    ]
    completed = subprocess.run(command, capture_output=True, check=False, text=True)
    return completed.returncode, completed.stdout + completed.stderr


def finding_line(output: str, symbol: str) -> str:
    """Return the first output line that mentions ``symbol``."""
    for line in output.splitlines():
        if symbol in line:
            return line
    return ""


def expect(label: str, condition: bool) -> bool:
    print(f"{'PASS' if condition else 'FAIL'}: {label}")
    return condition


def main() -> int:
    lint_code, lint_output = run_checker("guard_lint")
    parity_code, parity_output = run_checker("guard_parity")

    guarded_lint = finding_line(lint_output, "wxFixtureGuardedFn")
    gui_lint = finding_line(lint_output, "wxFixtureGuiFn")
    multiline_parity = finding_line(parity_output, "wxFixtureMultilineFn")
    guarded_parity = finding_line(parity_output, "wxFixtureGuardedFn")

    results = [
        expect("guard_lint exits 1 on the fixture tree", lint_code == 1),
        expect(
            "guard_lint reports wxFixtureGuardedFn as an error and wxFixtureGuiFn as a note",
            ": error: wxFixtureGuardedFn" in guarded_lint
            and ": note: wxFixtureGuiFn" in gui_lint
            and "wxFixtureMultilineFn" not in lint_output,
        ),
        expect("guard_parity exits 1 on the fixture tree", parity_code == 1),
        expect(
            "guard_parity reports the multi-line mismatch, the missing definition, and no finding for the matching pair",
            "header-unguarded/src-guarded" in multiline_parity
            and "no-definition-found" in guarded_parity
            and "wxFixtureMatchedFn" not in parity_output,
        ),
    ]
    return 0 if all(results) else 1


if __name__ == "__main__":
    sys.exit(main())
