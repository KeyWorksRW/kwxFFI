/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse C++ class definitions and inheritance hierarchies
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "class_parser.h"
#include "parser_utils.h"

#include <array>
#include <format>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <string_view>
#include <unordered_set>

// Named constants for magic strings used in function parsing.
constexpr std::string_view WX_PREFIX { "wx" };
constexpr std::string_view KWX_PREFIX { "kwx" };
constexpr const char* MACRO_TCLASS = "TClass";
constexpr const char* MACRO_TSELF = "TSelf";
constexpr const char* METHOD_DELETE = "Delete";
constexpr int MAX_INHERITANCE_DEPTH = 50;

// Check if parentheses are balanced in the given string.
[[nodiscard]] static bool ParensBalanced(const std::string& text)
{
    int depth = 0;
    for (const char char_val: text)
    {
        if (char_val == '(')
        {
            ++depth;
        }
        else if (char_val == ')')
        {
            --depth;
        }
        if (depth < 0)
        {
            return false;
        }
    }
    return depth == 0;
}

// Find the function parameter list opening paren, scanning backwards from the
// semicolon. Returns the position of the matching '(' for the ')' that precedes ';'.
// This correctly skips over macro parens in the return type, e.g.:
//   TClass(wxButton) wxButton_Create(TClass(wxWindow) parent, ...);
static size_t FindFuncParenOpen(const std::string& line, size_t semicolon_pos)
{
    // Find the ')' just before the semicolon
    size_t paren_close = std::string::npos;
    for (size_t i = semicolon_pos; i != std::string::npos; --i)
    {
        if (line[i] == ')')
        {
            paren_close = i;
            break;
        }
        if (i == 0)
        {
            break;
        }
    }
    if (paren_close == std::string::npos)
    {
        return std::string::npos;
    }

    // Walk backwards from paren_close to find matching '('
    int depth = 0;
    for (size_t i = paren_close; i != std::string::npos; --i)
    {
        if (line[i] == ')')
        {
            ++depth;
        }
        else if (line[i] == '(')
        {
            --depth;
            if (depth == 0)
            {
                return i;
            }
        }
        if (i == 0)
        {
            break;
        }
    }
    return std::string::npos;
}

