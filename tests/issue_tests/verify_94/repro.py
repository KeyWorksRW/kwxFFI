#!/usr/bin/env python3
"""Issue 94 reproducer: the four wxGeneric*Dialog classes are part of the FFI.

Issue 94 asks for wxGenericColourDialog, wxGenericFontDialog,
wxGenericFileDialog and wxGenericDirDialog to be declared in include/,
exported from src/, classified as GUI and emitted by kwxgen for every language
backend.

The generic implementations are not part of the wxMSW/wxGTK wxcore build
(only OSX_COMMON_SRC and UNIV_SRC list them), so the fix has to add
src/generic/{colrdlgg,fontdlgg,filedlgg,dirdlgg}.cpp to the wxcore target
before the wrappers can link.

Checks:
  A. include/kwx_dialogs_extra.h declares each class with `extends wxDialog`
     and every required accessor.
  B. src/ defines every declared symbol with EXPORT (guard_parity's contract).
  C. CMakeLists.txt adds the four portable generic dialog sources to wxcore.
  D. kwxgen generate emits the four class names for fortran, go, julia, lua and
     typescript, in both the full and the gui profile, deterministically.
  E. When a freshly built kwxFFI shared library is present, every new symbol
     resolves from it. Skipped when the library is missing or older than the
     sources, so the script also works on a source-only checkout.

Usage:
    python tests/issue_tests/verify_94/repro.py [--root <repo>] [--kwxgen <exe>]

Exit codes: 0 fixed, 1 still broken.
"""

import argparse
import ctypes
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

CLASSES = {
    "wxGenericColourDialog": [
        "wxGenericColourDialog_Create",
        "wxGenericColourDialog_GetColourData",
        "wxGenericColourDialog_Delete",
    ],
    "wxGenericFontDialog": [
        "wxGenericFontDialog_Create",
        "wxGenericFontDialog_GetFontData",
        "wxGenericFontDialog_Delete",
    ],
    "wxGenericFileDialog": [
        "wxGenericFileDialog_Create",
        "wxGenericFileDialog_GetPath",
        "wxGenericFileDialog_SetPath",
        "wxGenericFileDialog_GetFilename",
        "wxGenericFileDialog_SetFilename",
        "wxGenericFileDialog_GetWildcard",
        "wxGenericFileDialog_SetWildcard",
        "wxGenericFileDialog_GetFilterIndex",
        "wxGenericFileDialog_SetFilterIndex",
        "wxGenericFileDialog_SetCustomizeHook",
        "wxGenericFileDialog_Delete",
    ],
    "wxGenericDirDialog": [
        "wxGenericDirDialog_Create",
        "wxGenericDirDialog_GetPath",
        "wxGenericDirDialog_SetPath",
        "wxGenericDirDialog_GetPaths",
        "wxGenericDirDialog_GetMessage",
        "wxGenericDirDialog_SetMessage",
        "wxGenericDirDialog_Delete",
    ],
}

GENERIC_SOURCES = ("colrdlgg.cpp", "fontdlgg.cpp", "filedlgg.cpp", "dirdlgg.cpp")
LANGUAGES = ("fortran", "go", "julia", "lua", "typescript")

KWXGEN_GLOBS = (
    "bin/*/kwxgen",
    "bin/*/kwxgen.exe",
    "kwxgen/bin/*/kwxgen*",
    "build/tests/bin/*/kwxgen*",
)

LIBRARY_GLOBS = (
    "lib/shared/Debug/kwxFFI.dll",
    "lib/shared/Release/kwxFFI.dll",
    "lib/Debug/kwxFFI.dll",
    "lib/Release/kwxFFI.dll",
    "lib/kwxFFI.dll",
    "lib/shared/Release/libkwxFFI.so",
    "lib/shared/Debug/libkwxFFI.so",
    "lib/libkwxFFI.so",
)

failures = 0


def expect(label, ok, observed=None):
    global failures
    print("EXPECTED: " + label)
    print("OBSERVED: " + ("ok" if ok else ("FAILED" if observed is None else observed)))
    if not ok:
        failures += 1
    return ok


def find_first(root, globs, suffixes=()):
    for pattern in globs:
        for candidate in sorted(root.glob(pattern)):
            if candidate.is_file() and (not suffixes or candidate.suffix in suffixes):
                return candidate
    return None


def check_declarations(root):
    header = root / "include" / "kwx_dialogs_extra.h"
    if not header.is_file():
        expect("include/kwx_dialogs_extra.h exists", False, "missing")
        return
    text = header.read_text(encoding="utf-8")
    for class_name, methods in CLASSES.items():
        declared = re.search(
            r"TClassDefExtend\(\s*" + class_name + r"\s*,\s*wxDialog\s*\)", text
        ) is not None
        expect(class_name + " extends wxDialog in the header", declared)
        missing = [name for name in methods if not re.search(r"\b" + name + r"\s*\(", text)]
        expect(
            "every " + class_name + " accessor is declared",
            not missing,
            "missing: " + ", ".join(missing) if missing else "all present",
        )


