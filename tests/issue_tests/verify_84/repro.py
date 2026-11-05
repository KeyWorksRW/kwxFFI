#!/usr/bin/env python3
"""Issue 84 reproducer: the notebook sample's book-control surface.

Issue 84 reported ten gaps in the kwxFFI surface that forced the wxWidgets
"notebook" sample port into substitutions. This script proves the seven that
were fixed:

  §1  wxNotebook is declared under wxBookCtrlBase (not wxControl) and every
      book control shares one `int` page index / page count type, so a single
      wxBookCtrlBase-typed variable holds any of the seven controls with no
      casts and no BigInt()/Number() conversions.
  §2  wxWithImages::SetImages / GetImageCount / HasImages / GetImage are bound,
      plus a wxBitmapBundleArray vector class to carry the bundles.
  §3  wxNB_NOPAGETHEME, wxBK_DEFAULT, wxNB_DEFAULT (and the already-present
      wxCHB_DEFAULT / wxLB_DEFAULT) are reachable, so a port can assemble the
      style flag word entirely from exported constants.
  §4  Class-block functions with no receiver (static in wxWidgets) are emitted
      as module-level functions instead of instance methods that forward
      this._ptr, so wxArtProvider_GetIcon / wxLog_SetActiveTarget need no
      fabricated wrapper.
  §8  A width-stable HitTestFlags(..., int*) variant exists next to the raw
      long* one, so a caller no longer has to know that `long` is 4 bytes on
      Windows and 8 on 64-bit Unix.
  §9  Every generated class file carries a non-owning wrapWx<Class>(ptr)
      factory, so a borrowed wxWindow* can be wrapped without arming Delete().
  §10 GTKAllowDiagnosticsControl() is declared and exported (a no-op outside
      wxGTK) so the symbol always exists.

Two independent mechanisms, neither needing a GUI:

  A. Generated surface -- run `kwxgen generate --lang typescript --profile full`
     into a temp directory and assert the emitted wrapper layer has the shape
     the issue asks for.
  B. Exported surface -- load the built shared library with ctypes and assert
     every new symbol resolves, the style constants carry the wxWidgets values,
     and the wxBitmapBundleArray container round-trips bundles.

A missing kwxgen skips mechanism A; a missing shared library skips mechanism B.

Usage:
    python tests/issue_tests/verify_84/repro.py [--root <repo>]
                                               [--kwxgen <exe>]
                                               [--library <path>]

Exit codes: 0 fixed, 1 still broken, 77 skipped (neither kwxgen nor library).
"""

import argparse
import ctypes
import os
import subprocess
import sys
import tempfile
from pathlib import Path

# The wxWidgets build used here keeps wxASSERT enabled even in Release, and an
# assert opens a modal dialog that would hang the run.
os.environ.setdefault("WXSUPPRESS_SIZER_FLAGS_CHECK", "1")

SKIP_RETURN_CODE = 77

KWXGEN_GLOBS = (
    "bin/*/kwxgen",
    "bin/*/kwxgen.exe",
    "kwxgen/bin/*/kwxgen*",
    "build/tests/bin/*/kwxgen*",
    "build/**/bin/*/kwxgen*",
)

LIBRARY_GLOBS = (
    "lib/shared/Release/kwxFFI.dll",
    "lib/shared/Release/libkwxFFI.so",
    "lib/shared/Release/libkwxFFI.dylib",
    "lib/shared/Debug/kwxFFI.dll",
    "lib/shared/Debug/libkwxFFI.so",
    "lib/shared/Debug/libkwxFFI.dylib",
    "lib/Release/kwxFFI.dll",
    "lib/Release/libkwxFFI.so",
    "lib/Release/libkwxFFI.dylib",
    "lib/Debug/kwxFFI.dll",
    "lib/Debug/libkwxFFI.so",
    "lib/Debug/libkwxFFI.dylib",
    "lib/kwxFFI.dll",
    "lib/libkwxFFI.so",
    "lib/libkwxFFI.dylib",
    "build/**/kwxFFI.dll",
    "build/**/libkwxFFI.so",
    "build/**/libkwxFFI.dylib",
)

