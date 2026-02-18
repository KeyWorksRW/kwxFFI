#pragma once

#include <wx/activityindicator.h>
#include <wx/animate.h>
#include <wx/apptrait.h>
#include <wx/artprov.h>
#include <wx/aui/auibar.h>
#include <wx/aui/auibook.h>
#include <wx/aui/dockart.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/tabmdi.h>
#include <wx/bannerwindow.h>
#include <wx/bmpcbox.h>
#include <wx/calctrl.h>
#include <wx/checklst.h>
#include <wx/choicebk.h>
#include <wx/clipbrd.h>
#include <wx/clrpicker.h>
#include <wx/collpane.h>
#include <wx/colordlg.h>
#include <wx/combo.h>
#include <wx/commandlinkbutton.h>
#include <wx/config.h>
#include <wx/dataview.h>
#include <wx/datectrl.h>
#include <wx/dirctrl.h>
#include <wx/display.h>
#include <wx/dnd.h>
#include <wx/docmdi.h>
#include <wx/docview.h>
#include <wx/filectrl.h>
#include <wx/filepicker.h>
#include <wx/fontdlg.h>
#include <wx/fontpicker.h>
#include <wx/gbsizer.h>
#include <wx/grid.h>
#include <wx/headerctrl.h>
#include <wx/html/helpctrl.h>
#include <wx/htmllbox.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/infobar.h>
#include <wx/laywin.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/minifram.h>
#include <wx/mstream.h>
#include <wx/notebook.h>
#include <wx/notifmsg.h>
#include <wx/odcombo.h>
#include <wx/popupwin.h>
#include <wx/print.h>
#include <wx/propdlg.h>
#include <wx/propgrid/manager.h>
#include <wx/rearrangectrl.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/gallery.h>
#include <wx/ribbon/page.h>
#include <wx/ribbon/panel.h>
#include <wx/ribbon/toolbar.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/sashwin.h>
#include <wx/sckipc.h>
#include <wx/simplebook.h>
#include <wx/sizer.h>
#include <wx/socket.h>
#include <wx/sound.h>
#include <wx/spinctrl.h>
#include <wx/splash.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>
#include <wx/statline.h>
#include <wx/textdlg.h>
#include <wx/timectrl.h>
#include <wx/toolbook.h>
#include <wx/tooltip.h>
#include <wx/treebook.h>
#include <wx/treectrl.h>
#include <wx/treelist.h>
#include <wx/uiaction.h>
#include <wx/vlbox.h>
#include <wx/vscroll.h>
#include <wx/webview.h>
#include <wx/wizard.h>
#include <wx/wrapsizer.h>
#include <wx/wx.h>

#if !wxCHECK_VERSION(3, 3, 1)
    #error "This code requires wxWidgets 3.3.1 or later"
#endif

#if !wxUSE_UNICODE_UTF8
    #error "This code requires wxWidgets built with UTF-8 Unicode support"
#endif

#include "kwx_def.h"

