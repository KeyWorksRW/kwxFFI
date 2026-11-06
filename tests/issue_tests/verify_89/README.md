# Issue 89 — dialogs sample surface

Issue #89 asked for the classes, methods, constants and free functions that keep
`wxSamples/src/dialogs` from reaching full parity with the C++ original.

## What the reproducer proves

`repro.py` runs two independent mechanisms.

### A. Generated TypeScript surface

It runs

```
kwxgen generate --headers include --defs src/kwx_defs.cpp \
                --lang typescript --profile full --out <temp>
```

and asserts, in the generated wrapper layer:

- `wxInfoBar extends wxControl`, `wxNotificationMessage extends wxEvtHandler`,
  `wxProgressDialog extends wxDialog`, `wxRichMessageDialog extends wxMessageDialog`,
  `wxGenericProgressDialog extends wxDialog`, `wxGenericNotificationMessage extends
  wxNotificationMessage`, `wxAddRemoveCtrl extends wxPanel`, the two dialog event
  classes extend `wxCommandEvent`, and `wxSystemAppearance`, `wxGenericValidator`,
  `wxRearrangeDialog`, `wxBusyInfoFlags` are generated with the required bases.
- `wxRearrangeCtrl.GetList()`, `wxRearrangeDialog.GetList()` and the
  `wxFileDialogCustomize.Add*` family return their declared wrapped class
  (`wxRearrangeList | null`, `wxFileDialogCustomControl | null`) instead of
  `Pointer`.
- Every requested method exists: rich message dialog, add/remove control,
  generic/app progress, rearrange dialog, busy-info flags, colour/notification
  content, system appearance, generic validator, info bar (style, checkbox,
  timed message, remove-all, close-button), progress dialog pulse/skip/delete,
  modal hook register/unregister/delete, `AddRadioButton`,
  `SetExtraControlCreator`, rich tooltip single-colour/bitmap, generic about
  custom controls, property-sheet default ctor and two-phase `CreateEx`,
  notification bitmap icon.
- The three `*Ex` free functions and all new constants are present.
- `src/kwx_constants_table_gen.cpp` (compiled into the DLL) is clang-formatted
  after generation, so it matches the freshly generated table ignoring
  whitespace: the same entries and values in the same order, formatting
  differences allowed. A second generation is byte-identical.

### B. Exported C surface

It loads the built shared library with `ctypes` and asserts every new symbol
resolves, then checks the new constants against the real wxWidgets 3.3.5 values
(`wxAPPLY = 0x20`, `wxCLOSE = 0x40`, `wxICON_NONE = 0x40000`,
`wxICON_AUTH_NEEDED = 0x80000`, the eight `wxPD_*` flags,
`wxColourData::NUM_CUSTOM = 16`, and the `Timeout_Auto`/`Timeout_Never` values).

A missing `kwxgen` skips mechanism A; a missing shared library skips mechanism B.

## Known limitation (not a regression)

`wxGenericColourDialog`, `wxGenericFontDialog`, `wxGenericFileDialog` and
`wxGenericDirDialog` are **not** compiled into the MSW wxWidgets build:
`src/generic/colrdlgg.cpp`, `fontdlgg.cpp`, `filedlgg.cpp` and `dirdlgg.cpp`
appear only in the OSX and wxUniversal source lists. Exporting them would make
every Windows link fail, so issue #89 sections 1.11–1.14 are intentionally not
implemented. The reproducer asserts that no generated class file appears for
them.

## Environment note

The `wxInfoBar` additions the issue uses (`ShowMessageFor`, `RemoveAllButtons`,
`ShowCloseButton`, `Timeout_Auto`/`Timeout_Never`) were added to the current
wxWidgets 3.3.5 development snapshot; the `build/_deps` checkout originally in
this workspace predated them. The local build tree was refreshed from the newer
`wx-dev-latest` snapshot (the `include/wx/infobar.h`, `include/wx/generic/infobar.h`,
`src/generic/infobar.cpp`, `include/wx/private/bmpbuttn.h` and
`src/common/bmpbtncmn.cpp` files). A clean configure fetches that snapshot from
the URL already used by `CMakeLists.txt`.

## Usage

```
python tests/issue_tests/verify_89/repro.py [--root <repo>] \
                                            [--kwxgen <exe>] \
                                            [--library <dll>]
```

Exit codes: `0` fixed, `1` still broken, `77` skipped (neither kwxgen nor a
shared library was found).
