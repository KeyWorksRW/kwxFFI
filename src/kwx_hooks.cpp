// Callback overrides for the wxWidgets virtuals a foreign language cannot
// implement itself.  The classes live in include/kwx_helper_hooks.h; this file
// defines their constructors, their virtual overrides, and the exported
// kwx<Base>_Create/_Delete/SetOn* functions.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <unordered_set>

// The class definitions live in include/kwx_helper_hooks.h; that header now
// carries no export declarations, so it needs no suppression macro.  The
// exported kwx<Base>_* functions are defined below inside an extern "C" block;
// their declarations live in include/kwx_hook_exports.h, which kwx_classes.h
// includes so kwxgen sees every one of them.
#include "kwx_helper_hooks.h"

// wxAppConsoleBase's constructor installs the object as the process-wide
// application singleton (wxWidgets src/common/appbase.cpp:147) and its
// destructor clears it (:162).  The two application helpers in this file
// therefore change what wxApp_GetApp() returns; that is inherent to
// constructing a wxAppConsole, not something this wrapper can avoid.
//
// wxApp is a channel-specific class (wx/msw/app.h on MSW, wx/osx/app.h on
// macOS, ...), so the wxApp hook is compiled only where GUI wxWidgets exists.
#if wxUSE_GUI
    #define KWX_HAVE_APP_HOOK 1
#else
    #define KWX_HAVE_APP_HOOK 0
#endif

// ---------------------------------------------------------------------------
// wxAppConsole
// ---------------------------------------------------------------------------

kwxAppConsole::kwxAppConsole(void* pObject) : wxAppConsole()
{
    m_object = pObject;
    m_on_cmd_line_parsed_func = nullptr;
    m_on_init_cmd_line_func = nullptr;
    m_on_exit_func = nullptr;
    m_on_run_func = nullptr;
    m_on_assert_failure_func = nullptr;
    m_on_event_loop_enter_func = nullptr;
    m_on_exception_in_main_loop_func = nullptr;
    m_store_current_exception_func = nullptr;
    m_on_fatal_exception_func = nullptr;
    m_on_unhandled_exception_func = nullptr;
    m_rethrow_stored_exception_func = nullptr;
    m_create_traits_func = nullptr;
}

bool kwxAppConsole::OnCmdLineParsed(wxCmdLineParser& parser)
{
    if (!m_on_cmd_line_parsed_func)
    {
        return wxAppConsole::OnCmdLineParsed(parser);
    }
    return m_on_cmd_line_parsed_func(m_object, &parser) != 0;
}

void kwxAppConsole::OnInitCmdLine(wxCmdLineParser& parser)
{
    if (!m_on_init_cmd_line_func)
    {
        wxAppConsole::OnInitCmdLine(parser);
        return;
    }
    m_on_init_cmd_line_func(m_object, &parser);
}

int kwxAppConsole::OnExit()
{
    if (!m_on_exit_func)
    {
        return wxAppConsole::OnExit();
    }
    return m_on_exit_func(m_object);
}

int kwxAppConsole::OnRun()
{
    if (!m_on_run_func)
    {
        return wxAppConsole::OnRun();
    }
    return m_on_run_func(m_object);
}

void kwxAppConsole::OnAssertFailure(const wxChar* file, int line, const wxChar* func,
                                    const wxChar* cond, const wxChar* msg)
{
    if (!m_on_assert_failure_func)
    {
        wxAppConsole::OnAssertFailure(file, line, func, cond, msg);
        return;
    }

    // The callback receives UTF-8 text, so the wxChar arguments are converted
    // into temporaries that stay alive for the duration of the call.
    const wxString file_text = file ? wxString(file) : wxString();
    const wxString func_text = func ? wxString(func) : wxString();
    const wxString cond_text = cond ? wxString(cond) : wxString();
    const wxString msg_text = msg ? wxString(msg) : wxString();
    m_on_assert_failure_func(
        m_object, (void*) file_text.utf8_str().data(), line, (void*) func_text.utf8_str().data(),
        (void*) cond_text.utf8_str().data(), (void*) msg_text.utf8_str().data());
}

void kwxAppConsole::OnEventLoopEnter(wxEventLoopBase* loop)
{
    if (!m_on_event_loop_enter_func)
    {
        wxAppConsole::OnEventLoopEnter(loop);
        return;
    }
    m_on_event_loop_enter_func(m_object, loop);
}

void kwxAppConsole::OnFatalException()
{
    if (!m_on_fatal_exception_func)
    {
        wxAppConsole::OnFatalException();
        return;
    }
    m_on_fatal_exception_func(m_object);
}

// The four exception hooks exist only when wxWidgets is built with
// wxUSE_EXCEPTIONS, which every kwxFFI build is (the library targets MSW with
// exceptions on).  They are defined unconditionally so they match the
// unguarded declarations in kwx_helper_hooks.h.
void kwxAppConsole::OnUnhandledException()
{
    if (!m_on_unhandled_exception_func)
    {
        wxAppConsole::OnUnhandledException();
        return;
    }
    m_on_unhandled_exception_func(m_object);
}

bool kwxAppConsole::OnExceptionInMainLoop()
{
    if (!m_on_exception_in_main_loop_func)
    {
        return wxAppConsole::OnExceptionInMainLoop();
    }
    return m_on_exception_in_main_loop_func(m_object) != 0;
}

bool kwxAppConsole::StoreCurrentException()
{
    if (!m_store_current_exception_func)
    {
        return wxAppConsole::StoreCurrentException();
    }
    return m_store_current_exception_func(m_object) != 0;
}

void kwxAppConsole::RethrowStoredException()
{
    if (!m_rethrow_stored_exception_func)
    {
        wxAppConsole::RethrowStoredException();
        return;
    }
    m_rethrow_stored_exception_func(m_object);
}

wxAppTraits* kwxAppConsole::CreateTraits()
{
    if (!m_create_traits_func)
    {
        return wxAppConsole::CreateTraits();
    }
    return static_cast<wxAppTraits*>(m_create_traits_func(m_object));
}

// ---------------------------------------------------------------------------
// wxApp
// ---------------------------------------------------------------------------

#if KWX_HAVE_APP_HOOK

kwxApp::kwxApp(void* pObject) : wxApp()
{
    m_object = pObject;
    m_on_cmd_line_parsed_func = nullptr;
    m_on_init_cmd_line_func = nullptr;
    m_on_exit_func = nullptr;
    m_filter_event_func = nullptr;
    m_get_class_info_func = nullptr;
    m_on_assert_failure_func = nullptr;
    m_create_traits_func = nullptr;
}

bool kwxApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
    if (!m_on_cmd_line_parsed_func)
    {
        return wxApp::OnCmdLineParsed(parser);
    }
    return m_on_cmd_line_parsed_func(m_object, &parser) != 0;
}

void kwxApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    if (!m_on_init_cmd_line_func)
    {
        wxApp::OnInitCmdLine(parser);
        return;
    }
    m_on_init_cmd_line_func(m_object, &parser);
}

int kwxApp::OnExit()
{
    if (!m_on_exit_func)
    {
        return wxApp::OnExit();
    }
    return m_on_exit_func(m_object);
}

int kwxApp::FilterEvent(wxEvent& event)
{
    if (!m_filter_event_func)
    {
        return wxApp::FilterEvent(event);
    }
    return m_filter_event_func(m_object, &event);
}

wxClassInfo* kwxApp::GetClassInfo() const
{
    if (!m_get_class_info_func)
    {
        return wxApp::GetClassInfo();
    }
    return static_cast<wxClassInfo*>(m_get_class_info_func(m_object));
}

void kwxApp::OnAssertFailure(const wxChar* file, int line, const wxChar* func, const wxChar* cond,
                             const wxChar* msg)
{
    if (!m_on_assert_failure_func)
    {
        wxApp::OnAssertFailure(file, line, func, cond, msg);
        return;
    }

    const wxString file_text = file ? wxString(file) : wxString();
    const wxString func_text = func ? wxString(func) : wxString();
    const wxString cond_text = cond ? wxString(cond) : wxString();
    const wxString msg_text = msg ? wxString(msg) : wxString();
    m_on_assert_failure_func(
        m_object, (void*) file_text.utf8_str().data(), line, (void*) func_text.utf8_str().data(),
        (void*) cond_text.utf8_str().data(), (void*) msg_text.utf8_str().data());
}

wxAppTraits* kwxApp::CreateTraits()
{
    if (!m_create_traits_func)
    {
        return wxApp::CreateTraits();
    }
    return static_cast<wxAppTraits*>(m_create_traits_func(m_object));
}

#endif  // KWX_HAVE_APP_HOOK

// ---------------------------------------------------------------------------
// wxObject
// ---------------------------------------------------------------------------

kwxObject::kwxObject(void* pObject) : wxObject()
{
    m_object = pObject;
    m_get_class_info_func = nullptr;
}

wxClassInfo* kwxObject::GetClassInfo() const
{
    if (!m_get_class_info_func)
    {
        return wxObject::GetClassInfo();
    }
    return static_cast<wxClassInfo*>(m_get_class_info_func(m_object));
}

