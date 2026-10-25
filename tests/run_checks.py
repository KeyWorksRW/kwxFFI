#!/usr/bin/env python3
"""Run the kwxFFI checks without requiring a CMake build.

`--static` runs only the checks that read the source tree. Without it the
export snapshot and `deno check` wrappers run too, using the newest kwxgen
binary that can be found under `bin/` or `build/`.

Exit code is 1 when any check failed, 0 otherwise (skips are not failures).
"""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_ROOT = SCRIPT_DIR.parent

SKIP_RETURN_CODE = 77

# Ordered by preference: a checked-in release binary first, then test builds.
KWXGEN_GLOBS = (
    "bin/*/kwxgen",
    "bin/*/kwxgen.exe",
    "build/tests/bin/*/kwxgen*",
    "build/**/bin/*/kwxgen*",
)


def discover_kwxgen(root: Path, explicit: str | None) -> Path | None:
    """Return a kwxgen executable path, or None when there is none."""
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = root / candidate
        if candidate.is_file():
            return candidate.resolve()
        print(f"warning: kwxgen binary not found at {candidate}", file=sys.stderr)
        return None

    found: list[Path] = []
    for pattern in KWXGEN_GLOBS:
        for candidate in root.glob(pattern):
            if candidate.is_file() and candidate.name.startswith("kwxgen"):
                found.append(candidate.resolve())

    if not found:
        return None

    unique = sorted(set(found))
    release_builds = [item for item in unique if "release" in str(item).lower()]
    candidates = release_builds or unique
    return max(candidates, key=lambda item: item.stat().st_mtime)


def run_check(label: str, script: Path, arguments: list[str], root: Path) -> str:
    """Run one checker and return its status line text."""
    if not script.is_file():
        return "SKIP (not implemented yet)"

    command = [sys.executable, str(script), *arguments]
    print(f"--- {label}")
    print(f"    {' '.join(command)}")
    completed = subprocess.run(command, cwd=str(root), check=False)

    if completed.returncode == 0:
        return "PASS"
    if completed.returncode == SKIP_RETURN_CODE:
        return "SKIP (exit 77)"
    return f"FAIL (exit {completed.returncode})"


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Run the kwxFFI source checks.")
    parser.add_argument(
        "--root",
        type=Path,
        default=DEFAULT_ROOT,
        help="Repository root (default: the parent of this script's directory)",
    )
    parser.add_argument(
        "--static",
        action="store_true",
        help="Run only the checks that need no built kwxgen binary",
    )
    parser.add_argument(
        "--kwxgen",
        default=None,
        help="Path to a kwxgen executable (default: auto-discover under bin/ or build/)",
    )
    options = parser.parse_args(argv)

    root = options.root.resolve()
    checks_dir = SCRIPT_DIR / "checks"

    results: list[tuple[str, str]] = []

    for name in ("guard_lint", "guard_parity"):
        status = run_check(name, checks_dir / f"{name}.py", ["--root", str(root)], root)
        results.append((name, status))

    kwxgen = discover_kwxgen(root, options.kwxgen)

    if options.static:
        print("--- export_snapshot: not run (--static)")
        print("--- deno_check: not run (--static)")
    elif kwxgen is None:
        results.append(("export_snapshot", "SKIP (kwxgen binary not found)"))
        results.append(("deno_check", "SKIP (kwxgen binary not found)"))
    else:
        for name in ("export_snapshot", "deno_check"):
            status = run_check(
                name,
                checks_dir / f"{name}.py",
                ["--root", str(root), "--kwxgen", str(kwxgen)],
                root,
            )
            results.append((name, status))

    print()
    width = max(len(name) for name, _ in results)
    for name, status in results:
        print(f"{name.ljust(width)}  {status}")

    passed = sum(1 for _, status in results if status == "PASS")
    failed = sum(1 for _, status in results if status.startswith("FAIL"))
    skipped = sum(1 for _, status in results if status.startswith("SKIP"))
    print(f"\n{passed} passed, {failed} failed, {skipped} skipped")

    return 1 if failed > 0 else 0


if __name__ == "__main__":
    sys.exit(main())
