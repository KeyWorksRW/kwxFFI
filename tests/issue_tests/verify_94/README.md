# Issue 94 — wrap the four `wxGeneric*Dialog` classes

Issue: [KeyWorksRW/kwxFFI#94 "Wrap the four wxGeneric\*Dialog classes (follow-up to #89 sections 1.11–1.14)"](https://github.com/KeyWorksRW/kwxFFI/issues/94)

## What was wrong

`wxGenericColourDialog`, `wxGenericFontDialog`, `wxGenericFileDialog` and
`wxGenericDirDialog` were missing from the FFI surface: no declaration in
`include/`, no `EXPORT` definition in `src/`, and therefore no class in any
kwxgen-generated binding.

The classes could not simply be declared. Their implementations are not part of
the wxWidgets `wxcore` target on Windows or GTK: `build/cmake/files.cmake` in
the wxWidgets snapshot lists `src/generic/{colrdlgg,fontdlgg,filedlgg,dirdlgg}.cpp`
only in `OSX_COMMON_SRC` and `UNIV_SRC`. The MSW and GTK ports compile
`src/msw/*dlg.cpp` and `src/gtk/*dlg.cpp` instead, so `wxGeneric*Dialog` is not
even compiled there — a wrapper symbol would fail to link.

## The fix

1. `CMakeLists.txt` adds the four portable sources to the `wxcore` target for
   every non-Apple platform (`macOS` already builds them through
   `OSX_COMMON_SRC`, so they must not be added twice).
2. `include/kwx_dialogs_extra.h` declares the four classes with
   `TClassDefExtend(..., wxDialog)`. The real C++ bases (`wxFontDialogBase`,
   `wxFileDialogBase`, `wxDirDialogBase`) are not wrapped, so `wxDialog` is the
   nearest real wrapped ancestor; declaring `extends wxFileDialog` would let a
   generated binding pass a `wxGenericFileDialog*` where a native
   `wxFileDialog*` is expected.
3. `src/wx_genericdialogs.cpp` defines 24 `EXPORT` functions, registered in
   `files_list.cmake`.
4. `tests/expected/symbols.sha256` is refreshed: `count 11598`,
   `sha256 18af4fb8e90f73a9f834ef89ed4d1514f281712f50afb36178ae455ea2daa63a`
   (previously `count 11574`, `sha256 35ab152d…`). The delta is exactly the 24
   new symbols, with nothing removed.

No `kwxgen` source change was needed: `profile.cpp` is an exclusion list, so the
four GUI classes are emitted by the `gui` profile by default.

## Running the reproducer

```
python tests/issue_tests/verify_94/repro.py
```

Optional arguments: `--root <repo>`, `--kwxgen <exe>`.

Exit code `0` means the issue is fixed, `1` means it is not.

## What the script checks

| Group | Proof |
|---|---|
| A. Header contract | `include/kwx_dialogs_extra.h` declares each class as `TClassDefExtend(<class>, wxDialog)` and declares every required accessor. |
| B. Definitions | every declared symbol has an `EXPORT` definition in `src/` (the `guard_parity` contract). |
| C. Build wiring | `CMakeLists.txt` adds the four `src/generic/*dlg.cpp` sources to `wxcore`. |
| D. Generated surface | `kwxgen generate` emits all four class names for `fortran`, `go`, `julia`, `lua` and `typescript`, keeps them in the `gui` profile, and a second generation is byte-identical. |
| E. Exported surface | when a `kwxFFI` shared library newer than the fix sources is present, all 24 new symbols resolve through `ctypes`. Skipped (not failed) on a source-only checkout. |

## Observed results

- Before the fix: `RESULT: 20 check(s) failed -- issue 94 is not fixed`.
- After the fix: every check passes, including the 24 symbols resolving from both
  `lib/shared/Debug/kwxFFI.dll` and `lib/shared/Release/kwxFFI.dll`.

## Verification performed on this tree

- `cmake --build build --config Debug --target kwxFFI kwxFFI_shared` — clean.
- `cmake --build build --config Release --target kwxFFI kwxFFI_shared` — clean.
- `ctest --test-dir build/tests -C Release -L cheap --output-on-failure` — 7/7 pass.
- `python tests/checks/export_snapshot.py --root . --kwxgen bin/Release/kwxgen.exe` — digest matches the refreshed baseline.
- `python tests/checks/symbol_resolve.py --root . --library lib/shared/Debug/kwxFFI.dll --kwxgen bin/Release/kwxgen.exe` — all 11598 symbols resolve (same for the Release DLL).

## Not verifiable here

Linux (GTK) and macOS builds. The declarations are platform-independent and the
CMake block is guarded `if(NOT APPLE)`, so GTK compiles the same four sources and
macOS keeps its existing `OSX_COMMON_SRC` copies. CI must confirm both.
