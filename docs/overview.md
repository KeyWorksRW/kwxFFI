# kwxFFI Project Overview

## What is kwxFFI?

kwxFFI (wxWidgets Foreign Function Interface) is a C-language wrapper library that exposes wxWidgets C++ functionality through a pure C API. Any language with a C FFI can build native wxWidgets applications on top of it, including languages with no C++ interop at all.

One C surface drives six bindings, each generated from the declarations in `include/` by the `kwxgen` tool:

| Binding | Repository | `kwxgen --lang` |
|---------|------------|-----------------|
| Fortran | `kwxFortran` | `fortran` |
| Go | `kwxGO` | `go` |
| Julia | `kwxJulia` | `julia` |
| LuaJIT | `kwxLuaJIT` | `lua` |
| Rust | `kwxRust` | `rust` |
| TypeScript | `kwxTypeScript` | `typescript` |

`lua` is the LuaJIT backend's own name (`LanguageEmitter::Name()`); `--lang luajit` is still
accepted and is normalised to `lua` before dispatch, so older scripts keep working.

## Why C Wrappers?

C++ has no standardized ABI (Application Binary Interface), meaning:
- Different compilers produce incompatible binaries
- Name mangling varies between compilers
- Class layouts and vtables differ
- Exception handling is not portable

C, however, has a well-defined calling convention that virtually every programming language can interface with. By wrapping wxWidgets C++ classes in C functions, we create a stable interface that any language can call.

## Architecture

```
Foreign language — Fortran, Go, Julia, LuaJIT, Rust, TypeScript
        │  C ABI call (extern "C", opaque void* handles, UTF-8 char*)
        ▼
kwxFFI — C wrapper library (wxButton_Create, wxWindow_Show, ...)
        │  direct C++ method calls, same process
        ▼
wxWidgets 3.3.2+ — built static, wxUSE_UNICODE_UTF8=1
        │  OS API calls
        ▼
Operating system — Windows, macOS, Linux/GTK
```

kwxFFI is a thin in-process shim, not a separate server: a pointer handed to a binding is the actual wxWidgets object, so there is no marshaling cost beyond the FFI boundary itself.

## Repository layout

| Path | Contents |
|------|----------|
| `include/` | Public C headers. `kwx_classes.h` is the aggregator that `kwxgen` parses. |
| `src/` | Wrapper implementations: `wx_*.cpp` per wrapped class or class group, `kwx_*.cpp` for hooks, helpers, constants and utilities. |
| `kwxgen/` | The binding generator: standalone C++23, no wxWidgets dependency. |
| `tests/` | `run_checks.py` plus CMake/CTest suites; `tests/expected/symbols.sha256` is the export digest. |
| `tools/` | Developer utilities, such as the constants-value dump kwxgen consumes. |
| `examples/` | Small consumer samples (`CApp`). |
| `docs/` | This overview and `decisions.md`. |
| `files_list.cmake` | `FFI_HDR_FILES` and `FFI_SRC_FILES`: every file the library builds. |
| `.tts/` | Task scripts, including `build-release.ps1`. |

## Header files (`include/`)

`kwxgen` reads exactly `kwx_classes.h` (and every header that file quoted-includes), `kwx_events.h`, `kwx_keys.h`, `kwx_constants.h`, and `src/kwx_defs.cpp`. A declaration in any other header is invisible to every backend.

