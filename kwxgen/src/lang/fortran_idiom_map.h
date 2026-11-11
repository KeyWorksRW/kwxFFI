#pragma once

// Fortran identifier and idiomatic type-mapping helpers for the generated per-class wrapper
// modules.  Fortran is case-insensitive and caps every identifier at 63 characters, so the
// name builders here are the single authority for module, type, and procedure names.  The
// type-name helper deliberately matches the rules used by kwx_types.f90 so a wrapper module
// always references the type the generated type tree actually declares.

#include "../model.h"
#include "lang_common.h"

#include <cctype>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>

// Fortran limits every identifier to 63 characters.
constexpr std::size_t FORTRAN_IDENTIFIER_LIMIT = 63;

// The type tree appends "_from_ptr" (9 characters) and "_t" (2 characters) to a class
// identifier, so the sanitized class-name base keeps that much headroom.
constexpr std::size_t FORTRAN_TYPE_IDENTIFIER_BASE_MAX = 52;

// Lowercase a name, replace every character that is invalid in a Fortran identifier with an
// underscore, prefix a leading digit with an underscore, and truncate to max_length.
[[nodiscard]] inline std::string FortranSanitizeIdentifier(const std::string& name,
                                                           std::size_t max_length)
{
    std::string identifier;
    identifier.reserve(name.size());
    for (const char char_value: name)
    {
        const unsigned char uchar_value = static_cast<unsigned char>(char_value);
        identifier +=
            (std::isalnum(uchar_value) != 0) ? static_cast<char>(std::tolower(uchar_value)) : '_';
    }
    if (identifier.empty())
    {
        identifier = "unnamed";
    }
    if (std::isdigit(static_cast<unsigned char>(identifier.front())) != 0)
    {
        identifier.insert(identifier.begin(), '_');
    }
    if (identifier.size() > max_length)
    {
        identifier.resize(max_length);
    }
    return identifier;
}

// Stable 4-hex-digit suffix used when a naive identifier would exceed the 63-character cap.
[[nodiscard]] inline std::string FortranHashSuffix(std::string_view text)
{
    std::uint32_t hash = 2166136261U;  // FNV-1a 32-bit
    for (const char char_value: text)
    {
        hash ^= static_cast<std::uint32_t>(static_cast<unsigned char>(char_value));
        hash *= 16777619U;
    }
    constexpr std::string_view HEX_DIGITS { "0123456789abcdef" };
    std::string suffix(4, '0');
    for (std::size_t idx = 0; idx < 4; ++idx)
    {
        suffix[3 - idx] = HEX_DIGITS[(hash >> (idx * 4U)) & 0xFU];
    }
    return suffix;
}

// Module that holds the wrapper procedures for a class: wxFooBar → wx_foo_bar.
// wxString maps to wx_string_methods because wx_string is the existing helper module that
// owns to_wxstring/from_wxstring.
[[nodiscard]] inline std::string FortranClassModuleName(const std::string& class_name)
{
    if (class_name == "wxString")
    {
        return "wx_string_methods";
    }
    return FortranSanitizeIdentifier(ToSnakeCase(class_name), FORTRAN_IDENTIFIER_LIMIT);
}

// Wrapper type name for a class, matching the identifier kwx_types.f90 declares.
[[nodiscard]] inline std::string FortranClassName(const std::string& class_name)
{
    return FortranSanitizeIdentifier(class_name, FORTRAN_TYPE_IDENTIFIER_BASE_MAX) + "_t";
}

// Procedure name for a class method: wx_<class_snake>_<method_snake>, plus _<ordinal> for
// the second and later overloads.  Names that would exceed 63 characters are truncated with
// a stable hash suffix so repeated runs produce identical output.
[[nodiscard]] inline std::string FortranMethodIdentifier(const std::string& class_name,
                                                         const std::string& method_name,
                                                         std::size_t ordinal)
{
    std::string identifier = FortranSanitizeIdentifier(ToSnakeCase(class_name), 40);
    identifier += "_";
    identifier += FortranSanitizeIdentifier(ToSnakeCase(method_name), 40);
    if (ordinal > 1)
    {
        identifier += "_";
        identifier += std::to_string(ordinal);
    }
    if (identifier.size() > FORTRAN_IDENTIFIER_LIMIT)
    {
        const std::string hash_suffix = FortranHashSuffix(identifier);
        identifier.resize(FORTRAN_IDENTIFIER_LIMIT - hash_suffix.size() - 1);
        identifier += "_";
        identifier += hash_suffix;
    }
    return identifier;
}

// How a wrapper parameter is declared and passed to the raw C function.
//
// `opaque_pointer` and `raw_pointer` are deliberately distinct. A bare `void*` parameter
// carries no type information — kwx_types.h spells user-data slots, string buffers and
// TClosureFun as `void*` — so `type(c_ptr)` is the only correct mapping and is not a
// fallback. Any other shape the emitter cannot express idiomatically is `raw_pointer` and is
// reported, because the caller could otherwise never discover the loss of type information.
enum class FortranParamKind
{
    self,
    string_input,
    string_output,
    string_array_input,
    integer_array_input,
    geometry,
    geometry_output,
    class_pointer,
    callback,
    scalar,
    scalar_output,
    scalar_input_output,
    byte_array_input,
    byte_array_output,
    byte_scalar_output,
    char_scalar_output,
    int_array_input,
    int_array_output,
    intptr_array_output,
    double_array_output,
    int_scalar_input,
    bool_scalar_input,
    cookie,
    string_array_output,
    object_array_output,
    opaque_pointer,
    raw_pointer
};

