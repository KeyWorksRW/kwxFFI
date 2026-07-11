/////////////////////////////////////////////////////////////////////////////
// Purpose:   Fortran ISO_C_BINDING FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "lang_fortran.h"

#include "../file_writer.h"
#include "fortran_type_map.h"
#include "lang_common.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <print>
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

    std::vector<ConstantDecl> sorted_constants = ffi_data.constants;
    std::ranges::sort(sorted_constants,
                      [](const ConstantDecl& left, const ConstantDecl& right)
                      {
                          return left.export_name < right.export_name;
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
        GenerateConstants(sorted_constants, output);
        GenerateClasses(ffi_data, output);
        GenerateFreeFunctions(ffi_data, output);

        output << "  end interface\n\n";
        output << "end module kwxffi\n";
    }

    // 2. Idiomatic Fortran wrapper modules
    GenerateTypes(ffi_data, outDir);
    GenerateStringModule(outDir);
    GenerateConstantsModule(ffi_data, outDir);
    GenerateWindowModule(ffi_data, outDir);
    GenerateFrameModule(ffi_data, outDir);
    GenerateControlsModule(ffi_data, outDir);
    GenerateMenusModule(ffi_data, outDir);
    GenerateSizersModule(ffi_data, outDir);
    GenerateEventsModule(ffi_data, outDir);
    GenerateDialogsModule(ffi_data, outDir);

    std::println(stderr, "Fortran: generated all files in {}", outDir.string());
}

VerifyResult FortranEmitter::Verify(const ParsedFFI& /* ffi_data */, const fs::path& /* out_dir */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("Fortran verify: use 'kwxgen verify' command instead");
    return result;
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

void FortranEmitter::GenerateConstants(const std::vector<ConstantDecl>& constants,
                                       std::ostream& output)
{
    output << "    ! Constants\n\n";

    for (const auto& constant: constants)
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

        const std::string fname = FortranName(constant.export_name);
        output << "    " << fType << " function " << fname << "() &\n";
        output << "        bind(C, name='" << constant.export_name << "')\n";
        output << "      import :: " << importSym << "\n";
        output << "    end function\n\n";
    }

    std::println(stderr, "  Constants:        {:L}", constants.size());
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
// kwx_types.f90 — Opaque pointer types
// -------------------------------------------------------------------------

void FortranEmitter::GenerateTypes(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "kwx_types.f90");

    output << "! Code generated by kwxgen. DO NOT EDIT.\n";
    output << "module kwx_types\n";
    output << "    use, intrinsic :: iso_c_binding\n";
    output << "    implicit none\n";
    output << "    private\n\n";

    // Helper: emit a base type with its own ptr + is_valid
    struct BaseType
    {
        const char* name;
    };
    // Helper: emit an extended type
    struct DerivedType
    {
        const char* name;
        const char* parent;
    };

    // Base types (each has its own ptr and is_valid)
    constexpr std::array<BaseType, 8> bases = { {
        { "wxWindow" },
        { "wxSizer" },
        { "wxEvent" },
        { "wxApp" },
        { "wxMenu" },
        { "wxMenuBar" },
        { "wxMenuItem" },
        { "wxString" },
    } };

    // Derived types
    constexpr std::array<DerivedType, 17> derived = { {
        { "wxFrame", "wxWindow" },
        { "wxDialog", "wxWindow" },
        { "wxPanel", "wxWindow" },
        { "wxButton", "wxWindow" },
        { "wxTextCtrl", "wxWindow" },
        { "wxStaticText", "wxWindow" },
        { "wxCheckBox", "wxWindow" },
        { "wxRadioButton", "wxWindow" },
        { "wxChoice", "wxWindow" },
        { "wxListBox", "wxWindow" },
        { "wxComboBox", "wxWindow" },
        { "wxStatusBar", "wxWindow" },
        { "wxToolBar", "wxWindow" },
        { "wxBoxSizer", "wxSizer" },
        { "wxFlexGridSizer", "wxSizer" },
        { "wxGridSizer", "wxSizer" },
        { "wxCommandEvent", "wxEvent" },
    } };

    // Emit base types
    for (const auto& base: bases)
    {
        const std::string tname = std::string(base.name) + "_t";
        output << "    type, public :: " << tname << "\n";
        output << "        type(c_ptr) :: ptr = c_null_ptr\n";
        output << "    contains\n";
        output << "        procedure :: is_valid => " << base.name << "_is_valid\n";
        output << "    end type " << tname << "\n\n";
    }

    // Emit derived types
    for (const auto& derived_entry: derived)
    {
        const std::string tname = std::string(derived_entry.name) + "_t";
        const std::string pname = std::string(derived_entry.parent) + "_t";
        output << "    type, extends(" << pname << "), public :: " << tname << "\n";
        output << "    end type " << tname << "\n\n";
    }

    output << "contains\n\n";

    // is_valid procedures for base types
    for (const auto& base: bases)
    {
        output << "    pure logical function " << base.name << "_is_valid(self) result(valid)\n";
        output << "        class(" << base.name << "_t), intent(in) :: self\n";
        output << "        valid = c_associated(self%ptr)\n";
        output << "    end function " << base.name << "_is_valid\n\n";
    }

    output << "end module kwx_types\n";
    std::println(stderr, "  Generated kwx_types.f90");
}

// -------------------------------------------------------------------------
// wx_string.f90 — String conversion utilities
// -------------------------------------------------------------------------

void FortranEmitter::GenerateStringModule(const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_string.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_string
    use, intrinsic :: iso_c_binding
    use kwx_types
    implicit none
    private

    public :: to_wxstring, from_wxstring, wxString_Delete

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

        subroutine wxString_Delete_C(wx_str) bind(C, name="wxString_Delete")
            import :: c_ptr
            type(c_ptr), value :: wx_str
        end subroutine

        function wxString_Length(wx_str) bind(C, name="wxString_Length")
            import :: c_ptr, c_int
            type(c_ptr), value :: wx_str
            integer(c_int) :: wxString_Length
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

    subroutine wxString_Delete(wx_str_ptr)
        type(c_ptr), intent(inout) :: wx_str_ptr
        if (c_associated(wx_str_ptr)) then
            call wxString_Delete_C(wx_str_ptr)
            wx_str_ptr = c_null_ptr
        end if
    end subroutine wxString_Delete

end module wx_string
)";
    std::println(stderr, "  Generated wx_string.f90");
}

// -------------------------------------------------------------------------
// kwx_constants.f90 — Friendly constant names
// -------------------------------------------------------------------------

void FortranEmitter::GenerateConstantsModule(const ParsedFFI& ffi_data, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "kwx_constants.f90");

    output << "! Code generated by kwxgen. DO NOT EDIT.\n";
    output << "module kwx_constants\n";
    output << "    use, intrinsic :: iso_c_binding\n";
    output << "    implicit none\n";
    output << "    private\n\n";

    // Collect all constants + events into a unified list of (fortran_name, c_name, return_type)
    struct ConstEntry
    {
        std::string fortran_name;
        std::string c_name;
        std::string return_type;  // "int" or has '*'
    };

    std::vector<ConstEntry> entries;

    // Constants from kwx_defs.cpp
    for (const auto& constant: ffi_data.constants)
    {
        const std::string fname = FortranName(constant.export_name);
        entries.push_back({ fname, constant.export_name, constant.return_type });
    }

    // Events
    for (const auto& event: ffi_data.events)
    {
        const std::string fname = FortranName(event.export_name);
        entries.push_back({ fname, event.export_name, "int" });
    }

    // Sort by Fortran name
    std::ranges::sort(entries,
                      [](const ConstEntry& left, const ConstEntry& right)
                      {
                          return left.fortran_name < right.fortran_name;
                      });

    // Public declarations — emit all
    for (const auto& entry: entries)
    {
        output << "    public :: " << entry.fortran_name << "\n";
    }
    output << "\n";

    // Interface block
    output << "    interface\n\n";

    for (const auto& entry: entries)
    {
        std::string ftype;
        std::string import_sym;
        if (entry.return_type.find('*') != std::string::npos)
        {
            ftype = "type(c_ptr)";
            import_sym = "c_ptr";
        }
        else
        {
            ftype = "integer(c_int)";
            import_sym = "c_int";
        }

        output << "        " << ftype << " function " << entry.fortran_name << "() &\n";
        output << "            bind(C, name='" << entry.c_name << "')\n";
        output << "            import :: " << import_sym << "\n";
        output << "        end function\n\n";
    }

    output << "    end interface\n\n";
    output << "end module kwx_constants\n";
    std::println(stderr, "  Generated kwx_constants.f90 ({} entries)", entries.size());
}

