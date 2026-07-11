/////////////////////////////////////////////////////////////////////////////
// Purpose:   Go/CGo FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

#include <unordered_set>

class GoEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& parsed_ffi, const std::filesystem::path& out_dir) override;
    VerifyResult Verify(const ParsedFFI& parsed_ffi,
                        const std::filesystem::path& directory) override;
    std::string_view Name() const override { return "go"; }

private:
    static void GenerateGlueFile(const ParsedFFI& parsed_ffi, const std::filesystem::path& out_dir);
    static void GenerateHelpers(const std::filesystem::path& out_dir);
    static void GenerateConstants(const ParsedFFI& parsed_ffi,
                                  const std::filesystem::path& out_dir);
    static void GenerateEvents(const ParsedFFI& parsed_ffi, const std::filesystem::path& out_dir);
    static void GenerateKeys(const ParsedFFI& parsed_ffi, const std::filesystem::path& out_dir);
    static size_t GenerateClassFiles(const ParsedFFI& parsed_ffi,
                                     const std::filesystem::path& out_dir);
    static void GenerateFreeFunctions(const ParsedFFI& parsed_ffi,
                                      const std::filesystem::path& out_dir);

    // Emit a single class file: classname_gen.go
    static void EmitClassFile(std::ostream& output, const ClassInfo& class_info,
                              const ParsedFFI& /*parsed_ffi*/,
                              const std::unordered_set<std::string>& wrapped_classes);
};