// ---------------------------------------------------------------------------
// wxEvtHandler
// ---------------------------------------------------------------------------

kwxEvtHandler::kwxEvtHandler(void* pObject) : wxEvtHandler()
{
    m_object = pObject;
    m_process_event_func = nullptr;
}

bool kwxEvtHandler::ProcessEvent(wxEvent& event)
{
    if (!m_process_event_func)
    {
        return wxEvtHandler::ProcessEvent(event);
    }
    return m_process_event_func(m_object, &event) != 0;
}

// ---------------------------------------------------------------------------
// wxPanel
// ---------------------------------------------------------------------------

kwxPanel::kwxPanel(void* pObject, wxWindow* parent, wxWindowID id, const wxPoint& pos,
                   const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
    m_object = pObject;
    m_transfer_data_from_window_func = nullptr;
    m_transfer_data_to_window_func = nullptr;
    m_do_get_best_client_size_func = nullptr;
    m_scroll_window_func = nullptr;
}

bool kwxPanel::TransferDataFromWindow()
{
    if (!m_transfer_data_from_window_func)
    {
        return wxPanel::TransferDataFromWindow();
    }
    return m_transfer_data_from_window_func(m_object) != 0;
}

bool kwxPanel::TransferDataToWindow()
{
    if (!m_transfer_data_to_window_func)
    {
        return wxPanel::TransferDataToWindow();
    }
    return m_transfer_data_to_window_func(m_object) != 0;
}

wxSize kwxPanel::DoGetBestClientSize() const
{
    if (!m_do_get_best_client_size_func)
    {
        return wxPanel::DoGetBestClientSize();
    }

    int width = 0;
    int height = 0;
    m_do_get_best_client_size_func(m_object, &width, &height);
    return wxSize(width, height);
}

void kwxPanel::ScrollWindow(int dx, int dy, const wxRect* rect)
{
    if (!m_scroll_window_func)
    {
        wxPanel::ScrollWindow(dx, dy, rect);
        return;
    }
    m_scroll_window_func(m_object, dx, dy, (void*) rect);
}

// ---------------------------------------------------------------------------
// wxVarHScrollHelper / wxVarVScrollHelper
//
// Neither helper can report its own target size: GetOrientationTargetSize() and
// GetNonOrientationTargetSize() are pure virtual on wxVarScrollHelperBase
// (wx/vscroll.h:139-140).  Both are forwarded to the target window, the same
// way wxVarVScrollHelper and wxVarHScrollHelper do it themselves
// (wx/vscroll.h:329-332 and :409-412).
// ---------------------------------------------------------------------------

kwxVarHScrollHelper::kwxVarHScrollHelper(wxWindow* winToScroll, void* pObject) :
    wxVarHScrollHelper(winToScroll)
{
    m_object = pObject;
    m_on_get_column_width_func = nullptr;
}

wxCoord kwxVarHScrollHelper::OnGetColumnWidth(size_t n) const
{
    if (!m_on_get_column_width_func)
    {
        return 0;
    }
    return m_on_get_column_width_func(m_object, n);
}

kwxVarVScrollHelper::kwxVarVScrollHelper(wxWindow* winToScroll, void* pObject) :
    wxVarVScrollHelper(winToScroll)
{
    m_object = pObject;
    m_on_get_row_height_func = nullptr;
}

wxCoord kwxVarVScrollHelper::OnGetRowHeight(size_t n) const
{
    if (!m_on_get_row_height_func)
    {
        return 0;
    }
    return m_on_get_row_height_func(m_object, n);
}

// ---------------------------------------------------------------------------
// wxTimer
// ---------------------------------------------------------------------------

kwxTimer::kwxTimer(void* pObject) : wxTimer()
{
    m_object = pObject;
    m_notify_func = nullptr;
}

void kwxTimer::Notify()
{
    if (!m_notify_func)
    {
        wxTimer::Notify();
        return;
    }
    m_notify_func(m_object);
}

// ---------------------------------------------------------------------------
// wxValidator
//
// Clone() must return a fresh object because wxWidgets copies validators by
// cloning; without a callback it falls back to the wxWidgets default (nullptr).
// ---------------------------------------------------------------------------

kwxValidator::kwxValidator(void* pObject) : wxValidator()
{
    m_object = pObject;
    m_clone_func = nullptr;
    m_validate_func = nullptr;
    m_transfer_from_window_func = nullptr;
    m_transfer_to_window_func = nullptr;
}

wxObject* kwxValidator::Clone() const
{
    if (!m_clone_func)
    {
        return wxValidator::Clone();
    }
    return static_cast<wxObject*>(m_clone_func(m_object));
}

bool kwxValidator::Validate(wxWindow* parent)
{
    if (!m_validate_func)
    {
        return wxValidator::Validate(parent);
    }
    return m_validate_func(m_object, parent) != 0;
}

bool kwxValidator::TransferFromWindow()
{
    if (!m_transfer_from_window_func)
    {
        return wxValidator::TransferFromWindow();
    }
    return m_transfer_from_window_func(m_object) != 0;
}

bool kwxValidator::TransferToWindow()
{
    if (!m_transfer_to_window_func)
    {
        return wxValidator::TransferToWindow();
    }
    return m_transfer_to_window_func(m_object) != 0;
}

// ---------------------------------------------------------------------------
// wxPreferencesPage
//
// GetName() and CreateWindow() are pure virtual, so both need a callback for
// the class to be instantiable at all; an unset callback yields an empty name
// and no window rather than an assertion.
// ---------------------------------------------------------------------------

kwxPreferencesPage::kwxPreferencesPage(void* pObject) : wxPreferencesPage()
{
    m_object = pObject;
    m_get_name_func = nullptr;
    m_create_window_func = nullptr;
    m_get_icon_func = nullptr;
}

wxString kwxPreferencesPage::GetName() const
{
    if (!m_get_name_func)
    {
        return wxString();
    }
    void* raw_name = m_get_name_func(m_object);
    if (!raw_name)
    {
        return wxString();
    }
    const wxString page_name(static_cast<const char*>(raw_name));
    return page_name;
}

wxWindow* kwxPreferencesPage::CreateWindow(wxWindow* parent)
{
    if (!m_create_window_func)
    {
        return nullptr;
    }
    return static_cast<wxWindow*>(m_create_window_func(m_object, parent));
}

// GetIcon() is not pure virtual, so an unset callback keeps the wxWidgets
// default icon instead of overriding it with an empty bundle.
wxBitmapBundle kwxPreferencesPage::GetIcon() const
{
    if (!m_get_icon_func)
    {
        return wxPreferencesPage::GetIcon();
    }

    wxBitmapBundle* raw_icon = static_cast<wxBitmapBundle*>(m_get_icon_func(m_object));
    if (!raw_icon)
    {
        return wxBitmapBundle();
    }

    const wxBitmapBundle page_icon = *raw_icon;
    delete raw_icon;
    return page_icon;
}

// ---------------------------------------------------------------------------
// wxHtmlListBox
//
// OnGetItem() is pure virtual on wxHtmlListBox (wx/htmllbox.h:91), so an unset
// callback yields an empty row rather than an assertion.
// ---------------------------------------------------------------------------

kwxHtmlListBox::kwxHtmlListBox(void* pObject, wxWindow* parent, wxWindowID id, const wxPoint& pos,
                               const wxSize& size, long style) :
    wxHtmlListBox(parent, id, pos, size, style)
{
    m_object = pObject;
    m_on_get_item_func = nullptr;
    m_get_selected_text_colour_func = nullptr;
}

wxString kwxHtmlListBox::OnGetItem(size_t n) const
{
    if (!m_on_get_item_func)
    {
        return wxString();
    }

    void* raw_item = m_on_get_item_func(m_object, n);
    if (!raw_item)
    {
        return wxString();
    }
    const wxString item_text(static_cast<const char*>(raw_item));
    return item_text;
}

wxColour kwxHtmlListBox::GetSelectedTextColour(const wxColour& colFg) const
{
    if (!m_get_selected_text_colour_func)
    {
        return wxHtmlListBox::GetSelectedTextColour(colFg);
    }

    wxColour* raw_colour =
        static_cast<wxColour*>(m_get_selected_text_colour_func(m_object, (void*) &colFg));
    if (!raw_colour)
    {
        return wxHtmlListBox::GetSelectedTextColour(colFg);
    }

    const wxColour selection_colour = *raw_colour;
    delete raw_colour;
    return selection_colour;
}

// ---------------------------------------------------------------------------
// wxVListBox
//
// OnDrawItem() and OnMeasureItem() are pure virtual on wxVListBox
// (wx/vlbox.h:215, :219), so both need a callback for the class to be
// instantiable.  OnDrawSeparator() is optional (wx/vlbox.h:226); an unset
// callback keeps the wxWidgets behaviour of drawing nothing between rows.
// ---------------------------------------------------------------------------

kwxVListBox::kwxVListBox(void* pObject, wxWindow* parent, wxWindowID id, const wxPoint& pos,
                         const wxSize& size, long style) : wxVListBox(parent, id, pos, size, style)
{
    m_object = pObject;
    m_on_draw_item_func = nullptr;
    m_on_draw_separator_func = nullptr;
    m_on_measure_item_func = nullptr;
}

