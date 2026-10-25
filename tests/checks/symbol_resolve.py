#!/usr/bin/env python3
"""Resolve the generated export manifest against a built shared library.

The export manifest is platform-agnostic by design, so the only way to prove a
manifest entry actually exists in a binary is to look it up. `ctypes.CDLL`
works for .dll, .so, and .dylib alike.

Unless `--manifest` names an explicit file, the manifest is generated with
`kwxgen exports` into a temporary directory, so there is no committed list to
keep in sync.

Exit codes: 0 when every symbol resolves, 1 when any symbol or the library load
fails.
"""

from __future__ import annotations

import argparse
import ctypes
import sys
import tempfile
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from _exports import DEF_FILE_NAME, generate, read_def_symbols

DEFAULT_ROOT = SCRIPT_DIR.parent.parent

MAX_REPORTED_MISSING = 50


def parse_arguments(argv: list[str] | None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Resolve the generated export manifest against a built shared library."
    )
    parser.add_argument(
        "--root",
        type=Path,
        default=DEFAULT_ROOT,
        help="Repository root (default: the parent of this script's directory)",
    )
    parser.add_argument(
        "--library",
        required=True,
        help="Path to the built shared library (.dll, .so, or .dylib)",
    )
    parser.add_argument(
        "--kwxgen",
        default=None,
        help="kwxgen executable used to generate the manifest (required without --manifest)",
    )
    parser.add_argument(
        "--manifest",
        type=Path,
        default=None,
        help="Explicit manifest to resolve (default: generate one with kwxgen exports)",
    )
    return parser.parse_args(argv)


def resolve_path(root: Path, path: Path) -> Path:
    if not path.is_absolute():
        path = root / path
    return path.resolve()


def read_manifest(path: Path) -> list[str]:
    # splitlines() handles CRLF manifests; duplicates are harmless here.
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    return [line.strip() for line in lines if line.strip()]


def generate_manifest(kwxgen: Path, root: Path) -> list[str] | None:
    """Generate the export manifest with kwxgen; return None on failure."""
    with tempfile.TemporaryDirectory(prefix="kwxffi_resolve_") as temp_dir_name:
        out_dir = Path(temp_dir_name)
        return_code = generate(kwxgen, root, out_dir)
        if return_code != 0:
            print(f"error: kwxgen exports failed with exit {return_code}", file=sys.stderr)
            return None
        def_path = out_dir / DEF_FILE_NAME
        if not def_path.is_file():
            print(f"error: {DEF_FILE_NAME} was not generated", file=sys.stderr)
            return None
        return read_def_symbols(def_path)


def main(argv: list[str] | None = None) -> int:
    options = parse_arguments(argv)
    root = options.root.resolve()
    library_path = resolve_path(root, Path(options.library))

    if options.manifest is not None:
        manifest_path = resolve_path(root, options.manifest)
        if not manifest_path.is_file():
            print(f"error: export manifest not found at {manifest_path}", file=sys.stderr)
            return 1
        manifest_label = str(manifest_path)
        symbols = read_manifest(manifest_path)
    else:
        if not options.kwxgen:
            print(
                "error: --kwxgen is required when --manifest is not given",
                file=sys.stderr,
            )
            return 1
        kwxgen = resolve_path(root, Path(options.kwxgen))
        if not kwxgen.is_file():
            print(f"error: kwxgen executable not found at {kwxgen}", file=sys.stderr)
            return 1
        generated_symbols = generate_manifest(kwxgen, root)
        if generated_symbols is None:
            return 1
        manifest_label = f"kwxgen exports ({kwxgen})"
        symbols = generated_symbols

    if not library_path.is_file():
        print(f"error: shared library not found at {library_path}", file=sys.stderr)
        return 1
    if not symbols:
        print(f"error: export manifest {manifest_label} is empty", file=sys.stderr)
        return 1

    print(f"Library:  {library_path}")
    print(f"Manifest: {manifest_label} ({len(symbols)} symbols)")

    try:
        library = ctypes.CDLL(str(library_path))
    except OSError as load_error:
        print(f"error: could not load {library_path}: {load_error}", file=sys.stderr)
        return 1

    missing: list[str] = []
    for name in symbols:
        try:
            getattr(library, name)
        except AttributeError:
            missing.append(name)

    if not missing:
        print(f"All {len(symbols)} symbols resolved.")
        return 0

    for name in missing[:MAX_REPORTED_MISSING]:
        print(f"  missing: {name}")
    if len(missing) > MAX_REPORTED_MISSING:
        print(f"  ... {len(missing) - MAX_REPORTED_MISSING} more")
    print(f"{len(missing)} of {len(symbols)} symbols unresolved")
    return 1


if __name__ == "__main__":
    sys.exit(main())