// -------------------------------------------------------------------------
// wx_window.f90 — wxWindow base class wrapper
// -------------------------------------------------------------------------

void FortranEmitter::GenerateWindowModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_window.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_window
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    implicit none
    private

    ! Visibility and state
    public :: wx_window_show, wx_window_hide
    public :: wx_window_enable, wx_window_disable
    public :: wx_window_is_enabled, wx_window_is_shown

    ! Size and position
    public :: wx_window_set_size, wx_window_move
    public :: wx_window_get_id

    ! Focus
    public :: wx_window_set_focus, wx_window_has_focus

    ! Refresh and update
    public :: wx_window_refresh, wx_window_update

    ! Layout
    public :: wx_window_center, wx_window_fit, wx_window_layout

    ! Destruction
    public :: wx_window_destroy, wx_window_close

    ! Hierarchy
    public :: wx_window_get_parent, wx_window_is_top_level

    ! Freeze/thaw
    public :: wx_window_freeze, wx_window_thaw

    ! Z-order
    public :: wx_window_raise, wx_window_lower

contains

    !--- Visibility and state ---

    function wx_window_show(window) result(shown)
        class(wxWindow_t), intent(in) :: window
        logical :: shown
        shown = (wxWindow_Show(window%ptr) /= 0)
    end function

    function wx_window_hide(window) result(hidden)
        class(wxWindow_t), intent(in) :: window
        logical :: hidden
        hidden = (wxWindow_Hide(window%ptr) /= 0)
    end function

    subroutine wx_window_enable(window)
        class(wxWindow_t), intent(in) :: window
        integer(c_int) :: result_
        result_ = wxWindow_Enable(window%ptr)
    end subroutine

    subroutine wx_window_disable(window)
        class(wxWindow_t), intent(in) :: window
        integer(c_int) :: result_
        result_ = wxWindow_Disable(window%ptr)
    end subroutine

    function wx_window_is_enabled(window) result(enabled)
        class(wxWindow_t), intent(in) :: window
        logical :: enabled
        enabled = (wxWindow_IsEnabled(window%ptr) /= 0)
    end function

    function wx_window_is_shown(window) result(shown)
        class(wxWindow_t), intent(in) :: window
        logical :: shown
        shown = (wxWindow_IsShown(window%ptr) /= 0)
    end function

    !--- Size and position ---

    subroutine wx_window_set_size(window, x, y, width, height)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in) :: x, y, width, height
        call wxWindow_SetSize(window%ptr, int(x, c_int), int(y, c_int), &
            int(width, c_int), int(height, c_int), 0_c_int)
    end subroutine

    subroutine wx_window_move(window, x, y)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in) :: x, y
        call wxWindow_Move(window%ptr, int(x, c_int), int(y, c_int), 0_c_int)
    end subroutine

    function wx_window_get_id(window) result(id)
        class(wxWindow_t), intent(in) :: window
        integer :: id
        id = int(wxWindow_GetId(window%ptr))
    end function

    !--- Focus ---

    subroutine wx_window_set_focus(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_SetFocus(window%ptr)
    end subroutine

    function wx_window_has_focus(window) result(focused)
        class(wxWindow_t), intent(in) :: window
        logical :: focused
        focused = (wxWindow_HasFocus(window%ptr) /= 0)
    end function

    !--- Refresh and update ---

    subroutine wx_window_refresh(window, erase_background)
        class(wxWindow_t), intent(in) :: window
        logical, intent(in), optional :: erase_background
        integer(c_int) :: erase
        erase = 1_c_int
        if (present(erase_background)) then
            erase = 0_c_int
            if (erase_background) erase = 1_c_int
        end if
        call wxWindow_Refresh(window%ptr, erase)
    end subroutine

    subroutine wx_window_update(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_UpdateWindowUI(window%ptr, 0_c_int)
    end subroutine

    !--- Layout ---

    subroutine wx_window_center(window, direction)
        class(wxWindow_t), intent(in) :: window
        integer, intent(in), optional :: direction
        integer(c_int) :: dir
        dir = wxBOTH()
        if (present(direction)) dir = int(direction, c_int)
        call wxWindow_CenterOnParent(window%ptr, dir)
    end subroutine

    subroutine wx_window_fit(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_Fit(window%ptr)
    end subroutine

    function wx_window_layout(window) result(ok)
        class(wxWindow_t), intent(in) :: window
        logical :: ok
        ok = (wxWindow_Layout(window%ptr) /= 0)
    end function

    !--- Destruction ---

    function wx_window_destroy(window) result(destroyed)
        class(wxWindow_t), intent(inout) :: window
        logical :: destroyed
        destroyed = (wxWindow_Destroy(window%ptr) /= 0)
        window%ptr = c_null_ptr
    end function

    function wx_window_close(window, force) result(closed)
        class(wxWindow_t), intent(in) :: window
        logical, intent(in), optional :: force
        logical :: closed
        integer(c_int) :: c_force
        c_force = 0_c_int
        if (present(force)) then
            if (force) c_force = 1_c_int
        end if
        closed = (wxWindow_Close(window%ptr, c_force) /= 0)
    end function

    !--- Hierarchy ---

    function wx_window_get_parent(window) result(parent)
        class(wxWindow_t), intent(in) :: window
        type(wxWindow_t) :: parent
        parent%ptr = wxWindow_GetParent(window%ptr)
    end function

    function wx_window_is_top_level(window) result(is_top)
        class(wxWindow_t), intent(in) :: window
        logical :: is_top
        is_top = (wxWindow_IsTopLevel(window%ptr) /= 0)
    end function

    !--- Freeze/thaw ---

    subroutine wx_window_freeze(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_Freeze(window%ptr)
    end subroutine

    subroutine wx_window_thaw(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_Thaw(window%ptr)
    end subroutine

    !--- Z-order ---

    subroutine wx_window_raise(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_Raise(window%ptr)
    end subroutine

    subroutine wx_window_lower(window)
        class(wxWindow_t), intent(in) :: window
        call wxWindow_Lower(window%ptr)
    end subroutine

end module wx_window
)";
    std::println(stderr, "  Generated wx_window.f90");
}

// -------------------------------------------------------------------------
// wx_frame.f90 — wxFrame + wxTopLevelWindow wrapper
// -------------------------------------------------------------------------

void FortranEmitter::GenerateFrameModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_frame.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_frame
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    use wx_string, only: to_wxstring, from_wxstring
    implicit none
    private

    ! Creation
    public :: wx_frame_create

    ! Show/hide/close
    public :: wx_frame_show, wx_frame_hide, wx_frame_close

    ! Status bar
    public :: wx_frame_create_status_bar, wx_frame_set_status_text
    public :: wx_frame_push_status_text, wx_frame_pop_status_text

    ! Menu bar
    public :: wx_frame_set_menu_bar, wx_frame_get_menu_bar

    ! Toolbar
    public :: wx_frame_create_tool_bar, wx_frame_get_tool_bar

    ! Window ops
    public :: wx_frame_center, wx_frame_set_size

    ! TopLevelWindow ops
    public :: wx_frame_restore, wx_frame_maximize, wx_frame_iconize
    public :: wx_frame_is_maximized, wx_frame_is_iconized
    public :: wx_frame_show_full_screen, wx_frame_is_full_screen
    public :: wx_frame_get_title, wx_frame_set_title
    public :: wx_frame_is_active
    public :: wx_frame_enable_close_button
    public :: wx_frame_enable_maximize_button
    public :: wx_frame_enable_minimize_button
    public :: wx_frame_request_user_attention

contains

    !--- Creation ---

    function wx_frame_create(title, parent, id, x, y, width, height, style) &
            result(frame)
        character(len=*), intent(in) :: title
        class(wxWindow_t), intent(in), optional :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxFrame_t) :: frame

        type(c_ptr) :: parent_ptr, title_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        parent_ptr = c_null_ptr
        if (present(parent)) parent_ptr = parent%ptr
        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = wxDEFAULT_FRAME_STYLE()
        if (present(style)) c_style = style

        title_ptr = to_wxstring(title)
        frame%ptr = wxFrame_Create(parent_ptr, c_id, title_ptr, &
            c_x, c_y, c_w, c_h, c_style)
        call wxString_Delete(title_ptr)
    end function

    !--- Show/hide/close ---

    subroutine wx_frame_show(frame)
        type(wxFrame_t), intent(in) :: frame
        integer(c_int) :: dummy
        dummy = wxWindow_Show(frame%ptr)
    end subroutine

    subroutine wx_frame_hide(frame)
        type(wxFrame_t), intent(in) :: frame
        integer(c_int) :: dummy
        dummy = wxWindow_Hide(frame%ptr)
    end subroutine

    subroutine wx_frame_close(frame, force)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in), optional :: force
        integer(c_int) :: c_force, dummy
        c_force = 0_c_int
        if (present(force)) then
            if (force) c_force = 1_c_int
        end if
        dummy = wxWindow_Close(frame%ptr, c_force)
    end subroutine

    !--- Status bar ---

    subroutine wx_frame_create_status_bar(frame, number, style)
        type(wxFrame_t), intent(in) :: frame
        integer, intent(in), optional :: number
        integer(c_long), intent(in), optional :: style
        type(c_ptr) :: result_
        integer(c_int) :: c_num
        integer(c_long) :: c_style
        c_num = 1_c_int
        if (present(number)) c_num = int(number, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style
        result_ = wxFrame_CreateStatusBar(frame%ptr, c_num, c_style)
    end subroutine

    subroutine wx_frame_set_status_text(frame, text, number)
        type(wxFrame_t), intent(in) :: frame
        character(len=*), intent(in) :: text
        integer, intent(in), optional :: number
        type(c_ptr) :: text_ptr
        integer(c_int) :: c_num
        c_num = 0_c_int
        if (present(number)) c_num = int(number, c_int)
        text_ptr = to_wxstring(text)
        call wxFrame_SetStatusText(frame%ptr, text_ptr, c_num)
        call wxString_Delete(text_ptr)
    end subroutine

    subroutine wx_frame_push_status_text(frame, text, number)
        type(wxFrame_t), intent(in) :: frame
        character(len=*), intent(in) :: text
        integer, intent(in), optional :: number
        type(c_ptr) :: text_ptr
        integer(c_int) :: c_num
        c_num = 0_c_int
        if (present(number)) c_num = int(number, c_int)
        text_ptr = to_wxstring(text)
        call wxFrame_PushStatusText(frame%ptr, text_ptr, c_num)
        call wxString_Delete(text_ptr)
    end subroutine

    subroutine wx_frame_pop_status_text(frame, number)
        type(wxFrame_t), intent(in) :: frame
        integer, intent(in), optional :: number
        integer(c_int) :: c_num
        c_num = 0_c_int
        if (present(number)) c_num = int(number, c_int)
        call wxFrame_PopStatusText(frame%ptr, c_num)
    end subroutine

    !--- Menu bar ---

    subroutine wx_frame_set_menu_bar(frame, menubar)
        type(wxFrame_t), intent(in) :: frame
        type(wxMenuBar_t), intent(in) :: menubar
        call wxFrame_SetMenuBar(frame%ptr, menubar%ptr)
    end subroutine

    function wx_frame_get_menu_bar(frame) result(menubar)
        type(wxFrame_t), intent(in) :: frame
        type(wxMenuBar_t) :: menubar
        menubar%ptr = wxFrame_GetMenuBar(frame%ptr)
    end function

    !--- Toolbar ---

    function wx_frame_create_tool_bar(frame, style) result(toolbar)
        type(wxFrame_t), intent(in) :: frame
        integer(c_long), intent(in), optional :: style
        type(wxToolBar_t) :: toolbar
        integer(c_long) :: c_style
        c_style = -1_c_long
        if (present(style)) c_style = style
        toolbar%ptr = wxFrame_CreateToolBar(frame%ptr, c_style)
    end function

    function wx_frame_get_tool_bar(frame) result(toolbar)
        type(wxFrame_t), intent(in) :: frame
        type(wxToolBar_t) :: toolbar
        toolbar%ptr = wxFrame_GetToolBar(frame%ptr)
    end function

    !--- Window ops ---

    subroutine wx_frame_center(frame, direction)
        type(wxFrame_t), intent(in) :: frame
        integer, intent(in), optional :: direction
        integer(c_int) :: dir
        dir = wxBOTH()
        if (present(direction)) dir = int(direction, c_int)
        call wxWindow_CenterOnParent(frame%ptr, dir)
    end subroutine

    subroutine wx_frame_set_size(frame, width, height)
        type(wxFrame_t), intent(in) :: frame
        integer, intent(in) :: width, height
        call wxWindow_SetSize(frame%ptr, -1_c_int, -1_c_int, &
            int(width, c_int), int(height, c_int), 0_c_int)
    end subroutine

    !--- TopLevelWindow ops ---

    subroutine wx_frame_restore(frame)
        type(wxFrame_t), intent(in) :: frame
        call wxTopLevelWindow_Restore(frame%ptr)
    end subroutine

    subroutine wx_frame_maximize(frame, maximize)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in), optional :: maximize
        integer(c_int) :: c_max
        c_max = 1_c_int
        if (present(maximize)) then
            c_max = 0_c_int
            if (maximize) c_max = 1_c_int
        end if
        call wxTopLevelWindow_Maximize(frame%ptr, c_max)
    end subroutine

    subroutine wx_frame_iconize(frame, iconize)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in), optional :: iconize
        integer(c_int) :: c_ico, dummy
        c_ico = 1_c_int
        if (present(iconize)) then
            c_ico = 0_c_int
            if (iconize) c_ico = 1_c_int
        end if
        dummy = wxTopLevelWindow_Iconize(frame%ptr, c_ico)
    end subroutine

    function wx_frame_is_maximized(frame) result(maximized)
        type(wxFrame_t), intent(in) :: frame
        logical :: maximized
        maximized = (wxTopLevelWindow_IsMaximized(frame%ptr) /= 0)
    end function

    function wx_frame_is_iconized(frame) result(iconized)
        type(wxFrame_t), intent(in) :: frame
        logical :: iconized
        iconized = (wxTopLevelWindow_IsIconized(frame%ptr) /= 0)
    end function

    function wx_frame_show_full_screen(frame, show, style) result(ok)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in) :: show
        integer(c_long), intent(in), optional :: style
        logical :: ok
        integer(c_int) :: c_show
        integer(c_long) :: c_style
        c_show = 0_c_int
        if (show) c_show = 1_c_int
        c_style = 0_c_long
        if (present(style)) c_style = style
        ok = (wxTopLevelWindow_ShowFullScreen(frame%ptr, c_show, c_style) /= 0)
    end function

    function wx_frame_is_full_screen(frame) result(full)
        type(wxFrame_t), intent(in) :: frame
        logical :: full
        full = (wxTopLevelWindow_IsFullScreen(frame%ptr) /= 0)
    end function

    function wx_frame_get_title(frame) result(title)
        type(wxFrame_t), intent(in) :: frame
        character(len=:), allocatable :: title
        type(c_ptr) :: ws_ptr
        ws_ptr = wxTopLevelWindow_GetTitle(frame%ptr)
        title = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_frame_set_title(frame, title)
        type(wxFrame_t), intent(in) :: frame
        character(len=*), intent(in) :: title
        type(c_ptr) :: title_ptr
        title_ptr = to_wxstring(title)
        call wxTopLevelWindow_SetTitle(frame%ptr, title_ptr)
        call wxString_Delete(title_ptr)
    end subroutine

    function wx_frame_is_active(frame) result(active)
        type(wxFrame_t), intent(in) :: frame
        logical :: active
        active = (wxTopLevelWindow_IsActive(frame%ptr) /= 0)
    end function

    function wx_frame_enable_close_button(frame, enable) result(ok)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in), optional :: enable
        logical :: ok
        integer(c_int) :: c_en
        c_en = 1_c_int
        if (present(enable)) then
            c_en = 0_c_int
            if (enable) c_en = 1_c_int
        end if
        ok = (wxTopLevelWindow_EnableCloseButton(frame%ptr, c_en) /= 0)
    end function

    function wx_frame_enable_maximize_button(frame, enable) result(ok)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in), optional :: enable
        logical :: ok
        integer(c_int) :: c_en
        c_en = 1_c_int
        if (present(enable)) then
            c_en = 0_c_int
            if (enable) c_en = 1_c_int
        end if
        ok = (wxTopLevelWindow_EnableMaximizeButton(frame%ptr, c_en) /= 0)
    end function

    function wx_frame_enable_minimize_button(frame, enable) result(ok)
        type(wxFrame_t), intent(in) :: frame
        logical, intent(in), optional :: enable
        logical :: ok
        integer(c_int) :: c_en
        c_en = 1_c_int
        if (present(enable)) then
            c_en = 0_c_int
            if (enable) c_en = 1_c_int
        end if
        ok = (wxTopLevelWindow_EnableMinimizeButton(frame%ptr, c_en) /= 0)
    end function

    subroutine wx_frame_request_user_attention(frame, flags)
        type(wxFrame_t), intent(in) :: frame
        integer, intent(in), optional :: flags
        integer(c_int) :: c_flags
        c_flags = 0_c_int
        if (present(flags)) c_flags = int(flags, c_int)
        call wxTopLevelWindow_RequestUserAttention(frame%ptr, c_flags)
    end subroutine

