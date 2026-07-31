////////////////////////////////////////////////////
// Purpose:   Deno TypeScript FFI binding generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

class TypeScriptEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& ffi, const std::filesystem::path& out_dir) override;
    [[nodiscard]] VerifyResult Verify(const ParsedFFI& ffi,
                                      const std::filesystem::path& out_dir) override;
    [[nodiscard]] std::string_view Name() const override { return "typescript"; }

private:
    // Emits kwx_ffi_gen.ts — the Deno.dlopen call with all C symbol definitions.
    static void GenerateFfi(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_constants_gen.ts — eagerly-evaluated events, keys, and constants.
    static void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_free_functions_gen.ts — free-function TypeScript wrappers.
    static void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits one TypeScript class file per parsed class, plus the master index.
    static void GenerateClassFiles(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits kwx_gen.ts — barrel re-export of all generated modules.
    static void GenerateIndex(const ParsedFFI& ffi, const std::filesystem::path& out_dir);

    // Emits the body of a single TypeScript class wrapper file.
    static void EmitClassFile(std::ostream& output, const ClassInfo& cls, const ParsedFFI& ffi);

    // Emits kwx_helpers_gen.ts — wxString conversion utilities for generated code.
    static void GenerateHelpers(const std::filesystem::path& out_dir);
};
