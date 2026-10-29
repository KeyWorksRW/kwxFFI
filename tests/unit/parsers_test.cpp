// Parser unit tests for kwxgen.
//
// The fixtures pin the guard-insensitive parser semantics: preprocessor guards
// are skipped rather than evaluated, so a declaration inside an inactive-guard
// region still appears in the parsed model. The export collector test pins the
// sorted, deduplicated symbol set.

#include "class_parser.h"
#include "constants_parser.h"
#include "exports_gen.h"
#include "model.h"
#include "profile.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

static int failure_count = 0;

#define CHECK(condition)                                                                         \
    do                                                                                           \
    {                                                                                            \
        if (!(condition))                                                                        \
        {                                                                                        \
            std::cerr << "FAIL " << #condition << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
            ++failure_count;                                                                     \
        }                                                                                        \
    } while (false)

#define CHECK_EQ(actual, expected)                                                              \
    do                                                                                          \
    {                                                                                           \
        if (!((actual) == (expected)))                                                          \
        {                                                                                       \
            std::cerr << "FAIL " << #actual << " == " << #expected << " at " << __FILE__ << ":" \
                      << __LINE__ << " (" << (actual) << " vs " << (expected) << ")\n";         \
            ++failure_count;                                                                    \
        }                                                                                       \
    } while (false)

// Free functions parsed from a constants header carry the name in method_name;
// c_func_name is only populated by the class parser.
[[nodiscard]] static bool HasFreeFunction(const std::vector<FunctionDecl>& functions,
                                          const std::string& function_name)
{
    return std::ranges::any_of(functions,
                               [&function_name](const FunctionDecl& function)
                               {
                                   return function.method_name == function_name;
                               });
}

[[nodiscard]] static const ClassInfo* FindClass(const std::vector<ClassInfo>& classes,
                                                const std::string& class_name)
{
    for (const ClassInfo& class_info: classes)
    {
        if (class_info.name == class_name)
        {
            return &class_info;
        }
    }
    return nullptr;
}

[[nodiscard]] static bool HasConstant(const std::vector<ConstantDecl>& constants,
                                      const std::string& export_name,
                                      const std::string& constant_name)
{
    return std::ranges::any_of(constants,
                               [&export_name, &constant_name](const ConstantDecl& constant)
                               {
                                   return constant.export_name == export_name &&
                                          constant.constant_name == constant_name;
                               });
}

[[nodiscard]] static bool ContainsSymbol(const std::vector<std::string>& symbols,
                                         const std::string& symbol)
{
    return std::ranges::find(symbols, symbol) != symbols.end();
}

static void TestConstantsParser(const std::filesystem::path& fixture_path)
{
    const ConstantsFileResult result = ParseConstants(fixture_path);

    // Both the plain and the __WINDOWS__-guarded declaration must be present.
    CHECK(HasFreeFunction(result.free_functions, "wxPlainFn"));
    CHECK(HasFreeFunction(result.free_functions, "wxGuardedFn"));
    CHECK(HasConstant(result.constants, "expFIXTURE_CONST", "FIXTURE_CONST"));
}

static void TestClassParser(const std::filesystem::path& fixture_path)
{
    const ClassParseResult result = ParseClasses(fixture_path);

    const ClassInfo* fixture_class = FindClass(result.classes, "wxFixtureClass");
    CHECK(fixture_class != nullptr);
    if (fixture_class != nullptr)
    {
        CHECK_EQ(fixture_class->name, std::string("wxFixtureClass"));
        CHECK(!fixture_class->methods.empty());
    }

    // The __APPLE__-guarded class must be present despite the guard.
    const ClassInfo* guarded_class = FindClass(result.classes, "wxGuardedClass");
    CHECK(guarded_class != nullptr);
    if (guarded_class != nullptr)
    {
        CHECK_EQ(guarded_class->name, std::string("wxGuardedClass"));
        CHECK(!guarded_class->methods.empty());
    }
}

