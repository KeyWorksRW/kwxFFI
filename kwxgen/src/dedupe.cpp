/////////////////////////////////////////////////////////////////////////////
// Purpose:   Remove repeated C symbols from the parsed model
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "dedupe.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// The declaration's name in the C namespace. The constants parser records the symbol in
// method_name and leaves c_func_name empty, so fall back to the construction the language
// emitters use (lang_common.h: CFuncName).
[[nodiscard]] static std::string SymbolName(const FunctionDecl& func)
{
    if (!func.c_func_name.empty())
    {
        return func.c_func_name;
    }
    if (func.class_name.empty())
    {
        return func.method_name;
    }
    return func.class_name + "_" + func.method_name;
}

// Parameter names are not part of a C signature and need not match between two declarations
// of the same symbol, so compare types only.
[[nodiscard]] static std::string SignatureOf(const FunctionDecl& func)
{
    std::string signature = func.return_type;
    signature += '(';
    for (std::size_t index = 0; index < func.params.size(); ++index)
    {
        if (index != 0)
        {
            signature += ", ";
        }
        signature += func.params[index].raw_type;
    }
    signature += ')';
    return signature;
}

struct KeptDeclaration
{
    std::string owner;      // class name, or "free functions"
    std::string signature;  // return type and parameter types of the retained declaration
};

// Returns true when func is the first declaration of its symbol and should be kept.
// A repeat with a different signature is reported: dropping it silently would hide a real
// header inconsistency behind what looks like a harmless duplicate.
[[nodiscard]] static bool IsFirstDeclaration(const FunctionDecl& func, const std::string& owner,
                                             std::unordered_map<std::string, KeptDeclaration>& kept)
{
    const std::string symbol = SymbolName(func);
    if (symbol.empty())
    {
        // Malformed declaration — the emitters' IsValidFunction filter drops it later.
        return true;
    }

    const std::string signature = SignatureOf(func);
    const KeptDeclaration declaration { .owner = owner, .signature = signature };
    const auto [existing, was_inserted] = kept.try_emplace(symbol, declaration);
    if (was_inserted)
    {
        return true;
    }

    if (existing->second.signature != signature)
    {
        std::cerr << "  Warning: duplicate C symbol '" << symbol
                  << "' has conflicting declarations; keeping the one from '"
                  << existing->second.owner << "', ignoring the one from '" << owner << "'\n";
    }
    return false;
}

std::size_t RemoveDuplicateFunctions(ParsedFFI& ffi_data)
{
    std::unordered_map<std::string, KeptDeclaration> kept;
    std::size_t removed_count = 0;

    // Class methods run first so a class binding always outranks a plain free function with
    // the same symbol, regardless of the order the parsers produced them in.
    for (ClassInfo& class_info: ffi_data.classes)
    {
        std::vector<FunctionDecl> unique_methods;
        unique_methods.reserve(class_info.methods.size());
        for (FunctionDecl& method: class_info.methods)
        {
            if (IsFirstDeclaration(method, class_info.name, kept))
            {
                unique_methods.push_back(std::move(method));
            }
            else
            {
                ++removed_count;
            }
        }
        class_info.methods = std::move(unique_methods);
    }

    std::vector<FunctionDecl> unique_free_functions;
    unique_free_functions.reserve(ffi_data.free_functions.size());
    for (FunctionDecl& func: ffi_data.free_functions)
    {
        if (IsFirstDeclaration(func, "free functions", kept))
        {
            unique_free_functions.push_back(std::move(func));
        }
        else
        {
            ++removed_count;
        }
    }
    ffi_data.free_functions = std::move(unique_free_functions);

    return removed_count;
}
