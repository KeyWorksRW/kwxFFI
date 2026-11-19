#pragma once

// kwx<Base> override hooks — callback plumbing for wxWidgets protected virtuals.
//
// wxWidgets dispatches application-level customisation through protected
// virtuals that a foreign language cannot override (an FFI caller has no
// derived C++ class).  Each class below derives from the wxWidgets base, keeps
// the foreign object pointer in a void* field, keeps one void* callback per
// virtual, and forwards the virtual to that callback.  This is the same shape
// as kwxComboCtrl in include/kwx_helper_combo.h and kwxAccessible in
// include/kwx_helper_accessible.h:
//
//   * constructor takes void* pObject,
//   * setters take void* pFunction and cast it to the typedef,
//   * every override is guarded by a null check so an unset callback keeps the
//     wxWidgets default behaviour.
//
// The exported kwx<Base>_* / <Base>_* functions are declared in the
// TClassDef/TClassDefExtend blocks at the bottom of this header; kwxgen
// attributes them to the class named in the block header, so the block header
// and the function prefix always agree.
//
// The application family comes first because kwxFFI has no application object
// at all.  A callback object is not the global application object: creating one
// does not install it into wxWidgets.  Only wxApp_GetApp() returns the instance
// the library itself created.
//
// CAUTION: wxAppConsoleBase's own constructor sets the process-wide application
// singleton (wxWidgets appbase.cpp:147) and its destructor clears it (:162).
// Constructing a kwxAppConsole or kwxApp therefore replaces wxApp_GetApp() for
// as long as it lives, and destroying it leaves that accessor returning null.
// An application port owns exactly one application object for the process
// lifetime; create it once and destroy it at shutdown.

#include "kwx_types.h"

#include <wx/addremovectrl.h>
#include <wx/app.h>
#include <wx/apptrait.h>
#include <wx/aui/tabmdi.h>
#include <wx/cmdline.h>
#include <wx/dataview.h>
#include <wx/debugrpt.h>
#include <wx/dialog.h>
#include <wx/docview.h>
#include <wx/dvrenderers.h>
#include <wx/event.h>
#include <wx/filesys.h>
#include <wx/html/htmlpars.h>
#include <wx/html/winpars.h>
#include <wx/htmllbox.h>
#include <wx/log.h>
#include <wx/modalhook.h>
#include <wx/nativewin.h>
#include <wx/object.h>
#include <wx/panel.h>
#include <wx/preferences.h>
#include <wx/renderer.h>
#include <wx/string.h>
#include <wx/textcompleter.h>
#include <wx/timer.h>
#include <wx/validate.h>
#include <wx/variant.h>
#include <wx/vscroll.h>
#include <wx/window.h>
#include <wx/wizard.h>

#include <string>

// ---------------------------------------------------------------------------
// wxAppConsole callbacks
// ---------------------------------------------------------------------------

// parser is a wxCmdLineParser*.  Return non-zero to continue, zero to abort.
typedef int (*kwxAppConsoleParserFunc)(void* pObject, void* parser);

// Return the exit code.
typedef int (*kwxAppConsoleExitFunc)(void* pObject);

// loop is a wxEventLoopBase*, only valid for the duration of the call.
typedef void (*kwxAppConsoleLoopFunc)(void* pObject, void* loop);

// file/func/cond/msg are UTF-8 strings carrying the assert location and text;
// any of them may be null when wxWidgets did not supply it.
typedef void (*kwxAppConsoleAssertFunc)(void* pObject, void* file, int line, void* func, void* cond,
                                        void* msg);

// Return non-zero to keep running (OnExceptionInMainLoop) or to report that the
// exception was stored (StoreCurrentException).
typedef int (*kwxAppConsoleBoolFunc)(void* pObject);

// Return a wxAppTraits*; the caller takes ownership.
typedef void* (*kwxAppConsoleTraitsFunc)(void* pObject);

class kwxAppConsole : public wxAppConsole
{
private:
    void* m_object;
    kwxAppConsoleParserFunc m_on_cmd_line_parsed_func;
    kwxAppConsoleParserFunc m_on_init_cmd_line_func;
    kwxAppConsoleExitFunc m_on_exit_func;
    kwxAppConsoleExitFunc m_on_run_func;
    kwxAppConsoleAssertFunc m_on_assert_failure_func;
    kwxAppConsoleLoopFunc m_on_event_loop_enter_func;
    kwxAppConsoleBoolFunc m_on_exception_in_main_loop_func;
    kwxAppConsoleBoolFunc m_store_current_exception_func;
    kwxAppConsoleBoolFunc m_on_fatal_exception_func;
    kwxAppConsoleBoolFunc m_on_unhandled_exception_func;
    kwxAppConsoleBoolFunc m_rethrow_stored_exception_func;
    kwxAppConsoleTraitsFunc m_create_traits_func;

public:
    explicit kwxAppConsole(void* pObject);

