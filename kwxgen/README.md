# kwxgen — kwxFFI Binding Generator

`kwxgen` parses the kwxFFI C header files and generates foreign-language bindings for wxWidgets.
It reads the `include/` headers and `src/kwx_defs.cpp` to build a complete model of the FFI
surface (~572 classes, ~4,679 methods, ~485 events, 99 key constants, ~1,174 defined constants),
then emits idiomatic bindings for each target language.

kwxgen lives in the `kwxgen/` subdirectory of kwxFFI. When a language port fetches kwxFFI (as a
submodule or checkout), kwxgen is included automatically. The generated files are written into
the *consumer* repo's source tree — kwxFFI itself is unchanged by `generate`.

---

## Caller Integration Guide

Each language port follows the same three-step pattern:

1. Obtain kwxFFI (submodule or clone)
2. Build `kwxgen` — pure C++23, zero external dependencies, builds in seconds
3. Run `kwxgen generate` — reads the kwxFFI headers, writes bindings into your repo

The sections below detail the exact steps for each language.

---

### Fortran ([kwxFortran](https://github.com/KeyWorksRW/kwxFortran))

**Prerequisites:** CMake 3.30+ and a C++23 compiler

**Step 1 — Build kwxgen and generate** (from CMakeLists.txt or a script):

```sh
cmake -S extern/kwxFFI/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen

extern/kwxFFI/bin/Debug/kwxgen generate \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    fortran \
    --out     src/gen/
```

**Generated output** (`src/gen/`): one `wx_button.f90`-style `module` per class using
`ISO_C_BINDING` `interface` blocks, plus `wx_events.f90`, `wx_keys.f90`,
`wx_constants.f90`. Compile and `use` normally:

```fortran
use wx_button
use wx_events
```

---

### Go ([kwxGO](https://github.com/KeyWorksRW/kwxGO))

**Prerequisites:** CMake 3.30+, a C++23 compiler.

```
add_custom_command(
    OUTPUT  ${CMAKE_SOURCE_DIR}/wx/events_gen.go
            ${CMAKE_SOURCE_DIR}/wx/keys_gen.go
            ${CMAKE_SOURCE_DIR}/wx/constants_gen.go
    COMMAND kwxgen generate
    DEPENDS kwxgen ${KWXFFI_HEADERS}
    COMMENT "Generating Go bindings"
)
```

**Generated output** (`wx/`): one `*_gen.go` file per class + `events_gen.go`,
`keys_gen.go`, `constants_gen.go`. Each file has the appropriate `// #include` cgo
directives.

**Verify bindings are current** (e.g. in CI):

```sh
kwxgen verify --headers extern/kwxFFI/include \
              --defs    extern/kwxFFI/src/kwx_defs.cpp \
              --lang    go --dir wx/
```

---

### Julia ([kwxJulia](https://github.com/KeyWorksRW/kwxJulia))

**Prerequisites:** CMake 3.30+ and a C++23 compiler.

**Step 1 — Build kwxgen:**

```sh
cmake -S extern/kwxFFI/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen
```

**Step 2 — Generate bindings** (typically from `deps/build.jl` or a Makefile):

```sh
extern/kwxFFI/bin/Debug/kwxgen generate \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    julia \
    --out     src/gen/
```

**Generated output** (`src/gen/`): one `.jl` file per class using `ccall`, plus
`events.jl`, `keys.jl`, `constants.jl`. Include from your package:

```julia
include("gen/events.jl")
include("gen/Button.jl")
```

Regenerate any time kwxFFI is updated; commit the generated files alongside hand-written code.

---

### LuaJIT ([kwxLuaJIT](https://github.com/KeyWorksRW/kwxLuaJIT))

**Prerequisites:** CMake 3.30+ and a C++23 compiler to build kwxgen

**Step 1 — Build kwxgen** (standalone, no CMake integration required for pure-Lua projects):

```sh
cmake -S extern/kwxFFI/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen
```

**Step 2 — Generate bindings:**

```sh
extern/kwxFFI/bin/Debug/kwxgen generate \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    luajit \
    --out     lua/wx/
```

**Generated output** (`lua/wx/`): `kwxffi.lua` — a single file with a consolidated
`ffi.cdef[[ ... ]]` block covering all declarations, plus one helper `.lua` per class
with idiomatic Lua wrappers. Load with:

```lua
local wx = require("wx.kwxffi")
```

---

### TypeScript ([kwxTypeScript](https://github.com/KeyWorksRW/kwxTypeScript))

**Prerequisites:** CMake 3.30+ and a C++23 compiler; Deno 1.40+.

**Step 1 — Build kwxgen:**

```sh
cmake -S extern/kwxFFI/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen
```

**Step 2 — Generate bindings** (from a `Makefile` or your build script):

```sh
extern/kwxFFI/bin/Debug/kwxgen generate \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    typescript \
    --out     gen/
```

**Generated output** (`gen/`):

- `kwx_ffi_gen.ts` — `Deno.dlopen` call with all C symbol definitions (classes, free functions,
  events, keys, constants). Import `lib` from this module to call functions directly.
- `kwx_constants_gen.ts` — Eagerly-evaluated numeric exports for all events, keys, and constants.
- `kwx_free_functions_gen.ts` — TypeScript wrappers for non-class C functions.
- `wx{Class}_gen.ts` — One file per class with a TypeScript class wrapping the FFI calls.
- `kwx_gen.ts` — Master barrel re-export of every generated module.

Run with:

```ts
import { lib } from "./gen/kwx_ffi_gen.ts";

// Or import the barrel for the full class-based API
import "./gen/kwx_gen.ts";

// Run with: deno run --allow-ffi your_script.ts
```

## Re-generating After kwxFFI Updates

When kwxFFI adds new classes or changes signatures:

```sh
# Rebuild kwxgen (in case the generator itself changed)
cmake --build build/kwxgen

# Regenerate
extern/kwxFFI/bin/Debug/kwxgen generate \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    <your-lang> \
    --out     <your-output-dir>/

# Commit the updated generated files
git add <your-output-dir>/
git commit -m "Regenerate bindings against kwxFFI <commit>"
```

Use `verify` first to see what changed before committing:

```sh
extern/kwxFFI/bin/Debug/kwxgen verify \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    <your-lang> \
    --dir     <your-output-dir>/
```

---

## Current Coverage

| Category | Count |
|---|---|
| Classes | 572 |
| Class methods | 4,679 |
| Events | 315 |
| Key constants | 99 |
| Defined constants | 1,174 |
| Free functions | 23 |

## Building

`kwxgen` is a standalone C++23 program with no wxWidgets dependency. It lives in the
`kwxgen/` subdirectory of kwxFFI:

```sh
# Build from the kwxgen directory
cmake -S kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen

# Or from the kwxFFI root (builds kwxFFI and kwxgen together)
cmake -S . -B build -G Ninja
cmake --build build --target kwxgen
```

The binary is output to `bin/<config>/kwxgen` (e.g., `bin/Debug/kwxgen`).

## Commands

### `parse` — Parse headers to JSON

```
kwxgen parse --headers <dir> --defs <file> [--out <file>]
```

Parses all kwxFFI headers and emits a JSON model of the entire FFI surface. If `--out` is omitted or set to `-`, JSON is written to stdout.

| Option | Description |
|---|---|
| `--headers <dir>` | Path to the kwxFFI `include/` directory |
| `--defs <file>` | Path to `src/kwx_defs.cpp` |
| `--out <file>` | Output JSON file (default: stdout) |

### `generate` — Generate language bindings

```
kwxgen generate --headers <dir> --defs <file> --lang <lang> --out <dir>
```

Parses the headers and generates binding source files for the specified language.

| Option | Description |
|---|---|
| `--headers <dir>` | Path to the kwxFFI `include/` directory |
| `--defs <file>` | Path to `src/kwx_defs.cpp` |
| `--lang <lang>` | Target language (see `kwxgen langs`) |
| `--out <dir>` | Output directory for generated files |
| `--libname <name>` | Runtime shared-lib name embedded in bindings (default: `kwxFFI`) |

### `verify` — Verify existing bindings

```
kwxgen verify --headers <dir> --defs <file> --lang <lang> --dir <dir>
```

Checks that generated bindings in `--dir` are up to date with the current headers.

### `diff` — Show header changes

```
kwxgen diff --headers <dir> --manifest <file>
```

Compares the current headers against a saved manifest to show what has changed.

### `langs` — List available backends

```
kwxgen langs
```

Prints the list of available language backends.
