#!/usr/bin/env python3
"""Reproducer for the wxPreferencesEditor / wxStockPreferencesPage gap.

The preferences sample could not be ported because

  1. wxPreferencesEditor had no binding at all,
  2. wxStockPreferencesPage had no binding at all, and
  3. the kwxPreferencesPage hooks took the callback's return value as void*,
     which a void-returning FFI thunk never sets, so a bound page always
     reported an empty name and a null window.

Checks:

  A. Header declarations.
  B. Source definitions.
  C. The export manifest contains every new symbol, and every language backend
     emits it.
  D. The generated TypeScript has the expected shapes and the stock-page block
     does not inherit the kwxPreferencesPage setters.
  E. When a built kwxFFI shared library is present, every new symbol resolves.

Usage:
    python tests/issue_tests/verify_preferences/repro.py [--root <repo>] [--kwxgen <exe>]

Exit codes: 0 fixed, 1 still broken, 77 skipped (no kwxgen).
"""

from __future__ import annotations

import argparse
import ctypes
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

NEW_SYMBOLS = (
    "wxPreferencesPage_Delete",
    "wxPreferencesPage_SetOnGetNameResult",
    "wxPreferencesPage_SetOnCreateWindowResult",
    "wxPreferencesPage_SetOnGetIconResult",
    "wxStockPreferencesPage_Create",
    "wxStockPreferencesPage_Delete",
    "wxStockPreferencesPage_GetKind",
    "wxStockPreferencesPage_SetOnCreateWindow",
    "wxStockPreferencesPage_SetOnCreateWindowResult",
    "wxPreferencesEditor_Create",
    "wxPreferencesEditor_Delete",
    "wxPreferencesEditor_AddPage",
    "wxPreferencesEditor_Show",
    "wxPreferencesEditor_Dismiss",
    "wxPreferencesEditor_ShouldApplyChangesImmediately",
    "wxPreferencesEditor_ShownModally",
)

LANGUAGES = ("fortran", "go", "julia", "lua", "rust", "typescript")

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

failures: list[str] = []


def expect(label: str, condition: bool, detail: str = "ok") -> bool:
    if condition:
        print(f"PASS: {label}")
        return True
    print(f"FAIL: {label} ({detail})")
    failures.append(label)
    return False


