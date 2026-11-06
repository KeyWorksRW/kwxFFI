#!/usr/bin/env python3
"""Reproducer for kwxFFI issue #92.

Issue #92 — "src/kwx_constants_table_gen.cpp is being generated with CRLF"

    Line endings should always be LF, not CRLF.
    It should be run through clang-format as well so it is consistent with other
    formatting.

What this script proves, against a built ``kwxgen``:

A. Every generated file for every backend (typescript, go, fortran, julia, lua,
   rust) uses LF only -- no 0x0D byte appears in any generated file.
B. ``kwx_constants_table_gen.cpp`` is emitted exactly as the repository's
   ``.clang-format`` formats it: the freshly generated file is byte-identical to
   the committed ``src/kwx_constants_table_gen.cpp``, and (when clang-format is
   installed) ``clang-format --dry-run --Werror`` reports no violation.
C. The conditional-write comparison is byte-exact: a generated file that is
   turned into CRLF on disk is rewritten back to LF by the next generation run
   (the pre-fix writer compared text, saw the two as equal and left it CRLF).
D. Generation is idempotent: a second run into the same directory rewrites
   nothing (the file's mtime is unchanged).

Exit codes: 0 = fixed, 1 = still broken, 77 = skipped (no kwxgen found).
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

LANGS = ("typescript", "go", "fortran", "julia", "lua", "rust")
TABLE_NAME = "kwx_constants_table_gen.cpp"
REFERENCE_TABLE = Path("src") / TABLE_NAME

failures: list[str] = []
notes: list[str] = []


def expect(label: str, condition: bool, detail: str) -> bool:
    """Record one check; return True when it passed so callers can skip follow-ups."""
    if condition:
        print(f"PASS: {label} ({detail})")
        return True
    print(f"FAIL: {label} ({detail})")
    failures.append(f"{label}: {detail}")
    return False


def find_kwxgen(root: Path, explicit: str | None) -> Path | None:
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = (root / candidate).resolve()
        return candidate if candidate.is_file() else None

    candidates = [
        root / "bin" / "Release" / "kwxgen.exe",
        root / "kwxgen" / "bin" / "Release" / "kwxgen.exe",
        root / "build" / "tests" / "bin" / "Release" / "kwxgen.exe",
        root / "bin" / "Debug" / "kwxgen.exe",
        root / "kwxgen" / "bin" / "Debug" / "kwxgen.exe",
        root / "kwxgen" / "bin" / "kwxgen.exe",
        root / "bin" / "kwxgen",
    ]
    for candidate in candidates:
        if candidate.is_file():
            return candidate
    return None


def generate(kwxgen: Path, root: Path, lang: str, out_dir: Path, profile: str) -> tuple[bool, str]:
    command = [
        str(kwxgen),
        "generate",
        "--headers",
        str(root / "include"),
        "--defs",
        str(root / "src" / "kwx_defs.cpp"),
        "--lang",
        lang,
        "--profile",
        profile,
        "--out",
        str(out_dir),
    ]
    completed = subprocess.run(command, cwd=str(root), check=False, capture_output=True, text=True)
    if completed.returncode != 0:
        return False, (completed.stdout + completed.stderr).strip()
    return True, ""


def generated_files(out_dir: Path) -> list[Path]:
    return sorted(p for p in out_dir.rglob("*") if p.is_file())


def count_cr(path: Path) -> int:
    return path.read_bytes().count(b"\r")


def check_lf_only(kwxgen: Path, root: Path, work: Path, profile: str) -> None:
    print("\n== A. generated files use LF only ==")
    for lang in LANGS:
        out_dir = work / f"lf_{lang}"
        ok, output = generate(kwxgen, root, lang, out_dir, profile)
        if not expect(f"generate --lang {lang}", ok, output or "exit 0"):
            continue
        files = generated_files(out_dir)
        if not files:
            expect(f"--lang {lang} produced files", False, f"no files under {out_dir}")
            continue
        cr_files = [p for p in files if count_cr(p) > 0]
        cr_bytes = sum(count_cr(p) for p in cr_files)
        if cr_files:
            sample = ", ".join(p.relative_to(out_dir).as_posix() for p in cr_files[:3])
        else:
            sample = "-"
        expect(
            f"--lang {lang} output has no CR bytes",
            not cr_files,
            f"{len(files)} files, {len(cr_files)} with CR ({cr_bytes} CR bytes) [{sample}]",
        )


def check_clang_format(path: Path, root: Path) -> None:
    clang_format = shutil.which("clang-format")
    if not clang_format:
        notes.append("clang-format not on PATH -- formatting check skipped")
        print("SKIP: clang-format --dry-run --Werror (clang-format not on PATH)")
        return

    # The generated file lives in a temp directory, so point clang-format at the
    # repository's .clang-format explicitly instead of searching upward from the file.
    style_config = root / ".clang-format"
    if not style_config.is_file():
        notes.append(".clang-format not found -- formatting check skipped")
        print("SKIP: clang-format --dry-run --Werror (.clang-format not found)")
        return
    style = f"--style=file:{style_config}"

    command = [clang_format, "--dry-run", "--Werror", style, str(path)]
    completed = subprocess.run(command, check=False, capture_output=True, text=True)
    output = (completed.stdout + completed.stderr).strip()
    clean = completed.returncode == 0 and "error:" not in output
    expect(
        "generated C++ is clang-format clean",
        clean,
        "no violations" if clean else output.splitlines()[0] if output else f"exit {completed.returncode}",
    )


def check_table_format(kwxgen: Path, root: Path, work: Path, profile: str) -> None:
    print("\n== B. generated C++ matches the committed, clang-formatted file ==")
    out_dir = work / "table"
    ok, output = generate(kwxgen, root, "typescript", out_dir, profile)
    if not expect("generate --lang typescript (table)", ok, output or "exit 0"):
        return

    generated = out_dir / TABLE_NAME
    reference = root / REFERENCE_TABLE
    if not expect(f"{TABLE_NAME} was generated", generated.is_file(), str(generated)):
        return
    if not expect(f"{REFERENCE_TABLE.as_posix()} exists", reference.is_file(), str(reference)):
        return

    generated_bytes = generated.read_bytes()
    reference_bytes = reference.read_bytes()
    expect(
        "generated table is byte-identical to the committed table",
        generated_bytes == reference_bytes,
        f"generated {len(generated_bytes)} bytes, committed {len(reference_bytes)} bytes, "
        f"CR bytes {generated_bytes.count(b'\r')}",
    )
    check_clang_format(generated, root)


def check_conditional_write(kwxgen: Path, root: Path, work: Path, profile: str) -> None:
    print("\n== C/D. byte-exact comparison and idempotent generation ==")
    out_dir = work / "rewrite"
    ok, output = generate(kwxgen, root, "typescript", out_dir, profile)
    if not expect("generate (first run)", ok, output or "exit 0"):
        return

    table = out_dir / TABLE_NAME
    if not expect(f"{TABLE_NAME} was generated", table.is_file(), str(table)):
        return

    # D. second run into the same directory must not rewrite anything.
    before = table.stat().st_mtime_ns
    ok, output = generate(kwxgen, root, "typescript", out_dir, profile)
    if expect("generate (second run)", ok, output or "exit 0"):
        after = table.stat().st_mtime_ns
        expect(
            "unchanged content is not rewritten",
            before == after,
            f"mtime {'unchanged' if before == after else 'changed'}",
        )

    # C. a CRLF file left on disk must be rewritten as LF.
    crlf_bytes = table.read_bytes().replace(b"\r\n", b"\n").replace(b"\n", b"\r\n")
    table.write_bytes(crlf_bytes)
    expect(
        "CRLF copy written to disk",
        count_cr(table) > 0,
        f"{count_cr(table)} CR bytes",
    )

    ok, output = generate(kwxgen, root, "typescript", out_dir, profile)
    if expect("generate (after CRLF file appeared)", ok, output or "exit 0"):
        expect(
            "CRLF file is rewritten with LF",
            count_cr(table) == 0,
            f"{count_cr(table)} CR bytes",
        )
        reference = (root / REFERENCE_TABLE).read_bytes()
        expect(
            "rewritten file still matches the committed table",
            table.read_bytes() == reference,
            f"{len(table.read_bytes())} bytes",
        )


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description="Reproducer for kwxFFI issue #92")
    parser.add_argument(
        "--root",
        default=str(Path(__file__).resolve().parents[3]),
        help="repository root (default: the checkout this script lives in)",
    )
    parser.add_argument("--kwxgen", default=None, help="path to the kwxgen executable")
    parser.add_argument("--profile", default="full", help="generator profile (default: full)")
    args = parser.parse_args(argv)

    root = Path(args.root).resolve()
    if not (root / "include" / "kwx_events.h").is_file():
        print(f"SKIP: {root} does not look like a kwxFFI checkout")
        return 77

    kwxgen = find_kwxgen(root, args.kwxgen)
    if kwxgen is None:
        print(
            "SKIP: no kwxgen executable found (pass --kwxgen <path>); "
            "build it with `cmake --build build --config Release --target kwxgen`"
        )
        return 77
    print(f"kwxgen: {kwxgen}")
    print(f"root:   {root}")

    with tempfile.TemporaryDirectory(prefix="kwxissue92_") as temp_dir:
        work = Path(temp_dir)
        print(f"work:   {work}")
        check_lf_only(kwxgen, root, work, args.profile)
        check_table_format(kwxgen, root, work, args.profile)
        check_conditional_write(kwxgen, root, work, args.profile)

    for note in notes:
        print(f"NOTE: {note}")

    if failures:
        print(f"\n{len(failures)} check(s) FAILED -- issue #92 is not fixed:")
        for failure in failures:
            print(f"  - {failure}")
        return 1

    print("\nAll checks passed -- issue #92 is fixed.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
