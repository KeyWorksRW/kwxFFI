/////////////////////////////////////////////////////////////////////////////
// Purpose:   Fortran ISO_C_BINDING FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "lang_fortran.h"

#include "../file_writer.h"
#include "fortran_idiom_map.h"
#include "fortran_type_map.h"
#include "lang_common.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <map>
#include <print>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

// String prefix constants for export name transformation
static constexpr std::string_view EXP_WX_PREFIX = "exp_wx";
static constexpr std::string_view EXPWX_PREFIX = "expwx";
static constexpr std::string_view EXPEVT_PREFIX = "expEVT_";
static constexpr std::string_view EXPK_PREFIX = "expK_";
static constexpr std::string_view EXP_PREFIX = "exp";
static constexpr std::string_view EXP_UNDER_PREFIX = "exp_";

// Transform a C export name (with "exp" prefix) into an idiomatic Fortran name.
//   exp_wxEVT_FOO -> wxEVT_FOO  (strip "exp_")
//   expwxFOO      -> wxFOO      (strip "exp")
//   expEVT_FOO    -> wxEVT_FOO  (replace "exp" with "wx")
//   expK_FOO      -> WXK_FOO    (replace "exp" with "WX")
//   expOther      -> Other      (strip "exp" fallback)
static std::string FortranName(const std::string& exportName)
{
    if (exportName.starts_with(EXP_WX_PREFIX))
    {
        return exportName.substr(EXP_UNDER_PREFIX.size());  // "exp_wxEVT_X" -> "wxEVT_X"
    }
    if (exportName.compare(0, EXPWX_PREFIX.size(), EXPWX_PREFIX.data()) == 0)
    {
        return exportName.substr(EXP_PREFIX.size());  // strip "exp" -> "wxFOO"
    }
    if (exportName.compare(0, EXPEVT_PREFIX.size(), EXPEVT_PREFIX.data()) == 0)
    {
        return "wx" + exportName.substr(EXP_PREFIX.size());  // "expEVT_X" -> "wxEVT_X"
    }
    if (exportName.compare(0, EXPK_PREFIX.size(), EXPK_PREFIX.data()) == 0)
    {
        return "WX" + exportName.substr(EXP_PREFIX.size());  // "expK_X" -> "WXK_X"
    }
    if (exportName.compare(0, EXP_PREFIX.size(), EXP_PREFIX.data()) == 0)
    {
        return exportName.substr(EXP_PREFIX.size());  // strip "exp"
    }
    return exportName;
}

// Fortran identifiers are case-insensitive, so a constant such as wxPROCESS_REDIRECT cannot be
// declared next to the wxProcess_Redirect method in the same module — that would be a duplicate
// identifier. The method keeps its exact C name; a colliding constant gets a "_FLAG" suffix,
// which keeps it recognizable as the wxWidgets flag it represents. Constants, events, keys and
// methods all live in the single kwxffi module, so this pass is the only naming authority.
struct ConstantFortranName
{
    std::string name;
    bool renamed = false;
};

// Map every constant's C export name to the Fortran identifier that must be used for it. The
// result is independent of parser order, so emitted identifiers are stable across runs.
[[nodiscard]] static std::map<std::string, ConstantFortranName>
    BuildConstantNames(const ParsedFFI& ffi_data)
{
    // Case-insensitive names already claimed by events, keys, methods and free functions.
    std::set<std::string> used;
    for (const auto& event: ffi_data.events)
    {
        used.insert(ToLower(FortranName(event.export_name)));
    }
    for (const auto& key_decl: ffi_data.keys)
    {
        used.insert(ToLower(FortranName(key_decl.export_name)));
    }
    for (const auto& class_info: ffi_data.classes)
    {
        for (const auto& method: class_info.methods)
        {
            if (IsValidFunction(method))
            {
                used.insert(ToLower(CFuncName(method)));
            }
        }
    }
    for (const auto& func: ffi_data.free_functions)
    {
        if (IsValidFunction(func))
        {
            used.insert(ToLower(CFuncName(func)));
        }
    }

    std::vector<const ConstantDecl*> sorted_constants;
    sorted_constants.reserve(ffi_data.constants.size());
    for (const auto& constant: ffi_data.constants)
    {
        sorted_constants.push_back(&constant);
    }
    std::ranges::sort(sorted_constants,
                      [](const ConstantDecl* left, const ConstantDecl* right)
                      {
                          return left->export_name < right->export_name;
                      });

    std::map<std::string, ConstantFortranName> names;
    for (const ConstantDecl* constant: sorted_constants)
    {
        std::string name = FortranName(constant->export_name);
        bool renamed = false;
        if (used.contains(ToLower(name)))
        {
            const std::string base_name = name + "_FLAG";
            name = base_name;
            renamed = true;
            int suffix = 0;
            while (used.contains(ToLower(name)))
            {
                ++suffix;
                name = base_name + std::to_string(suffix);
            }
        }
        used.insert(ToLower(name));
        names.insert_or_assign(constant->export_name, ConstantFortranName { name, renamed });
    }
    return names;
}

// Emit a single Fortran interface declaration for a C function.
// Handles both subroutines (void return) and functions (non-void return).
static void EmitFortranInterface(std::ostream& output, const std::string& cName,
                                 const FortranReturnInfo& retInfo,
                                 const std::vector<FortranParam>& params)
{
    const std::set<std::string> imports = CollectImports(params, retInfo);

    if (retInfo.is_void)
    {
        // Subroutine
        output << "    subroutine " << cName << "(";
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (i > 0)
            {
                output << ", ";
            }
            output << params[i].name;
        }
        output << ") &\n";
        output << "        bind(C, name='" << cName << "')\n";
    }
    else
    {
        // Function with return type
        output << "    " << retInfo.fortran_type << " function " << cName << "(";
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (i > 0)
            {
                output << ", ";
            }
            output << params[i].name;
        }
        output << ") &\n";
        output << "        bind(C, name='" << cName << "')\n";
    }

    // Import statement
    if (!imports.empty())
    {
        output << "      import :: ";
        bool first = true;
        for (const auto& symbol: imports)
        {
            if (!first)
            {
                output << ", ";
            }
            output << symbol;
            first = false;
        }
        output << "\n";
    }

    // Parameter declarations
    for (const auto& param: params)
    {
        output << "      " << param.fortran_type << (param.pass_by_value ? ", value" : "")
               << " :: " << param.name << "\n";
    }

    if (retInfo.is_void)
    {
        output << "    end subroutine\n";
    }
    else
    {
        output << "    end function\n";
    }
}

// Emit an interface declaration from a FunctionDecl.
static void EmitFunctionInterface(std::ostream& output, const FunctionDecl& func)
{
    const std::string cName = CFuncName(func);
    const FortranReturnInfo retInfo = FortranReturnType(func.return_type, func.return_macro);

    std::vector<FortranParam> fParams;
    for (const auto& param: func.params)
    {
        std::vector<FortranParam> expanded = ExpandParamToFortran(param);
        for (auto&& fort_param: expanded)
        {
            fParams.push_back(std::move(fort_param));
        }
    }

    EmitFortranInterface(output, cName, retInfo, fParams);
}

// -------------------------------------------------------------------------
// FortranEmitter public interface
// -------------------------------------------------------------------------

void FortranEmitter::Generate(const ParsedFFI& ffi_data, const fs::path& outDir)
{
    std::ignore = fs::create_directories(outDir);

    // Sort once; passed to all sub-generators that need ordered output.
    std::vector<EventDecl> sorted_events = ffi_data.events;
    std::ranges::sort(sorted_events,
                      [](const EventDecl& left, const EventDecl& right)
                      {
                          return left.event_name < right.event_name;
                      });

    std::vector<KeyDecl> sorted_keys = ffi_data.keys;
    std::ranges::sort(sorted_keys,
                      [](const KeyDecl& left, const KeyDecl& right)
                      {
                          return left.key_name < right.key_name;
                      });

    // 1. Raw C interface module (kwxffi_gen.f90)
    {
        const fs::path path = outDir / "kwxffi_gen.f90";
        ConditionalFileWriter output(path);

        output << "! Code generated by kwxgen. DO NOT EDIT.\n";
        output << "module kwxffi\n";
        output << "  use, intrinsic :: iso_c_binding\n";
        output << "  implicit none\n\n";
        output << "  interface\n\n";

        GenerateEvents(sorted_events, output);
        GenerateKeys(sorted_keys, output);
        GenerateConstants(ffi_data, output);
        GenerateClasses(ffi_data, output);
        GenerateFreeFunctions(ffi_data, output);

        output << "  end interface\n\n";
        output << "end module kwxffi\n";
    }

    // 2. Idiomatic Fortran wrapper modules
    GenerateTypeTree(ffi_data, outDir);
    GenerateStringModule(outDir);
    GenerateEventsModule(ffi_data, outDir);
    GenerateClassModules(ffi_data, outDir);

    std::println(stderr, "Fortran: generated all files in {}", outDir.string());
}

VerifyResult FortranEmitter::Verify(const ParsedFFI& /* ffi_data */, const fs::path& /* out_dir */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("Fortran verify: use 'kwxgen verify' command instead");
    return result;
}

// Root of every generated Fortran wrapper type. It owns the two handle fields that all
// wrapper types inherit.
static constexpr std::string_view FORTRAN_ROOT_CLASS = "wxObject";