// Parse a function declaration from a string like:
//   "TClass(wxButton) wxButton_Create(TClass(wxWindow) parent, int id, ...)"
// (without the trailing semicolon)
// Returns true on success.
[[nodiscard]] static bool ParseFunctionDecl(const std::string& decl_str,
                                            const std::string& current_class,
                                            FunctionDecl& decl_out)
{
    // Find the function parameter list
    size_t semicolon = decl_str.rfind(';');
    if (semicolon == std::string::npos)
    {
        // No semicolon — try without (might have been stripped)
        semicolon = decl_str.size();
    }

    // Find the matching open paren for the function parameters
    const size_t func_paren_open = FindFuncParenOpen(decl_str, semicolon - 1);
    if (func_paren_open == std::string::npos)
    {
        return false;
    }

    // Find the matching close paren
    size_t func_paren_close = std::string::npos;
    {
        int depth = 0;
        for (size_t i = func_paren_open; i < decl_str.size(); ++i)
        {
            if (decl_str[i] == '(')
            {
                ++depth;
            }
            else if (decl_str[i] == ')')
            {
                --depth;
                if (depth == 0)
                {
                    func_paren_close = i;
                    break;
                }
            }
        }
    }
    if (func_paren_close == std::string::npos)
    {
        return false;
    }

    // Extract: prefix (return type + func name) and parameter list
    const std::string prefix = Trim(decl_str.substr(0, func_paren_open));
    const std::string param_str =
        Trim(decl_str.substr(func_paren_open + 1, func_paren_close - func_paren_open - 1));

    if (prefix.empty())
    {
        return false;
    }

    // Split prefix into return type and function name.
    // The function name is the last token. Return type may include macro parens.
    std::string func_name;
    std::string return_type_str;

    // Check if prefix ends with ')' — return type is a macro like TClass(wxFoo)
    const size_t last_close = prefix.rfind(')');
    const size_t last_space = prefix.rfind(' ');

    if (last_close != std::string::npos &&
        (last_space == std::string::npos || last_close > last_space))
    {
        // The function name follows a macro return type.
        // Find the end of the macro: walk forward from last_close to find func name.
        const std::string after_macro = Trim(prefix.substr(last_close + 1));
        if (after_macro.empty())
        {
            // The entire prefix is the function name (no return type) — unlikely,
            // but handle it. Actually this means the return type IS the macro and there's
            // no separate func name after it. This shouldn't happen for well-formed decls.
            return false;
        }
        func_name = after_macro;
        return_type_str = Trim(prefix.substr(0, last_close + 1));
    }
    else if (last_space != std::string::npos)
    {
        // Simple case: "void wxButton_SetDefault" or "int wxButton_GetId"
        func_name = Trim(prefix.substr(last_space + 1));
        return_type_str = Trim(prefix.substr(0, last_space));
    }
    else
    {
        // Single word — function name with no explicit return type
        // (shouldn't happen in valid C declarations, but handle gracefully)
        func_name = prefix;
        return_type_str = "int";  // default assumption
    }

    if (func_name.empty())
    {
        return false;
    }

    // Preserve the original C symbol name verbatim before we remap the class prefix.
    decl_out.c_func_name = func_name;

    // Check for pointer in func_name: e.g., "void*" as return followed by func name
    // Handle "void* wxConnection_Request" where last_space split gives func "wxConn..."
    // and return "void*" — this should already work with the space split above.

    // Split function name into class prefix and method name.
    // Only treat 'ClassName_Method' as a class method when:
    //   (a) the prefix starts with 'wx' or 'kwx' (standard naming), OR
    //   (b) the prefix has no wx/kwx but "wx"+prefix matches the current class
    //       (shortened naming: BitmapDataObject_Delete -> wxBitmapDataObject).
    // Everything else (expXXX_YYY, expBK_*, etc.) becomes a free function.
    const size_t underscore = func_name.find('_');
    if (underscore != std::string::npos)
    {
        const std::string candidate_class = func_name.substr(0, underscore);
        const bool has_wx_prefix =
            candidate_class.size() >= WX_PREFIX.length() && candidate_class.starts_with(WX_PREFIX);
        const bool has_kwx_prefix = candidate_class.size() >= KWX_PREFIX.length() &&
                                    candidate_class.starts_with(KWX_PREFIX);

        if (has_wx_prefix || has_kwx_prefix)
        {
            // Standard wx/kwx prefix -- direct class assignment.
            decl_out.class_name = candidate_class;
            decl_out.method_name = func_name.substr(underscore + 1);
        }
        else if (!current_class.empty() &&
                 (current_class == std::string { WX_PREFIX } + candidate_class ||
                  current_class == std::string { KWX_PREFIX } + candidate_class ||
                  current_class == candidate_class))
        {
            // Shortened prefix convention (e.g., BitmapDataObject_Delete inside the
            // wxBitmapDataObject class block).  Map to the canonical class name.
            decl_out.class_name = current_class;
            decl_out.method_name = func_name.substr(underscore + 1);
        }
        else
        {
            // Non-wx/kwx prefix not matching the current class context.
            // Treat as a free function (expPROPSHEET_DEFAULT, expBK_*, etc.).
            decl_out.class_name = {};
            decl_out.method_name = func_name;
        }
    }
    else
    {
        // No underscore -- free function (kwxMessageBox, PushProvider, etc.)
        decl_out.class_name = {};
        decl_out.method_name = func_name;
    }

    // Parse return type for macro info
    decl_out.return_type = return_type_str;
    std::ignore = ParseMacroType(return_type_str, decl_out.return_macro, decl_out.return_arg);

    // Parse parameters
    if (!param_str.empty())
    {
        const std::vector<std::string> tokens = SplitParams(param_str);
        for (const auto& token: tokens)
        {
            decl_out.params.push_back(ParseOneParam(token));
        }
    }

    // Compute flags
    decl_out.is_constructor = decl_out.method_name.starts_with("Create");
    decl_out.is_destructor = decl_out.method_name == METHOD_DELETE;
    decl_out.has_self = !decl_out.params.empty() && decl_out.params[0].macro_name == MACRO_TSELF;

    return true;
}

