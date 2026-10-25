#!/usr/bin/env python3
"""Declaration/definition platform-guard parity for kwxFFI.

``guard_lint`` looks at headers alone. This checker answers the complementary
question: does the implementation in ``src/*.cpp`` agree with the header about
whether a symbol is platform-specific?

- ``header-guarded/src-unguarded`` -- the header hides the declaration on other
  platforms but the definition is compiled everywhere.
- ``header-unguarded/src-guarded`` -- the declaration is always visible and the
  generator emits it, but the definition only exists on the guarded platforms,
  so the generated binding fails to link elsewhere.
- ``guard-condition-mismatch`` -- both sides are guarded, but by different
  platform guards.
- ``no-definition-found`` -- a platform-guarded declaration has no ``EXPORT``
  definition at all (reported as a note: the definition may live outside the
  scanned translation units).

Only platform-guard state is compared. Feature guards (``wxUSE_*``) are
reported in the guard columns and, when they differ between the two sides, as a
note. An unguarded declaration with no definition is deliberately not reported:
it may be emitted by a macro or by another translation unit, and it carries no
guard-parity information.

Exit codes: 0 = no error-level findings, 1 = at least one error.
Python standard library only; Python 3.9+.
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from _guardscan import PLATFORM_RE, GuardState, detect_declaration, iter_declarations

EXPORT_RE = re.compile(r"^\s*EXPORT\s+")


def parse_export_symbol(line: str) -> str | None:
    """Return the identifier immediately before the first ``(`` on an EXPORT line."""
    open_index = line.find("(")
    head = line if open_index == -1 else line[:open_index]
    identifiers = re.findall(r"[A-Za-z_]\w*", head)
    if not identifiers:
        return None
    return identifiers[-1]


@dataclass(frozen=True)
class Declaration:
    symbol: str
    location: str
    state: GuardState


@dataclass(frozen=True)
class Definition:
    symbol: str
    location: str
    state: GuardState


@dataclass
class Finding:
    severity: str
    category: str
    symbol: str
    header_state: str
    src_state: str
    location: str
    note: str = ""


def collect_declarations(root: Path) -> dict[str, list[Declaration]]:
    declarations: dict[str, list[Declaration]] = {}
    include_dir = root / "include"
    for path in sorted(include_dir.glob("*.h")):
        relative_path = path.relative_to(root).as_posix()
        for number, line, state in iter_declarations(path):
            detected = detect_declaration(line)
            if detected is None:
                continue
            _, symbol = detected
            location = f"{relative_path}:{number}"
            declarations.setdefault(symbol, []).append(
                Declaration(symbol, location, state)
            )
    return declarations


def collect_definitions(root: Path) -> dict[str, list[Definition]]:
    definitions: dict[str, list[Definition]] = {}
    source_dir = root / "src"
    for path in sorted(source_dir.glob("*.cpp")):
        relative_path = path.relative_to(root).as_posix()
        for number, line, state in iter_declarations(path):
            if EXPORT_RE.match(line) is None:
                continue
            symbol = parse_export_symbol(line)
            if symbol is None:
                continue
            location = f"{relative_path}:{number}"
            definitions.setdefault(symbol, []).append(Definition(symbol, location, state))
    return definitions


def preferred_declaration(records: list[Declaration]) -> Declaration:
    for record in records:
        if record.state.platform:
            return record
    for record in records:
        if record.state.features:
            return record
    return records[0]


def preferred_definition(records: list[Definition]) -> Definition:
    for record in records:
        if record.state.platform:
            return record
    return records[0]


def platform_tokens(state: GuardState) -> frozenset[str]:
    return frozenset(PLATFORM_RE.findall(state.condition_text))


def compare(
    symbol: str,
    declaration: Declaration | None,
    definition: Definition | None,
) -> Finding | None:
    if declaration is None:
        if definition is None:
            return None
        return Finding(
            "note",
            "no-declaration-found",
            symbol,
            "missing",
            definition.state.label,
            definition.location,
        )

    if definition is None:
        if declaration.state.platform:
            return Finding(
                "note",
                "no-definition-found",
                symbol,
                declaration.state.label,
                "missing",
                declaration.location,
            )
        return None

    header_state = declaration.state
    src_state = definition.state
    finding = Finding(
        "error",
        "",
        symbol,
        header_state.label,
        src_state.label,
        definition.location,
    )

    if header_state.platform and not src_state.platform:
        finding.category = "header-guarded/src-unguarded"
        return finding
    if src_state.platform and not header_state.platform:
        finding.category = "header-unguarded/src-guarded"
        return finding
    if header_state.platform and src_state.platform:
        if platform_tokens(header_state) != platform_tokens(src_state):
            finding.category = "guard-condition-mismatch"
            return finding
        if set(header_state.features) != set(src_state.features):
            finding.severity = "note"
            finding.category = "feature-guard-mismatch"
            finding.location = declaration.location
            finding.note = "feature guards differ"
            return finding
        return None

    return None


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Compare header and definition platform guards."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=SCRIPT_DIR.parent.parent,
        help="Repository root (default: the parent of the tests directory)",
    )
    options = parser.parse_args(argv)

    root = options.root.resolve()
    if not (root / "include").is_dir() or not (root / "src").is_dir():
        print(f"error: no include/ or src/ directory under {root}", file=sys.stderr)
        return 1

    declarations = collect_declarations(root)
    definitions = collect_definitions(root)

    candidates: set[str] = set()
    for symbol, records in declarations.items():
        if any(record.state.platform for record in records):
            candidates.add(symbol)
    for symbol, records in definitions.items():
        if any(record.state.platform for record in records):
            candidates.add(symbol)

    findings: list[Finding] = []
    for symbol in sorted(candidates):
        declaration = (
            preferred_declaration(declarations[symbol]) if symbol in declarations else None
        )
        definition = (
            preferred_definition(definitions[symbol]) if symbol in definitions else None
        )
        finding = compare(symbol, declaration, definition)
        if finding is not None:
            findings.append(finding)

    widths = {
        "severity": len("severity"),
        "symbol": len("symbol"),
        "header": len("header"),
        "src": len("src"),
        "location": len("file:line"),
        "category": len("status"),
    }
    for finding in findings:
        widths["severity"] = max(widths["severity"], len(finding.severity))
        widths["symbol"] = max(widths["symbol"], len(finding.symbol))
        widths["header"] = max(widths["header"], len(finding.header_state))
        widths["src"] = max(widths["src"], len(finding.src_state))
        widths["location"] = max(widths["location"], len(finding.location))
        widths["category"] = max(widths["category"], len(finding.category))

    print(
        f"{'severity'.ljust(widths['severity'])}  "
        f"{'symbol'.ljust(widths['symbol'])}  "
        f"{'header'.ljust(widths['header'])}  "
        f"{'src'.ljust(widths['src'])}  "
        f"{'file:line'.ljust(widths['location'])}  status"
    )
    for finding in findings:
        print(
            f"{finding.severity.ljust(widths['severity'])}  "
            f"{finding.symbol.ljust(widths['symbol'])}  "
            f"{finding.header_state.ljust(widths['header'])}  "
            f"{finding.src_state.ljust(widths['src'])}  "
            f"{finding.location.ljust(widths['location'])}  {finding.category}"
        )

    errors = sum(1 for finding in findings if finding.severity == "error")
    notes = len(findings) - errors
    print(
        f"\nchecked {len(candidates)} guard-relevant symbol(s) against "
        f"{len(declarations)} header declaration(s) and "
        f"{len(definitions)} definition(s)"
    )
    print(f"{errors} error(s), {notes} note(s)")
    return 1 if errors else 0


if __name__ == "__main__":
    sys.exit(main())