// Every class the model knows about: parsed classes, every parent named by the hierarchy,
// and every mixin. A mixin is not itself instantiated by a consumer, but wrapper modules
// take `class(<mixin>_t)` arguments, so the type must exist.
[[nodiscard]] static std::set<std::string> CollectFortranClassNames(const ParsedFFI& ffi_data)
{
    std::set<std::string> class_names;
    for (const ClassInfo& class_info: ffi_data.classes)
    {
        class_names.insert(class_info.name);
    }
    for (const std::pair<const std::string, std::string>& parent_entry: ffi_data.parent_map)
    {
        class_names.insert(parent_entry.first);
        if (!parent_entry.second.empty())
        {
            class_names.insert(parent_entry.second);
        }
    }
    for (const std::pair<const std::string, std::vector<std::string>>& mixin_entry:
         ffi_data.mixin_map)
    {
        class_names.insert(mixin_entry.first);
        for (const std::string& mixin_name: mixin_entry.second)
        {
            class_names.insert(mixin_name);
        }
    }
    class_names.insert(std::string(FORTRAN_ROOT_CLASS));
    return class_names;
}

// -------------------------------------------------------------------------
// Coverage report
// -------------------------------------------------------------------------

// Count the wrapper procedures a class module exposes, using the same C-name dedupe rule as
// CollectFortranClassProcedures(). Mixin methods belong to the consumer's module, so they
// are counted here as well. Counting the emitted procedures rather than the raw model keeps
// the parity gate honest about what the module really exposes.
static void CountFortranClassProcedures(const ClassInfo& class_info, const ParsedFFI& ffi_data,
                                        CoverageInfo& report)
{
    std::set<std::string> emitted_c_functions;
    size_t wrapped_count = 0;
    size_t collapsed_count = 0;

    const auto count_methods = [&](const ClassInfo& method_owner)
    {
        for (const FunctionDecl& method: method_owner.methods)
        {
            if (!IsValidFunction(method))
            {
                continue;
            }
            if (emitted_c_functions.insert(CFuncName(method)).second)
            {
                ++wrapped_count;
            }
            else
            {
                ++collapsed_count;
            }
        }
    };

    count_methods(class_info);

    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        ffi_data.mixin_map.find(class_info.name);
    if (mixin_iter != ffi_data.mixin_map.end())
    {
        for (const std::string& mixin_name: mixin_iter->second)
        {
            for (const ClassInfo& mixin_class: ffi_data.classes)
            {
                if (mixin_class.name == mixin_name)
                {
                    count_methods(mixin_class);
                    break;
                }
            }
        }
    }

    report.method_counts_by_class[class_info.name] = wrapped_count;
    if (collapsed_count != 0)
    {
        report.deduplicated_method_counts_by_class[class_info.name] = collapsed_count;
        report.deduplicated_method_count += collapsed_count;
    }
}

// Every parsed class plus every synthesized parent and mixin is represented in
// kwx_types.f90, so the whole type set counts as wrapped. A class contributes method counts
// only when GenerateClassModules() actually writes a module for it, so the report measures
// the emitted wrapper surface rather than the type tree.
CoverageInfo FortranEmitter::Coverage(const ParsedFFI& ffi_data) const
{
    CoverageInfo report;
    report.free_function_count = ffi_data.free_functions.size();
    report.event_count = ffi_data.events.size();
    report.key_count = ffi_data.keys.size();
    report.constant_count = ffi_data.constants.size();

    const std::set<std::string> class_names = CollectFortranClassNames(ffi_data);
    report.wrapped_classes.assign(class_names.begin(), class_names.end());

    // Mirror GenerateClassModules(): a class gets a module only when it owns at least one
    // valid method and its module name does not collide with an earlier class.
    std::set<std::string> generated_modules;
    for (const std::string& class_name: report.wrapped_classes)
    {
        const ClassInfo* class_info = nullptr;
        for (const ClassInfo& candidate: ffi_data.classes)
        {
            if (candidate.name == class_name)
            {
                class_info = &candidate;
                break;
            }
        }
        if (class_info == nullptr)
        {
            continue;
        }

        bool has_valid_method = false;
        for (const FunctionDecl& method: class_info->methods)
        {
            if (IsValidFunction(method))
            {
                has_valid_method = true;
                break;
            }
        }
        if (!has_valid_method)
        {
            continue;
        }

        if (!generated_modules.insert(FortranClassModuleName(class_name)).second)
        {
            continue;
        }

        CountFortranClassProcedures(*class_info, ffi_data, report);
    }

    return report;
}

// -------------------------------------------------------------------------
// Events
// -------------------------------------------------------------------------

void FortranEmitter::GenerateEvents(const std::vector<EventDecl>& events, std::ostream& output)
{
    output << "    ! Events\n\n";

    for (const auto& event: events)
    {
        const std::string fname = FortranName(event.export_name);
        output << "    integer(c_int) function " << fname << "() &\n";
        output << "        bind(C, name='" << event.export_name << "')\n";
        output << "      import :: c_int\n";
        output << "    end function\n\n";
    }

    std::println(stderr, "  Events:           {:L}", events.size());
}

// -------------------------------------------------------------------------
// Keys
// -------------------------------------------------------------------------

void FortranEmitter::GenerateKeys(const std::vector<KeyDecl>& keys, std::ostream& output)
{
    output << "    ! Keys\n\n";

    for (const auto& key_decl: keys)
    {
        const std::string fname = FortranName(key_decl.export_name);
        output << "    integer(c_int) function " << fname << "() &\n";
        output << "        bind(C, name='" << key_decl.export_name << "')\n";
        output << "      import :: c_int\n";
        output << "    end function\n\n";
    }

    std::println(stderr, "  Keys:             {:L}", keys.size());
}

// -------------------------------------------------------------------------
// Constants
// -------------------------------------------------------------------------

void FortranEmitter::GenerateConstants(const ParsedFFI& ffi_data, std::ostream& output)
{
    output << "    ! Constants\n\n";

    const std::map<std::string, ConstantFortranName> constant_names = BuildConstantNames(ffi_data);

    std::vector<ConstantDecl> sorted_constants = ffi_data.constants;
    std::ranges::sort(sorted_constants,
                      [](const ConstantDecl& left, const ConstantDecl& right)
                      {
                          return left.export_name < right.export_name;
                      });

    for (const auto& constant: sorted_constants)
    {
        std::string fType;
        std::string importSym;
        if (constant.return_type.find('*') != std::string::npos)
        {
            fType = "type(c_ptr)";
            importSym = "c_ptr";
        }
        else
        {
            fType = "integer(c_int)";
            importSym = "c_int";
        }

        const ConstantFortranName& fortran_name = constant_names.at(constant.export_name);
        if (fortran_name.renamed)
        {
            output << "    ! " << FortranName(constant.export_name) << " renamed to "
                   << fortran_name.name << ":\n";
            output << "    ! Fortran identifiers are case-insensitive.\n";
        }
        output << "    " << fType << " function " << fortran_name.name << "() &\n";
        output << "        bind(C, name='" << constant.export_name << "')\n";
        output << "      import :: " << importSym << "\n";
        output << "    end function\n\n";
    }

    std::println(stderr, "  Constants:        {:L}", sorted_constants.size());
}

// -------------------------------------------------------------------------
// Classes
// -------------------------------------------------------------------------