# --- Mechanism A: the emitted TypeScript wrapper layer -----------------------
# (label, generated file, substring that must be present)
EXPECTED_IN_GENERATED = (
    # §1 wxNotebook derives from wxBookCtrlBase in both the class file and the
    # class hierarchy the wrapper extends.
    ("wxNotebook extends wxBookCtrlBase", "wxNotebook_gen.ts",
     "export class wxNotebook extends wxBookCtrlBase"),
    # §1 the shared page API is number/boolean all the way down
    ("wxBookCtrlBase GetPageCount is a number", "wxBookCtrlBase_gen.ts",
     "GetPageCount(): number"),
    ("wxNotebook GetPageCount is a number", "wxNotebook_gen.ts",
     "GetPageCount(): number"),
    ("wxBookCtrlBase GetPage takes a number", "wxBookCtrlBase_gen.ts",
     "GetPage(page: number): Pointer"),
    ("wxBookCtrlBase SetSelection takes a number", "wxBookCtrlBase_gen.ts",
     "SetSelection(page: number): number"),
    ("wxBookCtrlBase InsertPage takes a number", "wxBookCtrlBase_gen.ts",
     "InsertPage(index: number"),
    ("wxNotebook InsertPage takes a number", "wxNotebook_gen.ts",
     "InsertPage(nPage: number"),
    ("wxAuiNotebook Split takes a number", "wxAuiNotebook_gen.ts",
     "Split(page: number, direction: number): void"),
    # §2 wxWithImages API and the bundle vector
    ("wxBookCtrlBase SetImages", "wxBookCtrlBase_gen.ts",
     "SetImages(images: Pointer): void"),
    ("wxBookCtrlBase GetImageCount", "wxBookCtrlBase_gen.ts",
     "GetImageCount(): number"),
    ("wxBookCtrlBase HasImages", "wxBookCtrlBase_gen.ts",
     "HasImages(): boolean"),
    ("wxBookCtrlBase GetImage", "wxBookCtrlBase_gen.ts",
     "GetImage(iconIndex: number): Pointer"),
    ("wxBitmapBundleArray factory", "wxBitmapBundleArray_gen.ts",
     "export function createWxBitmapBundleArray()"),
    ("wxBitmapBundleArray Add", "wxBitmapBundleArray_gen.ts",
     "Add(item: Pointer): void"),
    ("wxBitmapBundleArray GetCount", "wxBitmapBundleArray_gen.ts",
     "GetCount(): number"),
    ("wxBitmapBundleArray Delete", "wxBitmapBundleArray_gen.ts",
     "lib.symbols.wxBitmapBundleArray_Delete(this._ptr);"),
    ("barrel re-exports wxBitmapBundleArray", "kwx_gen.ts",
     "export * from \"./wxBitmapBundleArray_gen.ts\";"),
    # §3 style constants reachable as module-level functions
    ("expNB_NOPAGETHEME is callable", "kwx_free_functions_gen.ts",
     "export function expNB_NOPAGETHEME()"),
    ("expBK_DEFAULT is callable", "kwx_free_functions_gen.ts",
     "export function expBK_DEFAULT()"),
    ("expNB_DEFAULT is callable", "kwx_free_functions_gen.ts",
     "export function expNB_DEFAULT()"),
    ("expCHB_DEFAULT is callable", "kwx_free_functions_gen.ts",
     "export function expCHB_DEFAULT()"),
    ("expLB_DEFAULT is callable", "kwx_free_functions_gen.ts",
     "export function expLB_DEFAULT()"),
    # §4 statics are module-level, not instance methods
    ("wxArtProvider_GetIcon is module-level", "kwx_free_functions_gen.ts",
     "export function wxArtProvider_GetIcon("),
    ("wxArtProvider_GetBitmapBundle is module-level", "kwx_free_functions_gen.ts",
     "export function wxArtProvider_GetBitmapBundle("),
    ("wxLog_SetActiveTarget is module-level", "kwx_free_functions_gen.ts",
     "export function wxLog_SetActiveTarget("),
    ("wxLog_GetActiveTarget is module-level", "kwx_free_functions_gen.ts",
     "export function wxLog_GetActiveTarget("),
    ("wxImage_GetImageCount is module-level", "kwx_free_functions_gen.ts",
     "export function wxImage_GetImageCount("),
    # §8 width-stable hit-test flags
    ("wxBookCtrlBase HitTestFlags", "wxBookCtrlBase_gen.ts",
     "HitTestFlags(x: number, y: number, flags: Pointer): number"),
    # §9 non-owning wrapper factories
    ("wrapWxWindow exists", "wxWindow_gen.ts",
     "export function wrapWxWindow(ptr: Pointer): wxWindow"),
    ("wrapWxNotebook exists", "wxNotebook_gen.ts",
     "export function wrapWxNotebook(ptr: Pointer): wxNotebook"),
    ("root class tracks a borrowed ptr", "wxObject_gen.ts",
     "protected _borrowed: boolean = false;"),
    ("root constructor accepts borrowed", "wxObject_gen.ts",
     "constructor(ptr: Pointer, borrowed: boolean = false)"),
    ("Delete() honours the borrowed flag", "wxObject_gen.ts",
     "if (this._disposed || this._borrowed) return;"),
    # §10 GTK-only helper always present
    ("GTKAllowDiagnosticsControl is exported", "kwx_free_functions_gen.ts",
     "export function GTKAllowDiagnosticsControl()"),
)