// Classify a single parsed parameter so the emitter can choose a declaration and a call
// argument without a second pass over the macro spelling.
[[nodiscard]] inline FortranParamKind ClassifyFortranParam(const Param& param)
{
    if (param.macro_name == "TSelf")
    {
        return FortranParamKind::self;
    }
    if (param.macro_name == "TClass" || param.macro_name == "TClassDef" ||
        param.macro_name == "TClassRef" || param.macro_name == "TClassOwned")
    {
        if (param.macro_arg == "wxString")
        {
            return FortranParamKind::string_input;
        }
        return FortranParamKind::class_pointer;
    }
    if (param.raw_type == "TStringOut")
    {
        return FortranParamKind::string_output;
    }

    // TString and TStringOut are TChar*, i.e. UTF-8 C strings — not wxString handles.
    if (param.raw_type == "TString")
    {
        return FortranParamKind::string_input;
    }
    if (param.macro_name == "TArrayString")
    {
        return FortranParamKind::string_array_input;
    }
    if (param.macro_name == "TArrayInt")
    {
        return FortranParamKind::integer_array_input;
    }
    if (param.macro_name == "TPoint" || param.macro_name == "TSize" ||
        param.macro_name == "TRect" || param.macro_name == "TVector" ||
        param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
        param.macro_name == "TRectLong" || param.macro_name == "TVectorLong" ||
        param.macro_name == "TColorRGB")
    {
        return FortranParamKind::geometry;
    }
    if (param.macro_name == "TPointOut" || param.macro_name == "TSizeOut" ||
        param.macro_name == "TRectOut" || param.macro_name == "TVectorOut" ||
        param.macro_name == "TPointOutVoid" || param.macro_name == "TSizeOutVoid" ||
        param.macro_name == "TRectOutVoid" || param.macro_name == "TVectorOutVoid" ||
        param.macro_name == "TPointOutLong" || param.macro_name == "TSizeOutLong" ||
        param.macro_name == "TRectOutLong" || param.macro_name == "TVectorOutLong" ||
        param.macro_name == "TSizeOutDouble")
    {
        return FortranParamKind::geometry_output;
    }
    if (param.macro_name == "TClosureFun" || param.raw_type == "TClosureFun")
    {
        return FortranParamKind::callback;
    }
    if (param.raw_type == "void*" || param.raw_type == "TStringVoid" ||
        param.raw_type == "TStringOutVoid")
    {
        return FortranParamKind::opaque_pointer;
    }

    if (param.raw_type == "TBytesIn")
    {
        return FortranParamKind::byte_array_input;
    }
    if (param.raw_type == "TBytesOut")
    {
        return FortranParamKind::byte_array_output;
    }
    if (param.raw_type == "TByteOut")
    {
        return FortranParamKind::byte_scalar_output;
    }
    if (param.raw_type == "TCharOut")
    {
        return FortranParamKind::char_scalar_output;
    }
    if (param.raw_type == "TIntArrayIn")
    {
        return FortranParamKind::int_array_input;
    }
    if (param.raw_type == "TIntArrayOut")
    {
        return FortranParamKind::int_array_output;
    }
    if (param.raw_type == "TDoubleArrayOut")
    {
        return FortranParamKind::double_array_output;
    }
    if (param.raw_type == "TIntIn")
    {
        return FortranParamKind::int_scalar_input;
    }
    if (param.raw_type == "TBoolIn")
    {
        return FortranParamKind::bool_scalar_input;
    }
    if (param.raw_type == "TCookie")
    {
        return FortranParamKind::cookie;
    }
    if (param.raw_type == "TArrayStringOut" || param.raw_type == "TArrayStringOutVoid")
    {
        return FortranParamKind::string_array_output;
    }
    if (param.raw_type == "TArrayIntOutVoid")
    {
        return FortranParamKind::int_array_output;
    }
    if (param.raw_type == "TArrayIntPtrOut" || param.raw_type == "TArrayIntPtrOutVoid" ||
        param.raw_type == "TArrayIntOut")
    {
        return FortranParamKind::intptr_array_output;
    }
    if (param.macro_name == "TArrayObjectOut" || param.macro_name == "TArrayObjectOutVoid")
    {
        return FortranParamKind::object_array_output;
    }

    if (ScalarPointerInfo scalar_pointer; LookupScalarPointer(param, scalar_pointer))
    {
        return scalar_pointer.is_in_out ? FortranParamKind::scalar_input_output :
                                          FortranParamKind::scalar_output;
    }

    const std::string& raw = param.raw_type;
    if (raw.empty() || raw == "int" || raw == "long" || raw == "double" || raw == "float" ||
        raw == "unsigned" || raw == "unsigned int" || raw == "unsigned long" || raw == "size_t" ||
        raw == "time_t" || raw == "wxUIntPtr" || raw == "uintptr_t" || raw == "TInt64" ||
        raw == "int64_t" || raw == "TBool" || raw == "TBoolInt" || raw == "TChar" ||
        raw == "unsigned char" || raw == "TUInt8" || raw == "TUInt16" || raw == "TUInt32" ||
        raw == "TUInt" || raw == "unsigned short" || raw == "intptr_t" || raw == "TIntPtr" ||
        raw == "TArrayLen" || raw == "TByteStringLen")
    {
        return FortranParamKind::scalar;
    }
    return FortranParamKind::raw_pointer;
}
