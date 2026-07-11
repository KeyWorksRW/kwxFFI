/////////////////////////////////////////////////////////////////////////////
// Purpose:   LuaJIT FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

class LuaJITEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir) override;
    VerifyResult Verify(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir) override;
    [[nodiscard]] std::string_view Name() const override { return "lua"; }

private:
    // Raw FFI layer: ffi.cdef declarations for all C functions
    static void GenerateEvents(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir);
    static void GenerateKeys(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir);
    static void GenerateConstants(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir);
    static void GenerateClasses(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir);
    static void GenerateFreeFunctions(const ParsedFFI& ffi_data,
                                      const std::filesystem::path& out_dir);
    static void GenerateInit(const std::filesystem::path& out_dir, const std::string& lib_name);

    // Idiomatic layer: per-class Lua modules with metatables and method wrappers
    static void GenerateHelpers(const std::filesystem::path& out_dir);
    static void GenerateIdiomaticClasses(const ParsedFFI& ffi_data,
                                         const std::filesystem::path& out_dir);
    static void EmitIdiomaticClassFile(std::ostream& output, const ClassInfo& class_info,
                                       const ParsedFFI& ffi_data);
};