// Extract TClassDef or TClassDefExtend from the beginning of a logical line.
// Returns the position AFTER the closing ')' of the class def macro, or string::npos
// if no class def is found. Populates class_name and parent_name.
static size_t ExtractClassDef(const std::string& line, std::string& class_name,
                              std::string& parent_name)
{
    class_name.clear();
    parent_name.clear();

    // Try TClassDefExtend(Name, Parent)
    const std::string marker_ext = "TClassDefExtend(";
    const std::string marker_def = "TClassDef(";

    size_t marker_pos = line.find(marker_ext);
    const bool is_extend = (marker_pos != std::string::npos);
    if (!is_extend)
    {
        marker_pos = line.find(marker_def);
    }
    if (marker_pos == std::string::npos)
    {
        return std::string::npos;
    }

    const size_t paren_start = marker_pos + (is_extend ? marker_ext.size() : marker_def.size()) - 1;

    // Find the matching closing paren
    int depth = 0;
    size_t paren_close = std::string::npos;
    for (size_t i = paren_start; i < line.size(); ++i)
    {
        if (line[i] == '(')
        {
            ++depth;
        }
        else if (line[i] == ')')
        {
            --depth;
            if (depth == 0)
            {
                paren_close = i;
                break;
            }
        }
    }
    if (paren_close == std::string::npos)
    {
        return std::string::npos;
    }

    // Extract content between parens
    const std::string content = Trim(line.substr(paren_start + 1, paren_close - paren_start - 1));

    if (is_extend)
    {
        // Split on comma: "Name, Parent"
        const size_t comma = content.find(',');
        if (comma != std::string::npos)
        {
            class_name = Trim(content.substr(0, comma));
            parent_name = Trim(content.substr(comma + 1));
        }
        else
        {
            class_name = content;
        }
    }
    else
    {
        class_name = content;
    }

    return paren_close + 1;
}

// Check if a logical line is a standalone class definition (no function content after
// the TClassDef closing paren).
[[nodiscard]] static bool IsStandaloneClassDef(const std::string& line)
{
    std::string class_name;
    std::string parent_name;
    const size_t after_classdef = ExtractClassDef(line, class_name, parent_name);
    if (after_classdef == std::string::npos)
    {
        return false;
    }
    // If nothing follows the class def (or only whitespace), it's standalone
    const std::string remainder = Trim(line.substr(after_classdef));
    return remainder.empty();
}

// Walk the parent hierarchy to check if a class derives from a target class.
[[nodiscard]] static bool
    DerivesFrom(const std::string& class_name, const std::string& target,
                const std::unordered_map<std::string, std::string>& parent_map,
                int max_depth = MAX_INHERITANCE_DEPTH)
{
    std::string current = class_name;
    for (int i = 0; i < max_depth; ++i)
    {
        if (current == target)
        {
            return true;
        }
        const std::unordered_map<std::string, std::string>::const_iterator iter =
            parent_map.find(current);
        if (iter == parent_map.end() || iter->second.empty())
        {
            return false;
        }
        current = iter->second;
    }
    return false;
}