void kwxVListBox::OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const
{
    if (!m_on_draw_item_func)
    {
        return;
    }

    // The callback receives a writable rect pointer, so the const reference is
    // copied: a callback that modifies it cannot corrupt the caller's rectangle.
    wxRect mutable_rect = rect;
    m_on_draw_item_func(m_object, &dc, &mutable_rect, n);
}

void kwxVListBox::OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const
{
    if (!m_on_draw_separator_func)
    {
        wxVListBox::OnDrawSeparator(dc, rect, n);
        return;
    }
    m_on_draw_separator_func(m_object, &dc, &rect, n);
}

wxCoord kwxVListBox::OnMeasureItem(size_t n) const
{
    if (!m_on_measure_item_func)
    {
        // OnMeasureItem() is pure virtual, so there is no base implementation to
        // fall back to.  One character height is the smallest height at which a
        // row can still show text; a callback that returns -1 also gets it.
        return GetCharHeight();
    }

    const int item_height = m_on_measure_item_func(m_object, n);
    if (item_height < 0)
    {
        return GetCharHeight();
    }
    return item_height;
}

// ---------------------------------------------------------------------------
// wxRendererNative
//
// The class derives from wxDelegateRendererNative, which forwards all 28
// pure virtuals to a delegate (wx/renderer.h:431-604); only the two virtuals
// this hook replaces are implemented here.
// ---------------------------------------------------------------------------

kwxRendererNative::kwxRendererNative(void* pObject) : wxDelegateRendererNative()
{
    m_object = pObject;
    m_draw_header_button_func = nullptr;
    m_get_version_func = nullptr;
}

int kwxRendererNative::DrawHeaderButton(wxWindow* win, wxDC& dc, const wxRect& rect, int flags,
                                        wxHeaderSortIconType sortArrow,
                                        wxHeaderButtonParams* params)
{
    if (!m_draw_header_button_func)
    {
        return wxDelegateRendererNative::DrawHeaderButton(win, dc, rect, flags, sortArrow, params);
    }

    const wxRect mutable_rect = rect;
    return m_draw_header_button_func(m_object, win, &dc, (void*) &mutable_rect, flags,
                                     (int) sortArrow, params);
}

wxRendererVersion kwxRendererNative::GetVersion() const
{
    if (!m_get_version_func)
    {
        return wxDelegateRendererNative::GetVersion();
    }

    // wxRendererVersion has no default constructor, so the callback fills two
    // ints that are then packed into the value wxWidgets expects.
    int version = wxRendererVersion::Current_Version;
    int age = wxRendererVersion::Current_Age;
    m_get_version_func(m_object, &version, &age);
    return wxRendererVersion(version, age);
}

// ---------------------------------------------------------------------------
// wxModalDialogHook
// ---------------------------------------------------------------------------

kwxModalDialogHook::kwxModalDialogHook(void* pObject) : wxModalDialogHook()
{
    m_object = pObject;
    m_enter_func = nullptr;
    m_exit_func = nullptr;
    m_capture_enter_dialog = false;
}

int kwxModalDialogHook::Enter(wxDialog* dialog)
{
    if (m_capture_enter_dialog)
    {
        // A void-capable binding cannot return an id, so its callback's return
        // value is meaningless; capture the dialog and let it be shown instead.
        if (m_enter_func)
        {
            m_enter_func(m_object, dialog);
        }
        return wxID_NONE;
    }
    if (!m_enter_func)
    {
        // There is no wxModalDialogHook implementation to fall back to:
        // Enter() is pure virtual.  wxID_NONE is what every wxWidgets hook
        // returns to let the dialog be shown (wx/modalhook.h:66-69).
        return wxID_NONE;
    }
    return m_enter_func(m_object, dialog);
}

void kwxModalDialogHook::Exit(wxDialog* dialog)
{
    if (!m_exit_func)
    {
        wxModalDialogHook::Exit(dialog);
        return;
    }
    m_exit_func(m_object, dialog);
}

// ---------------------------------------------------------------------------
// wxAddRemoveAdaptor
// ---------------------------------------------------------------------------

kwxAddRemoveAdaptor::kwxAddRemoveAdaptor(void* pObject)
{
    m_object = pObject;
    m_get_items_ctrl_func = nullptr;
    m_can_add_func = nullptr;
    m_can_remove_func = nullptr;
    m_on_add_func = nullptr;
    m_on_remove_func = nullptr;
    m_items_ctrl = nullptr;
    m_can_add = false;
    m_can_remove = false;
}

wxWindow* kwxAddRemoveAdaptor::GetItemsCtrl() const
{
    if (!m_get_items_ctrl_func)
    {
        return m_items_ctrl;
    }
    return static_cast<wxWindow*>(m_get_items_ctrl_func(m_object, nullptr, nullptr));
}

bool kwxAddRemoveAdaptor::CanAdd() const
{
    if (!m_can_add_func)
    {
        return m_can_add;
    }
    return m_can_add_func(m_object, nullptr, nullptr) != 0;
}

bool kwxAddRemoveAdaptor::CanRemove() const
{
    if (!m_can_remove_func)
    {
        return m_can_remove;
    }
    return m_can_remove_func(m_object, nullptr, nullptr) != 0;
}

void kwxAddRemoveAdaptor::OnAdd()
{
    if (!m_on_add_func)
    {
        return;
    }
    m_on_add_func(m_object, nullptr, nullptr);
}

void kwxAddRemoveAdaptor::OnRemove()
{
    if (!m_on_remove_func)
    {
        return;
    }
    m_on_remove_func(m_object, nullptr, nullptr);
}

// ---------------------------------------------------------------------------
// wxTextCompleterSimple
// ---------------------------------------------------------------------------

kwxTextCompleterSimple::kwxTextCompleterSimple(void* pObject) : wxTextCompleterSimple()
{
    m_object = pObject;
    m_get_completions_func = nullptr;
}

void kwxTextCompleterSimple::GetCompletions(const wxString& prefix, wxArrayString& result)
{
    if (!m_get_completions_func)
    {
        return;
    }
    m_get_completions_func(m_object, (void*) &prefix, &result);
}

// ---------------------------------------------------------------------------
// wxHtmlTagsModule
// ---------------------------------------------------------------------------

kwxHtmlTagsModule::kwxHtmlTagsModule(void* pObject) : wxHtmlTagsModule()
{
    m_object = pObject;
    m_fill_handlers_table_func = nullptr;
}

// OnInit()/OnExit() are pure virtual on wxModule.  A hook object is a plain
// callbacks carrier, not a wxWidgets module, so it neither registers itself nor
// fails application startup: OnInit() succeeds and OnExit() does nothing.
bool kwxHtmlTagsModule::OnInit()
{
    return true;
}

void kwxHtmlTagsModule::OnExit() {}

void kwxHtmlTagsModule::FillHandlersTable(wxHtmlWinParser* parser)
{
    if (!m_fill_handlers_table_func)
    {
        return;
    }
    m_fill_handlers_table_func(m_object, parser);
}

// ---------------------------------------------------------------------------
// wxAppTraits
//
// Only kwxAppTraits has the SetLogTarget() slot.  Track the objects created
// here so a wxAppTraits pointer from wxApp::GetTraits() (a platform traits
// object, not one of these helpers) is never cast to the wrong type.
static std::unordered_set<wxAppTraits*> g_kwxAppTraits;
//
// CreateLogTarget()/CreateRenderer() are pure virtual on wxAppTraitsBase, but
// wxConsoleAppTraits implements both (wx/apptrait.h:216, :222), so an unset
// callback forwards there.  This class therefore has to derive from
// wxConsoleAppTraits rather than wxAppTraits.
// ---------------------------------------------------------------------------

kwxAppTraits::kwxAppTraits(void* pObject) : wxConsoleAppTraits()
{
    m_object = pObject;
    m_create_log_target_func = nullptr;
    m_create_renderer_func = nullptr;
    m_log_target = nullptr;
}

wxLog* kwxAppTraits::CreateLogTarget()
{
    if (m_log_target)
    {
        return m_log_target;
    }
    if (!m_create_log_target_func)
    {
        return wxConsoleAppTraits::CreateLogTarget();
    }
    return (wxLog*) m_create_log_target_func(m_object);
}

wxRendererNative* kwxAppTraits::CreateRenderer()
{
    if (!m_create_renderer_func)
    {
        return wxConsoleAppTraits::CreateRenderer();
    }
    return (wxRendererNative*) m_create_renderer_func(m_object);
}

// ---------------------------------------------------------------------------
// wxEvent
// ---------------------------------------------------------------------------

wxIMPLEMENT_ABSTRACT_CLASS(kwxEvent, wxEvent);

kwxEvent::kwxEvent(void* pObject) : wxEvent()
{
    m_object = pObject;
    m_clone_func = nullptr;
}

