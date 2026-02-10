#include "wrapper.h"

#include <wx/generic/logg.h>
#include <wx/log.h>

#include <wx/fileconf.h>
#include <wx/grid.h>
#include <wx/html/htmlwin.h>
#include <wx/listctrl.h>
#include <wx/process.h>
#include <wx/progdlg.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/propgrid.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>

#include <wx/numdlg.h>
#include <wx/power.h>

////////////////////////////////////////////////////////////////////////////////
// wxc specific events
////////////////////////////////////////////////////////////////////////////////

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_LOCAL_EVENT_TYPE(wxEVT_DELETE, 1000)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_HTML_CELL_MOUSE_HOVER, 1002)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_HTML_SET_TITLE, 1004)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_INPUT_SINK, 1005)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_SORT, 1006)
END_DECLARE_EVENT_TYPES()

DEFINE_LOCAL_EVENT_TYPE(wxEVT_DELETE)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_HTML_CELL_MOUSE_HOVER)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_HTML_SET_TITLE)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_INPUT_SINK)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_SORT)

// Exported wxC event wrappers - must be C linkage
extern "C"
{
    MAKE_EVENT_WRAPPER(EVT_DELETE)
    MAKE_EVENT_WRAPPER(EVT_HTML_CELL_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_HTML_CELL_MOUSE_HOVER)
    MAKE_EVENT_WRAPPER(EVT_HTML_LINK_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_HTML_SET_TITLE)
    MAKE_EVENT_WRAPPER(EVT_INPUT_SINK)
    MAKE_EVENT_WRAPPER(EVT_SORT)
}

/*-----------------------------------------------------------------------------
  Timers
-----------------------------------------------------------------------------*/
class wxTimerEx : public wxTimer
{
private:
    wxClosure* m_closure;

public:
    wxTimerEx();
    ~wxTimerEx();

    void Connect(wxClosure* closure);
    wxClosure* GetClosure();
    void Notify();
};

wxTimerEx::wxTimerEx()
{
    m_closure = nullptr;
}

wxTimerEx::~wxTimerEx()
{
    if (m_closure)
    {
        m_closure->DecRef();
        m_closure = nullptr;
    }
}

void wxTimerEx::Connect(wxClosure* closure)
{
    if (m_closure)
        m_closure->DecRef();
    m_closure = closure;
    if (m_closure)
        m_closure->IncRef();
}

wxClosure* wxTimerEx::GetClosure()
{
    return m_closure;
}

void wxTimerEx::Notify()
{
    wxTimerEvent timerEvent(*this);
    if (m_closure)
        m_closure->Invoke(&timerEvent);
}

/*-----------------------------------------------------------------------------
  wxInputSink wrapper: adds non-blocking event driven input channel
-----------------------------------------------------------------------------*/
class wxInputSink;

class wxInputSinkEvent : public wxEvent
{
private:
    char* m_buffer;
    size_t m_bufferLen;
    size_t m_lastRead;
    wxStreamError m_lastError;

    void Read(wxInputStream* input);
    friend class wxInputSink;

public:
    wxInputSinkEvent(int id, size_t bufferLen);
    wxInputSinkEvent(const wxInputSinkEvent& event); /* copy constructor */
    ~wxInputSinkEvent();

    wxEvent* Clone() const { return new wxInputSinkEvent(*this); }

    wxStreamError LastError() const { return m_lastError; }
    int LastRead() const { return m_lastRead; }
    char* LastInput() const { return m_buffer; }
};

class wxInputSink : public wxThread
{
private:
    wxEvtHandler* m_evtHandler;
    wxInputStream* m_input;
    wxInputSinkEvent m_event;

protected:
    ExitCode Entry();

public:
    wxInputSink(wxInputStream* input, wxEvtHandler* evtHandler, int bufferLen);
    ~wxInputSink();

    intptr_t GetId();
    void Start();
};

wxInputSink::wxInputSink(wxInputStream* input, wxEvtHandler* evtHandler, int bufferLen) :
    wxThread(wxTHREAD_DETACHED), m_event(0, bufferLen)
{
    m_input = input;
    m_evtHandler = evtHandler;
}

wxInputSink::~wxInputSink()
{
    /* fprintf(stderr, "InputSink is deleted\n"); */
}

void wxInputSink::Start()
{
    wxThreadError result = Create();
    switch (result)
    {
        case wxTHREAD_NO_ERROR:
            Run();
            break;
        case wxTHREAD_RUNNING:
            break;
        default:
            Delete();
            break;
    }
}

intptr_t wxInputSink::GetId()
{
    return (intptr_t) m_input;
}

wxThread::ExitCode wxInputSink::Entry()
{
    if (m_input == nullptr || m_evtHandler == nullptr || m_event.m_buffer == nullptr)
        return 0;

    m_event.SetId(GetId());

    /* while input && not external destroy */
    while (!TestDestroy() && m_event.LastError() == wxSTREAM_NO_ERROR)
    {
        /* (blocking) read */
        m_event.Read(m_input);

        /* post the event to the main gui thread (note: event is cloned and thus the input buffer
         * copied)*/
        m_evtHandler->AddPendingEvent(m_event);
    }

    /* Process pending events */
    wxWakeUpIdle();

    /* return */
    if (m_event.LastError() == wxSTREAM_NO_ERROR || m_event.LastError() == wxSTREAM_EOF)
        return (ExitCode) 0;
    else
        return (ExitCode) 1;
}

wxInputSinkEvent::wxInputSinkEvent(int id, size_t bufferLen) : wxEvent(id, wxEVT_INPUT_SINK)
{
    m_lastError = wxSTREAM_NO_ERROR;
    m_lastRead = 0;
    if (bufferLen <= 0)
        bufferLen = 128;
    m_buffer = (char*) malloc(bufferLen + 1);
    m_bufferLen = (m_buffer ? bufferLen : 0);
}

wxInputSinkEvent::wxInputSinkEvent(const wxInputSinkEvent& event) : wxEvent(event)
{
    /* we copy only the exact input buffer, as 'Read' will never be called */
    m_lastError = event.m_lastError;
    m_bufferLen = 0;
    m_lastRead = 0;
    m_buffer = (char*) malloc(event.m_lastRead + 1);
    if (m_buffer)
    {
        m_bufferLen = event.m_lastRead;
        m_lastRead = event.m_lastRead;
        memcpy(m_buffer, event.m_buffer, m_lastRead);
        m_buffer[m_lastRead] = 0;
    }
}

wxInputSinkEvent::~wxInputSinkEvent()
{
    if (m_buffer)
        free(m_buffer);
}

void wxInputSinkEvent::Read(wxInputStream* input)
{
    /* check */
    if (input == nullptr || m_buffer == nullptr || m_bufferLen == 0)
    {
        m_lastError = wxSTREAM_READ_ERROR;
        m_lastRead = 0;
        return;
    }

    /* read */
    input->Read(m_buffer, m_bufferLen);
    m_lastError = input->GetLastError();
    if (m_lastError == wxSTREAM_NO_ERROR)
        m_lastRead = input->LastRead();
    else
        m_lastRead = 0;

    /* maintain invariants */
    if (m_lastRead < 0)
        m_lastRead = 0;
    if (m_lastRead > m_bufferLen)
        m_lastRead = m_bufferLen;

    /* add zero terminator */
    m_buffer[m_lastRead] = 0;
}

/*-----------------------------------------------------------------------------
  wxHtmlWindow wrapper: adds normal events instead of using inheritance
-----------------------------------------------------------------------------*/
class wxcHtmlWindow : public wxHtmlWindow
{
private:
    DECLARE_DYNAMIC_CLASS(wxcHtmlWindow)
public:
    wxcHtmlWindow() : wxHtmlWindow() {};
    wxcHtmlWindow(wxWindow*, wxWindowID id, const wxPoint&, const wxSize& size, long style,
                  const wxString&);

    bool OnCellClicked(wxHtmlCell* cell, wxCoord x, wxCoord y, const wxMouseEvent& event);
    void OnCellMouseHover(wxHtmlCell* cell, wxCoord x, wxCoord y);
    void OnLinkClicked(const wxHtmlLinkInfo& link);
    wxHtmlOpeningStatus OnOpeningURL(wxHtmlURLType type, const wxString& url, wxString* redirect);
    void OnSetTitle(const wxString& title);
};

IMPLEMENT_DYNAMIC_CLASS(wxcHtmlWindow, wxHtmlWindow)

class wxcHtmlEvent : public wxCommandEvent
{
private:
    DECLARE_DYNAMIC_CLASS(wxcHtmlEvent)
private:
    const wxMouseEvent* m_mouseEvent;
    const wxHtmlCell* m_htmlCell;
    const wxHtmlLinkInfo* m_linkInfo;
    wxPoint m_logicalPosition;

public:
    wxcHtmlEvent() : wxCommandEvent() {};
    wxcHtmlEvent(wxEventType commandType, int id, const wxMouseEvent* mouseEvent,
                 const wxHtmlCell* htmlCell, const wxHtmlLinkInfo* linkInfo, wxPoint logicalPoint);
    const wxMouseEvent* GetMouseEvent();
    const wxHtmlCell* GetHtmlCell();
    wxString* GetHtmlCellId();
    wxString* GetHref();
    wxString* GetTarget();
    wxPoint GetLogicalPosition();
};

