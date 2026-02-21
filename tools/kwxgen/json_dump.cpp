#include "json_dump.h"

#include <fstream>
#include <iostream>

namespace kwxgen
{

    namespace
    {

        // Escape a string for JSON output.
        std::string JsonEscape(const std::string& s)
        {
            std::string result;
            result.reserve(s.size() + 4);
            for (char c: s)
            {
                switch (c)
                {
                    case '"':
                        result += "\\\"";
                        break;
                    case '\\':
                        result += "\\\\";
                        break;
                    case '\n':
                        result += "\\n";
                        break;
                    case '\r':
                        result += "\\r";
                        break;
                    case '\t':
                        result += "\\t";
                        break;
                    default:
                        result += c;
                }
            }
            return result;
        }

        void WriteParam(std::ostream& out, const Param& p, const std::string& indent)
        {
            out << indent << "{\n";
            out << indent << "  \"raw_type\": \"" << JsonEscape(p.raw_type) << "\",\n";
            out << indent << "  \"macro_name\": \"" << JsonEscape(p.macro_name) << "\",\n";
            out << indent << "  \"macro_arg\": \"" << JsonEscape(p.macro_arg) << "\",\n";
            out << indent << "  \"param_name\": \"" << JsonEscape(p.param_name) << "\"\n";
            out << indent << "}";
        }

        void WriteFunctionDecl(std::ostream& out, const FunctionDecl& f, const std::string& indent)
        {
            out << indent << "{\n";
            out << indent << "  \"class_name\": \"" << JsonEscape(f.class_name) << "\",\n";
            out << indent << "  \"method_name\": \"" << JsonEscape(f.method_name) << "\",\n";
            out << indent << "  \"return_type\": \"" << JsonEscape(f.return_type) << "\",\n";
            out << indent << "  \"return_macro\": \"" << JsonEscape(f.return_macro) << "\",\n";
            out << indent << "  \"return_arg\": \"" << JsonEscape(f.return_arg) << "\",\n";
            out << indent << "  \"is_constructor\": " << (f.is_constructor ? "true" : "false")
                << ",\n";
            out << indent << "  \"is_destructor\": " << (f.is_destructor ? "true" : "false")
                << ",\n";
            out << indent << "  \"has_self\": " << (f.has_self ? "true" : "false") << ",\n";
            out << indent << "  \"params\": [";
            if (f.params.empty())
            {
                out << "]";
            }
            else
            {
                out << "\n";
                for (size_t i = 0; i < f.params.size(); ++i)
                {
                    WriteParam(out, f.params[i], indent + "    ");
                    if (i + 1 < f.params.size())
                        out << ",";
                    out << "\n";
                }
                out << indent << "  ]";
            }
            out << "\n" << indent << "}";
        }

    }  // anonymous namespace

    void DumpJson(const ParsedFFI& ffi, std::ostream& out)
    {
        out << "{\n";

        // Summary counts
        size_t total_methods = 0;
        for (auto& cls: ffi.classes)
            total_methods += cls.methods.size();
        out << "  \"summary\": {\n";
        out << "    \"events\": " << ffi.events.size() << ",\n";
        out << "    \"keys\": " << ffi.keys.size() << ",\n";
        out << "    \"constants\": " << ffi.constants.size() << ",\n";
        out << "    \"classes\": " << ffi.classes.size() << ",\n";
        out << "    \"total_methods\": " << total_methods << ",\n";
        out << "    \"free_functions\": " << ffi.free_functions.size() << "\n";
        out << "  },\n";

        // Events
        out << "  \"events\": [\n";
        for (size_t i = 0; i < ffi.events.size(); ++i)
        {
            out << "    { \"export_name\": \"" << JsonEscape(ffi.events[i].export_name)
                << "\", \"event_name\": \"" << JsonEscape(ffi.events[i].event_name) << "\" }";
            if (i + 1 < ffi.events.size())
                out << ",";
            out << "\n";
        }
        out << "  ],\n";

        // Keys
        out << "  \"keys\": [\n";
        for (size_t i = 0; i < ffi.keys.size(); ++i)
        {
            out << "    { \"export_name\": \"" << JsonEscape(ffi.keys[i].export_name)
                << "\", \"key_name\": \"" << JsonEscape(ffi.keys[i].key_name) << "\" }";
            if (i + 1 < ffi.keys.size())
                out << ",";
            out << "\n";
        }
        out << "  ],\n";

        // Constants
        out << "  \"constants\": [\n";
        for (size_t i = 0; i < ffi.constants.size(); ++i)
        {
            const auto& c = ffi.constants[i];
            out << "    { \"export_name\": \"" << JsonEscape(c.export_name)
                << "\", \"constant_name\": \"" << JsonEscape(c.constant_name)
                << "\", \"return_type\": \"" << JsonEscape(c.return_type) << "\" }";
            if (i + 1 < ffi.constants.size())
                out << ",";
            out << "\n";
        }
        out << "  ],\n";

        // Free functions
        out << "  \"free_functions\": [\n";
        for (size_t i = 0; i < ffi.free_functions.size(); ++i)
        {
            WriteFunctionDecl(out, ffi.free_functions[i], "    ");
            if (i + 1 < ffi.free_functions.size())
                out << ",";
            out << "\n";
        }
        out << "  ],\n";

        // Classes (empty for Phase 3)
        out << "  \"classes\": [\n";
        for (size_t i = 0; i < ffi.classes.size(); ++i)
        {
            const auto& cls = ffi.classes[i];
            out << "    {\n";
            out << "      \"name\": \"" << JsonEscape(cls.name) << "\",\n";
            out << "      \"parent\": \"" << JsonEscape(cls.parent) << "\",\n";
            out << "      \"is_window_derived\": " << (cls.is_window_derived ? "true" : "false")
                << ",\n";
            out << "      \"is_object_derived\": " << (cls.is_object_derived ? "true" : "false")
                << ",\n";
            out << "      \"methods\": [\n";
            for (size_t j = 0; j < cls.methods.size(); ++j)
            {
                WriteFunctionDecl(out, cls.methods[j], "        ");
                if (j + 1 < cls.methods.size())
                    out << ",";
                out << "\n";
            }
            out << "      ]\n";
            out << "    }";
            if (i + 1 < ffi.classes.size())
                out << ",";
            out << "\n";
        }
        out << "  ],\n";

        // Parent map
        out << "  \"parent_map\": {\n";
        {
            size_t idx = 0;
            for (auto& [child, parent]: ffi.parent_map)
            {
                out << "    \"" << JsonEscape(child) << "\": \"" << JsonEscape(parent) << "\"";
                if (++idx < ffi.parent_map.size())
                    out << ",";
                out << "\n";
            }
        }
        out << "  }\n";

        out << "}\n";
    }

    bool DumpJsonToFile(const ParsedFFI& ffi, const std::string& filePath)
    {
        std::ofstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Error: cannot open output file " << filePath << "\n";
            return false;
        }
        DumpJson(ffi, file);
        return true;
    }

}  // namespace kwxgen