#define MAKE_EVENT_WRAPPER(evt)   \
    WXFFI_EXPORT(int, exp##evt)() \
    {                             \
        return (int) wx##evt;     \
    }
#define MAKE_UNDEF_EVENT_WRAPPER(evt) \
    WXFFI_EXPORT(int, exp##evt)()     \
    {                                 \
        return (int) wxEVT_NULL;      \
    }

extern "C"
{
    typedef void (*ClosureFun)(void* closureFun, void* data, void* event);

    typedef bool (*AppInitFunc)(void);

    typedef void (*kwxFunc)(void* pObject, void* event);
    typedef int (*TextDropFunc)(void* pObject, long x, long y, void* text);
    typedef int (*FileDropFunc)(void* pObject, long x, long y, void* files, int count);
    typedef void (*DragZeroFunc)(void* pObject);
    typedef int (*DragTwoFunc)(void* pObject, long x, long y);
    typedef int (*DragThreeFunc)(void* pObject, long x, long y, int def);

    typedef void* (*TGetText)(void* pObject, void* text);

    typedef int (*DataGetDataSize)(void* pObject);
    typedef int (*DataGetDataHere)(void* pObject, void* buffer);
    typedef int (*DataSetData)(void* pObject, int size, const void* buffer);

    typedef int (*ValidateFunc)(void* pObject);

    typedef int (*TCPAdviseFunc)(void* pObject, void* topic, void* item, void* data, int size,
                                 int format);
    typedef int (*TCPExecuteFunc)(void* pObject, void* topic, void* data, int size, int format);
    typedef char* (*TCPRequestFunc)(void* pObject, void* topic, void* item, void* size, int format);
    typedef int (*TCPPokeFunc)(void* pObject, void* topic, void* item, void* data, int size,
                               int format);
    typedef int (*TCPStartAdviseFunc)(void* pObject, void* topic, void* item);
    typedef int (*TCPStopAdviseFunc)(void* pObject, void* topic, void* item);
    typedef void* (*TCPOnConnection)(void* pObject, void* count);
    typedef int (*TCPOnDisconnect)(void* pObject);

    typedef int (*PrintBeginDocument)(void* pObject, int start, int endVal);
    typedef void (*PrintCommon)(void* pObject);
    typedef int (*PrintBeginPage)(void* pObject, int page);
    typedef void (*PrintPageInfo)(void* pObject, int* minVal, int* maxVal, int* from, int* to);

    typedef int (*PreviewFrameFunc)(void* pObject);

    typedef int (*TreeCompareFunc)(void* pObject, void* item1, void* item2);
}

// Miscellaneous helper functions

// Copies the contents of a wxString to a buffer and returns the length of the
// string
int copyStrToBuf(void* dst, wxString& src);

/*
    A Closure is used to call foreign functions. They are closures
    because they don't just contain a function pointer but also some
    local data supplied at creation time. The closures are reference counted
    by 'Callbacks'. Each event handler uses callbacks to react to primitive
    events like EVT_LEFT_CLICK and EVT_MOTION. These callbacks invoke the
    corresponding closure. Due to reference counting, a single closure can
    handle a range of events.
*/
class wxClosure : public wxClientData
{
protected:
    int m_refcount;    // callbacks reference count the closures
    ClosureFun m_fun;  // the foreign function to call
    void* m_data;      // the associated data, passed along with the function call
public:
    wxClosure(ClosureFun fun, void* data);
    ~wxClosure();

    virtual void IncRef();
    virtual void DecRef();

    virtual void Invoke(wxEvent* event);
    virtual void* GetData();
};

class wxCallback : public wxObject
{
private:
    wxClosure* m_closure;  // the closure to invoke
public:
    wxCallback(wxClosure* closure);
    ~wxCallback();

    void Invoke(wxEvent* event);
    wxClosure* GetClosure();
};

/*
    kwxEventHandler provides a generic event routing mechanism for all
    language ports. Its HandleEvent method extracts the wxCallback from
    the event's user data and invokes the associated closure. This is
    used by wxEvtHandler_Connect/Disconnect so that language ports never
    need direct access to wxClosure/wxCallback classes.
*/
class kwxEventHandler : public wxEvtHandler
{
public:
    void HandleEvent(wxEvent& evt);
};

class kwxDataObject : public wxObject
{
public:
    kwxDataObject(void* data) : wxObject() { data = data; };
    void* data;
};

class kwxDropTarget : public wxDropTarget
{
private:
    DragThreeFunc on_data_func;
    DragTwoFunc on_drop_func;
    DragThreeFunc on_enter_func;
    DragThreeFunc on_drag_func;
    DragZeroFunc on_leave_func;
    void* obj;

public:
    kwxDropTarget(void* pObject) : wxDropTarget()
    {
        on_data_func = nullptr;
        on_drop_func = nullptr;
        on_enter_func = nullptr;
        on_drag_func = nullptr;
        on_leave_func = nullptr;
        obj = pObject;
    };
    wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);
    bool OnDrop(wxCoord x, wxCoord y);
    wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult def);
    wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
    void OnLeave();

    void SetOnData(DragThreeFunc pFunction) { on_data_func = pFunction; };
    void SetOnDrop(DragTwoFunc pFunction) { on_drop_func = pFunction; };
    void SetOnEnter(DragThreeFunc pFunction) { on_enter_func = pFunction; };
    void SetOnDragOver(DragThreeFunc pFunction) { on_drag_func = pFunction; };
    void SetOnLeave(DragZeroFunc pFunction) { on_leave_func = pFunction; };
};