wxEvent* kwxEvent::Clone() const
{
    if (m_clone_func)
    {
        return (wxEvent*) m_clone_func(m_object);
    }

    // Clone() is pure virtual, so there is no base implementation.  wxEvent is
    // abstract and cannot be copied, so a fresh wxCommandEvent carrying this
    // event's type, id and timestamp is the neutral default: it keeps event
    // posting working for a hook that never set a clone callback.
    wxCommandEvent* const copy = new wxCommandEvent(m_eventType, m_id);
    copy->SetTimestamp(m_timeStamp);
    return copy;
}

// ---------------------------------------------------------------------------
// wxVariantData
// ---------------------------------------------------------------------------

kwxVariantData::kwxVariantData(void* pObject) : wxVariantData()
{
    m_object = pObject;
    m_eq_func = nullptr;
    m_get_type_func = nullptr;
}

bool kwxVariantData::Eq(wxVariantData& data) const
{
    if (!m_eq_func)
    {
        // Eq() is pure virtual, so there is no base implementation.  Comparing
        // by address is the identity comparison a port gets by default.
        return &data == this;
    }
    return m_eq_func(m_object, &data) != 0;
}

wxString kwxVariantData::GetType() const
{
    if (!m_get_type_func)
    {
        // GetType() is also pure virtual; an empty name is the neutral answer.
        return wxString();
    }

    const char* const type_name = (const char*) m_get_type_func(m_object);
    return type_name ? wxString::FromUTF8(type_name) : wxString();
}

// ---------------------------------------------------------------------------
// wxWizardPage
// ---------------------------------------------------------------------------

kwxWizardPage::kwxWizardPage(void* pObject) : wxWizardPage()
{
    m_object = pObject;
    m_get_next_func = nullptr;
    m_get_prev_func = nullptr;
}

wxWizardPage* kwxWizardPage::GetNext() const
{
    // A null return means "last page", which is what wxWizardPage has no base
    // value for (GetNext() is pure virtual, wx/wizard.h:73).
    if (!m_get_next_func)
    {
        return nullptr;
    }
    return (wxWizardPage*) m_get_next_func(m_object);
}

wxWizardPage* kwxWizardPage::GetPrev() const
{
    if (!m_get_prev_func)
    {
        return nullptr;
    }
    return (wxWizardPage*) m_get_prev_func(m_object);
}

// ---------------------------------------------------------------------------
// wxPopupTransientWindow
// ---------------------------------------------------------------------------

kwxPopupTransientWindow::kwxPopupTransientWindow(void* pObject, wxWindow* parent, int style) :
    wxPopupTransientWindow(parent, style)
{
    m_object = pObject;
    m_popup_func = nullptr;
    m_show_func = nullptr;
    m_process_left_down_func = nullptr;
    m_on_dismiss_func = nullptr;
}

void kwxPopupTransientWindow::Popup(wxWindow* focus)
{
    if (!m_popup_func)
    {
        wxPopupTransientWindow::Popup(focus);
        return;
    }
    m_popup_func(m_object, focus);
}

bool kwxPopupTransientWindow::Show(bool show)
{
    if (!m_show_func)
    {
        return wxPopupTransientWindow::Show(show);
    }
    return m_show_func(m_object, show ? 1 : 0) != 0;
}

bool kwxPopupTransientWindow::ProcessLeftDown(wxMouseEvent& event)
{
    if (!m_process_left_down_func)
    {
        return wxPopupTransientWindow::ProcessLeftDown(event);
    }
    return m_process_left_down_func(m_object, &event) != 0;
}

void kwxPopupTransientWindow::OnDismiss()
{
    if (!m_on_dismiss_func)
    {
        wxPopupTransientWindow::OnDismiss();
        return;
    }
    m_on_dismiss_func(m_object);
}

// ---------------------------------------------------------------------------
// wxDocument
//
// LoadObject() and SaveObject() are deliberately not overridden: their
// signatures take std::istream& / std::ostream& (wx/docview.h:101-105), which
// cannot cross a fixed extern "C" boundary.  Both are in the not-representable
// register of .private/port/fix_worklist.md.
// ---------------------------------------------------------------------------

kwxDocument::kwxDocument(void* pObject) : wxDocument()
{
    m_object = pObject;
    m_do_open_document_func = nullptr;
    m_do_save_document_func = nullptr;
    m_get_class_info_func = nullptr;
    m_is_modified_func = nullptr;
    m_modify_func = nullptr;
    m_on_create_func = nullptr;
    m_on_open_document_func = nullptr;
}

bool kwxDocument::DoOpenDocument(const wxString& file)
{
    if (!m_do_open_document_func)
    {
        return wxDocument::DoOpenDocument(file);
    }
    return m_do_open_document_func(m_object, (void*) &file) != 0;
}

bool kwxDocument::DoSaveDocument(const wxString& file)
{
    if (!m_do_save_document_func)
    {
        return wxDocument::DoSaveDocument(file);
    }
    return m_do_save_document_func(m_object, (void*) &file) != 0;
}

wxClassInfo* kwxDocument::GetClassInfo() const
{
    if (!m_get_class_info_func)
    {
        return wxDocument::GetClassInfo();
    }
    return (wxClassInfo*) m_get_class_info_func(m_object);
}

bool kwxDocument::IsModified() const
{
    if (!m_is_modified_func)
    {
        return wxDocument::IsModified();
    }
    return m_is_modified_func(m_object) != 0;
}

void kwxDocument::Modify(bool modified)
{
    if (!m_modify_func)
    {
        wxDocument::Modify(modified);
        return;
    }
    m_modify_func(m_object, modified ? 1 : 0);
}

bool kwxDocument::OnCreate(const wxString& path, long flags)
{
    if (!m_on_create_func)
    {
        return wxDocument::OnCreate(path, flags);
    }
    return m_on_create_func(m_object, (void*) &path, flags) != 0;
}

bool kwxDocument::OnOpenDocument(const wxString& filename)
{
    if (!m_on_open_document_func)
    {
        return wxDocument::OnOpenDocument(filename);
    }
    return m_on_open_document_func(m_object, (void*) &filename) != 0;
}

// ---------------------------------------------------------------------------
// wxView
// ---------------------------------------------------------------------------

kwxView::kwxView(void* pObject) : wxView()
{
    m_object = pObject;
    m_on_draw_func = nullptr;
    m_on_close_func = nullptr;
    m_on_create_func = nullptr;
    m_on_update_func = nullptr;
}

void kwxView::OnDraw(wxDC* dc)
{
    if (!m_on_draw_func)
    {
        return;
    }
    m_on_draw_func(m_object, dc);
}

bool kwxView::OnClose(bool deleteWindow)
{
    if (!m_on_close_func)
    {
        return wxView::OnClose(deleteWindow);
    }
    return m_on_close_func(m_object, deleteWindow ? 1 : 0) != 0;
}

bool kwxView::OnCreate(wxDocument* document, long flags)
{
    if (!m_on_create_func)
    {
        return wxView::OnCreate(document, flags);
    }
    return m_on_create_func(m_object, document, flags) != 0;
}

void kwxView::OnUpdate(wxView* sender, wxObject* hint)
{
    if (!m_on_update_func)
    {
        wxView::OnUpdate(sender, hint);
        return;
    }
    m_on_update_func(m_object, sender, hint);
}

// ---------------------------------------------------------------------------
// wxFileSystemHandler
// ---------------------------------------------------------------------------

kwxFileSystemHandler::kwxFileSystemHandler(void* pObject) : wxFileSystemHandler()
{
    m_object = pObject;
    m_can_open_func = nullptr;
    m_open_file_func = nullptr;
}

bool kwxFileSystemHandler::CanOpen(const wxString& location)
{
    if (!m_can_open_func)
    {
        return false;
    }
    return m_can_open_func(m_object, (void*) &location) != 0;
}

wxFSFile* kwxFileSystemHandler::OpenFile(wxFileSystem& fs, const wxString& location)
{
    if (!m_open_file_func)
    {
        return nullptr;
    }
    return (wxFSFile*) m_open_file_func(m_object, &fs, (void*) &location);
}

// ---------------------------------------------------------------------------
// wxHtmlTagHandler
// ---------------------------------------------------------------------------

kwxHtmlTagHandler::kwxHtmlTagHandler(void* pObject) : wxHtmlTagHandler()
{
    m_object = pObject;
    m_get_supported_tags_func = nullptr;
    m_handle_tag_func = nullptr;
}

wxString kwxHtmlTagHandler::GetSupportedTags()
{
    if (!m_get_supported_tags_func)
    {
        // GetSupportedTags() is pure virtual, so there is no base value to
        // return; an empty list means "this handler claims no tag".
        return wxString();
    }

    const char* const tags = (const char*) m_get_supported_tags_func(m_object);
    return tags ? wxString::FromUTF8(tags) : wxString();
}

bool kwxHtmlTagHandler::HandleTag(const wxHtmlTag& tag)
{
    if (!m_handle_tag_func)
    {
        // HandleTag() is pure virtual as well; not handling the tag is what
        // wxHtmlWinTagHandler does for a tag it does not know.
        return false;
    }
    return m_handle_tag_func(m_object, (void*) &tag) != 0;
}

