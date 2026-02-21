#include "constants_parser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace kwxgen
{

    namespace
    {

        // Parse a simple macro type like "TClass(wxWindow)" into macro_name="TClass",
        // macro_arg="wxWindow" Returns true if the type was a macro form, false for plain types
        // like "int", "void*".
        bool ParseMacroType(const std::string& type, std::string& macro_name,
                            std::string& macro_arg)
        {
            std::regex re_macro(R"(^(\w+)\((.+)\)$)");
            std::smatch m;
            if (std::regex_match(type, m, re_macro))
            {
                macro_name = m[1].str();
                macro_arg = m[2].str();
                return true;
            }
            macro_name.clear();
            macro_arg.clear();
            return false;
        }

        // Split a parameter list string by commas, respecting parenthesized groups.
        // "TClass(wxImage) src, TClass(wxImage) dest, int flags"
        // → ["TClass(wxImage) src", "TClass(wxImage) dest", "int flags"]
        std::vector<std::string> SplitParams(const std::string& paramStr)
        {
            std::vector<std::string> result;
            int depth = 0;
            size_t start = 0;
            for (size_t i = 0; i < paramStr.size(); ++i)
            {
                if (paramStr[i] == '(')
                    ++depth;
                else if (paramStr[i] == ')')
                    --depth;
                else if (paramStr[i] == ',' && depth == 0)
                {
                    std::string token = paramStr.substr(start, i - start);
                    // Trim whitespace
                    auto b = token.find_first_not_of(" \t");
                    auto e = token.find_last_not_of(" \t");
                    if (b != std::string::npos)
                        result.push_back(token.substr(b, e - b + 1));
                    start = i + 1;
                }
            }
            // Last token
            if (start < paramStr.size())
            {
                std::string token = paramStr.substr(start);
                auto b = token.find_first_not_of(" \t");
                auto e = token.find_last_not_of(" \t");
                if (b != std::string::npos)
                    result.push_back(token.substr(b, e - b + 1));
            }
            return result;
        }

        // Parse a single parameter token like "TClass(wxWindow) parent" or "int flags" into a
        // Param.
        Param ParseOneParam(const std::string& token)
        {
            Param p;

            // Try macro form: "TClass(wxFoo) name" or "TClass(wxFoo)"
            std::regex re_macro_param(R"(^(\w+)\(([^)]+)\)\s*(\w*)$)");
            std::smatch m;
            if (std::regex_match(token, m, re_macro_param))
            {
                p.macro_name = m[1].str();
                p.macro_arg = m[2].str();
                p.param_name = m[3].str();
                p.raw_type = p.macro_name + "(" + p.macro_arg + ")";
                return p;
            }

            // Plain type: "int flags", "void* pointer", "int"
            // Find last whitespace-separated word as param name (if there are at least two words)
            auto last_space = token.rfind(' ');
            if (last_space != std::string::npos)
            {
                std::string maybe_name = token.substr(last_space + 1);
                std::string maybe_type = token.substr(0, last_space);
                // Trim trailing spaces from type
                auto e = maybe_type.find_last_not_of(" \t");
                if (e != std::string::npos)
                    maybe_type = maybe_type.substr(0, e + 1);

                // Check if maybe_name looks like an identifier (not a pointer suffix)
                if (std::regex_match(maybe_name, std::regex(R"(^\w+$)")) && maybe_name != "int" &&
                    maybe_name != "void" && maybe_name != "double" && maybe_name != "float")
                {
                    p.raw_type = maybe_type;
                    p.param_name = maybe_name;
                    // Handle pointer types like "void*" or "void *"
                    // Handle type pointers: "void* name" → raw_type="void*"
                    return p;
                }
            }

            // No parameter name — type only
            p.raw_type = token;
            return p;
        }

        // Parse a single-line free function declaration.
        // Returns true if parsed, false otherwise.
        bool ParseFreeFunction(const std::string& line, FunctionDecl& decl)
        {
            // Match: RETURN_TYPE FUNC_NAME(PARAMS);
            // Return type can be: "TClass(wxFoo)", "int", "void", "void*", "TBool", "TStringVoid"
            // The return type may include parens for macros.

            // Strategy: find the function name by looking for the last identifier before '('
            // that isn't inside a TClass(...) macro.

            // Find the parameter list between outermost ( and );
            auto paren_open = line.find('(');

            // But TClass(wxFoo) in the return type also has parens. We need the *function* paren.
            // The function paren is the one that matches ');' at the end.
            auto semicolon = line.rfind(';');
            if (semicolon == std::string::npos)
                return false;

            auto paren_close = line.rfind(')', semicolon);
            if (paren_close == std::string::npos)
                return false;

            // Now find the matching open paren for this close paren
            int depth = 0;
            size_t func_paren_open = std::string::npos;
            for (size_t i = paren_close; i != std::string::npos; --i)
            {
                if (line[i] == ')')
                    ++depth;
                else if (line[i] == '(')
                {
                    --depth;
                    if (depth == 0)
                    {
                        func_paren_open = i;
                        break;
                    }
                }
                if (i == 0)
                    break;
            }
            if (func_paren_open == std::string::npos)
                return false;

            // Extract the part before the function paren: "TClass(wxFoo) Null_Foo"
            std::string prefix = line.substr(0, func_paren_open);
            // Trim
            auto pe = prefix.find_last_not_of(" \t");
            if (pe == std::string::npos)
                return false;
            prefix = prefix.substr(0, pe + 1);

            // The function name is the last word in prefix
            auto last_space = prefix.rfind(' ');
            auto last_close_paren = prefix.rfind(')');

            std::string func_name;
            std::string return_type_str;

            if (last_close_paren != std::string::npos &&
                (last_space == std::string::npos || last_close_paren > last_space))
            {
                // Return type ends with ')' — it's a macro like TClass(wxFoo)
                // Function name follows after the closing paren + space
                auto after_paren = prefix.find_first_not_of(" \t", last_close_paren + 1);
                if (after_paren == std::string::npos)
                    return false;
                func_name = prefix.substr(after_paren);
                return_type_str = prefix.substr(0, last_close_paren + 1);
                // Trim return type
                auto rb = return_type_str.find_first_not_of(" \t");
                if (rb != std::string::npos)
                    return_type_str = return_type_str.substr(rb);
            }
            else if (last_space != std::string::npos)
            {
                func_name = prefix.substr(last_space + 1);
                return_type_str = prefix.substr(0, last_space);
                auto rb = return_type_str.find_first_not_of(" \t");
                if (rb != std::string::npos)
                    return_type_str = return_type_str.substr(rb);
            }
            else
            {
                return false;  // No return type + name separation
            }

            decl.method_name = func_name;
            decl.return_type = return_type_str;
            ParseMacroType(return_type_str, decl.return_macro, decl.return_arg);

            // Extract parameter string
            std::string paramStr =
                line.substr(func_paren_open + 1, paren_close - func_paren_open - 1);
            // Trim
            auto pb = paramStr.find_first_not_of(" \t");
            if (pb != std::string::npos)
            {
                auto ppe = paramStr.find_last_not_of(" \t");
                paramStr = paramStr.substr(pb, ppe - pb + 1);

                auto tokens = SplitParams(paramStr);
                for (auto& tok: tokens)
                    decl.params.push_back(ParseOneParam(tok));
            }

            return true;
        }

    }  // anonymous namespace

    ConstantsFileResult ParseConstants(const std::filesystem::path& filePath)
    {
        ConstantsFileResult result;
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Error: cannot open " << filePath << "\n";
            return result;
        }

        // WXFFI_EXPORT pattern: "WXFFI_EXPORT(int, expNAME)();"
        std::regex re_wxffi(R"(^\s*WXFFI_EXPORT\s*\(\s*(\w+)\s*,\s*(exp\w+)\s*\)\s*\(\s*\)\s*;)");

        std::string accumulated;
        std::string line;

        while (std::getline(file, line))
        {
            // Skip preprocessor and blank lines
            if (line.empty() || line[0] == '#')
                continue;

            // Check for WXFFI_EXPORT constant
            std::smatch m;
            if (std::regex_search(line, m, re_wxffi))
            {
                ConstantDecl decl;
                decl.return_type = m[1].str();
                decl.export_name = m[2].str();
                // Strip "exp" or "expwx" prefix for constant_name
                std::string name = decl.export_name;
                if (name.substr(0, 5) == "expwx")
                    decl.constant_name = name.substr(5);
                else if (name.substr(0, 3) == "exp")
                    decl.constant_name = name.substr(3);
                else
                    decl.constant_name = name;
                result.constants.push_back(std::move(decl));
                continue;
            }

            // Handle multi-line continuation: if line starts with whitespace and we have
            // accumulated content, join it.
            bool is_continuation =
                !accumulated.empty() && !line.empty() && (line[0] == ' ' || line[0] == '\t');

            if (is_continuation)
            {
                // Trim leading whitespace from continuation and join
                auto b = line.find_first_not_of(" \t");
                if (b != std::string::npos)
                    accumulated += " " + line.substr(b);
                // Check if now complete (ends with ;)
                auto trimmed_end = accumulated.find_last_not_of(" \t");
                if (trimmed_end != std::string::npos && accumulated[trimmed_end] == ';')
                {
                    FunctionDecl decl;
                    if (ParseFreeFunction(accumulated, decl))
                        result.free_functions.push_back(std::move(decl));
                    accumulated.clear();
                }
                continue;
            }

            // If we had accumulated content that didn't continue, process it
            if (!accumulated.empty())
            {
                FunctionDecl decl;
                if (ParseFreeFunction(accumulated, decl))
                    result.free_functions.push_back(std::move(decl));
                accumulated.clear();
            }

            // Try to parse as a complete single-line free function
            auto trimmed_end = line.find_last_not_of(" \t");
            if (trimmed_end != std::string::npos && line[trimmed_end] == ';')
            {
                FunctionDecl decl;
                if (ParseFreeFunction(line, decl))
                    result.free_functions.push_back(std::move(decl));
            }
            else if (trimmed_end != std::string::npos)
            {
                // Doesn't end with ; — start accumulating for multi-line
                auto b = line.find_first_not_of(" \t");
                if (b != std::string::npos)
                    accumulated = line.substr(b);
            }
        }

        // Flush any remaining accumulated line
        if (!accumulated.empty())
        {
            FunctionDecl decl;
            if (ParseFreeFunction(accumulated, decl))
                result.free_functions.push_back(std::move(decl));
        }

        return result;
    }

}  // namespace kwxgen