class kwxDragDataObject : public wxDataObjectSimple
{
private:
    void* obj;
    DataGetDataSize OnGetDataSize;
    DataGetDataHere OnGetDataHere;
    DataSetData OnSetData;

public:
    kwxDragDataObject(void* pObject, const wxString& format, DataGetDataSize fnGetDataSize,
                      DataGetDataHere fnGetDataHere, DataSetData fnSetData) :
        wxDataObjectSimple(format)
    {
        obj = pObject;
        OnGetDataSize = fnGetDataSize;
        OnGetDataHere = fnGetDataHere;
        OnSetData = fnSetData;
    }
    size_t GetDataSize() const { return (size_t) OnGetDataSize(obj); }
    bool GetDataHere(void* buf) const { return OnGetDataHere(obj, buf) != 0; }
    bool SetData(size_t len, const void* buf) { return OnSetData(obj, (int) len, buf) != 0; }
};

class kwxTextDropTarget : public wxTextDropTarget
{
private:
    DragThreeFunc on_data_func;
    DragTwoFunc on_drop_func;
    DragThreeFunc on_enter_func;
    DragThreeFunc on_drag_func;
    DragZeroFunc on_leave_func;
    TextDropFunc func;
    void* obj;

public:
    kwxTextDropTarget(void* pObject, TextDropFunc pFunction) : wxTextDropTarget()
    {
        on_data_func = nullptr;
        on_drop_func = nullptr;
        on_enter_func = nullptr;
        on_drag_func = nullptr;
        on_leave_func = nullptr;
        func = pFunction;
        obj = pObject;
    };

    virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& text);

    wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);
    bool OnDrop(wxCoord x, wxCoord y);
    wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult def);
    wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
    void OnLeave();

    void SetOnData(DragThreeFunc pFunction) { on_data_func = pFunction; };
    void SetOnDrop(DragTwoFunc pFunction) { on_drop_func = pFunction; };
    void SetOnEnter(DragThreeFunc pFunction) { on_enter_func = pFunction; };
    void SetOnDragOver(DragThreeFunc pFunction) { on_drag_func = pFunction; };
    void SetOnLeave(DragZeroFunc pFunction) { on_leave_func = pFunction; };
};

class kwxFileDropTarget : public wxFileDropTarget
{
private:
    DragThreeFunc on_data_func;
    DragTwoFunc on_drop_func;
    DragThreeFunc on_enter_func;
    DragThreeFunc on_drag_func;
    DragZeroFunc on_leave_func;
    FileDropFunc func;
    void* obj;

public:
    kwxFileDropTarget(void* pObject, FileDropFunc pFunction) : wxFileDropTarget()
    {
        on_data_func = nullptr;
        on_drop_func = nullptr;
        on_enter_func = nullptr;
        on_drag_func = nullptr;
        on_leave_func = nullptr;
        func = pFunction;
        obj = pObject;
    };

    virtual bool OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames);

    wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);
    bool OnDrop(wxCoord x, wxCoord y);
    wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult def);
    wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);
    void OnLeave();

    void SetOnData(DragThreeFunc pFunction) { on_data_func = pFunction; };
    void SetOnDrop(DragTwoFunc pFunction) { on_drop_func = pFunction; };
    void SetOnEnter(DragThreeFunc pFunction) { on_enter_func = pFunction; };
    void SetOnDragOver(DragThreeFunc pFunction) { on_drag_func = pFunction; };
    void SetOnLeave(DragZeroFunc pFunction) { on_leave_func = pFunction; };
};

