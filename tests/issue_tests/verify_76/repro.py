#!/usr/bin/env python3
"""Issue 76 reproducer: font surface and the TBool return ABI.

Issue 76 reported that the Python (ctypes) binding for wxFont returned garbage
booleans -- ``wxFont_IsOk`` yielded ``-1386532095`` -- because kwxFFI's ``TBool``
was declared as an 8-byte C++ ``bool`` in an int-sized slot.  The same issue
reported that ``wxFontInfo``, the ``wxFont`` copy/assign helpers, ``wxArrayInt``,
``wxArrayString_Delete``, ``wxSizer_GetDefaultBorder`` and the ``wxTEXT_TYPE_ANY``
/ ``wxSTB_*`` constants were missing from the C surface.

This script proves the fix with two independent mechanisms:

  A. Generated surface -- generate the Fortran bindings with a built ``kwxgen``
     and assert every new symbol reaches a ``bind(C, name='...')`` line.
  B. Return ABI -- load the built shared library with ``ctypes`` and assert that
     every boolean accessor returns exactly 0 or 1, then exercise the new
     surface (wxFontInfo, wxFont copy/assign, wxArrayInt, wxArrayString, font
     enumeration, wxSizer_GetDefaultBorder and the text-control constants).

No GUI, no consumer-language repository and no network access is required.  A
missing ``kwxgen`` skips mechanism A; a missing shared library skips mechanism B.

Usage:
    python tests/issue_tests/verify_76/repro.py [--root <repo>]
                                                [--kwxgen <exe>]
                                                [--library <path>]

Exit codes: 0 fixed, 1 still broken, 77 skipped (neither kwxgen nor library).
"""

import argparse
import ctypes
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

# The wxWidgets build used here keeps wxASSERT enabled even in Release, and an
# assert opens a modal dialog that hangs the process.  Suppress the sizer-flag
# check before anything loads the library.
os.environ.setdefault("WXSUPPRESS_SIZER_FLAGS_CHECK", "1")

SKIP_RETURN_CODE = 77

# Ordered by preference: checked-in release binaries first, then test builds.
KWXGEN_GLOBS = (
    "bin/*/kwxgen",
    "bin/*/kwxgen.exe",
    "kwxgen/bin/*/kwxgen*",
    "build/tests/bin/*/kwxgen*",
    "build/**/bin/*/kwxgen*",
)

# Ordered by preference: release installs first, then debug, then build trees.
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

# Every symbol the fixed tree must place in the Fortran binding surface.
EXPECTED_BINDINGS = (
    # wxFontInfo -- named-parameter font descriptions
    "wxFontInfo_Create",
    "wxFontInfo_CreateDefault",
    "wxFontInfo_Delete",
    "wxFontInfo_SetFamily",
    "wxFontInfo_SetFaceName",
    "wxFontInfo_SetWeight",
    "wxFontInfo_SetStyle",
    "wxFontInfo_SetBold",
    "wxFontInfo_SetLight",
    "wxFontInfo_SetItalic",
    "wxFontInfo_SetSlant",
    "wxFontInfo_SetUnderlined",
    "wxFontInfo_SetStrikethrough",
    "wxFontInfo_SetEncoding",
    "wxFontInfo_GetFractionalPointSize",
    "wxFontInfo_GetFamily",
    "wxFontInfo_GetStyle",
    "wxFontInfo_GetNumericWeight",
    "wxFontInfo_GetEncoding",
    "wxFontInfo_GetFaceName",
    "wxFontInfo_IsUnderlined",
    "wxFontInfo_IsStrikethrough",
    # wxFont copy, assignment and construction from wxFontInfo
    "wxFont_CreateFromInfo",
    "wxFont_CreateFromFont",
    "wxFont_Assign",
    # wxArrayInt and the missing wxArrayString destructor
    "wxArrayString_Delete",
    "wxArrayInt_Create",
    "wxArrayInt_Delete",
    "wxArrayInt_Add",
    "wxArrayInt_GetCount",
    "wxArrayInt_Item",
    "wxArrayInt_Clear",
    "wxArrayInt_IsEmpty",
    # Font enumeration helpers used by the font picker
    "wxFontEnumerator_CreateDefault",
    "wxFontEnumerator_EnumerateFacenamesToArray",
    "wxFontEnumerator_EnumerateEncodingsToArray",
    # Miscellaneous helpers named by the issue
    "wxSizer_GetDefaultBorder",
    "expwxTEXT_TYPE_ANY",
    "expwxSTB_SIZEGRIP",
    "expwxSTB_SHOW_TIPS",
    "expwxSTB_ELLIPSIZE_START",
    "expwxSTB_ELLIPSIZE_MIDDLE",
    "expwxSTB_ELLIPSIZE_END",
)