def read(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")


def find_kwxgen(root: Path, explicit: str | None) -> Path | None:
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = root / candidate
        return candidate if candidate.is_file() else None
    candidates = (
        root / "bin" / "Release" / "kwxgen.exe",
        root / "bin" / "Debug" / "kwxgen.exe",
        root / "kwxgen" / "bin" / "Release" / "kwxgen.exe",
        root / "bin" / "kwxgen",
    )
    for candidate in candidates:
        if candidate.is_file():
            return candidate
    return None


def generate(kwxgen: Path, root: Path, language: str, out_dir: Path):
    command = [
        str(kwxgen),
        "generate",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--lang",
        language,
        "--profile",
        "full",
        "--out",
        str(out_dir),
    ]
    return subprocess.run(command, cwd=str(root), check=False, capture_output=True, text=True)


def check_headers(root: Path) -> None:
    print("\n== A. header declarations ==")
    hooks = read(root / "include" / "kwx_hook_exports.h")
    helper = read(root / "include" / "kwx_helper_hooks.h")

    expect(
        "the wxPreferencesEditor block declares Create/AddPage/Show/Dismiss",
        re.search(
            r"TClassDef\(wxPreferencesEditor\)[\s\S]*?wxPreferencesEditor_Create"
            r"[\s\S]*?wxPreferencesEditor_AddPage[\s\S]*?wxPreferencesEditor_Show"
            r"[\s\S]*?wxPreferencesEditor_Dismiss",
            hooks,
        )
        is not None,
    )
    expect(
        "wxPreferencesEditor_ShouldApplyChangesImmediately is declared",
        "wxPreferencesEditor_ShouldApplyChangesImmediately" in hooks,
    )
    expect(
        "wxPreferencesEditor_ShownModally is declared",
        "wxPreferencesEditor_ShownModally" in hooks,
    )
    expect(
        "the wxStockPreferencesPage block is declared parentless",
        re.search(r"TClassDef\(wxStockPreferencesPage\)", hooks) is not None
        and "TClassDefExtend(wxStockPreferencesPage" not in hooks,
    )
    for symbol in (
        "wxStockPreferencesPage_Create",
        "wxStockPreferencesPage_Delete",
        "wxStockPreferencesPage_GetKind",
        "wxStockPreferencesPage_SetOnCreateWindow",
        "wxStockPreferencesPage_SetOnCreateWindowResult",
    ):
        expect(f"include/ declares {symbol}", symbol in hooks)
    for symbol in (
        "wxPreferencesPage_SetOnGetNameResult",
        "wxPreferencesPage_SetOnCreateWindowResult",
        "wxPreferencesPage_SetOnGetIconResult",
    ):
        expect(f"include/ declares {symbol}", symbol in hooks)
    expect(
        "kwxPreferencesPage keeps a scratch result per override",
        "m_result_name" in helper
        and "m_result_window" in helper
        and "m_result_icon" in helper,
    )
    expect(
        "kwxStockPreferencesPage does not derive from kwxPreferencesPage",
        "class kwxStockPreferencesPage : public wxStockPreferencesPage" in helper,
    )


def check_sources(root: Path) -> None:
    print("\n== B. source definitions ==")
    hooks = read(root / "src" / "kwx_hooks.cpp")

    expect(
        "GetName clears the scratch result before invoking the callback",
        re.search(
            r"wxString kwxPreferencesPage::GetName\(\) const\s*\{[\s\S]*?m_result_name\.clear\(\);"
            r"[\s\S]*?m_get_name_func\(m_object\);[\s\S]*?return m_result_name;",
            hooks,
        )
        is not None,
    )
    expect(
        "CreateWindow clears the scratch result before invoking the callback",
        re.search(
            r"wxWindow\* kwxPreferencesPage::CreateWindow\(wxWindow\* parent\)\s*\{"
            r"[\s\S]*?m_result_window = nullptr;[\s\S]*?m_create_window_func\(m_object, parent\);"
            r"[\s\S]*?return m_result_window;",
            hooks,
        )
        is not None,
    )
    expect(
        "GetIcon consumes and deletes the published bundle",
        "delete m_result_icon;" in hooks,
    )
    expect(
        "no preference override casts the callback's return value any more",
        "static_cast<const char*>(raw_name)" not in hooks
        and "static_cast<wxWindow*>(m_create_window_func" not in hooks,
    )
    expect(
        "kwxStockPreferencesPage::CreateWindow is defined",
        "wxWindow* kwxStockPreferencesPage::CreateWindow(wxWindow* parent)" in hooks,
    )
    for symbol in NEW_SYMBOLS:
        expect(f"src/kwx_hooks.cpp defines {symbol}", symbol in hooks)
    expect(
        "wxStockPreferencesPage_Create maps kind 1 to Kind_Advanced",
        "wxStockPreferencesPage::Kind_Advanced" in hooks,
    )


def check_exports_manifest(kwxgen: Path, root: Path, work: Path) -> None:
    print("\n== C1. export manifest ==")
    out_dir = work / "exports"
    completed = subprocess.run(
        [
            str(kwxgen),
            "exports",
            "--headers",
            str(root / "include"),
            "--defs",
            str(root / "src" / "kwx_defs.cpp"),
            "--out",
            str(out_dir),
        ],
        cwd=str(root),
        check=False,
        capture_output=True,
        text=True,
    )
    if not expect(
        "kwxgen exports exits 0",
        completed.returncode == 0,
        (completed.stderr or "")[-1000:],
    ):
        return
    def_file = out_dir / "kwxFFI.def"
    if not def_file.is_file():
        candidates = sorted(out_dir.glob("*.def"))
        if not candidates:
            expect("kwxFFI.def was generated", False, "no .def file")
            return
        def_file = candidates[0]
    manifest = def_file.read_text(encoding="utf-8", errors="replace")
    for symbol in NEW_SYMBOLS:
        expect(f"export manifest contains {symbol}", symbol in manifest)


def check_generated(kwxgen: Path, root: Path, work: Path) -> None:
    print("\n== C2. all backends emit the new surface ==")
    for language in LANGUAGES:
        out_dir = work / f"gen_{language}"
        completed = generate(kwxgen, root, language, out_dir)
        if not expect(
            f"{language}: kwxgen generate exits 0",
            completed.returncode == 0,
            (completed.stderr or completed.stdout)[-1000:],
        ):
            continue
        text = "\n".join(
            read(path) for path in sorted(out_dir.rglob("*")) if path.is_file()
        ).lower()
        missing = [symbol for symbol in NEW_SYMBOLS if symbol.lower() not in text]
        expect(
            f"{language} emits every new symbol",
            not missing,
            "missing: " + ", ".join(missing) if missing else "all present",
        )


def check_typescript_shapes(kwxgen: Path, root: Path, work: Path) -> None:
    print("\n== D. generated TypeScript shapes ==")
    out_dir = work / "ts_full"
    completed = generate(kwxgen, root, "typescript", out_dir)
    if not expect(
        "typescript: kwxgen generate exits 0",
        completed.returncode == 0,
        (completed.stderr or completed.stdout)[-1000:],
    ):
        return

    editor = read(out_dir / "wxPreferencesEditor_gen.ts")
    expect(
        "wxPreferencesEditor emits createWxPreferencesEditor",
        "export function createWxPreferencesEditor(" in editor,
    )
    for method in ("AddPage", "Show", "Dismiss", "Delete"):
        expect(
            f"wxPreferencesEditor emits {method}",
            re.search(r"\b" + method + r"\(", editor) is not None,
        )

    page = read(out_dir / "wxPreferencesPage_gen.ts")
    for method in ("SetOnGetNameResult", "SetOnCreateWindowResult", "SetOnGetIconResult"):
        expect(
            f"wxPreferencesPage emits {method}",
            re.search(r"\b" + method + r"\(", page) is not None,
        )
    expect(
        "wxPreferencesPage emits a real Delete()",
        "lib.symbols.wxPreferencesPage_Delete(this._ptr)" in page,
    )

    stock = read(out_dir / "wxStockPreferencesPage_gen.ts")
    expect(
        "wxStockPreferencesPage emits createWxStockPreferencesPage",
        "export function createWxStockPreferencesPage(" in stock,
    )
    expect(
        "wxStockPreferencesPage emits GetKind",
        re.search(r"\bGetKind\(", stock) is not None,
    )
    expect(
        "wxStockPreferencesPage emits SetOnCreateWindowResult",
        re.search(r"\bSetOnCreateWindowResult\(", stock) is not None,
    )
    expect(
        "wxStockPreferencesPage does not inherit the kwxPreferencesPage setters",
        "SetOnGetName(" not in stock and "SetOnGetIcon(" not in stock,
    )

    free = read(out_dir / "kwx_free_functions_gen.ts")
    expect(
        "ShouldApplyChangesImmediately is emitted as a boolean helper",
        re.search(
            r"export function wxPreferencesEditor_ShouldApplyChangesImmediately\(\): boolean",
            free,
        )
        is not None,
    )
    expect(
        "ShownModally is emitted as a boolean helper",
        re.search(r"export function wxPreferencesEditor_ShownModally\(\): boolean", free)
        is not None,
    )


def check_library(root: Path) -> None:
    print("\n== E. built shared library ==")
    library_path = None
    for pattern in LIBRARY_GLOBS:
        for candidate in sorted(root.glob(pattern)):
            if candidate.is_file():
                library_path = candidate
                break
        if library_path:
            break
    if library_path is None:
        print("SKIP: no built shared library")
        return

    handles = []
    if hasattr(os, "add_dll_directory"):
        directories = [library_path.parent]
        directories.extend(
            Path(entry) for entry in os.environ.get("PATH", "").split(os.pathsep) if entry
        )
        for directory in directories:
            if directory.is_dir():
                try:
                    handles.append(os.add_dll_directory(str(directory)))
                except OSError:
                    pass
    try:
        library = ctypes.CDLL(str(library_path))
    except OSError as error:  # pragma: no cover - environment dependent
        print(f"SKIP: could not load {library_path}: {error}")
        return

    for symbol in NEW_SYMBOLS:
        try:
            getattr(library, symbol)
            resolved = True
        except AttributeError:
            resolved = False
        expect(f"{symbol} resolves from {library_path.name}", resolved)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[3])
    parser.add_argument("--kwxgen", default=None)
    options = parser.parse_args(argv)

    root = options.root.resolve()
    kwxgen = find_kwxgen(root, options.kwxgen)
    if kwxgen is None:
        print("SKIP: no kwxgen executable found")
        return 77

    print(f"Repository: {root}")
    print(f"kwxgen:     {kwxgen}")

    check_headers(root)
    check_sources(root)

    with tempfile.TemporaryDirectory(prefix="kwxffi_prefs_") as temp_name:
        work = Path(temp_name)
        check_exports_manifest(kwxgen, root, work)
        check_generated(kwxgen, root, work)
        check_typescript_shapes(kwxgen, root, work)

    check_library(root)

    print()
    if failures:
        print(f"BROKEN: {len(failures)} check(s) failed")
        return 1
    print("FIXED: all checks passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
