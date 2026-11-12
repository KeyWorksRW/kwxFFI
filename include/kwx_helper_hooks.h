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
#include <wx/cmdline.h>
#include <wx/docview.h>
#include <wx/event.h>
#include <wx/filesys.h>
#include <wx/html/htmlpars.h>
#include <wx/html/winpars.h>
#include <wx/htmllbox.h>
#include <wx/log.h>
#include <wx/modalhook.h>
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

protected:
    bool OnCmdLineParsed(wxCmdLineParser& parser) override;
    void OnInitCmdLine(wxCmdLineParser& parser) override;
    int OnExit() override;
    int FilterEvent(wxEvent& event) override;
    wxClassInfo* GetClassInfo() const override;
    void OnAssertFailure(const wxChar* file, int line, const wxChar* func, const wxChar* cond,
                         const wxChar* msg) override;
    wxAppTraits* CreateTraits() override;
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

class kwxStockPreferencesPage : public wxStockPreferencesPage
{
private:
    kwxPreferencesPageWindowFunc m_create_window_func;
    wxWindow* m_result_window;

public:
    explicit kwxStockPreferencesPage(Kind kind) : wxStockPreferencesPage(kind)
    {
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

public:
    explicit kwxDocument(void* pObject);

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

public:
    explicit kwxView(void* pObject);

    void SetOnOnDraw(void* pFunction) { m_on_draw_func = (kwxViewDrawFunc) pFunction; }
    void SetOnOnClose(void* pFunction) { m_on_close_func = (kwxViewCloseFunc) pFunction; }
    void SetOnOnCreate(void* pFunction) { m_on_create_func = (kwxViewCreateFunc) pFunction; }
    void SetOnOnUpdate(void* pFunction) { m_on_update_func = (kwxViewUpdateFunc) pFunction; }

    void OnDraw(wxDC* dc) override;
    bool OnClose(bool deleteWindow) override;
    bool OnCreate(wxDocument* document, long flags) override;
    void OnUpdate(wxView* sender, wxObject* hint) override;
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

// The exported kwx<Base>_* / <Base>_* declarations are NOT in this header.
// kwxgen expands the quoted includes of include/kwx_classes.h, so every
// declaration reachable from there is parsed as a declaration model; a C++ class
// body is not one, and parsing it emitted an "unparsed function" warning for
// every line of every class.  The declarations live in
// include/kwx_hook_exports.h instead — the same helper/declaration split
// include/kwx_combo_extra.h:9-10 documents for the combo helpers.  Both files
// must be kept in step: a hook with a class here and no block there reaches no
// binding.
