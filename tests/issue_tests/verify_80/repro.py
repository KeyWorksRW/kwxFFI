#!/usr/bin/env python3
"""Issue 80 reproducer: kwxgen must not rename TypeScript members.

The TypeScript emitter renames a member to ``<Member>__<Class>`` when the same
method reaches a class through two FFI wrappers whose return types disagree
(TypeScript forbids two overloads differing only by return type).  Issue 80
traces all eight renames to kwxFFI declarations whose return type did not match
the wrapped C++ method.

This script generates TypeScript bindings from the repository's own headers and
asserts that the emitted bindings contain no renamed members.  It needs only a
built ``kwxgen`` binary; no consumer repository checkout and no network access.

Usage:
    python tests/issue_tests/verify_80/repro.py [--root <repo>] [--kwxgen <exe>]

Exit codes: 0 fixed, 1 still broken, 77 skipped (no kwxgen binary).
"""

import argparse
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

SKIP_RETURN_CODE = 77

# Ordered by preference: checked-in release binaries first, then test builds.
KWXGEN_GLOBS = (
    "bin/*/kwxgen",
    "bin/*/kwxgen.exe",
    "kwxgen/bin/*/kwxgen*",
    "build/tests/bin/*/kwxgen*",
    "build/**/bin/*/kwxgen*",
)

RENAMED_MEMBER = re.compile(r"\b[A-Za-z_]\w*__wx\w*\b")


def discover_kwxgen(root, explicit):
    """Return a kwxgen executable path, or None when there is none."""
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = root / candidate
        return candidate.resolve() if candidate.is_file() else None

    found = []
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


def expect(label, ok, observed):
    """Print one EXPECTED/OBSERVED pair; return 1 when the assertion failed."""
    print("EXPECTED: " + label)
    print("OBSERVED: " + (("ok" if ok else "FAILED") if observed is None else observed))
    return 0 if ok else 1


def check_report(report):
    """Assert the --rename-report JSON describes zero renames."""
    if not report.is_file():
        return expect("kwxgen wrote a --rename-report file", False, str(report) + " does not exist")

    failures = expect("kwxgen wrote a --rename-report file", True, None)
    try:
        data = json.loads(report.read_text(encoding="utf-8"))
    except (OSError, ValueError) as error:
        return failures + expect("the rename report is valid JSON", False, str(error))

    count = data.get("count")
    renames = data.get("renames") or []
    failures += expect(
        "the rename report count is 0",
        count == 0,
        "count = %r" % (count,),
    )
    failures += expect(
        "the rename report lists no renamed member",
        len(renames) == 0,
        "renames = " + json.dumps(renames),
    )
    return failures


def check_generated(out_dir):
    """Assert no generated TypeScript file contains a <Member>__<Class> name."""
    if not out_dir.is_dir():
        return expect("kwxgen generated TypeScript output", False, str(out_dir) + " does not exist")

    failures = 0
    files = sorted(out_dir.rglob("*.ts"))
    failures += expect(
        "kwxgen emitted TypeScript files",
        len(files) > 0,
        "%d .ts file(s) under %s" % (len(files), out_dir),
    )

    hits = []
    for path in files:
        try:
            lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        except OSError as error:
            hits.append("%s: %s" % (path.name, error))
            continue
        for number, line in enumerate(lines, 1):
            match = RENAMED_MEMBER.search(line)
            if match:
                hits.append("%s:%d: %s" % (path.name, number, match.group(0)))

    failures += expect(
        "no generated member is renamed to <Member>__<Class>",
        len(hits) == 0,
        "no renamed member" if not hits else "; ".join(hits[:10]),
    )
    return failures


def main(argv=None):
    parser = argparse.ArgumentParser(description="Reproduce issue 80 (kwxgen TypeScript renames).")
    parser.add_argument("--root", default=None, help="Repository root")
    parser.add_argument("--kwxgen", default=None, help="Path to the kwxgen executable")
    options = parser.parse_args(argv)

    root = Path(options.root).resolve() if options.root else Path(__file__).resolve().parents[3]
    headers = root / "include"
    defs = root / "src" / "kwx_defs.cpp"
    if not headers.is_dir() or not defs.is_file():
        print("FAIL: %s or %s is missing; is --root the kwxFFI repository?" % (headers, defs))
        return 1

    kwxgen = discover_kwxgen(root, options.kwxgen)
    if kwxgen is None:
        print("SKIP: no kwxgen binary found under bin/, kwxgen/bin/, or build/")
        return SKIP_RETURN_CODE

    work_dir = Path(tempfile.mkdtemp(prefix="kwx_issue80_"))
    try:
        out_dir = work_dir / "ts"
        report = work_dir / "rename.json"
        command = [
            str(kwxgen),
            "generate",
            "--headers",
            str(headers),
            "--defs",
            str(defs),
            "--lang",
            "typescript",
            "--profile",
            "full",
            "--out",
            str(out_dir),
            "--rename-report",
            str(report),
        ]
        print("RUN: " + " ".join(command))
        completed = subprocess.run(
            command, cwd=str(root), capture_output=True, text=True, timeout=900
        )
        if completed.returncode != 0:
            print("EXPECTED: kwxgen generate exits 0")
            print("OBSERVED: exit code %d" % completed.returncode)
            print((completed.stderr or completed.stdout)[-2000:])
            return 1

        failures = check_report(report) + check_generated(out_dir)
    finally:
        shutil.rmtree(work_dir, ignore_errors=True)

    if failures:
        print("SUMMARY: %d assertion(s) failed -- the renames are still generated" % failures)
        return 1
    print("SUMMARY: all assertions passed -- no TypeScript member renames")
    return 0


if __name__ == "__main__":
    sys.exit(main())
