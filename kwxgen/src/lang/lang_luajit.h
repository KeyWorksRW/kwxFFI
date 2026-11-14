/////////////////////////////////////////////////////////////////////////////
// Purpose:   LuaJIT FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

#include <optional>

class LuaJITEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir) override;
    VerifyResult Verify(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir) override;
    [[nodiscard]] std::string_view Name() const override { return "lua"; }
    [[nodiscard]] CoverageInfo Coverage(const ParsedFFI& ffi_data) const override;
    UiDescriptor BuildUiDescriptor(const ParsedFFI& parsed_ffi) const override;
    std::vector<std::string>
        VerifyUiDescriptor(const UiDescriptor& descriptor,
                           const std::filesystem::path& generated_dir) const override;

private:
    // The generation sequence without the progress summary, so VerifyUiDescriptor can rebuild the
    // tree from the model the descriptor was built from.
    static void GenerateInto(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir);

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
    static void GenerateIdiomaticFreeFunctions(const ParsedFFI& ffi_data,
                                               const std::filesystem::path& out_dir);
    static void EmitIdiomaticClassFile(std::ostream& output, const ClassInfo& class_info,
                                       const ParsedFFI& ffi_data);

    // The profiled model BuildUiDescriptor was last called with.  VerifyUiDescriptor has no model
    // parameter and emit-ui calls the two methods back to back on the same emitter, so the
    // verification pass regenerates the tree from this copy rather than judging an empty
    // directory.
    mutable std::optional<ParsedFFI> m_ui_model;
};