// ---------------------------------------------------------------------------
// Exports
// ---------------------------------------------------------------------------

extern "C"
{
    // kwxAppConsole -----------------------------------------------------------

    EXPORT void* kwxAppConsole_Create(void* pObject)
    {
        return (void*) new kwxAppConsole(pObject);
    }

    EXPORT void kwxAppConsole_Delete(kwxAppConsole* self)
    {
        delete self;
    }

    EXPORT void kwxAppConsole_SetOnOnCmdLineParsed(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnCmdLineParsed(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnInitCmdLine(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnInitCmdLine(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnExit(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnExit(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnRun(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnRun(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnAssertFailure(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnAssertFailure(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnEventLoopEnter(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnEventLoopEnter(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnExceptionInMainLoop(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnExceptionInMainLoop(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnFatalException(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnFatalException(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnOnUnhandledException(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnOnUnhandledException(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnStoreCurrentException(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnStoreCurrentException(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnRethrowStoredException(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnRethrowStoredException(pFunction);
    }

    EXPORT void kwxAppConsole_SetOnCreateTraits(kwxAppConsole* self, void* pFunction)
    {
        self->SetOnCreateTraits(pFunction);
    }

    // wxAppConsole aliases: the portability matrix resolves an override row to
    // both the kwx<Base>_ and the <Base>_ spelling, so the same setter is
    // exported under the base name.  The receiver is the same helper object.

    EXPORT void wxAppConsole_SetOnOnCmdLineParsed(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnCmdLineParsed(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnInitCmdLine(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnInitCmdLine(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnExit(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnExit(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnRun(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnRun(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnAssertFailure(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnAssertFailure(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnEventLoopEnter(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnEventLoopEnter(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnExceptionInMainLoop(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnExceptionInMainLoop(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnFatalException(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnFatalException(pFunction);
    }

    EXPORT void wxAppConsole_SetOnOnUnhandledException(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnOnUnhandledException(pFunction);
    }

    EXPORT void wxAppConsole_SetOnStoreCurrentException(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnStoreCurrentException(pFunction);
    }

    EXPORT void wxAppConsole_SetOnRethrowStoredException(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnRethrowStoredException(pFunction);
    }

    EXPORT void wxAppConsole_SetOnCreateTraits(wxAppConsole* self, void* pFunction)
    {
        static_cast<kwxAppConsole*>(self)->SetOnCreateTraits(pFunction);
    }

    // kwxApp ------------------------------------------------------------------

#if KWX_HAVE_APP_HOOK

    EXPORT void* kwxApp_Create(void* pObject)
    {
        return (void*) new kwxApp(pObject);
    }

    EXPORT void kwxApp_Delete(kwxApp* self)
    {
        delete self;
    }

    EXPORT void kwxApp_SetOnOnCmdLineParsed(kwxApp* self, void* pFunction)
    {
        self->SetOnOnCmdLineParsed(pFunction);
    }

    EXPORT void kwxApp_SetOnOnInitCmdLine(kwxApp* self, void* pFunction)
    {
        self->SetOnOnInitCmdLine(pFunction);
    }

    EXPORT void kwxApp_SetOnOnExit(kwxApp* self, void* pFunction)
    {
        self->SetOnOnExit(pFunction);
    }

    EXPORT void kwxApp_SetOnFilterEvent(kwxApp* self, void* pFunction)
    {
        self->SetOnFilterEvent(pFunction);
    }

    EXPORT void kwxApp_SetOnGetClassInfo(kwxApp* self, void* pFunction)
    {
        self->SetOnGetClassInfo(pFunction);
    }

    EXPORT void kwxApp_SetOnOnAssertFailure(kwxApp* self, void* pFunction)
    {
        self->SetOnOnAssertFailure(pFunction);
    }

    EXPORT void kwxApp_SetOnCreateTraits(kwxApp* self, void* pFunction)
    {
        self->SetOnCreateTraits(pFunction);
    }

#else  // !KWX_HAVE_APP_HOOK

    // wxApp only exists in a GUI build, where kwxApp is a real class.  The
    // declarations stay visible to kwxgen (it skips preprocessor lines) because
    // a binding that targets a GUI build can call them; in this build the
    // helpers report that no application object could be created.

    EXPORT void* kwxApp_Create(void* pObject)
    {
        wxUnusedVar(pObject);
        return nullptr;
    }

    EXPORT void kwxApp_Delete(kwxApp* self)
    {
        wxUnusedVar(self);
    }

    EXPORT void kwxApp_SetOnOnCmdLineParsed(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnOnInitCmdLine(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnOnExit(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnFilterEvent(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnGetClassInfo(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnOnAssertFailure(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnCreateTraits(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

#endif  // KWX_HAVE_APP_HOOK

    // kwxObject ---------------------------------------------------------------

    EXPORT void* kwxObject_Create(void* pObject)
    {
        return (void*) new kwxObject(pObject);
    }

    EXPORT void kwxObject_Delete(kwxObject* self)
    {
        delete self;
    }

    EXPORT void kwxObject_SetOnGetClassInfo(kwxObject* self, void* pFunction)
    {
        self->SetOnGetClassInfo(pFunction);
    }

    EXPORT void wxObject_SetOnGetClassInfo(wxObject* self, void* pFunction)
    {
        static_cast<kwxObject*>(self)->SetOnGetClassInfo(pFunction);
    }

    // kwxEvtHandler -----------------------------------------------------------

    EXPORT void* kwxEvtHandler_Create(void* pObject)
    {
        return (void*) new kwxEvtHandler(pObject);
    }

    EXPORT void kwxEvtHandler_Delete(kwxEvtHandler* self)
    {
        delete self;
    }

    EXPORT void kwxEvtHandler_SetOnProcessEvent(kwxEvtHandler* self, void* pFunction)
    {
        self->SetOnProcessEvent(pFunction);
    }

    // kwxPanel ----------------------------------------------------------------

    EXPORT void* kwxPanel_Create(void* pObject, wxWindow* parent, int id, int x, int y, int width,
                                 int height, long style)
    {
        return (void*) new kwxPanel(pObject, parent, id, wxPoint(x, y), wxSize(width, height),
                                    style);
    }

    EXPORT void kwxPanel_Delete(kwxPanel* self)
    {
        delete self;
    }

    EXPORT void kwxPanel_SetOnTransferDataFromWindow(kwxPanel* self, void* pFunction)
    {
        self->SetOnTransferDataFromWindow(pFunction);
    }

    EXPORT void kwxPanel_SetOnTransferDataToWindow(kwxPanel* self, void* pFunction)
    {
        self->SetOnTransferDataToWindow(pFunction);
    }

    // The <Base>_SetOn aliases the portability matrix also resolves ovh rows to.
    EXPORT void wxPanel_SetOnTransferDataFromWindow(wxPanel* self, void* pFunction)
    {
        static_cast<kwxPanel*>(self)->SetOnTransferDataFromWindow(pFunction);
    }

    EXPORT void wxPanel_SetOnTransferDataToWindow(wxPanel* self, void* pFunction)
    {
        static_cast<kwxPanel*>(self)->SetOnTransferDataToWindow(pFunction);
    }

    // kwxVarHScrollHelper -----------------------------------------------------

    EXPORT void* kwxVarHScrollHelper_Create(wxWindow* winToScroll, void* pObject)
    {
        return (void*) new kwxVarHScrollHelper(winToScroll, pObject);
    }

    EXPORT void kwxVarHScrollHelper_Delete(kwxVarHScrollHelper* self)
    {
        delete self;
    }

    EXPORT void kwxVarHScrollHelper_SetOnOnGetColumnWidth(kwxVarHScrollHelper* self,
                                                          void* pFunction)
    {
        self->SetOnOnGetColumnWidth(pFunction);
    }

    EXPORT void wxVarHScrollHelper_SetOnOnGetColumnWidth(wxVarHScrollHelper* self, void* pFunction)
    {
        static_cast<kwxVarHScrollHelper*>(self)->SetOnOnGetColumnWidth(pFunction);
    }

    // kwxVarVScrollHelper -----------------------------------------------------

    EXPORT void* kwxVarVScrollHelper_Create(wxWindow* winToScroll, void* pObject)
    {
        return (void*) new kwxVarVScrollHelper(winToScroll, pObject);
    }

    EXPORT void kwxVarVScrollHelper_Delete(kwxVarVScrollHelper* self)
    {
        delete self;
    }

    EXPORT void kwxVarVScrollHelper_SetOnOnGetRowHeight(kwxVarVScrollHelper* self, void* pFunction)
    {
        self->SetOnOnGetRowHeight(pFunction);
    }

    EXPORT void wxVarVScrollHelper_SetOnOnGetRowHeight(wxVarVScrollHelper* self, void* pFunction)
    {
        static_cast<kwxVarVScrollHelper*>(self)->SetOnOnGetRowHeight(pFunction);
    }

    // kwxTimer ----------------------------------------------------------------

    EXPORT void* kwxTimer_Create(void* pObject)
    {
        return (void*) new kwxTimer(pObject);
    }

    EXPORT void kwxTimer_Delete(kwxTimer* self)
    {
        delete self;
    }

    EXPORT void kwxTimer_SetOnNotify(kwxTimer* self, void* pFunction)
    {
        self->SetOnNotify(pFunction);
    }

    EXPORT void wxTimer_SetOnNotify(wxTimer* self, void* pFunction)
    {
        static_cast<kwxTimer*>(self)->SetOnNotify(pFunction);
    }

    // kwxValidator ------------------------------------------------------------

    EXPORT void* kwxValidator_Create(void* pObject)
    {
        return (void*) new kwxValidator(pObject);
    }

    EXPORT void kwxValidator_Delete(kwxValidator* self)
    {
        delete self;
    }

    EXPORT void kwxValidator_SetOnClone(kwxValidator* self, void* pFunction)
    {
        self->SetOnClone(pFunction);
    }

    EXPORT void kwxValidator_SetOnValidate(kwxValidator* self, void* pFunction)
    {
        self->SetOnValidate(pFunction);
    }

    EXPORT void kwxValidator_SetOnTransferFromWindow(kwxValidator* self, void* pFunction)
    {
        self->SetOnTransferFromWindow(pFunction);
    }

    EXPORT void kwxValidator_SetOnTransferToWindow(kwxValidator* self, void* pFunction)
    {
        self->SetOnTransferToWindow(pFunction);
    }

    // kwxPreferencesPage ------------------------------------------------------

    EXPORT void* kwxPreferencesPage_Create(void* pObject)
    {
        return (void*) new kwxPreferencesPage(pObject);
    }

    EXPORT void kwxPreferencesPage_Delete(kwxPreferencesPage* self)
    {
        delete self;
    }

    EXPORT void kwxPreferencesPage_SetOnGetName(kwxPreferencesPage* self, void* pFunction)
    {
        self->SetOnGetName(pFunction);
    }

    EXPORT void kwxPreferencesPage_SetOnCreateWindow(kwxPreferencesPage* self, void* pFunction)
    {
        self->SetOnCreateWindow(pFunction);
    }

    EXPORT void kwxPreferencesPage_SetOnGetIcon(kwxPreferencesPage* self, void* pFunction)
    {
        self->SetOnGetIcon(pFunction);
    }

    // wxEvtHandler alias: the portability matrix also resolves an ovh row to
    // the <Base>_ spelling, which is declared in the existing wxEvtHandler block
    // of include/kwx_classes_sync.h.

    EXPORT void wxEvtHandler_SetOnProcessEvent(wxEvtHandler* self, void* pFunction)
    {
        static_cast<kwxEvtHandler*>(self)->SetOnProcessEvent(pFunction);
    }

    // The <Base>_SetOn aliases for the two bases whose helpers have pure-virtual
    // overrides.  Both receivers are the kwx* helper object.

    EXPORT void wxValidator_SetOnClone(wxValidator* self, void* pFunction)
    {
        static_cast<kwxValidator*>(self)->SetOnClone(pFunction);
    }

    EXPORT void wxValidator_SetOnValidate(wxValidator* self, void* pFunction)
    {
        static_cast<kwxValidator*>(self)->SetOnValidate(pFunction);
    }

    EXPORT void wxValidator_SetOnTransferFromWindow(wxValidator* self, void* pFunction)
    {
        static_cast<kwxValidator*>(self)->SetOnTransferFromWindow(pFunction);
    }

    EXPORT void wxValidator_SetOnTransferToWindow(wxValidator* self, void* pFunction)
    {
        static_cast<kwxValidator*>(self)->SetOnTransferToWindow(pFunction);
    }

    EXPORT void wxPreferencesPage_SetOnGetName(wxPreferencesPage* self, void* pFunction)
    {
        static_cast<kwxPreferencesPage*>(self)->SetOnGetName(pFunction);
    }

    EXPORT void wxPreferencesPage_SetOnCreateWindow(wxPreferencesPage* self, void* pFunction)
    {
        static_cast<kwxPreferencesPage*>(self)->SetOnCreateWindow(pFunction);
    }

    EXPORT void wxPreferencesPage_SetOnGetIcon(wxPreferencesPage* self, void* pFunction)
    {
        static_cast<kwxPreferencesPage*>(self)->SetOnGetIcon(pFunction);
    }

    // kwxHtmlListBox --------------------------------------------------------

    EXPORT void* kwxHtmlListBox_Create(void* pObject, wxWindow* parent, int id, int x, int y,
                                       int width, int height, long style)
    {
        return (void*) new kwxHtmlListBox(pObject, parent, id, wxPoint(x, y), wxSize(width, height),
                                          style);
    }

    EXPORT void kwxHtmlListBox_Delete(kwxHtmlListBox* self)
    {
        delete self;
    }

    EXPORT void kwxHtmlListBox_SetOnOnGetItem(kwxHtmlListBox* self, void* pFunction)
    {
        self->SetOnOnGetItem(pFunction);
    }

    EXPORT void kwxHtmlListBox_SetOnGetSelectedTextColour(kwxHtmlListBox* self, void* pFunction)
    {
        self->SetOnGetSelectedTextColour(pFunction);
    }

    EXPORT void wxHtmlListBox_SetOnOnGetItem(wxHtmlListBox* self, void* pFunction)
    {
        static_cast<kwxHtmlListBox*>(self)->SetOnOnGetItem(pFunction);
    }

    EXPORT void wxHtmlListBox_SetOnGetSelectedTextColour(wxHtmlListBox* self, void* pFunction)
    {
        static_cast<kwxHtmlListBox*>(self)->SetOnGetSelectedTextColour(pFunction);
    }

    // kwxVListBox ------------------------------------------------------------

    EXPORT void* kwxVListBox_Create(void* pObject, wxWindow* parent, int id, int x, int y,
                                    int width, int height, long style)
    {
        return (void*) new kwxVListBox(pObject, parent, id, wxPoint(x, y), wxSize(width, height),
                                       style);
    }

    EXPORT void kwxVListBox_Delete(kwxVListBox* self)
    {
        delete self;
    }

    EXPORT void kwxVListBox_SetOnOnDrawItem(kwxVListBox* self, void* pFunction)
    {
        self->SetOnOnDrawItem(pFunction);
    }

    EXPORT void kwxVListBox_SetOnOnDrawSeparator(kwxVListBox* self, void* pFunction)
    {
        self->SetOnOnDrawSeparator(pFunction);
    }

    EXPORT void kwxVListBox_SetOnOnMeasureItem(kwxVListBox* self, void* pFunction)
    {
        self->SetOnOnMeasureItem(pFunction);
    }

    EXPORT void wxVListBox_SetOnOnDrawItem(wxVListBox* self, void* pFunction)
    {
        static_cast<kwxVListBox*>(self)->SetOnOnDrawItem(pFunction);
    }

    EXPORT void wxVListBox_SetOnOnDrawSeparator(wxVListBox* self, void* pFunction)
    {
        static_cast<kwxVListBox*>(self)->SetOnOnDrawSeparator(pFunction);
    }

    EXPORT void wxVListBox_SetOnOnMeasureItem(wxVListBox* self, void* pFunction)
    {
        static_cast<kwxVListBox*>(self)->SetOnOnMeasureItem(pFunction);
    }

    // kwxRendererNative ------------------------------------------------------

    EXPORT void* kwxRendererNative_Create(void* pObject)
    {
        return (void*) new kwxRendererNative(pObject);
    }

    EXPORT void kwxRendererNative_Delete(kwxRendererNative* self)
    {
        delete self;
    }

    EXPORT void kwxRendererNative_SetOnDrawHeaderButton(kwxRendererNative* self, void* pFunction)
    {
        self->SetOnDrawHeaderButton(pFunction);
    }

    EXPORT void kwxRendererNative_SetOnGetVersion(kwxRendererNative* self, void* pFunction)
    {
        self->SetOnGetVersion(pFunction);
    }

    EXPORT void wxRendererNative_SetOnDrawHeaderButton(wxRendererNative* self, void* pFunction)
    {
        static_cast<kwxRendererNative*>(self)->SetOnDrawHeaderButton(pFunction);
    }

    EXPORT void wxRendererNative_SetOnGetVersion(wxRendererNative* self, void* pFunction)
    {
        static_cast<kwxRendererNative*>(self)->SetOnGetVersion(pFunction);
    }

    // kwxModalDialogHook -----------------------------------------------------

    EXPORT void* kwxModalDialogHook_Create(void* pObject)
    {
        return (void*) new kwxModalDialogHook(pObject);
    }

    EXPORT void kwxModalDialogHook_Delete(kwxModalDialogHook* self)
    {
        delete self;
    }

    EXPORT void kwxModalDialogHook_SetOnEnter(kwxModalDialogHook* self, void* pFunction)
    {
        self->SetOnEnter(pFunction);
    }

    EXPORT void kwxModalDialogHook_SetOnExit(kwxModalDialogHook* self, void* pFunction)
    {
        self->SetOnExit(pFunction);
    }

    EXPORT void kwxModalDialogHook_CaptureEnterDialog(kwxModalDialogHook* self, int capture)
    {
        self->SetCaptureEnterDialog(capture != 0);
    }

    EXPORT void wxModalDialogHook_SetOnEnter(wxModalDialogHook* self, void* pFunction)
    {
        static_cast<kwxModalDialogHook*>(self)->SetOnEnter(pFunction);
    }

    EXPORT void wxModalDialogHook_SetOnExit(wxModalDialogHook* self, void* pFunction)
    {
        static_cast<kwxModalDialogHook*>(self)->SetOnExit(pFunction);
    }

    EXPORT void wxModalDialogHook_CaptureEnterDialog(wxModalDialogHook* self, int capture)
    {
        static_cast<kwxModalDialogHook*>(self)->SetCaptureEnterDialog(capture != 0);
    }

    EXPORT void wxModalDialogHook_Register(wxModalDialogHook* self)
    {
        self->Register();
    }

    EXPORT void wxModalDialogHook_Unregister(wxModalDialogHook* self)
    {
        self->Unregister();
    }

    EXPORT void wxModalDialogHook_Delete(wxModalDialogHook* self)
    {
        delete self;
    }

    // kwxAddRemoveAdaptor ----------------------------------------------------

    EXPORT kwxAddRemoveAdaptor* kwxAddRemoveAdaptor_Create(void* pObject)
    {
        return new kwxAddRemoveAdaptor(pObject);
    }

    EXPORT void kwxAddRemoveAdaptor_SetOnGetItemsCtrl(kwxAddRemoveAdaptor* self, void* pFunction)
    {
        self->SetOnGetItemsCtrl(pFunction);
    }

    EXPORT void kwxAddRemoveAdaptor_SetOnCanAdd(kwxAddRemoveAdaptor* self, void* pFunction)
    {
        self->SetOnCanAdd(pFunction);
    }

    EXPORT void kwxAddRemoveAdaptor_SetOnCanRemove(kwxAddRemoveAdaptor* self, void* pFunction)
    {
        self->SetOnCanRemove(pFunction);
    }

    EXPORT void kwxAddRemoveAdaptor_SetOnAdd(kwxAddRemoveAdaptor* self, void* pFunction)
    {
        self->SetOnAdd(pFunction);
    }

    EXPORT void kwxAddRemoveAdaptor_SetOnRemove(kwxAddRemoveAdaptor* self, void* pFunction)
    {
        self->SetOnRemove(pFunction);
    }

    EXPORT void kwxAddRemoveAdaptor_SetItemsCtrl(kwxAddRemoveAdaptor* self, wxWindow* ctrl)
    {
        self->SetItemsCtrl(ctrl);
    }

    EXPORT void kwxAddRemoveAdaptor_SetCanAdd(kwxAddRemoveAdaptor* self, int value)
    {
        self->SetCanAdd(value != 0);
    }

    EXPORT void kwxAddRemoveAdaptor_SetCanRemove(kwxAddRemoveAdaptor* self, int value)
    {
        self->SetCanRemove(value != 0);
    }

    EXPORT void kwxAddRemoveAdaptor_Delete(kwxAddRemoveAdaptor* self)
    {
        delete self;
    }

    // kwxTextCompleterSimple -------------------------------------------------

    EXPORT void* kwxTextCompleterSimple_Create(void* pObject)
    {
        return (void*) new kwxTextCompleterSimple(pObject);
    }

    EXPORT void kwxTextCompleterSimple_Delete(kwxTextCompleterSimple* self)
    {
        delete self;
    }

    EXPORT void kwxTextCompleterSimple_SetOnGetCompletions(kwxTextCompleterSimple* self,
                                                           void* pFunction)
    {
        self->SetOnGetCompletions(pFunction);
    }

    EXPORT void wxTextCompleterSimple_SetOnGetCompletions(wxTextCompleterSimple* self,
                                                          void* pFunction)
    {
        static_cast<kwxTextCompleterSimple*>(self)->SetOnGetCompletions(pFunction);
    }

    // kwxHtmlTagsModule ------------------------------------------------------

    EXPORT void* kwxHtmlTagsModule_Create(void* pObject)
    {
        return (void*) new kwxHtmlTagsModule(pObject);
    }

    EXPORT void kwxHtmlTagsModule_Delete(kwxHtmlTagsModule* self)
    {
        delete self;
    }

    EXPORT void kwxHtmlTagsModule_SetOnFillHandlersTable(kwxHtmlTagsModule* self, void* pFunction)
    {
        self->SetOnFillHandlersTable(pFunction);
    }

    EXPORT void wxHtmlTagsModule_SetOnFillHandlersTable(wxHtmlTagsModule* self, void* pFunction)
    {
        static_cast<kwxHtmlTagsModule*>(self)->SetOnFillHandlersTable(pFunction);
    }

    // kwxDocument ------------------------------------------------------------

    EXPORT void* kwxDocument_Create(void* pObject)
    {
        return (void*) new kwxDocument(pObject);
    }

    EXPORT void kwxDocument_Delete(kwxDocument* self)
    {
        delete self;
    }

    EXPORT void kwxDocument_SetOnDoOpenDocument(kwxDocument* self, void* pFunction)
    {
        self->SetOnDoOpenDocument(pFunction);
    }

    EXPORT void kwxDocument_SetOnDoSaveDocument(kwxDocument* self, void* pFunction)
    {
        self->SetOnDoSaveDocument(pFunction);
    }

    EXPORT void kwxDocument_SetOnGetClassInfo(kwxDocument* self, void* pFunction)
    {
        self->SetOnGetClassInfo(pFunction);
    }

    EXPORT void kwxDocument_SetOnIsModified(kwxDocument* self, void* pFunction)
    {
        self->SetOnIsModified(pFunction);
    }

    EXPORT void kwxDocument_SetOnModify(kwxDocument* self, void* pFunction)
    {
        self->SetOnModify(pFunction);
    }

    EXPORT void kwxDocument_SetOnOnCreate(kwxDocument* self, void* pFunction)
    {
        self->SetOnOnCreate(pFunction);
    }

    EXPORT void kwxDocument_SetOnOnOpenDocument(kwxDocument* self, void* pFunction)
    {
        self->SetOnOnOpenDocument(pFunction);
    }

    // wxDocument aliases: the portability matrix also resolves an ovh row to the
    // <Base>_ spelling.  The receiver is the same helper object.

    EXPORT void wxDocument_SetOnDoOpenDocument(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnDoOpenDocument(pFunction);
    }

    EXPORT void wxDocument_SetOnDoSaveDocument(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnDoSaveDocument(pFunction);
    }

    EXPORT void wxDocument_SetOnGetClassInfo(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnGetClassInfo(pFunction);
    }

    EXPORT void wxDocument_SetOnIsModified(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnIsModified(pFunction);
    }

    EXPORT void wxDocument_SetOnModify(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnModify(pFunction);
    }

    EXPORT void wxDocument_SetOnOnCreate(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnOnCreate(pFunction);
    }

    EXPORT void wxDocument_SetOnOnOpenDocument(wxDocument* self, void* pFunction)
    {
        static_cast<kwxDocument*>(self)->SetOnOnOpenDocument(pFunction);
    }

    // kwxView ----------------------------------------------------------------

    EXPORT void* kwxView_Create(void* pObject)
    {
        return (void*) new kwxView(pObject);
    }

    EXPORT void kwxView_Delete(kwxView* self)
    {
        delete self;
    }

    EXPORT void kwxView_SetOnOnDraw(kwxView* self, void* pFunction)
    {
        self->SetOnOnDraw(pFunction);
    }

    EXPORT void kwxView_SetOnOnClose(kwxView* self, void* pFunction)
    {
        self->SetOnOnClose(pFunction);
    }

    EXPORT void kwxView_SetOnOnCreate(kwxView* self, void* pFunction)
    {
        self->SetOnOnCreate(pFunction);
    }

    EXPORT void kwxView_SetOnOnUpdate(kwxView* self, void* pFunction)
    {
        self->SetOnOnUpdate(pFunction);
    }

    EXPORT void wxView_SetOnOnDraw(wxView* self, void* pFunction)
    {
        static_cast<kwxView*>(self)->SetOnOnDraw(pFunction);
    }

    EXPORT void wxView_SetOnOnClose(wxView* self, void* pFunction)
    {
        static_cast<kwxView*>(self)->SetOnOnClose(pFunction);
    }

    EXPORT void wxView_SetOnOnCreate(wxView* self, void* pFunction)
    {
        static_cast<kwxView*>(self)->SetOnOnCreate(pFunction);
    }

    EXPORT void wxView_SetOnOnUpdate(wxView* self, void* pFunction)
    {
        static_cast<kwxView*>(self)->SetOnOnUpdate(pFunction);
    }

    // kwxFileSystemHandler ---------------------------------------------------

    EXPORT void* kwxFileSystemHandler_Create(void* pObject)
    {
        return (void*) new kwxFileSystemHandler(pObject);
    }

    EXPORT void kwxFileSystemHandler_Delete(kwxFileSystemHandler* self)
    {
        delete self;
    }

    EXPORT void kwxFileSystemHandler_SetOnCanOpen(kwxFileSystemHandler* self, void* pFunction)
    {
        self->SetOnCanOpen(pFunction);
    }

    EXPORT void kwxFileSystemHandler_SetOnOpenFile(kwxFileSystemHandler* self, void* pFunction)
    {
        self->SetOnOpenFile(pFunction);
    }

    EXPORT void wxFileSystemHandler_SetOnCanOpen(wxFileSystemHandler* self, void* pFunction)
    {
        static_cast<kwxFileSystemHandler*>(self)->SetOnCanOpen(pFunction);
    }

    EXPORT void wxFileSystemHandler_SetOnOpenFile(wxFileSystemHandler* self, void* pFunction)
    {
        static_cast<kwxFileSystemHandler*>(self)->SetOnOpenFile(pFunction);
    }

    // kwxHtmlTagHandler ------------------------------------------------------

    EXPORT void* kwxHtmlTagHandler_Create(void* pObject)
    {
        return (void*) new kwxHtmlTagHandler(pObject);
    }

    EXPORT void kwxHtmlTagHandler_Delete(kwxHtmlTagHandler* self)
    {
        delete self;
    }

    EXPORT void kwxHtmlTagHandler_SetOnGetSupportedTags(kwxHtmlTagHandler* self, void* pFunction)
    {
        self->SetOnGetSupportedTags(pFunction);
    }

    EXPORT void kwxHtmlTagHandler_SetOnHandleTag(kwxHtmlTagHandler* self, void* pFunction)
    {
        self->SetOnHandleTag(pFunction);
    }

    EXPORT void wxHtmlTagHandler_SetOnGetSupportedTags(wxHtmlTagHandler* self, void* pFunction)
    {
        static_cast<kwxHtmlTagHandler*>(self)->SetOnGetSupportedTags(pFunction);
    }

    EXPORT void wxHtmlTagHandler_SetOnHandleTag(wxHtmlTagHandler* self, void* pFunction)
    {
        static_cast<kwxHtmlTagHandler*>(self)->SetOnHandleTag(pFunction);
    }

    // kwxAppTraits -----------------------------------------------------------

    EXPORT void* kwxAppTraits_Create(void* pObject)
    {
        kwxAppTraits* const traits = new kwxAppTraits(pObject);
        g_kwxAppTraits.insert(static_cast<wxAppTraits*>(traits));
        return (void*) traits;
    }

    EXPORT void kwxAppTraits_Delete(kwxAppTraits* self)
    {
        g_kwxAppTraits.erase(static_cast<wxAppTraits*>(self));
        delete self;
    }

    EXPORT void kwxAppTraits_SetOnCreateLogTarget(kwxAppTraits* self, void* pFunction)
    {
        self->SetOnCreateLogTarget(pFunction);
    }

    EXPORT void kwxAppTraits_SetOnCreateRenderer(kwxAppTraits* self, void* pFunction)
    {
        self->SetOnCreateRenderer(pFunction);
    }

    // The base-name setters are safe only for a kwxAppTraits helper.  A
    // platform traits object (wxApp::GetTraits()) has no callback slots, so
    // ignore the call instead of casting it to the wrong type.
    EXPORT void wxAppTraits_SetOnCreateLogTarget(wxAppTraits* self, void* pFunction)
    {
        if (g_kwxAppTraits.contains(self))
        {
            static_cast<kwxAppTraits*>(self)->SetOnCreateLogTarget(pFunction);
        }
    }

    EXPORT void wxAppTraits_SetOnCreateRenderer(wxAppTraits* self, void* pFunction)
    {
        if (g_kwxAppTraits.contains(self))
        {
            static_cast<kwxAppTraits*>(self)->SetOnCreateRenderer(pFunction);
        }
    }

    EXPORT wxLog* kwxAppTraits_SetLogTarget(kwxAppTraits* self, wxLog* target)
    {
        return self->SetLogTarget(target);
    }

    // wxAppTraits itself has no log-target setter: CreateLogTarget() is the
    // virtual factory.  For a kwxAppTraits helper the target is stored there.
    // Any other traits object (notably the platform traits that
    // wxApp::GetTraits() returns) is handled by installing the same target as
    // the process-wide active log target, which is the observable effect a
    // caller wants and avoids an invalid downcast.
    EXPORT wxLog* wxAppTraits_SetLogTarget(wxAppTraits* self, wxLog* target)
    {
        if (g_kwxAppTraits.contains(self))
        {
            return static_cast<kwxAppTraits*>(self)->SetLogTarget(target);
        }
        return wxLog::SetActiveTarget(target);
    }

    // kwxEvent ---------------------------------------------------------------

    EXPORT void* kwxEvent_Create(void* pObject)
    {
        return (void*) new kwxEvent(pObject);
    }

    EXPORT void kwxEvent_Delete(kwxEvent* self)
    {
        delete self;
    }

    EXPORT void kwxEvent_SetOnClone(kwxEvent* self, void* pFunction)
    {
        self->SetOnClone(pFunction);
    }

    EXPORT void wxEvent_SetOnClone(wxEvent* self, void* pFunction)
    {
        static_cast<kwxEvent*>(self)->SetOnClone(pFunction);
    }

    // kwxVariantData ---------------------------------------------------------

    EXPORT void* kwxVariantData_Create(void* pObject)
    {
        return (void*) new kwxVariantData(pObject);
    }

    EXPORT void kwxVariantData_Delete(kwxVariantData* self)
    {
        delete self;
    }

    EXPORT void kwxVariantData_SetOnEq(kwxVariantData* self, void* pFunction)
    {
        self->SetOnEq(pFunction);
    }

    EXPORT void kwxVariantData_SetOnGetType(kwxVariantData* self, void* pFunction)
    {
        self->SetOnGetType(pFunction);
    }

    // The <Base>_SetOn aliases the portability matrix also resolves ovh rows to.
    EXPORT void wxVariantData_SetOnEq(wxVariantData* self, void* pFunction)
    {
        static_cast<kwxVariantData*>(self)->SetOnEq(pFunction);
    }

    EXPORT void wxVariantData_SetOnGetType(wxVariantData* self, void* pFunction)
    {
        static_cast<kwxVariantData*>(self)->SetOnGetType(pFunction);
    }

    // kwxWizardPage ----------------------------------------------------------

    EXPORT void* kwxWizardPage_Create(void* pObject)
    {
        return (void*) new kwxWizardPage(pObject);
    }

    EXPORT void kwxWizardPage_Delete(kwxWizardPage* self)
    {
        delete self;
    }

    EXPORT void kwxWizardPage_SetOnGetNext(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnGetNext(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnGetPrev(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnGetPrev(pFunction);
    }

    EXPORT void wxWizardPage_SetOnGetNext(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnGetNext(pFunction);
    }

    EXPORT void wxWizardPage_SetOnGetPrev(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnGetPrev(pFunction);
    }

    // kwxPopupTransientWindow ------------------------------------------------

    EXPORT void* kwxPopupTransientWindow_Create(void* pObject, wxWindow* parent, int style)
    {
        return (void*) new kwxPopupTransientWindow(pObject, parent, style);
    }

    EXPORT void kwxPopupTransientWindow_Delete(kwxPopupTransientWindow* self)
    {
        delete self;
    }

    EXPORT void kwxPopupTransientWindow_SetOnPopup(kwxPopupTransientWindow* self, void* pFunction)
    {
        self->SetOnPopup(pFunction);
    }

    EXPORT void kwxPopupTransientWindow_SetOnShow(kwxPopupTransientWindow* self, void* pFunction)
    {
        self->SetOnShow(pFunction);
    }

    EXPORT void kwxPopupTransientWindow_SetOnProcessLeftDown(kwxPopupTransientWindow* self,
                                                             void* pFunction)
    {
        self->SetOnProcessLeftDown(pFunction);
    }

    EXPORT void kwxPopupTransientWindow_SetOnOnDismiss(kwxPopupTransientWindow* self,
                                                       void* pFunction)
    {
        self->SetOnOnDismiss(pFunction);
    }

    // The <Base>_SetOn spellings the portability matrix also resolves.  The
    // receiver is the same helper object.

    EXPORT void wxPopupTransientWindow_SetOnPopup(wxPopupTransientWindow* self, void* pFunction)
    {
        static_cast<kwxPopupTransientWindow*>(self)->SetOnPopup(pFunction);
    }

    EXPORT void wxPopupTransientWindow_SetOnShow(wxPopupTransientWindow* self, void* pFunction)
    {
        static_cast<kwxPopupTransientWindow*>(self)->SetOnShow(pFunction);
    }

    EXPORT void wxPopupTransientWindow_SetOnProcessLeftDown(wxPopupTransientWindow* self,
                                                            void* pFunction)
    {
        static_cast<kwxPopupTransientWindow*>(self)->SetOnProcessLeftDown(pFunction);
    }

    EXPORT void wxPopupTransientWindow_SetOnOnDismiss(wxPopupTransientWindow* self, void* pFunction)
    {
        static_cast<kwxPopupTransientWindow*>(self)->SetOnOnDismiss(pFunction);
    }
}