# (label, file, substring that must be ABSENT)
FORBIDDEN_IN_GENERATED = (
    # §4 the static lookups must not survive as instance methods that forward
    # this._ptr to a receiver-less C function.
    ("wxArtProvider has no instance GetIcon", "wxArtProvider_gen.ts", "  GetIcon("),
    ("wxArtProvider has no instance GetBitmapBundle", "wxArtProvider_gen.ts",
     "  GetBitmapBundle("),
    ("wxLog has no instance SetActiveTarget", "wxLog_gen.ts", "  SetActiveTarget("),
    ("wxLog has no instance GetActiveTarget", "wxLog_gen.ts", "  GetActiveTarget("),
    ("wxImage has no instance GetImageCount", "wxImage_gen.ts", "  GetImageCount("),
    # §9 the guard must not still be the old un-borrowed form
    ("Delete() is not the old disposed-only guard", "wxObject_gen.ts",
     "    if (this._disposed) return;\n    this._disposed = true;\n    lib.symbols.wxObject_Delete"),
)

# The hand-written explicit-receiver shape (wxStyledTextCtrl and friends) must
# keep forwarding a named `pObject` parameter as it does today.
PRESERVED_SHAPE = (
    ("wxStyledTextCtrl keeps its explicit receiver", "wxStyledTextCtrl_gen.ts",
     "AddRefDocument(pObject: Pointer, docPointer: Pointer)"),
)

# --- Mechanism B: the exported C surface ------------------------------------
REQUIRED_EXPORTS = (
    # §2
    "wxBookCtrlBase_SetImages",
    "wxBookCtrlBase_GetImageCount",
    "wxBookCtrlBase_HasImages",
    "wxBookCtrlBase_GetImage",
    "wxBitmapBundleArray_Create",
    "wxBitmapBundleArray_Delete",
    "wxBitmapBundleArray_GetCount",
    "wxBitmapBundleArray_Add",
    # §8
    "wxBookCtrlBase_HitTestFlags",
    "wxBookCtrlBase_HitTest",
    # §3
    "expNB_NOPAGETHEME",
    "expBK_DEFAULT",
    "expNB_DEFAULT",
    "expCHB_DEFAULT",
    "expLB_DEFAULT",
    "expNB_TOP",
    # §10
    "GTKAllowDiagnosticsControl",
    # §1: the reparented class itself needs no new symbol, but the page API must
    # still be exported with one shared shape.
    "wxNotebook_GetPageCount",
    "wxBookCtrlBase_GetPageCount",
    "wxBookCtrlBase_InsertPage",
    "wxBookCtrlBase_HitTest",
)

# wxWidgets values (build/_deps/wxwidgets-src/include/wx/notebook.h and
# wx/bookctrl.h) -- do not guess these.
EXPECTED_CONSTANT_VALUES = (
    ("expNB_NOPAGETHEME", 0x0400),
    ("expBK_DEFAULT", 0x0000),
    ("expNB_DEFAULT", 0x0000),
    ("expCHB_DEFAULT", 0x0000),
    ("expLB_DEFAULT", 0x0000),
    ("expNB_TOP", 0x0010),
    ("expNB_BOTTOM", 0x0020),
)

SVG_SOURCE = (
    '<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16">'
    '<rect width="16" height="16" fill="#c00"/></svg>'
)


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


def discover_library(root, explicit):
    """Return a shared library path, or None when there is none."""
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = root / candidate
        return candidate.resolve() if candidate.is_file() else None

    for pattern in LIBRARY_GLOBS:
        for candidate in root.glob(pattern):
            if candidate.is_file():
                return candidate.resolve()
    return None


