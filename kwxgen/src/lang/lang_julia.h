/////////////////////////////////////////////////////////////////////////////
// Purpose:   Julia FFI code generator using ccall bindings
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

#include <optional>

class JuliaEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir) override;
    VerifyResult Verify(const ParsedFFI& parsed_ffi,
                        const std::filesystem::path& directory) override;
    [[nodiscard]] std::string_view Name() const override { return "julia"; }
    [[nodiscard]] CoverageInfo Coverage(const ParsedFFI& parsed_ffi) const override;
    UiDescriptor BuildUiDescriptor(const ParsedFFI& parsed_ffi) const override;
    std::vector<std::string>
        VerifyUiDescriptor(const UiDescriptor& descriptor,
                           const std::filesystem::path& generated_dir) const override;

private:
    static void GenerateEvents(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateKeys(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateConstants(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateClasses(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);

    // The generation sequence without the progress summary, so VerifyUiDescriptor can rebuild
    // the tree from the model the descriptor was built from.
    static void GenerateInto(const ParsedFFI& parsed_ffi, const std::filesystem::path& outDir);
    static void GenerateFreeFunctions(const ParsedFFI& parsed_ffi,
                                      const std::filesystem::path& outDir);
    static void GenerateModule(const std::filesystem::path& outDir, const std::string& libName);

    // Generated type preamble (abstract roots, wxEvent, _wx_wrap) and string runtime
    // (wxString lifecycle, _wx_take_cstring, _wx_take_wxstring).
    static void GenerateTypePreamble(const ParsedFFI& parsed_ffi,
                                     const std::filesystem::path& outDir);
    static void GenerateStringRuntime(const std::filesystem::path& outDir);

    // Idiomatic per-class Julia wrappers (structs + constructors + methods)
    static void GenerateIdiomaticStructs(const ParsedFFI& parsed_ffi,
                                         const std::filesystem::path& outDir);
    static void GenerateIdiomaticClasses(const ParsedFFI& parsed_ffi,
                                         const std::filesystem::path& outDir);
    static void EmitIdiomaticClassFile(std::ostream& output, const ClassInfo& class_info,
                                       const ParsedFFI& parsed_ffi);

    // Idiomatic wrappers for the top-level free functions (wxAboutBox, wxGetColourFromUserEx...).
    static void GenerateIdiomaticFreeFunctions(const ParsedFFI& parsed_ffi,
                                               const std::filesystem::path& outDir);
    // export lines for every binding the idiomatic layer defines.
    static void GenerateIdiomaticExports(const std::filesystem::path& outDir);

    // The profiled model BuildUiDescriptor was last called with.  VerifyUiDescriptor has no
    // model parameter and emit-ui calls the two methods back to back on the same emitter, so
    // the verification step regenerates the tree from this copy.
    mutable std::optional<ParsedFFI> m_ui_model;
};