void FortranEmitter::GenerateClasses(const ParsedFFI& ffi_data, std::ostream& output)
{
    size_t methodCount = 0;
    size_t skippedCount = 0;

    for (const auto& class_decl: ffi_data.classes)
    {
        if (class_decl.methods.empty())
        {
            continue;
        }

        output << "    ! " << class_decl.name << "\n\n";

        for (const auto& func: class_decl.methods)
        {
            if (!IsValidFunction(func))
            {
                ++skippedCount;
                continue;
            }
            EmitFunctionInterface(output, func);
            output << "\n";
            ++methodCount;
        }
    }

    std::print(stderr, "  Class methods:    {:L}", methodCount);
    if (skippedCount > 0)
    {
        std::print(stderr, " ({:L} skipped)", skippedCount);
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// Free Functions
// -------------------------------------------------------------------------

void FortranEmitter::GenerateFreeFunctions(const ParsedFFI& ffi_data, std::ostream& output)
{
    if (ffi_data.free_functions.empty())
    {
        return;
    }

    output << "    ! Free functions\n\n";

    size_t count = 0;
    for (const auto& func: ffi_data.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        EmitFunctionInterface(output, func);
        output << "\n";
        ++count;
    }

    std::println(stderr, "  Free functions:   {:L}", count);
}

// -------------------------------------------------------------------------
// kwx_types.f90 — Generated class type tree
// -------------------------------------------------------------------------

// Map every model class name to its Fortran type identifier. Names arrive sorted so the
// assignment — and any collision suffix — is deterministic across runs.
[[nodiscard]] static std::map<std::string, std::string>
    BuildFortranTypeIdentifiers(const std::set<std::string>& class_names)
{
    std::map<std::string, std::string> identifiers;
    std::set<std::string> used_identifiers;

    for (const std::string& class_name: class_names)
    {
        std::string identifier =
            FortranSanitizeIdentifier(class_name, FORTRAN_TYPE_IDENTIFIER_BASE_MAX);
        if (used_identifiers.contains(identifier))
        {
            const std::string base_identifier = identifier;
            for (size_t ordinal = 2;; ++ordinal)
            {
                identifier = base_identifier + "_" + std::to_string(ordinal);
                if (!used_identifiers.contains(identifier))
                {
                    break;
                }
            }
            std::println(stderr,
                         "Fortran type tree: '{}' collides with an existing identifier, using '{}'",
                         class_name, identifier);
        }
        used_identifiers.insert(identifier);
        identifiers.insert_or_assign(class_name, identifier);
    }
    return identifiers;
}

// Fortran requires the parent type to be declared before the type that extends it, so the
// emission order must be a topological order of the parent relation. Kahn's algorithm gives
// that order; any class left unplaced is appended in name order so the output stays complete
// even if the hierarchy was malformed.
[[nodiscard]] static std::vector<std::string>
    TopologicalClassOrder(const std::map<std::string, std::string>& parents,
                          const std::set<std::string>& class_names, std::string_view root_class)
{
    std::map<std::string, std::vector<std::string>> children;
    std::map<std::string, size_t> pending_parents;
    for (const std::string& class_name: class_names)
    {
        const std::map<std::string, std::string>::const_iterator parent_iter =
            parents.find(class_name);
        if (parent_iter == parents.end())
        {
            continue;  // the root type is emitted separately
        }
        children[parent_iter->second].push_back(class_name);
        ++pending_parents[class_name];
    }

    std::vector<std::string> ordered_classes;
    ordered_classes.reserve(class_names.size());

    // `class_names` is sorted, so this queue is deterministic.
    std::vector<std::string> ready { std::string(root_class) };
    for (size_t next = 0; next < ready.size(); ++next)
    {
        const std::string& parent_name = ready[next];
        const std::map<std::string, std::vector<std::string>>::const_iterator child_iter =
            children.find(parent_name);
        if (child_iter == children.end())
        {
            continue;
        }
        for (const std::string& child_name: child_iter->second)
        {
            size_t& remaining = pending_parents[child_name];
            --remaining;
            if (remaining == 0)
            {
                ordered_classes.push_back(child_name);
                ready.push_back(child_name);
            }
        }
    }

    if (ordered_classes.size() + 1 != class_names.size())
    {
        const std::set<std::string> placed(ordered_classes.begin(), ordered_classes.end());
        for (const std::string& class_name: class_names)
        {
            if (class_name != root_class && !placed.contains(class_name))
            {
                std::println(stderr, "Fortran type tree: '{}' is unreachable from the root type",
                             class_name);
                ordered_classes.push_back(class_name);
            }
        }
    }

    return ordered_classes;
}

// Break inheritance cycles. Fortran rejects a circular type extension, and the parsed
// hierarchy is not guaranteed acyclic: a malformed input can make two classes each other's
// parent. Each cycle is broken at its lexicographically first member, which extends the root
// type instead, and the affected classes are reported.
static void BreakFortranParentCycles(std::map<std::string, std::string>& parents,
                                     std::string_view root_class)
{
    std::set<std::string> resolved;
    for (const std::pair<const std::string, std::string>& parent_entry: parents)
    {
        std::set<std::string> chain;
        std::string current = parent_entry.first;
        while (current != root_class)
        {
            if (chain.contains(current))
            {
                // `current` starts the cycle. Walk the cycle to find its first member.
                std::string first_member = current;
                std::string walker = parents.at(current);
                while (walker != current)
                {
                    first_member = std::min(first_member, walker);
                    walker = parents.at(walker);
                }
                if (resolved.contains(first_member))
                {
                    break;
                }
                resolved.insert(first_member);
                parents.insert_or_assign(first_member, std::string(root_class));
                std::println(stderr, "Fortran type tree: inheritance cycle broken at '{}'",
                             first_member);
                break;
            }
            chain.insert(current);
            const std::map<std::string, std::string>::const_iterator parent_iter =
                parents.find(current);
            if (parent_iter == parents.end())
            {
                break;
            }
            current = parent_iter->second;
        }
    }
}

// Emit the module function that wraps a raw C pointer in the matching derived type.
// `owned` is optional so a borrowed handle — the common case for getters — never deletes
// an object the C++ side still owns.
static void EmitFromPtr(std::ostream& output, const std::string& type_name)
{
    output << "    function " << type_name << "_from_ptr(ptr, owned) result(obj)\n";
    output << "        type(c_ptr), intent(in), value :: ptr\n";
    output << "        logical, intent(in), optional :: owned\n";
    output << "        type(" << type_name << "_t) :: obj\n";
    output << "        obj%ptr = ptr\n";
    output << "        if (present(owned)) obj%owned = owned\n";
    output << "    end function " << type_name << "_from_ptr\n\n";
}

void FortranEmitter::GenerateTypeTree(const ParsedFFI& ffi_data, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "kwx_types.f90");

    output << "! Code generated by kwxgen. DO NOT EDIT.\n";
    output << "module kwx_types\n";
    output << "    use, intrinsic :: iso_c_binding\n";
    output << "    implicit none\n";
    output << "    private\n\n";

    // Every class the model knows about: parsed classes, every parent named by the hierarchy,
    // and every mixin. A mixin is not itself instantiated by a consumer, but wrapper modules
    // take `class(<mixin>_t)` arguments, so the type must exist.
    const std::set<std::string> class_names = CollectFortranClassNames(ffi_data);

    const std::map<std::string, std::string> identifiers = BuildFortranTypeIdentifiers(class_names);

    // Resolve the type each class extends. An empty, self-referential, or unknown parent
    // extends the root type, which keeps a malformed hierarchy from producing invalid Fortran.
    std::map<std::string, std::string> parents;
    for (const std::string& class_name: class_names)
    {
        if (class_name == FORTRAN_ROOT_CLASS)
        {
            continue;
        }
        std::string parent_name;
        const std::unordered_map<std::string, std::string>::const_iterator parent_iter =
            ffi_data.parent_map.find(class_name);
        if (parent_iter != ffi_data.parent_map.end())
        {
            parent_name = parent_iter->second;
        }
        if (parent_name.empty() || parent_name == class_name || !class_names.contains(parent_name))
        {
            parent_name = std::string(FORTRAN_ROOT_CLASS);
        }
        parents.insert_or_assign(class_name, parent_name);
    }

    BreakFortranParentCycles(parents, FORTRAN_ROOT_CLASS);
    const std::vector<std::string> ordered_classes =
        TopologicalClassOrder(parents, class_names, FORTRAN_ROOT_CLASS);

    // The root type owns the handle fields; every other type inherits them.
    const std::string root_type = identifiers.at(std::string(FORTRAN_ROOT_CLASS));
    output << "    type, public :: " << root_type << "_t\n";
    output << "        type(c_ptr) :: ptr = c_null_ptr\n";
    output << "        logical :: owned = .false.\n";
    output << "    contains\n";
    output << "        procedure :: is_valid => " << root_type << "_is_valid\n";
    output << "    end type " << root_type << "_t\n\n";

    for (const std::string& class_name: ordered_classes)
    {
        const std::string& type_name = identifiers.at(class_name);
        const std::string& parent_type = identifiers.at(parents.at(class_name));
        output << "    type, extends(" << parent_type << "_t), public :: " << type_name << "_t\n";
        output << "    end type " << type_name << "_t\n\n";
    }

    // The type tree declares every handle builder public: a wrapper module in another file
    // calls `<class>_from_ptr` and would otherwise only see a private module procedure.
    for (const std::string& class_name: ordered_classes)
    {
        output << "    public :: " << identifiers.at(class_name) << "_from_ptr\n";
    }
    output << "    public :: " << root_type << "_from_ptr\n";
    output << "\n";

    output << "contains\n\n";

    output << "    pure logical function " << root_type << "_is_valid(self) result(valid)\n";
    output << "        class(" << root_type << "_t), intent(in) :: self\n";
    output << "        valid = c_associated(self%ptr)\n";
    output << "    end function " << root_type << "_is_valid\n\n";

    // One borrowed-or-owned handle builder per class. `owned` defaults to false, so a handle
    // returned by a getter never frees an object the C++ side still owns.
    EmitFromPtr(output, root_type);
    for (const std::string& class_name: ordered_classes)
    {
        EmitFromPtr(output, identifiers.at(class_name));
    }

    output << "end module kwx_types\n";
    std::println(stderr, "  Generated kwx_types.f90 ({} types)", ordered_classes.size() + 1);
}

// -------------------------------------------------------------------------
// wx_string.f90 — String conversion utilities
// -------------------------------------------------------------------------

void FortranEmitter::GenerateStringModule(const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_string.f90");

    // wxString_Delete is NOT declared here. The raw `kwxffi` module already provides it
    // (generated from include/kwx_classes.h), and every wrapper module does `use kwxffi`.
    // Declaring a second module procedure with that name makes any scope that imports both
    // ambiguous, so this module re-exports the kwxffi entity instead and offers the
    // null-resetting convenience as wx_string_delete.
    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_string
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi, only: wxString_Delete, kwxFree
    implicit none
    private

    public :: to_wxstring, from_wxstring, from_cstring, free_cstring, wx_string_delete, &
        wxString_Delete

    interface
        function wxString_CreateUTF8(str) bind(C, name="wxString_CreateUTF8")
            import :: c_ptr, c_char
            character(kind=c_char), dimension(*), intent(in) :: str
            type(c_ptr) :: wxString_CreateUTF8
        end function

        function wxString_GetString(wx_str, buffer) bind(C, name="wxString_GetString")
            import :: c_ptr, c_int
            type(c_ptr), value :: wx_str
            type(c_ptr), value :: buffer
            integer(c_int) :: wxString_GetString
        end function

        ! A TString is a bare char*, so its length comes from the C library rather than from
        ! an FFI accessor.
        function c_strlen(str) bind(C, name="strlen")
            import :: c_ptr, c_size_t
            type(c_ptr), value :: str
            integer(c_size_t) :: c_strlen
        end function
    end interface

contains

    function to_wxstring(fstring) result(ptr)
        character(len=*), intent(in) :: fstring
        type(c_ptr) :: ptr
        character(kind=c_char, len=:), allocatable :: cstr

        cstr = trim(fstring) // c_null_char
        ptr = wxString_CreateUTF8(cstr)
    end function to_wxstring

    function from_wxstring(wx_str_ptr) result(fstring)
        type(c_ptr), intent(in) :: wx_str_ptr
        character(len=:), allocatable :: fstring
        integer(c_int) :: slen, i
        character(kind=c_char), dimension(:), allocatable, target :: buffer
        type(c_ptr) :: buf_ptr

        if (.not. c_associated(wx_str_ptr)) then
            fstring = ""
            return
        end if

        slen = wxString_GetString(wx_str_ptr, c_null_ptr)
        if (slen <= 0) then
            fstring = ""
            return
        end if

        allocate(buffer(slen + 1))
        buf_ptr = c_loc(buffer(1))
        slen = wxString_GetString(wx_str_ptr, buf_ptr)

        allocate(character(len=slen) :: fstring)
        do i = 1, slen
            fstring(i:i) = buffer(i)
        end do
    end function from_wxstring

    ! Copies a NUL-terminated UTF-8 C string into a Fortran string. The pointer is NOT freed:
    ! the FFI does not state whether a TString result is strdup()ed or borrowed. Use
    ! free_cstring() on the raw pointer when the C function documents caller ownership.
    function from_cstring(cstr) result(fstring)
        type(c_ptr), intent(in) :: cstr
        character(len=:), allocatable :: fstring
        character(kind=c_char), dimension(:), pointer :: chars
        integer(c_size_t) :: slen
        integer :: idx

        fstring = ""
        if (.not. c_associated(cstr)) return

        slen = c_strlen(cstr)
        if (slen <= 0) return

        allocate(character(len=int(slen)) :: fstring)
        call c_f_pointer(cstr, chars, [int(slen)])
        do idx = 1, int(slen)
            fstring(idx:idx) = chars(idx)
        end do
    end function from_cstring

    ! Releases a string buffer the C side allocated with malloc()/strdup() and clears the
    ! caller's pointer so a stale handle cannot survive the call.
    subroutine free_cstring(cstr)
        type(c_ptr), intent(inout) :: cstr
        if (c_associated(cstr)) then
            call kwxFree(cstr)
            cstr = c_null_ptr
        end if
    end subroutine free_cstring

    ! Frees wx_str_ptr and clears it. The re-exported kwxffi wxString_Delete takes its
    ! argument by value, so it cannot null the caller's pointer; use this when a stale
    ! handle must not survive the call.
    subroutine wx_string_delete(wx_str_ptr)
        type(c_ptr), intent(inout) :: wx_str_ptr
        if (c_associated(wx_str_ptr)) then
            call wxString_Delete(wx_str_ptr)
            wx_str_ptr = c_null_ptr
        end if
    end subroutine wx_string_delete

end module wx_string
)";
    std::println(stderr, "  Generated wx_string.f90");
}

