# wxPreferencesEditor / wxStockPreferencesPage verification package

Issue: `wxPreferencesEditor` and `wxStockPreferencesPage` had no binding at all,
and `wxPreferencesPage`'s hook setters could not substitute because every
runtime callback has the fixed `void(void*, void*, void*)` thunk signature while
`GetName()`/`CreateWindow()`/`GetIcon()` must return
`char*`/`wxWindow*`/`wxBitmapBundle*`.

Reproducer: `python tests/issue_tests/verify_preferences/repro.py`

Exit codes: `0` fixed, `1` still broken, `77` skipped when no `kwxgen` executable
is found.

## What changed

| Area | Surface | Change |
| --- | --- | --- |
| `wxPreferencesPage` hooks | `kwxPreferencesPage_SetOnGetName`/`SetOnCreateWindow`/`SetOnGetIcon` | The callbacks are now `void`-returning *and* usable: each override clears a scratch result, invokes the callback, and returns whatever the callback published. An unset callback still yields an empty name and a null window. |
| Result publishing | `wxPreferencesPage_SetOnGetNameResult`, `_SetOnCreateWindowResult`, `_SetOnGetIconResult` | New. The callback calls the matching setter before it returns: a UTF-8 `char*` (copied), the `wxWindow*` it created (the page owns it), or a `wxBitmapBundle*` allocated with `new` (copied and deleted). |
| Ownership | `wxPreferencesPage_Delete` | New `<Base>_` spelling so a generated wrapper has a `Delete()`; it deletes the same `kwxPreferencesPage` helper object. |
| `wxStockPreferencesPage` | `wxStockPreferencesPage_Create/Delete/GetKind`, `_SetOnCreateWindow`, `_SetOnCreateWindowResult` | New. `Kind` is `0 = General`, `1 = Advanced`. `CreateWindow()` is still pure on the wxWidgets class, so a `kwxStockPreferencesPage` helper supplies the callback-driven override. The block is declared **parentless** — the C++ helper derives from `wxStockPreferencesPage`, not from `kwxPreferencesPage`, so a binding must not inherit setters that down-cast their receiver. |
| `wxPreferencesEditor` | `wxPreferencesEditor_Create/Delete/AddPage/Show/Dismiss`, `_ShouldApplyChangesImmediately`, `_ShownModally` | New class block. A null title is accepted and means "no title". The editor owns every page added to it. |

## Why the callbacks publish their results

`kwxts` (and the other runtimes) create native callbacks from a fixed
`void (*)(void*, void*, void*)` thunk table, so a callback can never return
`char*`/`wxWindow*`/`wxBitmapBundle*`. Publishing through a setter keeps the one
callback shape every runtime already supports while still letting the override
return the right value.

## Verification performed

Build (owning tree, Debug):

```bat
cmake --build build --config Debug --target kwxFFI kwxFFI_shared
```

Check suite:

```bat
python tests\run_checks.py
```

All 7 checks pass (`parser_tests`-equivalent static checks, `guard_lint`,
`guard_parity`, `checker_self_test`, `c_includability`, `binding_coverage`,
`export_snapshot`, `deno_check`).

Reproducer:

```bat
python tests\issue_tests\verify_preferences\repro.py
```

`symbol_resolve.py` against `lib/shared/Debug/kwxFFI.dll` resolves all **11,962**
exported symbols.

## Export surface

The surface grew by 19 symbols:

- 4 `wxPreferencesPage_*` (`Delete`, `SetOnGetNameResult`,
  `SetOnCreateWindowResult`, `SetOnGetIconResult`),
- 6 `wxStockPreferencesPage_*` (`Create`, `Delete`, `GetKind`,
  `SetOnCreateWindow`, `SetOnCreateWindowResult`, plus the `wxPreferencesPage_Delete`
  alias counted above),
- 7 `wxPreferencesEditor_*` (`Create`, `Delete`, `AddPage`, `Show`, `Dismiss`,
  `ShouldApplyChangesImmediately`, `ShownModally`).

New digest:

- `count 11962`
- `sha256 a366fb856d5764a19fda34170f8abc1315c264b68506e51a52f320c58170c726`

## Pre-fix behaviour

- no `wxPreferencesEditor` class block at all;
- no `wxStockPreferencesPage` class block at all;
- `kwxPreferencesPage::GetName()`/`CreateWindow()`/`GetIcon()` took the callback's
  return value as `void*`, which a `void`-returning thunk never sets, so a bound
  page always reported an empty name and a null window.

## Notes and follow-ups

- `wxPreferencesEditor_ShouldApplyChangesImmediately()` is `false` on MSW and
  `true` on GTK+/OS X; a port must read it rather than assume either.
- `wxPreferencesEditor_ShownModally()` is exposed for the same reason: `Show()`
  blocks on MSW but not on GTK+/OS X.
- The five language ports must regenerate to pick the new surface up.
