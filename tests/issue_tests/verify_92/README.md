# Issue 92 — generated files must use LF, and the generated C++ must be clang-formatted

Issue #92 reported that `src/kwx_constants_table_gen.cpp` is generated with CRLF,
and asked that generated C++ also be run through clang-format so it is consistent
with the rest of the repository.

## Root cause

`ConditionalFileWriter` (`kwxgen/src/file_writer.cpp`) opened both the comparison
stream and the output stream in text mode. On Windows that means every `\n` the
emitter buffered was written as `\r\n`. It also meant the "did the content
change?" comparison normalized CRLF back to LF, so a CRLF file already on disk
always compared equal to the buffered LF content and was never rewritten — the
defect was self-perpetuating.

The formatting half of the report is a consequence of `GenerateConstantsTableC`
emitting text that was not in the layout `.clang-format` produces: the
declarations inside `extern "C" { ... }` started at column 0 and the
`std::call_once` lambda was emitted on a single line. Reformatting that text with
the repository's `.clang-format` reproduces the committed
`src/kwx_constants_table_gen.cpp` exactly, so the emitter now emits that layout
directly.

## Fix

- `kwxgen/src/file_writer.cpp` / `file_writer.h` — the existing file is read and
  the new file is written with `std::ios::binary`. The comparison is byte-exact
  and no newline translation can happen, so generated files always use LF on
  every platform. A CRLF file left behind by an earlier build is now detected as
  different and rewritten as LF.
- `kwxgen/src/lang/lang_typescript.cpp`, `TypeScriptEmitter::GenerateConstantsTableC`
  — the table is emitted in the clang-format layout (everything inside
  `extern "C" { ... }` indented four spaces, the `std::call_once` lambda split
  the way clang-format splits it). The emitted content — declarations, order,
  names, counts — is unchanged.
- `kwxgen/src/verify.cpp` — comment only; `ReadFileContents` still reads in text
  mode so a reference checkout whose files use CRLF is not reported as a
  content mismatch, but the old justification no longer applied.

The emitter deliberately does **not** shell out to `clang-format`: generation has
to be hermetic and byte-reproducible (`kwxgen verify`, the export-snapshot
digest, and the byte-identical regeneration assertion below all depend on that),
and an installed formatter's version would silently change the output. The
reproducer instead asserts that the output *is* what clang-format produces.

## What the reproducer proves

`repro.py` runs only against generated output; it never writes into the
repository or into a downstream language repository.

### A. Line endings (all backends)

For `typescript`, `go`, `fortran`, `julia`, `lua` and `rust` it runs

```
kwxgen generate --headers include --defs src/kwx_defs.cpp \
                --lang <lang> --profile full --out <temp>
```

and asserts that no generated file contains a single `0x0D` byte.

### B. clang-format consistency

For `--lang typescript` it asserts that the generated
`kwx_constants_table_gen.cpp` is **byte-identical** to the committed
`src/kwx_constants_table_gen.cpp`, and — when `clang-format` is on `PATH` — that
`clang-format --dry-run --Werror --style=file:<repo>/.clang-format` reports no
violation. The style file is passed explicitly because the generated file lives
in a temp directory.

### C. Byte-exact comparison

It generates the table, converts the generated file on disk to CRLF, generates
again, and asserts the file is back to LF and still byte-identical to the
committed table. This is the check that fails on the pre-fix writer, which
compared text and therefore considered the CRLF file unchanged.

### D. Idempotence

A second generation into the same directory must not rewrite the file (mtime
unchanged), so the conditional-write optimisation still works.

## Pre-fix / post-fix evidence

| check | pre-fix kwxgen | fixed kwxgen |
|---|---|---|
| CR bytes in `--lang typescript` output (665 files) | 103,091 across all 665 files | 0 |
| CR bytes in `--lang go` / `fortran` / `julia` / `lua` / `rust` | 101,871 / 79,366 / 96,839 / 65,032 / 101,089 | 0 each |
| generated table vs committed table | 268,199 vs 325,753 bytes, 7,209 CR bytes | 325,753 vs 325,753 bytes, byte-identical |
| `clang-format --dry-run --Werror` on generated table | violation at 6:2 | no violations |
| CRLF file on disk rewritten to LF | no (still 7,209 CR bytes) | yes (0 CR bytes) |

Exit codes: `0` fixed, `1` still broken, `77` skipped (no `kwxgen`, or the
`.clang-format` / `clang-format` binary is unavailable for the formatting check).

## Usage

```
python tests/issue_tests/verify_92/repro.py [--root <repo>] \
                                           [--kwxgen <exe>] \
                                           [--profile full]
```

`--kwxgen` defaults to the first executable found among `bin/Release`,
`kwxgen/bin/Release`, `build/tests/bin/Release`, and the Debug variants.
Build one with `cmake --build build --config Release --target kwxgen`.

## Notes

- No exported symbol, header, generator input or profile changes; the export
  digest in `tests/expected/symbols.sha256` is untouched and `export_snapshot`
  still matches it (11,574 symbols).
- `src/kwx_constants_table_gen.cpp` is compiled into the DLL and was already in
  the desired LF, clang-formatted state; the fix is that regeneration now
  reproduces it instead of overwriting it with CRLF, unformatted text.
- Downstream repositories are not touched; all generation in the reproducer goes
  to a temporary directory.
