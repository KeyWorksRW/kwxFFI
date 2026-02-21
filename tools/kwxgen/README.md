# kwxgen — kwxFFI Binding Generator

`kwxgen` parses the kwxFFI C header files and generates foreign-language bindings for wxWidgets.
It reads the `include/` headers and `src/kwx_defs.cpp` to build a complete model of the FFI
surface (~572 classes, ~4,679 methods, ~485 events, 99 key constants, ~1,174 defined constants),
then emits idiomatic bindings for each target language.

**kwxgen lives in kwxFFI and is consumed by the six language port repos.** The generated files
are written into the *consumer* repo's source tree — kwxFFI itself is unchanged by `generate`.

---

## Caller Integration Guide

Each language port follows the same three-step pattern:

1. Obtain kwxFFI (submodule or clone)
2. Build `kwxgen` — pure C++17, zero external dependencies, builds in seconds
3. Run `kwxgen generate` — reads the kwxFFI headers, writes bindings into your repo

The sections below detail the exact steps for each language.

---

### Go (kwxGO)

**Prerequisites:** CMake 3.30+, a C++17 compiler.

**Step 1 — Build kwxgen in your CMakeLists.txt:**

```cmake
set(KWXFFI_DIR ${CMAKE_SOURCE_DIR}/extern/kwxFFI)

add_subdirectory(${KWXFFI_DIR}/tools/kwxgen kwxgen-build)

set(KWXFFI_HEADERS
    ${KWXFFI_DIR}/include/kwx_classes.h
    ${KWXFFI_DIR}/include/kwx_events.h
    ${KWXFFI_DIR}/include/kwx_keys.h
    ${KWXFFI_DIR}/include/kwx_constants.h
)

add_custom_command(
    OUTPUT  ${CMAKE_SOURCE_DIR}/wx/events_gen.go
            ${CMAKE_SOURCE_DIR}/wx/keys_gen.go
            ${CMAKE_SOURCE_DIR}/wx/constants_gen.go
    COMMAND kwxgen generate
                --headers ${KWXFFI_DIR}/include
                --defs    ${KWXFFI_DIR}/src/kwx_defs.cpp
                --lang    go
                --out     ${CMAKE_SOURCE_DIR}/wx/
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

### LuaJIT (kwxLuaJIT)

**Prerequisites:** CMake 3.30+ and a C++17 compiler to build kwxgen

**Step 1 — Build kwxgen** (standalone, no CMake integration required for pure-Lua projects):

```sh
cmake -S extern/kwxFFI/tools/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen
```

**Step 2 — Generate bindings:**

```sh
build/kwxgen/kwxgen generate \
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

### Julia (kwxJulia)

**Prerequisites:** CMake 3.30+ and a C++17 compiler.

**Step 1 — Build kwxgen:**

```sh
cmake -S extern/kwxFFI/tools/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen
```

**Step 2 — Generate bindings** (typically from `deps/build.jl` or a Makefile):

```sh
build/kwxgen/kwxgen generate \
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

### Rust (kwxRust)

**Prerequisites:** CMake 3.30+ and a C++17 compiler

**Step 1 — Invoke kwxgen from `build.rs`:**

```rust
fn main() {
    // Build kwxgen if not already built
    let kwxgen = std::process::Command::new("cmake")
        .args(["--build", "build/kwxgen"])
        .status().expect("cmake build failed");

    // Generate Rust bindings
    std::process::Command::new("build/kwxgen/kwxgen")
        .args([
            "generate",
            "--headers", "extern/kwxFFI/include",
            "--defs",    "extern/kwxFFI/src/kwx_defs.cpp",
            "--lang",    "rust",
            "--out",     "src/gen/",
        ])
        .status().expect("kwxgen failed");

    println!("cargo:rerun-if-changed=extern/kwxFFI/include/kwx_classes.h");
    println!("cargo:rerun-if-changed=extern/kwxFFI/include/kwx_events.h");
}
```

**Generated output** (`src/gen/`): `sys.rs` with `extern "C"` declarations for all
functions; one `button.rs`-style file per class with a safe wrapper struct, `impl` block,
and `Drop` for classes that have a `Delete` method. Include from `lib.rs`:

```rust
mod gen;
pub use gen::button::Button;
```

---

### Perl (kwxPerl)

**Prerequisites:** CMake 3.30+ and a C++17 compiler; Perl 5.32+ with `FFI::Platypus` 2.00+.

**Step 1 — Build kwxgen and generate** (from `Makefile.PL` or a setup script):

```sh
cmake -S extern/kwxFFI/tools/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen

build/kwxgen/kwxgen generate \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --lang    perl \
    --out     lib/Wx/Gen/
```

**Generated output** (`lib/Wx/Gen/`): one `.pm` file per class using
`FFI::Platypus->attach(...)`. Each generated module is a plain `.pm` that can be
`use`d directly:

```perl
use Wx::Gen::Button;
my $btn = Wx::Gen::Button->Create($parent, -1, "OK", ...);
```

---

### Fortran (kwxFortran)

**Prerequisites:** CMake 3.30+ and a C++17 compiler

**Step 1 — Build kwxgen and generate** (from CMakeLists.txt or a script):

```sh
cmake -S extern/kwxFFI/tools/kwxgen -B build/kwxgen -G Ninja
cmake --build build/kwxgen

build/kwxgen/kwxgen generate \
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

## Re-generating After kwxFFI Updates

When kwxFFI adds new classes or changes signatures:

# Rebuild kwxgen (in case the generator itself changed)
cmake --build build/kwxgen

# Regenerate
build/kwxgen/kwxgen generate \
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
build/kwxgen/kwxgen verify \
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

`kwxgen` is a standalone C++17 program with no wxWidgets dependency:

```sh
cmake -S tools/kwxgen -B tools/kwxgen/build -G Ninja
cmake --build tools/kwxgen/build
```

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