end module wx_frame
)";
    std::println(stderr, "  Generated wx_frame.f90");
}

// -------------------------------------------------------------------------
// wx_controls.f90 — Control wrappers
// -------------------------------------------------------------------------

void FortranEmitter::GenerateControlsModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_controls.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_controls
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    use wx_string, only: to_wxstring, from_wxstring
    implicit none
    private

    ! wxButton
    public :: wx_button_create, wx_button_set_default

    ! wxTextCtrl
    public :: wx_text_ctrl_create
    public :: wx_text_ctrl_get_value, wx_text_ctrl_set_value
    public :: wx_text_ctrl_change_value
    public :: wx_text_ctrl_clear
    public :: wx_text_ctrl_write_text, wx_text_ctrl_append_text
    public :: wx_text_ctrl_is_modified, wx_text_ctrl_is_editable
    public :: wx_text_ctrl_get_number_of_lines
    public :: wx_text_ctrl_set_hint

    ! wxStaticText
    public :: wx_static_text_create

    ! wxPanel
    public :: wx_panel_create

    ! wxCheckBox
    public :: wx_checkbox_create
    public :: wx_checkbox_get_value, wx_checkbox_set_value

    ! wxRadioButton
    public :: wx_radiobutton_create
    public :: wx_radiobutton_get_value, wx_radiobutton_set_value

    ! wxChoice
    public :: wx_choice_create, wx_choice_append
    public :: wx_choice_delete, wx_choice_clear, wx_choice_get_count
    public :: wx_choice_get_selection, wx_choice_set_selection
    public :: wx_choice_find_string
    public :: wx_choice_get_string, wx_choice_set_string

    ! wxListBox
    public :: wx_listbox_create, wx_listbox_append
    public :: wx_listbox_delete, wx_listbox_clear, wx_listbox_get_count
    public :: wx_listbox_get_selection, wx_listbox_set_selection
    public :: wx_listbox_find_string
    public :: wx_listbox_get_string, wx_listbox_set_string
    public :: wx_listbox_is_selected

    ! wxComboBox
    public :: wx_combobox_create, wx_combobox_append
    public :: wx_combobox_delete, wx_combobox_clear, wx_combobox_get_count
    public :: wx_combobox_get_selection, wx_combobox_set_selection
    public :: wx_combobox_find_string
    public :: wx_combobox_get_string, wx_combobox_set_string
    public :: wx_combobox_get_value, wx_combobox_set_value