    void SetOnOnCmdLineParsed(void* pFunction)
    {
        m_on_cmd_line_parsed_func = (kwxAppConsoleParserFunc) pFunction;
    }
    void SetOnOnInitCmdLine(void* pFunction)
    {
        m_on_init_cmd_line_func = (kwxAppConsoleParserFunc) pFunction;
    }
    void SetOnOnExit(void* pFunction) { m_on_exit_func = (kwxAppConsoleExitFunc) pFunction; }
    void SetOnOnRun(void* pFunction) { m_on_run_func = (kwxAppConsoleExitFunc) pFunction; }
    void SetOnOnAssertFailure(void* pFunction)
    {
        m_on_assert_failure_func = (kwxAppConsoleAssertFunc) pFunction;
    }
    void SetOnOnEventLoopEnter(void* pFunction)
    {
        m_on_event_loop_enter_func = (kwxAppConsoleLoopFunc) pFunction;
    }
    void SetOnOnExceptionInMainLoop(void* pFunction)
    {
        m_on_exception_in_main_loop_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnStoreCurrentException(void* pFunction)
    {
        m_store_current_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnOnFatalException(void* pFunction)
    {
        m_on_fatal_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnOnUnhandledException(void* pFunction)
    {
        m_on_unhandled_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnRethrowStoredException(void* pFunction)
    {
        m_rethrow_stored_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnCreateTraits(void* pFunction)
    {
        m_create_traits_func = (kwxAppConsoleTraitsFunc) pFunction;
    }

protected:
    bool OnCmdLineParsed(wxCmdLineParser& parser) override;
    void OnInitCmdLine(wxCmdLineParser& parser) override;
    int OnExit() override;
    int OnRun() override;
    void OnAssertFailure(const wxChar* file, int line, const wxChar* func, const wxChar* cond,
                         const wxChar* msg) override;
    void OnEventLoopEnter(wxEventLoopBase* loop) override;
    void OnFatalException() override;
    // The exception hooks exist only when wxWidgets is built with
    // wxUSE_EXCEPTIONS, which every kwxFFI build is (the library targets MSW
    // with exceptions on).  They are declared unconditionally because
    // tests/checks/guard_lint.py rejects a declaration under a feature guard
    // that is not in its allowlist.
    void OnUnhandledException() override;
    bool OnExceptionInMainLoop() override;
    bool StoreCurrentException() override;
    void RethrowStoredException() override;
    wxAppTraits* CreateTraits() override;
};

// ---------------------------------------------------------------------------
// wxApp callbacks
// ---------------------------------------------------------------------------

// event is a wxEvent*.  FilterEvent returns -1 to pass the event on, or one of
// the wxEventFilter::EventFilter values to stop or skip it.
typedef int (*kwxAppEventFunc)(void* pObject, void* event);

// Return a wxClassInfo*; the caller does not own it.  Shared by the wxApp and
// wxObject hooks, which both override GetClassInfo().
typedef void* (*kwxObjectClassInfoFunc)(void* pObject);

class kwxApp : public wxApp
{
private:
    void* m_object;
    kwxAppConsoleParserFunc m_on_cmd_line_parsed_func;
    kwxAppConsoleParserFunc m_on_init_cmd_line_func;
    kwxAppConsoleExitFunc m_on_exit_func;
    kwxAppEventFunc m_filter_event_func;
    kwxObjectClassInfoFunc m_get_class_info_func;
    kwxAppConsoleAssertFunc m_on_assert_failure_func;
    kwxAppConsoleTraitsFunc m_create_traits_func;
    kwxAppConsoleBoolFunc m_on_fatal_exception_func;
    kwxAppConsoleBoolFunc m_on_unhandled_exception_func;
    kwxAppConsoleBoolFunc m_store_current_exception_func;
    kwxAppConsoleBoolFunc m_on_exception_in_main_loop_func;
    kwxAppConsoleBoolFunc m_rethrow_stored_exception_func;

public:
    explicit kwxApp(void* pObject);

    void SetOnOnCmdLineParsed(void* pFunction)
    {
        m_on_cmd_line_parsed_func = (kwxAppConsoleParserFunc) pFunction;
    }
    void SetOnOnInitCmdLine(void* pFunction)
    {
        m_on_init_cmd_line_func = (kwxAppConsoleParserFunc) pFunction;
    }
    void SetOnOnExit(void* pFunction) { m_on_exit_func = (kwxAppConsoleExitFunc) pFunction; }
    void SetOnFilterEvent(void* pFunction) { m_filter_event_func = (kwxAppEventFunc) pFunction; }
    void SetOnGetClassInfo(void* pFunction)
    {
        m_get_class_info_func = (kwxObjectClassInfoFunc) pFunction;
    }
    void SetOnOnAssertFailure(void* pFunction)
    {
        m_on_assert_failure_func = (kwxAppConsoleAssertFunc) pFunction;
    }
    void SetOnCreateTraits(void* pFunction)
    {
        m_create_traits_func = (kwxAppConsoleTraitsFunc) pFunction;
    }
    void SetOnOnFatalException(void* pFunction)
    {
        m_on_fatal_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnOnUnhandledException(void* pFunction)
    {
        m_on_unhandled_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnStoreCurrentException(void* pFunction)
    {
        m_store_current_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnOnExceptionInMainLoop(void* pFunction)
    {
        m_on_exception_in_main_loop_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnRethrowStoredException(void* pFunction)
    {
        m_rethrow_stored_exception_func = (kwxAppConsoleBoolFunc) pFunction;
    }

protected:
    bool OnCmdLineParsed(wxCmdLineParser& parser) override;
    void OnInitCmdLine(wxCmdLineParser& parser) override;
    int OnExit() override;
    int FilterEvent(wxEvent& event) override;
    wxClassInfo* GetClassInfo() const override;
    void OnAssertFailure(const wxChar* file, int line, const wxChar* func, const wxChar* cond,
                         const wxChar* msg) override;
    wxAppTraits* CreateTraits() override;
    // A wxApp has the same exception hooks as wxAppConsole, so a port never has to
    // install them through the wxAppConsole base-name aliases.
    void OnFatalException() override;
    void OnUnhandledException() override;
    bool OnExceptionInMainLoop() override;
    bool StoreCurrentException() override;
    void RethrowStoredException() override;
};

// ---------------------------------------------------------------------------
// wxObject callbacks
// ---------------------------------------------------------------------------

class kwxObject : public wxObject
{
private:
    void* m_object;
    kwxObjectClassInfoFunc m_get_class_info_func;

public:
    explicit kwxObject(void* pObject);

    void SetOnGetClassInfo(void* pFunction)
    {
        m_get_class_info_func = (kwxObjectClassInfoFunc) pFunction;
    }

    wxClassInfo* GetClassInfo() const override;
};

// ---------------------------------------------------------------------------
// wxDebugReportUpload callbacks
// ---------------------------------------------------------------------------

// reply is a wxArrayString*, valid only for the duration of the call; the
// callback must not keep the pointer.
typedef void (*kwxDebugReportUploadReplyFunc)(void* pObject, void* reply);

class kwxDebugReportUpload : public wxDebugReportUpload
{
private:
    void* m_object;
    kwxDebugReportUploadReplyFunc m_on_server_reply_func;
    bool m_server_reply_result;

public:
    kwxDebugReportUpload(void* pObject, const wxString& url, const wxString& input,
                         const wxString& action);

    void SetOnOnServerReply(void* pFunction)
    {
        m_on_server_reply_func = (kwxDebugReportUploadReplyFunc) pFunction;
    }
    // Publish the hook's answer: non-zero keeps the report, zero reports failure.
    void SetOnServerReplyResult(bool result) { m_server_reply_result = result; }

protected:
    bool OnServerReply(const wxArrayString& reply) override;
};

// ---------------------------------------------------------------------------
// wxEvtHandler callbacks
// ---------------------------------------------------------------------------

class kwxEvtHandler : public wxEvtHandler
{
private:
    void* m_object;
    kwxAppEventFunc m_process_event_func;

public:
    explicit kwxEvtHandler(void* pObject);

    void SetOnProcessEvent(void* pFunction) { m_process_event_func = (kwxAppEventFunc) pFunction; }

    bool ProcessEvent(wxEvent& event) override;
};

// ---------------------------------------------------------------------------
// wxPanel callbacks
// ---------------------------------------------------------------------------

// Return the best client size in pixels; the callback receives two int* outputs
// so no wxSize crosses the boundary.
typedef void (*kwxPanelBestSizeFunc)(void* pObject, int* width, int* height);

// dx/dy are the scroll deltas and rect a const wxRect* (null when unset).
typedef void (*kwxPanelScrollFunc)(void* pObject, int dx, int dy, void* rect);

class kwxPanel : public wxPanel
{
private:
    void* m_object;
    kwxAppConsoleBoolFunc m_transfer_data_from_window_func;
    kwxAppConsoleBoolFunc m_transfer_data_to_window_func;
    kwxPanelBestSizeFunc m_do_get_best_client_size_func;
    kwxPanelScrollFunc m_scroll_window_func;

public:
    kwxPanel(void* pObject, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
             long style = wxTAB_TRAVERSAL | wxNO_BORDER);

    void SetOnTransferDataFromWindow(void* pFunction)
    {
        m_transfer_data_from_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnTransferDataToWindow(void* pFunction)
    {
        m_transfer_data_to_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnDoGetBestClientSize(void* pFunction)
    {
        m_do_get_best_client_size_func = (kwxPanelBestSizeFunc) pFunction;
    }
    void SetOnScrollWindow(void* pFunction)
    {
        m_scroll_window_func = (kwxPanelScrollFunc) pFunction;
    }

    bool TransferDataFromWindow() override;
    bool TransferDataToWindow() override;
    wxSize DoGetBestClientSize() const override;
    void ScrollWindow(int dx, int dy, const wxRect* rect = nullptr) override;
};

// ---------------------------------------------------------------------------
// wxDialog callbacks
// ---------------------------------------------------------------------------

// wxDialog's own TransferDataFromWindow / TransferDataToWindow walk the child
// windows, which is what runs the child validators.  A hook replaces that, so a
// port that needs the standard transfer must call the chaining export first
// (a plain virtual call would re-enter the hook).  With no hook installed the
// helper forwards to wxDialog, i.e. it behaves exactly like a plain dialog.
class kwxDialog : public wxDialog
{
private:
    void* m_object;
    kwxAppConsoleBoolFunc m_transfer_data_from_window_func;
    kwxAppConsoleBoolFunc m_transfer_data_to_window_func;

public:
    kwxDialog(void* pObject, wxWindow* parent, wxWindowID id, const wxString& title,
              const wxPoint& pos, const wxSize& size, long style = wxDEFAULT_DIALOG_STYLE);

    void SetOnTransferDataFromWindow(void* pFunction)
    {
        m_transfer_data_from_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnTransferDataToWindow(void* pFunction)
    {
        m_transfer_data_to_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }

    bool TransferDataFromWindow() override;
    bool TransferDataToWindow() override;
};

// ---------------------------------------------------------------------------
// wxVarHScrollHelper / wxVarVScrollHelper callbacks
// ---------------------------------------------------------------------------

// item is the column/row index.  Return that unit's size in pixels; a negative
// value means "no callback", in which case the wxWidgets value is used.
typedef int (*kwxVarScrollSizeFunc)(void* pObject, size_t item);

class kwxVarHScrollHelper : public wxVarHScrollHelper
{
private:
    void* m_object;
    kwxVarScrollSizeFunc m_on_get_column_width_func;

public:
    kwxVarHScrollHelper(wxWindow* winToScroll, void* pObject);

    void SetOnOnGetColumnWidth(void* pFunction)
    {
        m_on_get_column_width_func = (kwxVarScrollSizeFunc) pFunction;
    }

protected:
    wxCoord OnGetColumnWidth(size_t n) const override;
};

class kwxVarVScrollHelper : public wxVarVScrollHelper
{
private:
    void* m_object;
    kwxVarScrollSizeFunc m_on_get_row_height_func;

public:
    kwxVarVScrollHelper(wxWindow* winToScroll, void* pObject);

    void SetOnOnGetRowHeight(void* pFunction)
    {
        m_on_get_row_height_func = (kwxVarScrollSizeFunc) pFunction;
    }

protected:
    wxCoord OnGetRowHeight(size_t n) const override;
};

// ---------------------------------------------------------------------------
// wxTimer callbacks
// ---------------------------------------------------------------------------

// The timer callback takes no arguments; start the timer with wxTimer_Start.
typedef void (*kwxTimerFunc)(void* pObject);

class kwxTimer : public wxTimer
{
private:
    void* m_object;
    kwxTimerFunc m_notify_func;

public:
    explicit kwxTimer(void* pObject);

    void SetOnNotify(void* pFunction) { m_notify_func = (kwxTimerFunc) pFunction; }

    void Notify() override;
};

// ---------------------------------------------------------------------------
// wxValidator callbacks
// ---------------------------------------------------------------------------

// Return a new wxObject; the caller takes ownership.  The callback receives no
// argument beyond the hook object because Clone() has no parameters.
typedef void* (*kwxValidatorCloneFunc)(void* pObject);

// parent is a wxWindow*.  Return non-zero to accept the value.
typedef int (*kwxValidatorValidateFunc)(void* pObject, void* parent);

class kwxValidator : public wxValidator
{
private:
    void* m_object;
    kwxValidatorCloneFunc m_clone_func;
    kwxValidatorValidateFunc m_validate_func;
    kwxAppConsoleBoolFunc m_transfer_from_window_func;
    kwxAppConsoleBoolFunc m_transfer_to_window_func;

public:
    explicit kwxValidator(void* pObject);

    void SetOnClone(void* pFunction) { m_clone_func = (kwxValidatorCloneFunc) pFunction; }
    void SetOnValidate(void* pFunction) { m_validate_func = (kwxValidatorValidateFunc) pFunction; }
    void SetOnTransferFromWindow(void* pFunction)
    {
        m_transfer_from_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnTransferToWindow(void* pFunction)
    {
        m_transfer_to_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }

    wxObject* Clone() const override;
    bool Validate(wxWindow* parent) override;
    bool TransferFromWindow() override;
    bool TransferToWindow() override;
};

// ---------------------------------------------------------------------------
// wxPreferencesPage callbacks
// ---------------------------------------------------------------------------

// Return a UTF-8 page name.  The string is copied before the callback returns.
// The void-only callback ABI cannot return a value, so the callback publishes
// its name with SetNameResult() before returning.
typedef void (*kwxPreferencesPageNameFunc)(void* pObject);

// parent is a wxWindow*.  The callback publishes the wxWindow* it created with
// SetCreateWindowResult(); the page takes ownership of that window.
typedef void (*kwxPreferencesPageWindowFunc)(void* pObject, void* parent);

// The callback publishes a wxBitmapBundle* allocated with new via
// SetGetIconResult(); the page copies it and deletes the original.
typedef void (*kwxPreferencesPageIconFunc)(void* pObject);

class kwxPreferencesPage : public wxPreferencesPage
{
private:
    void* m_object;
    kwxPreferencesPageNameFunc m_get_name_func;
    kwxPreferencesPageWindowFunc m_create_window_func;
    kwxPreferencesPageIconFunc m_get_icon_func;

    // Scratch results the callbacks fill in; cleared before each callback runs.
    mutable wxString m_result_name;
    mutable wxWindow* m_result_window;
    mutable wxBitmapBundle* m_result_icon;

public:
    explicit kwxPreferencesPage(void* pObject);

    void SetOnGetName(void* pFunction) { m_get_name_func = (kwxPreferencesPageNameFunc) pFunction; }
    void SetOnCreateWindow(void* pFunction)
    {
        m_create_window_func = (kwxPreferencesPageWindowFunc) pFunction;
    }
    void SetOnGetIcon(void* pFunction) { m_get_icon_func = (kwxPreferencesPageIconFunc) pFunction; }

    // Store the value a callback wants GetName()/CreateWindow()/GetIcon() to
    // return.  Only the callback whose override is running should call these.
    void SetNameResult(const char* name) { m_result_name = name ? wxString(name) : wxString(); }
    void SetCreateWindowResult(wxWindow* window) { m_result_window = window; }
    void SetGetIconResult(wxBitmapBundle* bundle) { m_result_icon = bundle; }

    wxString GetName() const override;
    wxWindow* CreateWindow(wxWindow* parent) override;
    wxBitmapBundle GetIcon() const override;
};

// ---------------------------------------------------------------------------
// wxStockPreferencesPage callbacks
//
// wxStockPreferencesPage supplies the stock "General"/"Advanced" page names but
// leaves CreateWindow() pure, so it cannot be instantiated on its own.  This
// helper adds a callback-driven CreateWindow() to it, which is what a port needs
// to use the stock page directly.
//
// The helper deliberately does NOT derive from kwxPreferencesPage: it needs
// wxStockPreferencesPage::GetName(), not the callback-driven one.  The FFI block
// for wxStockPreferencesPage is therefore declared without a parent, so a
// generated binding never inherits the kwxPreferencesPage setters, which
// down-cast their receiver and would be undefined behaviour on this object.
// ---------------------------------------------------------------------------

// m_object is the per-page callback context: it is handed to every CreateWindow
// callback, so a port reaches its own state directly instead of publishing it
// through a global or static.
class kwxStockPreferencesPage : public wxStockPreferencesPage
{
private:
    void* m_object;
    kwxPreferencesPageWindowFunc m_create_window_func;
    wxWindow* m_result_window;

public:
    // pObject is the callback state pointer handed to every CreateWindow
    // callback.  The kind-only form keeps the previous behaviour with a null
    // state pointer.
    explicit kwxStockPreferencesPage(Kind kind, void* pObject = nullptr) :
        wxStockPreferencesPage(kind)
    {
        m_object = pObject;
        m_create_window_func = nullptr;
        m_result_window = nullptr;
    }

    void SetOnCreateWindow(void* pFunction)
    {
        m_create_window_func = (kwxPreferencesPageWindowFunc) pFunction;
    }

    void SetCreateWindowResult(wxWindow* window) { m_result_window = window; }

    wxWindow* CreateWindow(wxWindow* parent) override;
};

// ---------------------------------------------------------------------------
// wxHtmlListBox callbacks
// ---------------------------------------------------------------------------

// Return the HTML body (without <html>) for item n, as a UTF-8 string.  The
// string is copied before the callback returns, so it may point at transient
// storage.
typedef void* (*kwxHtmlListBoxItemFunc)(void* pObject, size_t n);

// colFg is a const wxColour*.  Return a wxColour* allocated with new, or null to
// keep the wxWidgets default selection colour; this class deletes whatever it
// receives.
typedef void* (*kwxHtmlListBoxColourFunc)(void* pObject, void* colFg);

// OnGetItem() is the only pure virtual left on wxHtmlListBox, so overriding it
// (plus GetSelectedTextColour) makes this class concrete.
class kwxHtmlListBox : public wxHtmlListBox
{
private:
    void* m_object;
    kwxHtmlListBoxItemFunc m_on_get_item_func;
    kwxHtmlListBoxColourFunc m_get_selected_text_colour_func;

public:
    kwxHtmlListBox(void* pObject, wxWindow* parent, wxWindowID id, const wxPoint& pos,
                   const wxSize& size, long style);

    void SetOnOnGetItem(void* pFunction)
    {
        m_on_get_item_func = (kwxHtmlListBoxItemFunc) pFunction;
    }
    void SetOnGetSelectedTextColour(void* pFunction)
    {
        m_get_selected_text_colour_func = (kwxHtmlListBoxColourFunc) pFunction;
    }

protected:
    wxString OnGetItem(size_t n) const override;
    wxColour GetSelectedTextColour(const wxColour& colFg) const override;
};

// ---------------------------------------------------------------------------
// wxVListBox callbacks
// ---------------------------------------------------------------------------

// dc is a wxDC* and rect a wxRect*; both are only valid for the duration of the
// call.  n is the item index.
typedef void (*kwxVListBoxDrawFunc)(void* pObject, void* dc, void* rect, size_t n);

// Return the item height in pixels; return -1 for the wxWidgets default.
typedef int (*kwxVListBoxMeasureFunc)(void* pObject, size_t n);

// OnDrawItem() and OnMeasureItem() are pure virtual on wxVListBox, so overriding
// both is what makes the class concrete.  OnDrawSeparator() is optional and
// keeps the wxWidgets behaviour when unset.
class kwxVListBox : public wxVListBox
{
private:
    void* m_object;
    kwxVListBoxDrawFunc m_on_draw_item_func;
    kwxVListBoxDrawFunc m_on_draw_separator_func;
    kwxVListBoxMeasureFunc m_on_measure_item_func;

public:
    kwxVListBox(void* pObject, wxWindow* parent, wxWindowID id, const wxPoint& pos,
                const wxSize& size, long style);

    void SetOnOnDrawItem(void* pFunction) { m_on_draw_item_func = (kwxVListBoxDrawFunc) pFunction; }
    void SetOnOnDrawSeparator(void* pFunction)
    {
        m_on_draw_separator_func = (kwxVListBoxDrawFunc) pFunction;
    }
    void SetOnOnMeasureItem(void* pFunction)
    {
        m_on_measure_item_func = (kwxVListBoxMeasureFunc) pFunction;
    }

protected:
    void OnDrawItem(wxDC& dc, const wxRect& rect, size_t n) const override;
    void OnDrawSeparator(wxDC& dc, wxRect& rect, size_t n) const override;
    wxCoord OnMeasureItem(size_t n) const override;
};

// ---------------------------------------------------------------------------
// wxRendererNative callbacks
// ---------------------------------------------------------------------------

// win is a wxWindow*, dc a wxDC* and rect a const wxRect*, all valid only for
// the duration of the call.  Return the optimal width for the label contents.
typedef int (*kwxRendererHeaderButtonFunc)(void* pObject, void* win, void* dc, void* rect,
                                           int flags, int sortArrow, void* headerParams);

// wxRendererVersion is a {version, age} pair, so it crosses as two ints.
typedef void (*kwxRendererVersionFunc)(void* pObject, int* version, int* age);

// wxRendererNative has 28 pure virtuals, so deriving from it would mean writing
// 28 pass-throughs.  wxDelegateRendererNative already implements all of them by
// forwarding to a delegate (wx/renderer.h:431-604) and only GetVersion() and
// DrawHeaderButton() are replaced here, which is the same shape the render
// sample itself uses (MyDllRenderer : public wxDelegateRendererNative).
//
// The exported block below names wxRendererNative as the model parent, not
// wxDelegateRendererNative: the real C++ base is an IS-A refinement of
// wxRendererNative, so a cast to wxRendererNative* is valid, and naming the
// declaring class is what lets the portability matrix resolve the pair's ovh id
// to wxRendererNative_SetOnGetVersion (renderer.h:421 declares GetVersion and
// wxDelegateRendererNative only forwards it at :597).
class kwxRendererNative : public wxDelegateRendererNative
{
private:
    void* m_object;
    kwxRendererHeaderButtonFunc m_draw_header_button_func;
    kwxRendererVersionFunc m_get_version_func;

public:
    explicit kwxRendererNative(void* pObject);

    void SetOnDrawHeaderButton(void* pFunction)
    {
        m_draw_header_button_func = (kwxRendererHeaderButtonFunc) pFunction;
    }
    void SetOnGetVersion(void* pFunction)
    {
        m_get_version_func = (kwxRendererVersionFunc) pFunction;
    }

    int DrawHeaderButton(wxWindow* win, wxDC& dc, const wxRect& rect, int flags,
                         wxHeaderSortIconType sortArrow, wxHeaderButtonParams* params) override;
    wxRendererVersion GetVersion() const override;
};

// ---------------------------------------------------------------------------
// wxModalDialogHook callbacks
// ---------------------------------------------------------------------------

// dialog is a wxDialog*.  Return wxID_NONE to let the dialog be shown, or any
// other id to skip showing it and return that id from ShowModal().
typedef int (*kwxModalDialogEnterFunc)(void* pObject, void* dialog);

typedef void (*kwxModalDialogExitFunc)(void* pObject, void* dialog);

// Enter() is the only pure virtual on wxModalDialogHook, so overriding it makes
// this class concrete.  Exit() keeps the wxWidgets no-op when unset.
class kwxModalDialogHook : public wxModalDialogHook
{
private:
    void* m_object;
    kwxModalDialogEnterFunc m_enter_func;
    kwxModalDialogExitFunc m_exit_func;
    bool m_capture_enter_dialog;

public:
    explicit kwxModalDialogHook(void* pObject);

    void SetOnEnter(void* pFunction) { m_enter_func = (kwxModalDialogEnterFunc) pFunction; }
    void SetOnExit(void* pFunction) { m_exit_func = (kwxModalDialogExitFunc) pFunction; }
    void SetCaptureEnterDialog(bool capture) { m_capture_enter_dialog = capture; }

protected:
    int Enter(wxDialog* dialog) override;
    void Exit(wxDialog* dialog) override;
};

// ---------------------------------------------------------------------------
// wxNativeWindow callbacks
// ---------------------------------------------------------------------------

// MSWOnNotify is MSW-only.  The callback returns non-zero when it handled the
// native notification; otherwise the base class runs.  lParam and result are
// the WXLPARAM values passed straight through to the native handler.
typedef int (*kwxNativeWindowNotifyFunc)(void* pObject, int idCtrl, void* lParam, void* result);

// handle is the platform-native child window (HWND / GtkWidget* / NSView*);
// wxNativeWindow neither creates nor destroys it.  On non-MSW platforms
// SetOnMSWNotify() still stores the pointer but never fires.  The MSW override
// of MSWOnNotify() lives in the platform-split subclass in src/kwx_hooks.cpp.
class kwxNativeWindow : public wxNativeWindow
{
private:
    void* m_object;
    kwxNativeWindowNotifyFunc m_notify_func = nullptr;

protected:
    // Delivers a native notification to the language callback.  The MSW
    // override of MSWOnNotify() lives in the platform-split subclass in
    // src/kwx_hooks.cpp: its WXLPARAM signature exists only on MSW, and a
    // public header must not carry a platform guard.
    bool InvokeMSWNotify(int idCtrl, void* lParam, void* result)
    {
        return m_notify_func != nullptr && m_notify_func(m_object, idCtrl, lParam, result) != 0;
    }

public:
    kwxNativeWindow(void* pObject, wxWindow* parent, wxWindowID id, void* handle);

    void SetOnMSWNotify(void* pFunction) { m_notify_func = (kwxNativeWindowNotifyFunc) pFunction; }
};

// ---------------------------------------------------------------------------
// wxTextCompleterSimple callbacks
// ---------------------------------------------------------------------------

// prefix is a const wxString* and result a wxArrayString* the callback appends
// its completions to.  Both are valid only for the duration of the call.
typedef void (*kwxTextCompleterFunc)(void* pObject, void* prefix, void* result);

// Only GetCompletions() is pure virtual; Start() and GetNext() are implemented
// by wxTextCompleterSimple itself (wx/textcompleter.h:50-51).
class kwxTextCompleterSimple : public wxTextCompleterSimple
{
private:
    void* m_object;
    kwxTextCompleterFunc m_get_completions_func;

public:
    explicit kwxTextCompleterSimple(void* pObject);

    void SetOnGetCompletions(void* pFunction)
    {
        m_get_completions_func = (kwxTextCompleterFunc) pFunction;
    }

    void GetCompletions(const wxString& prefix, wxArrayString& result) override;
};

// ---------------------------------------------------------------------------
// wxLog callbacks
//
// kwxLog already exists in src/wx_log.cpp (a legacy DoLog()-based helper whose
// kwxLog_Create signature is published in include/kwx_classes.h:105-107), so the
// DoLogRecord()/DoLogTextAtLevel() callbacks were added to that class rather than
// introducing a second helper for the same base.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// wxHtmlTagsModule callbacks
// ---------------------------------------------------------------------------

// parser is a wxHtmlWinParser* valid only for the duration of the call.
typedef void (*kwxHtmlTagsModuleFillFunc)(void* pObject, void* parser);

// wxHtmlTagsModule derives from wxModule, whose OnInit()/OnExit() are pure
// virtual (wx/module.h:40, :45); both are implemented here so the class is
// concrete.  FillHandlersTable() is the only virtual of wxHtmlTagsModule's own
// that the widget sample overrides (wx/html/winpars.h:283).
class kwxHtmlTagsModule : public wxHtmlTagsModule
{
private:
    void* m_object;
    kwxHtmlTagsModuleFillFunc m_fill_handlers_table_func;

public:
    explicit kwxHtmlTagsModule(void* pObject);

    void SetOnFillHandlersTable(void* pFunction)
    {
        m_fill_handlers_table_func = (kwxHtmlTagsModuleFillFunc) pFunction;
    }

    bool OnInit() override;
    void OnExit() override;
    void FillHandlersTable(wxHtmlWinParser* parser) override;
};

// ---------------------------------------------------------------------------
// wxAppTraits callbacks
// ---------------------------------------------------------------------------

// Return a wxLog* the caller takes ownership of.
typedef void* (*kwxAppTraitsLogFunc)(void* pObject);

// Return a wxRendererNative* the caller takes ownership of, or null to use the
// platform default renderer.
typedef void* (*kwxAppTraitsRendererFunc)(void* pObject);

// wxAppTraits itself has 13 pure virtuals, so this derives from
// wxConsoleAppTraits, which is concrete on every port (wx/msw/apptrait.h:17,
// wx/unix/apptrait.h, and the generic declaration at wx/apptrait.h:306) and
// already implements the whole interface; only the two virtuals the samples
// override are replaced here.  A wxConsoleAppTraits IS-A wxAppTraits, so the
// receiver casts to wxAppTraits* without adjustment.
class kwxAppTraits : public wxConsoleAppTraits
{
private:
    void* m_object;
    kwxAppTraitsLogFunc m_create_log_target_func;
    kwxAppTraitsRendererFunc m_create_renderer_func;
    wxLog* m_log_target;

public:
    explicit kwxAppTraits(void* pObject);

    void SetOnCreateLogTarget(void* pFunction)
    {
        m_create_log_target_func = (kwxAppTraitsLogFunc) pFunction;
    }
    void SetOnCreateRenderer(void* pFunction)
    {
        m_create_renderer_func = (kwxAppTraitsRendererFunc) pFunction;
    }

    wxLog* SetLogTarget(wxLog* target)
    {
        wxLog* previous = m_log_target;
        m_log_target = target;
        return previous;
    }

    wxLog* CreateLogTarget() override;
    wxRendererNative* CreateRenderer() override;
};

// ---------------------------------------------------------------------------
// wxEvent callbacks
// ---------------------------------------------------------------------------

// Return a new wxEvent of the same concrete type; the caller takes ownership.
typedef void* (*kwxEventCloneFunc)(void* pObject);

// wxEvent::Clone() is pure virtual (wx/event.h:1016), so overriding it is what
// makes this class concrete.  wxEvent's constructor installs no singleton.
class kwxEvent : public wxEvent
{
private:
    void* m_object;
    kwxEventCloneFunc m_clone_func;

public:
    explicit kwxEvent(void* pObject);

    void SetOnClone(void* pFunction) { m_clone_func = (kwxEventCloneFunc) pFunction; }

    wxEvent* Clone() const override;

    // No default constructor, so register the class info without a factory.
    wxDECLARE_ABSTRACT_CLASS(kwxEvent);
};

// ---------------------------------------------------------------------------
// wxVariantData callbacks
// ---------------------------------------------------------------------------

// Return non-zero when the two data objects hold equal values.
typedef int (*kwxVariantDataEqFunc)(void* pObject, void* otherData);

// Return the type name as a UTF-8 string; the string is copied before the
// callback returns, so it may point at transient storage.
typedef void* (*kwxVariantDataTypeFunc)(void* pObject);

// Eq() and GetType() are both pure virtual on wxVariantData
// (wx/variant.h:62, :73), so both need a callback for the class to be concrete.
class kwxVariantData : public wxVariantData
{
private:
    void* m_object;
    kwxVariantDataEqFunc m_eq_func;
    kwxVariantDataTypeFunc m_get_type_func;

public:
    explicit kwxVariantData(void* pObject);

    void SetOnEq(void* pFunction) { m_eq_func = (kwxVariantDataEqFunc) pFunction; }
    void SetOnGetType(void* pFunction) { m_get_type_func = (kwxVariantDataTypeFunc) pFunction; }

    bool Eq(wxVariantData& data) const override;
    wxString GetType() const override;
};

// ---------------------------------------------------------------------------
// wxWizardPage callbacks
// ---------------------------------------------------------------------------

// Return a wxWizardPage* owned by the page it belongs to; the caller does not
// delete it.
typedef void* (*kwxWizardPageFunc)(void* pObject);

// Out-parameter spelling of the navigation hooks. GetNext()/GetPrev() return a
// page pointer, which a runtime whose native thunk cannot return a value cannot
// produce; these callbacks write the page pointer through `page` instead. `page`
// is initialized to null before the call, so a callback that writes nothing means
// "last page" (GetNext) or "first page" (GetPrev).
typedef void (*kwxWizardPageGetPageOutFunc)(void* pObject, void** page);

// Out-parameter spelling of the transfer hooks: write 0 to veto (false) and any
// other value to accept (true). `result` is initialized to 1 before the call, so a
// callback that writes nothing keeps wxWidgets' accept-by-default behaviour.
typedef void (*kwxWizardPageTransferOutFunc)(void* pObject, int* result);

// GetNext() and GetPrev() are both pure virtual (wx/wizard.h:72-73).
class kwxWizardPage : public wxWizardPage
{
private:
    void* m_object;
    kwxWizardPageFunc m_get_next_func;
    kwxWizardPageFunc m_get_prev_func;
    kwxAppConsoleBoolFunc m_transfer_data_from_window_func;
    kwxAppConsoleBoolFunc m_transfer_data_to_window_func;
    kwxWizardPageGetPageOutFunc m_get_next_out_func;
    kwxWizardPageGetPageOutFunc m_get_prev_out_func;
    kwxWizardPageTransferOutFunc m_transfer_data_from_window_out_func;
    kwxWizardPageTransferOutFunc m_transfer_data_to_window_out_func;

public:
    explicit kwxWizardPage(void* pObject);

    void SetOnGetNext(void* pFunction) { m_get_next_func = (kwxWizardPageFunc) pFunction; }
    void SetOnGetPrev(void* pFunction) { m_get_prev_func = (kwxWizardPageFunc) pFunction; }
    void SetOnTransferDataFromWindow(void* pFunction)
    {
        m_transfer_data_from_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnTransferDataToWindow(void* pFunction)
    {
        m_transfer_data_to_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }

    // An Out callback takes precedence over the returning spelling.
    void SetOnGetNextOut(void* pFunction)
    {
        m_get_next_out_func = (kwxWizardPageGetPageOutFunc) pFunction;
    }
    void SetOnGetPrevOut(void* pFunction)
    {
        m_get_prev_out_func = (kwxWizardPageGetPageOutFunc) pFunction;
    }
    void SetOnTransferDataFromWindowOut(void* pFunction)
    {
        m_transfer_data_from_window_out_func = (kwxWizardPageTransferOutFunc) pFunction;
    }
    void SetOnTransferDataToWindowOut(void* pFunction)
    {
        m_transfer_data_to_window_out_func = (kwxWizardPageTransferOutFunc) pFunction;
    }

    wxWizardPage* GetNext() const override;
    wxWizardPage* GetPrev() const override;
    bool TransferDataFromWindow() override;
    bool TransferDataToWindow() override;
};

// ---------------------------------------------------------------------------
// wxWizardPageSimple callbacks
// ---------------------------------------------------------------------------

// The same hook family as kwxWizardPage, carried by the page class that owns the
// chain.  wxWizardPage declares no SetNext()/SetPrev()/Chain() at all, so a page
// that overrides navigation or transfer and must stay linkable belongs here, not
// on kwxWizardPage.  Unlike kwxWizardPage, every override falls through to
// wxWizardPageSimple when its hook is not installed, so the prev/next pointers
// installed through SetNext()/SetPrev()/Chain() keep their meaning on a page that
// overrides nothing.
class kwxWizardPageSimple : public wxWizardPageSimple
{
private:
    void* m_object;
    kwxWizardPageFunc m_get_next_func;
    kwxWizardPageFunc m_get_prev_func;
    kwxAppConsoleBoolFunc m_transfer_data_from_window_func;
    kwxAppConsoleBoolFunc m_transfer_data_to_window_func;
    kwxWizardPageGetPageOutFunc m_get_next_out_func;
    kwxWizardPageGetPageOutFunc m_get_prev_out_func;
    kwxWizardPageTransferOutFunc m_transfer_data_from_window_out_func;
    kwxWizardPageTransferOutFunc m_transfer_data_to_window_out_func;

public:
    kwxWizardPageSimple(void* pObject, wxWizard* parent, wxWizardPage* prev, wxWizardPage* next,
                        const wxBitmapBundle& bitmap);

    void SetOnGetNext(void* pFunction) { m_get_next_func = (kwxWizardPageFunc) pFunction; }
    void SetOnGetPrev(void* pFunction) { m_get_prev_func = (kwxWizardPageFunc) pFunction; }
    void SetOnTransferDataFromWindow(void* pFunction)
    {
        m_transfer_data_from_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }
    void SetOnTransferDataToWindow(void* pFunction)
    {
        m_transfer_data_to_window_func = (kwxAppConsoleBoolFunc) pFunction;
    }

    // An Out callback takes precedence over the returning spelling.
    void SetOnGetNextOut(void* pFunction)
    {
        m_get_next_out_func = (kwxWizardPageGetPageOutFunc) pFunction;
    }
    void SetOnGetPrevOut(void* pFunction)
    {
        m_get_prev_out_func = (kwxWizardPageGetPageOutFunc) pFunction;
    }
    void SetOnTransferDataFromWindowOut(void* pFunction)
    {
        m_transfer_data_from_window_out_func = (kwxWizardPageTransferOutFunc) pFunction;
    }
    void SetOnTransferDataToWindowOut(void* pFunction)
    {
        m_transfer_data_to_window_out_func = (kwxWizardPageTransferOutFunc) pFunction;
    }

    wxWizardPage* GetNext() const override;
    wxWizardPage* GetPrev() const override;
    bool TransferDataFromWindow() override;
    bool TransferDataToWindow() override;
};

// ---------------------------------------------------------------------------
// wxPopupTransientWindow callbacks
// ---------------------------------------------------------------------------

// event is a wxMouseEvent*.  Return non-zero to report the click was handled.
typedef int (*kwxPopupLeftDownFunc)(void* pObject, void* event);
typedef void (*kwxPopupFunc)(void* pObject, void* focus);
typedef int (*kwxPopupShowFunc)(void* pObject, int show);

// wxPopupTransientWindow still declares Dismiss() and Popup() pure
// (wx/popupwin.h:112-133); both are implemented here so the class is concrete.
class kwxPopupTransientWindow : public wxPopupTransientWindow
{
private:
    void* m_object;
    kwxPopupFunc m_popup_func;
    kwxPopupShowFunc m_show_func;
    kwxPopupLeftDownFunc m_process_left_down_func;
    kwxTimerFunc m_on_dismiss_func;

public:
    kwxPopupTransientWindow(void* pObject, wxWindow* parent, int style);

    void SetOnPopup(void* pFunction) { m_popup_func = (kwxPopupFunc) pFunction; }
    void SetOnShow(void* pFunction) { m_show_func = (kwxPopupShowFunc) pFunction; }
    void SetOnProcessLeftDown(void* pFunction)
    {
        m_process_left_down_func = (kwxPopupLeftDownFunc) pFunction;
    }
    void SetOnOnDismiss(void* pFunction) { m_on_dismiss_func = (kwxTimerFunc) pFunction; }

    // A callback replaces the override above.  A port that needs the C++ shape
    // "log, then call the wxWidgets implementation" calls the matching
    // CallBase* function from inside its callback: the qualified call invokes
    // the wxWidgets implementation directly instead of re-entering the
    // override (and therefore the callback) through virtual dispatch.
    void CallBasePopup(wxWindow* focus) { wxPopupTransientWindow::Popup(focus); }
    bool CallBaseShow(bool show) { return wxPopupTransientWindow::Show(show); }
    bool CallBaseProcessLeftDown(wxMouseEvent& event)
    {
        return wxPopupTransientWindow::ProcessLeftDown(event);
    }
    void CallBaseOnDismiss() { wxPopupTransientWindow::OnDismiss(); }

    void Popup(wxWindow* focus = nullptr) override;
    bool Show(bool show = true) override;
    bool ProcessLeftDown(wxMouseEvent& event) override;
    void OnDismiss() override;
};

// ---------------------------------------------------------------------------
// wxDocument callbacks//
// ---------------------------------------------------------------------------

// All string arguments are const wxString* values valid only for the duration
// of the call.  Return non-zero for success.
typedef int (*kwxDocumentStringBoolFunc)(void* pObject, void* text);

// path is a const wxString* and flags a long.
typedef int (*kwxDocumentCreateFunc)(void* pObject, void* path, long flags);
typedef int (*kwxDocumentBoolFunc)(void* pObject);
typedef void (*kwxDocumentModifyFunc)(void* pObject, int modified);

// LoadObject() and SaveObject() are absent on purpose: their signatures take
// std::istream& / std::ostream& (wx/docview.h:101-105), which cannot cross a
// fixed extern "C" boundary; they are recorded as not-representable.
// The library-wide uniform thunk, void (*)(void* data, void* arg1, void* arg2).  A
// late-bound backend can install only this shape, so every value-returning typed
// callback above has a WithData twin that is checked before it.
// Integers/bools travel as (void*)(intptr_t)value.
typedef void (*kwxDocumentHookFn)(void* data, void* arg1, void* arg2);

class kwxDocument : public wxDocument
{
private:
    void* m_object;
    kwxDocumentStringBoolFunc m_do_open_document_func;
    kwxDocumentStringBoolFunc m_do_save_document_func;
    kwxObjectClassInfoFunc m_get_class_info_func;
    kwxDocumentBoolFunc m_is_modified_func;
    kwxDocumentModifyFunc m_modify_func;
    kwxDocumentCreateFunc m_on_create_func;
    kwxDocumentStringBoolFunc m_on_open_document_func;

    kwxDocumentHookFn m_do_open_document_hook;
    void* m_do_open_document_hook_data;
    kwxDocumentHookFn m_do_save_document_hook;
    void* m_do_save_document_hook_data;
    kwxDocumentHookFn m_is_modified_hook;
    void* m_is_modified_hook_data;
    kwxDocumentHookFn m_modify_hook;
    void* m_modify_hook_data;
    kwxDocumentHookFn m_on_create_hook;
    void* m_on_create_hook_data;
    kwxDocumentHookFn m_on_open_document_hook;
    void* m_on_open_document_hook_data;

    // Set by the Set...Result members and cleared before every hook call, so only
    // the call in flight can answer; IsModified() is const, hence mutable.
    mutable bool m_published;
    mutable bool m_result_bool;

public:
    // parent is the owning document for a child/details document; the base
    // constructor moves the new object into parent->m_childDocuments and does not
    // register it with the document manager.
    explicit kwxDocument(void* pObject, wxDocument* parent = nullptr);

    void SetOnDoOpenDocument(void* pFunction)
    {
        m_do_open_document_func = (kwxDocumentStringBoolFunc) pFunction;
    }
    void SetOnDoSaveDocument(void* pFunction)
    {
        m_do_save_document_func = (kwxDocumentStringBoolFunc) pFunction;
    }
    void SetOnGetClassInfo(void* pFunction)
    {
        m_get_class_info_func = (kwxObjectClassInfoFunc) pFunction;
    }
    void SetOnIsModified(void* pFunction) { m_is_modified_func = (kwxDocumentBoolFunc) pFunction; }
    void SetOnModify(void* pFunction) { m_modify_func = (kwxDocumentModifyFunc) pFunction; }
    void SetOnOnCreate(void* pFunction) { m_on_create_func = (kwxDocumentCreateFunc) pFunction; }
    void SetOnOnOpenDocument(void* pFunction)
    {
        m_on_open_document_func = (kwxDocumentStringBoolFunc) pFunction;
    }

    void SetOnDoOpenDocumentWithData(void* pFunction, void* data)
    {
        m_do_open_document_hook = (kwxDocumentHookFn) pFunction;
        m_do_open_document_hook_data = data;
    }
    void SetOnDoSaveDocumentWithData(void* pFunction, void* data)
    {
        m_do_save_document_hook = (kwxDocumentHookFn) pFunction;
        m_do_save_document_hook_data = data;
    }
    void SetOnIsModifiedWithData(void* pFunction, void* data)
    {
        m_is_modified_hook = (kwxDocumentHookFn) pFunction;
        m_is_modified_hook_data = data;
    }
    void SetOnModifyWithData(void* pFunction, void* data)
    {
        m_modify_hook = (kwxDocumentHookFn) pFunction;
        m_modify_hook_data = data;
    }
    void SetOnOnCreateWithData(void* pFunction, void* data)
    {
        m_on_create_hook = (kwxDocumentHookFn) pFunction;
        m_on_create_hook_data = data;
    }
    void SetOnOnOpenDocumentWithData(void* pFunction, void* data)
    {
        m_on_open_document_hook = (kwxDocumentHookFn) pFunction;
        m_on_open_document_hook_data = data;
    }

    void SetDoOpenDocumentResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetDoSaveDocumentResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetIsModifiedResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetOnCreateResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetOnOpenDocumentResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }

protected:
    bool DoOpenDocument(const wxString& file) override;
    bool DoSaveDocument(const wxString& file) override;
    wxClassInfo* GetClassInfo() const override;
    bool IsModified() const override;
    void Modify(bool modified) override;
    bool OnCreate(const wxString& path, long flags) override;
    bool OnOpenDocument(const wxString& filename) override;
};

// ---------------------------------------------------------------------------
// wxView callbacks
// ---------------------------------------------------------------------------

// dc is a wxDC*, doc a wxDocument*, sender a wxView* and hint a wxObject*;
// each is valid only for the duration of the call and may be null.
typedef void (*kwxViewDrawFunc)(void* pObject, void* dc);
typedef int (*kwxViewCloseFunc)(void* pObject, int deleteWindow);
typedef int (*kwxViewCreateFunc)(void* pObject, void* document, long flags);
typedef void (*kwxViewUpdateFunc)(void* pObject, void* sender, void* hint);

// The same uniform thunk for the two value-returning view hooks.
typedef void (*kwxViewHookFn)(void* data, void* arg1, void* arg2);

// OnDraw() is the only pure virtual on wxView, so overriding it makes this
// class concrete.
class kwxView : public wxView
{
private:
    void* m_object;
    kwxViewDrawFunc m_on_draw_func;
    kwxViewCloseFunc m_on_close_func;
    kwxViewCreateFunc m_on_create_func;
    kwxViewUpdateFunc m_on_update_func;

    kwxViewHookFn m_on_create_hook;
    void* m_on_create_hook_data;
    kwxViewHookFn m_on_close_hook;
    void* m_on_close_hook_data;

    // See kwxDocument: only the call in flight can answer, so the published value is
    // cleared before every invocation.  The view hooks are not const, but the pair is
    // kept mutable so both helpers have the same shape.
    mutable bool m_published;
    mutable bool m_result_bool;

public:
    explicit kwxView(void* pObject);

    void SetOnOnDraw(void* pFunction) { m_on_draw_func = (kwxViewDrawFunc) pFunction; }
    void SetOnOnClose(void* pFunction) { m_on_close_func = (kwxViewCloseFunc) pFunction; }
    void SetOnOnCreate(void* pFunction) { m_on_create_func = (kwxViewCreateFunc) pFunction; }
    void SetOnOnUpdate(void* pFunction) { m_on_update_func = (kwxViewUpdateFunc) pFunction; }

    void SetOnOnCreateWithData(void* pFunction, void* data)
    {
        m_on_create_hook = (kwxViewHookFn) pFunction;
        m_on_create_hook_data = data;
    }
    void SetOnOnCloseWithData(void* pFunction, void* data)
    {
        m_on_close_hook = (kwxViewHookFn) pFunction;
        m_on_close_hook_data = data;
    }

    void SetOnCreateResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetOnCloseResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }

    void OnDraw(wxDC* dc) override;
    bool OnClose(bool deleteWindow) override;
    bool OnCreate(wxDocument* document, long flags) override;
    void OnUpdate(wxView* sender, wxObject* hint) override;
};

// ---------------------------------------------------------------------------
// wxDocTemplate callbacks
// ---------------------------------------------------------------------------

// Called from DoCreateDocument()/DoCreateView().  The template object is passed so one
// callback can serve several templates; the hook publishes what it built with
// kwxDocTemplate_SetCreatedDocument()/SetCreatedView() before returning.
typedef void (*kwxDocTemplateCreateDocumentFunc)(void* pObject, void* templateObject);
typedef void (*kwxDocTemplateCreateViewFunc)(void* pObject, void* templateObject, void* document);

// DoCreateDocument()/DoCreateView() are the only override points that keep the whole
// base lifecycle (InitDocument, OnCreate, SetDocument) intact -- do not override
// CreateDocument()/CreateView() themselves.
//
// DoCreateView() receives no argument, so the document it is creating a view for is
// recorded by InitDocument(), which the base CreateDocument() calls before the
// document's OnCreate(); a view created later by a separate CreateView() request (the
// "new view" command) therefore reaches its hook with a null document.
class kwxDocTemplate : public wxDocTemplate
{
private:
    void* m_object;
    kwxDocTemplateCreateDocumentFunc m_create_document_func;
    kwxDocTemplateCreateViewFunc m_create_view_func;
    wxDocument* m_created_document;
    wxView* m_created_view;
    wxDocument* m_initing_document;

public:
    kwxDocTemplate(void* pObject, wxDocManager* manager, const wxString& descr,
                   const wxString& filter, const wxString& dir, const wxString& ext,
                   const wxString& docTypeName, const wxString& viewTypeName, long flags);

    void SetOnCreateDocument(void* pFunction)
    {
        m_create_document_func = (kwxDocTemplateCreateDocumentFunc) pFunction;
    }
    void SetOnCreateView(void* pFunction)
    {
        m_create_view_func = (kwxDocTemplateCreateViewFunc) pFunction;
    }
    void SetCreatedDocument(wxDocument* doc) { m_created_document = doc; }
    void SetCreatedView(wxView* view) { m_created_view = view; }

    bool InitDocument(wxDocument* doc, const wxString& path, long flags) override;

protected:
    wxDocument* DoCreateDocument() override;
    wxView* DoCreateView() override;
};

// ---------------------------------------------------------------------------
// Document/view frames for AUI MDI
// ---------------------------------------------------------------------------
// wxDocParentFrameAny<T> and wxDocChildFrameAny<T, P> are templates (wx/docview.h:829,
// :669), so no binding can name the instantiation a port needs for the C++ sample's
// --aui mode.  These two classes ARE those instantiations under a C-visible name.
// Each inherits its frame class as its FIRST base, which is what the generated
// `extends` clause claims, so a helper can be passed wherever the base frame is
// expected.  Frames are wx-owned: there is deliberately no _Delete -- destroy them with
// wxWindow_Destroy, exactly as for wxDocParentFrame / wxDocChildFrame.
class kwxDocAuiParentFrame : public wxDocParentFrameAny<wxAuiMDIParentFrame>
{
public:
    kwxDocAuiParentFrame() = default;
    kwxDocAuiParentFrame(wxDocManager* manager, wxFrame* parent, wxWindowID id,
                         const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    {
        Create(manager, parent, id, title, pos, size, style);
    }
};

class kwxDocAuiChildFrame : public wxDocChildFrameAny<wxAuiMDIChildFrame, wxAuiMDIParentFrame>
{
public:
    kwxDocAuiChildFrame() = default;
    kwxDocAuiChildFrame(wxDocument* doc, wxView* view, wxAuiMDIParentFrame* parent, wxWindowID id,
                        const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    {
        Create(doc, view, parent, id, title, pos, size, style);
    }
};

// ---------------------------------------------------------------------------
// wxFileSystemHandler callbacks
// ---------------------------------------------------------------------------

// location is a const wxString*.  Return non-zero when this handler owns it.
typedef int (*kwxFileSystemCanOpenFunc)(void* pObject, void* location);

// fs is a wxFileSystem* and location a const wxString*.  Return a wxFSFile*
// the caller takes ownership of, or null.
typedef void* (*kwxFileSystemOpenFileFunc)(void* pObject, void* fs, void* location);

// CanOpen() and OpenFile() are both pure virtual (wx/filesys.h:115, :120).
class kwxFileSystemHandler : public wxFileSystemHandler
{
private:
    void* m_object;
    kwxFileSystemCanOpenFunc m_can_open_func;
    kwxFileSystemOpenFileFunc m_open_file_func;

public:
    explicit kwxFileSystemHandler(void* pObject);

    void SetOnCanOpen(void* pFunction) { m_can_open_func = (kwxFileSystemCanOpenFunc) pFunction; }
    void SetOnOpenFile(void* pFunction)
    {
        m_open_file_func = (kwxFileSystemOpenFileFunc) pFunction;
    }

    bool CanOpen(const wxString& location) override;
    wxFSFile* OpenFile(wxFileSystem& fs, const wxString& location) override;
};

// ---------------------------------------------------------------------------
// wxHtmlTagHandler callbacks
// ---------------------------------------------------------------------------

// Return the supported tag names as a UTF-8 string; it is copied before the
// callback returns.
typedef void* (*kwxHtmlTagHandlerTagsFunc)(void* pObject);

// tag is a const wxHtmlTag*.  Return non-zero when the tag was handled.
typedef int (*kwxHtmlTagHandlerTagFunc)(void* pObject, void* tag);

// GetSupportedTags() and HandleTag() are both pure virtual
// (wx/html/htmlpars.h:233, :239).
class kwxHtmlTagHandler : public wxHtmlTagHandler
{
private:
    void* m_object;
    kwxHtmlTagHandlerTagsFunc m_get_supported_tags_func;
    kwxHtmlTagHandlerTagFunc m_handle_tag_func;

public:
    explicit kwxHtmlTagHandler(void* pObject);

    void SetOnGetSupportedTags(void* pFunction)
    {
        m_get_supported_tags_func = (kwxHtmlTagHandlerTagsFunc) pFunction;
    }
    void SetOnHandleTag(void* pFunction)
    {
        m_handle_tag_func = (kwxHtmlTagHandlerTagFunc) pFunction;
    }

    wxString GetSupportedTags() override;
    bool HandleTag(const wxHtmlTag& tag) override;
};

// ---------------------------------------------------------------------------
// wxAddRemoveAdaptor callbacks
// ---------------------------------------------------------------------------

// Every callback takes three pointers so the runtime's fixed three-argument
// thunk can be used for all of them.  Only pObject carries information; the two
// trailing pointers are always null.
using kwxAddRemoveGetItemsCtrlFn = void* (*) (void* pObject, void* arg1, void* arg2);
using kwxAddRemoveBoolFn = TBool (*)(void* pObject, void* arg1, void* arg2);
using kwxAddRemoveVoidFn = void (*)(void* pObject, void* arg1, void* arg2);

// Every member of wxAddRemoveAdaptor is pure virtual, so all five are overridden
// to make this class concrete.  An unset callback keeps the inert behaviour:
// no control, nothing can be added or removed, and the actions do nothing.  That
// null check belongs here, in the override, not at the FFI boundary.
//
// wxAddRemoveCtrl::SetAdaptor() takes ownership of the adaptor and deletes it
// with the control, so kwxAddRemoveAdaptor_Delete is only for an adaptor that
// was never handed to a control.
class kwxAddRemoveAdaptor : public wxAddRemoveAdaptor
{
private:
    void* m_object;
    kwxAddRemoveGetItemsCtrlFn m_get_items_ctrl_func;
    kwxAddRemoveBoolFn m_can_add_func;
    kwxAddRemoveBoolFn m_can_remove_func;
    kwxAddRemoveVoidFn m_on_add_func;
    kwxAddRemoveVoidFn m_on_remove_func;
    wxWindow* m_items_ctrl;
    bool m_can_add;
    bool m_can_remove;

public:
    explicit kwxAddRemoveAdaptor(void* pObject);

    void SetOnGetItemsCtrl(void* pFunction)
    {
        m_get_items_ctrl_func = reinterpret_cast<kwxAddRemoveGetItemsCtrlFn>(pFunction);
    }
    void SetOnCanAdd(void* pFunction)
    {
        m_can_add_func = reinterpret_cast<kwxAddRemoveBoolFn>(pFunction);
    }
    void SetOnCanRemove(void* pFunction)
    {
        m_can_remove_func = reinterpret_cast<kwxAddRemoveBoolFn>(pFunction);
    }
    void SetOnAdd(void* pFunction)
    {
        m_on_add_func = reinterpret_cast<kwxAddRemoveVoidFn>(pFunction);
    }
    void SetOnRemove(void* pFunction)
    {
        m_on_remove_func = reinterpret_cast<kwxAddRemoveVoidFn>(pFunction);
    }

    void SetItemsCtrl(wxWindow* ctrl) { m_items_ctrl = ctrl; }
    void SetCanAdd(bool value) { m_can_add = value; }
    void SetCanRemove(bool value) { m_can_remove = value; }

    wxWindow* GetItemsCtrl() const override;
    bool CanAdd() const override;
    bool CanRemove() const override;
    void OnAdd() override;
    void OnRemove() override;
};

// ---------------------------------------------------------------------------
// wxDataViewModel / wxDataViewIndexListModel / wxDataViewVirtualListModel callbacks
// ---------------------------------------------------------------------------
//
// A foreign language cannot subclass a wxDataView model, so the helpers below derive
// from the real wxWidgets model, keep one foreign function pointer plus one token per
// virtual, and forward each virtual to it.  The callback shape is the library-wide
// uniform thunk
//
//     void (*)(void* data, void* arg1, void* arg2)
//
// where `data` is the per-hook token (never pObject).  Integers cross as
// (void*)(intptr_t)value, so an integer zero arrives as NULL.  Out-values are
// published with the Set*Result members while the callback runs; the in-flight block
// is cleared before every call, so a callback that publishes nothing leaves the
// neutral default below in place.
//
// The wxDataViewModel queries are const, so the in-flight block they write while their
// callback runs is mutable.  Only one hook runs at a time, so a single set of result
// slots serves every hook.

using kwxDataViewHookFn = void (*)(void* data, void* arg1, void* arg2);

class kwxDataViewModel : public wxDataViewModel
{
private:
    void* m_object;

    kwxDataViewHookFn m_get_value_hook;
    void* m_get_value_hook_data;
    kwxDataViewHookFn m_set_value_hook;
    void* m_set_value_hook_data;
    kwxDataViewHookFn m_get_parent_hook;
    void* m_get_parent_hook_data;
    kwxDataViewHookFn m_is_container_hook;
    void* m_is_container_hook_data;
    kwxDataViewHookFn m_get_children_hook;
    void* m_get_children_hook_data;
    kwxDataViewHookFn m_has_value_hook;
    void* m_has_value_hook_data;
    kwxDataViewHookFn m_is_enabled_hook;
    void* m_is_enabled_hook_data;
    kwxDataViewHookFn m_has_container_columns_hook;
    void* m_has_container_columns_hook_data;
    kwxDataViewHookFn m_compare_hook;
    void* m_compare_hook_data;
    kwxDataViewHookFn m_has_default_compare_hook;
    void* m_has_default_compare_hook_data;
    kwxDataViewHookFn m_resort_hook;
    void* m_resort_hook_data;
    kwxDataViewHookFn m_get_attr_hook;
    void* m_get_attr_hook_data;

    mutable bool m_published;
    mutable unsigned int m_pending_column;
    mutable bool m_pending_ascending;
    mutable wxVariant m_result_variant;
    mutable wxDataViewItem m_result_item;
    mutable bool m_result_bool;
    mutable int m_result_int;
    mutable unsigned int m_result_uint;
    mutable wxDataViewItemAttr m_result_attr;
    mutable wxDataViewItemArray* m_children_target;

    void ResetInFlight() const;

public:
    explicit kwxDataViewModel(void* pObject);

    void SetOnGetValueWithData(void* pFunction, void* data)
    {
        m_get_value_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_value_hook_data = data;
    }
    void SetOnSetValueWithData(void* pFunction, void* data)
    {
        m_set_value_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_set_value_hook_data = data;
    }
    void SetOnGetParentWithData(void* pFunction, void* data)
    {
        m_get_parent_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_parent_hook_data = data;
    }
    void SetOnIsContainerWithData(void* pFunction, void* data)
    {
        m_is_container_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_is_container_hook_data = data;
    }
    void SetOnGetChildrenWithData(void* pFunction, void* data)
    {
        m_get_children_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_children_hook_data = data;
    }
    void SetOnHasValueWithData(void* pFunction, void* data)
    {
        m_has_value_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_has_value_hook_data = data;
    }
    void SetOnIsEnabledWithData(void* pFunction, void* data)
    {
        m_is_enabled_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_is_enabled_hook_data = data;
    }
    void SetOnHasContainerColumnsWithData(void* pFunction, void* data)
    {
        m_has_container_columns_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_has_container_columns_hook_data = data;
    }
    void SetOnCompareWithData(void* pFunction, void* data)
    {
        m_compare_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_compare_hook_data = data;
    }
    void SetOnHasDefaultCompareWithData(void* pFunction, void* data)
    {
        m_has_default_compare_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_has_default_compare_hook_data = data;
    }
    void SetOnResortWithData(void* pFunction, void* data)
    {
        m_resort_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_resort_hook_data = data;
    }
    void SetOnGetAttrWithData(void* pFunction, void* data)
    {
        m_get_attr_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_attr_hook_data = data;
    }

    unsigned int GetPendingColumn() const { return m_pending_column; }
    bool GetPendingAscending() const { return m_pending_ascending; }

    void SetGetValueResult(const wxVariant& value)
    {
        m_result_variant = value;
        m_published = true;
    }
    void SetSetValueResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetGetParentResult(const wxDataViewItem& parent)
    {
        m_result_item = parent;
        m_published = true;
    }
    void SetIsContainerResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetGetChildrenCountResult(unsigned int count)
    {
        m_result_uint = count;
        m_published = true;
    }
    // Appends to the array the in-flight GetChildren() received.  It deliberately does not
    // publish a count: an appended array is already the answer, and only an explicit
    // SetGetChildrenCountResult overrides the array size.
    void AddChildResult(const wxDataViewItem& item)
    {
        if (m_children_target)
        {
            m_children_target->Add(item);
        }
    }
    void SetHasValueResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetIsEnabledResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetHasContainerColumnsResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetCompareResult(int result)
    {
        m_result_int = result;
        m_published = true;
    }
    void SetHasDefaultCompareResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    // Copies the attribute and is itself the success signal for GetAttr.
    void SetGetAttrResult(const wxDataViewItemAttr& attr)
    {
        m_result_attr = attr;
        m_result_bool = true;
        m_published = true;
    }
    void GetValue(wxVariant& variant, const wxDataViewItem& item, unsigned int col) const override;
    bool SetValue(const wxVariant& variant, const wxDataViewItem& item, unsigned int col) override;
    wxDataViewItem GetParent(const wxDataViewItem& item) const override;
    bool IsContainer(const wxDataViewItem& item) const override;
    unsigned int GetChildren(const wxDataViewItem& item,
                             wxDataViewItemArray& children) const override;
    bool HasValue(const wxDataViewItem& item, unsigned int col) const override;
    bool IsEnabled(const wxDataViewItem& item, unsigned int col) const override;
    bool GetAttr(const wxDataViewItem& item, unsigned int col,
                 wxDataViewItemAttr& attr) const override;
    bool HasContainerColumns(const wxDataViewItem& item) const override;
    int Compare(const wxDataViewItem& item1, const wxDataViewItem& item2, unsigned int column,
                bool ascending) const override;
    bool HasDefaultCompare() const override;
    void Resort() override;
};

// Shared override bodies for the two row-based models.  A member template cannot be
// defined out of line without an explicit instantiation, and wxDataViewVirtualListModel
// is a typedef of wxDataViewIndexListModel on macOS, which would make a second explicit
// instantiation of the same specialisation an error -- so the bodies live here.
template <typename TModel>
class kwxDataViewRowModel : public TModel
{
private:
    void* m_object;

    kwxDataViewHookFn m_get_value_by_row_hook;
    void* m_get_value_by_row_hook_data;
    kwxDataViewHookFn m_set_value_by_row_hook;
    void* m_set_value_by_row_hook_data;
    kwxDataViewHookFn m_get_row_hook;
    void* m_get_row_hook_data;
    kwxDataViewHookFn m_get_count_hook;
    void* m_get_count_hook_data;
    kwxDataViewHookFn m_get_attr_by_row_hook;
    void* m_get_attr_by_row_hook_data;
    kwxDataViewHookFn m_is_enabled_by_row_hook;
    void* m_is_enabled_by_row_hook_data;
    kwxDataViewHookFn m_compare_hook;
    void* m_compare_hook_data;
    kwxDataViewHookFn m_has_default_compare_hook;
    void* m_has_default_compare_hook_data;

    mutable bool m_published;
    mutable unsigned int m_pending_row;
    mutable unsigned int m_pending_column;
    mutable bool m_pending_ascending;
    mutable wxVariant m_result_variant;
    mutable bool m_result_bool;
    mutable int m_result_int;
    mutable unsigned int m_result_uint;
    mutable wxDataViewItemAttr m_result_attr;

    void ResetInFlight() const
    {
        m_published = false;
        m_pending_row = 0;
        m_pending_column = 0;
        m_pending_ascending = false;
        m_result_variant = wxVariant();
        m_result_bool = false;
        m_result_int = 0;
        m_result_uint = 0;
        m_result_attr = wxDataViewItemAttr();
    }

protected:
    kwxDataViewRowModel(void* pObject, unsigned int initialSize) : TModel(initialSize)
    {
        m_object = pObject;
        m_get_value_by_row_hook = nullptr;
        m_get_value_by_row_hook_data = nullptr;
        m_set_value_by_row_hook = nullptr;
        m_set_value_by_row_hook_data = nullptr;
        m_get_row_hook = nullptr;
        m_get_row_hook_data = nullptr;
        m_get_count_hook = nullptr;
        m_get_count_hook_data = nullptr;
        m_get_attr_by_row_hook = nullptr;
        m_get_attr_by_row_hook_data = nullptr;
        m_is_enabled_by_row_hook = nullptr;
        m_is_enabled_by_row_hook_data = nullptr;
        m_compare_hook = nullptr;
        m_compare_hook_data = nullptr;
        m_has_default_compare_hook = nullptr;
        m_has_default_compare_hook_data = nullptr;
        ResetInFlight();
    }

public:
    void SetOnGetValueByRowWithData(void* pFunction, void* data)
    {
        m_get_value_by_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_value_by_row_hook_data = data;
    }
    void SetOnSetValueByRowWithData(void* pFunction, void* data)
    {
        m_set_value_by_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_set_value_by_row_hook_data = data;
    }
    void SetOnGetRowWithData(void* pFunction, void* data)
    {
        m_get_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_row_hook_data = data;
    }
    void SetOnGetCountWithData(void* pFunction, void* data)
    {
        m_get_count_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_count_hook_data = data;
    }
    void SetOnGetAttrByRowWithData(void* pFunction, void* data)
    {
        m_get_attr_by_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_attr_by_row_hook_data = data;
    }
    void SetOnIsEnabledByRowWithData(void* pFunction, void* data)
    {
        m_is_enabled_by_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_is_enabled_by_row_hook_data = data;
    }
    void SetOnCompareWithData(void* pFunction, void* data)
    {
        m_compare_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_compare_hook_data = data;
    }
    void SetOnHasDefaultCompareWithData(void* pFunction, void* data)
    {
        m_has_default_compare_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_has_default_compare_hook_data = data;
    }

    unsigned int GetPendingColumn() const { return m_pending_column; }
    unsigned int GetPendingRow() const { return m_pending_row; }
    bool GetPendingAscending() const { return m_pending_ascending; }

    void SetGetValueByRowResult(const wxVariant& value)
    {
        m_result_variant = value;
        m_published = true;
    }
    void SetSetValueByRowResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetGetRowResult(unsigned int row)
    {
        m_result_uint = row;
        m_published = true;
    }
    void SetGetCountResult(unsigned int count)
    {
        m_result_uint = count;
        m_published = true;
    }
    void SetGetAttrByRowResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    // Copies the attribute and is itself the success signal for GetAttrByRow.
    void SetGetAttrByRowAttr(const wxDataViewItemAttr& attr)
    {
        m_result_attr = attr;
        m_result_bool = true;
        m_published = true;
    }
    void SetIsEnabledByRowResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetCompareResult(int result)
    {
        m_result_int = result;
        m_published = true;
    }
    void SetHasDefaultCompareResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }

    void GetValueByRow(wxVariant& variant, unsigned int row, unsigned int col) const override
    {
        if (!m_get_value_by_row_hook)
        {
            // No callback: leave the variant untouched, which is what an empty cell is.
            return;
        }
        ResetInFlight();
        m_pending_row = row;
        m_pending_column = col;
        m_get_value_by_row_hook(m_get_value_by_row_hook_data, (void*) (intptr_t) row, nullptr);
        if (m_published)
        {
            variant = m_result_variant;
        }
    }

    bool SetValueByRow(const wxVariant& variant, unsigned int row, unsigned int col) override
    {
        if (!m_set_value_by_row_hook)
        {
            return false;
        }
        ResetInFlight();
        m_pending_row = row;
        m_pending_column = col;
        m_set_value_by_row_hook(m_set_value_by_row_hook_data, const_cast<wxVariant*>(&variant),
                                nullptr);
        return m_published ? m_result_bool : false;
    }

    unsigned int GetRow(const wxDataViewItem& item) const override
    {
        if (!m_get_row_hook)
        {
            return 0;
        }
        ResetInFlight();
        m_get_row_hook(m_get_row_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
        return m_published ? m_result_uint : 0;
    }

    unsigned int GetCount() const override
    {
        if (!m_get_count_hook)
        {
            return 0;
        }
        ResetInFlight();
        m_get_count_hook(m_get_count_hook_data, nullptr, nullptr);
        return m_published ? m_result_uint : 0;
    }

    // A port publishes the attribute with SetGetAttrByRowAttr, which copies it and
    // implies success; publishing only the boolean leaves the attribute untouched.
    bool GetAttrByRow(unsigned int row, unsigned int col, wxDataViewItemAttr& attr) const override
    {
        if (!m_get_attr_by_row_hook)
        {
            return false;
        }
        ResetInFlight();
        m_pending_row = row;
        m_pending_column = col;
        m_get_attr_by_row_hook(m_get_attr_by_row_hook_data, (void*) (intptr_t) row,
                               (void*) (intptr_t) col);
        if (!m_published)
        {
            return false;
        }
        if (m_result_bool)
        {
            attr = m_result_attr;
        }
        return m_result_bool;
    }

    bool IsEnabledByRow(unsigned int row, unsigned int col) const override
    {
        if (!m_is_enabled_by_row_hook)
        {
            return true;
        }
        ResetInFlight();
        m_pending_row = row;
        m_pending_column = col;
        m_is_enabled_by_row_hook(m_is_enabled_by_row_hook_data, (void*) (intptr_t) row,
                                 (void*) (intptr_t) col);
        return m_published ? m_result_bool : true;
    }

    int Compare(const wxDataViewItem& item1, const wxDataViewItem& item2, unsigned int column,
                bool ascending) const override
    {
        if (!m_compare_hook)
        {
            // 0 is "the rows compare equal"; the base classes' index compare is not
            // reachable here without a callback because wxDataViewVirtualListModel
            // overrides Compare itself and wxDataViewIndexListModel does not.
            return 0;
        }
        ResetInFlight();
        m_pending_column = column;
        m_pending_ascending = ascending;
        m_compare_hook(m_compare_hook_data, const_cast<wxDataViewItem*>(&item1),
                       const_cast<wxDataViewItem*>(&item2));
        return m_published ? m_result_int : 0;
    }

    bool HasDefaultCompare() const override
    {
        if (!m_has_default_compare_hook)
        {
            return false;
        }
        ResetInFlight();
        m_has_default_compare_hook(m_has_default_compare_hook_data, nullptr, nullptr);
        return m_published ? m_result_bool : false;
    }
};

class kwxDataViewVirtualListModel : public kwxDataViewRowModel<wxDataViewVirtualListModel>
{
public:
    kwxDataViewVirtualListModel(void* pObject, unsigned int initialSize) :
        kwxDataViewRowModel<wxDataViewVirtualListModel>(pObject, initialSize)
    {
    }
};

class kwxDataViewIndexListModel : public kwxDataViewRowModel<wxDataViewIndexListModel>
{
public:
    kwxDataViewIndexListModel(void* pObject, unsigned int initialSize) :
        kwxDataViewRowModel<wxDataViewIndexListModel>(pObject, initialSize)
    {
    }
};

// ---------------------------------------------------------------------------
// wxDataViewListStore
// ---------------------------------------------------------------------------
//
// The store keeps its own rows and columns.  With no hook installed every override below
// calls the wxDataViewListStore implementation instead of returning a neutral constant,
// so an unhooked store behaves exactly like a plain one.
//
// Hook argument map, after `data`:
//
//   HasValue            (&item, NULL)                     column -> GetPendingColumn
//   IsEnabledByRow      ((void*)(intptr_t)row, (void*)(intptr_t)col)
//   GetAttrByRow        ((void*)(intptr_t)row, (void*)(intptr_t)col)
//                                                       attr   -> SetGetAttrByRowAttr
//
// The attribute is published with SetGetAttrByRowAttr, which copies it and implies
// success.
//
// The store is reference counted like every wxDataViewModel: a consumer releases it with
// wxDataViewModel_DecRef, never with delete.

class kwxDataViewListStore : public wxDataViewListStore
{
private:
    void* m_object;

    kwxDataViewHookFn m_has_value_hook;
    void* m_has_value_hook_data;
    kwxDataViewHookFn m_is_enabled_by_row_hook;
    void* m_is_enabled_by_row_hook_data;
    kwxDataViewHookFn m_get_attr_by_row_hook;
    void* m_get_attr_by_row_hook_data;

    mutable bool m_published;
    mutable unsigned int m_pending_row;
    mutable unsigned int m_pending_column;
    mutable bool m_result_bool;
    mutable wxDataViewItemAttr m_result_attr;

    void ResetInFlight() const
    {
        m_published = false;
        m_pending_row = 0;
        m_pending_column = 0;
        m_result_bool = false;
        m_result_attr = wxDataViewItemAttr();
    }

public:
    explicit kwxDataViewListStore(void* pObject) : wxDataViewListStore()
    {
        m_object = pObject;
        m_has_value_hook = nullptr;
        m_has_value_hook_data = nullptr;
        m_is_enabled_by_row_hook = nullptr;
        m_is_enabled_by_row_hook_data = nullptr;
        m_get_attr_by_row_hook = nullptr;
        m_get_attr_by_row_hook_data = nullptr;
        ResetInFlight();
    }

    void SetOnHasValueWithData(void* pFunction, void* data)
    {
        m_has_value_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_has_value_hook_data = data;
    }
    void SetOnIsEnabledByRowWithData(void* pFunction, void* data)
    {
        m_is_enabled_by_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_is_enabled_by_row_hook_data = data;
    }
    void SetOnGetAttrByRowWithData(void* pFunction, void* data)
    {
        m_get_attr_by_row_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_attr_by_row_hook_data = data;
    }

    unsigned int GetPendingRow() const { return m_pending_row; }
    unsigned int GetPendingColumn() const { return m_pending_column; }

    void SetHasValueResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetIsEnabledByRowResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetGetAttrByRowResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    // Copies the attribute and implies success, so a port publishes no separate boolean.
    void SetGetAttrByRowAttr(const wxDataViewItemAttr& attr)
    {
        m_result_attr = attr;
        m_result_bool = true;
        m_published = true;
    }

    bool HasValue(const wxDataViewItem& item, unsigned int col) const override
    {
        if (!m_has_value_hook)
        {
            return wxDataViewListStore::HasValue(item, col);
        }
        ResetInFlight();
        m_pending_column = col;
        m_has_value_hook(m_has_value_hook_data, const_cast<wxDataViewItem*>(&item), nullptr);
        return m_published ? m_result_bool : wxDataViewListStore::HasValue(item, col);
    }

    bool IsEnabledByRow(unsigned int row, unsigned int col) const override
    {
        if (!m_is_enabled_by_row_hook)
        {
            return wxDataViewListStore::IsEnabledByRow(row, col);
        }
        ResetInFlight();
        m_pending_row = row;
        m_pending_column = col;
        m_is_enabled_by_row_hook(m_is_enabled_by_row_hook_data, (void*) (intptr_t) row,
                                 (void*) (intptr_t) col);
        return m_published ? m_result_bool : wxDataViewListStore::IsEnabledByRow(row, col);
    }

    bool GetAttrByRow(unsigned int row, unsigned int col, wxDataViewItemAttr& attr) const override
    {
        if (!m_get_attr_by_row_hook)
        {
            return wxDataViewListStore::GetAttrByRow(row, col, attr);
        }
        ResetInFlight();
        m_pending_row = row;
        m_pending_column = col;
        m_get_attr_by_row_hook(m_get_attr_by_row_hook_data, (void*) (intptr_t) row,
                               (void*) (intptr_t) col);
        if (!m_published)
        {
            return wxDataViewListStore::GetAttrByRow(row, col, attr);
        }
        if (m_result_bool)
        {
            attr = m_result_attr;
        }
        return m_result_bool;
    }
};

// ---------------------------------------------------------------------------
// wxDataViewCustomRenderer callbacks
// ---------------------------------------------------------------------------
//
// Same thunk and the same publication rule as the models.  The renderer carries no data
// of its own beyond the in-flight block, so a Render callback reads the cell it must
// paint from GetRenderRect / GetRenderState / GetRenderDC and the value to draw from
// GetCurrentValue.
//
// Activate() and LeftClick() are deprecated in wxWidgets (ActivateCell() replaces both)
// but a port may still implement them, so their overrides are declared here and the
// deprecation warning they raise is suppressed for this block only.
#if defined(_MSC_VER)
    #pragma warning(push)
    #pragma warning(disable : 4996)
#elif defined(__GNUC__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

class kwxDataViewCustomRenderer : public wxDataViewCustomRenderer
{
private:
    void* m_object;

    kwxDataViewHookFn m_render_hook;
    void* m_render_hook_data;
    kwxDataViewHookFn m_get_size_hook;
    void* m_get_size_hook_data;
    kwxDataViewHookFn m_set_value_hook;
    void* m_set_value_hook_data;
    kwxDataViewHookFn m_get_value_hook;
    void* m_get_value_hook_data;
    kwxDataViewHookFn m_activate_cell_hook;
    void* m_activate_cell_hook_data;
    kwxDataViewHookFn m_activate_hook;
    void* m_activate_hook_data;
    kwxDataViewHookFn m_left_click_hook;
    void* m_left_click_hook_data;
    kwxDataViewHookFn m_start_drag_hook;
    void* m_start_drag_hook_data;
    kwxDataViewHookFn m_create_editor_ctrl_hook;
    void* m_create_editor_ctrl_hook_data;
    kwxDataViewHookFn m_get_value_from_editor_ctrl_hook;
    void* m_get_value_from_editor_ctrl_hook_data;
    kwxDataViewHookFn m_validate_hook;
    void* m_validate_hook_data;
    kwxDataViewHookFn m_has_editor_ctrl_hook;
    void* m_has_editor_ctrl_hook_data;
    kwxDataViewHookFn m_accessible_description_hook;
    void* m_accessible_description_hook_data;

    // In-flight block.  GetSize() and GetValue() are const, so the state their callbacks
    // read is mutable.  m_current_value, m_editor_parent and m_editor_ctrl are NOT
    // cleared between calls: Render() runs after SetValue() and needs the value that call
    // stored, and GetEditorParent()/GetEditorCtrl() report what the last CreateEditorCtrl()
    // received and returned.
    mutable bool m_published;
    mutable wxRect m_render_rect;
    mutable int m_render_state;
    mutable wxDC* m_render_dc;
    mutable unsigned int m_pending_column;
    mutable wxRect m_editor_rect;
    mutable wxWindow* m_editor_parent;
    mutable wxWindow* m_editor_ctrl;
    mutable wxVariant m_current_value;
    mutable bool m_result_bool;
    mutable wxSize m_result_size;
    mutable wxVariant m_result_variant;
    mutable wxWindow* m_result_window;
    mutable const wxMouseEvent* m_mouse_event;
    mutable wxPoint m_pending_cursor;
    mutable bool m_cursor_valid;
    mutable bool m_has_editor_value;
    mutable wxString m_accessible_description;

    void ResetInFlight() const;

public:
    kwxDataViewCustomRenderer(void* pObject, const wxString& variantType, wxDataViewCellMode mode,
                              int align);

    void SetOnRenderWithData(void* pFunction, void* data)
    {
        m_render_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_render_hook_data = data;
    }
    void SetOnGetSizeWithData(void* pFunction, void* data)
    {
        m_get_size_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_size_hook_data = data;
    }
    void SetOnSetValueWithData(void* pFunction, void* data)
    {
        m_set_value_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_set_value_hook_data = data;
    }
    void SetOnGetValueWithData(void* pFunction, void* data)
    {
        m_get_value_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_value_hook_data = data;
    }
    void SetOnActivateCellWithData(void* pFunction, void* data)
    {
        m_activate_cell_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_activate_cell_hook_data = data;
    }
    void SetOnActivateWithData(void* pFunction, void* data)
    {
        m_activate_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_activate_hook_data = data;
    }
    void SetOnLeftClickWithData(void* pFunction, void* data)
    {
        m_left_click_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_left_click_hook_data = data;
    }
    void SetOnStartDragWithData(void* pFunction, void* data)
    {
        m_start_drag_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_start_drag_hook_data = data;
    }
    void SetOnCreateEditorCtrlWithData(void* pFunction, void* data)
    {
        m_create_editor_ctrl_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_create_editor_ctrl_hook_data = data;
    }
    void SetOnGetValueFromEditorCtrlWithData(void* pFunction, void* data)
    {
        m_get_value_from_editor_ctrl_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_get_value_from_editor_ctrl_hook_data = data;
    }
    void SetOnValidateWithData(void* pFunction, void* data)
    {
        m_validate_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_validate_hook_data = data;
    }
    void SetOnHasEditorCtrlWithData(void* pFunction, void* data)
    {
        m_has_editor_ctrl_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_has_editor_ctrl_hook_data = data;
    }
    void SetOnGetAccessibleDescriptionWithData(void* pFunction, void* data)
    {
        m_accessible_description_hook = reinterpret_cast<kwxDataViewHookFn>(pFunction);
        m_accessible_description_hook_data = data;
    }

    // RenderText()/GetTextExtent() are protected on wxDataViewCustomRenderer, so a
    // Render()/GetSize() callback can only reach them through these forwarders.  The
    // qualified call is deliberate: it always runs the standard renderer's implementation,
    // never a derived override.
    void CallRenderText(const wxString& text, int xoffset, const wxRect& cell, wxDC* dc, int state)
    {
        wxDataViewCustomRenderer::RenderText(text, xoffset, cell, dc, state);
    }
    wxSize CallGetTextExtent(const wxString& text) const
    {
        return wxDataViewCustomRenderer::GetTextExtent(text);
    }

    wxDC* GetRenderDC() const { return m_render_dc; }
    const wxRect& GetRenderRect() const { return m_render_rect; }
    int GetRenderState() const { return m_render_state; }
    const wxVariant& GetCurrentValue() const { return m_current_value; }
    const wxRect& GetEditorRect() const { return m_editor_rect; }
    wxWindow* GetEditorParent() const { return m_editor_parent; }
    wxWindow* GetEditorCtrl() const { return m_editor_ctrl; }
    unsigned int GetPendingColumn() const { return m_pending_column; }
    // Borrowed: valid only inside the ActivateCell callback that received it.
    const wxMouseEvent* GetActivateCellMouseEvent() const { return m_mouse_event; }
    int GetPendingCursorX() const { return m_pending_cursor.x; }
    int GetPendingCursorY() const { return m_pending_cursor.y; }

    void SetRenderResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetGetSizeResult(const wxSize& size)
    {
        m_result_size = size;
        m_published = true;
    }
    void SetGetValueResult(const wxVariant& value)
    {
        m_result_variant = value;
        m_published = true;
    }
    void SetSetValueResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetActivateCellResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetActivateResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetLeftClickResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetStartDragResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetCreateEditorCtrlResult(wxWindow* editor)
    {
        m_result_window = editor;
        m_published = true;
    }
    void SetGetValueFromEditorCtrlResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    // Publishing the edited value is itself the success signal for GetValueFromEditorCtrl.
    void SetGetValueFromEditorCtrlValue(const wxVariant& value)
    {
        m_result_variant = value;
        m_has_editor_value = true;
    }
    void SetValidateResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    void SetHasEditorCtrlResult(bool result)
    {
        m_result_bool = result;
        m_published = true;
    }
    // Copies on purpose: the callback's string buffer is call-scoped in every binding.
    void SetAccessibleDescription(const wxString& description)
    {
        m_accessible_description = description;
        m_published = true;
    }

    bool Render(wxRect cell, wxDC* draw_dc, int state) override;
    wxSize GetSize() const override;
    bool SetValue(const wxVariant& value) override;
    bool GetValue(wxVariant& value) const override;
    bool ActivateCell(const wxRect& cell, wxDataViewModel* model, const wxDataViewItem& item,
                      unsigned int col, const wxMouseEvent* mouseEvent) override;
    bool Activate(wxRect cell, wxDataViewModel* model, const wxDataViewItem& item,
                  unsigned int col) override;
    bool LeftClick(wxPoint cursor, wxRect cell, wxDataViewModel* model, const wxDataViewItem& item,
                   unsigned int col) override;
    bool StartDrag(const wxPoint& cursor, const wxRect& cell, wxDataViewModel* model,
                   const wxDataViewItem& item, unsigned int col) override;
    wxWindow* CreateEditorCtrl(wxWindow* parent, wxRect labelRect, const wxVariant& value) override;
    bool GetValueFromEditorCtrl(wxWindow* editor, wxVariant& value) override;
    bool Validate(wxVariant& value) override;
    bool HasEditorCtrl() const override;

    // The base declares it pure when wxWidgets was built with accessibility support; a
    // scripted renderer has no descriptive text of its own.
#if wxUSE_ACCESSIBILITY
    wxString GetAccessibleDescription() const override;
#endif
};

#if defined(_MSC_VER)
    #pragma warning(pop)
#elif defined(__GNUC__)
    #pragma GCC diagnostic pop
#endif

// The exported kwx<Base>_* / <Base>_* declarations are NOT in this header.
// kwxgen expands the quoted includes of include/kwx_classes.h, so every
// declaration reachable from there is parsed as a declaration model; a C++ class
// body is not one, and parsing it emitted an "unparsed function" warning for
// every line of every class.  The declarations live in
// include/kwx_hook_exports.h instead — the same helper/declaration split
// include/kwx_combo_extra.h:9-10 documents for the combo helpers.  Both files
// must be kept in step: a hook with a class here and no block there reaches no
// binding.