| File | Purpose | Parsed |
|------|---------|--------|
| `kwx_classes.h` | Aggregator: the `TClassDef` blocks for every wrapped class. A new module header must be added to its include list or its declarations do not exist. | yes |
| `kwx_events.h` | Event type accessors, `exp_wxEVT_*` and `exp_EVT_*`. | yes |
| `kwx_keys.h` | Key code accessors, `expK_*`. | yes |
| `kwx_constants.h` | Free functions, `WXFFI_EXPORT` constants, and `wxCFree`. | yes |
| `kwx_classes_sync.h` | Declarations for exports that were implemented before a header declaration existed. | yes |
| `kwx_spec_residual.h` | Residual spec entries that no other module owns. | yes |
| `kwx_hook_exports.h`, `kwx_propgrid_hooks.h`, `kwx_richtext_hooks.h` | Hook setters for protected virtuals. | yes |
| `kwx_accessible.h`, `kwx_msaa.h` | Accessibility wrappers. | yes |
| Module headers: `kwx_core_extra.h`, `kwx_dialogs_extra.h`, `kwx_grid_extra.h`, `kwx_html.h`, `kwx_log.h`, `kwx_methods_gdi.h`, `kwx_methods_views.h`, `kwx_methods_window.h`, `kwx_net_extra.h`, `kwx_process.h`, `kwx_propgrid_extra.h`, `kwx_regex_xml_extra.h`, `kwx_ribbon_extra.h`, `kwx_richtext.h`, `kwx_thread_extra.h`, `kwx_combo_extra.h`, `kwx_console.h`, `kwx_aui_serializer.h`, `kwx_date_locale_extra.h`, `kwx_file_stream_extra.h`, `kwx_gesture_extra.h` | Focused class groups. | yes (via `kwx_classes.h`) |
| `kwx_types.h` | The `T*` macros that annotate C signatures. | no |
| `kwx_def.h` | `EXPORT`, `WXFFI_EXPORT`, `WXFFI_CONSTANT_INT`, `WXFFI_CONSTANT_STR`. | no |
| `kwx_wrapper.h` | Precompiled header: all wxWidgets includes, version gates, and the helper class bodies (`wxClosure`, `wxCallback`, `kwx*` classes). | no |
| `kwx_helper_*.h` | C++ helper class bodies and callback typedefs, pulled in by `kwx_wrapper.h`. | no |
| `kwx_grid.h` | Grid helper classes and callback types. | no |
| `kwx_msw_aliases.h`, `kwx_platform_aliases.h` | `using` aliases for classes that do not exist on every platform, inside `#ifdef __cplusplus`. | parsed, aliases only |
| `kwx_glue.h` | Backward-compatibility shim. Include the focused headers instead; never add declarations here. | no |

Parsed headers must compile as C99, because the Go cgo preamble includes them. Keep them free of classes, templates, namespaces, references, `using` (outside a `__cplusplus` guard) and C++ keywords; use only the `T*` macros, `void*` and C scalar types. Never guard a declaration with a preprocessor `#if`: kwxgen ignores guards, so the guard only breaks the platform that cannot compile it. Alias the type instead, and guard only the implementation.

## Source files (`src/`)

- `wx_<class>.cpp` wraps one wxWidgets class or a tight group of related classes (`wx_button.cpp`, `wx_window.cpp`, `wx_frame.cpp`, `wx_event.cpp`).
- `kwx_*.cpp` holds shared helpers and special cases (`kwx_extra.cpp`, `kwx_hooks.cpp`, `kwx_console.cpp`, `kwx_stream.cpp`, `kwx_defs.cpp`).
- `kwx_wrapper.cpp` implements `wxCFree` and other core helpers. `kwx_constants_table_gen.cpp` is generated by the TypeScript emitter and must stay byte-identical to its output.

Every source file must be listed in `FFI_SRC_FILES` in `files_list.cmake`.

## Wrapper function pattern

```cpp
extern "C"
{
    // Constructor: returns a new object that the caller owns.
    EXPORT wxButton* wxButton_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                     int width, int height, int style)
    {
        return new wxButton(parent, id, *text, wxPoint(x, y), wxSize(width, height), style);
    }

    // Method: self is the receiver.
    EXPORT void wxWindow_Show(wxWindow* self, int show)
    {
        self->Show(show != 0);
    }

    // TClass(wxString) return: caller releases it with wxString_Delete.
    EXPORT wxString* wxControl_GetLabel(wxControl* self)
    {
        return new wxString(self->GetLabel());
    }

    // TString return: strdup'ed UTF-8, caller releases it with wxCFree.
    EXPORT TString wxNumberFormatter_GetThousandsSeparator()
    {
        return strdup(wxUILocale::GetCurrent().GetNumberFormatting().groupSeparator.utf8_string().data());
    }
}
```