contains

    !--- wxButton ---

    function wx_button_create(label, parent, id, x, y, width, height, style) &
            result(button)
        character(len=*), intent(in) :: label
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxButton_t) :: button

        type(c_ptr) :: label_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        label_ptr = to_wxstring(label)
        button%ptr = wxButton_Create(parent%ptr, c_id, label_ptr, &
            c_x, c_y, c_w, c_h, c_style)
        call wxString_Delete(label_ptr)
    end function

    subroutine wx_button_set_default(button)
        type(wxButton_t), intent(in) :: button
        call wxButton_SetDefault(button%ptr)
    end subroutine

    !--- wxTextCtrl ---

    function wx_text_ctrl_create(parent, value, id, x, y, width, height, style) &
            result(ctrl)
        class(wxWindow_t), intent(in) :: parent
        character(len=*), intent(in), optional :: value
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxTextCtrl_t) :: ctrl

        type(c_ptr) :: val_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        if (present(value)) then
            val_ptr = to_wxstring(value)
        else
            val_ptr = to_wxstring("")
        end if

        ctrl%ptr = wxTextCtrl_Create(parent%ptr, c_id, val_ptr, &
            c_x, c_y, c_w, c_h, c_style)
        call wxString_Delete(val_ptr)
    end function

    function wx_text_ctrl_get_value(ctrl) result(value)
        type(wxTextCtrl_t), intent(in) :: ctrl
        character(len=:), allocatable :: value
        type(c_ptr) :: ws_ptr
        ws_ptr = wxTextCtrl_GetValue(ctrl%ptr)
        value = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_text_ctrl_set_value(ctrl, value)
        type(wxTextCtrl_t), intent(in) :: ctrl
        character(len=*), intent(in) :: value
        type(c_ptr) :: val_ptr
        val_ptr = to_wxstring(value)
        call wxTextCtrl_SetValue(ctrl%ptr, val_ptr)
        call wxString_Delete(val_ptr)
    end subroutine

    subroutine wx_text_ctrl_change_value(ctrl, value)
        type(wxTextCtrl_t), intent(in) :: ctrl
        character(len=*), intent(in) :: value
        type(c_ptr) :: val_ptr
        val_ptr = to_wxstring(value)
        call wxTextCtrl_ChangeValue(ctrl%ptr, val_ptr)
        call wxString_Delete(val_ptr)
    end subroutine

    subroutine wx_text_ctrl_clear(ctrl)
        type(wxTextCtrl_t), intent(in) :: ctrl
        call wxTextCtrl_Clear(ctrl%ptr)
    end subroutine

    subroutine wx_text_ctrl_write_text(ctrl, text)
        type(wxTextCtrl_t), intent(in) :: ctrl
        character(len=*), intent(in) :: text
        type(c_ptr) :: text_ptr
        text_ptr = to_wxstring(text)
        call wxTextCtrl_WriteText(ctrl%ptr, text_ptr)
        call wxString_Delete(text_ptr)
    end subroutine

    subroutine wx_text_ctrl_append_text(ctrl, text)
        type(wxTextCtrl_t), intent(in) :: ctrl
        character(len=*), intent(in) :: text
        type(c_ptr) :: text_ptr
        text_ptr = to_wxstring(text)
        call wxTextCtrl_AppendText(ctrl%ptr, text_ptr)
        call wxString_Delete(text_ptr)
    end subroutine

    function wx_text_ctrl_is_modified(ctrl) result(modified)
        type(wxTextCtrl_t), intent(in) :: ctrl
        logical :: modified
        modified = (wxTextCtrl_IsModified(ctrl%ptr) /= 0)
    end function

    function wx_text_ctrl_is_editable(ctrl) result(editable)
        type(wxTextCtrl_t), intent(in) :: ctrl
        logical :: editable
        editable = (wxTextCtrl_IsEditable(ctrl%ptr) /= 0)
    end function

    function wx_text_ctrl_get_number_of_lines(ctrl) result(nlines)
        type(wxTextCtrl_t), intent(in) :: ctrl
        integer :: nlines
        nlines = int(wxTextCtrl_GetNumberOfLines(ctrl%ptr))
    end function

    subroutine wx_text_ctrl_set_hint(ctrl, hint)
        type(wxTextCtrl_t), intent(in) :: ctrl
        character(len=*), intent(in) :: hint
        type(c_ptr) :: hint_ptr
        integer(c_int) :: res
        hint_ptr = to_wxstring(hint)
        res = wxTextEntry_SetHint(ctrl%ptr, hint_ptr)
        call wxString_Delete(hint_ptr)
    end subroutine


        )";  // end first raw string chunk
    output << R"(
    !--- wxStaticText ---

    function wx_static_text_create(label, parent, id, x, y, width, height, &
            style) result(st)
        character(len=*), intent(in) :: label
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxStaticText_t) :: st

        type(c_ptr) :: label_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        label_ptr = to_wxstring(label)
        st%ptr = wxStaticText_Create(parent%ptr, c_id, label_ptr, &
            c_x, c_y, c_w, c_h, c_style)
        call wxString_Delete(label_ptr)
    end function

    !--- wxPanel ---

    function wx_panel_create(parent, id, x, y, width, height, style) &
            result(panel)
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxPanel_t) :: panel

        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = wxTAB_TRAVERSAL()
        if (present(style)) c_style = style

        panel%ptr = wxPanel_Create(parent%ptr, c_id, &
            c_x, c_y, c_w, c_h, c_style)
    end function

    !--- wxCheckBox ---

    function wx_checkbox_create(label, parent, id, x, y, width, height, &
            style) result(cb)
        character(len=*), intent(in) :: label
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxCheckBox_t) :: cb

        type(c_ptr) :: label_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        label_ptr = to_wxstring(label)
        cb%ptr = wxCheckBox_Create(parent%ptr, c_id, label_ptr, &
            c_x, c_y, c_w, c_h, c_style)
        call wxString_Delete(label_ptr)
    end function

    function wx_checkbox_get_value(cb) result(checked)
        type(wxCheckBox_t), intent(in) :: cb
        logical :: checked
        checked = (wxCheckBox_GetValue(cb%ptr) /= 0)
    end function

    subroutine wx_checkbox_set_value(cb, checked)
        type(wxCheckBox_t), intent(in) :: cb
        logical, intent(in) :: checked
        integer(c_int) :: val
        val = 0_c_int
        if (checked) val = 1_c_int
        call wxCheckBox_SetValue(cb%ptr, val)
    end subroutine

    !--- wxRadioButton ---

    function wx_radiobutton_create(label, parent, id, x, y, width, height, &
            style) result(rb)
        character(len=*), intent(in) :: label
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxRadioButton_t) :: rb

        type(c_ptr) :: label_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        label_ptr = to_wxstring(label)
        rb%ptr = wxRadioButton_Create(parent%ptr, c_id, label_ptr, &
            c_x, c_y, c_w, c_h, c_style)
        call wxString_Delete(label_ptr)
    end function

    function wx_radiobutton_get_value(rb) result(selected)
        type(wxRadioButton_t), intent(in) :: rb
        logical :: selected
        selected = (wxRadioButton_GetValue(rb%ptr) /= 0)
    end function

    subroutine wx_radiobutton_set_value(rb, selected)
        type(wxRadioButton_t), intent(in) :: rb
        logical, intent(in) :: selected
        integer(c_int) :: val
        val = 0_c_int
        if (selected) val = 1_c_int
        call wxRadioButton_SetValue(rb%ptr, val)
    end subroutine

    !--- wxChoice ---

    function wx_choice_create(parent, id, x, y, width, height, style) &
            result(choice)
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxChoice_t) :: choice

        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        choice%ptr = wxChoice_Create(parent%ptr, c_id, &
            c_x, c_y, c_w, c_h, 0_c_int, c_null_ptr, c_style)
    end function

    subroutine wx_choice_append(choice, item)
        type(wxChoice_t), intent(in) :: choice
        character(len=*), intent(in) :: item
        type(c_ptr) :: item_ptr
        item_ptr = to_wxstring(item)
        call wxChoice_Append(choice%ptr, item_ptr)
        call wxString_Delete(item_ptr)
    end subroutine

    subroutine wx_choice_delete(choice, index)
        type(wxChoice_t), intent(in) :: choice
        integer, intent(in) :: index
        call wxChoice_Delete(choice%ptr, int(index, c_int))
    end subroutine

    subroutine wx_choice_clear(choice)
        type(wxChoice_t), intent(in) :: choice
        call wxChoice_Clear(choice%ptr)
    end subroutine

    function wx_choice_get_count(choice) result(n)
        type(wxChoice_t), intent(in) :: choice
        integer :: n
        n = int(wxChoice_GetCount(choice%ptr))
    end function

    function wx_choice_get_selection(choice) result(sel)
        type(wxChoice_t), intent(in) :: choice
        integer :: sel
        sel = int(wxChoice_GetSelection(choice%ptr))
    end function

    subroutine wx_choice_set_selection(choice, index)
        type(wxChoice_t), intent(in) :: choice
        integer, intent(in) :: index
        call wxChoice_SetSelection(choice%ptr, int(index, c_int))
    end subroutine

    function wx_choice_find_string(choice, str) result(index)
        type(wxChoice_t), intent(in) :: choice
        character(len=*), intent(in) :: str
        integer :: index
        type(c_ptr) :: str_ptr
        str_ptr = to_wxstring(str)
        index = int(wxChoice_FindString(choice%ptr, str_ptr))
        call wxString_Delete(str_ptr)
    end function

    function wx_choice_get_string(choice, index) result(str)
        type(wxChoice_t), intent(in) :: choice
        integer, intent(in) :: index
        character(len=:), allocatable :: str
        type(c_ptr) :: ws_ptr
        ws_ptr = wxChoice_GetString(choice%ptr, int(index, c_int))
        str = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_choice_set_string(choice, index, str)
        type(wxChoice_t), intent(in) :: choice
        integer, intent(in) :: index
        character(len=*), intent(in) :: str
        type(c_ptr) :: str_ptr
        str_ptr = to_wxstring(str)
        call wxChoice_SetString(choice%ptr, int(index, c_int), str_ptr)
        call wxString_Delete(str_ptr)
    end subroutine
        )";  // end second raw string chunk
    output << R"(

    !--- wxListBox ---

    function wx_listbox_create(parent, id, x, y, width, height, style) &
            result(lb)
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxListBox_t) :: lb

        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        lb%ptr = wxListBox_Create(parent%ptr, c_id, &
            c_x, c_y, c_w, c_h, 0_c_int, c_null_ptr, c_style)
    end function

    subroutine wx_listbox_append(lb, item)
        type(wxListBox_t), intent(in) :: lb
        character(len=*), intent(in) :: item
        type(c_ptr) :: item_ptr
        item_ptr = to_wxstring(item)
        call wxListBox_Append(lb%ptr, item_ptr)
        call wxString_Delete(item_ptr)
    end subroutine

    subroutine wx_listbox_delete(lb, index)
        type(wxListBox_t), intent(in) :: lb
        integer, intent(in) :: index
        call wxListBox_Delete(lb%ptr, int(index, c_int))
    end subroutine

    subroutine wx_listbox_clear(lb)
        type(wxListBox_t), intent(in) :: lb
        call wxListBox_Clear(lb%ptr)
    end subroutine

    function wx_listbox_get_count(lb) result(n)
        type(wxListBox_t), intent(in) :: lb
        integer :: n
        n = int(wxListBox_GetCount(lb%ptr))
    end function

    function wx_listbox_get_selection(lb) result(sel)
        type(wxListBox_t), intent(in) :: lb
        integer :: sel
        sel = int(wxListBox_GetSelection(lb%ptr))
    end function

    subroutine wx_listbox_set_selection(lb, index, sel)
        type(wxListBox_t), intent(in) :: lb
        integer, intent(in) :: index
        logical, intent(in), optional :: sel
        integer(c_int) :: c_sel
        c_sel = 1_c_int
        if (present(sel)) then
            c_sel = 0_c_int
            if (sel) c_sel = 1_c_int
        end if
        call wxListBox_SetSelection(lb%ptr, int(index, c_int), c_sel)
    end subroutine

    function wx_listbox_find_string(lb, str) result(index)
        type(wxListBox_t), intent(in) :: lb
        character(len=*), intent(in) :: str
        integer :: index
        type(c_ptr) :: str_ptr
        str_ptr = to_wxstring(str)
        index = int(wxListBox_FindString(lb%ptr, str_ptr))
        call wxString_Delete(str_ptr)
    end function

    function wx_listbox_get_string(lb, index) result(str)
        type(wxListBox_t), intent(in) :: lb
        integer, intent(in) :: index
        character(len=:), allocatable :: str
        type(c_ptr) :: ws_ptr
        ws_ptr = wxListBox_GetString(lb%ptr, int(index, c_int))
        str = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_listbox_set_string(lb, index, str)
        type(wxListBox_t), intent(in) :: lb
        integer, intent(in) :: index
        character(len=*), intent(in) :: str
        type(c_ptr) :: str_ptr
        str_ptr = to_wxstring(str)
        call wxListBox_SetString(lb%ptr, int(index, c_int), str_ptr)
        call wxString_Delete(str_ptr)
    end subroutine

    function wx_listbox_is_selected(lb, index) result(selected)
        type(wxListBox_t), intent(in) :: lb
        integer, intent(in) :: index
        logical :: selected
        selected = (wxListBox_IsSelected(lb%ptr, int(index, c_int)) /= 0)
    end function

    !--- wxComboBox ---

    function wx_combobox_create(parent, id, value, x, y, width, height, &
            style) result(cb)
        class(wxWindow_t), intent(in) :: parent
        integer, intent(in), optional :: id
        character(len=*), intent(in), optional :: value
        integer, intent(in), optional :: x, y, width, height
        integer(c_long), intent(in), optional :: style
        type(wxComboBox_t) :: cb

        type(c_ptr) :: val_ptr
        integer(c_int) :: c_id, c_x, c_y, c_w, c_h
        integer(c_long) :: c_style

        c_id = wxID_ANY()
        if (present(id)) c_id = int(id, c_int)
        c_x = -1_c_int
        if (present(x)) c_x = int(x, c_int)
        c_y = -1_c_int
        if (present(y)) c_y = int(y, c_int)
        c_w = -1_c_int
        if (present(width)) c_w = int(width, c_int)
        c_h = -1_c_int
        if (present(height)) c_h = int(height, c_int)
        c_style = 0_c_long
        if (present(style)) c_style = style

        if (present(value)) then
            val_ptr = to_wxstring(value)
        else
            val_ptr = to_wxstring("")
        end if

        cb%ptr = wxComboBox_Create(parent%ptr, c_id, val_ptr, &
            c_x, c_y, c_w, c_h, 0_c_int, c_null_ptr, c_style)
        call wxString_Delete(val_ptr)
    end function

    subroutine wx_combobox_append(cb, item)
        type(wxComboBox_t), intent(in) :: cb
        character(len=*), intent(in) :: item
        type(c_ptr) :: item_ptr
        item_ptr = to_wxstring(item)
        call wxComboBox_Append(cb%ptr, item_ptr)
        call wxString_Delete(item_ptr)
    end subroutine

    subroutine wx_combobox_delete(cb, index)
        type(wxComboBox_t), intent(in) :: cb
        integer, intent(in) :: index
        call wxComboBox_Delete(cb%ptr, int(index, c_int))
    end subroutine

    subroutine wx_combobox_clear(cb)
        type(wxComboBox_t), intent(in) :: cb
        call wxComboBox_Clear(cb%ptr)
    end subroutine

    function wx_combobox_get_count(cb) result(n)
        type(wxComboBox_t), intent(in) :: cb
        integer :: n
        n = int(wxComboBox_GetCount(cb%ptr))
    end function

    function wx_combobox_get_selection(cb) result(sel)
        type(wxComboBox_t), intent(in) :: cb
        integer :: sel
        sel = int(wxComboBox_GetSelection(cb%ptr))
    end function

    subroutine wx_combobox_set_selection(cb, index)
        type(wxComboBox_t), intent(in) :: cb
        integer, intent(in) :: index
        call wxComboBox_SetSelection(cb%ptr, int(index, c_int))
    end subroutine

    function wx_combobox_find_string(cb, str) result(index)
        type(wxComboBox_t), intent(in) :: cb
        character(len=*), intent(in) :: str
        integer :: index
        type(c_ptr) :: str_ptr
        str_ptr = to_wxstring(str)
        index = int(wxComboBox_FindString(cb%ptr, str_ptr))
        call wxString_Delete(str_ptr)
    end function

    function wx_combobox_get_string(cb, index) result(str)
        type(wxComboBox_t), intent(in) :: cb
        integer, intent(in) :: index
        character(len=:), allocatable :: str
        type(c_ptr) :: ws_ptr
        ws_ptr = wxComboBox_GetString(cb%ptr, int(index, c_int))
        str = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_combobox_set_string(cb, index, str)
        type(wxComboBox_t), intent(in) :: cb
        integer, intent(in) :: index
        character(len=*), intent(in) :: str
        type(c_ptr) :: str_ptr
        str_ptr = to_wxstring(str)
        call wxComboBox_SetString(cb%ptr, int(index, c_int), str_ptr)
        call wxString_Delete(str_ptr)
    end subroutine

    function wx_combobox_get_value(cb) result(value)
        type(wxComboBox_t), intent(in) :: cb
        character(len=:), allocatable :: value
        type(c_ptr) :: ws_ptr
        ws_ptr = wxComboBox_GetValue(cb%ptr)
        value = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_combobox_set_value(cb, value)
        type(wxComboBox_t), intent(in) :: cb
        character(len=*), intent(in) :: value
        type(c_ptr) :: val_ptr
        val_ptr = to_wxstring(value)
        call wxComboBox_SetValue(cb%ptr, val_ptr)
        call wxString_Delete(val_ptr)
    end subroutine

