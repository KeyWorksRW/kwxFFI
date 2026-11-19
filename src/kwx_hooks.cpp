// Callback overrides for the wxWidgets virtuals a foreign language cannot
// implement itself.  The classes live in include/kwx_helper_hooks.h; this file
// defines their constructors, their virtual overrides, and the exported
// kwx<Base>_Create/_Delete/SetOn* functions.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// The wxDataView renderer classes (wxDataViewRenderer, wxDataViewCustomRenderer) live in
// wx/dvrenderers.h; kwx_wrapper.h pulls in wx/dataview.h, which does not include it in
// every configuration.
#include <wx/dvrenderers.h>

#include <cstdint>
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
    m_on_fatal_exception_func = nullptr;
    m_on_unhandled_exception_func = nullptr;
    m_store_current_exception_func = nullptr;
    m_on_exception_in_main_loop_func = nullptr;
    m_rethrow_stored_exception_func = nullptr;
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

// wxApp owns the same five exception hooks as wxAppConsole.  They exist on the
// wxApp helper so a port never has to reach them through the wxAppConsole
// base-name aliases, which cannot be applied to a wxApp object.
void kwxApp::OnFatalException()
{
    if (!m_on_fatal_exception_func)
    {
        wxApp::OnFatalException();
        return;
    }
    m_on_fatal_exception_func(m_object);
}

void kwxApp::OnUnhandledException()
{
    if (!m_on_unhandled_exception_func)
    {
        wxApp::OnUnhandledException();
        return;
    }
    m_on_unhandled_exception_func(m_object);
}

bool kwxApp::OnExceptionInMainLoop()
{
    if (!m_on_exception_in_main_loop_func)
    {
        return wxApp::OnExceptionInMainLoop();
    }
    return m_on_exception_in_main_loop_func(m_object) != 0;
}

bool kwxApp::StoreCurrentException()
{
    if (!m_store_current_exception_func)
    {
        return wxApp::StoreCurrentException();
    }
    return m_store_current_exception_func(m_object) != 0;
}

void kwxApp::RethrowStoredException()
{
    if (!m_rethrow_stored_exception_func)
    {
        wxApp::RethrowStoredException();
        return;
    }
    m_rethrow_stored_exception_func(m_object);
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
// wxDebugReportUpload
//
// The wxWidgets debugrpt sample derives from wxDebugReportUpload only to log the
// reply curl got back from the server.  The helper publishes that reply through a
// callback and lets the callback decide the return value of OnServerReply(): the
// hook answers with SetOnServerReplyResult() while it runs.
// ---------------------------------------------------------------------------

kwxDebugReportUpload::kwxDebugReportUpload(void* pObject, const wxString& url,
                                           const wxString& input, const wxString& action) :
    wxDebugReportUpload(url, input, action)
{
    m_object = pObject;
    m_on_server_reply_func = nullptr;
    m_server_reply_result = true;
}

bool kwxDebugReportUpload::OnServerReply(const wxArrayString& reply)
{
    if (!m_on_server_reply_func)
    {
        return m_server_reply_result;
    }

    // The answer is per reply: reset it before every call so a callback that
    // publishes nothing keeps the report.
    m_server_reply_result = true;
    m_on_server_reply_func(m_object, const_cast<wxArrayString*>(&reply));
    return m_server_reply_result;
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
// kwxDialog
// ---------------------------------------------------------------------------

kwxDialog::kwxDialog(void* pObject, wxWindow* parent, wxWindowID id, const wxString& title,
                     const wxPoint& pos, const wxSize& size, long style) :
    wxDialog(parent, id, title, pos, size, style)
{
    m_object = pObject;
    m_transfer_data_from_window_func = nullptr;
    m_transfer_data_to_window_func = nullptr;
}

bool kwxDialog::TransferDataFromWindow()
{
    if (!m_transfer_data_from_window_func)
    {
        return wxDialog::TransferDataFromWindow();
    }
    return m_transfer_data_from_window_func(m_object) != 0;
}

bool kwxDialog::TransferDataToWindow()
{
    if (!m_transfer_data_to_window_func)
    {
        return wxDialog::TransferDataToWindow();
    }
    return m_transfer_data_to_window_func(m_object) != 0;
}

// ---------------------------------------------------------------------------
// kwxFrame
//
// Mirrors MyFrame::ProcessEvent in wxSamples/src/richtext/richtext.cpp:1325-1363:
// the frame forwards a command event to the focused window's handler and reports
// it handled when that handler consumed it, otherwise it defers to
// wxFrame::ProcessEvent.  A callback that publishes no result therefore means
// "not handled" -- never "handled" -- so an update-UI event still reaches the
// frame's own handlers.
//
// TryBefore is hooked separately for the sample's "forward frame menu/update-UI
// events to the child canvas first" pattern, and the base implementation is always
// chained.
// ---------------------------------------------------------------------------

// Uniform single-thunk hook ABI, identical to the typedef src/kwx_richtext_hooks.cpp
// declares for its hooks: the first argument is the per-hook token, the next two are
// the hook arguments, and unused positions are null.
typedef void (*kwxHookFunc)(void* data, void* arg1, void* arg2);

class kwxFrame : public wxFrame
{
private:
    void* m_object;
    kwxAppEventFunc m_process_event_func;

    kwxHookFunc m_process_event_hook;
    void* m_process_event_hook_data;

    bool m_result_bool;
    bool m_has_result;

    kwxAppEventFunc m_try_before_func;
    kwxHookFunc m_try_before_hook;
    void* m_try_before_hook_data;

    bool m_try_before_result;
    bool m_has_try_before_result;

public:
    kwxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
             const wxSize& size, long style);

    void SetCallbackObject(void* object) { m_object = object; }
    void* GetCallbackObject() const { return m_object; }

    void SetOnProcessEvent(void* pFunction) { m_process_event_func = (kwxAppEventFunc) pFunction; }
    void SetOnProcessEventWithData(void* pFunction, void* data)
    {
        m_process_event_hook = (kwxHookFunc) pFunction;
        m_process_event_hook_data = data;
    }

    void SetProcessEventResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }

    void SetOnTryBefore(void* pFunction) { m_try_before_func = (kwxAppEventFunc) pFunction; }
    void SetOnTryBeforeWithData(void* pFunction, void* data)
    {
        m_try_before_hook = (kwxHookFunc) pFunction;
        m_try_before_hook_data = data;
    }

    void SetTryBeforeResult(bool result)
    {
        m_try_before_result = result;
        m_has_try_before_result = true;
    }

    bool ProcessEvent(wxEvent& event) override;

protected:
    bool TryBefore(wxEvent& event) override;
};

kwxFrame::kwxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos,
                   const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    m_object = nullptr;
    m_process_event_func = nullptr;
    m_process_event_hook = nullptr;
    m_process_event_hook_data = nullptr;
    m_result_bool = false;
    m_has_result = false;
    m_try_before_func = nullptr;
    m_try_before_hook = nullptr;
    m_try_before_hook_data = nullptr;
    m_try_before_result = false;
    m_has_try_before_result = false;
}

bool kwxFrame::ProcessEvent(wxEvent& event)
{
    if (m_process_event_hook)
    {
        // The answer is per event: clear the previous one before every call so a
        // callback that publishes nothing always falls through.
        m_result_bool = false;
        m_has_result = false;
        m_process_event_hook(m_process_event_hook_data, &event, nullptr);
        if (m_has_result && m_result_bool)
        {
            return true;
        }
        return wxFrame::ProcessEvent(event);
    }
    if (m_process_event_func)
    {
        return m_process_event_func(m_object, &event) != 0;
    }
    return wxFrame::ProcessEvent(event);
}

