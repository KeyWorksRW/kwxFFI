/////////////////////////////////////////////////////////////////////////////
// Purpose:   Generate agent-oriented markdown documentation for all kwxFFI
//            languages from the parsed FFI model data.
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "md_files_gen.h"

#include "file_writer.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <print>
#include <string>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

// ---------------------------------------------------------------------------
// Language metadata
// ---------------------------------------------------------------------------

struct LangMeta
{
    std::string_view key;        // directory name + file prefix
    std::string_view full_name;  // "Fortran (kwxFFI)", "TypeScript (Deno FFI)", etc.
};

static constexpr std::array<LangMeta, 5> kwx_Languages = { {
    { .key = "fortran", .full_name = "Fortran (kwxFFI)" },
    { .key = "go", .full_name = "Go (CGo FFI)" },
    { .key = "julia", .full_name = "Julia (ccall FFI)" },
    { .key = "lua", .full_name = "LuaJIT (FFI)" },
    // { "perl",       "Perl (FFI::Raw)"        },
    { .key = "typescript", .full_name = "TypeScript (Deno FFI)" },
} };

// ---------------------------------------------------------------------------
// Type simplification helpers
// ---------------------------------------------------------------------------

// Strip the leading "wx" prefix if present (e.g. "wxButton" → "Button").
// Used only for display purposes where the wx prefix is implicit.
static std::string_view StripWxPrefix(std::string_view name)
{
    if (name.starts_with("wx") && name.size() > 2)
    {
        return name.substr(2);
    }
    return name;
}

// Simplify a C FFI parameter type to an agent-friendly form.
// Returns empty string for TSelf (should be skipped).
static std::string SimplifyParamType(const Param& param)
{
    // TSelf — implicit receiver, skip
    if (param.macro_name == "TSelf")
    {
        return {};
    }

    // Macro-wrapped types
    if (param.macro_name == "TClass")
    {
        return param.macro_arg;  // "wxWindow", "wxButton", etc.
    }
    if (param.macro_name == "TPoint")
    {
        return "wxPoint";
    }
    if (param.macro_name == "TSize")
    {
        return "wxSize";
    }
    if (param.macro_name == "TRect")
    {
        return "wxRect";
    }
    if (param.macro_name == "TString" || param.raw_type == "TString")
    {
        return "str";
    }

    // Booleans
    if (param.macro_name == "TBool" || param.macro_name == "TBoolInt" ||
        param.raw_type == "TBool" || param.raw_type == "TBoolInt")
    {
        return "bool";
    }

    // Array/pointer types
    if (param.macro_name.starts_with("TArray") || param.raw_type.contains('*'))
    {
        return "pointer";
    }

    // Numeric types
    if (param.raw_type == "int" || param.raw_type == "long" || param.raw_type == "unsigned" ||
        param.raw_type == "size_t" || param.raw_type == "int32_t" || param.raw_type == "uint32_t")
    {
        return "int";
    }
    if (param.raw_type == "float" || param.raw_type == "double")
    {
        return "float";
    }

    // void
    if (param.raw_type == "void")
    {
        return "void";
    }

    // Fallback — use raw type as-is
    return param.raw_type;
}

// Simplify a return type to agent-friendly form.
// Returns empty string for void ( → void should be omitted).
static std::string SimplifyReturnType(const FunctionDecl& func_decl)
{
    // Macro-wrapped returns
    if (func_decl.return_macro == "TClass")
    {
        return func_decl.return_arg;
    }
    if (func_decl.return_macro == "TPoint")
    {
        return "wxPoint";
    }
    if (func_decl.return_macro == "TSize")
    {
        return "wxSize";
    }
    if (func_decl.return_macro == "TRect")
    {
        return "wxRect";
    }
    if (func_decl.return_macro == "TString" || func_decl.return_type == "TString")
    {
        return "str";
    }

    // Booleans
    if (func_decl.return_macro == "TBool" || func_decl.return_macro == "TBoolInt" ||
        func_decl.return_type == "TBool" || func_decl.return_type == "TBoolInt")
    {
        return "bool";
    }

    // void
    if (func_decl.return_type == "void")
    {
        return {};
    }

    // Pointers
    if (func_decl.return_type.contains('*'))
    {
        return "pointer";
    }

    // Numerics
    if (func_decl.return_type == "int" || func_decl.return_type == "long" ||
        func_decl.return_type == "unsigned" || func_decl.return_type == "size_t" ||
        func_decl.return_type == "int32_t" || func_decl.return_type == "uint32_t")
    {
        return "int";
    }
    if (func_decl.return_type == "float" || func_decl.return_type == "double")
    {
        return "float";
    }

    return func_decl.return_type;
}