class kwxTextValidator : public wxTextValidator
{
public:
    kwxTextValidator(void* pObject, void* pFunction, void* text, long style) :
        wxTextValidator(style, &buf)
    {
        obj = pObject;
        fnc = (ValidateFunc) pFunction;
        buf = (const char*) text;
    };

    kwxTextValidator(const kwxTextValidator& other)
    {
        Copy(other);
        obj = other.obj;
        fnc = other.fnc;
        buf = other.buf;
    };

    virtual wxObject* Clone(void) const { return new kwxTextValidator(*this); }
    virtual bool Validate(wxWindow* parent);

private:
    wxString buf;
    void* obj;
    ValidateFunc fnc;
};

class kwxConnection : public wxTCPConnection
{
private:
    TCPAdviseFunc DoOnAdvise;
    TCPExecuteFunc DoOnExecute;
    TCPRequestFunc DoOnRequest;
    TCPPokeFunc DoOnPoke;
    TCPStartAdviseFunc DoOnStartAdvise;
    TCPStopAdviseFunc DoOnStopAdvise;
    TCPOnDisconnect DoOnDisconnect;
    void* kwxObject;

public:
    kwxConnection() : wxTCPConnection()
    {
        DoOnAdvise = nullptr;
        DoOnExecute = nullptr;
        DoOnRequest = nullptr;
        DoOnPoke = nullptr;
        DoOnStartAdvise = nullptr;
        DoOnStopAdvise = nullptr;
        DoOnDisconnect = nullptr;
        kwxObject = nullptr;
    }

    kwxConnection(char* buffer, int size) : wxTCPConnection(buffer, size)
    {
        DoOnAdvise = nullptr;
        DoOnExecute = nullptr;
        DoOnRequest = nullptr;
        DoOnPoke = nullptr;
        DoOnStartAdvise = nullptr;
        DoOnStopAdvise = nullptr;
        DoOnDisconnect = nullptr;
        kwxObject = nullptr;
    }

    void SetOnAdvise(void* pFunction) { DoOnAdvise = (TCPAdviseFunc) pFunction; };
    void SetOnExecute(void* pFunction) { DoOnExecute = (TCPExecuteFunc) pFunction; };
    void SetOnRequest(void* pFunction) { DoOnRequest = (TCPRequestFunc) pFunction; };
    void SetOnPoke(void* pFunction) { DoOnPoke = (TCPPokeFunc) pFunction; };
    void SetOnStartAdvise(void* pFunction) { DoOnStartAdvise = (TCPStartAdviseFunc) pFunction; };
    void SetOnStopAdvise(void* pFunction) { DoOnStopAdvise = (TCPStopAdviseFunc) pFunction; };
    void SetOnDisconnect(void* pFunction) { DoOnDisconnect = (TCPOnDisconnect) pFunction; };
    void SetCallbackObject(void* pObject) { kwxObject = pObject; };

    virtual bool OnExecute(const wxString& topic, char* data, int size, wxIPCFormat format)
    {
        return DoOnExecute ? DoOnExecute(kwxObject, (void*) topic.utf8_str().data(), data, size,
                                         (int) format) != 0 :
                             FALSE;
    };

    virtual char* OnRequest(const wxString& topic, const wxString& item, int* size,
                            wxIPCFormat format)
    {
        return DoOnRequest ?
                   DoOnRequest(kwxObject, (void*) topic.utf8_str().data(),
                               (void*) item.utf8_str().data(), (void*) size, (int) format) :
                   (char*) nullptr;
    };

    virtual bool OnPoke(const wxString& topic, const wxString& item, char* data, int size,
                        wxIPCFormat format)
    {
        return DoOnPoke ? DoOnPoke(kwxObject, (void*) topic.utf8_str().data(),
                                   (void*) item.utf8_str().data(), data, size, (int) format) :
                          FALSE;
    };

