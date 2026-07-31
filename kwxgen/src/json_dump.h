/////////////////////////////////////////////////////////////////////////////
// Purpose:   Dump the parsed FFI model as JSON output
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

// The `parse` command serializes the full ParsedFFI model as JSON, serving two purposes:
//
// 1. Debugging / inspection. Running `kwxgen parse --headers ... --defs ...` gives a
//    human-readable view of exactly what the parsers extracted — without going through a
//    full code-gen cycle. Useful when developing new parsers or tracking down missing entries.
//
// 2. Machine-readable interchange. The JSON output is a complete snapshot of the FFI
//    surface: classes, methods, free functions, parameters, return types, events, keys,
//    constants, parent map, and mixin map. Any external tool can consume it without linking
//    to kwxgen or re-parsing the headers.
//
//    The primary downstream consumer is a Lua auto-completion VSCode extension. A VSCode
//    extension is written in TypeScript/JavaScript, so JSON is its native format. The
//    extension reads the JSON file produced during the kwxFFI build and uses it to drive
//    auto-completion: class names, method signatures, parameter names and types,
//    constructor/destructor flags, inheritance (parent_map), and mixed-in methods
//    (mixin_map). This is cleaner than parsing generated Lua bindings (fragile, lossy)
//    and requires no runtime linkage to the kwxgen library.

#pragma once

#include "model.h"

#include <ostream>
#include <string>

// Serialize ParsedFFI to prettified JSON on the given output stream.
void DumpJson(const ParsedFFI& parsed_ffi, std::ostream& output);

// Serialize ParsedFFI to prettified JSON and write to a file. Returns true on success.
[[nodiscard]] bool DumpJsonToFile(const ParsedFFI& parsed_ffi, const std::string& file_path);