IMPLEMENT_DYNAMIC_CLASS(wxcHtmlEvent, wxCommandEvent)

wxcHtmlWindow::wxcHtmlWindow(wxWindow* prt, wxWindowID id, const wxPoint& pt, const wxSize& size,
                             long style, const wxString& title) :
    wxHtmlWindow(prt, id, pt, size, style, title)
{
}

bool wxcHtmlWindow::OnCellClicked(wxHtmlCell* cell, wxCoord x, wxCoord y, const wxMouseEvent& event)
{
    wxHtmlLinkInfo* linkPtr;
    if (cell == nullptr)
        return false;

    linkPtr = cell->GetLink(x, y);
    if (linkPtr != nullptr)
    {
        wxHtmlLinkInfo link(*linkPtr);
        link.SetEvent(&event);
        link.SetHtmlCell(cell);
        {
            wxcHtmlEvent htmlEvent(wxEVT_HTML_LINK_CLICKED, this->GetId(), &event, cell, &link,
                                   wxPoint(x, y));
            this->ProcessEvent(htmlEvent);
        }
    }
    else
    {
        wxcHtmlEvent htmlEvent(wxEVT_HTML_CELL_CLICKED, this->GetId(), &event, cell, nullptr,
                               wxPoint(x, y));
        this->ProcessEvent(htmlEvent);
    }
    return true;
}

void wxcHtmlWindow::OnCellMouseHover(wxHtmlCell* cell, wxCoord x, wxCoord y)
{
    wxcHtmlEvent htmlEvent(wxEVT_HTML_CELL_MOUSE_HOVER, this->GetId(), nullptr, cell, nullptr,
                           wxPoint(x, y));
    this->ProcessEvent(htmlEvent);
}

void wxcHtmlWindow::OnLinkClicked(const wxHtmlLinkInfo& link)
{
    wxcHtmlEvent htmlEvent(wxEVT_HTML_LINK_CLICKED, this->GetId(), link.GetEvent(),
                           link.GetHtmlCell(), &link, wxPoint(-1, -1));
    this->ProcessEvent(htmlEvent);
}

void wxcHtmlWindow::OnSetTitle(const wxString& title)
{
    wxcHtmlEvent htmlEvent(wxEVT_HTML_SET_TITLE, this->GetId(), nullptr, nullptr, nullptr,
                           wxPoint(-1, -1));
    htmlEvent.SetString(title);
    this->ProcessEvent(htmlEvent);
}

wxcHtmlEvent::wxcHtmlEvent(wxEventType commandType, int id, const wxMouseEvent* mouseEvent,
                           const wxHtmlCell* htmlCell, const wxHtmlLinkInfo* linkInfo,
                           wxPoint logicalPoint) : wxCommandEvent(commandType, id)
{
    m_mouseEvent = mouseEvent;
    m_htmlCell = htmlCell;
    m_linkInfo = linkInfo;
    m_logicalPosition = logicalPoint;
}

const wxMouseEvent* wxcHtmlEvent::GetMouseEvent()
{
    return m_mouseEvent;
}

const wxHtmlCell* wxcHtmlEvent::GetHtmlCell()
{
    return m_htmlCell;
}

wxString* wxcHtmlEvent::GetHtmlCellId()
{
    if (m_htmlCell)
        return new wxString(m_htmlCell->GetId());
    else
        return new wxString("");
}

wxString* wxcHtmlEvent::GetHref()
{
    if (m_linkInfo)
        return new wxString(m_linkInfo->GetHref());
    else
        return new wxString("");
}

wxString* wxcHtmlEvent::GetTarget()
{
    if (m_linkInfo)
        return new wxString(m_linkInfo->GetTarget());
    else
        return new wxString("");
}

wxPoint wxcHtmlEvent::GetLogicalPosition()
{
    return m_logicalPosition;
}

/*-----------------------------------------------------------------------------
  wxGridCellTextEnterEditor
-----------------------------------------------------------------------------*/
class wxGridCellTextEnterEditor : public wxGridCellTextEditor
{
public:
    wxGridCellTextEnterEditor() : wxGridCellTextEditor() {}

    void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler);
};

void wxGridCellTextEnterEditor::Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler)
{
    wxGridCellTextEditor::Create(parent, id, evtHandler);

    {
        long style = m_control->GetWindowStyle();
        m_control->SetWindowStyle(style | wxTE_PROCESS_ENTER);
    }
}

/*-----------------------------------------------------------------------------
  pre processor definitions
-----------------------------------------------------------------------------*/
static const char* defineDefs[] = {
#ifdef __WINDOWS__
    "__WINDOWS__",
#endif  // any Windows, yom may also use
#ifdef __WIN16__
    "__WIN16__",
#endif  // Win16 API
#ifdef __WIN32__
    "__WIN32__",
#endif  // Win32 API
#ifdef __WIN95__
    "__WIN95__",
#endif  // Windows 95 or NT 4.0 and above system (not NT 3.5x)
#ifdef __WXGTK__
    "__WXGTK__",
#endif  // GTK
#ifdef __WXGTK12__
    "__WXGTK12__",
#endif  // GTK 1.2 or higher
#ifdef __WXGTK20__
    "__WXGTK20__",
#endif  // GTK 2.0 or higher
#ifdef __WXMOTIF__
    "__WXMOTIF__",
#endif  // Motif
#ifdef __WXMAC__
    "__WXMAC__",
#endif  // MacOS
#ifdef __WXMGL__
    "__WXMGL__",
#endif  // SciTech Soft MGL
#ifdef __WXUNIVERSAL__
    "__WXUNIVERSAL__",
#endif  // will be also defined)
#ifdef __WXMSW__
    "__WXMSW__",
#endif  // Any Windows
#ifdef __WXOS2__
    "__WXOS2__",
#endif  // OS/2 native Presentation Manager
#ifdef __WXPM__
    "__WXPM__",
#endif  // OS/2 native Presentation Manager
#ifdef __WXSTUBS__
    "__WXSTUBS__",
#endif  // Stubbed version ('template' wxWin implementation)
#ifdef __WXXT__
    "__WXXT__",
#endif  // Xt; mutually exclusive with WX_MOTIF, not implemented in wxWindows 2.x
// wxX11
#ifdef __WXX11__
    "__WXX11__",
#endif
#ifdef __WXUNIVERSAL__
    "__WXUNIVERSAL__",
#endif  // will be also defined)
#ifdef __WXWINE__
    "__WXWINE__",
#endif  // WINE (i.e. Win32 on Unix)
#ifdef __WXUNIVERSAL__
    "__WXUNIVERSAL__",
#endif  // wxUniversal port, always defined in addition to one of the symbols above so this should
        // be tested first.
#ifdef __X__
    "__X__",
#endif  // any X11-based GUI toolkit except GTK+

// any Mac OS version
#ifdef __APPLE__
    "__APPLE__",
#endif
// AIX
#ifdef __AIX__
    "__AIX__",
#endif
// Any BSD
#ifdef __BSD__
    "__BSD__",
#endif
// Cygwin: Unix on Win32
#ifdef __CYGWIN__
    "__CYGWIN__",
#endif
// Mac OS X
#ifdef __DARWIN__
    "__DARWIN__",
#endif
#ifdef ____DATA_GENERAL____
    "__DATA_GENERAL__",
#endif
// DOS (used with wxMGL only)
#ifdef __DOS_GENERAL__
    "__DOS_GENERAL__",
#endif
// FreeBSD
#ifdef __FREEBSD__
    "__FREEBSD__",
#endif
// HP-UX (Unix)
#ifdef ____HPUX____
    "__HPUX__",
#endif
// Linux
#ifdef __LINUX__
    "__LINUX__",
#endif
// OSF/1
#ifdef __OSF__
    "__OSF__",
#endif
// IRIX
#ifdef __SGI__
    "__SGI__",
#endif
// Solaris
#ifdef __SOLARIS__
    "__SOLARIS__",
#endif
// Any Sun
#ifdef __SUN__
    "__SUN__",
#endif
// Sun OS
#ifdef __SUNOS__
    "__SUNOS__",
#endif
// SystemV R4
#ifdef __SVR4__
    "__SVR4__",
#endif
// SystemV generic
#ifdef __SYSV__
    "__SYSV__",
#endif
// Ultrix
#ifdef __ULTRIX__
    "__ULTRIX__",
#endif
// any Unix
#ifdef __UNIX__
    "__UNIX__",
#endif
// Unix, BeOS or VMS
#ifdef __UNIX_LIKE__
    "__UNIX_LIKE__",
#endif
// VMS
#ifdef __VMS__
    "__VMS__",
#endif
// any Windows
#ifdef __WINDOWS__
    "__WINDOWS__",
#endif

// DEC Alpha architecture
#ifdef __ALPHA__
    "__ALPHA__",
#endif
// Intel i386 or compatible
#ifdef __INTEL__
    "__INTEL__",
#endif
// Motorola Power PC
#ifdef __POWERPC__
    "__POWERPC__",
#endif

// Borland C++
#ifdef __BORLANDC__
    "__BORLANDC__",
#endif
// DJGPP
#ifdef __DJGPP__
    "__DJGPP__",
#endif
// Gnu C++ on any platform
#ifdef __GNUG__
    "__GNUG__",
#endif
// GnuWin32 compiler
#ifdef __GNUWIN32__
    "__GNUWIN32__",
#endif
// CodeWarrior MetroWerks compiler
#ifdef __MWERKS__
    "__MWERKS__",
#endif
// Sun CC
#ifdef __SUNCC__
    "__SUNCC__",
#endif
// Symantec C++
#ifdef __SYMANTECC__
    "__SYMANTECC__",
#endif
// IBM Visual Age (OS/2)
#ifdef __VISAGECPP__
    "__VISAGECPP__",
#endif
// Microsoft Visual C++
#ifdef __VISUALC__
    "__VISUALC__",
#endif
// AIX compiler
#ifdef __XLC__
    "__XLC__",
#endif
// Watcom C++
#ifdef __WATCOMC__
    "__WATCOMC__",
#endif
    nullptr
};