bool kwxFrame::TryBefore(wxEvent& event)
{
    if (m_try_before_hook)
    {
        // Per event: clear the previous answer so a callback that publishes nothing
        // always falls through to wxFrame::TryBefore().
        m_try_before_result = false;
        m_has_try_before_result = false;
        m_try_before_hook(m_try_before_hook_data, &event, nullptr);
        if (m_has_try_before_result && m_try_before_result)
        {
            return true;
        }
    }
    else if (m_try_before_func)
    {
        if (m_try_before_func(m_object, &event) != 0)
        {
            return true;
        }
    }

    // Qualified call: a plain virtual call would re-enter this override.
    return wxFrame::TryBefore(event);
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
// the class to be instantiable at all.  The callbacks are void-returning (the
// FFI ABI has no other shape), so each override clears its scratch result,
// invokes the callback, and then returns whatever the callback published.  An
// unset callback — or one that publishes nothing — yields an empty name, no
// window or no icon rather than an assertion.
// ---------------------------------------------------------------------------

kwxPreferencesPage::kwxPreferencesPage(void* pObject) : wxPreferencesPage()
{
    m_object = pObject;
    m_get_name_func = nullptr;
    m_create_window_func = nullptr;
    m_get_icon_func = nullptr;
    m_result_window = nullptr;
    m_result_icon = nullptr;
}

wxString kwxPreferencesPage::GetName() const
{
    if (!m_get_name_func)
    {
        return wxString();
    }
    m_result_name.clear();
    m_get_name_func(m_object);
    return m_result_name;
}

wxWindow* kwxPreferencesPage::CreateWindow(wxWindow* parent)
{
    if (!m_create_window_func)
    {
        return nullptr;
    }
    m_result_window = nullptr;
    m_create_window_func(m_object, parent);
    return m_result_window;
}

// GetIcon() is not pure virtual, so an unset callback keeps the wxWidgets
// default icon instead of overriding it with an empty bundle.
wxBitmapBundle kwxPreferencesPage::GetIcon() const
{
    if (!m_get_icon_func)
    {
        return wxPreferencesPage::GetIcon();
    }

    m_result_icon = nullptr;
    m_get_icon_func(m_object);
    if (!m_result_icon)
    {
        return wxBitmapBundle();
    }

    const wxBitmapBundle page_icon = *m_result_icon;
    delete m_result_icon;
    m_result_icon = nullptr;
    return page_icon;
}

// ---------------------------------------------------------------------------
// wxStockPreferencesPage
// ---------------------------------------------------------------------------

wxWindow* kwxStockPreferencesPage::CreateWindow(wxWindow* parent)
{
    if (!m_create_window_func)
    {
        return nullptr;
    }
    m_result_window = nullptr;
    m_create_window_func(m_object, parent);
    return m_result_window;
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
// kwxNativeWindow
// ---------------------------------------------------------------------------

// Create() is called here rather than in the constructor so a failure leaves no
// half-built object behind; each binding's Create checks the window's validity.
kwxNativeWindow::kwxNativeWindow(void* pObject, wxWindow* parent, wxWindowID id, void* handle) :
    wxNativeWindow(), m_object(pObject)
{
    Create(parent, id, (wxNativeWindowHandle) handle);
}

#ifdef __WXMSW__
namespace
{
    // MSWOnNotify() takes WXLPARAM, which exists only on MSW, so the override
    // cannot be declared in the public header.  kwxNativeWindow_Create below
    // instantiates this subclass; the bindings only ever see kwxNativeWindow*.
    class kwxNativeWindowMSW : public kwxNativeWindow
    {
    public:
        kwxNativeWindowMSW(void* pObject, wxWindow* parent, wxWindowID id, void* handle) :
            kwxNativeWindow(pObject, parent, id, handle)
        {
        }

    protected:
        bool MSWOnNotify(int idCtrl, WXLPARAM lParam, WXLPARAM* result) override
        {
            if (InvokeMSWNotify(idCtrl, (void*) lParam, result))
            {
                return true;
            }
            return wxNativeWindow::MSWOnNotify(idCtrl, lParam, result);
        }
    };
}  // namespace
#endif

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
    m_transfer_data_from_window_func = nullptr;
    m_transfer_data_to_window_func = nullptr;
    m_get_next_out_func = nullptr;
    m_get_prev_out_func = nullptr;
    m_transfer_data_from_window_out_func = nullptr;
    m_transfer_data_to_window_out_func = nullptr;
}

wxWizardPage* kwxWizardPage::GetNext() const
{
    if (m_get_next_out_func)
    {
        void* page = nullptr;
        m_get_next_out_func(m_object, &page);
        return static_cast<wxWizardPage*>(page);
    }

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
    if (m_get_prev_out_func)
    {
        void* page = nullptr;
        m_get_prev_out_func(m_object, &page);
        return static_cast<wxWizardPage*>(page);
    }

    if (!m_get_prev_func)
    {
        return nullptr;
    }
    return (wxWizardPage*) m_get_prev_func(m_object);
}

bool kwxWizardPage::TransferDataFromWindow()
{
    if (m_transfer_data_from_window_out_func)
    {
        int result = 1;
        m_transfer_data_from_window_out_func(m_object, &result);
        return result != 0;
    }

    if (!m_transfer_data_from_window_func)
    {
        return wxWizardPage::TransferDataFromWindow();
    }
    return m_transfer_data_from_window_func(m_object) != 0;
}

bool kwxWizardPage::TransferDataToWindow()
{
    if (m_transfer_data_to_window_out_func)
    {
        int result = 1;
        m_transfer_data_to_window_out_func(m_object, &result);
        return result != 0;
    }

    if (!m_transfer_data_to_window_func)
    {
        return wxWizardPage::TransferDataToWindow();
    }
    return m_transfer_data_to_window_func(m_object) != 0;
}

// ---------------------------------------------------------------------------
// wxWizardPageSimple
//
// Same bodies as kwxWizardPage, except that an unset hook falls through to the
// wxWizardPageSimple implementation instead of a neutral value: the base already
// answers from the prev/next pointers, which is what keeps SetNext()/SetPrev()/
// Chain() meaningful on a page that overrides nothing.
// ---------------------------------------------------------------------------

kwxWizardPageSimple::kwxWizardPageSimple(void* pObject, wxWizard* parent, wxWizardPage* prev,
                                         wxWizardPage* next, const wxBitmapBundle& bitmap) :
    wxWizardPageSimple(parent, prev, next, bitmap)
{
    m_object = pObject;
    m_get_next_func = nullptr;
    m_get_prev_func = nullptr;
    m_transfer_data_from_window_func = nullptr;
    m_transfer_data_to_window_func = nullptr;
    m_get_next_out_func = nullptr;
    m_get_prev_out_func = nullptr;
    m_transfer_data_from_window_out_func = nullptr;
    m_transfer_data_to_window_out_func = nullptr;
}

wxWizardPage* kwxWizardPageSimple::GetNext() const
{
    if (m_get_next_out_func)
    {
        void* page = nullptr;
        m_get_next_out_func(m_object, &page);
        return static_cast<wxWizardPage*>(page);
    }

    if (!m_get_next_func)
    {
        return wxWizardPageSimple::GetNext();
    }
    return (wxWizardPage*) m_get_next_func(m_object);
}

wxWizardPage* kwxWizardPageSimple::GetPrev() const
{
    if (m_get_prev_out_func)
    {
        void* page = nullptr;
        m_get_prev_out_func(m_object, &page);
        return static_cast<wxWizardPage*>(page);
    }

    if (!m_get_prev_func)
    {
        return wxWizardPageSimple::GetPrev();
    }
    return (wxWizardPage*) m_get_prev_func(m_object);
}

bool kwxWizardPageSimple::TransferDataFromWindow()
{
    if (m_transfer_data_from_window_out_func)
    {
        int result = 1;
        m_transfer_data_from_window_out_func(m_object, &result);
        return result != 0;
    }

    if (!m_transfer_data_from_window_func)
    {
        return wxWizardPageSimple::TransferDataFromWindow();
    }
    return m_transfer_data_from_window_func(m_object) != 0;
}

bool kwxWizardPageSimple::TransferDataToWindow()
{
    if (m_transfer_data_to_window_out_func)
    {
        int result = 1;
        m_transfer_data_to_window_out_func(m_object, &result);
        return result != 0;
    }

    if (!m_transfer_data_to_window_func)
    {
        return wxWizardPageSimple::TransferDataToWindow();
    }
    return m_transfer_data_to_window_func(m_object) != 0;
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
// kwxDocTemplate
//
// The base class can only create through a wxClassInfo, so both creation hooks are
// taken here and the object the hook published is returned.  Never fall back to the
// base: with null class info it returns null anyway.
// ---------------------------------------------------------------------------

kwxDocTemplate::kwxDocTemplate(void* pObject, wxDocManager* manager, const wxString& descr,
                               const wxString& filter, const wxString& dir, const wxString& ext,
                               const wxString& docTypeName, const wxString& viewTypeName,
                               long flags) :
    wxDocTemplate(manager, descr, filter, dir, ext, docTypeName, viewTypeName, nullptr, nullptr,
                  flags)
{
    m_object = pObject;
    m_create_document_func = nullptr;
    m_create_view_func = nullptr;
    m_created_document = nullptr;
    m_created_view = nullptr;
    m_initing_document = nullptr;
}

// Records the document for the DoCreateView() hook, which receives no argument.  The
// base implementation is what calls the document's OnCreate(), so it must run.
bool kwxDocTemplate::InitDocument(wxDocument* doc, const wxString& path, long flags)
{
    m_initing_document = doc;
    const bool created = wxDocTemplate::InitDocument(doc, path, flags);
    m_initing_document = nullptr;
    return created;
}

wxDocument* kwxDocTemplate::DoCreateDocument()
{
    if (!m_create_document_func)
    {
        return nullptr;
    }
    m_created_document = nullptr;
    m_create_document_func(m_object, this);
    wxDocument* const doc = m_created_document;
    m_created_document = nullptr;
    return doc;
}

wxView* kwxDocTemplate::DoCreateView()
{
    if (!m_create_view_func)
    {
        return nullptr;
    }
    m_created_view = nullptr;
    m_create_view_func(m_object, this, m_initing_document);
    wxView* const view = m_created_view;
    m_created_view = nullptr;
    return view;
}

// ---------------------------------------------------------------------------
// wxDocument
//
// LoadObject() and SaveObject() are deliberately not overridden: their
// signatures take std::istream& / std::ostream& (wx/docview.h:101-105), which
// cannot cross a fixed extern "C" boundary.  Both are in the not-representable
// register of .private/port/fix_worklist.md.
// ---------------------------------------------------------------------------

kwxDocument::kwxDocument(void* pObject, wxDocument* parent) : wxDocument(parent)
{
    m_object = pObject;
    m_do_open_document_func = nullptr;
    m_do_save_document_func = nullptr;
    m_get_class_info_func = nullptr;
    m_is_modified_func = nullptr;
    m_modify_func = nullptr;
    m_on_create_func = nullptr;
    m_on_open_document_func = nullptr;
    m_do_open_document_hook = nullptr;
    m_do_open_document_hook_data = nullptr;
    m_do_save_document_hook = nullptr;
    m_do_save_document_hook_data = nullptr;
    m_is_modified_hook = nullptr;
    m_is_modified_hook_data = nullptr;
    m_modify_hook = nullptr;
    m_modify_hook_data = nullptr;
    m_on_create_hook = nullptr;
    m_on_create_hook_data = nullptr;
    m_on_open_document_hook = nullptr;
    m_on_open_document_hook_data = nullptr;
    m_published = false;
    m_result_bool = false;
}

bool kwxDocument::DoOpenDocument(const wxString& file)
{
    if (m_do_open_document_hook)
    {
        m_published = false;
        m_do_open_document_hook(m_do_open_document_hook_data, (void*) &file, nullptr);
        return m_published ? m_result_bool : wxDocument::DoOpenDocument(file);
    }
    if (!m_do_open_document_func)
    {
        return wxDocument::DoOpenDocument(file);
    }
    return m_do_open_document_func(m_object, (void*) &file) != 0;
}

bool kwxDocument::DoSaveDocument(const wxString& file)
{
    if (m_do_save_document_hook)
    {
        m_published = false;
        m_do_save_document_hook(m_do_save_document_hook_data, (void*) &file, nullptr);
        return m_published ? m_result_bool : wxDocument::DoSaveDocument(file);
    }
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
    if (m_is_modified_hook)
    {
        m_published = false;
        m_is_modified_hook(m_is_modified_hook_data, nullptr, nullptr);
        return m_published ? m_result_bool : wxDocument::IsModified();
    }
    if (!m_is_modified_func)
    {
        return wxDocument::IsModified();
    }
    return m_is_modified_func(m_object) != 0;
}

void kwxDocument::Modify(bool modified)
{
    if (m_modify_hook)
    {
        m_published = false;
        m_modify_hook(m_modify_hook_data, (void*) (intptr_t) (modified ? 1 : 0), nullptr);
        return;
    }
    if (!m_modify_func)
    {
        wxDocument::Modify(modified);
        return;
    }
    m_modify_func(m_object, modified ? 1 : 0);
}

bool kwxDocument::OnCreate(const wxString& path, long flags)
{
    if (m_on_create_hook)
    {
        m_published = false;
        m_on_create_hook(m_on_create_hook_data, (void*) &path, (void*) (intptr_t) flags);
        return m_published ? m_result_bool : wxDocument::OnCreate(path, flags);
    }
    if (!m_on_create_func)
    {
        return wxDocument::OnCreate(path, flags);
    }
    return m_on_create_func(m_object, (void*) &path, flags) != 0;
}

bool kwxDocument::OnOpenDocument(const wxString& filename)
{
    if (m_on_open_document_hook)
    {
        m_published = false;
        m_on_open_document_hook(m_on_open_document_hook_data, (void*) &filename, nullptr);
        return m_published ? m_result_bool : wxDocument::OnOpenDocument(filename);
    }
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
    m_on_create_hook = nullptr;
    m_on_create_hook_data = nullptr;
    m_on_close_hook = nullptr;
    m_on_close_hook_data = nullptr;
    m_published = false;
    m_result_bool = false;
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
    if (m_on_close_hook)
    {
        m_published = false;
        m_on_close_hook(m_on_close_hook_data, (void*) (intptr_t) (deleteWindow ? 1 : 0), nullptr);
        return m_published ? m_result_bool : wxView::OnClose(deleteWindow);
    }
    if (!m_on_close_func)
    {
        return wxView::OnClose(deleteWindow);
    }
    return m_on_close_func(m_object, deleteWindow ? 1 : 0) != 0;
}

bool kwxView::OnCreate(wxDocument* document, long flags)
{
    if (m_on_create_hook)
    {
        m_published = false;
        m_on_create_hook(m_on_create_hook_data, document, (void*) (intptr_t) flags);
        return m_published ? m_result_bool : wxView::OnCreate(document, flags);
    }
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
// wxDataViewModel / wxDataViewCustomRenderer
// ---------------------------------------------------------------------------

// wxWidgets marks the renderer's Activate()/LeftClick() deprecated (ActivateCell()
// replaces both) but a port may still implement them, so their override definitions
// below -- and their delegated base calls -- have the deprecation warning suppressed,
// exactly as the matching declarations in include/kwx_helper_hooks.h do.
#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4996)
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

kwxDataViewModel::kwxDataViewModel(void* pObject) : wxDataViewModel()
{
    m_object = pObject;
    m_get_value_hook = nullptr;
    m_get_value_hook_data = nullptr;
    m_set_value_hook = nullptr;
    m_set_value_hook_data = nullptr;
    m_get_parent_hook = nullptr;
    m_get_parent_hook_data = nullptr;
    m_is_container_hook = nullptr;
    m_is_container_hook_data = nullptr;
    m_get_children_hook = nullptr;
    m_get_children_hook_data = nullptr;
    m_has_value_hook = nullptr;
    m_has_value_hook_data = nullptr;
    m_is_enabled_hook = nullptr;
    m_is_enabled_hook_data = nullptr;
    m_has_container_columns_hook = nullptr;
    m_has_container_columns_hook_data = nullptr;
    m_compare_hook = nullptr;
    m_compare_hook_data = nullptr;
    m_has_default_compare_hook = nullptr;
    m_has_default_compare_hook_data = nullptr;
    m_resort_hook = nullptr;
    m_resort_hook_data = nullptr;
    m_get_attr_hook = nullptr;
    m_get_attr_hook_data = nullptr;
    m_published = false;
    m_pending_column = 0;
    m_pending_ascending = false;
    m_result_variant = wxVariant();
    m_result_item = wxDataViewItem();
    m_result_bool = false;
    m_result_int = 0;
    m_result_uint = 0;
    m_result_attr = wxDataViewItemAttr();
    m_children_target = nullptr;
}

// Clears everything the previous hook call published, so a callback that publishes
// nothing falls through to the neutral default of the hook it was called from.
void kwxDataViewModel::ResetInFlight() const
{
    m_published = false;
    m_pending_column = 0;
    m_pending_ascending = false;
    m_result_variant = wxVariant();
    m_result_item = wxDataViewItem();
    m_result_bool = false;
    m_result_int = 0;
    m_result_uint = 0;
    m_result_attr = wxDataViewItemAttr();
}

void kwxDataViewModel::GetValue(wxVariant& variant, const wxDataViewItem& item,
                                unsigned int col) const
{
    if (!m_get_value_hook)
    {
        // No callback: leave the variant untouched, which is what an empty cell is.
        return;
    }

    ResetInFlight();
    m_pending_column = col;
    m_get_value_hook(m_get_value_hook_data, const_cast<wxDataViewItem*>(&item), &variant);

    if (m_published)
    {
        variant = m_result_variant;
    }
}

bool kwxDataViewModel::SetValue(const wxVariant& variant, const wxDataViewItem& item,
                                unsigned int col)
{
    if (!m_set_value_hook)
    {
        return false;
    }

    ResetInFlight();
    m_pending_column = col;
    m_set_value_hook(m_set_value_hook_data, const_cast<wxDataViewItem*>(&item),
                     const_cast<wxVariant*>(&variant));
    return m_published ? m_result_bool : false;
}

wxDataViewItem kwxDataViewModel::GetParent(const wxDataViewItem& item) const
{
    if (!m_get_parent_hook)
    {
        return wxDataViewItem();
    }

    ResetInFlight();
    m_get_parent_hook(m_get_parent_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
    return m_published ? m_result_item : wxDataViewItem();
}

bool kwxDataViewModel::IsContainer(const wxDataViewItem& item) const
{
    if (!m_is_container_hook)
    {
        return false;
    }

    ResetInFlight();
    m_is_container_hook(m_is_container_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
    return m_published ? m_result_bool : false;
}

unsigned int kwxDataViewModel::GetChildren(const wxDataViewItem& item,
                                           wxDataViewItemArray& children) const
{
    if (!m_get_children_hook)
    {
        return 0;
    }

    ResetInFlight();
    m_children_target = &children;
    m_get_children_hook(m_get_children_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
    m_children_target = nullptr;

    // AddChildResult() appends without publishing a count, so a callback may answer the
    // hook purely by appending children; only an explicit count overrides the array size.
    if (m_published)
    {
        return m_result_uint;
    }
    return static_cast<unsigned int>(children.GetCount());
}

bool kwxDataViewModel::HasValue(const wxDataViewItem& item, unsigned int col) const
{
    if (!m_has_value_hook)
    {
        return true;
    }

    ResetInFlight();
    m_pending_column = col;
    m_has_value_hook(m_has_value_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
    return m_published ? m_result_bool : true;
}

bool kwxDataViewModel::IsEnabled(const wxDataViewItem& item, unsigned int col) const
{
    if (!m_is_enabled_hook)
    {
        return true;
    }

    ResetInFlight();
    m_pending_column = col;
    m_is_enabled_hook(m_is_enabled_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
    return m_published ? m_result_bool : true;
}

// No callback falls through to the base implementation, which reports "no attributes" and
// leaves the attribute untouched; a callback that publishes nothing does the same.
bool kwxDataViewModel::GetAttr(const wxDataViewItem& item, unsigned int col,
                               wxDataViewItemAttr& attr) const
{
    if (!m_get_attr_hook)
    {
        return wxDataViewModel::GetAttr(item, col, attr);
    }

    ResetInFlight();
    m_pending_column = col;
    m_get_attr_hook(m_get_attr_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
    if (!m_published)
    {
        return wxDataViewModel::GetAttr(item, col, attr);
    }
    if (m_result_bool)
    {
        attr = m_result_attr;
    }
    return m_result_bool;
}

bool kwxDataViewModel::HasContainerColumns(const wxDataViewItem& item) const
{
    if (!m_has_container_columns_hook)
    {
        return false;
    }

    ResetInFlight();
    m_has_container_columns_hook(m_has_container_columns_hook_data,
                                 const_cast<wxDataViewItem*>(&item), nullptr);
    return m_published ? m_result_bool : false;
}

int kwxDataViewModel::Compare(const wxDataViewItem& item1, const wxDataViewItem& item2,
                              unsigned int column, bool ascending) const
{
    if (!m_compare_hook)
    {
        return 0;
    }

    ResetInFlight();
    m_pending_column = column;
    m_pending_ascending = ascending;
    m_compare_hook(m_compare_hook_data, const_cast<wxDataViewItem*>(&item1),
                   const_cast<wxDataViewItem*>(&item2));
    return m_published ? m_result_int : 0;
}

bool kwxDataViewModel::HasDefaultCompare() const
{
    if (!m_has_default_compare_hook)
    {
        return false;
    }

    ResetInFlight();
    m_has_default_compare_hook(m_has_default_compare_hook_data, nullptr, nullptr);
    return m_published ? m_result_bool : false;
}

void kwxDataViewModel::Resort()
{
    if (!m_resort_hook)
    {
        wxDataViewModel::Resort();
        return;
    }

    ResetInFlight();
    m_resort_hook(m_resort_hook_data, nullptr, nullptr);
}

kwxDataViewCustomRenderer::kwxDataViewCustomRenderer(void* pObject, const wxString& variantType,
                                                     wxDataViewCellMode mode, int align) :
    wxDataViewCustomRenderer(variantType, mode, align)
{
    m_object = pObject;
    m_render_hook = nullptr;
    m_render_hook_data = nullptr;
    m_get_size_hook = nullptr;
    m_get_size_hook_data = nullptr;
    m_set_value_hook = nullptr;
    m_set_value_hook_data = nullptr;
    m_get_value_hook = nullptr;
    m_get_value_hook_data = nullptr;
    m_activate_cell_hook = nullptr;
    m_activate_cell_hook_data = nullptr;
    m_activate_hook = nullptr;
    m_activate_hook_data = nullptr;
    m_left_click_hook = nullptr;
    m_left_click_hook_data = nullptr;
    m_start_drag_hook = nullptr;
    m_start_drag_hook_data = nullptr;
    m_create_editor_ctrl_hook = nullptr;
    m_create_editor_ctrl_hook_data = nullptr;
    m_get_value_from_editor_ctrl_hook = nullptr;
    m_get_value_from_editor_ctrl_hook_data = nullptr;
    m_validate_hook = nullptr;
    m_validate_hook_data = nullptr;
    m_has_editor_ctrl_hook = nullptr;
    m_has_editor_ctrl_hook_data = nullptr;
    m_accessible_description_hook = nullptr;
    m_accessible_description_hook_data = nullptr;
    m_published = false;
    m_render_rect = wxRect();
    m_render_state = 0;
    m_render_dc = nullptr;
    m_pending_column = 0;
    m_editor_rect = wxRect();
    m_editor_parent = nullptr;
    m_editor_ctrl = nullptr;
    m_current_value = wxVariant();
    m_result_bool = false;
    m_result_size = wxSize(0, 0);
    m_result_variant = wxVariant();
    m_result_window = nullptr;
    m_mouse_event = nullptr;
    m_pending_cursor = wxPoint(0, 0);
    m_cursor_valid = false;
    m_has_editor_value = false;
}

void kwxDataViewCustomRenderer::ResetInFlight() const
{
    m_published = false;
    m_result_bool = false;
    m_result_size = wxSize(0, 0);
    m_result_variant = wxVariant();
    m_result_window = nullptr;
    m_mouse_event = nullptr;
    m_pending_cursor = wxPoint(0, 0);
    m_cursor_valid = false;
    m_has_editor_value = false;
    m_accessible_description.clear();
}

bool kwxDataViewCustomRenderer::Render(wxRect cell, wxDC* draw_dc, int state)
{
    if (!m_render_hook)
    {
        // Nothing to draw: an unset Render callback paints nothing and reports failure so
        // the caller does not treat the cell as rendered.
        return false;
    }

    ResetInFlight();
    m_render_rect = cell;
    m_render_state = state;
    m_render_dc = draw_dc;
    m_render_hook(m_render_hook_data, draw_dc, nullptr);
    return m_published ? m_result_bool : false;
}

wxSize kwxDataViewCustomRenderer::GetSize() const
{
    if (!m_get_size_hook)
    {
        return wxSize(0, 0);
    }

    ResetInFlight();
    m_get_size_hook(m_get_size_hook_data, nullptr, nullptr);
    return m_published ? m_result_size : wxSize(0, 0);
}

bool kwxDataViewCustomRenderer::SetValue(const wxVariant& value)
{
    // Keep the value even without a callback: Render() and GetValue() read it back.
    m_current_value = value;

    if (!m_set_value_hook)
    {
        return false;
    }

    ResetInFlight();
    m_set_value_hook(m_set_value_hook_data, const_cast<wxVariant*>(&value), nullptr);
    return m_published ? m_result_bool : false;
}

bool kwxDataViewCustomRenderer::GetValue(wxVariant& value) const
{
    if (!m_get_value_hook)
    {
        return false;
    }

    ResetInFlight();
    m_get_value_hook(m_get_value_hook_data, &value, nullptr);

    // Publishing a value is the success signal for this hook.
    if (m_published)
    {
        value = m_result_variant;
        m_current_value = m_result_variant;
    }
    return m_published;
}

bool kwxDataViewCustomRenderer::ActivateCell(const wxRect& cell,
                                             [[maybe_unused]] wxDataViewModel* model,
                                             [[maybe_unused]] const wxDataViewItem& item,
                                             unsigned int col, const wxMouseEvent* mouseEvent)
{
    if (!m_activate_cell_hook)
    {
        return wxDataViewCustomRenderer::ActivateCell(cell, model, item, col, mouseEvent);
    }

    ResetInFlight();
    m_render_rect = cell;
    m_pending_column = col;
    // Read from the callback with GetActivateCellMouseEvent; it dies with this call.
    m_mouse_event = mouseEvent;
    m_activate_cell_hook(m_activate_cell_hook_data, nullptr, nullptr);
    return m_published ? m_result_bool : false;
}

bool kwxDataViewCustomRenderer::Activate(wxRect cell, [[maybe_unused]] wxDataViewModel* model,
                                         [[maybe_unused]] const wxDataViewItem& item,
                                         unsigned int col)
{
    if (!m_activate_hook)
    {
        return wxDataViewCustomRenderer::Activate(cell, model, item, col);
    }

    ResetInFlight();
    m_render_rect = cell;
    m_pending_column = col;
    m_activate_hook(m_activate_hook_data, nullptr, nullptr);
    return m_published ? m_result_bool : false;
}

bool kwxDataViewCustomRenderer::LeftClick(wxPoint cursor, wxRect cell,
                                          [[maybe_unused]] wxDataViewModel* model,
                                          [[maybe_unused]] const wxDataViewItem& item,
                                          unsigned int col)
{
    if (!m_left_click_hook)
    {
        return wxDataViewCustomRenderer::LeftClick(cursor, cell, model, item, col);
    }

    ResetInFlight();
    m_render_rect = cell;
    m_pending_column = col;
    m_pending_cursor = cursor;
    m_cursor_valid = true;
    m_left_click_hook(m_left_click_hook_data, nullptr, nullptr);
    return m_published ? m_result_bool : false;
}

bool kwxDataViewCustomRenderer::StartDrag(const wxPoint& cursor, const wxRect& cell,
                                          [[maybe_unused]] wxDataViewModel* model,
                                          [[maybe_unused]] const wxDataViewItem& item,
                                          unsigned int col)
{
    if (!m_start_drag_hook)
    {
        return wxDataViewCustomRenderer::StartDrag(cursor, cell, model, item, col);
    }

    ResetInFlight();
    m_render_rect = cell;
    m_pending_column = col;
    m_pending_cursor = cursor;
    m_cursor_valid = true;
    m_start_drag_hook(m_start_drag_hook_data, nullptr, nullptr);
    return m_published ? m_result_bool : false;
}

wxWindow* kwxDataViewCustomRenderer::CreateEditorCtrl(wxWindow* parent, wxRect labelRect,
                                                      const wxVariant& value)
{
    if (!m_create_editor_ctrl_hook)
    {
        return wxDataViewCustomRenderer::CreateEditorCtrl(parent, labelRect, value);
    }

    ResetInFlight();
    m_editor_rect = labelRect;
    m_editor_parent = parent;
    m_create_editor_ctrl_hook(m_create_editor_ctrl_hook_data, parent,
                              const_cast<wxVariant*>(&value));
    m_editor_ctrl = m_published ? m_result_window : nullptr;
    return m_editor_ctrl;
}

bool kwxDataViewCustomRenderer::GetValueFromEditorCtrl(wxWindow* editor, wxVariant& value)
{
    if (!m_get_value_from_editor_ctrl_hook)
    {
        return wxDataViewCustomRenderer::GetValueFromEditorCtrl(editor, value);
    }

    ResetInFlight();
    m_editor_ctrl = editor;
    m_get_value_from_editor_ctrl_hook(m_get_value_from_editor_ctrl_hook_data, editor, nullptr);
    if (m_has_editor_value)
    {
        value = m_result_variant;
    }
    // Publishing an edited value alone is success; the boolean only matters when the
    // callback publishes it.
    return m_published ? m_result_bool : m_has_editor_value;
}

bool kwxDataViewCustomRenderer::Validate(wxVariant& value)
{
    if (!m_validate_hook)
    {
        return wxDataViewCustomRenderer::Validate(value);
    }

    ResetInFlight();
    m_validate_hook(m_validate_hook_data, &value, nullptr);
    return m_published ? m_result_bool : true;
}

bool kwxDataViewCustomRenderer::HasEditorCtrl() const
{
    if (!m_has_editor_ctrl_hook)
    {
        return false;
    }

    ResetInFlight();
    m_has_editor_ctrl_hook(m_has_editor_ctrl_hook_data, nullptr, nullptr);
    return m_published ? m_result_bool : false;
}

#if wxUSE_ACCESSIBILITY
wxString kwxDataViewCustomRenderer::GetAccessibleDescription() const
{
    if (!m_accessible_description_hook)
    {
        // No callback: the base implementation, which stringifies the current value.
        return wxDataViewCustomRenderer::GetAccessibleDescription();
    }

    ResetInFlight();
    m_accessible_description_hook(m_accessible_description_hook_data, nullptr, nullptr);
    return m_published ? m_accessible_description :
                         wxDataViewCustomRenderer::GetAccessibleDescription();
}
#endif

#if defined(_MSC_VER)
    #pragma warning(pop)
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

// wxDataViewRendererBase declares IsHighlighted() protected, and no renderer class makes
// it public again.  This shim re-declares that one member as public and adds neither data
// nor overrides, so the static_cast below reaches the real virtual through the object's own
// vtable.
class kwxRendererHighlightAccess : public wxDataViewRenderer
{
public:
    using wxDataViewRenderer::IsHighlighted;
};

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
    // exported under the base name.
    //
    // These aliases are only valid on the matching helper object.  A wxApp is not
    // a kwxAppConsole, so the checked cast below does nothing when the receiver is
    // the wrong helper -- the unchecked cast it replaces wrote the callback pointer
    // into unrelated memory, which crashed the process during shutdown.

    EXPORT void wxAppConsole_SetOnOnCmdLineParsed(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnCmdLineParsed(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnInitCmdLine(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnInitCmdLine(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnExit(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnExit(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnRun(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnRun(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnAssertFailure(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnAssertFailure(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnEventLoopEnter(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnEventLoopEnter(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnExceptionInMainLoop(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnExceptionInMainLoop(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnFatalException(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnFatalException(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnOnUnhandledException(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnOnUnhandledException(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnStoreCurrentException(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnStoreCurrentException(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnRethrowStoredException(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnRethrowStoredException(pFunction);
        }
    }

    EXPORT void wxAppConsole_SetOnCreateTraits(wxAppConsole* self, void* pFunction)
    {
        if (kwxAppConsole* helper = dynamic_cast<kwxAppConsole*>(self))
        {
            helper->SetOnCreateTraits(pFunction);
        }
    }

    EXPORT wxString* wxAppConsole_GetAppName(wxAppConsole* self)
    {
        return new wxString(self->GetAppName());
    }

    EXPORT void wxAppConsole_SetAppName(wxAppConsole* self, wxString* name)
    {
        self->SetAppName(*name);
    }

    EXPORT wxString* wxAppConsole_GetAppDisplayName(wxAppConsole* self)
    {
        return new wxString(self->GetAppDisplayName());
    }

    EXPORT void wxAppConsole_SetAppDisplayName(wxAppConsole* self, wxString* name)
    {
        self->SetAppDisplayName(*name);
    }

    EXPORT wxString* wxAppConsole_GetVendorName(wxAppConsole* self)
    {
        return new wxString(self->GetVendorName());
    }

    EXPORT void wxAppConsole_SetVendorName(wxAppConsole* self, wxString* name)
    {
        self->SetVendorName(*name);
    }

    EXPORT void wxAppConsole_ExitMainLoop(wxAppConsole* self)
    {
        self->ExitMainLoop();
    }

    EXPORT void wxAppConsole_ProcessPendingEvents(wxAppConsole* self)
    {
        self->ProcessPendingEvents();
    }

    EXPORT int wxAppConsole_Yield(wxAppConsole* self)
    {
        return self->Yield();
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

    EXPORT void kwxApp_SetOnOnFatalException(kwxApp* self, void* pFunction)
    {
        self->SetOnOnFatalException(pFunction);
    }

    EXPORT void kwxApp_SetOnOnUnhandledException(kwxApp* self, void* pFunction)
    {
        self->SetOnOnUnhandledException(pFunction);
    }

    EXPORT void kwxApp_SetOnStoreCurrentException(kwxApp* self, void* pFunction)
    {
        self->SetOnStoreCurrentException(pFunction);
    }

    EXPORT void kwxApp_SetOnOnExceptionInMainLoop(kwxApp* self, void* pFunction)
    {
        self->SetOnOnExceptionInMainLoop(pFunction);
    }

    EXPORT void kwxApp_SetOnRethrowStoredException(kwxApp* self, void* pFunction)
    {
        self->SetOnRethrowStoredException(pFunction);
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

    EXPORT void kwxApp_SetOnOnFatalException(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnOnUnhandledException(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnStoreCurrentException(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnOnExceptionInMainLoop(kwxApp* self, void* pFunction)
    {
        wxUnusedVar(self);
        wxUnusedVar(pFunction);
    }

    EXPORT void kwxApp_SetOnRethrowStoredException(kwxApp* self, void* pFunction)
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

    // kwxDebugReportUpload ----------------------------------------------------

    EXPORT void* kwxDebugReportUpload_Create(void* pObject, wxString* url, wxString* input,
                                             wxString* action)
    {
        return (void*) new kwxDebugReportUpload(pObject, *url, *input, *action);
    }

    EXPORT void kwxDebugReportUpload_Delete(kwxDebugReportUpload* self)
    {
        delete self;
    }

    EXPORT void kwxDebugReportUpload_SetOnOnServerReply(kwxDebugReportUpload* self, void* pFunction)
    {
        self->SetOnOnServerReply(pFunction);
    }

    EXPORT void kwxDebugReportUpload_SetOnServerReplyResult(kwxDebugReportUpload* self, int result)
    {
        self->SetOnServerReplyResult(result != 0);
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

    EXPORT void kwxPanel_SetOnDoGetBestClientSize(kwxPanel* self, void* pFunction)
    {
        self->SetOnDoGetBestClientSize(pFunction);
    }

    EXPORT void kwxPanel_SetOnScrollWindow(kwxPanel* self, void* pFunction)
    {
        self->SetOnScrollWindow(pFunction);
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

    EXPORT void wxPanel_SetOnDoGetBestClientSize(wxPanel* self, void* pFunction)
    {
        static_cast<kwxPanel*>(self)->SetOnDoGetBestClientSize(pFunction);
    }

    EXPORT void wxPanel_SetOnScrollWindow(wxPanel* self, void* pFunction)
    {
        static_cast<kwxPanel*>(self)->SetOnScrollWindow(pFunction);
    }

    // kwxDialog ---------------------------------------------------------------

    EXPORT wxDialog* kwxDialog_Create(void* pObject, wxWindow* parent, int id, wxString* title,
                                      int x, int y, int width, int height, long style)
    {
        if (!title)
            return nullptr;
        return new kwxDialog(pObject, parent, id, *title, wxPoint(x, y), wxSize(width, height),
                             style);
    }

    EXPORT void kwxDialog_SetOnTransferDataFromWindow(kwxDialog* self, void* pFunction)
    {
        self->SetOnTransferDataFromWindow(pFunction);
    }

    EXPORT void kwxDialog_SetOnTransferDataToWindow(kwxDialog* self, void* pFunction)
    {
        self->SetOnTransferDataToWindow(pFunction);
    }

    // Qualified calls: a plain virtual call would re-enter the hook.
    EXPORT int kwxDialogOnTransferDataFromWindowBase(kwxDialog* self)
    {
        if (!self)
            return 0;
        return self->wxDialog::TransferDataFromWindow();
    }

    EXPORT int kwxDialogOnTransferDataToWindowBase(kwxDialog* self)
    {
        if (!self)
            return 0;
        return self->wxDialog::TransferDataToWindow();
    }

    // kwxFrame ----------------------------------------------------------------

    EXPORT void* kwxFrame_Create(wxWindow* parent, int id, wxString* title, int x, int y, int width,
                                 int height, long style)
    {
        return new kwxFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void kwxFrame_Delete(kwxFrame* self)
    {
        delete self;
    }

    EXPORT void kwxFrame_SetCallbackObject(kwxFrame* self, void* object)
    {
        self->SetCallbackObject(object);
    }

    EXPORT void* kwxFrame_GetCallbackObject(kwxFrame* self)
    {
        return self->GetCallbackObject();
    }

    EXPORT void kwxFrame_SetOnProcessEvent(kwxFrame* self, void* pFunction)
    {
        self->SetOnProcessEvent(pFunction);
    }

    EXPORT void kwxFrame_SetOnProcessEventWithData(kwxFrame* self, void* pFunction, void* data)
    {
        self->SetOnProcessEventWithData(pFunction, data);
    }

    EXPORT void kwxFrame_SetProcessEventResult(kwxFrame* self, int result)
    {
        self->SetProcessEventResult(result != 0);
    }

    EXPORT void kwxFrame_SetOnTryBefore(kwxFrame* self, void* pFunction)
    {
        self->SetOnTryBefore(pFunction);
    }

    EXPORT void kwxFrame_SetOnTryBeforeWithData(kwxFrame* self, void* pFunction, void* data)
    {
        self->SetOnTryBeforeWithData(pFunction, data);
    }

    EXPORT void kwxFrame_SetTryBeforeResult(kwxFrame* self, int result)
    {
        self->SetTryBeforeResult(result != 0);
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

    EXPORT void kwxPreferencesPage_SetOnGetNameResult(kwxPreferencesPage* self, const char* name)
    {
        self->SetNameResult(name);
    }

    EXPORT void kwxPreferencesPage_SetOnCreateWindowResult(kwxPreferencesPage* self,
                                                           wxWindow* window)
    {
        self->SetCreateWindowResult(window);
    }

    EXPORT void kwxPreferencesPage_SetOnGetIconResult(kwxPreferencesPage* self,
                                                      wxBitmapBundle* bundle)
    {
        self->SetGetIconResult(bundle);
    }

    // wxStockPreferencesPage ------------------------------------------------

    // The receiver of every function below is a kwxStockPreferencesPage, because
    // the wxStockPreferencesPage base is abstract (CreateWindow is pure).  The
    // symbols use the wx<Class>_ name so they match the declaration block.

    EXPORT void* wxStockPreferencesPage_Create(int kind)
    {
        // Only the two stock kinds exist; anything else is the General page.
        const wxStockPreferencesPage::Kind page_kind =
            (kind == wxStockPreferencesPage::Kind_Advanced) ?
                wxStockPreferencesPage::Kind_Advanced :
                wxStockPreferencesPage::Kind_General;
        return (void*) new kwxStockPreferencesPage(page_kind);
    }

    EXPORT void* wxStockPreferencesPage_CreateWithState(int kind, void* pObject)
    {
        // Only the two stock kinds exist; anything else is the General page.
        const wxStockPreferencesPage::Kind page_kind =
            (kind == wxStockPreferencesPage::Kind_Advanced) ?
                wxStockPreferencesPage::Kind_Advanced :
                wxStockPreferencesPage::Kind_General;
        return (void*) new kwxStockPreferencesPage(page_kind, pObject);
    }

    EXPORT int wxStockPreferencesPage_GetKind(wxStockPreferencesPage* self)
    {
        return static_cast<int>(static_cast<kwxStockPreferencesPage*>(self)->GetKind());
    }

    EXPORT void wxStockPreferencesPage_Delete(wxStockPreferencesPage* self)
    {
        delete static_cast<kwxStockPreferencesPage*>(self);
    }

    EXPORT void wxStockPreferencesPage_SetOnCreateWindow(wxStockPreferencesPage* self,
                                                         void* pFunction)
    {
        static_cast<kwxStockPreferencesPage*>(self)->SetOnCreateWindow(pFunction);
    }

    EXPORT void wxStockPreferencesPage_SetOnCreateWindowResult(wxStockPreferencesPage* self,
                                                               wxWindow* window)
    {
        static_cast<kwxStockPreferencesPage*>(self)->SetCreateWindowResult(window);
    }

    // wxPreferencesEditor ----------------------------------------------------

    EXPORT void* wxPreferencesEditor_Create(wxString* title)
    {
        return (void*) new wxPreferencesEditor(title ? *title : wxString());
    }

    EXPORT void wxPreferencesEditor_Delete(wxPreferencesEditor* self)
    {
        delete self;
    }

    EXPORT void wxPreferencesEditor_AddPage(wxPreferencesEditor* self, wxPreferencesPage* page)
    {
        self->AddPage(page);
    }

    EXPORT void wxPreferencesEditor_AddStockPage(wxPreferencesEditor* self,
                                                 wxStockPreferencesPage* page)
    {
        // Up-cast only: kwxStockPreferencesPage derives from wxStockPreferencesPage,
        // which derives from wxPreferencesPage.  The editor takes ownership of the
        // page, exactly as wxPreferencesEditor_AddPage does.
        self->AddPage(static_cast<wxPreferencesPage*>(page));
    }

    EXPORT void wxPreferencesEditor_Show(wxPreferencesEditor* self, wxWindow* parent)
    {
        self->Show(parent);
    }

    EXPORT void wxPreferencesEditor_Dismiss(wxPreferencesEditor* self)
    {
        self->Dismiss();
    }

    EXPORT int wxPreferencesEditor_ShouldApplyChangesImmediately()
    {
        return wxPreferencesEditor::ShouldApplyChangesImmediately() ? 1 : 0;
    }

    EXPORT int wxPreferencesEditor_ShownModally()
    {
        return wxPreferencesEditor::ShownModally() ? 1 : 0;
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

    EXPORT void wxPreferencesPage_Delete(wxPreferencesPage* self)
    {
        delete static_cast<kwxPreferencesPage*>(self);
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

    EXPORT void wxPreferencesPage_SetOnGetNameResult(wxPreferencesPage* self, const char* name)
    {
        static_cast<kwxPreferencesPage*>(self)->SetNameResult(name);
    }

    EXPORT void wxPreferencesPage_SetOnCreateWindowResult(wxPreferencesPage* self, wxWindow* window)
    {
        static_cast<kwxPreferencesPage*>(self)->SetCreateWindowResult(window);
    }

    EXPORT void wxPreferencesPage_SetOnGetIconResult(wxPreferencesPage* self,
                                                     wxBitmapBundle* bundle)
    {
        static_cast<kwxPreferencesPage*>(self)->SetGetIconResult(bundle);
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

    // kwxNativeWindow --------------------------------------------------------

    EXPORT void* kwxNativeWindow_Create(void* pObject, wxWindow* parent, int id, void* handle)
    {
#ifdef __WXMSW__
        return (void*) new kwxNativeWindowMSW(pObject, parent, id, handle);
#else
        return (void*) new kwxNativeWindow(pObject, parent, id, handle);
#endif
    }

    EXPORT void kwxNativeWindow_Delete(kwxNativeWindow* self)
    {
        delete self;
    }

    EXPORT void kwxNativeWindow_SetOnMSWNotify(kwxNativeWindow* self, void* pFunction)
    {
        self->SetOnMSWNotify(pFunction);
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

    // kwxDocTemplate ---------------------------------------------------------

    EXPORT void* kwxDocTemplate_Create(void* pObject, wxDocManager* manager, wxString* descr,
                                       wxString* filter, wxString* dir, wxString* ext,
                                       wxString* docTypeName, wxString* viewTypeName, long flags)
    {
        return (void*) new kwxDocTemplate(pObject, manager, *descr, *filter, *dir, *ext,
                                          *docTypeName, *viewTypeName, flags);
    }

    EXPORT void kwxDocTemplate_SetOnCreateDocument(kwxDocTemplate* self, void* pFunction)
    {
        self->SetOnCreateDocument(pFunction);
    }

    EXPORT void kwxDocTemplate_SetOnCreateView(kwxDocTemplate* self, void* pFunction)
    {
        self->SetOnCreateView(pFunction);
    }

    EXPORT void kwxDocTemplate_SetCreatedDocument(kwxDocTemplate* self, wxDocument* doc)
    {
        self->SetCreatedDocument(doc);
    }

    EXPORT void kwxDocTemplate_SetCreatedView(kwxDocTemplate* self, wxView* view)
    {
        self->SetCreatedView(view);
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

    // The uniform WithData hooks.  Installed means it wins over the typed callback;
    // publishing nothing falls back to the base implementation.

    EXPORT void kwxDocument_SetOnDoOpenDocumentWithData(kwxDocument* self, void* pFunction,
                                                        void* data)
    {
        self->SetOnDoOpenDocumentWithData(pFunction, data);
    }

    EXPORT void kwxDocument_SetDoOpenDocumentResult(kwxDocument* self, int result)
    {
        self->SetDoOpenDocumentResult(result != 0);
    }

    EXPORT void kwxDocument_SetOnDoSaveDocumentWithData(kwxDocument* self, void* pFunction,
                                                        void* data)
    {
        self->SetOnDoSaveDocumentWithData(pFunction, data);
    }

    EXPORT void kwxDocument_SetDoSaveDocumentResult(kwxDocument* self, int result)
    {
        self->SetDoSaveDocumentResult(result != 0);
    }

    EXPORT void kwxDocument_SetOnIsModifiedWithData(kwxDocument* self, void* pFunction, void* data)
    {
        self->SetOnIsModifiedWithData(pFunction, data);
    }

    EXPORT void kwxDocument_SetIsModifiedResult(kwxDocument* self, int result)
    {
        self->SetIsModifiedResult(result != 0);
    }

    EXPORT void kwxDocument_SetOnModifyWithData(kwxDocument* self, void* pFunction, void* data)
    {
        self->SetOnModifyWithData(pFunction, data);
    }

    EXPORT void kwxDocument_SetOnOnCreateWithData(kwxDocument* self, void* pFunction, void* data)
    {
        self->SetOnOnCreateWithData(pFunction, data);
    }

    EXPORT void kwxDocument_SetOnCreateResult(kwxDocument* self, int result)
    {
        self->SetOnCreateResult(result != 0);
    }

    EXPORT void kwxDocument_SetOnOnOpenDocumentWithData(kwxDocument* self, void* pFunction,
                                                        void* data)
    {
        self->SetOnOnOpenDocumentWithData(pFunction, data);
    }

    EXPORT void kwxDocument_SetOnOpenDocumentResult(kwxDocument* self, int result)
    {
        self->SetOnOpenDocumentResult(result != 0);
    }

    // Chaining exports: qualified calls, because a plain virtual call would re-enter
    // the override above and recurse.

    EXPORT int kwxDocument_OnCreateBase(kwxDocument* self, wxString* path, long flags)
    {
        return self->wxDocument::OnCreate(*path, flags);
    }

    EXPORT int kwxDocument_OnOpenDocumentBase(kwxDocument* self, wxString* filename)
    {
        return self->wxDocument::OnOpenDocument(*filename);
    }

    EXPORT int kwxDocument_IsModifiedBase(kwxDocument* self)
    {
        return self->wxDocument::IsModified();
    }

    EXPORT void kwxDocument_ModifyBase(kwxDocument* self, int modified)
    {
        self->wxDocument::Modify(modified != 0);
    }

    EXPORT void* kwxDocument_CreateWithParent(void* pObject, wxDocument* parent)
    {
        return (void*) new kwxDocument(pObject, parent);
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

    EXPORT void wxDocument_SetOnDoOpenDocumentWithData(wxDocument* self, void* pFunction,
                                                       void* data)
    {
        static_cast<kwxDocument*>(self)->SetOnDoOpenDocumentWithData(pFunction, data);
    }

    EXPORT void wxDocument_SetDoOpenDocumentResult(wxDocument* self, int result)
    {
        static_cast<kwxDocument*>(self)->SetDoOpenDocumentResult(result != 0);
    }

    EXPORT void wxDocument_SetOnDoSaveDocumentWithData(wxDocument* self, void* pFunction,
                                                       void* data)
    {
        static_cast<kwxDocument*>(self)->SetOnDoSaveDocumentWithData(pFunction, data);
    }

    EXPORT void wxDocument_SetDoSaveDocumentResult(wxDocument* self, int result)
    {
        static_cast<kwxDocument*>(self)->SetDoSaveDocumentResult(result != 0);
    }

    EXPORT void wxDocument_SetOnIsModifiedWithData(wxDocument* self, void* pFunction, void* data)
    {
        static_cast<kwxDocument*>(self)->SetOnIsModifiedWithData(pFunction, data);
    }

    EXPORT void wxDocument_SetIsModifiedResult(wxDocument* self, int result)
    {
        static_cast<kwxDocument*>(self)->SetIsModifiedResult(result != 0);
    }

    EXPORT void wxDocument_SetOnModifyWithData(wxDocument* self, void* pFunction, void* data)
    {
        static_cast<kwxDocument*>(self)->SetOnModifyWithData(pFunction, data);
    }

    EXPORT void wxDocument_SetOnOnCreateWithData(wxDocument* self, void* pFunction, void* data)
    {
        static_cast<kwxDocument*>(self)->SetOnOnCreateWithData(pFunction, data);
    }

    EXPORT void wxDocument_SetOnCreateResult(wxDocument* self, int result)
    {
        static_cast<kwxDocument*>(self)->SetOnCreateResult(result != 0);
    }

    EXPORT void wxDocument_SetOnOnOpenDocumentWithData(wxDocument* self, void* pFunction,
                                                       void* data)
    {
        static_cast<kwxDocument*>(self)->SetOnOnOpenDocumentWithData(pFunction, data);
    }

    EXPORT void wxDocument_SetOnOpenDocumentResult(wxDocument* self, int result)
    {
        static_cast<kwxDocument*>(self)->SetOnOpenDocumentResult(result != 0);
    }

    EXPORT int wxDocument_OnCreateBase(wxDocument* self, wxString* path, long flags)
    {
        return self->wxDocument::OnCreate(*path, flags);
    }

    EXPORT int wxDocument_OnOpenDocumentBase(wxDocument* self, wxString* filename)
    {
        return self->wxDocument::OnOpenDocument(*filename);
    }

    EXPORT int wxDocument_IsModifiedBase(wxDocument* self)
    {
        return self->wxDocument::IsModified();
    }

    EXPORT void wxDocument_ModifyBase(wxDocument* self, int modified)
    {
        self->wxDocument::Modify(modified != 0);
    }

    EXPORT void* wxDocument_CreateWithParent(void* pObject, wxDocument* parent)
    {
        return (void*) new kwxDocument(pObject, parent);
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

    EXPORT void kwxView_SetOnOnCreateWithData(kwxView* self, void* pFunction, void* data)
    {
        self->SetOnOnCreateWithData(pFunction, data);
    }

    EXPORT void kwxView_SetOnCreateResult(kwxView* self, int result)
    {
        self->SetOnCreateResult(result != 0);
    }

    EXPORT void kwxView_SetOnOnCloseWithData(kwxView* self, void* pFunction, void* data)
    {
        self->SetOnOnCloseWithData(pFunction, data);
    }

    EXPORT void kwxView_SetOnCloseResult(kwxView* self, int result)
    {
        self->SetOnCloseResult(result != 0);
    }

    // Qualified call: a plain virtual call would re-enter the override and recurse.
    EXPORT int kwxView_OnCloseBase(void* pObject, int deleteWindow)
    {
        return ((kwxView*) pObject)->wxView::OnClose(deleteWindow != 0);
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

    EXPORT void wxView_SetOnOnCreateWithData(wxView* self, void* pFunction, void* data)
    {
        static_cast<kwxView*>(self)->SetOnOnCreateWithData(pFunction, data);
    }

    EXPORT void wxView_SetOnCreateResult(wxView* self, int result)
    {
        static_cast<kwxView*>(self)->SetOnCreateResult(result != 0);
    }

    EXPORT void wxView_SetOnOnCloseWithData(wxView* self, void* pFunction, void* data)
    {
        static_cast<kwxView*>(self)->SetOnOnCloseWithData(pFunction, data);
    }

    EXPORT void wxView_SetOnCloseResult(wxView* self, int result)
    {
        static_cast<kwxView*>(self)->SetOnCloseResult(result != 0);
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

    EXPORT int kwxWizardPage_Create2(kwxWizardPage* self, wxWizard* parent, wxBitmapBundle* bitmap)
    {
        wxBitmapBundle bmp;
        if (bitmap)
            bmp = *bitmap;
        return self->Create(parent, bmp) ? 1 : 0;
    }

    EXPORT void kwxWizardPage_SetOnGetNext(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnGetNext(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnGetPrev(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnGetPrev(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnTransferDataFromWindow(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnTransferDataFromWindow(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnTransferDataToWindow(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnTransferDataToWindow(pFunction);
    }

    EXPORT void wxWizardPage_SetOnGetNext(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnGetNext(pFunction);
    }

    EXPORT void wxWizardPage_SetOnGetPrev(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnGetPrev(pFunction);
    }

    EXPORT int wxWizardPage_Create2(wxWizardPage* self, wxWizard* parent, wxBitmapBundle* bitmap)
    {
        wxBitmapBundle bmp;
        if (bitmap)
            bmp = *bitmap;
        return static_cast<kwxWizardPage*>(self)->Create(parent, bmp) ? 1 : 0;
    }

    EXPORT void wxWizardPage_SetOnTransferDataFromWindow(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnTransferDataFromWindow(pFunction);
    }

    EXPORT void wxWizardPage_SetOnTransferDataToWindow(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnTransferDataToWindow(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnGetNextOut(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnGetNextOut(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnGetPrevOut(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnGetPrevOut(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnTransferDataFromWindowOut(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnTransferDataFromWindowOut(pFunction);
    }

    EXPORT void kwxWizardPage_SetOnTransferDataToWindowOut(kwxWizardPage* self, void* pFunction)
    {
        self->SetOnTransferDataToWindowOut(pFunction);
    }

    EXPORT void wxWizardPage_SetOnGetNextOut(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnGetNextOut(pFunction);
    }

    EXPORT void wxWizardPage_SetOnGetPrevOut(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnGetPrevOut(pFunction);
    }

    EXPORT void wxWizardPage_SetOnTransferDataFromWindowOut(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnTransferDataFromWindowOut(pFunction);
    }

    EXPORT void wxWizardPage_SetOnTransferDataToWindowOut(wxWizardPage* self, void* pFunction)
    {
        static_cast<kwxWizardPage*>(self)->SetOnTransferDataToWindowOut(pFunction);
    }

    // kwxWizardPageSimple ----------------------------------------------------

    EXPORT void* kwxWizardPageSimple_Create(void* pObject, wxWizard* parent, wxWizardPage* prev,
                                            wxWizardPage* next, wxBitmapBundle* bitmap)
    {
        wxBitmapBundle bmp;
        if (bitmap)
        {
            bmp = *bitmap;
        }
        return (void*) new kwxWizardPageSimple(pObject, parent, prev, next, bmp);
    }

    EXPORT void kwxWizardPageSimple_Delete(kwxWizardPageSimple* self)
    {
        delete self;
    }

    EXPORT void kwxWizardPageSimple_SetOnGetNext(kwxWizardPageSimple* self, void* pFunction)
    {
        self->SetOnGetNext(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnGetPrev(kwxWizardPageSimple* self, void* pFunction)
    {
        self->SetOnGetPrev(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnTransferDataFromWindow(kwxWizardPageSimple* self,
                                                                void* pFunction)
    {
        self->SetOnTransferDataFromWindow(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnTransferDataToWindow(kwxWizardPageSimple* self,
                                                              void* pFunction)
    {
        self->SetOnTransferDataToWindow(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnGetNextOut(kwxWizardPageSimple* self, void* pFunction)
    {
        self->SetOnGetNextOut(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnGetPrevOut(kwxWizardPageSimple* self, void* pFunction)
    {
        self->SetOnGetPrevOut(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnTransferDataFromWindowOut(kwxWizardPageSimple* self,
                                                                   void* pFunction)
    {
        self->SetOnTransferDataFromWindowOut(pFunction);
    }

    EXPORT void kwxWizardPageSimple_SetOnTransferDataToWindowOut(kwxWizardPageSimple* self,
                                                                 void* pFunction)
    {
        self->SetOnTransferDataToWindowOut(pFunction);
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

    // Base implementations reachable from inside a callback.  CallBase* uses a
    // qualified call, which bypasses virtual dispatch, so a callback can log
    // and then delegate without re-entering itself.
    EXPORT void kwxPopupTransientWindow_CallBasePopup(kwxPopupTransientWindow* self,
                                                      wxWindow* focus)
    {
        self->CallBasePopup(focus);
    }

    EXPORT int kwxPopupTransientWindow_CallBaseShow(kwxPopupTransientWindow* self, int show)
    {
        return self->CallBaseShow(show != 0);
    }

    EXPORT int kwxPopupTransientWindow_CallBaseProcessLeftDown(kwxPopupTransientWindow* self,
                                                               wxMouseEvent* event)
    {
        return self->CallBaseProcessLeftDown(*event);
    }

    EXPORT void kwxPopupTransientWindow_CallBaseOnDismiss(kwxPopupTransientWindow* self)
    {
        self->CallBaseOnDismiss();
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

    // kwxDataViewModel -------------------------------------------------------

    // The returned model is reference counted like every wxDataViewModel: release it with
    // wxDataViewModel_DecRef, never with delete.
    EXPORT wxDataViewModel* wxDataViewModel_CreateDefault(void* pObject)
    {
        return new kwxDataViewModel(pObject);
    }

    EXPORT void wxDataViewModel_SetOnGetValueWithData(wxDataViewModel* self, void* pFunction,
                                                      void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnGetValueWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnSetValueWithData(wxDataViewModel* self, void* pFunction,
                                                      void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnSetValueWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnGetParentWithData(wxDataViewModel* self, void* pFunction,
                                                       void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnGetParentWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnIsContainerWithData(wxDataViewModel* self, void* pFunction,
                                                         void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnIsContainerWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnGetChildrenWithData(wxDataViewModel* self, void* pFunction,
                                                         void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnGetChildrenWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnHasValueWithData(wxDataViewModel* self, void* pFunction,
                                                      void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnHasValueWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnIsEnabledWithData(wxDataViewModel* self, void* pFunction,
                                                       void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnIsEnabledWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnHasContainerColumnsWithData(wxDataViewModel* self,
                                                                 void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnHasContainerColumnsWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnCompareWithData(wxDataViewModel* self, void* pFunction,
                                                     void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnCompareWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnHasDefaultCompareWithData(wxDataViewModel* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnHasDefaultCompareWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnResortWithData(wxDataViewModel* self, void* pFunction,
                                                    void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnResortWithData(pFunction, data);
    }

    EXPORT void wxDataViewModel_SetOnGetAttrWithData(wxDataViewModel* self, void* pFunction,
                                                     void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetOnGetAttrWithData(pFunction, data);
    }

    EXPORT unsigned int wxDataViewModel_GetPendingColumn(wxDataViewModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<kwxDataViewModel*>(self)->GetPendingColumn();
    }

    EXPORT int wxDataViewModel_GetPendingAscending(wxDataViewModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<kwxDataViewModel*>(self)->GetPendingAscending() ? 1 : 0;
    }

    EXPORT void wxDataViewModel_SetGetValueResult(wxDataViewModel* self, wxVariant* value)
    {
        if (!self || !value)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetGetValueResult(*value);
    }

    EXPORT void wxDataViewModel_SetSetValueResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetSetValueResult(result != 0);
    }

    EXPORT void wxDataViewModel_SetGetParentResult(wxDataViewModel* self, wxDataViewItem* parent)
    {
        if (!self || !parent)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetGetParentResult(*parent);
    }

    EXPORT void wxDataViewModel_SetIsContainerResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetIsContainerResult(result != 0);
    }

    EXPORT void wxDataViewModel_SetGetChildrenCountResult(wxDataViewModel* self, unsigned int count)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetGetChildrenCountResult(count);
    }

    EXPORT void wxDataViewModel_AddChildResult(wxDataViewModel* self, wxDataViewItem* item)
    {
        if (!self || !item)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->AddChildResult(*item);
    }

    EXPORT void wxDataViewModel_SetHasValueResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetHasValueResult(result != 0);
    }

    EXPORT void wxDataViewModel_SetIsEnabledResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetIsEnabledResult(result != 0);
    }

    EXPORT void wxDataViewModel_SetHasContainerColumnsResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetHasContainerColumnsResult(result != 0);
    }

    EXPORT void wxDataViewModel_SetCompareResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetCompareResult(result);
    }

    EXPORT void wxDataViewModel_SetHasDefaultCompareResult(wxDataViewModel* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetHasDefaultCompareResult(result != 0);
    }

    EXPORT void wxDataViewModel_SetGetAttrResult(wxDataViewModel* self, wxDataViewItemAttr* attr)
    {
        if (!self || !attr)
        {
            return;
        }
        static_cast<kwxDataViewModel*>(self)->SetGetAttrResult(*attr);
    }

    // kwxDataViewVirtualListModel --------------------------------------------

    // Both row models are reference counted like every wxDataViewModel: release them with
    // wxDataViewModel_DecRef, never with delete.
    EXPORT kwxDataViewVirtualListModel* wxDataViewVirtualListModel_Create(void* pObject,
                                                                          unsigned int initialSize)
    {
        return new kwxDataViewVirtualListModel(pObject, initialSize);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetOnGetValueByRowWithData(kwxDataViewVirtualListModel* self,
                                                              void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetValueByRowWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetOnSetValueByRowWithData(kwxDataViewVirtualListModel* self,
                                                              void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnSetValueByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewVirtualListModel_SetOnGetRowWithData(kwxDataViewVirtualListModel* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewVirtualListModel_SetOnGetCountWithData(kwxDataViewVirtualListModel* self,
                                                                 void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetCountWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetOnGetAttrByRowWithData(kwxDataViewVirtualListModel* self,
                                                             void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetAttrByRowWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetOnIsEnabledByRowWithData(kwxDataViewVirtualListModel* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnIsEnabledByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewVirtualListModel_SetOnCompareWithData(kwxDataViewVirtualListModel* self,
                                                                void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnCompareWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetOnHasDefaultCompareWithData(kwxDataViewVirtualListModel* self,
                                                                  void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnHasDefaultCompareWithData(pFunction, data);
    }

    EXPORT unsigned int
        wxDataViewVirtualListModel_GetPendingColumn(kwxDataViewVirtualListModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingColumn();
    }

    EXPORT unsigned int wxDataViewVirtualListModel_GetPendingRow(kwxDataViewVirtualListModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingRow();
    }

    EXPORT int wxDataViewVirtualListModel_GetPendingAscending(kwxDataViewVirtualListModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingAscending() ? 1 : 0;
    }

    EXPORT void wxDataViewVirtualListModel_SetGetValueByRowResult(kwxDataViewVirtualListModel* self,
                                                                  wxVariant* value)
    {
        if (!self || !value)
        {
            return;
        }
        self->SetGetValueByRowResult(*value);
    }

    EXPORT void wxDataViewVirtualListModel_SetSetValueByRowResult(kwxDataViewVirtualListModel* self,
                                                                  int result)
    {
        if (!self)
        {
            return;
        }
        self->SetSetValueByRowResult(result != 0);
    }

    EXPORT void wxDataViewVirtualListModel_SetGetRowResult(kwxDataViewVirtualListModel* self,
                                                           unsigned int row)
    {
        if (!self)
        {
            return;
        }
        self->SetGetRowResult(row);
    }

    EXPORT void wxDataViewVirtualListModel_SetGetCountResult(kwxDataViewVirtualListModel* self,
                                                             unsigned int count)
    {
        if (!self)
        {
            return;
        }
        self->SetGetCountResult(count);
    }

    EXPORT void wxDataViewVirtualListModel_SetGetAttrByRowResult(kwxDataViewVirtualListModel* self,
                                                                 int result)
    {
        if (!self)
        {
            return;
        }
        self->SetGetAttrByRowResult(result != 0);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetIsEnabledByRowResult(kwxDataViewVirtualListModel* self,
                                                           int result)
    {
        if (!self)
        {
            return;
        }
        self->SetIsEnabledByRowResult(result != 0);
    }

    EXPORT void wxDataViewVirtualListModel_SetCompareResult(kwxDataViewVirtualListModel* self,
                                                            int result)
    {
        if (!self)
        {
            return;
        }
        self->SetCompareResult(result);
    }

    EXPORT void
        wxDataViewVirtualListModel_SetHasDefaultCompareResult(kwxDataViewVirtualListModel* self,
                                                              int result)
    {
        if (!self)
        {
            return;
        }
        self->SetHasDefaultCompareResult(result != 0);
    }

    EXPORT void wxDataViewVirtualListModel_SetGetAttrByRowAttr(kwxDataViewVirtualListModel* self,
                                                               wxDataViewItemAttr* attr)
    {
        if (!self || !attr)
        {
            return;
        }
        self->SetGetAttrByRowAttr(*attr);
    }

    EXPORT void wxDataViewVirtualListModel_RowPrepended(kwxDataViewVirtualListModel* self)
    {
        if (!self)
        {
            return;
        }
        self->RowPrepended();
    }

    EXPORT void wxDataViewVirtualListModel_RowInserted(kwxDataViewVirtualListModel* self,
                                                       unsigned int before)
    {
        if (!self)
        {
            return;
        }
        self->RowInserted(before);
    }

    EXPORT void wxDataViewVirtualListModel_RowAppended(kwxDataViewVirtualListModel* self)
    {
        if (!self)
        {
            return;
        }
        self->RowAppended();
    }

    EXPORT void wxDataViewVirtualListModel_RowDeleted(kwxDataViewVirtualListModel* self,
                                                      unsigned int row)
    {
        if (!self)
        {
            return;
        }
        self->RowDeleted(row);
    }

    EXPORT void wxDataViewVirtualListModel_RowsDeleted(kwxDataViewVirtualListModel* self,
                                                       wxArrayInt* rows)
    {
        if (rows)
        {
            self->RowsDeleted(*rows);
        }
    }

    EXPORT void wxDataViewVirtualListModel_RowChanged(kwxDataViewVirtualListModel* self,
                                                      unsigned int row)
    {
        if (!self)
        {
            return;
        }
        self->RowChanged(row);
    }

    EXPORT void wxDataViewVirtualListModel_RowValueChanged(kwxDataViewVirtualListModel* self,
                                                           unsigned int row, unsigned int col)
    {
        if (!self)
        {
            return;
        }
        self->RowValueChanged(row, col);
    }

    EXPORT void wxDataViewVirtualListModel_Reset(kwxDataViewVirtualListModel* self,
                                                 unsigned int newSize)
    {
        if (!self)
        {
            return;
        }
        self->Reset(newSize);
    }

    EXPORT void wxDataViewVirtualListModel_GetItem(kwxDataViewVirtualListModel* self,
                                                   unsigned int row, wxDataViewItem* result)
    {
        if (!self || !result)
        {
            return;
        }
        *result = self->GetItem(row);
    }

    // kwxDataViewIndexListModel ----------------------------------------------

    EXPORT kwxDataViewIndexListModel* wxDataViewIndexListModel_Create(void* pObject,
                                                                      unsigned int initialSize)
    {
        return new kwxDataViewIndexListModel(pObject, initialSize);
    }

    EXPORT void wxDataViewIndexListModel_SetOnGetValueByRowWithData(kwxDataViewIndexListModel* self,
                                                                    void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetValueByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewIndexListModel_SetOnSetValueByRowWithData(kwxDataViewIndexListModel* self,
                                                                    void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnSetValueByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewIndexListModel_SetOnGetRowWithData(kwxDataViewIndexListModel* self,
                                                             void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewIndexListModel_SetOnGetCountWithData(kwxDataViewIndexListModel* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetCountWithData(pFunction, data);
    }

    EXPORT void wxDataViewIndexListModel_SetOnGetAttrByRowWithData(kwxDataViewIndexListModel* self,
                                                                   void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetAttrByRowWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewIndexListModel_SetOnIsEnabledByRowWithData(kwxDataViewIndexListModel* self,
                                                             void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnIsEnabledByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewIndexListModel_SetOnCompareWithData(kwxDataViewIndexListModel* self,
                                                              void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnCompareWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewIndexListModel_SetOnHasDefaultCompareWithData(kwxDataViewIndexListModel* self,
                                                                void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnHasDefaultCompareWithData(pFunction, data);
    }

    EXPORT unsigned int wxDataViewIndexListModel_GetPendingColumn(kwxDataViewIndexListModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingColumn();
    }

    EXPORT unsigned int wxDataViewIndexListModel_GetPendingRow(kwxDataViewIndexListModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingRow();
    }

    EXPORT int wxDataViewIndexListModel_GetPendingAscending(kwxDataViewIndexListModel* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingAscending() ? 1 : 0;
    }

    EXPORT void wxDataViewIndexListModel_SetGetValueByRowResult(kwxDataViewIndexListModel* self,
                                                                wxVariant* value)
    {
        if (!self || !value)
        {
            return;
        }
        self->SetGetValueByRowResult(*value);
    }

    EXPORT void wxDataViewIndexListModel_SetSetValueByRowResult(kwxDataViewIndexListModel* self,
                                                                int result)
    {
        if (!self)
        {
            return;
        }
        self->SetSetValueByRowResult(result != 0);
    }

    EXPORT void wxDataViewIndexListModel_SetGetRowResult(kwxDataViewIndexListModel* self,
                                                         unsigned int row)
    {
        if (!self)
        {
            return;
        }
        self->SetGetRowResult(row);
    }

    EXPORT void wxDataViewIndexListModel_SetGetCountResult(kwxDataViewIndexListModel* self,
                                                           unsigned int count)
    {
        if (!self)
        {
            return;
        }
        self->SetGetCountResult(count);
    }

    EXPORT void wxDataViewIndexListModel_SetGetAttrByRowResult(kwxDataViewIndexListModel* self,
                                                               int result)
    {
        if (!self)
        {
            return;
        }
        self->SetGetAttrByRowResult(result != 0);
    }

    EXPORT void wxDataViewIndexListModel_SetGetAttrByRowAttr(kwxDataViewIndexListModel* self,
                                                             wxDataViewItemAttr* attr)
    {
        if (!self || !attr)
        {
            return;
        }
        self->SetGetAttrByRowAttr(*attr);
    }

    EXPORT void wxDataViewIndexListModel_SetIsEnabledByRowResult(kwxDataViewIndexListModel* self,
                                                                 int result)
    {
        if (!self)
        {
            return;
        }
        self->SetIsEnabledByRowResult(result != 0);
    }

    EXPORT void wxDataViewIndexListModel_SetCompareResult(kwxDataViewIndexListModel* self,
                                                          int result)
    {
        if (!self)
        {
            return;
        }
        self->SetCompareResult(result);
    }

    EXPORT void wxDataViewIndexListModel_SetHasDefaultCompareResult(kwxDataViewIndexListModel* self,
                                                                    int result)
    {
        if (!self)
        {
            return;
        }
        self->SetHasDefaultCompareResult(result != 0);
    }

    EXPORT void wxDataViewIndexListModel_RowPrepended(kwxDataViewIndexListModel* self)
    {
        if (!self)
        {
            return;
        }
        self->RowPrepended();
    }

    EXPORT void wxDataViewIndexListModel_RowInserted(kwxDataViewIndexListModel* self,
                                                     unsigned int before)
    {
        if (!self)
        {
            return;
        }
        self->RowInserted(before);
    }

    EXPORT void wxDataViewIndexListModel_RowAppended(kwxDataViewIndexListModel* self)
    {
        if (!self)
        {
            return;
        }
        self->RowAppended();
    }

    EXPORT void wxDataViewIndexListModel_RowDeleted(kwxDataViewIndexListModel* self,
                                                    unsigned int row)
    {
        if (!self)
        {
            return;
        }
        self->RowDeleted(row);
    }

    EXPORT void wxDataViewIndexListModel_RowsDeleted(kwxDataViewIndexListModel* self,
                                                     wxArrayInt* rows)
    {
        if (rows)
        {
            self->RowsDeleted(*rows);
        }
    }

    EXPORT void wxDataViewIndexListModel_RowChanged(kwxDataViewIndexListModel* self,
                                                    unsigned int row)
    {
        if (!self)
        {
            return;
        }
        self->RowChanged(row);
    }

    EXPORT void wxDataViewIndexListModel_RowValueChanged(kwxDataViewIndexListModel* self,
                                                         unsigned int row, unsigned int col)
    {
        if (!self)
        {
            return;
        }
        self->RowValueChanged(row, col);
    }

    EXPORT void wxDataViewIndexListModel_Reset(kwxDataViewIndexListModel* self,
                                               unsigned int newSize)
    {
        if (!self)
        {
            return;
        }
        self->Reset(newSize);
    }

    EXPORT void wxDataViewIndexListModel_GetItem(kwxDataViewIndexListModel* self, unsigned int row,
                                                 wxDataViewItem* result)
    {
        if (!self || !result)
        {
            return;
        }
        *result = self->GetItem(row);
    }

    // kwxDataViewListStore ---------------------------------------------------

    // The returned store is the scripted subclass; with no hook installed it behaves
    // exactly like a plain wxDataViewListStore.  It is reference counted like every
    // wxDataViewModel: release it with wxDataViewModel_DecRef, never with delete.
    EXPORT wxDataViewListStore* wxDataViewListStore_Create(void* pObject)
    {
        return new kwxDataViewListStore(pObject);
    }

    EXPORT void wxDataViewListStore_SetOnHasValueWithData(wxDataViewListStore* self,
                                                          void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetOnHasValueWithData(pFunction, data);
    }

    EXPORT void wxDataViewListStore_SetOnIsEnabledByRowWithData(wxDataViewListStore* self,
                                                                void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetOnIsEnabledByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewListStore_SetOnGetAttrByRowWithData(wxDataViewListStore* self,
                                                              void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetOnGetAttrByRowWithData(pFunction, data);
    }

    EXPORT void wxDataViewListStore_SetHasValueResult(wxDataViewListStore* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetHasValueResult(result != 0);
    }

    EXPORT void wxDataViewListStore_SetIsEnabledByRowResult(wxDataViewListStore* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetIsEnabledByRowResult(result != 0);
    }

    EXPORT void wxDataViewListStore_SetGetAttrByRowResult(wxDataViewListStore* self, int result)
    {
        if (!self)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetGetAttrByRowResult(result != 0);
    }

    EXPORT void wxDataViewListStore_SetGetAttrByRowAttr(wxDataViewListStore* self,
                                                        wxDataViewItemAttr* attr)
    {
        if (!self || !attr)
        {
            return;
        }
        static_cast<kwxDataViewListStore*>(self)->SetGetAttrByRowAttr(*attr);
    }

    EXPORT unsigned int wxDataViewListStore_GetPendingRow(wxDataViewListStore* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<kwxDataViewListStore*>(self)->GetPendingRow();
    }

    EXPORT unsigned int wxDataViewListStore_GetPendingColumn(wxDataViewListStore* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<kwxDataViewListStore*>(self)->GetPendingColumn();
    }

    // Both of these are virtual, so the scripted override is reached through the base
    // pointer; they answer from the store's own storage when no hook is installed.
    EXPORT int wxDataViewListStore_IsEnabledByRow(wxDataViewListStore* self, unsigned int row,
                                                  unsigned int col)
    {
        if (!self)
        {
            return 1;
        }
        return self->IsEnabledByRow(row, col) ? 1 : 0;
    }

    EXPORT int wxDataViewListStore_GetAttrByRow(wxDataViewListStore* self, unsigned int row,
                                                unsigned int col, wxDataViewItemAttr* attr)
    {
        if (!self || !attr)
        {
            return 0;
        }
        return self->GetAttrByRow(row, col, *attr) ? 1 : 0;
    }

    // wxDataViewRenderer -----------------------------------------------------

    // These accessors work on any renderer, including the standard ones wxWidgets creates;
    // the hook setters below apply to the kwxDataViewCustomRenderer helper only.
    EXPORT void wxDataViewRenderer_SetMode(wxDataViewRenderer* self, int mode)
    {
        if (!self)
        {
            return;
        }
        self->SetMode(static_cast<wxDataViewCellMode>(mode));
    }

    EXPORT int wxDataViewRenderer_GetMode(wxDataViewRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<int>(self->GetMode());
    }

    EXPORT void wxDataViewRenderer_SetAlignment(wxDataViewRenderer* self, int align)
    {
        if (!self)
        {
            return;
        }
        self->SetAlignment(align);
    }

    EXPORT int wxDataViewRenderer_GetAlignment(wxDataViewRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetAlignment();
    }

    EXPORT void wxDataViewRenderer_EnableEllipsize(wxDataViewRenderer* self, int mode)
    {
        if (!self)
        {
            return;
        }
        self->EnableEllipsize(static_cast<wxEllipsizeMode>(mode));
    }

    EXPORT int wxDataViewRenderer_GetEllipsizeMode(wxDataViewRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<int>(self->GetEllipsizeMode());
    }

    // The variant type the renderer expects -- wx 3.3's replacement for the deprecated
    // wxDataViewModel::GetColumnType().
    EXPORT wxString* wxDataViewRenderer_GetVariantType(wxDataViewRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return new wxString(self->GetVariantType());
    }

    EXPORT int wxDataViewRenderer_GetValue(wxDataViewRenderer* self, wxVariant* value)
    {
        if (!self || !value)
        {
            return 0;
        }

        wxVariant current;
        if (!self->GetValue(current))
        {
            return 0;
        }
        *value = current;
        return 1;
    }

    EXPORT int wxDataViewRenderer_SetValue(wxDataViewRenderer* self, wxVariant* value)
    {
        if (!self || !value)
        {
            return 0;
        }
        return self->SetValue(*value) ? 1 : 0;
    }

    EXPORT void wxDataViewRenderer_SetEnabled(wxDataViewRenderer* self, int enabled)
    {
        if (!self)
        {
            return;
        }
        self->SetEnabled(enabled != 0);
    }

    EXPORT int wxDataViewRenderer_IsHighlighted(wxDataViewRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return static_cast<kwxRendererHighlightAccess*>(self)->IsHighlighted() ? 1 : 0;
    }

    EXPORT wxString* wxDataViewRenderer_GetAccessibleDescription(wxDataViewRenderer* self)
    {
        if (!self)
        {
            return new wxString();
        }
#if wxUSE_ACCESSIBILITY
        return new wxString(self->GetAccessibleDescription());
#else
        return new wxString();
#endif
    }

    // kwxDataViewCustomRenderer ----------------------------------------------

    EXPORT kwxDataViewCustomRenderer* wxDataViewCustomRenderer_Create(char* variantType, int mode,
                                                                      int align)
    {
        const wxString type = variantType ? wxString::FromUTF8(variantType) : wxString("string");
        return new kwxDataViewCustomRenderer(nullptr, type, static_cast<wxDataViewCellMode>(mode),
                                             align);
    }

    // Standard renderers -----------------------------------------------------
    //
    // These create real wxWidgets renderers and derive from wxDataViewRenderer or
    // wxDataViewCustomRenderer; the column they are handed to owns them.  Each
    // ..._CreateDefault passes the C++ defaults of its class.

    EXPORT wxDataViewTextRenderer* wxDataViewTextRenderer_CreateDefault()
    {
        return new wxDataViewTextRenderer();
    }

    EXPORT wxDataViewTextRenderer* wxDataViewTextRenderer_Create(char* variantType, int mode,
                                                                 int align)
    {
        const wxString type = variantType ? wxString::FromUTF8(variantType) :
                                            wxDataViewTextRenderer::GetDefaultType();
        return new wxDataViewTextRenderer(type, static_cast<wxDataViewCellMode>(mode), align);
    }

#if wxUSE_MARKUP
    EXPORT void wxDataViewTextRenderer_EnableMarkup(wxDataViewTextRenderer* self, int enable)
    {
        if (!self)
        {
            return;
        }
        self->EnableMarkup(enable != 0);
    }
#else
    // wxWidgets built without markup support: the call is inert.
    EXPORT void wxDataViewTextRenderer_EnableMarkup([[maybe_unused]] wxDataViewTextRenderer* self,
                                                    [[maybe_unused]] int enable)
    {
    }
#endif

    EXPORT wxDataViewToggleRenderer* wxDataViewToggleRenderer_CreateDefault()
    {
        return new wxDataViewToggleRenderer();
    }

    EXPORT wxDataViewToggleRenderer* wxDataViewToggleRenderer_Create(char* variantType, int mode,
                                                                     int align)
    {
        const wxString type = variantType ? wxString::FromUTF8(variantType) :
                                            wxDataViewToggleRenderer::GetDefaultType();
        return new wxDataViewToggleRenderer(type, static_cast<wxDataViewCellMode>(mode), align);
    }

    // ShowAsRadio() takes no argument in C++: TBool true turns the radio look on and false
    // cannot turn it back off.
    EXPORT void wxDataViewToggleRenderer_ShowAsRadio(wxDataViewToggleRenderer* self, int radio)
    {
        if (!self || radio == 0)
        {
            return;
        }
        self->ShowAsRadio();
    }

    EXPORT wxDataViewBitmapRenderer* wxDataViewBitmapRenderer_CreateDefault()
    {
        return new wxDataViewBitmapRenderer();
    }

    EXPORT wxDataViewBitmapRenderer* wxDataViewBitmapRenderer_Create(char* variantType, int mode,
                                                                     int align)
    {
        const wxString type = variantType ? wxString::FromUTF8(variantType) :
                                            wxDataViewBitmapRenderer::GetDefaultType();
        return new wxDataViewBitmapRenderer(type, static_cast<wxDataViewCellMode>(mode), align);
    }

    EXPORT wxDataViewProgressRenderer*
        wxDataViewProgressRenderer_Create(wxString* label, char* variantType, int mode, int align)
    {
        const wxString caption = label ? *label : wxString();
        const wxString type = variantType ? wxString::FromUTF8(variantType) :
                                            wxDataViewProgressRenderer::GetDefaultType();
        return new wxDataViewProgressRenderer(caption, type, static_cast<wxDataViewCellMode>(mode),
                                              align);
    }

    EXPORT wxDataViewIconTextRenderer* wxDataViewIconTextRenderer_CreateDefault()
    {
        return new wxDataViewIconTextRenderer();
    }

    EXPORT wxDataViewIconTextRenderer* wxDataViewIconTextRenderer_Create(char* variantType,
                                                                         int mode, int align)
    {
        const wxString type = variantType ? wxString::FromUTF8(variantType) :
                                            wxDataViewIconTextRenderer::GetDefaultType();
        return new wxDataViewIconTextRenderer(type, static_cast<wxDataViewCellMode>(mode), align);
    }

    EXPORT wxDataViewSpinRenderer* wxDataViewSpinRenderer_Create(int min, int max, int mode,
                                                                 int align)
    {
        return new wxDataViewSpinRenderer(min, max, static_cast<wxDataViewCellMode>(mode), align);
    }

    EXPORT wxDataViewChoiceRenderer* wxDataViewChoiceRenderer_Create(wxArrayString* choices,
                                                                     int mode, int align)
    {
        const wxArrayString values = choices ? *choices : wxArrayString();
        return new wxDataViewChoiceRenderer(values, static_cast<wxDataViewCellMode>(mode), align);
    }

    // The index is not range checked by wxWidgets; a port passes a valid one.
    EXPORT wxString* wxDataViewChoiceRenderer_GetChoice(wxDataViewChoiceRenderer* self, int index)
    {
        if (!self)
        {
            return nullptr;
        }
        return new wxString(self->GetChoice(static_cast<size_t>(index)));
    }

    // Borrowed: the renderer's own choice list.
    EXPORT wxArrayString* wxDataViewChoiceRenderer_GetChoices(wxDataViewChoiceRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return const_cast<wxArrayString*>(&self->GetChoices());
    }

    EXPORT wxDataViewChoiceByIndexRenderer*
        wxDataViewChoiceByIndexRenderer_Create(wxArrayString* choices, int mode, int align)
    {
        const wxArrayString values = choices ? *choices : wxArrayString();
        return new wxDataViewChoiceByIndexRenderer(values, static_cast<wxDataViewCellMode>(mode),
                                                   align);
    }

    // When wxUSE_DATEPICKCTRL is 0 wxDataViewDateRenderer is a typedef of the text renderer,
    // which has the same constructor shape, so this body compiles either way.
    EXPORT wxDataViewDateRenderer* wxDataViewDateRenderer_Create(char* variantType, int mode,
                                                                 int align)
    {
        const wxString type = variantType ? wxString::FromUTF8(variantType) :
                                            wxDataViewDateRenderer::GetDefaultType();
        return new wxDataViewDateRenderer(type, static_cast<wxDataViewCellMode>(mode), align);
    }

    EXPORT wxDataViewCheckIconTextRenderer* wxDataViewCheckIconTextRenderer_CreateDefault()
    {
        return new wxDataViewCheckIconTextRenderer();
    }

    EXPORT wxDataViewCheckIconTextRenderer* wxDataViewCheckIconTextRenderer_Create(int mode,
                                                                                   int align)
    {
        return new wxDataViewCheckIconTextRenderer(static_cast<wxDataViewCellMode>(mode), align);
    }

    EXPORT void
        wxDataViewCheckIconTextRenderer_Allow3rdStateForUser(wxDataViewCheckIconTextRenderer* self,
                                                             int allow)
    {
        if (!self)
        {
            return;
        }
        self->Allow3rdStateForUser(allow != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnRenderWithData(kwxDataViewCustomRenderer* self,
                                                             void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnRenderWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnGetSizeWithData(kwxDataViewCustomRenderer* self,
                                                              void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetSizeWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnSetValueWithData(kwxDataViewCustomRenderer* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnSetValueWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnGetValueWithData(kwxDataViewCustomRenderer* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetValueWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnActivateCellWithData(kwxDataViewCustomRenderer* self,
                                                                   void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnActivateCellWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnActivateWithData(kwxDataViewCustomRenderer* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnActivateWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnLeftClickWithData(kwxDataViewCustomRenderer* self,
                                                                void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnLeftClickWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnStartDragWithData(kwxDataViewCustomRenderer* self,
                                                                void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnStartDragWithData(pFunction, data);
    }

    EXPORT void
        wxDataViewCustomRenderer_SetOnCreateEditorCtrlWithData(kwxDataViewCustomRenderer* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnCreateEditorCtrlWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnGetValueFromEditorCtrlWithData(
        kwxDataViewCustomRenderer* self, void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetValueFromEditorCtrlWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnValidateWithData(kwxDataViewCustomRenderer* self,
                                                               void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnValidateWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnHasEditorCtrlWithData(kwxDataViewCustomRenderer* self,
                                                                    void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnHasEditorCtrlWithData(pFunction, data);
    }

    EXPORT void wxDataViewCustomRenderer_SetOnGetAccessibleDescriptionWithData(
        kwxDataViewCustomRenderer* self, void* pFunction, void* data)
    {
        if (!self)
        {
            return;
        }
        self->SetOnGetAccessibleDescriptionWithData(pFunction, data);
    }

    EXPORT wxDC* wxDataViewCustomRenderer_GetRenderDC(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return self->GetRenderDC();
    }

    EXPORT void wxDataViewCustomRenderer_GetRenderRect(kwxDataViewCustomRenderer* self, int* x,
                                                       int* y, int* width, int* height)
    {
        if (!self)
        {
            return;
        }

        const wxRect rect = self->GetRenderRect();
        if (x)
        {
            *x = rect.GetX();
        }
        if (y)
        {
            *y = rect.GetY();
        }
        if (width)
        {
            *width = rect.GetWidth();
        }
        if (height)
        {
            *height = rect.GetHeight();
        }
    }

    EXPORT int wxDataViewCustomRenderer_GetRenderState(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetRenderState();
    }

    // Returns a new wxVariant the caller must free.
    EXPORT wxVariant* wxDataViewCustomRenderer_GetCurrentValue(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return new wxVariant(self->GetCurrentValue());
    }

    EXPORT wxRect* wxDataViewCustomRenderer_GetEditorRect(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return new wxRect(self->GetEditorRect());
    }

    EXPORT wxWindow* wxDataViewCustomRenderer_GetEditorParent(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return self->GetEditorParent();
    }

    EXPORT wxWindow* wxDataViewCustomRenderer_GetEditorCtrl(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return self->GetEditorCtrl();
    }

    EXPORT unsigned int wxDataViewCustomRenderer_GetPendingColumn(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingColumn();
    }

    // Borrowed: the event belongs to wxWidgets and outlives only the ActivateCell callback
    // that received it.
    EXPORT wxMouseEvent*
        wxDataViewCustomRenderer_GetActivateCellMouseEvent(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return const_cast<wxMouseEvent*>(self->GetActivateCellMouseEvent());
    }

    EXPORT int wxDataViewCustomRenderer_GetPendingCursorX(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingCursorX();
    }

    EXPORT int wxDataViewCustomRenderer_GetPendingCursorY(kwxDataViewCustomRenderer* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetPendingCursorY();
    }

    // RenderText()/GetTextExtent() receive their text as a UTF-8 buffer: the declaration in
    // include/kwx_hook_exports.h spells parameter A as TString (== char*), so it is converted
    // with wxString::FromUTF8 here and must never be taken as a wxString*.
    EXPORT void wxDataViewCustomRenderer_RenderText(kwxDataViewCustomRenderer* self,
                                                    const char* text, int xoffset, int cell_x,
                                                    int cell_y, int cell_width, int cell_height,
                                                    wxDC* dc, int state)
    {
        if (!self)
        {
            return;
        }
        self->CallRenderText(text ? wxString::FromUTF8(text) : wxString(), xoffset,
                             wxRect(cell_x, cell_y, cell_width, cell_height), dc, state);
    }

    // Both out-parameters are optional; the caller passes int[1] buffers.
    EXPORT void wxDataViewCustomRenderer_GetTextExtent(kwxDataViewCustomRenderer* self,
                                                       const char* text, int* width, int* height)
    {
        if (!self)
        {
            return;
        }
        const wxSize size = self->CallGetTextExtent(text ? wxString::FromUTF8(text) : wxString());
        if (width)
        {
            *width = size.x;
        }
        if (height)
        {
            *height = size.y;
        }
    }

    EXPORT void wxDataViewCustomRenderer_SetRenderResult(kwxDataViewCustomRenderer* self,
                                                         int result)
    {
        if (!self)
        {
            return;
        }
        self->SetRenderResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetGetSizeResult(kwxDataViewCustomRenderer* self,
                                                          int width, int height)
    {
        if (!self)
        {
            return;
        }
        self->SetGetSizeResult(wxSize(width, height));
    }

    EXPORT void wxDataViewCustomRenderer_SetGetValueResult(kwxDataViewCustomRenderer* self,
                                                           wxVariant* value)
    {
        if (!self || !value)
        {
            return;
        }
        self->SetGetValueResult(*value);
    }

    EXPORT void wxDataViewCustomRenderer_SetSetValueResult(kwxDataViewCustomRenderer* self,
                                                           int result)
    {
        if (!self)
        {
            return;
        }
        self->SetSetValueResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetActivateCellResult(kwxDataViewCustomRenderer* self,
                                                               int result)
    {
        if (!self)
        {
            return;
        }
        self->SetActivateCellResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetActivateResult(kwxDataViewCustomRenderer* self,
                                                           int result)
    {
        if (!self)
        {
            return;
        }
        self->SetActivateResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetLeftClickResult(kwxDataViewCustomRenderer* self,
                                                            int result)
    {
        if (!self)
        {
            return;
        }
        self->SetLeftClickResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetStartDragResult(kwxDataViewCustomRenderer* self,
                                                            int result)
    {
        if (!self)
        {
            return;
        }
        self->SetStartDragResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetCreateEditorCtrlResult(kwxDataViewCustomRenderer* self,
                                                                   wxWindow* editor)
    {
        if (!self)
        {
            return;
        }
        self->SetCreateEditorCtrlResult(editor);
    }

    EXPORT void
        wxDataViewCustomRenderer_SetGetValueFromEditorCtrlResult(kwxDataViewCustomRenderer* self,
                                                                 int result)
    {
        if (!self)
        {
            return;
        }
        self->SetGetValueFromEditorCtrlResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetValidateResult(kwxDataViewCustomRenderer* self,
                                                           int result)
    {
        if (!self)
        {
            return;
        }
        self->SetValidateResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetHasEditorCtrlResult(kwxDataViewCustomRenderer* self,
                                                                int result)
    {
        if (!self)
        {
            return;
        }
        self->SetHasEditorCtrlResult(result != 0);
    }

    EXPORT void wxDataViewCustomRenderer_SetAccessibleDescription(kwxDataViewCustomRenderer* self,
                                                                  wxString* description)
    {
        if (!self)
        {
            return;
        }
        self->SetAccessibleDescription(description ? *description : wxString());
    }

    EXPORT void
        wxDataViewCustomRenderer_SetGetValueFromEditorCtrlValue(kwxDataViewCustomRenderer* self,
                                                                wxVariant* value)
    {
        if (!self || !value)
        {
            return;
        }
        self->SetGetValueFromEditorCtrlValue(*value);
    }

    // wxDataViewColumn -------------------------------------------------------

    // The column takes ownership of the renderer, so the caller must not delete it after
    // this call.  align is a wxALIGN_* value or wxDVR_DEFAULT_ALIGNMENT; flags is a
    // combination of wxDATAVIEW_COL_*.
    EXPORT wxDataViewColumn* wxDataViewColumn_CreateWithRenderer(wxString* title,
                                                                 wxDataViewRenderer* renderer,
                                                                 unsigned int modelColumn,
                                                                 int width, int align, int flags)
    {
        if (!renderer)
        {
            return nullptr;
        }

        const wxString label = title ? *title : wxString();
        return new wxDataViewColumn(label, renderer, modelColumn, width,
                                    static_cast<wxAlignment>(align), flags);
    }
}
