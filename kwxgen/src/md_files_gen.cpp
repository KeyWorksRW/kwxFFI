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
    std::string_view full_name;  // "Fortran (kwxFFI)", "TypeScript (kwx_ts FFI)", etc.
};

static constexpr std::array<LangMeta, 5> kwx_Languages = { {
    { .key = "fortran", .full_name = "Fortran (kwxFFI)" },
    { .key = "go", .full_name = "Go (CGo FFI)" },
    { .key = "julia", .full_name = "Julia (ccall FFI)" },
    { .key = "lua", .full_name = "LuaJIT (FFI)" },
    // { "perl",       "Perl (FFI::Raw)"        },
    { .key = "typescript", .full_name = "TypeScript (kwx_ts FFI)" },
} };

// ---------------------------------------------------------------------------
// Worked examples
//
// One entry per (language, class). An entry exists only for a class that carries a
// `verified-emitter` record for that language in
// wxUiEditor/src/generate/ffi_ui/verified.json -- a `verified-port`-only class is not
// documentable here. The code is copied from the passing hand-ported reference in
// <repo>/tests/quick_port: only the port's named constants are inlined, a call the port wraps is
// kept on one line, and a parent argument is shown as the frame the form passes. Nothing is
// invented and nothing is borrowed from another language.
//
// Languages are the five keys of kwx_Languages above; `rust` has no AMD page at all.
// Classes are the quick.wxui nodes that pass the verified-emitter gate in all five: wxFrame,
// wxMenuBar, wxMenu, wxStatusBar, wxRichTextCtrl, wxDialog, wxBoxSizer and
// wxStdDialogButtonSizer. wxMenuItem is deliberately absent -- no lane emits a wxMenuItem
// constructor (all six ports call wxMenu.append_by_id), so it has no verified-emitter record.
// ---------------------------------------------------------------------------

struct ClassExample
{
    std::string_view lang;
    std::string_view class_name;
    std::string_view source;  // port file the snippet was copied from
    std::string_view code;    // fenced block body, verbatim from that file
};

static constexpr std::array<ClassExample, 40> kwx_class_examples = { {
    // ---- fortran -- kwxFortran/tests/quick_port/quick_port.f90 ----
    { .lang = "fortran",
      .class_name = "wxFrame",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxwindow_t) :: parent_window
type(wxframe_t) :: form_window
type(wxmenubar_t) :: menubar
type(wxstatusbar_t) :: status_bar

parent_window%ptr = parent
form_window = wx_frame_create(parent_window, wxID_ANY(), "wxFrame test for kwx languages", -1, -1, -1, -1, wxDEFAULT_FRAME_STYLE())

menubar = wx_menu_bar_create(0)
call wx_frame_set_menu_bar(form_window, menubar)

status_bar = wx_frame_create_status_bar(form_window, 1, wxSTB_DEFAULT_STYLE(), wxID_ANY())

call wx_top_level_window_set_min_size(form_window, 500, 300)
call wx_window_center(form_window, wxBOTH())
)md" },
    { .lang = "fortran",
      .class_name = "wxMenuBar",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxmenubar_t) :: menubar
type(wxmenu_t) :: file_menu
integer :: append_index

menubar = wx_menu_bar_create(0)
file_menu = wx_menu_create("&File", 0)
call wx_menu_append_by_id(file_menu, wxID_EXIT())
append_index = wx_menu_bar_append(menubar, file_menu, "&File")
)md" },
    { .lang = "fortran",
      .class_name = "wxMenu",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxmenu_t) :: file_menu

file_menu = wx_menu_create("&File", 0)
call wx_menu_append_by_id(file_menu, wxID_EXIT())
)md" },
    { .lang = "fortran",
      .class_name = "wxStatusBar",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxstatusbar_t) :: status_bar

status_bar = wx_frame_create_status_bar(form_window, 1, wxSTB_DEFAULT_STYLE(), wxID_ANY())
)md" },
    { .lang = "fortran",
      .class_name = "wxRichTextCtrl",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxrichtextctrl_t) :: rich_text