// ---------------------------------------------------------------------------
// Format a parameter list for a method/constructor signature.
//   "name: type" pairs, TSelf skipped, comma-separated.
// ---------------------------------------------------------------------------

static std::string FormatParamList(const std::vector<Param>& params)
{
    std::string result;
    bool is_first = true;
    for (const auto& param: params)
    {
        const std::string simplified = SimplifyParamType(param);
        if (simplified.empty())
        {
            continue;  // TSelf — skip
        }

        if (!is_first)
        {
            result += ", ";
        }
        is_first = false;

        if (!param.param_name.empty())
        {
            result += param.param_name;
            result += ": ";
        }
        result += simplified;
    }
    return result;
}

// ---------------------------------------------------------------------------
// Write a single per-class markdown file.
// ---------------------------------------------------------------------------

static void WriteClassMarkdown(const ClassInfo& class_info, const LangMeta& lang,
                               const fs::path& out_dir)
{
    const fs::path file_path = out_dir / (std::string(lang.key) + "-" + class_info.name + ".md");

    ConditionalFileWriter out(file_path);
    if (!out.is_open())
    {
        return;
    }

    // Section 1 — File header
    out << "<!-- Code generated by kwxgen. DO NOT EDIT. -->\n";
    out << "# " << class_info.name << " (" << lang.key << ")\n\n";
    out << "**Language:** " << lang.full_name << "\n";
    out << "**C++ equivalent:** " << class_info.name << "\n";
    out << "**Parent:** " << (class_info.parent.empty() ? "none" : class_info.parent) << "\n";
    out << "**Window-derived:** " << (class_info.is_window_derived ? "yes" : "no") << "\n";

    // Section 2 — Constructor
    out << "\n## Constructor\n\n";
    bool has_constructor = false;
    for (const auto& method: class_info.methods)
    {
        if (!method.is_constructor)
        {
            continue;
        }
        has_constructor = true;

        const std::string params = FormatParamList(method.params);
        const std::string ret = SimplifyReturnType(method);
        out << method.method_name << "(" << params << ")";
        if (!ret.empty())
        {
            out << " → " << ret;
        }
        // For constructors returning TClass, append " | null" (FFI can fail)
        if (method.return_macro == "TClass")
        {
            out << " | null";
        }
        out << "\n";
    }

    if (!has_constructor)
    {
        out << "This class has no constructor — it is constructed as a parent object "
               "or via a free function.\n";
    }

    // Section 3 — Methods (deduplicated by name)
    out << "\n## Methods\n\n";
    std::unordered_set<std::string> seen_methods;

    for (const auto& method: class_info.methods)
    {
        // Skip constructors (already in Section 2) and TClassDef sentinel methods
        if (method.is_constructor)
        {
            continue;
        }

        // Deduplicate: same method name → emit once
        if (!seen_methods.insert(method.method_name).second)
        {
            continue;
        }

        const std::string params = FormatParamList(method.params);
        const std::string ret = SimplifyReturnType(method);

        out << method.method_name << "(" << params << ")";
        if (!ret.empty())
        {
            out << " → " << ret;
        }
        out << "\n";
    }

    // Section 4 — Events (per-class mapping not available from the flat model)
    out << "\n## Events\n\n";
    out << "Per-class event mapping is not available from the current model — see events.md for "
           "the full list.\n";

    // Section 5 — Constants (per-class mapping not available from the flat model)
    out << "\n## Constants\n\n";
    out << "Per-class constant mapping is not available from the current model — see constants.md "
           "for the full list.\n";
}

// ---------------------------------------------------------------------------
// Write constants.md — every constant with its simplified type.
// ---------------------------------------------------------------------------

