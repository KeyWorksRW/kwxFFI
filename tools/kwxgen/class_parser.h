#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

namespace kwxgen
{

    // Parse kwx_classes.h → vector<ClassInfo> + parent_map
    // Handles:
    //   TClassDef(Name) / TClassDefExtend(Name, Parent) blocks
    //   Multi-line function declarations (continuation via unbalanced parens)
    //   Nested macro types: TClass, TSelf, TPoint, TSize, TRect, TArray*, etc.
    //   Empty class definitions (no methods)
    //   Inheritance hierarchy resolution (parent_map, is_window_derived, is_object_derived)
    struct ClassParseResult
    {
        std::vector<ClassInfo> classes;
        std::unordered_map<std::string, std::string> parent_map;
        std::vector<FunctionDecl>
            free_functions;  // exp* and other non-class free functions found in kwx_classes.h
        // Maps concrete class → list of mixin classes it implements.
        std::unordered_map<std::string, std::vector<std::string>> mixin_map;
    };

    ClassParseResult ParseClasses(const std::filesystem::path& filePath);

}  // namespace kwxgen