rich_text = wx_rich_text_ctrl_create(form_window, wxID_ANY(), -1, -1, 400, 250, ior(wxVSCROLL(), ior(wxHSCROLL(), wxWANTS_CHARS())))
call wx_window_set_min_size(rich_text, 400, 250)
)md" },
    { .lang = "fortran",
      .class_name = "wxDialog",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxwindow_t) :: parent_window
type(wxdialog_t) :: form_window
type(wxboxsizer_t) :: box_sizer
type(wxstddialogbuttonsizer_t) :: std_btn

parent_window%ptr = parent
form_window = wx_dialog_create(parent_window, wxID_ANY(), "Main Test Dialog", -1, -1, -1, -1, wxDEFAULT_DIALOG_STYLE())
box_sizer = wx_box_sizer_create(wxHORIZONTAL())
std_btn = wx_dialog_create_std_dialog_button_sizer(form_window, int(ior(wxOK(), wxCANCEL()), kind=c_long))
call wx_sizer_add_sizer(box_sizer, std_btn, 0, wxEXPAND(), 0, c_null_ptr)
call wx_window_set_sizer(form_window, box_sizer, .true.)
call wx_window_center(form_window, wxVERTICAL())
)md" },
    { .lang = "fortran",
      .class_name = "wxBoxSizer",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxboxsizer_t) :: box_sizer
type(wxstddialogbuttonsizer_t) :: std_btn

