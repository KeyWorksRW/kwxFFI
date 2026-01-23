# kwxFFI Project Overview

## What is kwxFFI?

kwxFFI (wxWidgets Foreign Function Interface) is a C-language wrapper library that exposes wxWidgets C++ functionality through a pure C API. This enables programming languages that support the C calling convention to use wxWidgets for building cross-platform GUI applications.

## Why C Wrappers?

C++ has no standardized ABI (Application Binary Interface), meaning:
- Different compilers produce incompatible binaries
- Name mangling varies between compilers
- Class layouts and vtables differ
- Exception handling is not portable

C, however, has a well-defined calling convention that virtually every programming language can interface with. By wrapping wxWidgets C++ classes in C functions, we create a stable interface that any language can call.

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    Foreign Language                         │
│           (Fortran, Go, Julia, LuaJIT, Rust)               │
└─────────────────────────────────────────────────────────────┘
                              │
                              │ FFI Call (C calling convention)
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                         kwxFFI                               │
│              C wrapper functions (this library)             │
│         wxButton_Create(), wxWindow_Show(), etc.            │
└─────────────────────────────────────────────────────────────┘
                              │
                              │ C++ method calls
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                       wxWidgets                             │
│                  C++ GUI framework                          │
└─────────────────────────────────────────────────────────────┘
                              │
                              │ OS API calls
                              ▼
┌─────────────────────────────────────────────────────────────┐
│                    Operating System                         │
│            (Windows, macOS, Linux/GTK)                      │
└─────────────────────────────────────────────────────────────┘
```

## Key Files and Their Roles

### Header Files (`include/`)

| File | Purpose |
|------|---------|
| `wrapper.h` | Precompiled header with all wxWidgets includes and helper classes. Contains `wxClosure`, `wxCallback`, and derived classes for callbacks/events. |
| `wxffi_def.h` | Export macros (`EXPORT`, `WXFFI_EXPORT`) for cross-platform DLL building. |
| `wxffi_types.h` | Type macros that add semantic meaning to function signatures (`TClass`, `TString`, `TPoint`, etc.). Enables foreign language tools to generate proper marshalling code. |
| `wxffi_glue.h` | All C wrapper function declarations. This is the main "API" header that foreign languages reference. |
| `wxffi_grid.h` | Callback types and helper class for custom grid data sources. |

### Source Files (`src/`)

Each `wx_*.cpp` file wraps a specific wxWidgets class or group of related classes:

- `wx_button.cpp` - Button controls
- `wx_window.cpp` - Base window functionality
- `wx_frame.cpp` - Frame/main window
- `wx_event.cpp` - Event types and handling
- etc.

### Build Files

| File | Purpose |
|------|---------|
| `CMakeLists.txt` | Main CMake configuration. Uses FetchContent to download wxWidgets 3.3+. |
| `files_list.cmake` | List of source files to compile. Add new wrapper files here. |

## Wrapper Function Pattern

Every wxWidgets class method is wrapped following this pattern:

```cpp
// Constructor - returns pointer to new object
EXPORT wxButton* wxButton_Create(wxWindow* parent, int id, wxString* label, 
                                  int x, int y, int w, int h, long style)
{
    return new wxButton(parent, id, *label, wxPoint(x, y), wxSize(w, h), style);
}

// Method - takes 'self' pointer as first parameter
EXPORT void wxWindow_Show(wxWindow* self, int show)
{
    self->Show(show != 0);
}

// String return - allocates new wxString, caller must free
EXPORT wxString* wxButton_GetLabel(wxButton* self)
{
    wxString* result = new wxString();
    *result = self->GetLabel();
    return result;
}
```

Key conventions:
- **Naming**: `wxClassName_MethodName` mirrors wxWidgets naming
- **Self pointer**: First parameter for methods (like `this` in C++)
- **Geometry**: `wxPoint` and `wxSize` are expanded to `int x, int y, int w, int h`
- **Strings**: Input as `wxString*`, output allocated with `new wxString()`
- **Memory**: Caller is responsible for freeing returned objects

## Event Handling

wxWidgets uses an event system for GUI callbacks. kwxFFI bridges this with:

### wxClosure
A reference-counted wrapper around a foreign function pointer and its associated data. When an event occurs, the closure is invoked with the event object.

### wxCallback  
Connects to the wxWidgets event system. When an event fires, the callback invokes its associated closure.

### Event Type Exports
Each wxWidgets event type is exposed through a function:

```cpp
MAKE_EVENT_WRAPPER(EVT_BUTTON)  // Creates expEVT_BUTTON() returning event ID
```

Foreign languages call `expEVT_BUTTON()` to get the event type ID, then register their callback using `wxEvtHandler_Connect()`.

## String Handling

kwxFFI requires wxWidgets 3.3+ built with `wxUSE_UNICODE_UTF8=1`. This means:

- All strings are internally UTF-8
- No UTF-8 ↔ UTF-16/UTF-32 conversions needed
- Better performance and simpler code
- Modern languages (Go, Rust, Julia, etc.) natively use UTF-8

## Helper Classes (ELJ* prefix)

Several classes derive from wxWidgets classes to support callbacks:

| Class | Purpose |
|-------|---------|
| `ELJApp` | Custom wxApp for FFI initialization |
| `ELJDropTarget` | Drag-and-drop target with foreign callbacks |
| `ELJTextDropTarget` | Text-specific drop target |
| `ELJFileDropTarget` | File-specific drop target |
| `ELJPrintout` | Print job with foreign callbacks |
| `ELJConnection` | TCP/IPC connection with foreign callbacks |
| `ELJTreeControl` | Tree control with custom compare callback |
| `ELJGridTable` | Grid data source with foreign callbacks |

Note: "ELJ" is a legacy prefix from the original wxEiffel/wxHaskell projects. These are kwxFFI-specific derived classes that enable callback functionality.

## Adding New Wrappers

1. **Add wxWidgets header** to `wrapper.h` if not already included
2. **Create source file** `src/wx_classname.cpp` following the pattern above
3. **Add declarations** to `wxffi_glue.h`
4. **Register source file** in `files_list.cmake`
5. **Build and test**

For events, use the `MAKE_EVENT_WRAPPER(EVT_NAME)` macro in the source file.

## Credits

This project is based on the FFI layer from [wxHaskell](https://codeberg.org/wxHaskell/wxHaskell). The original code provided a complete wxWidgets 3.2 interface.