end module wx_controls
)";
    std::println(stderr, "  Generated wx_controls.f90");
}

// -------------------------------------------------------------------------
// wx_menus.f90 — Menu wrappers
// -------------------------------------------------------------------------

void FortranEmitter::GenerateMenusModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_menus.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_menus
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    use wx_string, only: to_wxstring, from_wxstring
    implicit none
    private

    ! wxMenu
    public :: wx_menu_create, wx_menu_delete
    public :: wx_menu_append, wx_menu_append_separator
    public :: wx_menu_append_check_item
    public :: wx_menu_enable, wx_menu_check
    public :: wx_menu_is_enabled, wx_menu_is_checked
    public :: wx_menu_get_item_count

    ! wxMenuBar
    public :: wx_menubar_create, wx_menubar_append
    public :: wx_menubar_get_menu_count, wx_menubar_get_menu
    public :: wx_menubar_enable_top

    ! wxMenuItem
    public :: wx_menuitem_create, wx_menuitem_delete
    public :: wx_menuitem_get_id, wx_menuitem_is_separator
    public :: wx_menuitem_get_label, wx_menuitem_set_label
    public :: wx_menuitem_is_checked, wx_menuitem_check
    public :: wx_menuitem_is_enabled, wx_menuitem_enable

contains

    !--- wxMenu ---

    function wx_menu_create(title) result(menu)
        character(len=*), intent(in), optional :: title
        type(wxMenu_t) :: menu
        type(c_ptr) :: title_ptr

        if (present(title)) then
            title_ptr = to_wxstring(title)
        else
            title_ptr = to_wxstring("")
        end if
        menu%ptr = wxMenu_Create(title_ptr, 0_c_long)
        call wxString_Delete(title_ptr)
    end function

    subroutine wx_menu_delete(menu)
        type(wxMenu_t), intent(inout) :: menu
        call wxMenu_DeletePointer(menu%ptr)
        menu%ptr = c_null_ptr
    end subroutine

    subroutine wx_menu_append(menu, id, text, help)
        type(wxMenu_t), intent(in) :: menu
        integer, intent(in) :: id
        character(len=*), intent(in) :: text
        character(len=*), intent(in), optional :: help
        type(c_ptr) :: text_ptr, help_ptr

        text_ptr = to_wxstring(text)
        if (present(help)) then
            help_ptr = to_wxstring(help)
        else
            help_ptr = to_wxstring("")
        end if
        call wxMenu_Append(menu%ptr, int(id, c_int), text_ptr, &
            help_ptr, 0_c_int)
        call wxString_Delete(text_ptr)
        call wxString_Delete(help_ptr)
    end subroutine

    subroutine wx_menu_append_separator(menu)
        type(wxMenu_t), intent(in) :: menu
        call wxMenu_AppendSeparator(menu%ptr)
    end subroutine

    subroutine wx_menu_append_check_item(menu, id, text, help)
        type(wxMenu_t), intent(in) :: menu
        integer, intent(in) :: id
        character(len=*), intent(in) :: text
        character(len=*), intent(in), optional :: help
        type(c_ptr) :: text_ptr, help_ptr

        text_ptr = to_wxstring(text)
        if (present(help)) then
            help_ptr = to_wxstring(help)
        else
            help_ptr = to_wxstring("")
        end if
        call wxMenu_AppendCheckItem(menu%ptr, int(id, c_int), &
            text_ptr, help_ptr)
        call wxString_Delete(text_ptr)
        call wxString_Delete(help_ptr)
    end subroutine

    subroutine wx_menu_enable(menu, id, enable)
        type(wxMenu_t), intent(in) :: menu
        integer, intent(in) :: id
        logical, intent(in) :: enable
        integer(c_int) :: c_en
        c_en = 0_c_int
        if (enable) c_en = 1_c_int
        call wxMenu_Enable(menu%ptr, int(id, c_int), c_en)
    end subroutine

    subroutine wx_menu_check(menu, id, check_)
        type(wxMenu_t), intent(in) :: menu
        integer, intent(in) :: id
        logical, intent(in) :: check_
        integer(c_int) :: c_chk
        c_chk = 0_c_int
        if (check_) c_chk = 1_c_int
        call wxMenu_Check(menu%ptr, int(id, c_int), c_chk)
    end subroutine

    function wx_menu_is_enabled(menu, id) result(enabled)
        type(wxMenu_t), intent(in) :: menu
        integer, intent(in) :: id
        logical :: enabled
        enabled = (wxMenu_IsEnabled(menu%ptr, int(id, c_int)) /= 0)
    end function

    function wx_menu_is_checked(menu, id) result(checked)
        type(wxMenu_t), intent(in) :: menu
        integer, intent(in) :: id
        logical :: checked
        checked = (wxMenu_IsChecked(menu%ptr, int(id, c_int)) /= 0)
    end function

    function wx_menu_get_item_count(menu) result(n)
        type(wxMenu_t), intent(in) :: menu
        integer :: n
        n = int(wxMenu_GetMenuItemCount(menu%ptr))
    end function

    !--- wxMenuBar ---

    function wx_menubar_create() result(menubar)
        type(wxMenuBar_t) :: menubar
        menubar%ptr = wxMenuBar_Create(0_c_int)
    end function

    subroutine wx_menubar_append(menubar, menu, title)
        type(wxMenuBar_t), intent(in) :: menubar
        type(wxMenu_t), intent(in) :: menu
        character(len=*), intent(in) :: title
        integer(c_int) :: dummy
        type(c_ptr) :: title_ptr
        title_ptr = to_wxstring(title)
        dummy = wxMenuBar_Append(menubar%ptr, menu%ptr, title_ptr)
        call wxString_Delete(title_ptr)
    end subroutine

    function wx_menubar_get_menu_count(menubar) result(n)
        type(wxMenuBar_t), intent(in) :: menubar
        integer :: n
        n = int(wxMenuBar_GetMenuCount(menubar%ptr))
    end function

    function wx_menubar_get_menu(menubar, pos) result(menu)
        type(wxMenuBar_t), intent(in) :: menubar
        integer, intent(in) :: pos
        type(wxMenu_t) :: menu
        menu%ptr = wxMenuBar_GetMenu(menubar%ptr, int(pos, c_int))
    end function

    subroutine wx_menubar_enable_top(menubar, pos, enable)
        type(wxMenuBar_t), intent(in) :: menubar
        integer, intent(in) :: pos
        logical, intent(in) :: enable
        integer(c_int) :: c_en
        c_en = 0_c_int
        if (enable) c_en = 1_c_int
        call wxMenuBar_EnableTop(menubar%ptr, int(pos, c_int), c_en)
    end subroutine

    !--- wxMenuItem ---

    function wx_menuitem_create(id, text, help) &
            result(item)
        integer, intent(in), optional :: id
        character(len=*), intent(in), optional :: text, help
        type(wxMenuItem_t) :: item

        ! Create a default menu item then configure
        item%ptr = wxMenuItem_Create()

        if (present(id)) then
            call wxMenuItem_SetId(item%ptr, int(id, c_int))
        end if

        if (present(text)) then
            block
                type(c_ptr) :: text_ptr
                text_ptr = to_wxstring(text)
                call wxMenuItem_SetItemLabel(item%ptr, text_ptr)
                call wxString_Delete(text_ptr)
            end block
        end if

        if (present(help)) then
            block
                type(c_ptr) :: help_ptr
                help_ptr = to_wxstring(help)
                call wxMenuItem_SetHelp(item%ptr, help_ptr)
                call wxString_Delete(help_ptr)
            end block
        end if
    end function

    subroutine wx_menuitem_delete(item)
        type(wxMenuItem_t), intent(inout) :: item
        call wxMenuItem_Delete(item%ptr)
        item%ptr = c_null_ptr
    end subroutine

    function wx_menuitem_get_id(item) result(id)
        type(wxMenuItem_t), intent(in) :: item
        integer :: id
        id = int(wxMenuItem_GetId(item%ptr))
    end function

    function wx_menuitem_is_separator(item) result(is_sep)
        type(wxMenuItem_t), intent(in) :: item
        logical :: is_sep
        is_sep = (wxMenuItem_IsSeparator(item%ptr) /= 0)
    end function

    function wx_menuitem_get_label(item) result(label)
        type(wxMenuItem_t), intent(in) :: item
        character(len=:), allocatable :: label
        type(c_ptr) :: ws_ptr
        ws_ptr = wxMenuItem_GetItemLabelText(item%ptr)
        label = from_wxstring(ws_ptr)
        call wxString_Delete(ws_ptr)
    end function

    subroutine wx_menuitem_set_label(item, label)
        type(wxMenuItem_t), intent(in) :: item
        character(len=*), intent(in) :: label
        type(c_ptr) :: label_ptr
        label_ptr = to_wxstring(label)
        call wxMenuItem_SetItemLabel(item%ptr, label_ptr)
        call wxString_Delete(label_ptr)
    end subroutine

    function wx_menuitem_is_checked(item) result(checked)
        type(wxMenuItem_t), intent(in) :: item
        logical :: checked
        checked = (wxMenuItem_IsChecked(item%ptr) /= 0)
    end function

    subroutine wx_menuitem_check(item, check_)
        type(wxMenuItem_t), intent(in) :: item
        logical, intent(in) :: check_
        integer(c_int) :: c_chk
        c_chk = 0_c_int
        if (check_) c_chk = 1_c_int
        call wxMenuItem_Check(item%ptr, c_chk)
    end subroutine

    function wx_menuitem_is_enabled(item) result(enabled)
        type(wxMenuItem_t), intent(in) :: item
        logical :: enabled
        enabled = (wxMenuItem_IsEnabled(item%ptr) /= 0)
    end function

    subroutine wx_menuitem_enable(item, enable)
        type(wxMenuItem_t), intent(in) :: item
        logical, intent(in) :: enable
        integer(c_int) :: c_en
        c_en = 0_c_int
        if (enable) c_en = 1_c_int
        call wxMenuItem_Enable(item%ptr, c_en)
    end subroutine

