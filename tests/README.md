# kwxFFI tests

Two ways in, both driven from the repository root unless noted.

## Without a CMake build

```sh
python tests/run_checks.py --static
```

`--static` runs only the checks that read the source tree. Without the flag the
export snapshot and the `deno check` wrapper run too, using the newest `kwxgen`
binary found under `bin/` or `build/` (override with `--kwxgen <path>`). Each
check prints one `PASS`, `FAIL`, or `SKIP` line plus a summary; the exit code is
1 only when a check failed. A checker script that does not exist yet reports
`SKIP (not implemented yet)`.

## With CMake and CTest

From `tests/`:

```sh
cmake --preset default
ctest --preset cheap
```

Or equivalently, from the repository root:

```sh
cmake -S tests -B build/tests -G "Ninja Multi-Config"
cmake --build build/tests --config Release
ctest --test-dir build/tests -C Release --output-on-failure
```

The tests project pulls in `kwxgen`, builds `kwxgen_core` from the generator
sources, and registers every check with the `cheap` label.

## What the checks mean

- `guard_lint` — scans `include/*.h` for declarations wrapped in platform
  guards (`__WINDOWS__`, `_WIN32`, `__APPLE__`, `__WXMSW__`, `wxHAS_*`, ...).
  The generator cannot see guards, so a guarded declaration produces bindings
  that only link on one platform. Feature guards (`wxUSE_GUI` and friends) are
  reported as notes, not errors.
- `guard_parity` — compares the guard state of each header declaration against
  its definition in `src/*.cpp` and reports declarations with no definition.
- `export_snapshot` — regenerates the export manifest with `kwxgen exports` and
  diffs it against `tests/expected/symbols.txt`.
- `symbol_resolve` — loads the built shared library and resolves every symbol in
  the manifest (registered only for shared-library builds).
- `deno_check` — runs `kwxgen check`; exits 77 (CTest `SKIP`) when `deno` is not
  installed.
- `parser_tests` — assert-based tests for the kwxgen parsers and the export
  symbol collector.

## Expected state

The suite is expected to be **RED** until the platform-guarded declarations are
removed from `include/kwx_constants.h`. `guard_lint` reports those as errors by
design; do not weaken the checks or add allowlist entries to hide them.
