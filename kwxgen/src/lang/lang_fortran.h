/////////////////////////////////////////////////////////////////////////////
// Purpose:   Fortran ISO_C_BINDING FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

class FortranEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& ffi_data, const std::filesystem::path& outDir) override;
    VerifyResult Verify(const ParsedFFI& ffi_data, const std::filesystem::path& out_dir) override;
    [[nodiscard]] std::string_view Name() const override { return "fortran"; }

private:
    // kwxffi_gen.f90 — raw C interface declarations
    static void GenerateEvents(const std::vector<EventDecl>& events, std::ostream& output);
    static void GenerateKeys(const std::vector<KeyDecl>& keys, std::ostream& output);
    static void GenerateConstants(const std::vector<ConstantDecl>& constants, std::ostream& output);
    static void GenerateClasses(const ParsedFFI& ffi_data, std::ostream& output);
    static void GenerateFreeFunctions(const ParsedFFI& ffi_data, std::ostream& output);

    // Idiomatic Fortran wrapper modules
    static void GenerateTypes(const ParsedFFI& ffi_data, const std::filesystem::path& outDir);
    static void GenerateStringModule(const std::filesystem::path& outDir);
    static void GenerateConstantsModule(const ParsedFFI& ffi_data,
                                        const std::filesystem::path& outDir);
    static void GenerateWindowModule(const ParsedFFI& ffi_data,
                                     const std::filesystem::path& outDir);
    static void GenerateFrameModule(const ParsedFFI& ffi_data, const std::filesystem::path& outDir);
    static void GenerateControlsModule(const ParsedFFI& ffi_data,
                                       const std::filesystem::path& outDir);
    static void GenerateMenusModule(const ParsedFFI& ffi_data, const std::filesystem::path& outDir);
    static void GenerateSizersModule(const ParsedFFI& ffi_data,
                                     const std::filesystem::path& outDir);
    static void GenerateEventsModule(const ParsedFFI& ffi_data,
                                     const std::filesystem::path& outDir);
    static void GenerateDialogsModule(const ParsedFFI& ffi_data,
                                      const std::filesystem::path& outDir);
};
