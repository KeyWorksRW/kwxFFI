# Issue 76: font sample: wxFontInfo/wxFont copy, font enumeration and choice helpers, wxArrayString missing; TBool returns read as int32

[Issue 76](https://github.com/KeyWorksRW/kwxFFI/issues/76)

## Problem

A font-selection sample written against the FFI surface could not be ported, and the parts that did
build returned nonsense. Six defects were fixed:

- **TBool return ABI.** `TBool`-returning accessors were exported as C++ `bool` but consumed as a
  32-bit integer, so a caller read uninitialised upper bits. `wxFont_IsOk` came back as
  `-1386532095`, `wxFont_GetStrikethrough` as `466055680`. Every `TBool` return is now normalised to
  `0`/`1` on the C side.
- **`wxFontDialog_Create` pointer reinterpretation.** `src/wx_fontdlg.cpp` cast the incoming
  `void*` to `wxFontData&` instead of `*(wxFontData*)`, so the dialog was handed a pointer value that
  was really the object, not the object itself.
- **Dropped facename in `OnFontEncoding`.** The encoding callback ignored the `facename` argument it
  was passed.
- **Null dereference in `EnumerateEncodings`.** `wxFontEnumerator_EnumerateEncodings*` dereferenced a
  NULL `facename`; NULL must now be treated as an empty string.
- **Missing surface.** `wxFontInfo` (create, delete, twelve setters, seven getters), `wxFont`
  construction from a `wxFontInfo` / from another `wxFont` plus `wxFont_Assign`, the whole
  `wxArrayInt` class, `wxArrayString_Delete`, `wxFontEnumerator_CreateDefault` and the two
  `*ToArray` enumeration helpers, `wxSizer_GetDefaultBorder`, and the `expwxTEXT_TYPE_ANY` /
  `expwxSTB_*` constants were absent from the headers. A duplicate bare `wxTextFile` declaration also
  hid that entire class from the generator; deleting the duplicate restores it.

## Trigger

Calling any of the symbols above through the C surface. Before the fix:

- the symbols with no declaration — `wxFontInfo_*`, `wxFont_CreateFromInfo`,
  `wxFont_CreateFromFont`, `wxFont_Assign`, `wxArrayInt_*`, `wxArrayString_Delete`,
  `wxFontEnumerator_CreateDefault`, `wxFontEnumerator_Enumerate*ToArray`,
  `wxSizer_GetDefaultBorder`, `expwxTEXT_TYPE_ANY`, `expwxSTB_*` — were unreachable: no header
  declared them, so no binding was generated and `dlsym`/`GetProcAddress` found nothing;
- `wxTextFile_Open` was missing from the generated bindings because the duplicate bare declaration
  replaced the class declaration;
- the `TBool` accessors that did exist returned garbage: a plain Arial font reported
  `wxFont_IsOk = -1386532095` instead of `1`, and `wxFont_GetStrikethrough` returned `466055680`
  instead of `0` — so a caller testing `if (value)` saw a "struck-through, fixed-width" font.

## How to verify

```sh
cmake --build build --config Release --target kwxFFI_shared
cmake --build build/kwxgen
python tests/issue_tests/verify_76/repro.py
```

The reproducer uses two independent mechanisms and needs a GUI for neither:

**A — generated surface** (requires a built `kwxgen`; skipped when absent). It runs
`kwxgen generate --headers include --defs src/kwx_defs.cpp --lang fortran --out <tempdir>` and asserts
`kwxffi_gen.f90` contains a `bind(C, name='<symbol>')` line for each symbol the issue names, that
`wxTextFile_Open` survived the duplicate-declaration cleanup, and that `wxArrayInt_Sort` is gone.

**B — return ABI** (requires the built shared library; skipped when absent). It loads the library with
`ctypes`, builds a 10-point Arial `wxFont` exactly as the reporter did, and asserts every boolean
accessor (`wxFont_IsOk`, `wxFont_GetUnderlined`, `wxFont_GetStrikethrough`, `wxFont_IsFixedWidth`,
`wxFont_IsUsingSizeInPixels`) returns exactly `0` or `1`. It then exercises `wxFontInfo` (14.5 pt,
bold/italic/underlined → size 14.5, weight 700, style 93), `wxFont_CreateFromInfo` /
`wxFont_CreateFromFont` / `wxFont_Assign`, `wxArrayString` and `wxArrayInt`, both font-enumeration
helpers (including a NULL facename), `wxSizer_GetDefaultBorder` and the text-control constants.

Expected output shape (fixed tree):

```
EXPECTED: kwxffi_gen.f90 binds wxFontInfo_Create
OBSERVED: present
...
EXPECTED: wxFont_IsOk returns a TBool (exactly 0 or 1)
OBSERVED: raw = 1
EXPECTED: wxFont_GetStrikethrough returns 0 for a plain Arial font
OBSERVED: raw = 0
...
EXPECTED: EnumerateEncodingsToArray with a NULL facename does not crash and returns the array size
OBSERVED: returned = 18, count = 18
SUMMARY: all assertions passed -- issue 76 surface and TBool ABI are fixed
```

Exit codes: `0` fixed, `1` still broken, `77` skipped (no `kwxgen` **and** no shared library).
`WXSUPPRESS_SIZER_FLAGS_CHECK=1` is set before the library loads because this wxWidgets build keeps
`wxASSERT` enabled in Release and an assert opens a modal dialog that would hang the run.

**Not exercised here:** `wxFontDialog_Create`. The font-dialog defect (`src/wx_fontdlg.cpp` casting
`void*` to `wxFontData&` instead of `*(wxFontData*)`) cannot be exercised headlessly — constructing a
`wxFontDialog` requires a GUI. It must be inspected by reading the fixed cast in
`src/wx_fontdlg.cpp`.

## Files

- `repro.py` — generates Fortran bindings to assert the surface, then drives the shared library
  through `ctypes` to assert the `TBool` ABI and the new font/array/enumeration helpers.
- `README.md` — this file.