Key conventions:
- **Naming**: `wxClassName_MethodName` mirrors wxWidgets. A few headers use a shortened prefix, so the C symbol in the header is authoritative rather than reconstructed from the class name.
- **Self pointer**: first parameter of every method — `TSelf(ClassName)` in the declaration, `wxClass*` in the definition.
- **Geometry**: `TPoint`/`TSize`/`TRect` expand to individual `int` parameters and are reconstructed in the wrapper.
- **No null checks**: passing null is undefined behavior. Do not add `if (ptr == nullptr)` guards; each binding's type system is expected to reject null.
- **Ownership**: constructors and `TClassOwned` returns belong to the caller; `TClass`, `TClassRef` and `TSelf` are borrowed.

## Type macros

The `T*` macros in `kwx_types.h` annotate a plain C signature so a generator can recover intent that the C type itself cannot express. The ones that matter most:

| Macro | C expansion | Use |
|-------|-------------|-----|
| `TClass(T)`, `TClassRef(T)` | `void*` | Borrowed handle |
| `TClassOwned(T)` | `void*` | Returned object the caller must delete |
| `TSelf(T)` | `void*` | Receiver; first parameter only |
| `TBool`, `TBoolInt` | `int` | Boolean |
| `TChar`, `TIntPtr`, `TInt64`, `TUInt*` | `char`, `intptr_t`, `int64_t`, fixed-width unsigned | Scalars |
| `TString`, `TStringOut` | `char*` | UTF-8 input; as a return type see Strings |
| `TStringLen` | `int` | Byte count |
| `TPoint(x, y)`, `TSize(w, h)`, `TRect(x, y, w, h)` | Expanded `int` parameters | Geometry |
| `TIntOut`, `TLongOut`, `TDoubleOut`, `TBoolOut`, `TSizeTOut`, `TInt64Out` | Pointer to scalar | Callee writes only |
| `TIntInOut`, `TDoubleInOut`, `TULongInOut` | Pointer to scalar | Callee reads the incoming value first |
| `TArrayString(n, p)`, `TArrayInt(n, p)`, `TArrayIntPtr(n, p)`, `TArrayObject(n, T, p)` | Count plus pointer | Arrays |
| `TBytesIn`/`TBytesOut`, `TIntArrayIn`/`TIntArrayOut`, `TCookie` | Typed pointers | Buffers and documented intent |

Use `TClassOwned` for every non-constructor factory (`Clone`, `GetNextEntry`, `NewStream`, `NewEntry`, ...). Without it the generated wrapper treats the result as borrowed, and its `Delete()` becomes a no-op that leaks the object. The OUT versus INOUT distinction is not cosmetic: Fortran maps them to `INTENT(OUT)` and `INTENT(INOUT)`.

## String handling

kwxFFI requires wxWidgets 3.3.2 or later built with `wxUSE_UNICODE_UTF8=1`; both are enforced by `#error` in `kwx_wrapper.h`. Every string crossing the ABI is UTF-8 `char*`, with no UTF-16/UTF-32 conversion, and no conversion cost for languages that are already UTF-8.

Three shapes exist, and conflating them is the most common binding defect:

| Shape | C form | Release with |
|-------|--------|--------------|
| `TClass(wxString)` return (most class getters) | `wxString*` allocated with `new wxString` | `wxString_Delete` |
| `TString` / `TStringVoid` return | `strdup`'ed `char*`, caller owns | `wxCFree` |
| Borrowed `TString` return | `char*` pointing into another object | never free |

Only three accessors return a borrowed string — `wxFgets`, `kwxUtf8Buffer_Data`, `wxInputSinkEvent_LastInput` — and the split is centralised in `kwxgen/src/lang/lang_common.h`. Do not re-derive it in an emitter, and do not treat a `TString` return as a `wxString*`: that crashes, and freeing a borrowed return corrupts the heap.

Helpers: `wxString_Create`, `wxString_CreateUTF8`, `wxString_CreateLen`, `wxString_GetString` and `wxString_Delete` in `src/kwx_extra.cpp`; `kwxUtf8Buffer_Create`/`_Data`/`_Delete` give a stable view of a wxString's UTF-8 content.

## Event handling

wxWidgets uses an event system for GUI callbacks. kwxFFI bridges this with:

- **Event type exports** — `exp_wxEVT_NAME()` returns the integer event type, so bindings never hardcode values. Implement with `MAKE_EVENT_WRAPPER(wxEVT_NAME)`; `MAKE_EVT_WRAPPER` produces the `exp_EVT_*` spelling.
- **`wxClosure`** — a reference-counted wrapper around a foreign function pointer and its associated data.
- **`wxCallback`** — connects to the wxWidgets event system and invokes its closure when the event fires.

The preferred registration path is `wxEvtHandler_Bind`, which routes through `wxEvtHandler::Bind()`. `wxEvtHandler_Unbind` removes every handler installed by `Bind` for an id range and event type; `wxEvtHandler_UnbindClosure` removes only the one installed for a specific closure, leaving other handlers on the same range in place. The legacy `wxEvtHandler_Connect` / `wxEvtHandler_Disconnect` pair is still exported. A directly-derived `wxEvent` subclass with no methods of its own still gets a wrapper type, so a binding can downcast an untyped event pointer and call inherited `wxEvent` accessors.

## Callback hooks (protected virtuals)

wxWidgets dispatches application customisation through protected virtuals that a foreign language cannot override. The `kwx<Base>` helper classes forward them:

- `kwx<Base>_Create(void* pObject, ...)` stores the opaque foreign handle; each `kwx<Base>_SetOn<Hook>(self, void* pFunction)` installs one callback.
- Every callback is `void (*)(void* pObject, ...)`; `pObject` comes back unchanged as the first argument and is never registered globally.
- A hook that must produce a value calls `Set<Name>Result()` on the same object before returning.
- An unset callback keeps the wxWidgets default behaviour; overrides are null-guarded.
- Two setter ABIs coexist: one distinct function per hook, and the uniform `…WithData(object, pFunction, void* data)` form whose callback is `void (*)(void* data, void* a, void* b)`. Use the uniform form when several hooks on one object share a shape, because the object pointer alone cannot identify the hook. The rich-text family (`include/kwx_richtext_hooks.h`) is the reference implementation.
- Hook declarations live in a parsed header; their C++ bodies live in `src/kwx_hooks.cpp`, `src/kwx_propgrid_hooks.cpp`, or an unparsed `kwx_helper_*.h`.

## Helper classes (`kwx*` prefix)

| Class | Purpose |
|-------|---------|
| `kwxAppConsole`, `kwxApp` | Application objects and protected-virtual forwarding |
| `kwxEventHandler` | Event handler with foreign hooks |
| `kwxDataObject`, `kwxDragDataObject` | Custom clipboard and drag data |
| `kwxDropTarget`, `kwxTextDropTarget`, `kwxFileDropTarget` | Drag-and-drop targets |
| `kwxTextValidator` | Validator with foreign callbacks |
| `kwxConnection`, `kwxServer`, `kwxClient` | IPC |
| `kwxPrintout`, `kwxPreviewFrame` | Printing |
| `kwxTreeControl` | Tree control with a compare callback |
| `kwxGridTable` | Grid data source with foreign callbacks |
| `kwxComboCtrl`, `kwxOwnerDrawnComboBox`, `kwxListViewComboPopup`, `kwxTreeCtrlComboPopup` | Combo customisation and popups |
| `kwxAccessible`, `kwxAccString` | Accessibility callbacks and string out-parameters |
| `kwxPGProperty`, `kwxPGTextCtrlEditor`, `kwxPropertyGridPage` | PropertyGrid extension points |

Bodies live in `kwx_wrapper.h` / `kwx_helper_*.h` and the matching `src/` file. The `ELJ*` names are historical and no longer used. Constructing `kwxAppConsole` or `kwxApp` sets the process-wide wxWidgets application singleton and destroying it clears that singleton, so create one per process.

## Console Applications

The FFI supports `wxAppConsole` for programs that are not GUI applications. The lifecycle is exposed through `kwxConsoleInitialize()`, `kwxConsoleRun()`, `kwxConsoleExitMainLoop()` and `kwxConsoleShutdown()`, declared in `include/kwx_console.h`. A console application does not initialize the GUI toolkit — it starts wxWidgets with a `wxAppConsole` even when the GUI libraries are linked, so no display connection is made.