end module wx_menus
)";
    std::println(stderr, "  Generated wx_menus.f90");
}

// -------------------------------------------------------------------------
// wx_sizers.f90 — Sizer wrappers
// -------------------------------------------------------------------------

void FortranEmitter::GenerateSizersModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_sizers.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_sizers
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    implicit none
    private

    ! wxBoxSizer
    public :: wx_box_sizer_create, wx_box_sizer_get_orientation

    ! wxSizer operations
    public :: wx_sizer_add_window, wx_sizer_add_sizer
    public :: wx_sizer_add_spacer, wx_sizer_add_stretch_spacer
    public :: wx_sizer_layout, wx_sizer_fit, wx_sizer_set_size_hints

    ! Convenience
    public :: wx_window_set_sizer

contains

    !--- wxBoxSizer ---

    function wx_box_sizer_create(orient) result(sizer)
        integer, intent(in) :: orient
        type(wxBoxSizer_t) :: sizer
        sizer%ptr = wxBoxSizer_Create(int(orient, c_int))
    end function

    function wx_box_sizer_get_orientation(sizer) result(orient)
        type(wxBoxSizer_t), intent(in) :: sizer
        integer :: orient
        orient = int(wxBoxSizer_GetOrientation(sizer%ptr))
    end function

    !--- wxSizer operations ---

    subroutine wx_sizer_add_window(sizer, window, proportion, flag, border)
        class(wxSizer_t), intent(in) :: sizer
        class(wxWindow_t), intent(in) :: window
        integer, intent(in), optional :: proportion, flag, border
        integer(c_int) :: c_prop, c_flag, c_border
        c_prop = 0_c_int
        if (present(proportion)) c_prop = int(proportion, c_int)
        c_flag = 0_c_int
        if (present(flag)) c_flag = int(flag, c_int)
        c_border = 0_c_int
        if (present(border)) c_border = int(border, c_int)
        call wxSizer_AddWindow(sizer%ptr, window%ptr, &
            c_prop, c_flag, c_border, c_null_ptr)
    end subroutine

    subroutine wx_sizer_add_sizer(sizer, child, proportion, flag, border)
        class(wxSizer_t), intent(in) :: sizer
        class(wxSizer_t), intent(in) :: child
        integer, intent(in), optional :: proportion, flag, border
        integer(c_int) :: c_prop, c_flag, c_border
        c_prop = 0_c_int
        if (present(proportion)) c_prop = int(proportion, c_int)
        c_flag = 0_c_int
        if (present(flag)) c_flag = int(flag, c_int)
        c_border = 0_c_int
        if (present(border)) c_border = int(border, c_int)
        call wxSizer_AddSizer(sizer%ptr, child%ptr, &
            c_prop, c_flag, c_border, c_null_ptr)
    end subroutine

    subroutine wx_sizer_add_spacer(sizer, width, height, proportion, flag, &
            border)
        class(wxSizer_t), intent(in) :: sizer
        integer, intent(in) :: width, height
        integer, intent(in), optional :: proportion, flag, border
        integer(c_int) :: c_prop, c_flag, c_border
        c_prop = 0_c_int
        if (present(proportion)) c_prop = int(proportion, c_int)
        c_flag = 0_c_int
        if (present(flag)) c_flag = int(flag, c_int)
        c_border = 0_c_int
        if (present(border)) c_border = int(border, c_int)
        call wxSizer_Add(sizer%ptr, int(width, c_int), &
            int(height, c_int), c_prop, c_flag, c_border, c_null_ptr)
    end subroutine

    subroutine wx_sizer_add_stretch_spacer(sizer, proportion)
        class(wxSizer_t), intent(in) :: sizer
        integer, intent(in), optional :: proportion
        integer(c_int) :: c_prop
        c_prop = 1_c_int
        if (present(proportion)) c_prop = int(proportion, c_int)
        call wxSizer_AddStretchSpacer(sizer%ptr, c_prop)
    end subroutine

    subroutine wx_sizer_layout(sizer)
        class(wxSizer_t), intent(in) :: sizer
        call wxSizer_Layout(sizer%ptr)
    end subroutine

    subroutine wx_sizer_fit(sizer, window)
        class(wxSizer_t), intent(in) :: sizer
        class(wxWindow_t), intent(in) :: window
        call wxSizer_Fit(sizer%ptr, window%ptr)
    end subroutine

    subroutine wx_sizer_set_size_hints(sizer, window)
        class(wxSizer_t), intent(in) :: sizer
        class(wxWindow_t), intent(in) :: window
        call wxSizer_SetSizeHints(sizer%ptr, window%ptr)
    end subroutine

    !--- Convenience ---

    subroutine wx_window_set_sizer(window, sizer)
        class(wxWindow_t), intent(in) :: window
        class(wxSizer_t), intent(in) :: sizer
        call wxWindow_SetSizer(window%ptr, sizer%ptr, 1_c_int)
    end subroutine