box_sizer = wx_box_sizer_create(wxHORIZONTAL())
std_btn = wx_dialog_create_std_dialog_button_sizer(form_window, int(ior(wxOK(), wxCANCEL()), kind=c_long))
call wx_sizer_add_sizer(box_sizer, std_btn, 0, wxEXPAND(), 0, c_null_ptr)
call wx_window_set_sizer(form_window, box_sizer, .true.)
)md" },
    { .lang = "fortran",
      .class_name = "wxStdDialogButtonSizer",
      .source = "kwxFortran/tests/quick_port/quick_port.f90",
      .code = R"md(type(wxstddialogbuttonsizer_t) :: std_btn

std_btn = wx_dialog_create_std_dialog_button_sizer(form_window, int(ior(wxOK(), wxCANCEL()), kind=c_long))
)md" },

    // ---- go -- kwxGO/tests/quick_port/quick_port_main.go ----
    { .lang = "go",
      .class_name = "wxFrame",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(frame := wx.NewFrame(nil, wx.ID_ANY, "wxFrame test for kwx languages", -1, -1, -1, -1, wx.DEFAULT_FRAME_STYLE)

menubar := wx.NewMenuBar(0)
frame.SetMenuBar(menubar.Ptr())

frame.CreateStatusBar(1, wx.STB_DEFAULT_STYLE, wx.ID_ANY)

frame.SetMinSize(500, 300)
frame.Center(wx.BOTH)
)md" },
    { .lang = "go",
      .class_name = "wxMenuBar",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(menubar := wx.NewMenuBar(0)
fileMenu := wx.NewMenu("&File", 0)
fileMenu.AppendById(wx.ID_EXIT)
menubar.Append(fileMenu.Ptr(), "&File")
)md" },
    { .lang = "go",
      .class_name = "wxMenu",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(fileMenu := wx.NewMenu("&File", 0)
fileMenu.AppendById(wx.ID_EXIT)
)md" },
    { .lang = "go",
      .class_name = "wxStatusBar",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(frame.CreateStatusBar(1, wx.STB_DEFAULT_STYLE, wx.ID_ANY)
)md" },
    { .lang = "go",
      .class_name = "wxRichTextCtrl",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(richText := wx.NewRichTextCtrl(frame.Ptr(), wx.ID_ANY, -1, -1, 400, 250, wx.VSCROLL|wx.HSCROLL|wx.WANTS_CHARS)
richText.SetMinSize(400, 250)
)md" },
    { .lang = "go",
      .class_name = "wxDialog",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(dialog := wx.NewDialog(frame.Ptr(), wx.ID_ANY, "Main Test Dialog", -1, -1, -1, -1, wx.DEFAULT_DIALOG_STYLE)
boxSizer := wx.NewBoxSizer(wx.HORIZONTAL)
stdBtn := dialog.CreateStdDialogButtonSizer(wx.OK | wx.CANCEL)
stdBtnFlags := wx.NewSizerFlags(0)
stdBtnFlags.Expand()
boxSizer.AddSizerFlags(stdBtn, stdBtnFlags.Ptr())
dialog.SetSizer(boxSizer.Ptr(), true)
dialog.Center(wx.VERTICAL)
)md" },
    { .lang = "go",
      .class_name = "wxBoxSizer",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(boxSizer := wx.NewBoxSizer(wx.HORIZONTAL)
stdBtn := dialog.CreateStdDialogButtonSizer(wx.OK | wx.CANCEL)
stdBtnFlags := wx.NewSizerFlags(0)
stdBtnFlags.Expand()
boxSizer.AddSizerFlags(stdBtn, stdBtnFlags.Ptr())
dialog.SetSizer(boxSizer.Ptr(), true)
)md" },
    { .lang = "go",
      .class_name = "wxStdDialogButtonSizer",
      .source = "kwxGO/tests/quick_port/quick_port_main.go",
      .code = R"md(stdBtn := dialog.CreateStdDialogButtonSizer(wx.OK | wx.CANCEL)
)md" },

    // ---- julia -- kwxJulia/tests/quick_port/quick_port_forms.jl ----
    { .lang = "julia",
      .class_name = "wxFrame",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(frame = wxFrame(nothing, KwxFFI.ID_ANY(), "wxFrame test for kwx languages", -1, -1, -1, -1, KwxFFI.DEFAULT_FRAME_STYLE())

menubar = wxMenuBar(0)
set_menu_bar!(frame, menubar)

create_status_bar(frame, 1, KwxFFI.STB_DEFAULT_STYLE(), KwxFFI.ID_ANY())

set_min_size!(frame, 500, 300)
center!(frame, KwxFFI.BOTH())
)md" },
    { .lang = "julia",
      .class_name = "wxMenuBar",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(menubar = wxMenuBar(0)
file_menu = wxMenu("&File", 0)
append_by_id!(file_menu, KwxFFI.ID_EXIT())
append(menubar, file_menu, "&File")
)md" },
    { .lang = "julia",
      .class_name = "wxMenu",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(file_menu = wxMenu("&File", 0)
append_by_id!(file_menu, KwxFFI.ID_EXIT())
)md" },
    { .lang = "julia",
      .class_name = "wxStatusBar",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(create_status_bar(frame, 1, KwxFFI.STB_DEFAULT_STYLE(), KwxFFI.ID_ANY())
)md" },
    { .lang = "julia",
      .class_name = "wxRichTextCtrl",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(rich_text = wxRichTextCtrl(frame, KwxFFI.ID_ANY(), -1, -1, 400, 250, KwxFFI.VSCROLL() | KwxFFI.HSCROLL() | KwxFFI.WANTS_CHARS())
set_min_size!(rich_text, 400, 250)
)md" },
    { .lang = "julia",
      .class_name = "wxDialog",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(dialog = wxDialog(frame, KwxFFI.ID_ANY(), "Main Test Dialog", -1, -1, -1, -1, KwxFFI.DEFAULT_DIALOG_STYLE())
box_sizer = wxBoxSizer(KwxFFI.HORIZONTAL())
std_btn = create_std_dialog_button_sizer(dialog, KwxFFI.OK() | KwxFFI.CANCEL())
add_sizer!(box_sizer, std_btn, 0, KwxFFI.EXPAND(), 0, C_NULL)
set_sizer!(dialog, box_sizer, true)
center!(dialog, KwxFFI.VERTICAL())
)md" },
    { .lang = "julia",
      .class_name = "wxBoxSizer",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(box_sizer = wxBoxSizer(KwxFFI.HORIZONTAL())
std_btn = create_std_dialog_button_sizer(dialog, KwxFFI.OK() | KwxFFI.CANCEL())
add_sizer!(box_sizer, std_btn, 0, KwxFFI.EXPAND(), 0, C_NULL)
set_sizer!(dialog, box_sizer, true)
)md" },
    { .lang = "julia",
      .class_name = "wxStdDialogButtonSizer",
      .source = "kwxJulia/tests/quick_port/quick_port_forms.jl",
      .code = R"md(std_btn = create_std_dialog_button_sizer(dialog, KwxFFI.OK() | KwxFFI.CANCEL())
)md" },

    // ---- lua -- kwxLuaJIT/tests/quick_port/quick_port_main.lua ----
    { .lang = "lua",
      .class_name = "wxFrame",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local frame = wx_classes.wxFrame.Create(nil, wx.ID_ANY, "wxFrame test for kwx languages", -1, -1, -1, -1, wx.DEFAULT_FRAME_STYLE)

local menubar = wx_classes.wxMenuBar.Create(0)
frame:SetMenuBar(menubar)

frame:CreateStatusBar(1, wx.STB_DEFAULT_STYLE, wx.ID_ANY)

frame:SetMinSize(500, 300)
frame:Center(wx.BOTH)
)md" },
    { .lang = "lua",
      .class_name = "wxMenuBar",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local menubar = wx_classes.wxMenuBar.Create(0)
local file_menu = wx_classes.wxMenu.Create("&File", 0)
file_menu:AppendById(wx.ID_EXIT)
menubar:Append(file_menu, "&File")
)md" },
    { .lang = "lua",
      .class_name = "wxMenu",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local file_menu = wx_classes.wxMenu.Create("&File", 0)
file_menu:AppendById(wx.ID_EXIT)
)md" },
    { .lang = "lua",
      .class_name = "wxStatusBar",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(frame:CreateStatusBar(1, wx.STB_DEFAULT_STYLE, wx.ID_ANY)
)md" },
    { .lang = "lua",
      .class_name = "wxRichTextCtrl",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local rich_text = wx_classes.wxRichTextCtrl.Create(frame, wx.ID_ANY, -1, -1, 400, 250, wx.VSCROLL + wx.HSCROLL + wx.WANTS_CHARS)
rich_text:SetMinSize(400, 250)
)md" },
    { .lang = "lua",
      .class_name = "wxDialog",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local dialog = wx_classes.wxDialog.Create(frame, wx.ID_ANY, "Main Test Dialog", -1, -1, -1, -1, wx.DEFAULT_DIALOG_STYLE)
local box_sizer = wx_classes.wxBoxSizer.Create(wx.HORIZONTAL)
local std_btn = dialog:CreateStdDialogButtonSizer(wx.OK + wx.CANCEL)
box_sizer:AddSizer(std_btn, 0, wx.EXPAND, 0, nil)
dialog:SetSizer(box_sizer:Ptr(), true)
dialog:Center(wx.VERTICAL)
)md" },
    { .lang = "lua",
      .class_name = "wxBoxSizer",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local box_sizer = wx_classes.wxBoxSizer.Create(wx.HORIZONTAL)
local std_btn = dialog:CreateStdDialogButtonSizer(wx.OK + wx.CANCEL)
box_sizer:AddSizer(std_btn, 0, wx.EXPAND, 0, nil)
dialog:SetSizer(box_sizer:Ptr(), true)
)md" },
    { .lang = "lua",
      .class_name = "wxStdDialogButtonSizer",
      .source = "kwxLuaJIT/tests/quick_port/quick_port_main.lua",
      .code = R"md(local std_btn = dialog:CreateStdDialogButtonSizer(wx.OK + wx.CANCEL)
)md" },

    // ---- typescript -- kwxTypeScript/tests/quick_port/quick_port_main.ts ----
    { .lang = "typescript",
      .class_name = "wxFrame",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const frame = createWxFrame(null, ID_ANY, createWxString("wxFrame test for kwx languages").ptr, -1, -1, -1, -1, DEFAULT_FRAME_STYLE)!;
const menubar = createWxMenuBar(0)!;
frame.SetMenuBar(menubar.ptr);
frame.CreateStatusBar(1, STB_DEFAULT_STYLE, ID_ANY);
frame.SetMinSize(500, 300);
frame.Center(BOTH);
)md" },
    { .lang = "typescript",
      .class_name = "wxMenuBar",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const menubar = createWxMenuBar(0)!;
const fileMenu = createWxMenu(createWxString("&File").ptr, BigInt(0))!;
fileMenu.AppendById(ID_EXIT);
menubar.Append(fileMenu.ptr, createWxString("&File").ptr);
)md" },
    { .lang = "typescript",
      .class_name = "wxMenu",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const fileMenu = createWxMenu(createWxString("&File").ptr, BigInt(0))!;
fileMenu.AppendById(ID_EXIT);
)md" },
    { .lang = "typescript",
      .class_name = "wxStatusBar",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(frame.CreateStatusBar(1, STB_DEFAULT_STYLE, ID_ANY);
)md" },
    { .lang = "typescript",
      .class_name = "wxRichTextCtrl",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const richText = createWxRichTextCtrl(frame.ptr, ID_ANY, -1, -1, 400, 250, VSCROLL | HSCROLL | WANTS_CHARS)!;
richText.SetMinSize(400, 250);
)md" },
    { .lang = "typescript",
      .class_name = "wxDialog",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const dialog = createWxDialog(frame.ptr, ID_ANY, createWxString("Main Test Dialog").ptr, -1, -1, -1, -1, DEFAULT_DIALOG_STYLE)!;
const boxSizer = createWxBoxSizer(HORIZONTAL)!;
const stdBtn = dialog.CreateStdDialogButtonSizer(BigInt(OK | CANCEL))!;
boxSizer.AddSizer(stdBtn.ptr, 0, EXPAND, 0, null);
dialog.SetSizer(boxSizer.ptr, true);
dialog.Center(VERTICAL);
)md" },
    { .lang = "typescript",
      .class_name = "wxBoxSizer",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const boxSizer = createWxBoxSizer(HORIZONTAL)!;
const stdBtn = dialog.CreateStdDialogButtonSizer(BigInt(OK | CANCEL))!;
boxSizer.AddSizer(stdBtn.ptr, 0, EXPAND, 0, null);
dialog.SetSizer(boxSizer.ptr, true);
)md" },
    { .lang = "typescript",
      .class_name = "wxStdDialogButtonSizer",
      .source = "kwxTypeScript/tests/quick_port/quick_port_main.ts",
      .code = R"md(const stdBtn = dialog.CreateStdDialogButtonSizer(BigInt(OK | CANCEL))!;
)md" },
} };

// Returns the example recorded for (lang, class), or nullptr when the class is not documented
// for that language.
static const ClassExample* FindClassExample(std::string_view lang, std::string_view class_name)
{
    for (const ClassExample& example: kwx_class_examples)
    {
        if (example.lang == lang && example.class_name == class_name)
        {
            return &example;
        }
    }
    return nullptr;
}

// Append the worked example for (lang, class) when one is recorded. A class without an
// example entry keeps its page unchanged.
static void WriteClassExample(std::string_view lang, std::string_view class_name,
                              ConditionalFileWriter& out)
{
    const ClassExample* example = FindClassExample(lang, class_name);
    if (example == nullptr)
    {
        return;
    }

    out << "\n## Example\n\n";
    out << "From `" << example->source << "` (the port's named constants inlined, a call the port wraps "
                                              "kept on one line, and its parent argument shown as the "
                                              "frame the form passes):\n\n";
    out << "```" << example->lang << "\n";
    out << example->code;
    out << "```\n";
}

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

    // Section 6 — Worked example, only for classes with a verified-emitter record
    WriteClassExample(lang.key, class_info.name, out);
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
        // The wx-prefixed spelling is the one the docstrings promise, and the Julia binding
        // emits it as a deprecated alias.  Document both names.
        if (event.export_name.starts_with("exp_wx") && !event.event_name.starts_with("wx"))
        {
            out << "wx" << event.event_name << "(id, handler)  (deprecated alias)\n";
        }
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
