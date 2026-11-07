# Issue #97 verification package

Issue: **#97 — dialogs sample port: 14 gaps - return-valued wrapper callbacks, broken wxFindDialogEvent getters, missing overloads and constants**

Reproducer: `python tests/issue_tests/verify_97/repro.py`

Exit codes: `0` fixed, `1` still broken, `77` skipped when no `kwxgen` executable is found.

The reporter withdrew items 11-14, so only items 1-10 are covered here.

## What changed

| Item | Surface | Change |
| --- | --- | --- |
| 1 | `kwxAddRemoveAdaptor` | Added `SetItemsCtrl(wxWindow*)`, `SetCanAdd(bool)`, `SetCanRemove(bool)` plus the matching C exports (`kwxAddRemoveAdaptor_SetItemsCtrl/SetCanAdd/SetCanRemove`). `GetItemsCtrl()`/`CanAdd()`/`CanRemove()` fall back to the stored values when no callback is installed, so a void-only binding can drive `wxAddRemoveCtrl`. |
| 2 | `wxModalDialogHook` | Added `CaptureEnterDialog(bool)` (`kwxModalDialogHook_CaptureEnterDialog` and the `wxModalDialogHook_` alias). In capture mode `Enter()` invokes the installed callback for its side effects and returns `wxID_NONE`, so the dialog is shown instead of being skipped by a garbage return value. |
| 3 | `wxFileDialog::SetExtraControlCreator` | Constraint documented at the declaration (`include/kwx_dialogs_extra.h`) and at the definition (`src/wx_filedialog.cpp`): the creator must return the created `wxWindow*`, the FFI callback ABI is void-only, and `SetCustomizeHook` is the supported route. No behaviour change — a void callback cannot supply the return value. |
| 4 | `kwxAppTraits` | Added `SetLogTarget(wxLog*)` returning the previous target (`kwxAppTraits_SetLogTarget` and `wxAppTraits_SetLogTarget`). `CreateLogTarget()` returns the explicitly installed target first. |
| 5 | `wxFindDialogEvent` | `GetFindString()`/`GetReplaceString()` now cast to `wxFindDialogEvent*` and `GetReplaceString()` returns the replace text. The header declaration changed from `int (pObject, void* ref)` to `TClass(wxString) (pObject)`, matching the definition. |
| 6 | `wxWindow` | Added the member-form id lookup. The C symbol is **`wxWindow_FindWindowByIdSelf`**, not `wxWindow_FindWindowById`, because the static form (`wxWindow::FindWindowById(long, wxWindow*)`) already owns that C name and the C ABI has no overloading. The generated method is `wxWindow.FindWindowByIdSelf(id)`. |
| 7 | `wxGenericProgressDialog` | `Update()` now takes the message: `wxGenericProgressDialog_Update(self, value, wxString* message, int* skip)` and passes `*message` to `wxGenericProgressDialog::Update`. This is an intentional exported-surface change. |
| 8 | `wxGenericFileDialog` | Added its own `GetPaths`, `GetFilenames` and `GetDirectory` wrappers, using `wxGenericFileDialog*` (the `wxFileDialog*` cast is invalid because the two classes are siblings on MSW). |
| 9 | `wxFrame` | Added `wxFrame_MSWGetSystemMenu(TSelf(wxFrame)) -> TClass(wxMenu)`. The declaration is platform-independent; only the body is guarded by `#ifdef __WXMSW__` (returns `nullptr` elsewhere), matching `wxFrame_MSWGetTaskBarButton`. |
| 10 | Constants | Added `expwxMINOR_VERSION`, `expwxALPHA_OPAQUE` (integer table) and `expwxVERSION_NUM_DOT_STRING`, `expwxFileSelectorDefaultWildcardStr` (`wxString*`, same pattern as the existing `expwxART_*` constants). `src/kwx_constants_table_gen.cpp` was regenerated with kwxgen. |

Generated TypeScript names follow the existing convention: the `wx` prefix is stripped, so the constants are `MINOR_VERSION`, `ALPHA_OPAQUE`, `VERSION_NUM_DOT_STRING` and `FileSelectorDefaultWildcardStr`.

## Verification performed

Build (owning tree, Debug):

```bat
cmake --build build --config Debug --target kwxFFI kwxFFI_shared
cmake --build build/tests --config Release
```

Cheap suite:

```bat
ctest --test-dir build/tests -C Release -L cheap --output-on-failure
```

All 7 tests pass (`parser_tests`, `guard_lint`, `guard_parity`, `checker_self_test`, `c_includability`, `export_snapshot`, `deno_check`).

Reproducer:

```bat
python tests\issue_tests\verify_97\repro.py
```

All checks pass; it also resolves all 16 new symbols from `lib/shared/Debug/kwxFFI.dll`.

`symbol_resolve.py` against the built DLL resolves all **11,614** exported symbols.

## Export surface

The exported surface changed on purpose (16 new symbols; two existing signatures corrected: `wxFindDialogEvent_GetFindString`, `wxFindDialogEvent_GetReplaceString` and `wxGenericProgressDialog_Update`). The baseline was refreshed with:

```bat
python tests\checks\export_snapshot.py --root . --kwxgen bin\Release\kwxgen.exe --update
```

New digest:

- `count 11614`
- `sha256 7e1624e27e68b40c1fec0cf27967aca3dbe7aa0d8117b140a717e28be1f7cdc8`

The +16 count is exactly the seven hook symbols, `wxWindow_FindWindowByIdSelf`, `wxFrame_MSWGetSystemMenu`, the three generic-file-dialog getters and the four constant accessors. The two return-type corrections and the `Update` parameter change do not add symbols.

## Pre-fix behaviour

The assertions target surface that does not exist in `HEAD`, so they fail before the fix:

- no `wxGenericFileDialog_GetPaths/GetFilenames/GetDirectory`, no `wxFrame_MSWGetSystemMenu`, no hook setters, no new constants;
- `wxFindDialogEvent_GetFindString` was declared `int (pObject, void* ref)` in the header while the definition returned `wxString*`;
- both find-dialog getters cast to `wxFindReplaceData*`, and `GetReplaceString` returned the find string;
- `wxGenericProgressDialog_Update` passed `wxEmptyString`;
- there was no member-form id lookup.

(This session could not execute a live pre-fix run because shell `git` is blocked in the workspace; the pre-fix state is the `HEAD` side of the recorded diffs, which the assertions above match one-for-one.)

## Notes and follow-ups

- Item 3 is documentation-only by design: the creator callback's return value cannot be produced by a void callback. The usable path is `wxFileDialog_SetCustomizeHook`.
- The `wxGenericProgressDialog_Update` change is an ABI change for the five language ports; they must regenerate from this header.
- Windows is the only platform buildable here. `wxFrame_MSWGetSystemMenu` compiles with a `nullptr` body off MSW; CI on Linux/macOS should confirm that branch links.
- No other backend-specific mapping change was needed: the five backends were generated and checked in the reproducer.