end module wx_sizers
)";
    std::println(stderr, "  Generated wx_sizers.f90");
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
    use kwxffi, wxClosure_C_ptr => wxClosure_Create
    use wx_string, only: from_wxstring
    implicit none
    private

    ! Connection
    public :: wx_connect, wx_disconnect

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

    ! Private wxClosure binding with c_funptr
    interface
        function wxClosure_Create(fun, data) bind(C, name="wxClosure_Create")
            import :: c_ptr, c_funptr
            type(c_funptr), value :: fun
            type(c_ptr), value :: data
            type(c_ptr) :: wxClosure_Create
        end function
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

        dummy = wxEvtHandler_Connect(window%ptr, c_first, c_last, c_type, &
            wxClosure_Create(fptr, data_ptr))
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
// wx_dialogs.f90 — Dialog wrappers
// -------------------------------------------------------------------------

void FortranEmitter::GenerateDialogsModule(const ParsedFFI& /* ffi_data */, const fs::path& outDir)
{
    ConditionalFileWriter output(outDir / "wx_dialogs.f90");

    output << R"(! Code generated by kwxgen. DO NOT EDIT.
module wx_dialogs
    use, intrinsic :: iso_c_binding
    use kwx_types
    use kwxffi
    use wx_string, only: to_wxstring
    implicit none
    private

    public :: wx_message_box

contains

    function wx_message_box(message, caption, style, parent) result(res)
        character(len=*), intent(in) :: message
        character(len=*), intent(in), optional :: caption
        integer, intent(in), optional :: style
        class(wxWindow_t), intent(in), optional :: parent
        integer :: res

        type(c_ptr) :: msg_ptr, cap_ptr, parent_ptr
        integer(c_int) :: c_style

        msg_ptr = to_wxstring(message)
        if (present(caption)) then
            cap_ptr = to_wxstring(caption)
        else
            cap_ptr = to_wxstring("Message")
        end if
        c_style = ior(wxOK(), wxICON_INFORMATION())
        if (present(style)) c_style = int(style, c_int)
        parent_ptr = c_null_ptr
        if (present(parent)) parent_ptr = parent%ptr

        res = int(kwxMessageBox(msg_ptr, cap_ptr, c_style, &
            parent_ptr, -1_c_int, -1_c_int))

        call wxString_Delete(msg_ptr)
        call wxString_Delete(cap_ptr)
    end function

end module wx_dialogs
)";
    std::println(stderr, "  Generated wx_dialogs.f90");
}