// -------------------------------------------------------------------------
// wx_events.f90 — Event connection and accessor wrappers
// -------------------------------------------------------------------------

void FortranEmitter::GenerateEventsModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_events.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_events
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    use wx_string, only: from_wxstring
    implicit none
    private

    ! Connection
    public :: wx_bind, wx_unbind, wx_connect, wx_disconnect

    ! Base event accessors
    public :: wx_event_get_id, wx_event_get_type, wx_event_skip
    public :: wx_event_get_timestamp, wx_event_get_skipped
    public :: wx_event_is_command_event

    ! Command event accessors
    public :: wx_command_event_get_string
    public :: wx_command_event_get_selection
    public :: wx_command_event_get_int
    public :: wx_command_event_get_extra_long
    public :: wx_command_event_is_checked
    public :: wx_command_event_is_selection

    ! Abstract callback interface
    public :: event_callback

    abstract interface
        subroutine event_callback(fun, data, evt) bind(C)
            import :: c_ptr
            type(c_ptr), value :: fun, data, evt
        end subroutine event_callback
    end interface

contains

    !--- Connection ---

    subroutine wx_connect(window, event_type, handler, user_data, id, last_id)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in) :: event_type
        procedure(event_callback) :: handler
        type(c_ptr), intent(in), optional :: user_data
        integer, intent(in), optional :: id
        integer, intent(in), optional :: last_id

        type(c_funptr) :: fptr
        type(c_ptr) :: data_ptr
        integer(c_int) :: c_first, c_last, c_type, dummy

        fptr = c_funloc(handler)
        data_ptr = c_null_ptr
        if (present(user_data)) data_ptr = user_data
        c_first = -1_c_int
        if (present(id)) c_first = int(id, c_int)
        c_last = c_first
        if (present(last_id)) c_last = int(last_id, c_int)
        c_type = int(event_type, c_int)

        ! TClosureFun is void* in C, so the function pointer crosses as a c_ptr.
        dummy = wxEvtHandler_Connect(window%ptr, c_first, c_last, c_type, &
            wxClosure_Create(transfer(fptr, c_null_ptr), data_ptr))
    end subroutine

    subroutine wx_bind(window, event_type, handler, user_data, id, last_id)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in) :: event_type
        procedure(event_callback) :: handler
        type(c_ptr), intent(in), optional :: user_data
        integer, intent(in), optional :: id
        integer, intent(in), optional :: last_id

        type(c_funptr) :: fptr
        type(c_ptr) :: data_ptr
        integer(c_int) :: c_first, c_last, c_type, dummy

        fptr = c_funloc(handler)
        data_ptr = c_null_ptr
        if (present(user_data)) data_ptr = user_data
        c_first = -1_c_int
        if (present(id)) c_first = int(id, c_int)
        c_last = c_first
        if (present(last_id)) c_last = int(last_id, c_int)
        c_type = int(event_type, c_int)

        dummy = wxEvtHandler_Bind(window%ptr, c_first, c_last, c_type, &
            wxClosure_Create(transfer(fptr, c_null_ptr), data_ptr))
    end subroutine

    subroutine wx_unbind(window, event_type, id, last_id)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in) :: event_type
        integer, intent(in), optional :: id, last_id

        integer(c_int) :: c_first, c_last, c_type, dummy

        c_first = -1_c_int
        if (present(id)) c_first = int(id, c_int)
        c_last = c_first
        if (present(last_id)) c_last = int(last_id, c_int)
        c_type = int(event_type, c_int)

        dummy = wxEvtHandler_Unbind(window%ptr, c_first, c_last, c_type)
    end subroutine

    subroutine wx_disconnect(window, event_type, id, last_id)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in) :: event_type
        integer, intent(in), optional :: id, last_id

        integer(c_int) :: c_first, c_last, c_type, dummy

        c_first = -1_c_int
        if (present(id)) c_first = int(id, c_int)
        c_last = c_first
        if (present(last_id)) c_last = int(last_id, c_int)
        c_type = int(event_type, c_int)

        dummy = wxEvtHandler_Disconnect(window%ptr, c_first, c_last, &
            c_type, -1_c_int)
    end subroutine

    !--- Base event accessors ---

    function wx_event_get_id(evt) result(id)
        type(c_ptr), intent(in) :: evt
        integer :: id
        id = 0
        if (.not. c_associated(evt)) return
        id = int(wxEvent_GetId(evt))
    end function

    function wx_event_get_type(evt) result(etype)
        type(c_ptr), intent(in) :: evt
        integer :: etype
        etype = 0
        if (.not. c_associated(evt)) return
        etype = int(wxEvent_GetEventType(evt))
    end function

    subroutine wx_event_skip(evt, skip)
        type(c_ptr), intent(in) :: evt
        logical, intent(in), optional :: skip
        integer(c_int) :: c_skip
        if (.not. c_associated(evt)) return
        c_skip = 1_c_int
        if (present(skip)) then
            c_skip = 0_c_int
            if (skip) c_skip = 1_c_int
        end if
        call wxEvent_Skip(evt, c_skip)
    end subroutine

    function wx_event_get_timestamp(evt) result(ts)
        type(c_ptr), intent(in) :: evt
        integer :: ts
        ts = 0
        if (.not. c_associated(evt)) return
        ts = int(wxEvent_GetTimestamp(evt))
    end function

    function wx_event_get_skipped(evt) result(skipped)
        type(c_ptr), intent(in) :: evt
        logical :: skipped
        skipped = .false.
        if (.not. c_associated(evt)) return
        skipped = (wxEvent_GetSkipped(evt) /= 0)
    end function

    function wx_event_is_command_event(evt) result(is_cmd)
        type(c_ptr), intent(in) :: evt
        logical :: is_cmd
        is_cmd = .false.
        if (.not. c_associated(evt)) return
        is_cmd = (wxEvent_IsCommandEvent(evt) /= 0)
    end function

    !--- Command event accessors ---

    function wx_command_event_get_string(evt) result(str)
        type(c_ptr), intent(in) :: evt
        character(len=:), allocatable :: str
        type(c_ptr) :: ws_ptr
        if (.not. c_associated(evt)) then
            str = ""
            return
        end if
        ws_ptr = wxCommandEvent_GetString(evt)
        str = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    function wx_command_event_get_selection(evt) result(sel)
        type(c_ptr), intent(in) :: evt
        integer :: sel
        sel = -1
        if (.not. c_associated(evt)) return
        sel = int(wxCommandEvent_GetSelection(evt))
    end function

    function wx_command_event_get_int(evt) result(val)
        type(c_ptr), intent(in) :: evt
        integer :: val
        val = 0
        if (.not. c_associated(evt)) return
        val = int(wxCommandEvent_GetInt(evt))
    end function

    function wx_command_event_get_extra_long(evt) result(val)
        type(c_ptr), intent(in) :: evt
        integer :: val
        val = 0
        if (.not. c_associated(evt)) return
        val = int(wxCommandEvent_GetExtraLong(evt))
    end function

    function wx_command_event_is_checked(evt) result(checked)
        type(c_ptr), intent(in) :: evt
        logical :: checked
        checked = .false.
        if (.not. c_associated(evt)) return
        checked = (wxCommandEvent_IsChecked(evt) /= 0)
    end function

    function wx_command_event_is_selection(evt) result(is_sel)
        type(c_ptr), intent(in) :: evt
        logical :: is_sel
        is_sel = .false.
        if (.not. c_associated(evt)) return
        is_sel = (wxCommandEvent_IsSelection(evt) /= 0)
    end function