static const char* useDefs[] = {
#ifdef wxUSE_UNIX
    "UNIX",
#endif
#ifdef wxUSE_NANOX
    "NANOX",
#endif
#ifdef wxUSE_NATIVE_STATUSBAR
    "NATIVE_STATUSBAR",
#endif
#ifdef wxUSE_OWNER_DRAWN
    "OWNER_DRAWN",
#endif
#ifdef wxUSE_OWNER_DRAWN
    "OWNER_DRAWN",
#endif
#ifdef wxUSE_RICHEDIT
    "RICHEDIT",
#endif
#ifdef wxUSE_RICHEDIT
    "RICHEDIT",
#endif
#ifdef wxUSE_REGEX
    "REGEX",
#endif
#ifdef wxUSE_ZLIB
    "ZLIB",
#endif
#ifdef wxUSE_LIBPNG
    "LIBPNG",
#endif
#ifdef wxUSE_LIBJPEG
    "LIBJPEG",
#endif
#ifdef wxUSE_LIBTIFF
    "LIBTIFF",
#endif
#ifdef wxUSE_ODBC
    "ODBC",
#endif
#ifdef wxUSE_FREETYPE
    "FREETYPE",
#endif
#ifdef wxUSE_THREADS
    "THREADS",
#endif
#if defined(wxcREFUSE_OPENGL)
    #undef wxUSE_OPENGL
    #undef wxUSE_GLCANVAS
#endif
#ifdef wxUSE_OPENGL
    "OPENGL",
#endif
#ifdef wxUSE_GLCANVAS
    "GLCANVAS",
#endif
#ifdef wxUSE_GUI
    "GUI",
#endif
#ifdef wxUSE_NOGUI
    "NOGUI",
#endif
#ifdef wxUSE_ON_FATAL_EXCEPTION
    "ON_FATAL_EXCEPTION",
#endif
#ifdef wxUSE_SNGLINST_CHECKER
    "SNGLINST_CHECKER",
#endif
#ifdef wxUSE_CONSTRAINTS
    "CONSTRAINTS",
#endif
#ifdef wxUSE_VALIDATORS
    "VALIDATORS",
#endif
#ifdef wxUSE_CONTROLS
    "CONTROLS",
#endif
#ifdef wxUSE_POPUPWIN
    "POPUPWIN",
#endif
#ifdef wxUSE_TIPWINDOW
    "TIPWINDOW",
#endif
#ifdef wxUSE_ACCEL
    "ACCEL",
#endif
#ifdef wxUSE_CALENDARCTRL
    "CALENDARCTRL",
#endif
#ifdef wxUSE_FILEDLG
    "FILEDLG",
#endif
#ifdef wxUSE_FINDREPLDLG
    "FINDREPLDLG",
#endif
#ifdef wxUSE_FONTDLG
    "FONTDLG",
#endif
#ifdef wxUSE_MIMETYPE
    "MIMETYPE",
#endif
#ifdef wxUSE_SYSTEM_OPTIONS
    "SYSTEM_OPTIONS",
#endif
#ifdef wxUSE_MSGDLG
    "MSGDLG",
#endif
#ifdef wxUSE_NUMBERDLG
    "NUMBERDLG",
#endif
#ifdef wxUSE_TEXTDLG
    "TEXTDLG",
#endif
#ifdef wxUSE_STARTUP_TIPS
    "STARTUP_TIPS",
#endif
#ifdef wxUSE_PROGRESSDLG
    "PROGRESSDLG",
#endif
#ifdef wxUSE_CHOICEDLG
    "CHOICEDLG",
#endif
#ifdef wxUSE_COLOURDLG
    "COLOURDLG",
#endif
#ifdef wxUSE_DIRDLG
    "DIRDLG",
#endif
#ifdef wxUSE_DRAGIMAGE
    "DRAGIMAGE",
#endif
#ifdef wxUSE_PROPSHEET
    "PROPSHEET",
#endif
#ifdef wxUSE_WIZARDDLG
    "WIZARDDLG",
#endif
#ifdef wxUSE_SPLASH
    "SPLASH",
#endif
#ifdef wxUSE_JOYSTICK
    "JOYSTICK",
#endif
#ifdef wxUSE_BUTTON
    "BUTTON",
#endif
#ifdef wxUSE_CARET
    "CARET",
#endif
#ifdef wxUSE_BMPBUTTON
    "BMPBUTTON",
#endif
#ifdef wxUSE_CHECKBOX
    "CHECKBOX",
#endif
#ifdef wxUSE_CHECKLISTBOX
    "CHECKLISTBOX",
#endif
#ifdef wxUSE_COMBOBOX
    "COMBOBOX",
#endif
#ifdef wxUSE_CHOICE
    "CHOICE",
#endif
#ifdef wxUSE_GAUGE
    "GAUGE",
#endif
#ifdef wxUSE_GRID
    "GRID",
#endif
#ifdef wxUSE_NEW_GRID
    "NEW_GRID",
#endif
#ifdef wxUSE_IMAGLIST
    "IMAGLIST",
#endif
#ifdef wxUSE_LISTBOX
    "LISTBOX",
#endif
#ifdef wxUSE_LISTCTRL
    "LISTCTRL",
#endif
#ifdef wxUSE_MENUS
    "MENUS",
#endif
#ifdef wxUSE_NOTEBOOK
    "NOTEBOOK",
#endif
#ifdef wxUSE_RADIOBOX
    "RADIOBOX",
#endif
#ifdef wxUSE_RADIOBTN
    "RADIOBTN",
#endif
#ifdef wxUSE_SASH
    "SASH",
#endif
#ifdef wxUSE_SCROLLBAR
    "SCROLLBAR",
#endif
#ifdef wxUSE_SLIDER
    "SLIDER",
#endif
#ifdef wxUSE_SPINBTN
    "SPINBTN",
#endif
#ifdef wxUSE_SPINCTRL
    "SPINCTRL",
#endif
#ifdef wxUSE_SPLITTER
    "SPLITTER",
#endif
#ifdef wxUSE_STATBMP
    "STATBMP",
#endif
#ifdef wxUSE_STATBOX
    "STATBOX",
#endif
#ifdef wxUSE_STATLINE
    "STATLINE",
#endif
#ifdef wxUSE_STATTEXT
    "STATTEXT",
#endif
#ifdef wxUSE_STATUSBAR
    "STATUSBAR",
#endif
#ifdef wxUSE_TOGGLEBTN
    "TOGGLEBTN",
#endif
#ifdef wxUSE_TAB_DIALOG
    "TAB_DIALOG",
#endif
#ifdef wxUSE_TABDIALOG
    "TABDIALOG",
#endif
#ifdef wxUSE_TEXTCTRL
    "TEXTCTRL",
#endif
#ifdef wxUSE_TOOLBAR
    "TOOLBAR",
#endif
#ifdef wxUSE_TOOLBAR_NATIVE
    "TOOLBAR_NATIVE",
#endif
#ifdef wxUSE_TOOLBAR_SIMPLE
    "TOOLBAR_SIMPLE",
#endif
#ifdef wxUSE_BUTTONBAR
    "BUTTONBAR",
#endif
#ifdef wxUSE_TREELAYOUT
    "TREELAYOUT",
#endif
#ifdef wxUSE_TREECTRL
    "TREECTRL",
#endif
#ifdef wxUSE_LONGLONG
    "LONGLONG",
#endif
#ifdef wxUSE_GEOMETRY
    "GEOMETRY",
#endif
#ifdef wxUSE_CMDLINE_PARSER
    "CMDLINE_PARSER",
#endif
#ifdef wxUSE_DATETIME
    "DATETIME",
#endif
#ifdef wxUSE_FILE
    "FILE",
#endif
#ifdef wxUSE_FFILE
    "FFILE",
#endif
#ifdef wxUSE_FSVOLUME
    "FSVOLUME",
#endif
#ifdef wxUSE_TEXTBUFFER
    "TEXTBUFFER",
#endif
#ifdef wxUSE_TEXTFILE
    "TEXTFILE",
#endif
#ifdef wxUSE_LOG
    "LOG",
#endif
#ifdef wxUSE_LOGWINDOW
    "LOGWINDOW",
#endif
#ifdef wxUSE_LOGGUI
    "LOGGUI",
#endif
#ifdef wxUSE_LOG_DIALOG
    "LOG_DIALOG",
#endif
#ifdef wxUSE_STOPWATCH
    "STOPWATCH",
#endif
#ifdef wxUSE_TIMEDATE
    "TIMEDATE",
#endif
#ifdef wxUSE_WAVE
    "WAVE",
#endif
#ifdef wxUSE_SOUND
    "SOUND",
#endif
#ifdef wxUSE_CONFIG
    "CONFIG",
#endif
#ifdef wxUSE_FONTMAP
    "FONTMAP",
#endif
#ifdef wxUSE_INTL
    "INTL",
#endif
#ifdef wxUSE_PROTOCOL
    "PROTOCOL",
#endif
#ifdef wxUSE_PROTOCOL_FILE
    "PROTOCOL_FILE",
#endif
#ifdef wxUSE_PROTOCOL_FTP
    "PROTOCOL_FTP",
#endif
#ifdef wxUSE_PROTOCOL_HTTP
    "PROTOCOL_HTTP",
#endif
#ifdef wxUSE_STREAMS
    "STREAMS",
#endif
#ifdef wxUSE_SOCKETS
    "SOCKETS",
#endif
#ifdef wxUSE_DIALUP_MANAGER
    "DIALUP_MANAGER",
#endif
#ifdef wxUSE_STD_IOSTREAM
    "STD_IOSTREAM",
#endif
#ifdef wxUSE_DYNLIB_CLASS
    "DYNLIB_CLASS",
#endif
#ifdef wxUSE_DYNAMIC_LOADER
    "DYNAMIC_LOADER",
#endif
#ifdef wxUSE_TIMER
    "TIMER",
#endif
#ifdef wxUSE_AFM_FOR_POSTSCRIPT
    "AFM_FOR_POSTSCRIPT",
#endif
#ifdef wxUSE_NORMALIZED_PS_FONTS
    "NORMALIZED_PS_FONTS",
#endif
#ifdef wxUSE_POSTSCRIPT
    "POSTSCRIPT",
#endif
#ifdef wxUSE_WCHAR_T
    "WCHAR_T",
#endif
#ifdef wxUSE_UNICODE
    "UNICODE",
#endif
#ifdef wxUSE_UNICODE_MSLU
    "UNICODE_MSLU",
#endif
#ifdef wxUSE_URL
    "URL",
#endif
#ifdef wxUSE_WCSRTOMBS
    "WCSRTOMBS",
#endif
#ifdef wxUSE_EXPERIMENTAL_
    "EXPERIMENTAL_PRINTF",
#endif
#ifdef wxUSE_IPC
    "IPC",
#endif
#ifdef wxUSE_X_RESOURCES
    "X_RESOURCES",
#endif
#ifdef wxUSE_CLIPBOARD
    "CLIPBOARD",
#endif
#ifdef wxUSE_DATAOBJ
    "DATAOBJ",
#endif
#ifdef wxUSE_TOOLTIPS
    "TOOLTIPS",
#endif
#ifdef wxUSE_DRAG_AND_DROP
    "DRAG_AND_DROP",
#endif
#ifdef wxUSE_OLE
    "OLE",
#endif
#ifdef wxUSE_SPLINES
    "SPLINES",
#endif
#ifdef wxUSE_MDI_ARCHITECTURE
    "MDI_ARCHITECTURE",
#endif
#ifdef wxUSE_DOC_VIEW_ARCHITECTURE
    "DOC_VIEW_ARCHITECTURE",
#endif
#ifdef wxUSE_PRINTING_ARCHITECTURE
    "PRINTING_ARCHITECTURE",
#endif
#ifdef wxUSE_PROLOGIO
    "PROLOGIO",
#endif
#ifdef wxUSE_RESOURCES
    "RESOURCES",
#endif
#ifdef wxUSE_WX_RESOURCES
    "WX_RESOURCES",
#endif
#ifdef wxUSE_HELP
    "HELP",
#endif
#ifdef wxUSE_WXHTML_HELP
    "WXHTML_HELP",
#endif
#ifdef wxUSE_MS_HTML_HELP
    "MS_HTML_HELP",
#endif
#ifdef wxUSE_IOSTREAMH
    "IOSTREAMH",
#endif
#ifdef wxUSE_APPLE_IEEE
    "APPLE_IEEE",
#endif
#ifdef wxUSE_MEMORY_TRACING
    "MEMORY_TRACING",
#endif
#ifdef wxUSE_DEBUG_NEW_ALWAYS
    "DEBUG_NEW_ALWAYS",
#endif
#ifdef wxUSE_DEBUG_CONTEXT
    "DEBUG_CONTEXT",
#endif
#ifdef wxUSE_GLOBAL_MEMORY_OPERATORS
    "GLOBAL_MEMORY_OPERATORS",
#endif
#ifdef wxUSE_SPLINES
    "SPLINES",
#endif
#ifdef wxUSE_DYNAMIC_CLASSES
    "DYNAMIC_CLASSES",
#endif
#ifdef wxUSE_METAFILE
    "METAFILE",
#endif
#ifdef wxUSE_ENH_METAFILE
    "ENH_METAFILE",
#endif
#ifdef wxUSE_MINIFRAME
    "MINIFRAME",
#endif
#ifdef wxUSE_HTML
    "HTML",
#endif
#ifdef wxUSE_FILESYSTEM
    "FILESYSTEM",
#endif
#ifdef wxUSE_FS_INET
    "FS_INET",
#endif
#ifdef wxUSE_FS_ZIP
    "FS_ZIP",
#endif
#ifdef wxUSE_BUSYINFO
    "BUSYINFO",
#endif
#ifdef wxUSE_ZIPSTREAM
    "ZIPSTREAM",
#endif
#ifdef wxUSE_PALETTE
    "PALETTE",
#endif
#ifdef wxUSE_IMAGE
    "IMAGE",
#endif
#ifdef wxUSE_GIF
    "GIF",
#endif
#ifdef wxUSE_PCX
    "PCX",
#endif
#ifdef wxUSE_IFF
    "IFF",
#endif
#ifdef wxUSE_PNM
    "PNM",
#endif
#ifdef wxUSE_XPM
    "XPM",
#endif
#ifdef wxUSE_ICO_CUR
    "ICO_CUR",
#endif

// detect using optional libraries in the contrib hierarchy.
#ifdef wxUSE_STC
    "STC",
#endif
    nullptr
};

