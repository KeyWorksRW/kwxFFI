# kwxgen — kwxFFI Binding Generator

`kwxgen` parses the kwxFFI C header files and generates foreign-language bindings for wxWidgets.
It reads the `include/` headers and `src/kwx_defs.cpp` to build a complete model of the FFI
surface (~653 classes, ~7,925 methods, ~308 events, 99 key constants, ~1,388 defined constants),
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

**Generated output** (`src/gen/`):

- `kwxffi_gen.f90` — the `kwxffi` module: every class method, free function, event, key
  and constant as an `ISO_C_BINDING` `interface` body. This is the single entry point for
  the raw C API; import the names you need with `only:`.
- `kwx_types.f90`, `wx_string.f90` — opaque pointer types and string conversion helpers.
- `wx_window.f90`, `wx_frame.f90`, `wx_controls.f90`, `wx_menus.f90`, `wx_sizers.f90`,
  `wx_events.f90`, `wx_dialogs.f90` — idiomatic wrappers over a subset of the raw API.

Compile and `use` normally:

```fortran
use kwxffi, only: wxOK, wxICON_INFORMATION, wxFrame_Create
use wx_frame
```

There is deliberately no separate constants module: constants, events and keys are part of
`kwxffi`, so `use kwxffi` is the only import needed for the raw API.

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

**Prerequisites:** CMake 3.30+ and a C++23 compiler; the `kwx_ts` runtime from
kwxTypeScript.

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

- `kwx_ffi_gen.ts` — `dlopen` call with all C symbol definitions (classes, free functions,
  events, keys, constants). Import `lib` from this module to call functions directly.
- `kwx_constants_gen.ts` — Eagerly-evaluated numeric exports for all events, keys, and constants.
  Integer-valued constants are read from a single lazily-filled C table; pointer-valued
  constants call their accessor eagerly.
- `kwx_constants_table_gen.cpp` — Generated C table (with `kwxConstants_IntCount` /
  `kwxConstants_IntTable` accessors) consumed by `kwx_constants_gen.ts`. Compile it into the
  kwxFFI shared library alongside the other `src/` files.
- `kwx_free_functions_gen.ts` — TypeScript wrappers for non-class C functions.
- `wx{Class}_gen.ts` — One file per class with a TypeScript class wrapping the FFI calls.
  Constructors are emitted as module-level `createWx{Class}()` functions rather than
  static `Create()` methods: TypeScript requires a derived static side to be assignable
  to every ancestor's static side, which cannot be satisfied once factory signatures
  differ across the hierarchy. Item-deletion methods that collide with the `Delete()`
  destructor are exposed as `DeleteItem()`.
- `kwx_gen.ts` — Master barrel re-export of every generated module.

Run with:

```ts
import { lib } from "./gen/kwx_ffi_gen.ts";

// Or import the barrel for the full class-based API
import "./gen/kwx_gen.ts";

// Run with: kwx_ts your_script.ts
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
| Classes | 653 |
| Class methods | 7,925 |
| Events | 308 |
| Key constants | 99 |
| Defined constants | 1,388 |
| Free functions | 214 |

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
| `--profile <name>` | Surface profile: `full` or `gui` (default: per language — see [Profiles](#profiles)) |

### `verify` — Verify existing bindings

```
kwxgen verify --headers <dir> --defs <file> --lang <lang> --dir <dir>
              [--profile <name>] [--deno-check] [--deno <exe>] [--deno-config <file>]
```

Checks that generated bindings in `--dir` are up to date with the current headers.
Generate and verify must use the same profile, otherwise `verify` will report the excluded
classes as missing.
With `--deno-check`, it also generates into a temp directory and runs `deno check`
on the TypeScript barrel (`kwx_gen.ts`). Without `--deno-config`, kwxgen writes a
small compile-time `kwx/platform` shim and a temporary `deno.jsonc`; pass the
consumer repo's `deno.jsonc` to type-check against the real runtime instead.

### `check` — Type-check generated TypeScript

```
kwxgen check --headers <dir> --defs <file> [--deno <exe>] [--deno-config <file>]
```

Generates TypeScript bindings into a temp directory and runs `deno check` on
`kwx_gen.ts`. No consumer tree is modified. This is the fastest way to verify an
emitter change before regenerating the consumer repo.

```sh
extern/kwxFFI/bin/Debug/kwxgen check \
    --headers extern/kwxFFI/include \
    --defs    extern/kwxFFI/src/kwx_defs.cpp \
    --deno-config deno.jsonc