# The duplicate bare wxTextFile declaration used to hide the whole class; the
# class must still reach the bindings after the duplicate was deleted.
MUST_SURVIVE_BINDINGS = ("wxTextFile_Open",)

# Symbols the fix removed on purpose.
MUST_BE_ABSENT_BINDINGS = ("wxArrayInt_Sort",)

# wxWidgets enum values (wx/defs.h, wx/font.h) -- do not guess these.
FONTFAMILY_SWISS = 74
FONTSTYLE_NORMAL = 90
FONTSTYLE_ITALIC = 93
FONTWEIGHT_NORMAL = 400
FONTWEIGHT_BOLD = 700
FONTENCODING_SYSTEM = 0

BOOL_ACCESSORS = (
    "wxFont_IsOk",
    "wxFont_GetUnderlined",
    "wxFont_GetStrikethrough",
    "wxFont_IsFixedWidth",
    "wxFont_IsUsingSizeInPixels",
)

TEXT_CONSTANTS = (
    "expwxTEXT_TYPE_ANY",
    "expwxSTB_SIZEGRIP",
    "expwxSTB_SHOW_TIPS",
    "expwxSTB_ELLIPSIZE_START",
    "expwxSTB_ELLIPSIZE_MIDDLE",
    "expwxSTB_ELLIPSIZE_END",
)

REQUIRED_EXPORTS = (
    "wxString_CreateUTF8",
    "wxFont_Create",
    "wxFont_CreateFromInfo",
    "wxFont_CreateFromFont",
    "wxFont_Assign",
    "wxFont_GetFractionalPointSize",
    "wxFont_GetUnderlined",
    "wxFontInfo_Create",
    "wxFontInfo_SetBold",
    "wxFontInfo_SetItalic",
    "wxFontInfo_SetUnderlined",
    "wxFontInfo_SetStrikethrough",
    "wxFontInfo_GetFractionalPointSize",
    "wxFontInfo_GetStyle",
    "wxFontInfo_GetNumericWeight",
    "wxFontInfo_IsUnderlined",
    "wxFontInfo_IsStrikethrough",
    "wxArrayString_Create",
    "wxArrayString_Add",
    "wxArrayString_GetCount",
    "wxArrayString_Delete",
    "wxArrayInt_Create",
    "wxArrayInt_Add",
    "wxArrayInt_GetCount",
    "wxArrayInt_Item",
    "wxArrayInt_IsEmpty",
    "wxArrayInt_Delete",
    "wxFontEnumerator_CreateDefault",
    "wxFontEnumerator_EnumerateFacenamesToArray",
    "wxFontEnumerator_EnumerateEncodingsToArray",
    "wxSizer_GetDefaultBorder",
    "expwxBLUE_PEN",
) + TEXT_CONSTANTS + BOOL_ACCESSORS


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

    # Glob order *is* the preference order, so the first hit wins.
    for pattern in LIBRARY_GLOBS:
        for candidate in root.glob(pattern):
            if candidate.is_file():
                return candidate.resolve()
    return None


def expect(label, ok, observed):
    """Print one EXPECTED/OBSERVED pair; return 1 when the assertion failed."""
    print("EXPECTED: " + label)
    print("OBSERVED: " + (("ok" if ok else "FAILED") if observed is None else observed))
    return 0 if ok else 1


