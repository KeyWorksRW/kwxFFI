# Issue 80: kwxgen: 8 remaining overload renames trace to kwxFFI return-type mismatches

[Issue 80](https://github.com/KeyWorksRW/kwxFFI/issues/80)

## Problem

Generating the TypeScript bindings reported eight members that the emitter had to rename to
`<Member>__<Class>` because the same method reached a class through two FFI wrappers whose return
types disagreed. Each trace led back to a kwxFFI declaration whose return type did not match the
wrapped C++ method (`wxAuiToolBar.GetWindowStyleFlag`, `wxBoxSizer.AddSpacer`, `wxFTP.Close`,
`wxWebViewEvent.GetInt`, `wxHtmlHelpController.DisplayContents`, and `wxToolBar.AddTool` /
`RemoveTool` / `SetDropdownMenu`). After correcting the return types, the rename report must be empty
so a regeneration produces no `__`-suffixed method names.

## Trigger

`kwxgen generate --lang typescript --profile full --rename-report <file>` over the repository's own
`include/` and `src/kwx_defs.cpp`. Before the fix the run printed `member renames: 8` and wrote
`{"count": 8, ...}` listing exactly the eight members above; the generated files contained names
such as `AddTool__wxToolBar`. The eight corrected declarations are
`wxWindow_GetWindowStyleFlag` (`int`→`long`), `wxSizer_AddSpacer` (`void`→`TClass(wxSizerItem)`),
`wxSocketBase_Close` (`void`→`TBool`), `wxCommandEvent_GetInt` (`long`→`int`),
`wxHtmlHelpController_DisplayContents` (`int`/`void`→`TBool`/`bool`), and
`wxToolBar_AddTool`/`wxToolBar_RemoveTool`/`wxToolBar_SetDropdownMenu`
(`void`→`TClass(wxToolBarToolBase)`/`TClass(wxToolBarToolBase)`/`TBool`).

## How to verify

1. Build the FFI surface (proves the new return types compile against wxWidgets):
   `cmake --build build --config Debug --target kwxFFI kwxFFI_shared`
2. Run the cheap suite: `ctest --test-dir build/tests -C Release -L cheap --output-on-failure`
3. Run the reproducer:
   `python tests/issue_tests/verify_80/repro.py`
4. Expected output (fixed tree):
   `EXPECTED: the rename report count is 0` / `OBSERVED: count = 0`,
   `EXPECTED: no generated member is renamed to <Member>__<Class>` / `OBSERVED: no renamed member`,
   and `SUMMARY: all assertions passed -- no TypeScript member renames` (exit 0).
5. Pre-fix observation, replaced by the above: the same generate command printed
   `member renames:          8` (`wxAuiToolBar.GetWindowStyleFlag`, `wxBoxSizer.AddSpacer`,
   `wxFTP.Close`, `wxHtmlHelpController.DisplayContents`, `wxToolBar.AddTool`,
   `wxToolBar.RemoveTool`, `wxToolBar.SetDropdownMenu`, `wxWebViewEvent.GetInt`), the report held
   `"count": 8`, and the generated `.ts` files contained `GetWindowStyleFlag__wxAuiToolBar`,
   `AddTool__wxToolBar`, and the other six suffixed names.

The reproducer uses `--profile full`, the profile that exhibits all eight renames; it needs only the
repository headers and a built `kwxgen`, and exits 77 when no binary is available.

## Files

- `repro.py` — generates TypeScript bindings into a temp directory and asserts the rename report is
  empty and no `__`-suffixed member is emitted.
- `README.md` — this file.