end module wx_events
)";
    std::println(stderr, "  Generated wx_events.f90");
}

// -------------------------------------------------------------------------
// Per-class wrapper modules
// -------------------------------------------------------------------------

// The index of the first parameter that is not the receiver. A leading TSelf(...) or a
// leading TClass(OwnClass) is the receiver and must not become a dummy argument.
[[nodiscard]] static std::size_t FortranReceiverParamCount(const FunctionDecl& func)
{
    if (func.params.empty())
    {
        return 0;
    }
    const Param& first_param = func.params.front();
    if (first_param.macro_name == "TSelf")
    {
        return 1;
    }
    if (first_param.macro_name == "TClass" && first_param.macro_arg == func.class_name)
    {
        return 1;
    }
    return 0;
}

// True when a FunctionDecl is an instance method rather than a factory. A TBool-returning
// Create() still takes a TSelf receiver and so belongs to the instance-method path; a
// Create() with a leading TClass(OwnClass) argument constructs an already allocated object
// and is also an instance method. Only a Create() with neither receiver form is a factory.
[[nodiscard]] static bool IsFortranInstanceMethod(const FunctionDecl& func)
{
    if (!func.is_constructor)
    {
        return true;
    }
    return func.has_self || FortranReceiverParamCount(func) > 0;
}

// A constructor must be a factory AND declare a class return. A function whose C declaration
// carries no return type (for example wxSingleInstanceChecker_Create) parses as an integer and
// must not be treated as a constructor, or its result would be assigned to a handle field.
[[nodiscard]] static bool IsFortranConstructor(const FunctionDecl& func)
{
    if (!func.is_constructor || IsFortranInstanceMethod(func))
    {
        return false;
    }
    return func.return_macro == "TClass" || func.return_macro == "TClassRef" || func.returns_owned;
}

// True when the only parameter a destructor declares is its receiver.
[[nodiscard]] static bool IsFortranDestructor(const FunctionDecl& func)
{
    return func.is_destructor && func.params.size() == FortranReceiverParamCount(func);
}

// A single wrapper procedure ready to be written into its class module.
struct FortranWrapperProcedure
{
    std::string identifier;
    std::string base_identifier;  // identifier before the uniqueness suffix
    std::string signature;        // type-only dummy list, used to detect ambiguous overloads
    std::string identity;         // full dummy declaration identity, redundant-duplicate key
    std::string text;
    bool is_constructor = false;
    bool is_destructor = false;
    bool is_function = false;
};

// State while a single class module is being built.
struct FortranClassModuleState
{
    std::string class_name;
    std::string module_name;
    std::string type_name;
    std::vector<std::string> public_names;
    std::vector<FortranWrapperProcedure> procedures;
    std::set<std::string> used_identifiers;
    bool uses_to_wxstring = false;
    bool uses_from_wxstring = false;
    bool uses_from_cstring = false;
    std::size_t deduplicated_count = 0;
};

// Make an identifier unique and no longer than the Fortran limit.
[[nodiscard]] static std::string MakeFortranIdentifierUnique(const std::string& identifier,
                                                             std::set<std::string>& used)
{
    std::string candidate = identifier;
    for (std::size_t ordinal = 2; used.contains(candidate); ++ordinal)
    {
        const std::string suffix = "_" + std::to_string(ordinal);
        candidate = identifier;
        if (candidate.size() + suffix.size() > FORTRAN_IDENTIFIER_LIMIT)
        {
            candidate.resize(FORTRAN_IDENTIFIER_LIMIT - suffix.size());
        }
        candidate += suffix;
    }
    used.insert(candidate);
    return candidate;
}

