#!/usr/bin/env python3
"""Platform-guard policy lint for the kwxFFI public headers.

The binding generator (kwxgen) skips preprocessor directives, so it parses
every declaration in ``include/*.h`` regardless of any guard around it. A
declaration wrapped in a platform guard therefore leaks into the generated
bindings and only links on the guarded platform(s) -- the defect class tracked
in issue #62.

This checker walks every ``include/*.h`` file with a conditional stack and
reports declarations found under a platform guard as errors. Declarations under
a known feature guard (``wxUSE_GUI`` and friends) are reported as notes because
the generator intentionally exposes the union of feature-gated declarations.

Exit codes: 0 = no error-level findings, 1 = at least one error.
Python standard library only; Python 3.9+.
"""

from __future__ import annotations

import argparse
import fnmatch
import re
import sys
from dataclasses import dataclass
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from _guardscan import detect_declaration, iter_declarations

DEFAULT_ALLOWLIST = SCRIPT_DIR / "guard_allowlist.txt"

# Feature guards that the generator deliberately treats as "always declared".
ALLOWED_FEATURES = frozenset(
    {
        "wxUSE_GUI",
        "wxUSE_ACCESSIBILITY",
        "wxUSE_UNICODE_UTF8",
        "wxUSE_GRAPHICS_CONTEXT",
    }
)


@dataclass(frozen=True)
class AllowlistEntry:
    path_glob: str
    condition_regex: re.Pattern[str]
    reason: str

    def matches(self, relative_path: str, condition: str) -> bool:
        return fnmatch.fnmatch(relative_path, self.path_glob) and (
            self.condition_regex.search(condition) is not None
        )


def load_allowlist(path: Path) -> list[AllowlistEntry]:
    entries: list[AllowlistEntry] = []
    if not path.is_file():
        return entries
    for number, raw in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        parts = line.split("|")
        if len(parts) != 3:
            print(
                f"{path}:{number}: warning: allowlist entry needs "
                "'path_glob|condition_regex|reason'",
                file=sys.stderr,
            )
            continue
        path_glob, condition, reason = (part.strip() for part in parts)
        try:
            pattern = re.compile(condition)
        except re.error as error:
            print(
                f"{path}:{number}: warning: invalid condition regex: {error}",
                file=sys.stderr,
            )
            continue
        entries.append(AllowlistEntry(path_glob, pattern, reason))
    return entries


@dataclass
class Finding:
    relative_path: str
    line: int
    severity: str
    symbol: str
    guard_kind: str
    condition: str


def lint_file(path: Path, root: Path, allowlist: list[AllowlistEntry]) -> list[Finding]:
    relative_path = path.relative_to(root).as_posix()
    findings: list[Finding] = []
    for number, line, state in iter_declarations(path):
        if not state.platform and not state.features:
            continue
        detected = detect_declaration(line)
        if detected is None:
            continue
        _, symbol = detected

        disallowed = [
            feature for feature in state.features if feature not in ALLOWED_FEATURES
        ]
        severity = "error" if (state.platform or disallowed) else "note"
        guard_kind = "platform" if state.platform else "feature"
        condition = state.condition_text

        if severity == "error" and any(
            entry.matches(relative_path, condition) for entry in allowlist
        ):
            severity = "note"

        findings.append(
            Finding(relative_path, number, severity, symbol, guard_kind, condition)
        )
    return findings


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Report declarations wrapped in platform guards."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=SCRIPT_DIR.parent.parent,
        help="Repository root (default: the parent of the tests directory)",
    )
    parser.add_argument(
        "--allowlist",
        type=Path,
        default=DEFAULT_ALLOWLIST,
        help="Allowlist file (default: tests/checks/guard_allowlist.txt)",
    )
    options = parser.parse_args(argv)

    root = options.root.resolve()
    include_dir = root / "include"
    if not include_dir.is_dir():
        print(f"error: no include directory under {root}", file=sys.stderr)
        return 1

    allowlist = load_allowlist(options.allowlist)

    findings: list[Finding] = []
    for path in sorted(include_dir.glob("*.h")):
        findings.extend(lint_file(path, root, allowlist))

    for finding in findings:
        print(
            f"{finding.relative_path}:{finding.line}: {finding.severity}: "
            f"{finding.symbol} inside {finding.guard_kind} guard "
            f"'{finding.condition}'"
        )

    errors = sum(1 for finding in findings if finding.severity == "error")
    notes = len(findings) - errors
    print(f"{errors} error(s), {notes} note(s)")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