// Strip C and C++ comments from all lines in place.
// Block comments spanning multiple lines are handled via a stateful scan.
static void StripComments(std::vector<std::string>& lines)
{
    bool in_block_comment = false;
    for (auto& line: lines)
    {
        std::string stripped_line;
        stripped_line.reserve(line.size());
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (in_block_comment)
            {
                if (line[i] == '*' && i + 1 < line.size() && line[i + 1] == '/')
                {
                    in_block_comment = false;
                    ++i;  // skip '/'
                }
                // else: inside block comment, discard character
            }
            else
            {
                if (line[i] == '/' && i + 1 < line.size())
                {
                    if (line[i + 1] == '/')
                    {
                        break;  // rest of line is a comment
                    }
                    if (line[i + 1] == '*')
                    {
                        in_block_comment = true;
                        ++i;  // skip '*'
                        continue;
                    }
                }
                stripped_line += line[i];
            }
        }
        line = std::move(stripped_line);
    }
}

// Build logical lines by joining continuation lines.
// A logical line is complete when parentheses are balanced AND either:
//   - It ends with ';'  (function declaration)
//   - It's a standalone class definition (TClassDef/TClassDefExtend with no function)
static std::vector<std::string> BuildLogicalLines(const std::vector<std::string>& lines)
{
    std::vector<std::string> logical_lines;
    std::string buffer;

    auto FlushBuffer = [&]()
    {
        if (!buffer.empty())
        {
            logical_lines.push_back(buffer);
            buffer.clear();
        }
    };

    for (const auto& raw_line: lines)
    {
        const std::string stripped = Trim(raw_line);

        // Skip preprocessor directives and empty lines
        if (stripped.empty())
        {
            // Empty line: flush any pending standalone class def
            if (!buffer.empty() && ParensBalanced(buffer))
            {
                FlushBuffer();
            }
            continue;
        }
        if (stripped[0] == '#')
        {
            continue;
        }

        // Accumulate into buffer
        if (buffer.empty())
        {
            buffer = stripped;
        }
        else
        {
            buffer += " " + stripped;
        }

        // Check completeness: semicolon-terminated or standalone class definition
        if (ParensBalanced(buffer))
        {
            if (buffer.back() == ';' || IsStandaloneClassDef(buffer))
            {
                FlushBuffer();
            }
            // Otherwise, keep accumulating (next line may add function content)
        }
        // If parens unbalanced, keep accumulating
    }
    // Flush any remaining buffer
    FlushBuffer();
    return logical_lines;
}

