#!/usr/bin/env python3
"""C-includability check for the kwxFFI public headers.

cgo compiles the preamble of a Go file as C99, not C++. The Go backend emits
``#include "kwx_classes.h"`` (plus the events, keys, and constants headers), so a
defect that only appears in a C translation unit -- a stray C++ ``using``, a
missing ``EXPORT`` definition, an implicit-int declaration -- breaks every Go
consumer even though the C++ library builds cleanly.

This checker compiles the exact include set the Go backend emits as C99 and
reports a failure when the compiler rejects it. Anything that kwxgen parses but
a C compiler cannot see (for example a declaration hidden behind ``wxUSE_*``)
shows up later as an unresolved ``C.<symbol>`` in cgo, which is why the guarded
declarations must stay visible to C.

Exit codes: 0 = headers compile as C, 1 = compiler error, 77 = no C compiler.
Python standard library only; Python 3.9+.
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
SKIP_RETURN_CODE = 77

# Candidate C compilers, in preference order. ``CC`` overrides the list.
COMPILER_CANDIDATES = ("clang", "clang-21", "clang-20", "gcc", "cc")

# The includes lang_go.cpp emits for the cgo preamble.
PREAMBLE = """\
#include "kwx_classes.h"
#include "kwx_events.h"
#include "kwx_keys.h"
#include "kwx_constants.h"
#include <stdlib.h>
"""


def discover_compiler() -> list[str] | None:
    """Return the compiler command (as argv prefix), or None when unavailable."""
    override = os.environ.get("CC", "").strip()
    if override:
        command = override.split()
        if command and shutil.which(command[0]):
            return command
        return None
    for candidate in COMPILER_CANDIDATES:
        if shutil.which(candidate):
            return [candidate]
    return None


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Compile the public headers as C99 the way cgo does."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=SCRIPT_DIR.parent.parent,
        help="Repository root (default: the parent of the tests directory)",
    )
    options = parser.parse_args(argv)

    root = options.root.resolve()
    include_dir = root / "include"
    if not include_dir.is_dir():
        print(f"error: no include directory under {root}", file=sys.stderr)
        return 1

    compiler = discover_compiler()
    if compiler is None:
        print("skip: no C compiler found (set CC to run this check)")
        return SKIP_RETURN_CODE

    with tempfile.TemporaryDirectory(prefix="kwxffi_c_") as temp_dir:
        probe = Path(temp_dir) / "kwxffi_c_includability.c"
        probe.write_text(PREAMBLE, encoding="utf-8")
        command = [
            *compiler,
            "-std=c99",
            "-fsyntax-only",
            "-I",
            str(include_dir),
            "-x",
            "c",
            str(probe),
        ]
        completed = subprocess.run(
            command,
            cwd=str(root),
            check=False,
            capture_output=True,
            text=True,
        )

    if completed.returncode != 0:
        print(
            "error: the public headers do not compile as C99; a cgo consumer will fail"
        )
        print(" ".join(command))
        sys.stdout.write(completed.stdout)
        sys.stderr.write(completed.stderr)
        return 1

    print(f"PASS: include/*.h compile as C99 ({compiler[0]})")
    return 0


if __name__ == "__main__":
    sys.exit(main())
