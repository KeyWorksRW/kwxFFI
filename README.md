# kwxFFI/kwxgen

## ⚠️ Warning: Not Production Ready

**Do not use this library in production yet.**

Expect significant API churn while the language bindings are developed. Do not use this library until the language ports that depend on it are fully implemented and stabilized.

---

## What this is

kwxFFI creates language bindings for [wxWidgets](https://www.wxwidgets.org/): a flat C ABI that lets non-C languages build cross-platform GUI applications which render with native controls on Windows, macOS and Linux. It exports roughly 11,000 wrapper functions — 13,002 exported symbols in total including constants and enums, pinned by `tests/expected/symbols.sha256`.

`kwxgen` reads the kwxFFI headers and generates each consumer's binding. The C wrappers are maintained by hand (largely with AI coding agents); the per-language bindings are generated. Never patch generated output — fix the parser, the emitter or the header, then regenerate.

**Requirements**: wxWidgets **3.3.2 or later**, built with UTF-8 Unicode support (`wxUSE_UNICODE_UTF8=1`). Both are enforced by `#error` in `include/kwx_wrapper.h`.

## Bindings

Six languages are under development:

| Language | Repository | `kwxgen --lang` |
|---|---|---|
| Fortran | [kwxFortran](https://github.com/KeyWorksRW/kwxFortran) | `fortran` |
| Go | [kwxGO](https://github.com/KeyWorksRW/kwxGO) | `go` |
| Julia | [kwxJulia](https://github.com/KeyWorksRW/kwxJulia) | `julia` |
| LuaJIT | [kwxLuaJIT](https://github.com/KeyWorksRW/kwxLuaJIT) | `lua` |
| Rust | [kwxRust](https://github.com/KeyWorksRW/kwxRust) | `rust` |
| TypeScript | [kwxTypeScript](https://github.com/KeyWorksRW/kwxTypeScript) | `typescript` |

## Documentation

| Document | Contents |
|---|---|
| [docs/overview.md](docs/overview.md) | Architecture, header anatomy, type and memory rules, kwxgen commands |
| [docs/decisions.md](docs/decisions.md) | Design decisions and their rationale |
| [kwxgen/README.md](kwxgen/README.md) | Generator usage, per-backend output, regeneration workflow |
| [tests/README.md](tests/README.md) | What each check means, how to triage a digest mismatch |

## Building

```sh
cmake -S . -B build -G Ninja
cmake --build build
```

wxWidgets must be discoverable by CMake. The root build produces both kwxFFI and `kwxgen` (written to `bin/<config>/kwxgen`). Options, all `OFF` by default:

| Option | Effect |
|---|---|
| `KWXFFI_BUILD_SHARED` | Build the shared library instead of the default static one |
| `KWXFFI_BUILD_BOTH` | Build static and shared from one wxWidgets build |
| `KWXFFI_BUILD_TESTS` | Register the kwxFFI tests |
| `KWXFFI_BUILD_TOOLS` | Build the developer tools |

`kwxgen` is a standalone C++23 program with no wxWidgets dependency and can be built on its own with `cmake -S kwxgen -B build/kwxgen -G Ninja`.

## Testing

```sh
python tests/run_checks.py --static        # source-only checks, no build required

cmake -S tests -B build/standalone-tests -G "Ninja Multi-Config"
cmake --build build/standalone-tests --config Release
ctest --test-dir build/standalone-tests -C Release --output-on-failure
```

# Credits

The original FFI code came from the wxHaskell (https://codeberg.org/wxHaskell/wxHaskell) team, which in turn was inspired by wxc project. A huge thanks go out to these teams for creating the original wxWidgets 3 interface!