    virtual bool OnStartAdvise(const wxString& topic, const wxString& item)
    {
        return DoOnStartAdvise ? DoOnStartAdvise(kwxObject, (void*) topic.utf8_str().data(),
                                                 (void*) item.utf8_str().data()) :
                                 FALSE;
    };

    virtual bool OnStopAdvise(const wxString& topic, const wxString& item)
    {
        return DoOnStopAdvise ? DoOnStopAdvise(kwxObject, (void*) topic.utf8_str().data(),
                                               (void*) item.utf8_str().data()) :
                                FALSE;
    };

    virtual bool OnAdvise(const wxString& topic, const wxString& item, char* data, int size,
                          wxIPCFormat format)
    {
        return DoOnAdvise ? DoOnAdvise(kwxObject, (void*) topic.utf8_str().data(),
                                       (void*) item.utf8_str().data(), data, size, (int) format) :
                            FALSE;
    };

    virtual bool OnDisconnect()
    {
        return DoOnDisconnect ? DoOnDisconnect(kwxObject) : wxTCPConnection::OnDisconnect();
    };
};

class kwxServer : public wxTCPServer
{
private:
    void* kwxObject;
    TCPOnConnection DoOnConnect;

public:
    kwxServer(void* pObject, void* pFunction) : wxTCPServer()
    {
        kwxObject = pObject;
        DoOnConnect = (TCPOnConnection) pFunction;
    };

    virtual wxConnectionBase* OnAcceptConnection(const wxString& topic)
    {
        kwxConnection* result = new kwxConnection();
        result->SetCallbackObject(DoOnConnect(kwxObject, (void*) result));
        return result;
    };
};

class kwxClient : public wxTCPClient
{
private:
    void* kwxObject;
    TCPOnConnection DoOnConnect;

public:
    kwxClient(void* pObject, void* pFunction) : wxTCPClient()
    {
        kwxObject = pObject;
        DoOnConnect = (TCPOnConnection) pFunction;
    };

    virtual wxConnectionBase* OnMakeConnection()
    {
        kwxConnection* result = new kwxConnection();
        result->SetCallbackObject(DoOnConnect(kwxObject, (void*) result));
        return result;
    };
};

class kwxPrintout : public wxPrintout
{
private:
    void* kwxObject;
    PrintBeginDocument DoOnBeginDocument;
    PrintCommon DoOnEndDocument;
    PrintCommon DoOnBeginPrinting;
    PrintCommon DoOnEndPrinting;
    PrintCommon DoOnPreparePrinting;
    PrintBeginPage DoOnPrintPage;
    PrintBeginPage DoOnHasPage;
    PrintPageInfo DoOnPageInfo;

public:
    kwxPrintout(void* title, void* pObject, void* fnBeginDocument, void* fnEndDocument,
                void* fnBeginPrinting, void* fnEndPrinting, void* fnPreparePrinting,
                void* fnPrintPage, void* fnHasPage, void* fnPageInfo) :
        wxPrintout((const char*) title)
    {
        kwxObject = pObject;
        DoOnBeginDocument = (PrintBeginDocument) fnBeginDocument;
        DoOnEndDocument = (PrintCommon) fnEndDocument;
        DoOnBeginPrinting = (PrintCommon) fnBeginPrinting;
        DoOnEndPrinting = (PrintCommon) fnEndPrinting;
        DoOnPreparePrinting = (PrintCommon) fnPreparePrinting;
        DoOnPrintPage = (PrintBeginPage) fnPrintPage;
        DoOnHasPage = (PrintBeginPage) fnHasPage;
        DoOnPageInfo = (PrintPageInfo) fnPageInfo;
    }

    virtual bool OnBeginDocument(int startPage, int endPage)
    {
        return wxPrintout::OnBeginDocument(startPage, endPage) &&
               (DoOnBeginDocument(kwxObject, startPage, endPage) != 0);
    }