static const char* hasDefs[] = {
#ifdef wxHAS_POWER_EVENTS
    "POWER_EVENTS",
#endif
#ifdef wxHAS_RADIO_MENU_ITEMS
    "RADIO_MENU_ITEMS",
#endif
    nullptr
};

/*-----------------------------------------------------------------------------
  EXTERN C
-----------------------------------------------------------------------------*/
extern "C"
{
    /*-----------------------------------------------------------------------------
      String
    -----------------------------------------------------------------------------*/
    typedef char utf8char;

    EXPORT wxString* wxString_Create(char* buffer)
    {
        return new wxString(buffer);
    }

    EXPORT wxString* wxString_CreateUTF8(utf8char* buffer)
    {
        return new wxString(buffer, wxConvUTF8);
    }

    EXPORT wxString* wxString_CreateLen(char* buffer, int len)
    {
        return new wxString(buffer, len);
    }

    EXPORT void wxString_Delete(wxString* s)
    {
        delete s;
    }

    EXPORT int wxString_GetString(wxString* s, char* buffer)
    {
        if (buffer)
            memcpy(buffer, s->utf8_str().data(), s->Length());
        return s->Length();
    }

    EXPORT size_t wxString_Length(wxString* s)
    {
        return s->length();
    }

    EXPORT wxCharBuffer* wxString_GetUtf8(wxString* s)
    {
        wxCharBuffer* cb = new wxCharBuffer;
        *cb = s->utf8_str();
        return cb;
    }

    EXPORT utf8char* wxCharBuffer_DataUtf8(wxCharBuffer* cb)
    {
        return (utf8char*) cb->data();
    }

    EXPORT void wxCharBuffer_Delete(wxCharBuffer* cb)
    {
        delete cb;
    }
    /*-----------------------------------------------------------------------------
      Point
    -----------------------------------------------------------------------------*/
    EXPORT void* wxPoint_Create(int x, int y)
    {
        return new wxPoint(x, y);
    }

    EXPORT void wxPoint_Delete(void* p)
    {
        delete (wxPoint*) p;
    }

    EXPORT int wxPoint_GetX(void* p)
    {
        return ((wxPoint*) p)->x;
    }

    EXPORT int wxPoint_GetY(void* p)
    {
        return ((wxPoint*) p)->y;
    }

    EXPORT void wxPoint_SetX(void* p, int x)
    {
        ((wxPoint*) p)->x = x;
    }

    EXPORT void wxPoint_SetY(void* p, int y)
    {
        ((wxPoint*) p)->y = y;
    }

    /*-----------------------------------------------------------------------------
      Size
    -----------------------------------------------------------------------------*/
    EXPORT void* wxSize_Create(int w, int h)
    {
        return new wxSize(w, h);
    }

    EXPORT void wxSize_Delete(void* s)
    {
        delete (wxSize*) s;
    }

    EXPORT int wxSize_GetWidth(void* s)
    {
        return ((wxSize*) s)->GetWidth();
    }

    EXPORT int wxSize_GetHeight(void* s)
    {
        return ((wxSize*) s)->GetHeight();
    }

    EXPORT void wxSize_SetWidth(wxSize* s, int w)
    {
        s->SetWidth(w);
    }

    EXPORT void wxSize_SetHeight(wxSize* s, int h)
    {
        s->SetHeight(h);
    }

    /*-----------------------------------------------------------------------------
      Rect
    -----------------------------------------------------------------------------*/
    EXPORT void* wxRect_Create(int x, int y, int w, int h)
    {
        return new wxRect(x, y, w, h);
    }

    EXPORT void wxRect_Delete(void* r)
    {
        delete (wxRect*) r;
    }

    EXPORT int wxRect_GetX(wxRect* r)
    {
        return r->GetX();
    }

    EXPORT int wxRect_GetY(wxRect* r)
    {
        return r->GetY();
    }

    EXPORT int wxRect_GetWidth(wxRect* r)
    {
        return r->GetWidth();
    }

    EXPORT int wxRect_GetHeight(wxRect* r)
    {
        return r->GetHeight();
    }

    EXPORT void wxRect_SetX(wxRect* r, int x)
    {
        r->SetX(x);
    }

    EXPORT void wxRect_SetY(wxRect* r, int y)
    {
        r->SetY(y);
    }

    EXPORT void wxRect_SetWidth(wxRect* r, int w)
    {
        r->SetWidth(w);
    }

    EXPORT void wxRect_SetHeight(wxRect* r, int h)
    {
        r->SetHeight(h);
    }

    /*-----------------------------------------------------------------------------
      pre-processor
    -----------------------------------------------------------------------------*/
    EXPORT int wxVersionNumber()
    {
        return wxVERSION_NUMBER;
    }

    EXPORT wxString* wxVersionString()
    {
        return new wxString(wxVERSION_STRING);
    }

    EXPORT int wxIsDefined(char* s)
    {
        int i;
        if (s == nullptr)
            return 0;
        /* check define */
        for (i = 0; defineDefs[i] != nullptr; i++)
        {
            if (strcmp(s, defineDefs[i]) == 0)
                return 1;
        }
        /* check wxUSE_XXX */
        if (strncmp(s, "wxUSE_", 6) == 0)
        {
            const char* t = s + 6;
            for (i = 0; useDefs[i] != nullptr; i++)
            {
                if (strcmp(t, useDefs[i]) == 0)
                    return 1;
            }
        }
        /* check wxHAS_XXX */
        if (strncmp(s, "wxHAS_", 6) == 0)
        {
            const char* t = s + 6;
            for (i = 0; hasDefs[i] != nullptr; i++)
            {
                if (strcmp(t, hasDefs[i]) == 0)
                    return 1;
            }
        }
        return 0;
    }

    EXPORT void* wxcMalloc(int size)
    {
        return malloc(size);
    }

    EXPORT void wxcFree(void* p)
    {
        if (p != nullptr)
            free(p);
    }

    EXPORT wxColour* wxcSystemSettingsGetColour(int systemColour)
    {
        wxColour* colour = new wxColour();
        *colour = wxSystemSettings::GetColour((wxSystemColour) systemColour);
        return colour;
    }

    EXPORT void wxcWakeUpIdle(void)
    {
        wxWakeUpIdle();
    }

    /*-----------------------------------------------------------------------------
      delete
    -----------------------------------------------------------------------------*/
    EXPORT void wxCursor_Delete(wxCursor* self)
    {
        delete self;
    }

    EXPORT void wxDateTime_Delete(wxDateTime* self)
    {
        delete self;
    }

    /*-----------------------------------------------------------------------------
      frame
    -----------------------------------------------------------------------------*/
    EXPORT wxString* wxFrame_GetTitle(wxFrame* self)
    {
        wxString* result = new wxString();
        *result = self->GetTitle();
        return result;
    }

    EXPORT void wxFrame_SetTitle(wxFrame* self, wxString* text)
    {
        self->SetTitle(*text);
    }

    EXPORT bool wxFrame_SetShape(wxFrame* self, wxRegion* region)
    {
        return self->SetShape(*region);
    }

    EXPORT bool wxFrame_ShowFullScreen(wxFrame* self, bool show, int style)
    {
        return self->ShowFullScreen(show, style);
    }

    EXPORT bool wxFrame_IsFullScreen(wxFrame* self)
    {
        return self->IsFullScreen();
    }

    EXPORT void wxFrame_Centre(wxFrame* self, int orientation)
    {
        self->Centre();
    }

    EXPORT void wxNotebook_AssignImageList(wxNotebook* self, wxImageList* imageList)
    {
        self->AssignImageList(imageList);
    }

    /*-----------------------------------------------------------------------------
      menu & toolbar
    -----------------------------------------------------------------------------*/
    EXPORT wxMenuBar* wxMenu_GetMenuBar(wxMenu* self)
    {
        return self->GetMenuBar();
    }

    EXPORT wxFrame* wxMenuBar_GetFrame(wxMenuBar* self)
    {
        return self->GetFrame();
    }

    EXPORT void wxToolBar_AddTool2(wxToolBar* self, int toolId, wxString* label, wxBitmap* bmp,
                                   wxBitmap* bmpDisabled, int itemKind, wxString* shortHelp,
                                   wxString* longHelp)
    {
        self->AddTool(toolId, *label, *bmp, *bmpDisabled, (wxItemKind) itemKind, *shortHelp,
                      *longHelp, nullptr);
    }

    /*-----------------------------------------------------------------------------
      listctrl
    -----------------------------------------------------------------------------*/
    EXPORT int wxListEvent_GetCacheFrom(wxListEvent* self)
    {
        return self->GetCacheFrom();
    }

    EXPORT int wxListEvent_GetCacheTo(wxListEvent* self)
    {
        return self->GetCacheTo();
    }

    EXPORT void wxListCtrl_AssignImageList(wxListCtrl* self, wxImageList* images, int which)
    {
        self->AssignImageList(images, which);
    }

    EXPORT void wxListCtrl_GetColumn2(wxListCtrl* self, int col, wxListItem* item)
    {
        bool success = self->GetColumn(col, *item);
        if (!success)
            item->SetId(-1);
    }

    EXPORT void wxListCtrl_GetItem2(wxListCtrl* self, wxListItem* info)
    {
        bool success = self->GetItem(*info);
        if (!success)
            info->SetId(-1);
    }

    EXPORT wxPoint* wxListCtrl_GetItemPosition2(wxListCtrl* self, int item)
    {
        wxPoint* pos = new wxPoint();
        bool success = self->GetItemPosition((long) item, *pos);
        if (success)
        {
            return pos;
        }
        else
        {
            delete pos;
            wxPoint* pt = new wxPoint(-1, -1);
            return pt;
        }
    }

    struct SortData
    {
        long id;
        wxClosure* closure;
    };

    int wxCALLBACK sortCallBack(wxIntPtr item1, wxIntPtr item2, wxIntPtr data)
    {
        wxClosure* closure = ((SortData*) data)->closure;
        long id = ((SortData*) data)->id;

        wxCommandEvent event(wxEVT_SORT, id);
        event.SetInt(item1);
        event.SetExtraLong(item2);
        closure->Invoke(&event);
        return event.GetInt();
    }

    EXPORT bool wxListCtrl_SortItems2(wxListCtrl* self, wxClosure* closure)
    {
        SortData sortData = { self->GetId(), closure };
        return self->SortItems(sortCallBack, (wxIntPtr) &sortData);
    }

    /*-----------------------------------------------------------------------------
      DC
    -----------------------------------------------------------------------------*/
    EXPORT void wxDC_GetPixel2(wxDC* self, int x, int y, wxColour* col)
    {
        bool success = self->GetPixel((wxCoord) x, (wxCoord) y, col);
        if (!success)
            *col = wxNullColour;
    }

    /*-----------------------------------------------------------------------------
      Object & static ClassInfo
    -----------------------------------------------------------------------------*/
    EXPORT bool wxObject_IsKindOf(wxObject* self, wxClassInfo* classInfo)
    {
        return self->IsKindOf(classInfo);
    }

    EXPORT wxClassInfo* wxObject_GetClassInfo(wxObject* self)
    {
        return self->GetClassInfo();
    }

    /* optimize */
    EXPORT bool wxObject_IsScrolledWindow(wxObject* self)
    {
        return self->IsKindOf(CLASSINFO(wxScrolledWindow));
    }

    EXPORT void wxObject_Delete(wxObject* self)
    {
        delete self;
    }

    /*-----------------------------------------------------------------------------
      classinfo
    -----------------------------------------------------------------------------*/
    EXPORT wxClassInfo* wxClassInfo_FindClass(wxString* name)
    {
        return wxClassInfo::FindClass(*name);
    }

    EXPORT wxString* wxClassInfo_GetClassNameEx(wxClassInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetClassName();
        return result;
    }

    EXPORT wxString* wxClassInfo_GetBaseClassName1(wxClassInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetBaseClassName1();
        return result;
    }

    EXPORT wxString* wxClassInfo_GetBaseClassName2(wxClassInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetBaseClassName2();
        return result;
    }

    EXPORT bool wxClassInfo_IsKindOfEx(wxClassInfo* self, wxClassInfo* classInfo)
    {
        return self->IsKindOf(classInfo);
    }

    EXPORT int wxClassInfo_GetSize(wxClassInfo* self)
    {
        return (self)->GetSize();
    }

    /*-----------------------------------------------------------------------------
      window
    -----------------------------------------------------------------------------*/
    EXPORT wxPoint* wxWindow_ConvertPixelsToDialogEx(wxWindow* self, int x, int y)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->ConvertPixelsToDialog(wxPoint(x, y));
        return pt;
    }

    EXPORT wxPoint* wxWindow_ConvertDialogToPixelsEx(wxWindow* self, int x, int y)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->ConvertDialogToPixels(wxPoint(x, y));
        return pt;
    }

    EXPORT void wxWindow_SetClientObject(wxWindow* self, wxClientData* obj)
    {
        self->SetClientObject(obj);
    }

    EXPORT wxPoint* wxWindow_ScreenToClient2(wxWindow* self, int x, int y)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->ScreenToClient(wxPoint(x, y));
        return pt;
    }

    EXPORT wxPoint* wxcGetMousePosition()
    {
        wxPoint* pt = new wxPoint();
        *pt = wxGetMousePosition();
        return pt;
    }

    /*-----------------------------------------------------------------------------
      scrolledwindow
    -----------------------------------------------------------------------------*/
    EXPORT void wxScrolledWindow_SetScrollRate(wxScrolledWindow* self, int xstep, int ystep)
    {
        self->SetScrollRate(xstep, ystep);
    }

    /*-----------------------------------------------------------------------------
      mouse
    -----------------------------------------------------------------------------*/
    EXPORT int wxMouseEvent_GetWheelDelta(wxMouseEvent* self)
    {
        return self->GetWheelDelta();
    }

    EXPORT int wxMouseEvent_GetWheelRotation(wxMouseEvent* self)
    {
        return self->GetWheelRotation();
    }

    EXPORT int wxMouseEvent_GetButton(wxMouseEvent* self)
    {
        return self->GetButton();
    }

    /*-----------------------------------------------------------------------------
      DC
    -----------------------------------------------------------------------------*/
    EXPORT double wxDC_GetUserScaleX(wxDC* dc)
    {
        double x = 1.0;
        double y = 1.0;
        dc->GetUserScale(&x, &y);
        return x;
    }

    EXPORT double wxDC_GetUserScaleY(wxDC* dc)
    {
        double x = 1.0;
        double y = 1.0;
        dc->GetUserScale(&x, &y);
        return y;
    }

    /*-----------------------------------------------------------------------------
      timers
    -----------------------------------------------------------------------------*/
    EXPORT wxTimerEx* wxTimerEx_Create()
    {
        return new wxTimerEx();
    }

    EXPORT void wxTimerEx_Connect(wxTimerEx* self, wxClosure* closure)
    {
        self->Connect(closure);
    }

    EXPORT wxClosure* wxTimerEx_GetClosure(wxTimerEx* self)
    {
        return self->GetClosure();
    }

    /*-----------------------------------------------------------------------------
      menu items
    -----------------------------------------------------------------------------*/
    EXPORT wxMenuItem* wxMenuItem_CreateSeparator()
    {
        return new wxMenuItem(nullptr, wxID_SEPARATOR, "", "", wxITEM_SEPARATOR, nullptr);
    }

    EXPORT wxMenuItem* wxMenuItem_CreateEx(int id, wxString* text, wxString* helpstr, int itemkind,
                                           wxMenu* submenu)
    {
        return new wxMenuItem(nullptr, id, *text, *helpstr, (wxItemKind) itemkind, submenu);
    }

    EXPORT void wxMenu_AppendRadioItem(wxMenu* self, int id, wxString* text, wxString* help)
    {
#ifdef wxHAS_RADIO_MENU_ITEMS
        self->AppendRadioItem(id, *text, *help);
#else
        self->AppendCheckItem(id, *text, *help);
#endif
    }

    /*------------------------------------------------------------------------------
      process
    ------------------------------------------------------------------------------*/
    EXPORT bool wxProcess_IsErrorAvailable(wxProcess* self)
    {
        return self->IsErrorAvailable();
    }

    EXPORT bool wxProcess_IsInputAvailable(wxProcess* self)
    {
        return self->IsInputAvailable();
    }

    EXPORT bool wxProcess_IsInputOpened(wxProcess* self)
    {
        return self->IsInputOpened();
    }

    EXPORT wxProcess* wxProcess_Open(wxString* cmd, int flags)
    {
        return wxProcess::Open(*cmd, ((flags | wxEXEC_ASYNC) & ~wxEXEC_SYNC));
    }

    EXPORT wxKillError wxKill(int pid, wxSignal signal)
    {
        return wxProcess::Kill(pid, signal);
    }

    EXPORT void wxStreamBase_Delete(wxStreamBase* stream)
    {
        if (stream)
            delete stream;
    }

    /*------------------------------------------------------------------------------
      TextCtrl
    ------------------------------------------------------------------------------*/
    EXPORT int wxTextCtrl_EmulateKeyPress(wxTextCtrl* self, wxKeyEvent* keyevent)
    {
        return self->EmulateKeyPress(*keyevent);
    }

    EXPORT void* wxTextCtrl_GetDefaultStyle(wxTextCtrl* self)
    {
        return (void*) &self->GetDefaultStyle();
    }

    EXPORT wxString* wxTextCtrl_GetRange(wxTextCtrl* self, long from, long to)
    {
        wxString* result = new wxString();
        *result = self->GetRange(from, to);
        return result;
    }

    EXPORT wxString* wxTextCtrl_GetStringSelection(wxTextCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetStringSelection();
        return result;
    }

    EXPORT bool wxTextCtrl_IsMultiLine(wxTextCtrl* self)
    {
        return self->IsMultiLine();
    }

    EXPORT bool wxTextCtrl_IsSingleLine(wxTextCtrl* self)
    {
        return self->IsSingleLine();
    }

    EXPORT bool wxTextCtrl_SetDefaultStyle(wxTextCtrl* self, wxTextAttr* style)
    {
        return self->SetDefaultStyle(*style);
    }

    EXPORT void wxTextCtrl_SetMaxLength(wxTextCtrl* self, long len)
    {
        self->SetMaxLength(len);
    }

    EXPORT bool wxTextCtrl_SetStyle(wxTextCtrl* self, long start, long end, wxTextAttr* style)
    {
        return self->SetStyle(start, end, *style);
    }

    /*------------------------------------------------------------------------------
      TextAttr
    ------------------------------------------------------------------------------*/
    EXPORT wxTextAttr* wxTextAttr_CreateDefault()
    {
        return new wxTextAttr();
    }

    EXPORT wxTextAttr* wxTextAttr_Create(wxColour* colText, wxColour* colBack, wxFont* font)
    {
        return new wxTextAttr(*colText, *colBack, *font);
    }

    EXPORT void wxTextAttr_Delete(wxTextAttr* self)
    {
        delete self;
    }

    EXPORT void wxTextAttr_GetBackgroundColour(wxTextAttr* self, wxColour* colour)
    {
        *colour = self->GetBackgroundColour();
    }

    EXPORT void wxTextAttr_GetFont(wxTextAttr* self, wxFont* font)
    {
        *font = self->GetFont();
    }

    EXPORT void wxTextAttr_GetTextColour(wxTextAttr* self, wxColour* colour)
    {
        *colour = self->GetTextColour();
    }

    EXPORT bool wxTextAttr_HasBackgroundColour(wxTextAttr* self)
    {
        return self->HasBackgroundColour();
    }

    EXPORT bool wxTextAttr_HasFont(wxTextAttr* self)
    {
        return self->HasFont();
    }

    EXPORT bool wxTextAttr_HasTextColour(wxTextAttr* self)
    {
        return self->HasTextColour();
    }

    EXPORT bool wxTextAttr_IsDefault(wxTextAttr* self)
    {
        return self->IsDefault();
    }

    EXPORT void wxTextAttr_SetTextColour(wxTextAttr* self, wxColour* colour)
    {
        self->SetTextColour(*colour);
    }

    EXPORT void wxTextAttr_SetBackgroundColour(wxTextAttr* self, wxColour* colour)
    {
        self->SetBackgroundColour(*colour);
    }

    EXPORT void wxTextAttr_SetFont(wxTextAttr* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    /*------------------------------------------------------------------------------
      progress dialog
    ------------------------------------------------------------------------------*/
    EXPORT wxProgressDialog* wxProgressDialog_Create(wxString* title, wxString* message, int max,
                                                     wxWindow* parent, int style)
    {
        return new wxProgressDialog(*title, *message, max, parent, style);
    }

    EXPORT bool wxProgressDialog_Update(wxProgressDialog* self, int value)
    {
        return self->Update(value);
    }

    EXPORT bool wxProgressDialog_UpdateWithMessage(wxProgressDialog* self, int value,
                                                   wxString* message)
    {
        return self->Update(value, *message);
    }

    EXPORT void wxProgressDialog_Resume(wxProgressDialog* self)
    {
        self->Resume();
    }

    /*------------------------------------------------------------------------------
      standard dialogs
    ------------------------------------------------------------------------------*/
    EXPORT void wxGetColourFromUser(wxWindow* parent, wxColour* colInit, wxColour* colour)
    {
        *colour = wxGetColourFromUser(parent, *colInit);
    }

    EXPORT void wxGetFontFromUser(wxWindow* parent, wxFont* fontInit, wxFont* font)
    {
        *font = wxGetFontFromUser(parent, *fontInit);
    }

    EXPORT int wxGetPasswordFromUser(char* message, char* caption, char* defaultText,
                                     wxWindow* parent, char* buffer)
    {
        /* we use a complicated caching method as we don't want to call getpassword twice :-) */
        static char* resultBuffer = nullptr;
        if (buffer == nullptr)
        {
            if (resultBuffer)
            {
                free(resultBuffer);
                resultBuffer = nullptr;
            }
            wxString result = wxGetPasswordFromUser(message, caption, defaultText, parent);
            resultBuffer = (char*) malloc(result.Length() + 1);
            if (resultBuffer)
            {
                strcpy(resultBuffer, result.utf8_str().data()); /* save result */
                return result.Length();
            }
            else
            {
                return 0;
            }
        }
        else if (resultBuffer)
        {
            int len = strlen(resultBuffer);
            memcpy(buffer, resultBuffer, len); /* copy saved result */
            free(resultBuffer);
            resultBuffer = nullptr;
            return len;
        }
        else
        {
            return 0;
        }
    }

    EXPORT int wxGetTextFromUser(char* message, char* caption, char* defaultText, wxWindow* parent,
                                 int x, int y, int center, char* buffer)
    {
        /* we use a complicated caching method as we don't want to call gettext twice :-) */
        static char* resultBuffer = nullptr;
        if (buffer == nullptr)
        {
            if (resultBuffer)
            {
                free(resultBuffer);
                resultBuffer = nullptr;
            }
            wxString result =
                wxGetTextFromUser(message, caption, defaultText, parent, x, y, center != 0);
            resultBuffer = (char*) malloc(result.Length() + 1);
            if (resultBuffer)
            {
                strcpy(resultBuffer, result.utf8_str().data()); /* save result */
                return result.Length();
            }
            else
            {
                return 0;
            }
        }
        else if (resultBuffer)
        {
            int len = strlen(resultBuffer);
            memcpy(buffer, resultBuffer, len); /* copy saved result */
            free(resultBuffer);
            resultBuffer = nullptr;
            return len;
        }
        else
        {
            return 0;
        }
    }

    EXPORT long wxGetNumberFromUser(wxString* message, wxString* prompt, wxString* caption,
                                    long value, long min, long max, wxWindow* parent, int x, int y)
    {
        return wxGetNumberFromUser(*message, *prompt, *caption, value, min, max, parent,
                                   wxPoint(x, y));
    }

    EXPORT void wxcBell(void)
    {
        wxBell();
    }

    EXPORT void wxcBeginBusyCursor(void)
    {
        wxBeginBusyCursor();
    }

    EXPORT int wxcIsBusy(void)
    {
        return (wxIsBusy());
    }

    EXPORT void wxcEndBusyCursor(void)
    {
        wxEndBusyCursor();
    }

    /*-----------------------------------------------------------------------------
      wxInputSink
    -----------------------------------------------------------------------------*/
    EXPORT wxInputSink* wxInputSink_Create(wxInputStream* input, wxEvtHandler* evtHandler,
                                           int bufferLen)
    {
        return new wxInputSink(input, evtHandler, bufferLen);
    }

    EXPORT int wxInputSink_GetId(wxInputSink* self)
    {
        return self->GetId();
    }

    EXPORT void wxInputSink_Start(wxInputSink* self)
    {
        self->Start();
    }

    EXPORT int wxInputSinkEvent_LastError(wxInputSinkEvent* self)
    {
        return self->LastError();
    }

    EXPORT int wxInputSinkEvent_LastRead(wxInputSinkEvent* self)
    {
        return self->LastRead();
    }

    EXPORT char* wxInputSinkEvent_LastInput(wxInputSinkEvent* self)
    {
        return self->LastInput();
    }

    /*-----------------------------------------------------------------------------
      html window
    -----------------------------------------------------------------------------*/
    EXPORT void* wxcHtmlEvent_GetMouseEvent(wxcHtmlEvent* self)
    {
        return (void*) (self->GetMouseEvent());
    }

    EXPORT void* wxcHtmlEvent_GetHtmlCell(wxcHtmlEvent* self)
    {
        return (void*) (self->GetHtmlCell());
    }

    EXPORT wxString* wxcHtmlEvent_GetHtmlCellId(wxcHtmlEvent* self)
    {
        return self->GetHtmlCellId();
    }

    EXPORT wxString* wxcHtmlEvent_GetHref(wxcHtmlEvent* self)
    {
        return self->GetHref();
    }

    EXPORT wxString* wxcHtmlEvent_GetTarget(wxcHtmlEvent* self)
    {
        return self->GetTarget();
    }

    EXPORT wxPoint* wxcHtmlEvent_GetLogicalPosition(wxcHtmlEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetLogicalPosition();
        return pt;
    }

    /*-----------------------------------------------------------------------------
      html window
    -----------------------------------------------------------------------------*/
    EXPORT wxHtmlWindow* wxHtmlWindow_Create(wxWindow* parent, int id, int x, int y, int width,
                                             int height, long style, wxString* name)
    {
        return new wxHtmlWindow(parent, id, wxPoint(x, y), wxSize(width, height), style, *name);
    }

    EXPORT wxHtmlWindow* wxcHtmlWindow_Create(wxWindow* parent, int id, int x, int y, int width,
                                              int height, long style, wxString* name)
    {
        return new wxcHtmlWindow(parent, id, wxPoint(x, y), wxSize(width, height), style, *name);
    }

    EXPORT bool wxHtmlWindow_AppendToPage(wxHtmlWindow* self, wxString* source)
    {
        return self->AppendToPage(*source);
    }

    EXPORT void* wxHtmlWindow_GetInternalRepresentation(wxHtmlWindow* self)
    {
        return (void*) self->GetInternalRepresentation();
    }

    EXPORT wxString* wxHtmlWindow_GetOpenedAnchor(wxHtmlWindow* self)
    {
        wxString* result = new wxString();
        *result = self->GetOpenedAnchor();
        return result;
    }

    EXPORT wxString* wxHtmlWindow_GetOpenedPage(wxHtmlWindow* self)
    {
        wxString* result = new wxString();
        *result = self->GetOpenedPage();
        return result;
    }

    EXPORT wxString* wxHtmlWindow_GetOpenedPageTitle(wxHtmlWindow* self)
    {
        wxString* result = new wxString();
        *result = self->GetOpenedPageTitle();
        return result;
    }

    EXPORT void* wxHtmlWindow_GetRelatedFrame(wxHtmlWindow* self)
    {
        return (void*) self->GetRelatedFrame();
    }

    EXPORT bool wxHtmlWindow_HistoryBack(wxHtmlWindow* self)
    {
        return self->HistoryBack();
    }

    EXPORT bool wxHtmlWindow_HistoryCanBack(wxHtmlWindow* self)
    {
        return self->HistoryCanBack();
    }

    EXPORT bool wxHtmlWindow_HistoryCanForward(wxHtmlWindow* self)
    {
        return self->HistoryCanForward();
    }

    EXPORT void wxHtmlWindow_HistoryClear(wxHtmlWindow* self)
    {
        self->HistoryClear();
    }

    EXPORT bool wxHtmlWindow_HistoryForward(wxHtmlWindow* self)
    {
        return self->HistoryForward();
    }

    EXPORT bool wxHtmlWindow_LoadPage(wxHtmlWindow* self, wxString* location)
    {
        return self->LoadPage(*location);
    }

    EXPORT void wxHtmlWindow_ReadCustomization(wxHtmlWindow* self, wxConfigBase* cfg,
                                               wxString* path)
    {
        self->ReadCustomization(cfg, *path);
    }

    EXPORT void wxHtmlWindow_SetBorders(wxHtmlWindow* self, int b)
    {
        self->SetBorders(b);
    }

    EXPORT void wxHtmlWindow_SetFonts(wxHtmlWindow* self, wxString* normal_face,
                                      wxString* fixed_face, int* sizes)
    {
        self->SetFonts(*normal_face, *fixed_face, sizes);
    }

    EXPORT int wxHtmlWindow_SetPage(wxHtmlWindow* self, wxString* source)
    {
        return self->SetPage(*source);
    }

    EXPORT void wxHtmlWindow_SetRelatedFrame(wxHtmlWindow* self, wxFrame* frame, wxString* format)
    {
        self->SetRelatedFrame(frame, *format);
    }

    EXPORT void wxHtmlWindow_SetRelatedStatusBar(wxHtmlWindow* self, int bar)
    {
        self->SetRelatedStatusBar(bar);
    }

    EXPORT void wxHtmlWindow_WriteCustomization(wxHtmlWindow* self, wxConfigBase* cfg,
                                                wxString* path)
    {
        self->WriteCustomization(cfg, *path);
    }

    /*-----------------------------------------------------------------------------
      LOGGER
    -----------------------------------------------------------------------------*/
    EXPORT wxLogStderr* wxLogStderr_Create()
    {
        return new wxLogStderr();
    }

    EXPORT wxLogStderr* wxLogStderr_CreateStdOut()
    {
        return new wxLogStderr(stdout);
    }

    EXPORT wxLogNull* wxLogNull_Create()
    {
        return new wxLogNull();
    }

    EXPORT wxLogTextCtrl* wxLogTextCtrl_Create(wxTextCtrl* text)
    {
        return new wxLogTextCtrl(text);
    }

#if wxUSE_LOGWINDOW
    EXPORT wxLogWindow* wxLogWindow_Create(wxFrame* parent, wxString* title, bool showit,
                                           bool passthrough)
    {
        return new wxLogWindow(parent, *title, showit, passthrough);
    }

    EXPORT wxFrame* wxLogWindow_GetFrame(wxLogWindow* self)
    {
        return self->GetFrame();
    }
#endif

    EXPORT void wxLog_Delete(wxLog* self)
    {
        delete self;
    }

    EXPORT void wxLog_OnLog(wxLog* self, int level, void* szString, int t)
    {
        self->OnLog((wxLogLevel) level, (const char*) szString, (time_t) t);
    }

    EXPORT void wxLog_Flush(wxLog* self)
    {
        self->Flush();
    }

    EXPORT bool wxLog_HasPendingMessages(wxLog* self)
    {
        return self->HasPendingMessages();
    }

    EXPORT void wxLog_FlushActive(wxLog* self)
    {
        self->FlushActive();
    }

    EXPORT void* wxLog_GetActiveTarget()
    {
        return (void*) wxLog::GetActiveTarget();
    }

    EXPORT void* wxLog_SetActiveTarget(wxLog* pLogger)
    {
        return (void*) wxLog::SetActiveTarget(pLogger);
    }

    EXPORT void wxLog_Suspend(wxLog* self)
    {
        self->Suspend();
    }

    EXPORT void wxLog_Resume(wxLog* self)
    {
        self->Resume();
    }

    EXPORT void wxLog_SetVerbose(wxLog* self, bool bVerbose)
    {
        self->SetVerbose(bVerbose);
    }

    EXPORT void wxLog_DontCreateOnDemand(wxLog* self)
    {
        self->DontCreateOnDemand();
    }

    // Obsolete
    // EWXWEXPORT(void,wxLog_SetTraceMask)(wxLog* self,int ulMask)

    EXPORT void wxLog_AddTraceMask(wxLog* self, void* str)
    {
        self->AddTraceMask((const char*) str);
    }

    EXPORT void wxLog_RemoveTraceMask(wxLog* self, void* str)
    {
        self->RemoveTraceMask((const char*) str);
    }

    EXPORT void wxLog_SetTimestamp(wxLog* self, void* ts)
    {
        self->SetTimestamp((const char*) ts);
    }

    EXPORT bool wxLog_GetVerbose(wxLog* self)
    {
        return self->GetVerbose();
    }

    EXPORT bool wxLog_IsAllowedTraceMask(wxLog* self, void* mask)
    {
        return self->IsAllowedTraceMask((const char*) mask);
    }

    EXPORT void* wxLog_GetTimestamp(wxLog* self)
    {
        return (void*) strdup((self->GetTimestamp()).utf8_str().data());
    }

    EXPORT void LogError(wxString* message)
    {
        wxLogError(*message);
    }

    EXPORT void LogFatalError(wxString* message)
    {
        wxLogFatalError(*message);
    }

    EXPORT void LogWarning(wxString* message)
    {
        wxLogWarning(*message);
    }

    EXPORT void LogMessage(wxString* message)
    {
        wxLogMessage(*message);
    }

    EXPORT void LogVerbose(wxString* message)
    {
        wxLogVerbose(*message);
    }

    EXPORT void LogStatus(wxString* message)
    {
        wxLogStatus(*message);
    }

    EXPORT void LogSysError(wxString* message)
    {
        wxLogSysError(*message);
    }

    EXPORT void LogDebug(wxString* message)
    {
        wxLogDebug(*message);
    }

    EXPORT void LogTrace(wxString* mask, wxString* message)
    {
        wxLogTrace(*mask, *message);
    }

    /*-----------------------------------------------------------------------------
      Grid text editor
    -----------------------------------------------------------------------------*/
    EXPORT wxGridCellTextEnterEditor* wxGridCellTextEnterEditor_Ctor()
    {
        return new wxGridCellTextEnterEditor();
    }

    /*-----------------------------------------------------------------------------
      ConfigBase
    -----------------------------------------------------------------------------*/
    EXPORT wxConfigBase* wxConfigBase_Get()
    {
        return wxConfigBase::Get();
    }

    EXPORT void wxConfigBase_Set(wxConfigBase* self)
    {
        wxConfigBase::Set(self);
    }

    EXPORT wxFileConfig* wxFileConfig_Create(wxInputStream* inp)
    {
        return new wxFileConfig(*inp);
    }

    /*-----------------------------------------------------------------------------
      PropertyGrid
    -----------------------------------------------------------------------------*/
    EXPORT void* wxPropertyGrid_Append(wxPropertyGrid* self, wxPGProperty* property)
    {
        return (void*) self->Append(property);
    }

    EXPORT void* wxPropertyGrid_Create(wxWindow* parent, int id, int x, int y, int width,
                                       int height, int style)
    {
        return (void*) new wxPropertyGrid(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT bool wxPropertyGrid_DisableProperty(wxPropertyGrid* self, wxString const* propName)
    {
        return self->DisableProperty(*propName);
    }

    /*-----------------------------------------------------------------------------
      wxPropertyGridEvent
      Defined within eljevent.cpp
    -----------------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------------
      PGProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxString* wxPGProperty_GetLabel(wxPGProperty* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT wxString* wxPGProperty_GetName(wxPGProperty* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT wxString* wxPGProperty_GetValueAsString(wxPGProperty* self)
    {
        wxString* result = new wxString();
        *result = self->GetValueAsString();
        return result;
    }

    EXPORT wxString* wxPGProperty_GetValueType(wxPGProperty* self)
    {
        wxString* result = new wxString();
        *result = self->GetValueType();
        return result;
    }

    EXPORT void wxPGProperty_SetHelpString(wxPGProperty* self, wxString const* helpString)
    {
        self->SetHelpString(*helpString);
    }

    /*-----------------------------------------------------------------------------
      wxStringProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxStringProperty* wxStringProperty_Create(wxString const* label, wxString const* name,
                                                     wxString const* value)
    {
        return new wxStringProperty(*label, *name, *value);
    }

    /*-----------------------------------------------------------------------------
      wxIntProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxIntProperty* wxIntProperty_Create(wxString const* label, wxString const* name,
                                               int value)
    {
        return new wxIntProperty(*label, *name, value);
    }

    /*-----------------------------------------------------------------------------
      wxBoolProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxBoolProperty* wxBoolProperty_Create(wxString const* label, wxString const* name,
                                                 bool value)
    {
        return new wxBoolProperty(*label, *name, value);
    }

    /*-----------------------------------------------------------------------------
      wxFloatProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxFloatProperty* wxFloatProperty_Create(wxString const* label, wxString const* name,
                                                   float value)
    {
        return new wxFloatProperty(*label, *name, value);
    }

    /*-----------------------------------------------------------------------------
      wxDateProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxDateProperty* wxDateProperty_Create(wxString const* label, wxString const* name,
                                                 wxDateTime const* value)
    {
        return new wxDateProperty(*label, *name, *value);
    }

    /*-----------------------------------------------------------------------------
      wxFileProperty
    -----------------------------------------------------------------------------*/
    EXPORT wxFileProperty* wxFileProperty_Create(wxString const* label, wxString const* name,
                                                 wxString const* value)
    {
        return new wxFileProperty(*label, *name, *value);
    }

    /*-----------------------------------------------------------------------------
      wxPropertyCategory
    -----------------------------------------------------------------------------*/
    EXPORT wxPropertyCategory* wxPropertyCategory_Create(wxString const* label)
    {
        return new wxPropertyCategory(*label);
    }

} /* extern "C" */
