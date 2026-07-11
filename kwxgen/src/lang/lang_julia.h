/////////////////////////////////////////////////////////////////////////////
// Purpose:   Julia FFI code generator using ccall bindings
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

class JuliaEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir) override;
    VerifyResult Verify(const ParsedFFI& parsed_ffi,
                        const std::filesystem::path& directory) override;
    [[nodiscard]] std::string_view Name() const override { return "julia"; }

private:
    static void GenerateEvents(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateKeys(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateConstants(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateClasses(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateFreeFunctions(const ParsedFFI& parsed_ffi,
                                      const std::filesystem::path& outDir);
    static void GenerateModule(const std::filesystem::path& outDir, const std::string& libName);

    // Idiomatic per-class Julia wrappers (structs + constructors + methods)
    static void GenerateIdiomaticClasses(const ParsedFFI& parsed_ffi,
                                         const std::filesystem::path& outDir);
    static void EmitIdiomaticClassFile(std::ostream& output, const ClassInfo& class_info,
                                       const ParsedFFI& parsed_ffi);
};
