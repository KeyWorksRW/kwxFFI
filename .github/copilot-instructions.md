# kwxFFI - wxWidgets Foreign Function Interface

## Project Overview

kwxFFI provides C-language wrapper functions around wxWidgets C++ classes, enabling foreign languages to use wxWidgets for building GUI applications. The library exposes wxWidgets functionality through a pure C API that can be called from any language supporting the C calling convention.

### Target Languages

This FFI is designed to support the following language ports:
- kwxFortran
- kwxGO
- kwxJulia
- kwxLuaJit
- kwxPerl
- kwxRust

### Key Design Decisions

- **AI-generated wrappers**: Unlike the original wxHaskell/wtc which used a Haskell tool to generate C wrappers, this project uses AI agents with proper instructions. This eliminates setup complexity and makes changes easier.
- **UTF-8 strings**: Requires wxWidgets 3.3+ built with `wxUSE_UNICODE_UTF8=1`. All strings are UTF-8, eliminating UTF-16/UTF-32 conversion overhead.
- **No deprecated support**: Deprecated functions, events, and constants are not wrapped.
- **Expanded macros**: Most generation macros have been expanded for better code readability.

## Build System

- **CMake-based build**: Uses CMake with FetchContent to automatically download and build wxWidgets 3.3+
- **wxWidgets headers location**: After building, wxWidgets headers are in `build/_deps/wxwidgets-src/include`
- **wxWidgets platform setup headers**: 
  - Windows: `build/_deps/wxwidgets-build/lib/vc_x64_lib/mswu`
  - macOS: `build/_deps/wxwidgets-build/lib/osx_cocoa-unicode-static`
  - Linux: `build/_deps/wxwidgets-build/lib/gtk3_unixu-3.3/include`

## Architecture

### Header Files (`include/`)

#### `wxffi_def.h` - Export Macros
Defines export macros for cross-platform DLL/shared library building:
- `EXPORT` - Used to mark functions for export
- `WXFFI_EXPORT(TYPE, FUNC_NAME)` - Macro for declaring exported functions
- `WXFFI_CONSTANT_INT/STR` - Macros for exposing constants

#### `wxffi_types.h` - Type System
Defines type macros that add semantic meaning to C signatures for FFI generation:
- `TClass(tp)` - Pointer to a wxWidgets class (compiles to `void*` or typed pointer)
- `TSelf(tp)` - The 'self' or 'this' pointer for method calls
- `TString` / `TStringOut` - String input/output parameters
- `TPoint(x,y)` / `TSize(w,h)` / `TRect(x,y,w,h)` - Geometry structures expanded to individual parameters
- `TBool` - Boolean type (int or bool depending on configuration)
- `TArrayString(n,p)` / `TArrayInt(n,p)` - Array parameters with length

These macros enable:
1. Tools to parse signatures and generate marshalling code for foreign languages
2. Optional type-safe compilation with `WXC_USE_TYPED_INTERFACE`

#### `wxffi_glue.h` - Function Declarations
The main header declaring all C wrapper functions:
- **Event type exports**: `expEVT_*()` functions return wxWidgets event type IDs
- **Key code exports**: `expK_*()` functions return key codes
- **Class wrappers**: `wxClassName_MethodName()` function declarations
- Grouped by class/functionality

#### `wxffi_grid.h` - Grid Table Callbacks
Defines callback types and the `ELJGridTable` class for custom grid data sources.

#### `wrapper.h` - C++ Implementation Support (Precompiled Header)
The precompiled header containing:
- All necessary wxWidgets includes
- Helper classes:
  - `wxClosure` - Wraps foreign function callbacks with reference counting
  - `wxCallback` - Event handler that invokes closures
  - `ELJApp` - Custom wxApp subclass for FFI initialization
  - `ELJDropTarget`, `ELJDragDataObject` - Drag-and-drop support
  - Various other ELJ* helper classes
- The `MAKE_EVENT_WRAPPER` macro for implementing event exports

### Source Files (`src/`)

Each `wx_*.cpp` file wraps a specific wxWidgets class or related group of classes. The pattern is:

```cpp
#include "wrapper.h"

extern "C"
{
    // Constructor wrapper
    EXPORT wxClassName* wxClassName_Create(wxWindow* parent, int id, ...)
    {
        return new wxClassName(parent, id, ...);
    }

    // Method wrapper - takes 'self' pointer as first parameter
    EXPORT ReturnType wxClassName_MethodName(wxClassName* self, ...)
    {
        return self->MethodName(...);
    }

    // For methods returning wxString - allocate new string
    EXPORT wxString* wxClassName_GetStringValue(wxClassName* self)
    {
        wxString* result = new wxString();
        *result = self->GetStringValue();
        return result;
    }

    // For methods returning objects by value - copy to output parameter
    EXPORT void wxClassName_GetRect(wxClassName* self, wxRect* outRect)
    {
        *outRect = self->GetRect();
    }
}
```

### Naming Conventions

1. **C wrapper functions**: `wxClassName_MethodName` - mirrors wxWidgets naming
2. **Event exports**: `expEVT_EVENT_NAME` - returns event type as int
3. **Constant exports**: `expConstantName` - returns constant value
4. **Helper classes**: `ELJ*` prefix (legacy from Eiffel-wxWidgets)

### Key Implementation Patterns

#### String Handling
- Input strings: `wxString*` pointer, dereferenced with `*str`
- Output strings: Allocate with `new wxString()`, caller must free

#### Object Creation
- Constructor wrappers return `ClassName*` pointer
- Memory management is caller's responsibility

#### Point/Size/Rect Parameters
- Expanded to individual int parameters: `int x, int y` instead of `wxPoint`
- Reconstructed in wrapper: `wxPoint(x, y)`

#### Callbacks/Events
- `wxClosure` wraps foreign function pointers with associated data
- `wxCallback` connects to wxWidgets event system
- Reference counting manages closure lifetime

## Adding New Wrappers

When wrapping a new wxWidgets class:

1. Add the wxWidgets header to `wrapper.h` if not already included
2. Create `src/wx_classname.cpp` following the pattern above
3. Add declarations to `wxffi_glue.h`
4. Add the source file to `files_list.cmake`

For events, use `MAKE_EVENT_WRAPPER(EVT_NAME)` macro in the implementation.

## Dependencies

- wxWidgets 3.3.0+ (automatically fetched via CMake FetchContent)
- C++23 compiler (MSVC, GCC, or Clang)
- CMake 3.20+

## Related Projects

This library is designed to support wxUiEditor code generation for foreign languages, providing the FFI layer that generated code can call into.