// Process logical lines into ClassInfo structures stored in result.
// Returns the total number of methods parsed.
static size_t ProcessLogicalLines(const std::vector<std::string>& logical_lines,
                                  ClassParseResult& result)
{
    size_t current_class_idx = SIZE_MAX;  // sentinel — no current class yet
    size_t total_methods = 0;

    // Find an existing ClassInfo by name, or create one.  Returns its index.
    auto GetOrCreateClassIdx = [&](const std::string& name,
                                   const std::string& parent = "") -> size_t
    {
        for (size_t i = 0; i < result.classes.size(); ++i)
        {
            if (result.classes[i].name == name)
            {
                return i;
            }
        }
        ClassInfo class_item;
        class_item.name = name;
        class_item.parent = parent;
        result.classes.push_back(std::move(class_item));
        return result.classes.size() - 1;
    };

    for (const auto& logical_line: logical_lines)
    {
        std::string class_name;
        std::string parent_name;
        const size_t after_classdef = ExtractClassDef(logical_line, class_name, parent_name);

        if (after_classdef != std::string::npos)
        {
            // Found a class definition — start a new class (or re-open an existing one)
            current_class_idx = GetOrCreateClassIdx(class_name, parent_name);
            if (!parent_name.empty())
            {
                result.classes[current_class_idx].parent = parent_name;
                result.parent_map[class_name] = parent_name;
            }

            // Check for function declarations on the same line after the class def
            const std::string remainder = Trim(logical_line.substr(after_classdef));
            if (!remainder.empty())
            {
                if (remainder.back() == ';')
                {
                    size_t scan_pos = 0;
                    while (scan_pos < remainder.size())
                    {
                        const size_t semi = remainder.find(';', scan_pos);
                        if (semi == std::string::npos)
                        {
                            break;
                        }

                        const std::string func_str =
                            Trim(remainder.substr(scan_pos, semi - scan_pos + 1));
                        if (!func_str.empty())
                        {
                            FunctionDecl decl;
                            if (ParseFunctionDecl(func_str, class_name, decl))
                            {
                                result.classes[current_class_idx].methods.push_back(
                                    std::move(decl));
                                ++total_methods;
                            }
                            else
                            {
                                std::cerr << "  Warning: unparsed function in class " << class_name
                                          << ": " << func_str << "\n";
                            }
                        }
                        scan_pos = semi + 1;
                    }
                }
                else
                {
                    std::cerr << "  Warning: incomplete function after class def " << class_name
                              << ": " << remainder << "\n";
                }
            }
        }
        else if (current_class_idx != SIZE_MAX)
        {
            // No class-def marker — parse functions and route by prefix.
            size_t scan_pos = 0;
            while (scan_pos < logical_line.size())
            {
                const size_t semi = logical_line.find(';', scan_pos);
                if (semi == std::string::npos)
                {
                    break;
                }

                const std::string func_str =
                    Trim(logical_line.substr(scan_pos, semi - scan_pos + 1));
                if (!func_str.empty())
                {
                    FunctionDecl decl;
                    if (ParseFunctionDecl(func_str, result.classes[current_class_idx].name, decl))
                    {
                        if (decl.class_name.empty())
                        {
                            // Free function embedded in a class section
                            result.free_functions.push_back(std::move(decl));
                        }
                        else
                        {
                            // Route to the class that matches the function's prefix.
                            size_t target_idx = current_class_idx;
                            if (decl.class_name != result.classes[current_class_idx].name)
                            {
                                target_idx = GetOrCreateClassIdx(decl.class_name);
                                current_class_idx = target_idx;
                            }
                            result.classes[target_idx].methods.push_back(std::move(decl));
                            ++total_methods;
                        }
                    }
                    else
                    {
                        std::cerr << "  Warning: unparsed function: " << func_str << "\n";
                    }
                }
                scan_pos = semi + 1;
            }
        }
        else
        {
            // Function before any class def — shouldn't happen in kwx_classes.h
            std::cerr << "  Warning: function before any class definition: " << logical_line
                      << "\n";
        }
    }

    return total_methods;
}

// Detect mixin classes: classes with no parent, no constructors, and all methods
// use TClass(ClassName) as their first parameter instead of TSelf(ClassName).
static void DetectMixinClasses(std::vector<ClassInfo>& classes)
{
    for (auto& class_entry: classes)
    {
        if (!class_entry.parent.empty() || class_entry.methods.empty())
        {
            continue;
        }
        bool has_constructor = false;
        bool all_tclass_self = true;
        bool has_non_ctor_methods = false;
        for (const auto& func: class_entry.methods)
        {
            if (func.is_constructor)
            {
                has_constructor = true;
                continue;
            }
            has_non_ctor_methods = true;
            if (func.params.empty() || func.params[0].macro_name != MACRO_TCLASS ||
                func.params[0].macro_arg != class_entry.name)
            {
                all_tclass_self = false;
                break;
            }
        }
        class_entry.is_mixin = !has_constructor && has_non_ctor_methods && all_tclass_self;
    }
}