```

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

### `profiles` — List profiles and per-language defaults

```
kwxgen profiles
```

Prints every profile name and the default profile for each language.

## Profiles

A profile selects how much of the kwxFFI surface a language binding exposes.

| Profile | Description |
|---|---|
| `full` | Every parsed class, free function, event, key and constant. |
| `gui` | Drops base-utility classes (regex, XML, threads/sync, sockets/HTTP/FTP, URL/URI, streams/compression, process spawn, config parsing, date/time, variants, text/temp files) because the runtime's standard library already provides that functionality. Any class still referenced by a retained signature is kept, so the generated code continues to compile. |

Default profile per language:

| Language | Default profile |
|---|---|
| `fortran` | `full` |
| `go` | `gui` |
| `julia` | `gui` |
| `luajit` | `full` |
| `typescript` | `full` |

The `exports` command always emits the complete surface and rejects `--profile`.

### Profile categories

Every class in the parsed model belongs to exactly one category. The authoritative,
regenerated list is `.private/coverage_expansion_inventory.md` (one line per class:
`name | method count | category | owning phase`).

| Category | In `gui`? | Meaning |
|---|---|---|
| `gui` | yes | Wrapped and exposed in every profile. |
| `base-utility` | no | The Go/Julia standard library already provides this functionality (date/time, filesystem paths, streams and compression, XML, threads/sync, process spawn, sockets/HTTP/FTP, URL/URI, regex, memory buffers, command-line parsing, dynamic libraries, variants, text/temp files, tokenizers, containers). Listed in `GuiExcludedClasses()` in `kwxgen/src/profile.cpp`. |
| `msw-excluded` | no | MSW-only and never wrapped (`wxAutomationObject`, `wxActiveXContainer`). |
| `legacy` | no | Deprecated base class, never wrapped (`wxNodeBase`, `wxVariantData`, `wxObjectRefData`). |

`wxFileName`, `wxDir`, `wxDirTraverser`, `wxStandardPaths`, `wxConfigBase`,
`wxFileConfig`, `wxLocale`, `wxUILocale`, `wxNumberFormatter` and `wxTranslations` stay
in `gui` by an explicit scope decision, even though a runtime could substitute its own
implementation.

MSW-only classes that survive through the alias pattern in
`include/kwx_msw_aliases.h` (`wxTaskBarButton`, `wxRegConfig`, `wxRegKey`,
`wxDDEClient`, `wxDDEServer`, `wxAuiMSWToolBarArt`, `wxWebViewIE`, `wxWebViewEdge`)
stay in `gui`.

### Rule: a new class must be classified

Adding a class to `include/` without classifying it is a defect: an unclassified
base-utility class silently leaks into the Go and Julia surface. To add a class:

1. Run `kwxgen parse --headers include --defs src/kwx_defs.cpp --out <model.json>`.
2. Regenerate `.private/coverage_expansion_inventory.md` from the new model.
3. If the class is `base-utility`, add its exact name to `GuiExcludedClasses()` in
   `kwxgen/src/profile.cpp`, keeping the list sorted.
4. Confirm `kwxgen generate --lang go --profile gui --out <temp>` omits it while
   `--profile full` includes it.

A `base-utility` class that a retained signature still references (as an ancestor,
mixin, parameter type or return type) is added back automatically, so the generated
bindings continue to compile. That is why `wxDateTime`, `wxVariant`, `wxArray`,
`wxArrayString`, `wxList`, `wxStreamBase`, `wxInputStream` and `wxOutputStream` appear
in `gui` output even though they are `base-utility`.