def add_windows_dll_directories(library_path):
    """Register Windows DLL search directories for the library's dependencies.

    Returns the handles from os.add_dll_directory; the caller must keep them
    referenced for as long as the library stays loaded.
    """
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
    """Assert every expected symbol reaches a generated bind(C, name=...) line."""
    out_dir = work_dir / "fortran"
    command = [
        str(kwxgen),
        "generate",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--lang",
        "fortran",
        "--out",
        str(out_dir),
    ]
    print("RUN: " + " ".join(command))
    completed = subprocess.run(
        command, cwd=str(root), capture_output=True, text=True, timeout=900
    )
    if completed.returncode != 0:
        print("EXPECTED: kwxgen generate exits 0")
        print("OBSERVED: exit code %d" % completed.returncode)
        print((completed.stderr or completed.stdout)[-2000:])
        return 1

    generated = out_dir / "kwxffi_gen.f90"
    if not generated.is_file():
        return expect("kwxgen generated kwxffi_gen.f90", False, str(generated) + " does not exist")

    text = generated.read_text(encoding="utf-8", errors="replace")
    failures = 0

    for symbol in EXPECTED_BINDINGS:
        needle = "bind(C, name='%s')" % symbol
        failures += expect(
            "kwxffi_gen.f90 binds " + symbol,
            needle in text,
            "present" if needle in text else "no bind(C) line for " + symbol,
        )

    for symbol in MUST_SURVIVE_BINDINGS:
        needle = "bind(C, name='%s')" % symbol
        failures += expect(
            "kwxffi_gen.f90 still binds " + symbol + " (class not hidden by a duplicate)",
            needle in text,
            "present" if needle in text else "no bind(C) line for " + symbol,
        )

    for symbol in MUST_BE_ABSENT_BINDINGS:
        needle = "bind(C, name='%s')" % symbol
        failures += expect(
            "kwxffi_gen.f90 does not bind removed symbol " + symbol,
            needle not in text,
            "absent" if needle not in text else "still declares " + symbol,
        )

    return failures


def bind(library, name, restype, argtypes):
    """Bind one exported C function to an explicit ctypes signature."""
    function = getattr(library, name)
    function.restype = restype
    function.argtypes = argtypes
    return function


