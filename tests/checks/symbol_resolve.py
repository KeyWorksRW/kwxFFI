#!/usr/bin/env python3
"""Resolve every symbol in the export snapshot against a built shared library.

The export manifest is platform-agnostic by design, so the only way to prove a
manifest entry actually exists in a binary is to look it up. `ctypes.CDLL`
works for .dll, .so, and .dylib alike.

Exit codes: 0 when every symbol resolves, 1 when any symbol or the library load
fails.
"""

from __future__ import annotations

import argparse
import ctypes
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_ROOT = SCRIPT_DIR.parent.parent

MAX_REPORTED_MISSING = 50


def parse_arguments(argv: list[str] | None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Resolve the export snapshot against a built shared library."
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
        "--manifest",
        type=Path,
        default=None,
        help="Snapshot to resolve (default: <root>/tests/expected/symbols.txt)",
    )
    return parser.parse_args(argv)


def resolve_path(root: Path, path: Path) -> Path:
    if not path.is_absolute():
        path = root / path
    return path.resolve()


def read_manifest(path: Path) -> list[str]:
    # splitlines() handles CRLF snapshots; duplicates are harmless here.
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    return [line.strip() for line in lines if line.strip()]


def main(argv: list[str] | None = None) -> int:
    options = parse_arguments(argv)
    root = options.root.resolve()
    library_path = resolve_path(root, Path(options.library))

    if options.manifest is None:
        manifest_path = root / "tests" / "expected" / "symbols.txt"
    else:
        manifest_path = resolve_path(root, options.manifest)

    if not library_path.is_file():
        print(f"error: shared library not found at {library_path}", file=sys.stderr)
        return 1
    if not manifest_path.is_file():
        print(f"error: export snapshot not found at {manifest_path}", file=sys.stderr)
        return 1

    symbols = read_manifest(manifest_path)
    if not symbols:
        print(f"error: export snapshot {manifest_path} is empty", file=sys.stderr)
        return 1

    print(f"Library:  {library_path}")
    print(f"Manifest: {manifest_path} ({len(symbols)} symbols)")

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