Console application traits install `wxLogStderr` and a console `wxMessageOutput`, so `LogError()` / `LogWarning()` and command-line help or syntax errors reach stderr through wx log formatting rather than hand-written writes. Subsystem choice belongs to the consumer's executable rule, not to the library: the kwxFFI archive is subsystem-neutral, and a console program must be linked with the console subsystem (MSVC `/SUBSYSTEM:CONSOLE`, CMake `add_executable()` without `WIN32`, no `-mwindows` for MinGW/clang, `go build` without `-ldflags "-H windowsgui"`).

## kwxgen — the binding generator

`kwxgen` is a standalone C++23 executable in `kwxgen/` with no wxWidgets dependency. It parses the headers into an in-memory model and renders each language backend from that model, so no binding hand-writes signature wrappers. It never modifies kwxFFI: `generate` writes only into a consumer tree.

Pipeline: `kwxgen.config.json` (optional, current directory) → `RunParsers` (`kwx_events.h`, `kwx_keys.h`, `src/kwx_defs.cpp`, `kwx_constants.h`, then `kwx_classes.h` and its quoted includes) → duplicate-symbol removal → optional constant values → profile → emitter.

| Command | Purpose |
|---------|---------|
| `parse` | Dump the parsed model as JSON. |
| `generate` | Write bindings into a consumer tree. |
| `verify` | Regenerate into a temp directory and compare with what is committed. |
| `check` | Generate TypeScript into a temp directory and run `deno check`. |
| `exports` | Write `.def` / `.map` / `.exp` for the complete surface. |
| `coverage` | Per-backend coverage report; `--require-parity` gates on the TypeScript surface. |
| `emit-ui`, `check-ui` | Write a language-neutral UI descriptor, and validate a project IR against it. |
| `langs`, `profiles` | Enumerate backends and profiles. |
| `all_md_files` | Agent-oriented Markdown generation. |
| `diff` | Declared but not implemented. |

Every backend defaults to `--profile full`. `--profile gui` is an explicit opt-down that drops the base-utility classes and adds back anything referenced by a retained signature, so generated code always resolves its types. Class selection is one shared rule in `kwxgen/src/lang/lang_common.h` — no backend keeps a private predicate or a hardcoded class list. Output is deterministic and LF-only, and is never patched by hand: fix the emitter instead.

## Adding New Wrappers

1. **Add the declaration** inside the class's existing `TClassDef` block in the owning module header — or in `kwx_classes_sync.h` when the export already exists without a declaration. A brand-new module header must also be added to the quoted include list in `kwx_classes.h`.
2. **Implement it** in the matching `src/wx_*.cpp` inside `extern "C"`, prefixed `EXPORT`, using the correct ownership and intent macros.
3. **Register new files** in `FFI_HDR_FILES` / `FFI_SRC_FILES` in `files_list.cmake`.
4. **Build Debug** and run `python tests/run_checks.py`.
5. **Update the digest** (`tests/expected/symbols.sha256`) only when the exported surface change is intended.
6. **Build Release** and verify all six consumers with `kwxgen verify --dir wx/`.

For events, use the `MAKE_EVENT_WRAPPER(wxEVT_NAME)` macro in the source file. Never guard a declaration by platform, never add a null-pointer check to a production wrapper, and never edit generated consumer output instead of the generator.

## Build and Test

```sh
cmake --fresh --preset ninja-clang
cd build && ninja -f build-Debug.ninja

python tests/run_checks.py            # static checks, coverage, export digest, deno
python tests/run_checks.py --static   # source-only, no generator binary needed
```

The suite is expected to be green. A `guard_lint`, `guard_parity` or `export_snapshot` failure is a real defect, not noise. See `tests/README.md` for check semantics and `kwxgen/README.md` for generator usage.

## Related documentation

- `docs/decisions.md` — rationale for the null-check policy, profiles, parity and helper conventions.
- `kwxgen/README.md` — generator usage.
- `tests/README.md` — check semantics and CTest layout.

## Credits

This project is loosely based on the FFI layer from [wxHaskell](https://codeberg.org/wxHaskell/wxHaskell).