def check_return_abi(library_path):
    """Assert TBool accessors return 0/1 and exercise the new surface."""
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

    # ---- TBool return ABI -------------------------------------------------
    string_create = bind(library, "wxString_CreateUTF8", ctypes.c_void_p, [ctypes.c_char_p])
    face = string_create(b"Arial")

    font_create = bind(
        library,
        "wxFont_Create",
        ctypes.c_void_p,
        [
            ctypes.c_int,
            ctypes.c_int,
            ctypes.c_int,
            ctypes.c_int,
            ctypes.c_int,
            ctypes.c_void_p,
            ctypes.c_int,
        ],
    )
    font = font_create(
        10,
        FONTFAMILY_SWISS,
        FONTSTYLE_NORMAL,
        FONTWEIGHT_NORMAL,
        0,
        face,
        FONTENCODING_SYSTEM,
    )
    failures += expect(
        "wxFont_Create(10, SWISS, NORMAL, 400, 0, \"Arial\", SYSTEM) returns a font",
        font is not None,
        "font = %s" % (font,),
    )
    if font is None:
        return failures

    raw_values = {}
    for symbol in BOOL_ACCESSORS:
        accessor = bind(library, symbol, ctypes.c_int32, [ctypes.c_void_p])
        raw = accessor(font)
        raw_values[symbol] = raw
        failures += expect(
            "%s returns a TBool (exactly 0 or 1)" % symbol,
            raw in (0, 1),
            "raw = %d" % raw,
        )

    failures += expect(
        "wxFont_GetStrikethrough returns 0 for a plain Arial font",
        raw_values["wxFont_GetStrikethrough"] == 0,
        "raw = %d" % raw_values["wxFont_GetStrikethrough"],
    )
    failures += expect(
        "wxFont_IsFixedWidth returns 0 for a plain Arial font",
        raw_values["wxFont_IsFixedWidth"] == 0,
        "raw = %d" % raw_values["wxFont_IsFixedWidth"],
    )

    # ---- wxFontInfo -------------------------------------------------------
    info_create = bind(library, "wxFontInfo_Create", ctypes.c_void_p, [ctypes.c_double])
    info = info_create(14.5)
    failures += expect(
        "wxFontInfo_Create(14.5) returns a wxFontInfo handle",
        info is not None,
        "info = %s" % (info,),
    )
    if info is None:
        return failures

    info_set_bool = bind(library, "wxFontInfo_SetBold", None, [ctypes.c_void_p, ctypes.c_int])
    info_set_bool(info, 1)
    info_set_bool = bind(library, "wxFontInfo_SetItalic", None, [ctypes.c_void_p, ctypes.c_int])
    info_set_bool(info, 1)
    info_set_bool = bind(library, "wxFontInfo_SetUnderlined", None, [ctypes.c_void_p, ctypes.c_int])
    info_set_bool(info, 1)
    info_set_bool = bind(
        library, "wxFontInfo_SetStrikethrough", None, [ctypes.c_void_p, ctypes.c_int]
    )
    info_set_bool(info, 0)

    size_getter = bind(
        library, "wxFontInfo_GetFractionalPointSize", ctypes.c_double, [ctypes.c_void_p]
    )
    info_size = size_getter(info)
    failures += expect(
        "wxFontInfo_GetFractionalPointSize is 14.5",
        abs(info_size - 14.5) < 1.0e-9,
        "value = %r" % info_size,
    )

    weight_getter = bind(library, "wxFontInfo_GetNumericWeight", ctypes.c_int, [ctypes.c_void_p])
    info_weight = weight_getter(info)
    failures += expect(
        "wxFontInfo_GetNumericWeight is %d after SetBold(1)" % FONTWEIGHT_BOLD,
        info_weight == FONTWEIGHT_BOLD,
        "value = %d" % info_weight,
    )

    style_getter = bind(library, "wxFontInfo_GetStyle", ctypes.c_int, [ctypes.c_void_p])
    info_style = style_getter(info)
    failures += expect(
        "wxFontInfo_GetStyle is %d after SetItalic(1)" % FONTSTYLE_ITALIC,
        info_style == FONTSTYLE_ITALIC,
        "value = %d" % info_style,
    )

    info_bool_getter = bind(library, "wxFontInfo_IsUnderlined", ctypes.c_int32, [ctypes.c_void_p])
    info_underlined = info_bool_getter(info)
    failures += expect(
        "wxFontInfo_IsUnderlined is 1",
        info_underlined == 1,
        "value = %d" % info_underlined,
    )

    info_bool_getter = bind(
        library, "wxFontInfo_IsStrikethrough", ctypes.c_int32, [ctypes.c_void_p]
    )
    info_strikethrough = info_bool_getter(info)
    failures += expect(
        "wxFontInfo_IsStrikethrough is 0",
        info_strikethrough == 0,
        "value = %d" % info_strikethrough,
    )

    # ---- wxFont copy, assignment and construction from wxFontInfo ---------
    create_from_info = bind(library, "wxFont_CreateFromInfo", ctypes.c_void_p, [ctypes.c_void_p])
    font_from_info = create_from_info(info)
    failures += expect(
        "wxFont_CreateFromInfo returns a font",
        font_from_info is not None,
        "font = %s" % (font_from_info,),
    )
    if font_from_info is None:
        return failures

    create_from_font = bind(library, "wxFont_CreateFromFont", ctypes.c_void_p, [ctypes.c_void_p])
    font_copy = create_from_font(font_from_info)
    failures += expect(
        "wxFont_CreateFromFont returns a font",
        font_copy is not None,
        "font = %s" % (font_copy,),
    )
    if font_copy is None:
        return failures

    font_size_getter = bind(
        library, "wxFont_GetFractionalPointSize", ctypes.c_double, [ctypes.c_void_p]
    )
    copy_size = font_size_getter(font_copy)
    failures += expect(
        "the copied font keeps the 14.5 point size",
        abs(copy_size - 14.5) < 1.0e-9,
        "value = %r" % copy_size,
    )

    font_bool_getter = bind(library, "wxFont_GetUnderlined", ctypes.c_int32, [ctypes.c_void_p])
    copy_underlined = font_bool_getter(font_copy)
    failures += expect(
        "the copied font keeps the underline flag",
        copy_underlined == 1,
        "value = %d" % copy_underlined,
    )

    font_assign = bind(library, "wxFont_Assign", None, [ctypes.c_void_p, ctypes.c_void_p])
    font_assign(font, font_copy)
    assigned_size = font_size_getter(font)
    failures += expect(
        "wxFont_Assign copies the point size onto the target font",
        abs(assigned_size - 14.5) < 1.0e-9,
        "value = %r" % assigned_size,
    )

    # ---- wxArrayString / wxArrayInt ---------------------------------------
    array_string_create = bind(library, "wxArrayString_Create", ctypes.c_void_p, [])
    array_string_count = bind(
        library, "wxArrayString_GetCount", ctypes.c_size_t, [ctypes.c_void_p]
    )
    array_string_add = bind(
        library, "wxArrayString_Add", None, [ctypes.c_void_p, ctypes.c_void_p]
    )
    array_string_delete = bind(library, "wxArrayString_Delete", None, [ctypes.c_void_p])

    strings = array_string_create()
    failures += expect(
        "wxArrayString_Create returns an array", strings is not None, "array = %s" % (strings,)
    )
    if strings is not None:
        array_string_add(strings, face)
        string_total = array_string_count(strings)
        failures += expect(
            "wxArrayString_GetCount is 1 after one Add",
            string_total == 1,
            "count = %d" % string_total,
        )

    array_int_create = bind(library, "wxArrayInt_Create", ctypes.c_void_p, [])
    array_int_add = bind(library, "wxArrayInt_Add", None, [ctypes.c_void_p, ctypes.c_int])
    array_int_count = bind(library, "wxArrayInt_GetCount", ctypes.c_size_t, [ctypes.c_void_p])
    array_int_item = bind(library, "wxArrayInt_Item", ctypes.c_int, [ctypes.c_void_p, ctypes.c_size_t])
    array_int_is_empty = bind(library, "wxArrayInt_IsEmpty", ctypes.c_int32, [ctypes.c_void_p])
    array_int_delete = bind(library, "wxArrayInt_Delete", None, [ctypes.c_void_p])

    ints = array_int_create()
    failures += expect(
        "wxArrayInt_Create returns an array", ints is not None, "array = %s" % (ints,)
    )
    if ints is not None:
        for value in (7, 3, 9):
            array_int_add(ints, value)
        int_total = array_int_count(ints)
        failures += expect(
            "wxArrayInt_GetCount is 3 after three Add calls",
            int_total == 3,
            "count = %d" % int_total,
        )
        int_item = array_int_item(ints, 1)
        failures += expect(
            "wxArrayInt_Item(1) is 3", int_item == 3, "value = %d" % int_item
        )
        int_empty = array_int_is_empty(ints)
        failures += expect(
            "wxArrayInt_IsEmpty is 0 for a populated array",
            int_empty == 0,
            "value = %d" % int_empty,
        )

    # ---- Font enumeration -------------------------------------------------
    enumerator_create = bind(
        library, "wxFontEnumerator_CreateDefault", ctypes.c_void_p, []
    )
    enumerator = enumerator_create()
    failures += expect(
        "wxFontEnumerator_CreateDefault returns an enumerator",
        enumerator is not None,
        "enumerator = %s" % (enumerator,),
    )

    if enumerator is not None:
        encodings = array_string_create()
        enumerate_encodings = bind(
            library,
            "wxFontEnumerator_EnumerateEncodingsToArray",
            ctypes.c_int,
            [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p],
        )
        returned_encodings = enumerate_encodings(enumerator, None, encodings)
        stored_encodings = array_string_count(encodings)
        failures += expect(
            "EnumerateEncodingsToArray with a NULL facename does not crash and "
            "returns the array size",
            returned_encodings == stored_encodings,
            "returned = %d, count = %d" % (returned_encodings, stored_encodings),
        )

        facenames = array_string_create()
        enumerate_facenames = bind(
            library,
            "wxFontEnumerator_EnumerateFacenamesToArray",
            ctypes.c_int,
            [ctypes.c_void_p, ctypes.c_int, ctypes.c_int, ctypes.c_void_p],
        )
        returned_faces = enumerate_facenames(
            enumerator, FONTENCODING_SYSTEM, 0, facenames
        )
        stored_faces = array_string_count(facenames)
        failures += expect(
            "EnumerateFacenamesToArray(FONTENCODING_SYSTEM, 0) returns the array size",
            returned_faces == stored_faces,
            "returned = %d, count = %d" % (returned_faces, stored_faces),
        )

        array_string_delete(facenames)
        array_string_delete(encodings)

    if strings is not None:
        array_string_delete(strings)
    if ints is not None:
        array_int_delete(ints)

    # ---- Miscellaneous helpers named by the issue -------------------------
    default_border = bind(library, "wxSizer_GetDefaultBorder", ctypes.c_int, [])
    border = default_border()
    failures += expect(
        "wxSizer_GetDefaultBorder returns a positive border",
        border > 0,
        "value = %d" % border,
    )

    for symbol in TEXT_CONSTANTS:
        constant = bind(library, symbol, ctypes.c_int, [])
        value = constant()
        failures += expect(
            symbol + " returns an int",
            isinstance(value, int),
            "value = %d" % value,
        )

    blue_pen = bind(library, "expwxBLUE_PEN", ctypes.c_void_p, [])
    pen = blue_pen()
    failures += expect(
        "expwxBLUE_PEN returns a non-null pen pointer",
        pen is not None,
        "pen = %s" % (pen,),
    )

    # dll_handles must outlive the loaded library; the local keeps it referenced.
    del dll_handles
    return failures


