# Issue 84: notebook sample — `wxNotebook` under `wxControl`, missing `SetImages`/`GetImageCount`, style constants, statics and `long*` outs

[Issue 84](https://github.com/KeyWorksRW/kwxFFI/issues/84)

## Problem

Porting `wxSamples/src/notebook` to `kwxTypeScript` worked, but seven areas of the kwxFFI
surface forced a cast, a raw `lib.symbols.*` call, or a substitution. The acceptance criteria
the reporter set are:

> the port can store the seven book controls in one `wxBookCtrlBase`-typed variable with no casts
> and no `BigInt()`/`Number()` conversions; `SetImages()` receives four DPI-scaled
> `wxBitmapBundle`s and `GetImageCount()` reads back 4; the style flag word is assembled entirely
> from exported constants; the active log target is set and restored through a static call without
> fabricating a wrapper; `wxArrayString` objects are freed; the hit-test flags need no
> `ArrayBuffer`; and `GetPage(0)->GetSize()` is one method call.

What was fixed:

| § | Defect | Fix |
|---|---|---|
| 1 | `wxNotebook` declared `TClassDefExtend(wxNotebook, wxControl)` in **two** blocks (`kwx_classes.h`, `kwx_methods_views.h`); the parser keeps the last block's parent, so both had to change | both reparented to `wxBookCtrlBase` |
| 1 | the same virtuals carried different index types — `int` for `wxNotebook`, `size_t` for `wxBookCtrlBase` — so one wrapper could not override the other (`GetPageCount(): bigint` vs `number`) | every page index and page count of all eight book controls converted to `int` on both the declaration and the definition side |
| 2 | `wxWithImages::SetImages`/`GetImageCount`/`HasImages`/`GetImage` were not bound, so a port had to build a fixed 32×32 `wxImageList` and track `hasImages` itself | bound, plus a `wxBitmapBundleArray` vector class (`Create`/`Delete`/`GetCount`/`Add`) modelled on `wxAuiNotebookPageArray` |
| 3 | `wxNB_NOPAGETHEME` and the `*_DEFAULT` flag words were not exported (`wxCHB_DEFAULT`/`wxLB_DEFAULT` existed; `expNB_*` covered only the four orientations) | `expNB_NOPAGETHEME`, `expBK_DEFAULT`, `expNB_DEFAULT` added (`wxTBK_DEFAULT` does not exist in wxWidgets and was deliberately not invented) |
| 4 | class-block functions with no receiver (static in wxWidgets) were emitted as instance methods forwarding `this._ptr`; a port had to call `lib.symbols.wxArtProvider_GetIcon` directly and fabricate `new wxLog(oldTarget).SetActiveTarget()`, where disposing the wrapper would `delete` a target wxLog still owns | the TypeScript emitter now emits receiver-less class-block functions as module-level `<Class>_<Method>` functions in `kwx_free_functions_gen.ts` |
| 8 | `wxBookCtrlBase_HitTest(..., long* flags)` forced the caller to know that `long` is 4 bytes on Windows and 8 on 64-bit Unix, so the port allocated an 8-byte zero-filled `ArrayBuffer` and read it with `getBigInt64` | added `wxBookCtrlBase_HitTestFlags(..., int* flags)`, which owns the `long` locally and narrows it; the raw `long*` variant is kept |
| 9 | `GetPage()`/`GetEventObject()` return borrowed pointers, but every generated class has an owning `Delete()`, so wrapping one was a double-free trap | every class file now emits `wrapWx<Class>(ptr)`, a non-owning factory; the root class tracks `_borrowed` and `Delete()` is a no-op for it |
| 10 | `GTKAllowDiagnosticsControl()` did not exist anywhere, so a GTK port could not silence the wxNotebook destruction diagnostics | declared unguarded and exported; the `__WXGTK__` guard is inside the body only |

Out of scope, as the issue itself rates it: §5 (`wxString` printf-style formatting — C varargs
cannot cross the FFI), §6 (`wxICON(sample)` — resource loading is a documentation note, not an
FFI gap), and §7 (`wxArrayString_Delete`, already present and tracked in #76 §5).

## Trigger

Before the fix, generating the TypeScript bindings produced:

- `wxNotebook_gen.ts`: `export class wxNotebook extends wxControl`, so a `wxNotebook` could not be
  passed to anything taking `wxBookCtrlBase`, and `GetPageCount(): number` had no counterpart on the
  base, whose wrapper said `GetPageCount(): bigint`. Every call had to branch on the concrete type
  and convert with `BigInt()`/`Number()`.
- `wxBookCtrlBase_gen.ts`: no `SetImages`, `GetImageCount`, `HasImages` or `GetImage`; `HitTestPage`
  took `flags: Pointer`.
- `wxArtProvider_gen.ts`: `GetIcon(id, client, width, height)` **as an instance method**, forwarding
  `this._ptr` to `wxArtProvider_GetIcon`, a static that takes no receiver.
- `wxLog_gen.ts`: `SetActiveTarget()` as an instance method, same problem.
- no `wxBitmapBundleArray`, no `expNB_NOPAGETHEME`, no `expBK_DEFAULT`, no
  `GTKAllowDiagnosticsControl`, no `wrapWx*` factory.

## How to verify

```sh
# generator (kwxgen/src/lang/lang_typescript.cpp changed)
cmake --build build/kwxgen
cmake --build build --config Release --target kwxgen

# C surface (include/** and src/** changed)
cmake --build build --config Debug --target kwxFFI kwxFFI_shared
cmake --build build --config Release --target kwxFFI_shared

python tests/issue_tests/verify_84/repro.py
```

The reproducer uses two independent mechanisms and needs a GUI for neither; a missing `kwxgen`
skips mechanism A, a missing shared library skips B.

**A — generated surface.** Runs
`kwxgen generate --headers include --defs src/kwx_defs.cpp --lang typescript --profile full --out <tmp>`
and asserts the emitted wrapper layer:

- `wxNotebook_gen.ts` says `export class wxNotebook extends wxBookCtrlBase`, and both
  `wxNotebook_gen.ts` and `wxBookCtrlBase_gen.ts` say `GetPageCount(): number`; every page-index
  parameter of all seven book controls is `number`, including `wxAuiNotebook.Split(page: number, …)`;
- `wxBookCtrlBase_gen.ts` has `SetImages`, `GetImageCount`, `HasImages`, `GetImage` and
  `HitTestFlags(x: number, y: number, flags: Pointer)`;
- `wxBitmapBundleArray_gen.ts` exists with a `createWxBitmapBundleArray()` factory, `Add`, `GetCount`
  and the owning `Delete()`, and `kwx_gen.ts` re-exports it;
- `expNB_NOPAGETHEME`, `expBK_DEFAULT`, `expNB_DEFAULT`, `expCHB_DEFAULT`, `expLB_DEFAULT` and
  `GTKAllowDiagnosticsControl` are callable from `kwx_free_functions_gen.ts`;
- `wxArtProvider_GetIcon`, `wxArtProvider_GetBitmapBundle`, `wxLog_SetActiveTarget`,
  `wxLog_GetActiveTarget` and `wxImage_GetImageCount` are **module-level** functions, and the
  same names are **absent** as instance methods on their class files;
- `wrapWxWindow` / `wrapWxNotebook` exist, the root class tracks `_borrowed`, and `Delete()` is the
  borrowed-aware guard;
- the hand-written explicit-receiver shape is preserved
  (`wxStyledTextCtrl_gen.ts` keeps `AddRefDocument(pObject: Pointer, docPointer: Pointer)`);
- a second generation into a second directory is byte-identical.

**B — exported surface.** Loads `lib/shared/Release/kwxFFI.dll` with `ctypes` and asserts every new
symbol resolves, the style constants carry the wxWidgets values
(`wxNB_NOPAGETHEME == 0x0400`, `wxBK_DEFAULT == wxNB_DEFAULT == wxCHB_DEFAULT == wxLB_DEFAULT == 0`),
`GTKAllowDiagnosticsControl()` is callable, and `wxBitmapBundleArray` round-trips four
`wxBitmapBundle_FromSVGFile` bundles back as `GetImageCount() == 4`.

Expected output shape (fixed tree):

```
EXPECTED: wxNotebook extends wxBookCtrlBase
OBSERVED: present
...
EXPECTED: wxArtProvider has no instance GetIcon
OBSERVED: absent
...
EXPECTED: expNB_NOPAGETHEME is 1024
OBSERVED: value = 1024
EXPECTED: four bundles added to the vector read back as GetImageCount() == 4
OBSERVED: count = 4
SUMMARY: all assertions passed -- issue 84 book-control surface is fixed
```

Exit codes: `0` fixed, `1` still broken, `77` skipped (no `kwxgen` **and** no shared library).
`WXSUPPRESS_SIZER_FLAGS_CHECK=1` is set before the library loads because this wxWidgets build keeps
`wxASSERT` enabled in Release and an assert opens a modal dialog that would hang the run.

### Pre-fix proof

Running the same script against the pre-fix tree (a worktree at the merge base, with the current
generator) fails 20 assertions, e.g.:

```
$ python tests/issue_tests/verify_84/repro.py --root <worktree-at-merge-base>
EXPECTED: wxNotebook extends wxBookCtrlBase
OBSERVED: missing: export class wxNotebook extends wxBookCtrlBase
EXPECTED: wxBookCtrlBase SetImages
OBSERVED: missing: SetImages(images: Pointer): void
EXPECTED: expNB_NOPAGETHEME is callable
OBSERVED: missing: export function expNB_NOPAGETHEME()
EXPECTED: wxBookCtrlBase HitTestFlags
OBSERVED: missing: HitTestFlags(x: number, y: number, flags: Pointer): number
...
SUMMARY: 20 assertion(s) failed -- issue 84 is not fixed
```

Mechanism B is skipped there because a worktree has no built library. The §4 and §9 assertions
exercise the emitter, so they pass in that run (the worktree supplies the old *headers*, not the old
emitter). The pre-fix emitter behaviour is recorded, not reconstructed: before the change the
generator emitted `GetIcon(id, client, width, height)` as a `wxArtProvider` instance method
forwarding `this._ptr`, and `wxNotebook extends wxControl` — both caught by the forbidden/expected
list above.

**Not exercised here:** §9's safety property is asserted structurally (the `_borrowed` guard and the
factory exist). Actually disposing a borrowed wrapper and observing that the child window survives
requires a GUI and a live wxWidgets frame, so it must be checked by reading `wxObject_gen.ts` /
`wxBookCtrlBase_gen.ts`.

## Platform note

Everything here builds and is proven on Windows. The behaviour is platform-independent: the
declarations are unguarded, `GTKAllowDiagnosticsControl`'s `__WXGTK__` guard is inside the body
only, and the style constant values come from the wxWidgets headers themselves (all three
`*_DEFAULT` words are `0x0000` on every port). CI on GTK/macOS will confirm that
`GTKAllowDiagnosticsControl` actually reaches `wxApp::GTKAllowDiagnosticsControl()` there; on MSW
it is intentionally a no-op stub so the exported symbol always exists.

## Files

- `repro.py` — generates TypeScript bindings and asserts the wrapper layer, then drives the shared
  library through `ctypes` to assert the exported surface, the constant values and the bundle vector.
- `README.md` — this file.
