#!/usr/bin/env python3
"""Shared driver for ``kwxgen exports``.

Both ``export_snapshot`` (which verifies the digest baseline) and
``symbol_resolve`` (which resolves symbols against a built shared library) need
the same generated export manifest. This module runs the generator and parses
the Windows module-definition file it writes.

Python standard library only; Python 3.9+.
"""

from __future__ import annotations

import subprocess
from pathlib import Path

DEF_FILE_NAME = "kwxffi_exports.def"
MAP_FILE_NAME = "kwxffi_exports.map"
EXP_FILE_NAME = "kwxffi_exports.exp"


def generate(kwxgen: Path, root: Path, out_dir: Path) -> int:
    """Run ``kwxgen exports`` into ``out_dir``; return its exit code."""
    command = [
        str(kwxgen),
        "exports",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--out",
        str(out_dir),
    ]
    print(f"--- {' '.join(command)}")
    completed = subprocess.run(command, cwd=str(root), check=False)
    return completed.returncode


def read_text_lines(path: Path) -> list[str]:
    # splitlines() strips both LF and CRLF, which matters because
    # .gitattributes sets `* text=auto` and generated files are CRLF on Windows.
    return path.read_text(encoding="utf-8", errors="replace").splitlines()


def read_def_symbols(path: Path) -> list[str]:
    """Parse a Windows module-definition file: drop comments and the header."""
    symbols: list[str] = []
    for raw_line in read_text_lines(path):
        line = raw_line.strip()
        if not line or line.startswith(";") or line == "EXPORTS":
            continue
        symbols.append(line)
    return symbols
