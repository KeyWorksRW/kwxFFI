////////////////////////////////////////////////////
// Purpose:   TypeScript FFI binding generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
////////////////////////////////////////////////////
// CR: [10-19-2026]

#pragma once

#include "../emitter.h"

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <unordered_set>

class TypeScriptEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& ffi, const std::filesystem::path& out_dir) override;
    // Intentionally unsupported: this emitter has no independent Verify implementation.
    // Real verification of generated TypeScript is done by VerifyGeneratedFiles() /
    // the `kwxgen verify` command.  Any generic caller receives a guaranteed failure.
    [[nodiscard]] VerifyResult Verify(const ParsedFFI& ffi,
                                      const std::filesystem::path& out_dir) override;
    [[nodiscard]] std::string_view Name() const override { return "typescript"; }

private:
    // Emits kwx_ffi_gen.ts — the dlopen call with all C symbol definitions.
    static void GenerateFfi(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_constants_gen.ts — table-backed events, keys, and constants.
    static void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_constants_table_gen.cpp — the lazily-filled integer constant table.
    static void GenerateConstantsTableC(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_free_functions_gen.ts — free-function TypeScript wrappers.
    static void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits wx{Class}_gen.ts for each class that has methods.
    static void GenerateClassFiles(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_gen.ts — barrel re-export of all generated modules.
    static void GenerateIndex(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits the body of a single TypeScript class wrapper file.
    static void EmitClassFile(std::ostream& output, const ClassInfo& cls, const ParsedFFI& ffi,
                              const std::unordered_map<std::string, const ClassInfo*>& class_index,
                              const std::unordered_set<std::string>& wrapped_classes);

    // Emits kwx_helpers_gen.ts — wxString conversion utilities for generated code.
    static void GenerateHelpers(const ParsedFFI& ffi, const std::filesystem::path& out_dir);
};
