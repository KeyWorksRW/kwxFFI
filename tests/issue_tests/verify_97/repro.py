#!/usr/bin/env python3
"""Reproducer for kwxFFI issue #97.

Issue #97 — "dialogs sample port: 14 gaps - return-valued wrapper callbacks,
broken wxFindDialogEvent getters, missing overloads and constants".

Items 11-14 of the report were withdrawn by the reporter, so only items 1-10
are asserted here:

  1. kwxAddRemoveAdaptor gains data-driven SetItemsCtrl/SetCanAdd/SetCanRemove.
  2. wxModalDialogHook gains CaptureEnterDialog so a void callback can show the
     dialog instead of returning garbage.
  3. wxFileDialog_SetExtraControlCreator's return-value constraint is documented
     at the declaration and at the definition.
  4. kwxAppTraits gains SetLogTarget (returns the previous target).
  5. wxFindDialogEvent_GetFindString/GetReplaceString cast to
     wxFindDialogEvent, return the right string, and agree with the header.
  6. wxWindow::FindWindow(long id) has a member-form wrapper
     (wxWindow_FindWindowByIdSelf, because the static form already owns
     wxWindow_FindWindowById).
  7. wxGenericProgressDialog_Update takes the message argument.
  8. wxGenericFileDialog has its own GetPaths/GetFilenames/GetDirectory.
  9. wxFrame_MSWGetSystemMenu is exported (declaration unguarded, body guarded).
 10. wxMINOR_VERSION, wxALPHA_OPAQUE, wxVERSION_NUM_DOT_STRING and
     wxFileSelectorDefaultWildcardStr are exported constants.

Checks:
  A. Header declarations.
  B. Source definitions (including that the old type-confused cast and the
     wrong GetReplaceString body are gone).
  C. The generated export manifest contains every new symbol, and all five
     language backends emit the new surface.
  D. The generated TypeScript binding has the corrected shapes and the four
     constants; the generated integer table matches the committed one.
  E. When a built kwxFFI shared library is present, every new symbol resolves
     from it (skipped when the library is missing).

Usage:
    python tests/issue_tests/verify_97/repro.py [--root <repo>] [--kwxgen <exe>]

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
    "kwxModalDialogHook_CaptureEnterDialog",
    "wxModalDialogHook_CaptureEnterDialog",
    "kwxAddRemoveAdaptor_SetItemsCtrl",
    "kwxAddRemoveAdaptor_SetCanAdd",
    "kwxAddRemoveAdaptor_SetCanRemove",
    "kwxAppTraits_SetLogTarget",
    "wxAppTraits_SetLogTarget",
    "wxWindow_FindWindowByIdSelf",
    "wxFrame_MSWGetSystemMenu",
    "wxGenericFileDialog_GetPaths",
    "wxGenericFileDialog_GetFilenames",
    "wxGenericFileDialog_GetDirectory",
    "expwxMINOR_VERSION",
    "expwxALPHA_OPAQUE",
    "expwxVERSION_NUM_DOT_STRING",
    "expwxFileSelectorDefaultWildcardStr",
)

LANGUAGES = ("fortran", "go", "julia", "lua", "typescript")

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
        root / "build" / "tests" / "bin" / "Release" / "kwxgen.exe",
        root / "bin" / "kwxgen",
    )
    for candidate in candidates:
        if candidate.is_file():
            return candidate
    return None


def generate(kwxgen: Path, root: Path, language: str, profile: str, out_dir: Path):
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
        profile,
        "--out",
        str(out_dir),
    ]
    return subprocess.run(command, cwd=str(root), check=False, capture_output=True, text=True)


def check_headers(root: Path) -> None:
    print("\n== A. header declarations ==")
    classes = read(root / "include" / "kwx_classes.h")
    sync = read(root / "include" / "kwx_classes_sync.h")
    dialogs = read(root / "include" / "kwx_dialogs_extra.h")
    hooks = read(root / "include" / "kwx_hook_exports.h")

    expect(
        "wxFindDialogEvent_GetFindString returns TClass(wxString) with only pObject",
        re.search(
            r"TClass\(wxString\)\s+wxFindDialogEvent_GetFindString"
            r"\(\s*TSelf\(wxFindDialogEvent\)\s+pObject\s*\)",
            classes,
        )
        is not None,
    )
    expect(
        "wxFindDialogEvent_GetReplaceString returns TClass(wxString) with only pObject",
        re.search(
            r"TClass\(wxString\)\s+wxFindDialogEvent_GetReplaceString"
            r"\(\s*TSelf\(wxFindDialogEvent\)\s+pObject\s*\)",
            classes,
        )
        is not None,
    )
    expect(
        "the find-dialog getters no longer take a void* ref out-parameter",
        re.search(
            r"wxFindDialogEvent_Get(?:Find|Replace)String\s*\([^;]*void\s*\*\s*ref",
            classes,
        )
        is None,
    )
    expect(
        "wxWindow_FindWindowByIdSelf is declared as the TSelf form",
        re.search(
            r"TClass\(wxWindow\)\s+wxWindow_FindWindowByIdSelf"
            r"\(\s*TSelf\(wxWindow\)\s+pObject\s*,\s*int\s+id\s*\)",
            classes,
        )
        is not None,
    )
    expect(
        "wxFrame_MSWGetSystemMenu is declared unguarded",
        re.search(
            r"TClass\(wxMenu\)\s+wxFrame_MSWGetSystemMenu"
            r"\(\s*TSelf\(wxFrame\)\s+pObject\s*\)",
            classes,
        )
        is not None,
    )
    expect(
        "wxGenericProgressDialog_Update declares the message parameter",
        re.search(
            r"wxGenericProgressDialog_Update\(\s*TSelf\(wxGenericProgressDialog\)\s+pObject"
            r"\s*,\s*int\s+value\s*,\s*TClass\(wxString\)\s+message\s*,\s*int\s*\*\s*skip\s*\)",
            sync,
            re.S,
        )
        is not None,
    )
    for getter in (
        "wxGenericFileDialog_GetPaths",
        "wxGenericFileDialog_GetFilenames",
        "wxGenericFileDialog_GetDirectory",
    ):
        expect(f"include/kwx_dialogs_extra.h declares {getter}", getter in dialogs)
    expect(
        "SetExtraControlCreator constraint mentions the returning creator callback",
        re.search(
            r"wxWindow\*[^\n]*\n(?:[^\n]*\n){0,3}?[^\n]*"
            r"wxFileDialog_SetExtraControlCreator",
            dialogs,
        )
        is not None,
    )
    for symbol in NEW_SYMBOLS:
        if symbol.startswith("expwx"):
            continue
        expect(f"include/ declares {symbol}", symbol in hooks or symbol in classes or symbol in dialogs or symbol in sync)


def check_sources(root: Path) -> None:
    print("\n== B. source definitions ==")
    find_repl = read(root / "src" / "wx_findrepldlg.cpp")
    find_block = re.search(
        r"wxFindDialogEvent_GetFindString.*?wxFindDialogEvent_GetReplaceString.*?\n\s*\}",
        find_repl,
        re.S,
    )
    segment = find_block.group(0) if find_block else ""
    expect(
        "GetFindString casts the event to wxFindDialogEvent",
        "((wxFindDialogEvent*) pObject)->GetFindString()" in segment,
    )
    expect(
        "GetReplaceString casts the event to wxFindDialogEvent and calls GetReplaceString",
        "((wxFindDialogEvent*) pObject)->GetReplaceString()" in segment,
    )
    expect(
        "no find-dialog getter casts to wxFindReplaceData any more",
        "wxFindReplaceData*) pObject" not in segment,
    )

    window = read(root / "src" / "wx_window.cpp")
    expect(
        "wxWindow_FindWindowByIdSelf calls self->FindWindow((long) id)",
        "wxWindow_FindWindowByIdSelf" in window
        and "self->FindWindow((long) id)" in window,
    )

    frame = read(root / "src" / "wx_frame.cpp")
    expect(
        "wxFrame_MSWGetSystemMenu is defined with a __WXMSW__-guarded body",
        re.search(
            r"EXPORT\s+void\*\s+wxFrame_MSWGetSystemMenu\(wxFrame\* self\)\s*\{"
            r"\s*#ifdef __WXMSW__\s*return \(void\*\) self->MSWGetSystemMenu\(\);",
            frame,
            re.S,
        )
        is not None,
    )

    extra = read(root / "src" / "kwx_extra.cpp")
    expect(
        "wxGenericProgressDialog_Update passes *message",
        re.search(
            r"wxGenericProgressDialog_Update\(wxGenericProgressDialog\* self,\s*int value,"
            r"\s*wxString\* message,\s*int\* skip\)",
            extra,
            re.S,
        )
        is not None
        and "self->Update(value, *message, &skip_value)" in extra,
    )

    generic = read(root / "src" / "wx_genericdialogs.cpp")
    for getter in (
        "wxGenericFileDialog_GetPaths",
        "wxGenericFileDialog_GetFilenames",
        "wxGenericFileDialog_GetDirectory",
    ):
        expect(
            f"{getter} is defined on wxGenericFileDialog",
            re.search(
                r"EXPORT[^\n]*" + getter + r"\(wxGenericFileDialog\* self",
                generic,
            )
            is not None,
        )
    expect(
        "the generic getters do not cast to wxFileDialog",
        re.search(r"wxGenericFileDialog\*\)[^\n]*wxFileDialog", generic) is None,
    )

    hooks = read(root / "src" / "kwx_hooks.cpp")
    for symbol in (
        "kwxModalDialogHook_CaptureEnterDialog",
        "wxModalDialogHook_CaptureEnterDialog",
        "kwxAddRemoveAdaptor_SetItemsCtrl",
        "kwxAddRemoveAdaptor_SetCanAdd",
        "kwxAddRemoveAdaptor_SetCanRemove",
        "kwxAppTraits_SetLogTarget",
        "wxAppTraits_SetLogTarget",
    ):
        expect(f"src/kwx_hooks.cpp defines {symbol}", symbol in hooks)

    defs = read(root / "src" / "kwx_defs.cpp")
    for symbol in (
        "expwxMINOR_VERSION",
        "expwxALPHA_OPAQUE",
        "expwxVERSION_NUM_DOT_STRING",
        "expwxFileSelectorDefaultWildcardStr",
    ):
        expect(f"src/kwx_defs.cpp defines {symbol}", re.search(r"EXPORT[^\n]*" + symbol + r"\s*\(", defs) is not None)

    table = read(root / "src" / "kwx_constants_table_gen.cpp")
    expect(
        "the integer table calls expwxMINOR_VERSION and expwxALPHA_OPAQUE",
        "expwxMINOR_VERSION()" in table and "expwxALPHA_OPAQUE()" in table,
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
    if not expect("kwxgen exports exits 0", completed.returncode == 0, (completed.stderr or "")[-1000:]):
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
        completed = generate(kwxgen, root, language, "full", out_dir)
        if not expect(
            f"{language}: kwxgen generate exits 0",
            completed.returncode == 0,
            (completed.stderr or completed.stdout)[-1000:],
        ):
            continue
        text = "\n".join(
            read(path) for path in sorted(out_dir.rglob("*")) if path.is_file()
        ).lower()
        missing = [
            symbol
            for symbol in NEW_SYMBOLS
            if symbol.lower() not in text
            and symbol.removeprefix("expwx").lower() not in text
        ]
        expect(
            f"{language} emits every new symbol",
            not missing,
            "missing: " + ", ".join(missing) if missing else "all present",
        )


def check_typescript_shapes(kwxgen: Path, root: Path, work: Path) -> None:
    print("\n== D. generated TypeScript shapes ==")
    out_dir = work / "ts_full"
    completed = generate(kwxgen, root, "typescript", "full", out_dir)
    if not expect(
        "typescript: kwxgen generate exits 0",
        completed.returncode == 0,
        (completed.stderr or completed.stdout)[-1000:],
    ):
        return

    find_event = read(out_dir / "wxFindDialogEvent_gen.ts")
    expect(
        "wxFindDialogEvent.getFindString returns wxString",
        re.search(r"GetFindString\(\):\s*wxString", find_event) is not None,
    )
    expect(
        "wxFindDialogEvent.getReplaceString returns wxString",
        re.search(r"GetReplaceString\(\):\s*wxString", find_event) is not None,
    )

    progress = read(out_dir / "wxGenericProgressDialog_gen.ts")
    expect(
        "wxGenericProgressDialog.update passes the message",
        re.search(
            r"Update\([^)]*message[^)]*\)[^{]*\{[^}]*wxGenericProgressDialog_Update"
            r"\([^)]*message",
            progress,
            re.S,
        )
        is not None,
    )

    generic = read(out_dir / "wxGenericFileDialog_gen.ts")
    for getter in ("GetPaths", "GetFilenames", "GetDirectory"):
        expect(f"wxGenericFileDialog emits {getter}", re.search(r"\b" + getter + r"\(", generic) is not None)

    window = read(out_dir / "wxWindow_gen.ts")
    expect(
        "wxWindow emits FindWindowByIdSelf",
        re.search(r"FindWindowByIdSelf\(", window) is not None,
    )

    frame = read(out_dir / "wxFrame_gen.ts")
    expect(
        "wxFrame emits MSWGetSystemMenu",
        re.search(r"MSWGetSystemMenu\(", frame) is not None,
    )

    constants = read(out_dir / "kwx_constants_gen.ts")
    expect("constants: ALPHA_OPAQUE is a number", re.search(r"ALPHA_OPAQUE:\s*number", constants) is not None)
    expect("constants: MINOR_VERSION is a number", re.search(r"MINOR_VERSION:\s*number", constants) is not None)
    expect(
        "constants: VERSION_NUM_DOT_STRING is exported",
        "VERSION_NUM_DOT_STRING" in constants,
    )
    expect(
        "constants: FileSelectorDefaultWildcardStr is exported",
        "FileSelectorDefaultWildcardStr" in constants,
    )

    generated_table = out_dir / "kwx_constants_table_gen.cpp"
    committed_table = root / "src" / "kwx_constants_table_gen.cpp"
    if generated_table.is_file() and committed_table.is_file():
        expect(
            "the committed integer table equals the generated one",
            generated_table.read_bytes() == committed_table.read_bytes(),
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
    try:
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

    with tempfile.TemporaryDirectory(prefix="kwxffi_97_") as temp_name:
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
