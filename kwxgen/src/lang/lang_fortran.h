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
    [[nodiscard]] CoverageInfo Coverage(const ParsedFFI& ffi_data) const override;

    // Describe how this backend expresses the UI idioms (emit-ui), built from the same
    // naming helpers and wrapper builder Generate() uses.
    UiDescriptor BuildUiDescriptor(const ParsedFFI& parsed_ffi) const override;

    // Compare every descriptor symbol against the declaration the generator wrote into
    // generated_dir and report arity disagreements as "MISMATCH <class>.<role> <symbol>".
    std::vector<std::string>
        VerifyUiDescriptor(const UiDescriptor& descriptor,
                           const std::filesystem::path& generated_dir) const override;

private:
    // kwxffi_gen.f90 — raw C interface declarations
    static void GenerateEvents(const std::vector<EventDecl>& events, std::ostream& output);
    static void GenerateKeys(const std::vector<KeyDecl>& keys, std::ostream& output);
    static void GenerateConstants(const ParsedFFI& ffi_data, std::ostream& output);
    static void GenerateClasses(const ParsedFFI& ffi_data, std::ostream& output);
    static void GenerateFreeFunctions(const ParsedFFI& ffi_data, std::ostream& output);

    // Idiomatic Fortran wrapper modules
    static void GenerateTypeTree(const ParsedFFI& ffi_data, const std::filesystem::path& outDir);
    static void GenerateStringModule(const std::filesystem::path& outDir);
    static void GenerateEventsModule(const ParsedFFI& ffi_data,
                                     const std::filesystem::path& outDir);

    // One generated module per class that has at least one valid method.
    static void GenerateClassModules(const ParsedFFI& ffi_data,
                                     const std::filesystem::path& outDir);
    // wx_free_functions.f90 — typed wrappers for every valid free function.
    static void GenerateFreeFunctionModule(const ParsedFFI& ffi_data,
                                           const std::filesystem::path& outDir);
    static void EmitClassModule(std::ostream& output, const ClassInfo& class_info,
                                const ParsedFFI& ffi_data);
};