def check_definitions(root):
    sources = "\n".join(
        path.read_text(encoding="utf-8", errors="replace")
        for path in sorted((root / "src").glob("*.cpp"))
    )
    for class_name, methods in CLASSES.items():
        missing = [
            name
            for name in methods
            if not re.search(r"\b" + name + r"\s*\(", sources)
        ]
        expect(
            "every " + class_name + " symbol has an EXPORT definition",
            not missing,
            "missing: " + ", ".join(missing) if missing else "all present",
        )


def check_cmake(root):
    text = (root / "CMakeLists.txt").read_text(encoding="utf-8")
    expect("CMakeLists.txt adds sources to the wxcore target",
           re.search(r"target_sources\(\s*wxcore\b", text) is not None)
    missing = [name for name in GENERIC_SOURCES if name not in text]
    expect(
        "the four generic dialog sources are compiled into wxcore",
        not missing,
        "missing: " + ", ".join(missing) if missing else "all present",
    )


def generate(root, kwxgen, language, profile, out_dir):
    command = [
        str(kwxgen), "generate",
        "--headers", str(root / "include"),
        "--defs", str(root / "src" / "kwx_defs.cpp"),
        "--lang", language,
        "--profile", profile,
        "--out", str(out_dir),
    ]
    return subprocess.run(command, cwd=str(root), capture_output=True, text=True, timeout=900)


def tree_text(out_dir):
    chunks = []
    for path in sorted(out_dir.rglob("*")):
        if path.is_file():
            chunks.append(path.read_text(encoding="utf-8", errors="replace"))
    return "\n".join(chunks)


def check_generated(root, kwxgen, work_dir):
    for language in LANGUAGES:
        out_dir = work_dir / ("full_" + language)
        completed = generate(root, kwxgen, language, "full", out_dir)
        if completed.returncode != 0:
            expect(language + ": kwxgen generate exits 0", False,
                   (completed.stderr or completed.stdout)[-1500:])
            continue
        text = tree_text(out_dir)
        missing = [name for name in CLASSES if name not in text]
        expect(
            language + " emits the four wxGeneric*Dialog classes",
            not missing,
            "missing: " + ", ".join(missing) if missing else "all present",
        )

    gui_dir = work_dir / "gui_go"
    completed = generate(root, kwxgen, "go", "gui", gui_dir)
    if completed.returncode != 0:
        expect("go (gui profile): kwxgen generate exits 0", False,
               (completed.stderr or completed.stdout)[-1500:])
    else:
        text = tree_text(gui_dir)
        missing = [name for name in CLASSES if name not in text]
        expect(
            "the gui profile keeps the four wxGeneric*Dialog classes",
            not missing,
            "missing: " + ", ".join(missing) if missing else "all present",
        )

    first = work_dir / "full_typescript"
    second = work_dir / "full_typescript_repeat"
    generate(root, kwxgen, "typescript", "full", second)
    mismatched = []
    for path in sorted(first.rglob("*.ts")):
        mirror = second / path.relative_to(first)
        if not mirror.is_file() or mirror.read_bytes() != path.read_bytes():
            mismatched.append(path.name)
    expect("a second generation is byte-identical", not mismatched,
           "identical" if not mismatched else str(mismatched[:5]))


def check_library(root):
    library = find_first(root, LIBRARY_GLOBS)
    if library is None:
        print("SKIP: no built kwxFFI shared library found")
        return
    newest_source = max(
        (root / "include" / "kwx_dialogs_extra.h").stat().st_mtime,
        (root / "src" / "wx_genericdialogs.cpp").stat().st_mtime
        if (root / "src" / "wx_genericdialogs.cpp").is_file() else 0,
    )
    if library.stat().st_mtime + 1 < newest_source:
        print("SKIP: " + str(library) + " predates the fix sources")
        return
    loader = ctypes.WinDLL if os.name == "nt" else ctypes.CDLL
    try:
        handle = loader(str(library))
    except OSError as error:
        expect("load " + library.name, False, str(error))
        return
    missing = []
    for methods in CLASSES.values():
        for name in methods:
            try:
                getattr(handle, name)
            except AttributeError:
                missing.append(name)
    expect("every new symbol resolves from " + library.name, not missing,
           "missing: " + ", ".join(missing[:10]) if missing else "all present")


def main():
    parser = argparse.ArgumentParser(description="Issue 94 reproducer")
    parser.add_argument("--root", type=Path,
                        default=Path(__file__).resolve().parents[3])
    parser.add_argument("--kwxgen", type=Path, default=None)
    args = parser.parse_args()
    root = args.root.resolve()

    check_declarations(root)
    check_definitions(root)
    check_cmake(root)

    kwxgen = args.kwxgen or find_first(root, KWXGEN_GLOBS)
    if kwxgen is None:
        print("SKIP: no kwxgen executable found; skipping the generated surface")
    else:
        with tempfile.TemporaryDirectory(prefix="issue94-") as temp:
            check_generated(root, kwxgen, Path(temp))

    check_library(root)

    print()
    if failures:
        print("RESULT: %d check(s) failed -- issue 94 is not fixed" % failures)
        return 1
    print("RESULT: all checks passed -- issue 94 is fixed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