    virtual void OnEndDocument()
    {
        wxPrintout::OnEndDocument();
        DoOnEndDocument(kwxObject);
    }

    virtual void OnBeginPrinting() { DoOnBeginPrinting(kwxObject); }

    virtual void OnEndPrinting() { DoOnEndPrinting(kwxObject); }

    virtual void OnPreparePrinting() { DoOnPreparePrinting(kwxObject); }

    virtual bool OnPrintPage(int page) { return DoOnPrintPage(kwxObject, page) != 0; }

    virtual bool HasPage(int page) { return DoOnHasPage(kwxObject, page) != 0; }

    virtual void GetPageInfo(int* minPage, int* maxPage, int* pageFrom, int* pageTo)
    {
        DoOnPageInfo(kwxObject, minPage, maxPage, pageFrom, pageTo);
    }
};

class kwxPreviewFrame : public wxPreviewFrame
{
private:
    void* kwxObject;
    PreviewFrameFunc DoInitialize;
    PreviewFrameFunc DoCreateCanvas;
    PreviewFrameFunc DoCreateControlBar;

public:
    kwxPreviewFrame(void* pObject, void* init, void* createCanvas, void* createToolbar,
                    void* preview, void* parent, void* title, int x, int y, int width, int height,
                    int style) :
        wxPreviewFrame((wxPrintPreviewBase*) preview, (wxFrame*) parent, (const char*) title,
                       wxPoint(x, y), wxSize(width, height), (long) style)
    {
        kwxObject = pObject;
        DoInitialize = (PreviewFrameFunc) init;
        DoCreateCanvas = (PreviewFrameFunc) createCanvas;
        DoCreateControlBar = (PreviewFrameFunc) createToolbar;
    }

    virtual void Initialize()
    {
        if ((DoInitialize) && DoInitialize(kwxObject))
            return;
        wxPreviewFrame::Initialize();
    }

    virtual void CreateCanvas()
    {
        if ((DoCreateCanvas) && DoCreateCanvas(kwxObject))
            return;
        wxPreviewFrame::CreateCanvas();
    }

    virtual void CreateControlBar()
    {
        if ((DoCreateControlBar) && DoCreateControlBar(kwxObject))
            return;
        wxPreviewFrame::CreateControlBar();
    }

    void SetPreviewCanvas(void* pObject) { m_previewCanvas = (wxPreviewCanvas*) pObject; }

    void SetControlBar(void* pObject) { m_controlBar = (wxPreviewControlBar*) pObject; }

    void SetPrintPreview(void* pObject) { m_printPreview = (wxPrintPreviewBase*) pObject; }

    void* GetPreviewCanvas() { return (void*) m_previewCanvas; }

    void* GetControlBar() { return (void*) m_controlBar; }

    void* GetPrintPreview() { return (void*) m_printPreview; }
};

class kwxTreeControl : public wxTreeCtrl
{
    DECLARE_DYNAMIC_CLASS(kwxTreeControl)

private:
    TreeCompareFunc compare_func;
    void* kwxObject;

public:
    kwxTreeControl() : wxTreeCtrl()
    {
        kwxObject = nullptr;
        compare_func = nullptr;
    };

    kwxTreeControl(void* pObject, void* compareFunc, wxWindow* parent, wxWindowID id = -1,
                   const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                   long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT,
                   const wxValidator& validator = wxDefaultValidator,
                   const wxString& name = wxT("wxTreeCtrl")) :
        wxTreeCtrl(parent, id, pos, size, style, validator, name)
    {
        kwxObject = pObject;
        compare_func = (TreeCompareFunc) compareFunc;
    };

    virtual int OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2)
    {
        return kwxObject ? compare_func(kwxObject, (void*) &item1, (void*) &item2) :
                           wxTreeCtrl::OnCompareItems(item1, item2);
    }
};