// Build mixin_map from hardcoded wxWidgets class hierarchy.
// These relationships reflect wxWidgets' C++ multiple inheritance that
// is not captured in kwx_classes.h's single-parent TClassDefExtend.
// Each entry is {mixin_class, {consumer_class, ...}}.
// IMPORTANT: wxSpinCtrl and wxSpinCtrlDouble are NOT wxTextEntry consumers
// — they only inherit wxTextEntry on some platforms (generic builds) but
// not on MSW or GTK, so including them would produce incorrect casts.
static void BuildMixinMap(ClassParseResult& result)
{
    // Hardcoded mixin → consumer table. Derived from wxWidgets 3.3 headers.
    // To update: check which concrete classes inherit the mixin in the
    // wxWidgets C++ headers, then verify the consumer class is wrapped
    // in kwx_classes.h (i.e., exists in result.classes).
    struct MixinEntry
    {
        const char* mixin;
        std::vector<const char*> consumers;
    };
    const std::array<MixinEntry, 2> mixin_table = { {
        { .mixin = "wxTextEntry",
          .consumers = { "wxTextCtrl", "wxComboBox", "wxSearchCtrl", "wxBitmapComboBox" } },
        { .mixin = "wxItemContainer",
          .consumers = { "wxListBox", "wxChoice", "wxCheckListBox", "wxComboBox",
                         "wxBitmapComboBox" } },
    } };

    // Build a name set for fast lookup of parsed classes.
    std::unordered_set<std::string> parsed_class_names;
    for (const auto& class_entry: result.classes)
    {
        parsed_class_names.insert(class_entry.name);
    }

    for (const auto& entry: mixin_table)
    {
        if (!parsed_class_names.contains(entry.mixin))
        {
            std::cerr << "  Warning: mixin '" << entry.mixin
                      << "' in mixin_table not found in parsed classes\n";
            continue;
        }
        for (const auto& consumer: entry.consumers)
        {
            if (!parsed_class_names.contains(consumer))
            {
                std::cerr << "  Warning: mixin consumer '" << consumer << "' (for " << entry.mixin
                          << ") not found in parsed classes\n";
                continue;
            }
            result.mixin_map[consumer].emplace_back(entry.mixin);
        }
    }
}

// Report summary statistics about the parsed classes to stderr.
static void ReportParseStats(const ClassParseResult& result, size_t total_methods)
{
    static const std::locale user_locale("");
    std::cerr << std::format(user_locale, "  Classes:        {:L}\n", result.classes.size());
    std::cerr << std::format(user_locale, "  Total methods:  {:L}\n", total_methods);
    std::cerr << std::format(user_locale, "  Class-section free funcs: {:L}\n",
                             result.free_functions.size());

    size_t mixin_count = 0;
    for (const auto& class_entry: result.classes)
    {
        if (class_entry.is_mixin)
        {
            ++mixin_count;
        }
    }
    if (mixin_count > 0)
    {
        std::cerr << std::format(user_locale, "  Mixin classes:  {:L}\n", mixin_count);
    }
    if (!result.mixin_map.empty())
    {
        size_t link_count = 0;
        for (const auto& [unused_key, mixins]: result.mixin_map)
        {
            link_count += mixins.size();
        }
        std::cerr << std::format(user_locale, "  Mixin links:    {:L} (across {:L} consumers)\n",
                                 link_count, result.mixin_map.size());
    }
}

ClassParseResult ParseClasses(const std::filesystem::path& file_path)
{
    ClassParseResult result;

    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open " << file_path << "\n";
        return result;
    }

    // Read all lines
    std::vector<std::string> lines;
    {
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
    }

    // Pre-process: strip C and C++ comments from all lines.
    StripComments(lines);

    // Phase 1: Build logical lines by joining continuations.
    const std::vector<std::string> logical_lines = BuildLogicalLines(lines);

    // Phase 2: Process logical lines into ClassInfo structures.
    const size_t total_methods = ProcessLogicalLines(logical_lines, result);

    // Phase 3: Resolve inheritance hierarchy flags.
    for (auto& class_entry: result.classes)
    {
        class_entry.is_window_derived =
            DerivesFrom(class_entry.name, "wxWindow", result.parent_map);
        class_entry.is_object_derived =
            DerivesFrom(class_entry.name, "wxObject", result.parent_map);
    }

    // Phase 4: Detect mixin classes.
    DetectMixinClasses(result.classes);

    // Phase 5: Build mixin_map from hardcoded wxWidgets class hierarchy.
    BuildMixinMap(result);

    // Report summary statistics.
    ReportParseStats(result, total_methods);

    return result;
}