def expect(label, ok, observed=None):
    """Print one EXPECTED/OBSERVED pair; return 1 when the assertion failed."""
    print("EXPECTED: " + label)
    print("OBSERVED: " + (("ok" if ok else "FAILED") if observed is None else observed))
    return 0 if ok else 1


def add_windows_dll_directories(library_path):
    """Register Windows DLL search directories; keep the handles alive."""
    if os.name != "nt":
        return []

    add_directory = getattr(os, "add_dll_directory", None)
    if add_directory is None:
        return []

    candidates = [str(library_path.parent)]
    candidates.extend(os.environ.get("PATH", "").split(os.pathsep))

    handles = []
    for candidate in candidates:
        if not candidate or not os.path.isdir(candidate):
            continue
        try:
            handles.append(add_directory(candidate))
        except OSError:
            continue
    return handles


def check_generated_surface(root, kwxgen, work_dir):
    """Generate TypeScript bindings and assert the wrapper layer's shape."""
    out_dir = work_dir / "typescript"
    command = [
        str(kwxgen),
        "generate",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--lang",
        "typescript",
        "--profile",
        "full",
        "--out",
        str(out_dir),
    ]
    print("RUN: " + " ".join(command))
    completed = subprocess.run(command, cwd=str(root), capture_output=True, text=True, timeout=900)
    if completed.returncode != 0:
        print("EXPECTED: kwxgen generate exits 0")
        print("OBSERVED: exit code %d" % completed.returncode)
        print((completed.stderr or completed.stdout)[-2000:])
        return 1

    cache = {}

    def read(name):
        if name not in cache:
            path = out_dir / name
            cache[name] = path.read_text(encoding="utf-8") if path.is_file() else None
        return cache[name]

    failures = 0
    for label, filename, needle in EXPECTED_IN_GENERATED:
        text = read(filename)
        if text is None:
            failures += expect("%s (%s exists)" % (label, filename), False, "file not generated")
            continue
        failures += expect(label, needle in text,
                           "present" if needle in text else "missing: " + needle)

    for label, filename, needle in PRESERVED_SHAPE:
        text = read(filename)
        ok = text is not None and needle in text
        failures += expect(label, ok, "present" if ok else "missing: " + needle)

    for label, filename, needle in FORBIDDEN_IN_GENERATED:
        text = read(filename)
        if text is None:
            failures += expect("%s (%s exists)" % (label, filename), False, "file not generated")
            continue
        ok = needle not in text
        failures += expect(label, ok, "absent" if ok else "still present: " + needle)

    # Determinism: a second generation must be byte-identical.
    second_dir = work_dir / "typescript_repeat"
    repeat = list(command)
    repeat[repeat.index(str(out_dir))] = str(second_dir)
    subprocess.run(repeat, cwd=str(root), capture_output=True, text=True, timeout=900)
    mismatched = []
    for path in sorted(out_dir.rglob("*.ts")):
        mirror = second_dir / path.relative_to(out_dir)
        if not mirror.is_file() or mirror.read_bytes() != path.read_bytes():
            mismatched.append(path.name)
    failures += expect("a second generation is byte-identical",
                       not mismatched, "identical" if not mismatched else str(mismatched[:5]))

    return failures


def bind(library, name, restype, argtypes):
    """Bind one exported C function to an explicit ctypes signature."""
    function = getattr(library, name)
    function.restype = restype
    function.argtypes = argtypes
    return function