// Convert a scalar C type to its Fortran declaration. Returns false when the type is not a
// plain scalar, so the caller falls back to the raw ISO_C_BINDING expansion.
[[nodiscard]] static bool FortranScalarDeclaration(const std::string& raw_type,
                                                   std::string& declaration,
                                                   std::string& argument_expression,
                                                   const std::string& name)
{
    if (raw_type.empty() || raw_type == "int" || raw_type == "unsigned" ||
        raw_type == "unsigned int" || raw_type == "TBoolInt" || raw_type == "TUInt" ||
        raw_type == "TUInt16" || raw_type == "TUInt32" || raw_type == "TArrayLen" ||
        raw_type == "TByteStringLen")
    {
        declaration = "integer(c_int), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "unsigned short")
    {
        declaration = "integer(c_short), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "intptr_t" || raw_type == "TIntPtr")
    {
        declaration = "integer(c_intptr_t), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "long" || raw_type == "unsigned long")
    {
        declaration = "integer(c_long), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "size_t" || raw_type == "wxUIntPtr" || raw_type == "uintptr_t")
    {
        declaration = "integer(c_size_t), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "time_t" || raw_type == "TInt64" || raw_type == "int64_t")
    {
        declaration = "integer(c_int64_t), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "double")
    {
        declaration = "real(c_double), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "float")
    {
        declaration = "real(c_float), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "TChar")
    {
        declaration = "character(c_char), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "TUInt8" || raw_type == "unsigned char")
    {
        declaration = "integer(c_int8_t), intent(in) :: " + name;
        argument_expression = name;
        return true;
    }
    if (raw_type == "TBool")
    {
        declaration = "logical, intent(in) :: " + name;
        argument_expression = "merge(1_c_int, 0_c_int, " + name + ")";
        return true;
    }
    return false;
}

// Fortran type of the pointee behind a scalar-pointer macro. Fortran has no unsigned
// integer, so T*Out and TUIntOut share integer(c_int) exactly as their value parameters do.
[[nodiscard]] static std::string FortranScalarPointerType(const std::string& c_type)
{
    if (c_type == "long" || c_type == "unsigned long")
    {
        return "integer(c_long)";
    }
    if (c_type == "double")
    {
        return "real(c_double)";
    }
    return "integer(c_int)";
}

// True when a parameter is a scalar length argument for a neighbouring buffer. A TStringOut
// parameter can only be exposed as a Fortran character buffer when the C declaration also
// names the buffer length; otherwise the caller has to own a raw C buffer.
[[nodiscard]] static bool HasFortranLengthSibling(const FunctionDecl& func,
                                                  std::size_t receiver_params)
{
    for (std::size_t param_index = receiver_params; param_index < func.params.size(); ++param_index)
    {
        const Param& sibling = func.params[param_index];
        if (ClassifyFortranParam(sibling) != FortranParamKind::scalar)
        {
            continue;
        }
        const std::string sibling_name = ToLower(sibling.param_name);
        if (sibling_name.contains("size") || sibling_name.contains("len"))
        {
            return true;
        }
    }
    return false;
}

// Type-only key for one dummy argument. Fortran resolves a generic interface on dummy types
// and ranks, never on names or intent, so two specifics agreeing here would be ambiguous.
//
// `integer(c_long)` is folded into `integer(c_int)` because the two are the same kind on the
// Windows ABIs this binding targets (LLP64, where long is 4 bytes); keeping them distinct
// would emit a generic that gfortran rejects as ambiguous. The cost is that a long/int
// overload set is not collected into a generic there, which is safe: both specifics stay
// callable under their own names.
[[nodiscard]] static std::string FortranDummySignatureKey(const std::string& declaration)
{
    const std::size_t name_pos = declaration.rfind(" :: ");
    std::string key = declaration.substr(0, name_pos);
    const std::size_t comma_pos = key.find(',');
    if (comma_pos != std::string::npos)
    {
        key.resize(comma_pos);
    }
    std::size_t search_pos = 0;
    while ((search_pos = key.find("c_long", search_pos)) != std::string::npos)
    {
        key.replace(search_pos, std::string("c_long").size(), "c_int");
        search_pos += std::string("c_int").size();
    }
    if (declaration.contains("(:)") || declaration.contains("dimension("))
    {
        key += "(:)";
    }
    return key;
}

// Full dummy declaration with the dummy name removed. Two procedures that agree on this for
// every dummy (same types, intents and attributes, in the same order) are the same Fortran
// procedure: a class method also emitted for a mixin it overrides, or one operation declared
// under a second C symbol. Only one of them is emitted.
[[nodiscard]] static std::string FortranDummyIdentityKey(const std::string& declaration)
{
    const std::size_t name_pos = declaration.rfind(" :: ");
    return name_pos == std::string::npos ? declaration : declaration.substr(0, name_pos);
}

// Build the wrapper procedure for one model method. `self_type` is the type the receiver is
// declared as, which is the consumer class for a mixin method. `is_mixin_method` is true when
// the method comes from a mixin, which allows the folded-signature duplicate rule below.
static void BuildFortranWrapperProcedure(FortranClassModuleState& state, const FunctionDecl& func,
                                         const std::string& self_type,
                                         const std::map<std::string, std::string>& type_names,
                                         bool is_mixin_method)
{
    const std::string c_function = CFuncName(func);
    const std::size_t receiver_params = FortranReceiverParamCount(func);
    // Some functions are attached to a class by their C prefix but declare no receiver (a static
    // helper such as wxColour_ValidName or wxComboCtrl_GetFeatures). Only emit `self` when the
    // model actually declares one, otherwise the call would pass an extra argument.
    const bool has_receiver = receiver_params > 0;
    const bool is_constructor = IsFortranConstructor(func);
    const bool is_destructor = IsFortranDestructor(func);
    const bool has_buffer_length = HasFortranLengthSibling(func, receiver_params);

    // Ordinal counts earlier same-named methods in this module so overloads get distinct
    // identifiers while remaining deterministic.
    std::string base_identifier;
    if (is_destructor)
    {
        base_identifier = FortranSanitizeIdentifier(ToSnakeCase(state.class_name), 40) + "_delete";
    }
    else
    {
        base_identifier = FortranMethodIdentifier(state.class_name, func.method_name, 1);
    }

    const std::string receiver_name = "self";
    // Method parameters occasionally include a C parameter literally named `self`; make the
    // generated dummy names unique so the receiver and that parameter can coexist.
    std::set<std::string> dummy_names { receiver_name };
    std::vector<std::string> dummy_declarations;
    std::vector<std::string> call_arguments;
    std::vector<std::string> local_declarations;
    std::vector<std::string> setup_statements;
    std::vector<std::string> cleanup_statements;

    const auto make_dummy_name = [&dummy_names](const std::string& base_name)
    {
        return MakeFortranIdentifierUnique(FortranSanitizeIdentifier(base_name, 40), dummy_names);
    };

    if (!is_constructor && has_receiver)
    {
        dummy_declarations.push_back("class(" + self_type + "), intent(" +
                                     std::string(is_destructor ? "inout" : "in") +
                                     ") :: " + receiver_name);
        call_arguments.push_back(receiver_name + "%ptr");
    }

    for (std::size_t param_index = receiver_params; param_index < func.params.size(); ++param_index)
    {
        const Param& param = func.params[param_index];
        const std::string base_name =
            make_dummy_name(param.param_name.empty() ? "arg" : param.param_name);
        const FortranParamKind kind = ClassifyFortranParam(param);

        if (kind == FortranParamKind::string_input)
        {
            dummy_declarations.push_back("character(len=*), intent(in) :: " + base_name);
            if (param.raw_type == "TString")
            {
                // A bare TString is a UTF-8 C string, not a wxString handle: copy it into a
                // NUL-terminated buffer and pass the address, because the raw kwxffi
                // interface declares the argument as type(c_ptr). The buffer is allocatable,
                // so it is released automatically when the procedure returns.
                const std::string buffer_name = base_name + "_c";
                local_declarations.push_back(
                    "character(kind=c_char, len=:), allocatable, target :: " + buffer_name);
                setup_statements.push_back(buffer_name + " = trim(" + base_name +
                                           ") // c_null_char");
                call_arguments.push_back("c_loc(" + buffer_name + ")");
            }
            else
            {
                const std::string pointer_name = base_name + "_ptr";
                local_declarations.push_back("type(c_ptr) :: " + pointer_name);
                setup_statements.push_back(pointer_name + " = to_wxstring(" + base_name + ")");
                cleanup_statements.push_back("call wxString_Delete(" + pointer_name + ")");
                call_arguments.push_back(pointer_name);
                state.uses_to_wxstring = true;
            }
            continue;
        }

        if (kind == FortranParamKind::string_output)
        {
            if (has_buffer_length)
            {
                // The C declaration names the buffer length, so a Fortran character array is
                // the complete contract: the caller sizes it and passes the length alongside.
                dummy_declarations.push_back(
                    "character(kind=c_char), dimension(:), intent(out), target, contiguous :: " +
                    base_name);
                call_arguments.push_back("c_loc(" + base_name + ")");
            }
            else
            {
                // Without a length in the C declaration the caller cannot prove the buffer
                // size, so hand back an untyped pointer it allocates itself.
                dummy_declarations.push_back("type(c_ptr), intent(out) :: " + base_name);
                call_arguments.push_back(base_name);
            }
            continue;
        }

        if (kind == FortranParamKind::string_array_input)
        {
            // TArrayString(n, p) is `int n, TString *p` — an array of C string pointers. Build
            // one NUL-terminated buffer per element, collect their addresses, and pass the
            // count plus the address of the pointer array.
            const std::string count_name = base_name + "_count";
            const std::string index_name = base_name + "_index";
            const std::string length_name = base_name + "_maxlen";
            const std::string buffer_name = base_name + "_buffer";
            const std::string pointers_name = base_name + "_ptrs";

            dummy_declarations.push_back("character(len=*), intent(in) :: " + base_name + "(:)");
            local_declarations.push_back("integer :: " + count_name + ", " + index_name + ", " +
                                         length_name);
            local_declarations.push_back(
                "character(kind=c_char, len=:), allocatable, target :: " + buffer_name + "(:)");
            local_declarations.push_back("type(c_ptr), allocatable, target :: " + pointers_name +
                                         "(:)");

            setup_statements.push_back(count_name + " = int(size(" + base_name + "), c_int)");
            setup_statements.push_back(length_name + " = 1");
            setup_statements.push_back("if (" + count_name + " > 0) " + length_name +
                                       " = maxval(len_trim(" + base_name + ")) + 1");
            // Always allocate at least one element: c_loc() is undefined for an unallocated
            // allocatable, and a zero-length array would pass an invalid address.
            setup_statements.push_back("allocate(character(len=" + length_name +
                                       ") :: " + buffer_name + "(max(1, " + count_name + ")))");
            setup_statements.push_back("allocate(" + pointers_name + "(max(1, " + count_name +
                                       ")))");
            setup_statements.push_back("do " + index_name + " = 1, " + count_name);
            setup_statements.push_back("    " + buffer_name + "(" + index_name + ") = trim(" +
                                       base_name + "(" + index_name + ")) // c_null_char");
            setup_statements.push_back("    " + pointers_name + "(" + index_name + ") = c_loc(" +
                                       buffer_name + "(" + index_name + "))");
            setup_statements.push_back("end do");

            call_arguments.push_back(count_name);
            call_arguments.push_back("c_loc(" + pointers_name + ")");
            continue;
        }

        if (kind == FortranParamKind::integer_array_input)
        {
            // TArrayInt(n, p) is `int n, int *p`, so the Fortran array can be passed directly
            // once it is known to be contiguous and addressable.
            dummy_declarations.push_back(
                "integer(c_int), intent(in), target, contiguous :: " + base_name + "(:)");
            call_arguments.push_back("int(size(" + base_name + "), c_int)");
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }

        if (kind == FortranParamKind::callback)
        {
            dummy_declarations.push_back("type(c_funptr), intent(in), value :: " + base_name);
            call_arguments.push_back(base_name);
            continue;
        }

        if (kind == FortranParamKind::opaque_pointer)
        {
            // A bare void* is a user-data slot or an untyped buffer. type(c_ptr) is the whole
            // type, so this is the complete mapping rather than a fallback.
            dummy_declarations.push_back("type(c_ptr), intent(in), value :: " + base_name);
            call_arguments.push_back(base_name);
            continue;
        }

        if (kind == FortranParamKind::byte_array_input)
        {
            dummy_declarations.push_back(
                "integer(c_int8_t), dimension(:), intent(in), target, contiguous :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::byte_array_output)
        {
            dummy_declarations.push_back(
                "integer(c_int8_t), dimension(:), intent(out), target, contiguous :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::byte_scalar_output)
        {
            dummy_declarations.push_back("integer(c_int8_t), intent(out), target :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::char_scalar_output)
        {
            dummy_declarations.push_back("character(kind=c_char), intent(out), target :: " +
                                         base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::int_array_input)
        {
            dummy_declarations.push_back(
                "integer(c_int), dimension(:), intent(in), target, contiguous :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::int_array_output)
        {
            dummy_declarations.push_back(
                "integer(c_int), dimension(:), intent(out), target, contiguous :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::intptr_array_output)
        {
            dummy_declarations.push_back(
                "integer(c_intptr_t), dimension(:), intent(out), target, contiguous :: " +
                base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::double_array_output)
        {
            dummy_declarations.push_back(
                "real(c_double), dimension(:), intent(out), target, contiguous :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::int_scalar_input ||
            kind == FortranParamKind::bool_scalar_input)
        {
            // The C function retains this pointer (wxGenericValidator stores it), so the
            // caller's storage must persist; INTENT(INOUT) documents that and forbids a
            // temporary copy.
            dummy_declarations.push_back("integer(c_int), intent(inout), target :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::cookie)
        {
            dummy_declarations.push_back("type(c_ptr), intent(inout), target :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }
        if (kind == FortranParamKind::string_array_output ||
            kind == FortranParamKind::object_array_output)
        {
            dummy_declarations.push_back("type(c_ptr), dimension(:), intent(out), target :: " +
                                         base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }

        if (kind == FortranParamKind::class_pointer || kind == FortranParamKind::self)
        {
            const std::map<std::string, std::string>::const_iterator type_iter =
                type_names.find(param.macro_arg);
            if (type_iter != type_names.end())
            {
                dummy_declarations.push_back("class(" + type_iter->second +
                                             "_t), intent(in) :: " + base_name);
                call_arguments.push_back(base_name + "%ptr");
                continue;
            }
            dummy_declarations.push_back("type(c_ptr), intent(in), value :: " + base_name);
            call_arguments.push_back(base_name);
            std::println(stderr,
                         "Fortran: {}.{} parameter '{}' uses an unknown class, "
                         "falling back to type(c_ptr)",
                         state.class_name, func.method_name, param.macro_arg);
            continue;
        }

        if (kind == FortranParamKind::geometry_output)
        {
            // int* outputs become individual scalars; c_loc() supplies the address the C
            // declaration expects. The *OutVoid spellings are the same thing as void*.
            std::string element_type = "integer(c_int)";
            if (param.macro_name == "TSizeOutDouble")
            {
                element_type = "real(c_double)";
            }
            else if (param.macro_name.ends_with("Long"))
            {
                element_type = "integer(c_long)";
            }
            for (const std::string& element: FortranSplitMacroArg(param.macro_arg))
            {
                const std::string element_name = make_dummy_name(element);
                dummy_declarations.push_back(element_type +
                                             ", intent(out), target :: " + element_name);
                call_arguments.push_back("c_loc(" + element_name + ")");
            }
            continue;
        }

        if (kind == FortranParamKind::scalar_output ||
            kind == FortranParamKind::scalar_input_output)
        {
            ScalarPointerInfo scalar_pointer;
            std::ignore = LookupScalarPointer(param, scalar_pointer);
            const std::string intent =
                (kind == FortranParamKind::scalar_input_output) ? "inout" : "out";
            if (scalar_pointer.c_type == "TBool" && kind == FortranParamKind::scalar_output)
            {
                // The C function writes an int. Expose a logical and convert after the call,
                // matching how TBool inputs are converted from logical.
                const std::string value_name = make_dummy_name(base_name + "_value");
                dummy_declarations.push_back("logical, intent(out) :: " + base_name);
                local_declarations.push_back("integer(c_int), target :: " + value_name);
                call_arguments.push_back("c_loc(" + value_name + ")");
                cleanup_statements.push_back(base_name + " = (" + value_name + " /= 0)");
                continue;
            }
            dummy_declarations.push_back(FortranScalarPointerType(scalar_pointer.c_type) +
                                         ", intent(" + intent + "), target :: " + base_name);
            call_arguments.push_back("c_loc(" + base_name + ")");
            continue;
        }

        if (kind == FortranParamKind::geometry)
        {
            std::string element_type = "integer(c_int)";
            if (param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
                param.macro_name == "TRectLong" || param.macro_name == "TVectorLong")
            {
                element_type = "integer(c_long)";
            }
            else if (param.macro_name == "TColorRGB")
            {
                element_type = "integer(c_int8_t)";
            }
            for (const std::string& element: FortranSplitMacroArg(param.macro_arg))
            {
                const std::string element_name = make_dummy_name(element);
                dummy_declarations.push_back(element_type + ", intent(in) :: " + element_name);
                call_arguments.push_back(element_name);
            }
            continue;
        }

        if (kind == FortranParamKind::scalar)
        {
            std::string declaration;
            std::string argument_expression;
            if (FortranScalarDeclaration(param.raw_type, declaration, argument_expression,
                                         base_name))
            {
                dummy_declarations.push_back(declaration);
                call_arguments.push_back(argument_expression);
                continue;
            }
        }

        // Unsupported shape: reuse the raw ISO_C_BINDING expansion so the call still matches
        // the kwxffi interface exactly, and report the loss of type information once per method.
        for (const FortranParam& raw_param: ExpandParamToFortran(param))
        {
            const std::string raw_name = make_dummy_name(raw_param.name);
            dummy_declarations.push_back(
                raw_param.fortran_type +
                (raw_param.pass_by_value ? ", intent(in), value" : ", intent(in)") +
                " :: " + raw_name);
            call_arguments.push_back(raw_name);
        }
        std::println(stderr, "Fortran: {}.{} parameter '{}' ({}) falls back to type(c_ptr)",
                     state.class_name, func.method_name, base_name,
                     param.raw_type.empty() ? std::string("unknown") : param.raw_type);
    }

    // Return handling. TBool becomes logical, TClass(wxString) and TString become Fortran
    // strings, a known class becomes its wrapper type, and everything else keeps the
    // ISO_C_BINDING type.
    bool returns_value = !func.return_type.empty() && func.return_type != "void";
    std::string result_declaration;
    std::string result_assignment;
    std::string result_name = "result_value";
    bool result_is_string = false;
    bool result_is_cstring = false;
    bool result_is_wrapper = false;

    if (is_constructor)
    {
        returns_value = true;
        result_name = make_dummy_name("result_object");
        result_declaration = "type(" + state.type_name + ") :: " + result_name;
    }
    else if (returns_value)
    {
        const bool returns_class =
            func.return_macro == "TClass" || func.return_macro == "TClassRef";
        if (func.return_type == "TString")
        {
            // TString is a NUL-terminated UTF-8 C string, so copy it into a Fortran string.
            // Ownership of the C buffer is not declared by the FFI (some exports strdup()
            // and some return an internal buffer), so the pointer is deliberately not freed;
            // wx_string::free_cstring() lets a caller release it when it knows the contract.
            result_is_cstring = true;
            result_name = make_dummy_name("result_text");
            result_declaration = "character(len=:), allocatable :: " + result_name;
            local_declarations.push_back("type(c_ptr) :: " + result_name + "_ptr");
            state.uses_from_cstring = true;
        }
        else if (returns_class && func.return_arg == "wxString")
        {
            result_is_string = true;
            result_name = make_dummy_name("result_text");
            result_declaration = "character(len=:), allocatable :: " + result_name;
            local_declarations.push_back("type(c_ptr) :: " + result_name + "_ptr");
            state.uses_from_wxstring = true;
        }
        else if (returns_class)
        {
            const std::map<std::string, std::string>::const_iterator type_iter =
                type_names.find(func.return_arg);
            if (type_iter != type_names.end())
            {
                result_name = make_dummy_name("result_object");
                result_is_wrapper = true;
                result_declaration = "type(" + type_iter->second + "_t) :: " + result_name;
            }
            else
            {
                result_name = "result_value";
                result_declaration = "type(c_ptr) :: result_value";
                std::println(stderr,
                             "Fortran: {}.{} returns an unknown class '{}', falling back to "
                             "type(c_ptr)",
                             state.class_name, func.method_name, func.return_arg);
            }
        }
        else if (func.return_type == "TBool" || func.return_type == "TBoolInt")
        {
            result_declaration = "logical :: result_value";
        }
        else
        {
            const FortranReturnInfo return_info =
                FortranReturnType(func.return_type, func.return_macro);
            result_declaration = return_info.fortran_type + " :: result_value";
        }
    }

    // Drop a wrapper that repeats a procedure already emitted for this module: same method
    // name and same dummy declarations, or a mixin overload that only differs in a C type
    // that folds to the same Fortran type (int vs long). The first occurrence (the class's
    // own method) wins; a Fortran caller cannot tell the copies apart.
    std::string identity;
    std::string signature;
    for (const std::string& declaration: dummy_declarations)
    {
        identity += FortranDummyIdentityKey(declaration);
        identity += ";";
        signature += FortranDummySignatureKey(declaration);
        signature += ";";
    }
    for (const FortranWrapperProcedure& existing: state.procedures)
    {
        if (existing.base_identifier != base_identifier || existing.is_function != returns_value)
        {
            continue;
        }
        if (existing.identity == identity || (is_mixin_method && existing.signature == signature))
        {
            ++state.deduplicated_count;
            return;
        }
    }

    const std::string identifier =
        MakeFortranIdentifierUnique(base_identifier, state.used_identifiers);

    // Assemble the call expression.
    std::string call_expression = c_function + "(";
    for (std::size_t arg_index = 0; arg_index < call_arguments.size(); ++arg_index)
    {
        if (arg_index > 0)
        {
            call_expression += ", ";
        }
        call_expression += call_arguments[arg_index];
    }
    call_expression += ")";

    if (is_constructor)
    {
        result_assignment = result_name + "%ptr = " + call_expression + "\n        " + result_name +
                            "%owned = .true.";
    }
    else if (returns_value && result_is_cstring)
    {
        result_assignment = result_name + "_ptr = " + call_expression + "\n        " + result_name +
                            " = from_cstring(" + result_name + "_ptr)";
    }
    else if (returns_value && result_is_string)
    {
        result_assignment = result_name + "_ptr = " + call_expression + "\n        " + result_name +
                            " = from_wxstring(" + result_name +
                            "_ptr)\n        call wxString_Delete(" + result_name + "_ptr)";
    }
    else if (returns_value && result_is_wrapper)
    {
        const std::string owned_flag = func.returns_owned ? ".true." : ".false.";
        result_assignment = result_name + " = " + type_names.at(func.return_arg) + "_from_ptr(" +
                            call_expression + ", " + owned_flag + ")";
    }
    else if (returns_value && result_declaration.starts_with("logical"))
    {
        result_assignment = result_name + " = (" + call_expression + " /= 0)";
    }
    else if (returns_value)
    {
        result_assignment = result_name + " = " + call_expression;
    }

    // Emit the procedure.
    std::ostringstream text;
    std::string argument_list;
    for (const std::string& declaration: dummy_declarations)
    {
        const std::size_t name_pos = declaration.rfind(" :: ");
        // A dummy argument list carries only the name: an array spec such as `x(:)` belongs
        // in the declaration, not in the list, or the line parses as a malformed definition.
        std::string dummy_name = declaration.substr(name_pos + 4);
        const std::size_t shape_pos = dummy_name.find('(');
        if (shape_pos != std::string::npos)
        {
            dummy_name.resize(shape_pos);
        }
        argument_list += (argument_list.empty() ? "" : ", ") + dummy_name;
    }

    if (!returns_value)
    {
        text << "    subroutine " << identifier << "(" << argument_list << ")\n";
        for (const std::string& declaration: dummy_declarations)
        {
            text << "        " << declaration << "\n";
        }
        for (const std::string& declaration: local_declarations)
        {
            text << "        " << declaration << "\n";
        }
        for (const std::string& statement: setup_statements)
        {
            text << "        " << statement << "\n";
        }
        if (is_destructor)
        {
            text << "        if (self%owned .and. c_associated(self%ptr)) then\n";
            text << "            call " << call_expression << "\n";
            text << "        end if\n";
            text << "        self%ptr = c_null_ptr\n";
            text << "        self%owned = .false.\n";
        }
        else
        {
            text << "        call " << call_expression << "\n";
        }
        for (const std::string& statement: cleanup_statements)
        {
            text << "        " << statement << "\n";
        }
        text << "    end subroutine " << identifier << "\n";
    }
    else
    {
        text << "    function " << identifier << "(" << argument_list << ") result(" << result_name
             << ")\n";
        for (const std::string& declaration: dummy_declarations)
        {
            text << "        " << declaration << "\n";
        }
        for (const std::string& declaration: local_declarations)
        {
            text << "        " << declaration << "\n";
        }
        text << "        " << result_declaration << "\n";
        for (const std::string& statement: setup_statements)
        {
            text << "        " << statement << "\n";
        }
        text << "        " << result_assignment << "\n";
        for (const std::string& statement: cleanup_statements)
        {
            text << "        " << statement << "\n";
        }
        text << "    end function " << identifier << "\n";
    }

    FortranWrapperProcedure procedure;
    procedure.identifier = identifier;
    procedure.base_identifier = base_identifier;
    procedure.identity = std::move(identity);
    procedure.signature = std::move(signature);
    procedure.text = text.str();
    procedure.is_constructor = is_constructor;
    procedure.is_destructor = is_destructor;
    procedure.is_function = returns_value;
    state.procedures.push_back(std::move(procedure));
    state.public_names.push_back(identifier);
}

// Collect the valid methods a class module exposes: the class's own methods plus every mixin
// method. The C function name dedupe key prevents a duplicate wrapper for the same symbol.
static void CollectFortranClassProcedures(FortranClassModuleState& state,
                                          const ClassInfo& class_info, const ParsedFFI& ffi_data,
                                          const std::map<std::string, std::string>& type_names,
                                          std::set<std::string>& emitted_c_functions)
{
    const auto emit_methods = [&](const ClassInfo& method_owner, bool is_mixin_method)
    {
        for (const FunctionDecl& method: method_owner.methods)
        {
            if (!IsValidFunction(method))
            {
                continue;
            }
            if (!emitted_c_functions.insert(CFuncName(method)).second)
            {
                ++state.deduplicated_count;
                continue;
            }
            BuildFortranWrapperProcedure(state, method, state.type_name, type_names,
                                         is_mixin_method);
        }
    };

    emit_methods(class_info, false);

    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        ffi_data.mixin_map.find(class_info.name);
    if (mixin_iter == ffi_data.mixin_map.end())
    {
        return;
    }
    for (const std::string& mixin_name: mixin_iter->second)
    {
        for (const ClassInfo& mixin_class: ffi_data.classes)
        {
            if (mixin_class.name == mixin_name)
            {
                emit_methods(mixin_class, true);
                break;
            }
        }
    }
}

// Build one generic interface per overload set. Fortran requires every specific of a generic
// to be the same kind (all functions or all subroutines), so the overload set is split on
// that first. Fortran also resolves a generic on the dummy types and ranks, so two specifics
// that agree on every dummy type cannot both be exposed under the base name: the first keeps
// the base name and the rest remain reachable only under their suffixed identifier. Exact
// duplicate wrappers are already dropped in BuildFortranWrapperProcedure, so reporting here
// only covers a pair that becomes ambiguous after the c_long/c_int folding.
[[nodiscard]] static std::string BuildFortranOverloadInterfaces(FortranClassModuleState& state)
{
    std::map<std::pair<std::string, bool>, std::vector<const FortranWrapperProcedure*>> groups;
    for (const FortranWrapperProcedure& procedure: state.procedures)
    {
        groups[std::make_pair(procedure.base_identifier, procedure.is_function)].push_back(
            &procedure);
    }

    std::set<std::string> public_names(state.public_names.begin(), state.public_names.end());
    std::ostringstream interfaces;
    for (const std::pair<const std::pair<std::string, bool>,
                         std::vector<const FortranWrapperProcedure*>>& group: groups)
    {
        if (group.second.size() < 2)
        {
            continue;
        }

        // The generic takes the first specific's name. That identifier is unique in the
        // module, so it cannot clash with a procedure from a different overload set.
        const std::string generic_name = group.second.front()->identifier;
        std::set<std::string> signatures;
        std::vector<std::string> specifics;
        for (const FortranWrapperProcedure* procedure: group.second)
        {
            if (!signatures.insert(procedure->signature).second)
            {
                std::println(stderr,
                             "Fortran: {}.{} overload has the same Fortran signature as an "
                             "earlier specific and is exposed only as '{}'",
                             state.class_name, group.first.first, procedure->identifier);
                continue;
            }
            specifics.push_back(procedure->identifier);
        }
        if (specifics.size() < 2)
        {
            continue;
        }

        interfaces << "    interface " << generic_name << "\n";
        for (const std::string& specific: specifics)
        {
            interfaces << "        module procedure " << specific << "\n";
        }
        interfaces << "    end interface\n\n";

        if (public_names.insert(generic_name).second)
        {
            state.public_names.push_back(generic_name);
        }
    }
    return interfaces.str();
}

void FortranEmitter::EmitClassModule(std::ostream& output, const ClassInfo& class_info,
                                     const ParsedFFI& ffi_data)
{
    const std::set<std::string> class_names = CollectFortranClassNames(ffi_data);
    const std::map<std::string, std::string> type_names = BuildFortranTypeIdentifiers(class_names);

    FortranClassModuleState state;
    state.class_name = class_info.name;
    state.module_name = FortranClassModuleName(class_info.name);
    state.type_name = type_names.at(class_info.name) + "_t";

    std::size_t own_method_count = 0;
    for (const FunctionDecl& method: class_info.methods)
    {
        if (IsValidFunction(method))
        {
            ++own_method_count;
        }
    }
    if (own_method_count == 0)
    {
        return;
    }

    std::set<std::string> emitted_c_functions;
    CollectFortranClassProcedures(state, class_info, ffi_data, type_names, emitted_c_functions);

    // Interfaces must be built before the public statements are written, because the builder
    // adds a public name for every generic it emits.
    const std::string interfaces = BuildFortranOverloadInterfaces(state);

    output << "! Code generated by kwxgen. DO NOT EDIT.\n";
    output << "module " << state.module_name << "\n";
    output << "    use, intrinsic :: iso_c_binding\n";
    output << "    use kwx_types\n";
    output << "    use kwxffi\n";

    std::vector<std::string> string_imports;
    if (state.uses_to_wxstring)
    {
        string_imports.emplace_back("to_wxstring");
    }
    if (state.uses_from_wxstring)
    {
        string_imports.emplace_back("from_wxstring");
    }
    if (state.uses_from_cstring)
    {
        string_imports.emplace_back("from_cstring");
    }
    if (!string_imports.empty())
    {
        output << "    use wx_string, only: ";
        for (std::size_t import_index = 0; import_index < string_imports.size(); ++import_index)
        {
            if (import_index > 0)
            {
                output << ", ";
            }
            output << string_imports[import_index];
        }
        output << "\n";
    }
    output << "    implicit none\n";
    output << "    private\n\n";

    for (const std::string& public_name: state.public_names)
    {
        output << "    public :: " << public_name << "\n";
    }
    output << interfaces;
    output << "\ncontains\n\n";

    for (const FortranWrapperProcedure& procedure: state.procedures)
    {
        output << procedure.text << "\n";
    }
    output << "end module " << state.module_name << "\n";
}

void FortranEmitter::GenerateClassModules(const ParsedFFI& ffi_data, const fs::path& outDir)
{
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(ffi_data);
    std::vector<std::string> ordered_classes(wrapped_classes.begin(), wrapped_classes.end());
    std::ranges::sort(ordered_classes);

    std::set<std::string> expected_files { "kwxffi_gen.f90", "kwx_types.f90", "wx_string.f90",
                                           "wx_events.f90" };

    size_t module_count = 0;
    std::set<std::string> generated_modules;
    for (const std::string& class_name: ordered_classes)
    {
        const ClassInfo* class_info = nullptr;
        for (const ClassInfo& candidate: ffi_data.classes)
        {
            if (candidate.name == class_name)
            {
                class_info = &candidate;
                break;
            }
        }
        if (class_info == nullptr)
        {
            continue;
        }

        bool has_valid_method = false;
        for (const FunctionDecl& method: class_info->methods)
        {
            if (IsValidFunction(method))
            {
                has_valid_method = true;
                break;
            }
        }
        if (!has_valid_method)
        {
            continue;
        }

        const std::string module_name = FortranClassModuleName(class_name);
        if (!generated_modules.insert(module_name).second)
        {
            std::println(stderr,
                         "Fortran: class '{}' maps to the already generated module '{}', skipped",
                         class_name, module_name);
            continue;
        }

        const fs::path module_path = outDir / (module_name + ".f90");
        {
            ConditionalFileWriter output(module_path);
            EmitClassModule(output, *class_info, ffi_data);
        }
        expected_files.insert(module_name + ".f90");
        ++module_count;
    }

    const std::size_t removed_count =
        RemoveStaleGeneratedFiles(outDir, expected_files, std::string_view(".f90"));
    if (removed_count > 0)
    {
        std::println(stderr, "  Removed {} stale generated file(s)", removed_count);
    }

    std::println(stderr, "  Generated {} class module(s)", module_count);
}
