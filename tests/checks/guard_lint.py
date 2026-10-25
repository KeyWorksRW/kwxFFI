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
from collections.abc import Iterator
from dataclasses import dataclass, field
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_ALLOWLIST = SCRIPT_DIR / "guard_allowlist.txt"

PLATFORM_RE = re.compile(
    r"\b(__WINDOWS__|_WIN32|_WIN64|__APPLE__|__MACH__|__linux__|__unix__"
    r"|__WXMSW__|__WXGTK__|__WXOSX__|__WXMAC__|wxHAS_[A-Z0-9_]+)\b"
)
FEATURE_RE = re.compile(r"\bwxUSE_[A-Za-z0-9_]+\b")
HEADER_GUARD_RE = re.compile(r"_(?:H|H_|HPP|HXX)$")

# Feature guards that the generator deliberately treats as "always declared".
ALLOWED_FEATURES = frozenset(
    {
        "wxUSE_GUI",
        "wxUSE_ACCESSIBILITY",
        "wxUSE_UNICODE_UTF8",
        "wxUSE_GRAPHICS_CONTEXT",
    }
)

DIRECTIVE_RE = re.compile(r"^#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)$")
DEFINE_RE = re.compile(r"^#\s*define\b")

CLASS_FORM_RE = re.compile(r"^TClassDef(?:Extend)?\s*\(")
CLASS_NAME_RE = re.compile(r"^TClassDef(?:Extend)?\s*\(\s*([A-Za-z_]\w*)")
FUNCTION_FORM_RE = re.compile(
    r"^(?:EXPORT\s+)?(?:[A-Za-z_]\w*(?:\s*\([^()]*\))?\s+)*[A-Za-z_]\w*\s*\("
)
REJECT_PREFIXES = ("//", "/*", "*", "#")
REJECT_WORDS_RE = re.compile(
    r"^(?:return|if|for|while|switch|template|using|typedef|namespace|class"
    r"|struct|enum|static_assert)\b"
)
IDENTIFIER_RE = re.compile(r"^[A-Za-z_]\w*$")


@dataclass
class GuardFrame:
    """One level of conditional nesting.

    ``#elif``/``#else`` keep the frame alive so the platform flag survives the
    whole ``#if``/``#elif``/``#else`` chain.
    """

    conditions: list[str]
    platform: bool
    features: set[str] = field(default_factory=set)
    ignored: bool = False


@dataclass(frozen=True)
class GuardState:
    """The active guard state for one source line."""

    conditions: tuple[str, ...]
    platform: bool
    features: tuple[str, ...]

    @property
    def condition_text(self) -> str:
        return " && ".join(condition for condition in self.conditions if condition)


def strip_comment(text: str) -> str:
    """Remove a trailing ``//`` comment from a preprocessor condition."""
    comment = text.find("//")
    if comment != -1:
        text = text[:comment]
    return text.strip()


def has_platform_token(text: str) -> bool:
    return PLATFORM_RE.search(text) is not None


def state_from_stack(stack: list[GuardFrame]) -> GuardState:
    active = [frame for frame in stack if not frame.ignored]
    conditions = tuple(
        frame.conditions[0] for frame in active if frame.conditions and frame.conditions[0]
    )
    features = sorted({token for frame in active for token in frame.features})
    return GuardState(conditions, any(frame.platform for frame in active), tuple(features))


def apply_directive(stack: list[GuardFrame], kind: str, rest: str) -> None:
    if kind in ("if", "ifdef", "ifndef"):
        condition = strip_comment(rest)
        ignored = kind == "ifndef" and HEADER_GUARD_RE.search(condition) is not None
        stack.append(
            GuardFrame(
                conditions=[condition],
                platform=has_platform_token(condition),
                features=set(FEATURE_RE.findall(condition)),
                ignored=ignored,
            )
        )
        return
    if kind == "endif":
        if stack:
            stack.pop()
        return
    if not stack:
        return
    frame = stack[-1]
    if kind == "elif":
        condition = strip_comment(rest)
        frame.conditions.append(condition)
        frame.platform = frame.platform or has_platform_token(condition)
        frame.features.update(FEATURE_RE.findall(condition))


def iter_source_lines(path: Path) -> Iterator[tuple[int, str, GuardState]]:
    """Yield ``(line_number, line, state)`` for non-directive source lines."""
    stack: list[GuardFrame] = []
    in_define = False
    text = path.read_text(encoding="utf-8", errors="replace")
    for number, raw in enumerate(text.splitlines(), 1):
        stripped = raw.strip()
        if not stripped:
            continue
        directive = DIRECTIVE_RE.match(stripped)
        if directive:
            apply_directive(stack, directive.group(1), directive.group(2))
            in_define = False
            continue
        if in_define:
            if not stripped.endswith("\\"):
                in_define = False
            continue
        if DEFINE_RE.match(stripped) and stripped.endswith("\\"):
            in_define = True
            continue
        yield number, raw, state_from_stack(stack)


def parse_free_function(line: str) -> str | None:
    """Mirror ``ParseFreeFunction`` from ``kwxgen/src/constants_parser.cpp``.

    Return types are macro-wrapped (``TClass(wxString) wxFileSelector(...)``),
    so the symbol is the identifier immediately before the function's opening
    paren -- the paren that matches the last ``)`` before the trailing ``;``.
    """
    semicolon = line.rfind(";")
    if semicolon == -1:
        return None
    close_index = line.rfind(")", 0, semicolon)
    if close_index == -1:
        return None

    depth = 0
    open_index = -1
    index = close_index
    while index >= 0:
        char = line[index]
        if char == ")":
            depth += 1
        elif char == "(":
            depth -= 1
            if depth == 0:
                open_index = index
                break
        index -= 1
    if open_index == -1:
        return None

    prefix = line[:open_index].rstrip()
    if not prefix:
        return None

    last_space = max(prefix.rfind(" "), prefix.rfind("\t"))
    last_close_paren = prefix.rfind(")")
    if last_close_paren != -1 and (last_space == -1 or last_close_paren > last_space):
        candidate = prefix[last_close_paren + 1 :].strip()
    elif last_space != -1:
        candidate = prefix[last_space + 1 :].strip()
    else:
        return None
    return candidate if IDENTIFIER_RE.match(candidate) else None


def detect_declaration(line: str) -> tuple[str, str] | None:
    """Return ``(kind, symbol)`` for a declaration line, else ``None``.

    ``kind`` is ``"function"`` or ``"class"``. A ``TClassDef`` line usually
    carries its first method on the same line, so the function symbol wins over
    the class name.
    """
    stripped = line.strip()
    if not stripped:
        return None
    if stripped.startswith(REJECT_PREFIXES):
        return None
    if REJECT_WORDS_RE.match(stripped):
        return None

    class_form = CLASS_FORM_RE.match(stripped) is not None
    function_form = FUNCTION_FORM_RE.match(stripped) is not None and (
        ";" in stripped or stripped.endswith("(")
    )

    if class_form:
        symbol = parse_free_function(stripped)
        if symbol:
            return "function", symbol
        match = CLASS_NAME_RE.match(stripped)
        if match:
            return "class", match.group(1)
        return None

    if function_form:
        symbol = parse_free_function(stripped)
        if symbol:
            return "function", symbol
    return None


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
    for number, line, state in iter_source_lines(path):
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
