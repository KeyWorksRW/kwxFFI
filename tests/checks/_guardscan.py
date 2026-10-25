#!/usr/bin/env python3
"""Shared platform-guard scanner for the kwxFFI checker scripts.

The binding generator (kwxgen) skips preprocessor directives, so it parses every
declaration in ``include/*.h`` regardless of any guard around it. ``guard_lint``
reports the declarations that are wrapped in a platform guard and
``guard_parity`` compares the guard state of a declaration with the guard state
of its definition in ``src/*.cpp``. Both need the same conditional stack and the
same declaration detector, which live here.

The scanner is multi-line aware: ``iter_declarations`` joins a declaration that
spans several physical lines into one logical line before detection. Without
that, a declaration such as::

    void wxTaskBarButton_SetOverlayIcon(TSelf(wxTaskBarButton) pObject, TClass(wxIcon) icon,
                                        TClass(wxString) description);

is invisible to both checkers.

Python standard library only; Python 3.9+.
"""

from __future__ import annotations

import re
from collections.abc import Iterator
from dataclasses import dataclass, field
from pathlib import Path

PLATFORM_RE = re.compile(
    r"\b(__WINDOWS__|_WIN32|_WIN64|__APPLE__|__MACH__|__linux__|__unix__"
    r"|__WXMSW__|__WXGTK__|__WXOSX__|__WXMAC__|wxHAS_[A-Z0-9_]+)\b"
)
FEATURE_RE = re.compile(r"\bwxUSE_[A-Za-z0-9_]+\b")
HEADER_GUARD_RE = re.compile(r"_(?:H|H_|HPP|HXX)$")

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

# A comment line cannot contribute to a declaration, and a line that ends with
# one of these characters closes the declaration it belongs to.
COMMENT_PREFIXES = ("//", "/*", "*")
TERMINATOR_SUFFIXES = (";", "{", "}", ":")


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

    @property
    def label(self) -> str:
        if self.platform:
            return f"guarded({self.condition_text})"
        if self.features:
            return f"feature({self.condition_text})"
        return "unguarded"


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
    """Yield ``(line_number, line, state)`` for non-directive physical lines."""
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


def iter_declarations(path: Path) -> Iterator[tuple[int, str, GuardState]]:
    """Yield ``(first_line_number, joined_text, state)`` per logical line.

    Consecutive non-blank, non-comment, non-directive lines are buffered and
    joined with a single space, so a declaration that spans several physical
    lines is detected as one declaration. The buffer is flushed at a blank line,
    a comment line, a preprocessor line, or a line ending with ``;``, ``{``,
    ``}``, or ``:`` -- the characters that end or open a declaration.

    The state always describes the lines in the buffer: a directive flushes the
    buffer before it changes the conditional stack.
    """
    stack: list[GuardFrame] = []
    in_define = False
    parts: list[str] = []
    first_line = 0

    def take() -> tuple[int, str, GuardState] | None:
        nonlocal parts, first_line
        if not parts:
            return None
        record = (first_line, " ".join(parts), state_from_stack(stack))
        parts = []
        first_line = 0
        return record

    text = path.read_text(encoding="utf-8", errors="replace")
    for number, raw in enumerate(text.splitlines(), 1):
        stripped = raw.strip()
        if not stripped:
            pending = take()
            if pending is not None:
                yield pending
            continue
        if stripped.startswith("#"):
            pending = take()
            if pending is not None:
                yield pending
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
        if in_define:
            if not stripped.endswith("\\"):
                in_define = False
            continue
        if stripped.startswith(COMMENT_PREFIXES):
            pending = take()
            if pending is not None:
                yield pending
            continue
        if not parts:
            first_line = number
        parts.append(stripped)
        if stripped.endswith(TERMINATOR_SUFFIXES):
            pending = take()
            if pending is not None:
                yield pending