static void WriteConstantsMarkdown(const ParsedFFI& ffi, const LangMeta& lang,
                                   const fs::path& out_dir)
{
    const fs::path file_path = out_dir / (std::string(lang.key) + "-constants.md");
    ConditionalFileWriter out(file_path);
    if (!out.is_open())
    {
        return;
    }

    out << "<!-- Code generated by kwxgen. DO NOT EDIT. -->\n";
    out << "# Constants (" << lang.key << ")\n\n";

    if (ffi.constants.empty())
    {
        out << "None.\n";
        return;
    }

    // Sort constants by name for stable output
    std::vector<ConstantDecl> sorted = ffi.constants;
    std::ranges::sort(sorted, {}, &ConstantDecl::constant_name);

    for (const auto& constant: sorted)
    {
        // Simplify the type
        std::string type_str;
        if (constant.return_type.contains('*'))
        {
            type_str = "pointer";
        }
        else if (constant.return_type == "int" || constant.return_type == "long" ||
                 constant.return_type == "unsigned" || constant.return_type == "size_t")
        {
            type_str = "int";
        }
        else if (constant.return_type.contains("wxString") ||
                 constant.return_type.contains("wxColour"))
        {
            type_str = "str";
        }
        else if (constant.return_type == "float" || constant.return_type == "double")
        {
            type_str = "float";
        }
        else
        {
            type_str = "int";  // Default for unknown types
        }

        out << "wx" << StripWxPrefix(constant.constant_name) << " → " << type_str << "\n";
    }
}

// ---------------------------------------------------------------------------
// Write events.md — every event macro.
// ---------------------------------------------------------------------------

static void WriteEventsMarkdown(const ParsedFFI& ffi, const LangMeta& lang, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / (std::string(lang.key) + "-events.md");
    ConditionalFileWriter out(file_path);
    if (!out.is_open())
    {
        return;
    }

    out << "<!-- Code generated by kwxgen. DO NOT EDIT. -->\n";
    out << "# Events (" << lang.key << ")\n\n";

    if (ffi.events.empty())
    {
        out << "None.\n";
        return;
    }

    // Sort events by name for stable output
    std::vector<EventDecl> sorted = ffi.events;
    std::ranges::sort(sorted, {}, &EventDecl::event_name);

    for (const auto& event: sorted)
    {
        out << event.event_name << "(id, handler)\n";
    }
}

// ---------------------------------------------------------------------------
// Write free_functions.md — all free functions with simplified signatures.
// ---------------------------------------------------------------------------

static void WriteFreeFunctionsMarkdown(const ParsedFFI& ffi, const LangMeta& lang,
                                       const fs::path& out_dir)
{
    const fs::path file_path = out_dir / (std::string(lang.key) + "-free_functions.md");
    ConditionalFileWriter out(file_path);
    if (!out.is_open())
    {
        return;
    }

    out << "<!-- Code generated by kwxgen. DO NOT EDIT. -->\n";
    out << "# Free Functions (" << lang.key << ")\n\n";

    if (ffi.free_functions.empty())
    {
        out << "None.\n";
        return;
    }

    // Deduplicate free functions by name
    std::unordered_set<std::string> seen;

    for (const auto& func: ffi.free_functions)
    {
        if (!seen.insert(func.method_name).second)
        {
            continue;
        }

        const std::string params = FormatParamList(func.params);
        const std::string ret = SimplifyReturnType(func);

        out << func.method_name << "(" << params << ")";
        if (!ret.empty())
        {
            out << " → " << ret;
        }
        out << "\n";
    }
}

// ---------------------------------------------------------------------------
// Public entry point
// ---------------------------------------------------------------------------

void GenerateAllMarkdownFiles(const ParsedFFI& ffi, const fs::path& out_dir)
{
    for (const auto& lang: kwx_Languages)
    {
        // Per-class markdown files
        for (const auto& class_info: ffi.classes)
        {
            WriteClassMarkdown(class_info, lang, out_dir);
        }

        // Global markdown files
        WriteConstantsMarkdown(ffi, lang, out_dir);
        WriteEventsMarkdown(ffi, lang, out_dir);
        WriteFreeFunctionsMarkdown(ffi, lang, out_dir);

        std::println(stderr, "  {}: {:L} classes + constants, events, free_functions", lang.key,
                     ffi.classes.size());
    }
}