static void TestProfileFilter()
{
    ParsedFFI ffi_data;

    ClassInfo frame_class;
    frame_class.name = "wxFrame";
    frame_class.parent = "wxWindow";
    FunctionDecl get_variant_method;
    get_variant_method.class_name = "wxFrame";
    get_variant_method.method_name = "GetVariant";
    get_variant_method.return_macro = "TClass";
    get_variant_method.return_arg = "wxVariant";
    frame_class.methods.push_back(get_variant_method);
    ffi_data.classes.push_back(frame_class);

    ClassInfo window_class;
    window_class.name = "wxWindow";
    window_class.parent = "wxObject";
    ffi_data.classes.push_back(window_class);

    ClassInfo socket_class;
    socket_class.name = "wxSocketBase";
    ffi_data.classes.push_back(socket_class);

    ClassInfo regex_class;
    regex_class.name = "wxRegEx";
    ffi_data.classes.push_back(regex_class);

    ClassInfo variant_class;
    variant_class.name = "wxVariant";
    ffi_data.classes.push_back(variant_class);

    ffi_data.parent_map["wxFrame"] = "wxWindow";
    ffi_data.parent_map["wxWindow"] = "wxObject";
    ffi_data.parent_map["wxSocketBase"] = "wxObject";

    const ParsedFFI gui_ffi = ApplyProfile(ffi_data, "gui");
    CHECK(FindClass(gui_ffi.classes, "wxSocketBase") == nullptr);
    CHECK(FindClass(gui_ffi.classes, "wxRegEx") == nullptr);
    CHECK(FindClass(gui_ffi.classes, "wxFrame") != nullptr);
    CHECK(FindClass(gui_ffi.classes, "wxWindow") != nullptr);
    CHECK(FindClass(gui_ffi.classes, "wxVariant") != nullptr);

    const ParsedFFI full_ffi = ApplyProfile(ffi_data, "full");
    CHECK_EQ(full_ffi.classes.size(), ffi_data.classes.size());
    CHECK(FindClass(full_ffi.classes, "wxSocketBase") != nullptr);
    CHECK(FindClass(full_ffi.classes, "wxRegEx") != nullptr);

    CHECK_EQ(DefaultProfileForLanguage("go"), std::string("gui"));
    CHECK_EQ(DefaultProfileForLanguage("julia"), std::string("gui"));
    CHECK_EQ(DefaultProfileForLanguage("typescript"), std::string("full"));
    CHECK_EQ(DefaultProfileForLanguage("fortran"), std::string("full"));
    CHECK_EQ(DefaultProfileForLanguage("luajit"), std::string("full"));
}

static void TestExportSymbols()
{
    ParsedFFI ffi_data;

    ClassInfo class_info;
    class_info.name = "wxFoo";
    FunctionDecl create_method;
    create_method.class_name = "wxFoo";
    create_method.method_name = "Create";
    create_method.c_func_name = "wxFoo_Create";
    class_info.methods.push_back(create_method);
    ffi_data.classes.push_back(class_info);

    ConstantDecl constant;
    constant.export_name = "expFoo";
    constant.constant_name = "Foo";
    ffi_data.constants.push_back(constant);

    EventDecl event;
    event.export_name = "expEVT_X";
    event.event_name = "EVT_X";
    ffi_data.events.push_back(event);

    const std::vector<std::string> symbols = CollectExportSymbols(ffi_data);

    CHECK(std::is_sorted(symbols.begin(), symbols.end()));
    CHECK(std::adjacent_find(symbols.begin(), symbols.end()) == symbols.end());
    CHECK(ContainsSymbol(symbols, "wxFoo_Create"));
    CHECK(ContainsSymbol(symbols, "expFoo"));
    CHECK(ContainsSymbol(symbols, "expEVT_X"));
    CHECK(ContainsSymbol(symbols, "kwxConstants_IntCount"));
    CHECK(ContainsSymbol(symbols, "kwxConstants_IntTable"));
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "usage: kwx_parser_tests <fixture-directory>\n";
        return 1;
    }

    const std::filesystem::path fixture_dir = argv[1];

    TestConstantsParser(fixture_dir / "guard_constants.h");
    TestClassParser(fixture_dir / "guard_classes.h");
    TestProfileFilter();
    TestExportSymbols();

    if (failure_count != 0)
    {
        std::cerr << failure_count << " parser check(s) failed\n";
        return 1;
    }

    std::cout << "All parser checks passed\n";
    return 0;
}