def main(argv=None):
    parser = argparse.ArgumentParser(
        description="Reproduce issue 76 (font surface and the TBool return ABI)."
    )
    parser.add_argument("--root", default=None, help="Repository root")
    parser.add_argument("--kwxgen", default=None, help="Path to the kwxgen executable")
    parser.add_argument(
        "--library", default=None, help="Path to the built shared library"
    )
    options = parser.parse_args(argv)

    root = Path(options.root).resolve() if options.root else Path(__file__).resolve().parents[3]
    headers = root / "include"
    defs = root / "src" / "kwx_defs.cpp"
    if not headers.is_dir() or not defs.is_file():
        print("FAIL: %s or %s is missing; is --root the kwxFFI repository?" % (headers, defs))
        return 1

    kwxgen = discover_kwxgen(root, options.kwxgen)
    library = discover_library(root, options.library)

    failures = 0
    mechanisms = 0

    if kwxgen is None:
        print("SKIP: mechanism A (generated surface) -- no kwxgen binary under bin/, kwxgen/bin/, or build/")
    else:
        mechanisms += 1
        work_dir = Path(tempfile.mkdtemp(prefix="kwx_issue76_"))
        try:
            failures += check_generated_surface(root, kwxgen, work_dir)
        finally:
            shutil.rmtree(work_dir, ignore_errors=True)

    if library is None:
        print("SKIP: mechanism B (TBool return ABI) -- no shared library found")
    else:
        mechanisms += 1
        print("LIBRARY: %s" % library)
        failures += check_return_abi(library)

    if mechanisms == 0:
        print("SKIP: no kwxgen binary and no shared library found; build one to run this check")
        return SKIP_RETURN_CODE

    if failures:
        print("SUMMARY: %d assertion(s) failed -- issue 76 is still present" % failures)
        return 1
    print("SUMMARY: all assertions passed -- issue 76 surface and TBool ABI are fixed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