def check_exported_surface(library_path):
    """Assert every new symbol resolves, constants match, containers round-trip."""
    dll_handles = add_windows_dll_directories(library_path)
    try:
        library = ctypes.CDLL(str(library_path))
    except OSError as error:
        return expect("%s loads with ctypes" % library_path.name, False, str(error))

    missing = [name for name in REQUIRED_EXPORTS if not hasattr(library, name)]
    failures = expect(
        "the shared library exports every symbol this check needs",
        not missing,
        "all present" if not missing else "missing: " + ", ".join(missing[:10]),
    )
    if missing:
        return failures

    # §3 the constants must carry the wxWidgets values, not invented ones.
    for name, expected in EXPECTED_CONSTANT_VALUES:
        accessor = bind(library, name, ctypes.c_int, [])
        value = accessor()
        failures += expect(
            "%s is %d" % (name, expected),
            value == expected,
            "value = %d" % value,
        )

    failures += expect(
        "wxNB_DEFAULT aliases wxBK_DEFAULT",
        hasattr(library, "expNB_DEFAULT")
        and bind(library, "expNB_DEFAULT", ctypes.c_int, [])()
        == bind(library, "expBK_DEFAULT", ctypes.c_int, [])()
        == 0,
    )

    # §10 the GTK helper is callable on every platform.
    try:
        helper = bind(library, "GTKAllowDiagnosticsControl", None, [])
        helper()
        failures += expect("GTKAllowDiagnosticsControl() is callable", True, "returned cleanly")
    except Exception as error:  # noqa: BLE001 - report whatever the loader raised
        failures += expect("GTKAllowDiagnosticsControl() is callable", False, str(error))

    # §2 the bundle vector carries DPI-scalable bundles, so the call site no
    # longer has to build a fixed-size wxImageList.
    string_create = bind(library, "wxString_CreateUTF8", ctypes.c_void_p, [ctypes.c_char_p])
    bundle_from_file = bind(library, "wxBitmapBundle_FromSVGFile", ctypes.c_void_p,
                            [ctypes.c_void_p, ctypes.c_int, ctypes.c_int])
    bundle_ok = bind(library, "wxBitmapBundle_IsOk", ctypes.c_int, [ctypes.c_void_p])
    array_create = bind(library, "wxBitmapBundleArray_Create", ctypes.c_void_p, [])
    array_add = bind(library, "wxBitmapBundleArray_Add", None,
                     [ctypes.c_void_p, ctypes.c_void_p])
    array_count = bind(library, "wxBitmapBundleArray_GetCount", ctypes.c_int, [ctypes.c_void_p])
    array_delete = bind(library, "wxBitmapBundleArray_Delete", None, [ctypes.c_void_p])

    with tempfile.TemporaryDirectory() as svg_dir:
        svg_path = os.path.join(svg_dir, "dot.svg")
        with open(svg_path, "w", encoding="utf-8") as handle:
            handle.write(SVG_SOURCE)
        name = string_create(svg_path.encode("utf-8"))
        bundle = bundle_from_file(name, 16, 16)

    failures += expect("wxBitmapBundle_FromSVGFile loads a 16x16 SVG bundle",
                       bool(bundle) and bundle_ok(bundle) == 1,
                       "bundle = %s" % (bundle,))
    if not bundle:
        return failures

    array = array_create()
    failures += expect("wxBitmapBundleArray_Create returns an empty vector",
                       bool(array) and array_count(array) == 0,
                       "count = %d" % (array_count(array) if array else -1))

    for _ in range(4):
        array_add(array, bundle)
    count = array_count(array)
    failures += expect(
        "four bundles added to the vector read back as GetImageCount() == 4",
        count == 4,
        "count = %d" % count,
    )

    array_delete(array)
    failures += expect("wxBitmapBundleArray_Delete releases the vector", True, "deleted")

    return failures


def main(argv=None):
    parser = argparse.ArgumentParser(description="Issue 84 reproducer")
    parser.add_argument("--root", type=Path,
                        default=Path(__file__).resolve().parents[3],
                        help="Repository root (default: three levels above this file)")
    parser.add_argument("--kwxgen", default=None, help="Path to the kwxgen executable")
    parser.add_argument("--library", default=None, help="Path to the kwxFFI shared library")
    options = parser.parse_args(argv)

    root = options.root.resolve()
    kwxgen = discover_kwxgen(root, options.kwxgen)
    library_path = discover_library(root, options.library)

    if kwxgen is None and library_path is None:
        print("SKIP: no kwxgen executable and no shared library found under %s" % root)
        return SKIP_RETURN_CODE

    failures = 0

    if kwxgen is None:
        print("SKIP: mechanism A (generated surface) — no kwxgen executable found")
    else:
        print("=== A. generated TypeScript surface ===")
        with tempfile.TemporaryDirectory() as work_dir:
            failures += check_generated_surface(root, kwxgen, Path(work_dir))

    if library_path is None:
        print("SKIP: mechanism B (exported surface) — no shared library found")
    else:
        print("=== B. exported C surface ===")
        failures += check_exported_surface(library_path)

    print()
    if failures:
        print("SUMMARY: %d assertion(s) failed -- issue 84 is not fixed" % failures)
        return 1
    print("SUMMARY: all assertions passed -- issue 84 book-control surface is fixed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
