#include "wrapper.h"

#include <wx/fs_zip.h>
#include <wx/html/htmlwin.h>
#include <wx/xrc/xmlres.h>

#ifdef wxUSE_STC
    #include <wx/stc/stc.h>
#endif

class wxMDIParentFrameXmlHandler : public wxXmlResourceHandler
{
public:
    wxMDIParentFrameXmlHandler();
    virtual wxObject* DoCreateResource();
    virtual bool CanHandle(wxXmlNode* node);
};

class wxMDIChildFrameXmlHandler : public wxXmlResourceHandler
{
public:
    wxMDIChildFrameXmlHandler();
    virtual wxObject* DoCreateResource();
    virtual bool CanHandle(wxXmlNode* node);
};

class wxSplitterWindowXmlHandler : public wxXmlResourceHandler
{
public:
    wxSplitterWindowXmlHandler();
    virtual wxObject* DoCreateResource();
    virtual bool CanHandle(wxXmlNode* node);
};

#ifdef wxUSE_STC
class wxStyledTextCtrlXmlHandler : public wxXmlResourceHandler
{
public:
    wxStyledTextCtrlXmlHandler();
    virtual wxObject* DoCreateResource();
    virtual bool CanHandle(wxXmlNode* node);
};
#endif

class wxGridXmlHandler : public wxXmlResourceHandler
{
public:
    wxGridXmlHandler();
    virtual wxObject* DoCreateResource();
    virtual bool CanHandle(wxXmlNode* node);
};

wxMDIParentFrameXmlHandler::wxMDIParentFrameXmlHandler() : wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxSTAY_ON_TOP);
    XRC_ADD_STYLE(wxCAPTION);
    XRC_ADD_STYLE(wxDEFAULT_DIALOG_STYLE);
    XRC_ADD_STYLE(wxDEFAULT_FRAME_STYLE);
    XRC_ADD_STYLE(wxSYSTEM_MENU);
    XRC_ADD_STYLE(wxRESIZE_BORDER);

    XRC_ADD_STYLE(wxFRAME_TOOL_WINDOW);
    XRC_ADD_STYLE(wxFRAME_FLOAT_ON_PARENT);
    XRC_ADD_STYLE(wxMAXIMIZE_BOX);
    XRC_ADD_STYLE(wxMINIMIZE_BOX);
    XRC_ADD_STYLE(wxSTAY_ON_TOP);

    XRC_ADD_STYLE(wxTAB_TRAVERSAL);
    XRC_ADD_STYLE(wxWS_EX_VALIDATE_RECURSIVELY);
    XRC_ADD_STYLE(wxCLIP_CHILDREN);

    AddWindowStyles();
}

wxObject* wxMDIParentFrameXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(frame, wxMDIParentFrame);

    frame->Create(m_parentAsWindow, GetID(), GetText("title"), wxDefaultPosition, wxDefaultSize,
                  GetStyle("style", wxDEFAULT_FRAME_STYLE), GetName());

    if (HasParam("size"))
        frame->SetClientSize(GetSize());
    if (HasParam("pos"))
        frame->Move(GetPosition());

    SetupWindow(frame);

    CreateChildren(frame);

    if (GetBool("centered", FALSE))
        frame->Centre();

    return frame;
}

bool wxMDIParentFrameXmlHandler::CanHandle(wxXmlNode* node)
{
    return IsOfClass(node, "wxMDIParentFrame");
}

wxMDIChildFrameXmlHandler::wxMDIChildFrameXmlHandler() : wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxSTAY_ON_TOP);
    XRC_ADD_STYLE(wxCAPTION);
    XRC_ADD_STYLE(wxDEFAULT_DIALOG_STYLE);
    XRC_ADD_STYLE(wxDEFAULT_FRAME_STYLE);
    XRC_ADD_STYLE(wxSYSTEM_MENU);
    XRC_ADD_STYLE(wxRESIZE_BORDER);

    XRC_ADD_STYLE(wxFRAME_TOOL_WINDOW);
    XRC_ADD_STYLE(wxFRAME_FLOAT_ON_PARENT);
    XRC_ADD_STYLE(wxMAXIMIZE_BOX);
    XRC_ADD_STYLE(wxMINIMIZE_BOX);
    XRC_ADD_STYLE(wxSTAY_ON_TOP);

    XRC_ADD_STYLE(wxTAB_TRAVERSAL);
    XRC_ADD_STYLE(wxWS_EX_VALIDATE_RECURSIVELY);
    XRC_ADD_STYLE(wxCLIP_CHILDREN);

    AddWindowStyles();
}

wxObject* wxMDIChildFrameXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(frame, wxMDIChildFrame);

    wxMDIParentFrame* prt = wxDynamicCast(m_parentAsWindow, wxMDIParentFrame);

    if (prt == nullptr)
    {
        wxLogError("Error in resource: wxMDIChildFrame has no wxMDIParentFrame.");
        return nullptr;
    }

    frame->Create(prt, GetID(), GetText("title"), wxDefaultPosition, wxDefaultSize,
                  GetStyle("style", wxDEFAULT_FRAME_STYLE), GetName());

    SetupWindow(frame);

    CreateChildren(frame);

    if (GetBool("centered", FALSE))
        frame->Centre();

    return frame;
}

bool wxMDIChildFrameXmlHandler::CanHandle(wxXmlNode* node)
{
    return IsOfClass(node, "wxMDIChildFrame");
}

wxSplitterWindowXmlHandler::wxSplitterWindowXmlHandler() : wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxSP_3D);
    XRC_ADD_STYLE(wxSP_3DSASH);
    XRC_ADD_STYLE(wxSP_BORDER);
    XRC_ADD_STYLE(wxSP_NOBORDER);
    XRC_ADD_STYLE(wxSP_PERMIT_UNSPLIT);
    XRC_ADD_STYLE(wxSP_LIVE_UPDATE);

    XRC_ADD_STYLE(wxTAB_TRAVERSAL);
    XRC_ADD_STYLE(wxCLIP_CHILDREN);

    AddWindowStyles();
}

wxObject* wxSplitterWindowXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(frame, wxSplitterWindow);

    frame->Create(m_parentAsWindow, GetID(), wxDefaultPosition, wxDefaultSize,
                  GetStyle("style", wxSP_3D), GetName());

    SetupWindow(frame);

    CreateChildren(frame);

    if (frame->GetChildren().GetCount() != 2)
    {
        wxLogError("Error in resource: Splitter window needs exactly two children.");
        return nullptr;
    }

    frame->SetSplitMode(GetLong("splitmode", wxSPLIT_VERTICAL));
    long sashpos = GetLong("sashposition", 100);

    wxWindowList::compatibility_iterator node = frame->GetChildren().GetFirst();
    wxWindow* wnd1 = node->GetData();
    wxWindow* wnd2 = node->GetNext()->GetData();

    if (frame->GetSplitMode() == wxSPLIT_VERTICAL)
        frame->SplitVertically(wnd1, wnd2, sashpos);
    else
        frame->SplitHorizontally(wnd1, wnd2, sashpos);

    return frame;
}

bool wxSplitterWindowXmlHandler::CanHandle(wxXmlNode* node)
{
    return IsOfClass(node, "wxSplitterWindow");
}

#ifdef wxUSE_STC
wxStyledTextCtrlXmlHandler::wxStyledTextCtrlXmlHandler() : wxXmlResourceHandler()
{
    AddWindowStyles();
}

wxObject* wxStyledTextCtrlXmlHandler::DoCreateResource()
{
    XRC_MAKE_INSTANCE(frame, wxStyledTextCtrl);

    frame->Create(m_parentAsWindow, GetID(), wxDefaultPosition, wxDefaultSize, GetStyle("style", 0),
                  GetName());

    if (HasParam("size"))
        frame->SetSize(GetSize());
    if (HasParam("pos"))
        frame->Move(GetPosition());

    SetupWindow(frame);

    return frame;
}

bool wxStyledTextCtrlXmlHandler::CanHandle(wxXmlNode* node)
{
    return IsOfClass(node, "wxStyledTextCtrl");
}
#endif

wxGridXmlHandler::wxGridXmlHandler() : wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxTAB_TRAVERSAL);
    XRC_ADD_STYLE(wxCLIP_CHILDREN);

    AddWindowStyles();
}

wxObject* wxGridXmlHandler::DoCreateResource()
{
    wxGrid* grid = new wxGrid(m_parentAsWindow, GetID(), wxDefaultPosition, wxDefaultSize,
                              GetStyle("style", wxWANTS_CHARS), GetName());

    long cols = GetLong("numcols", 0);
    long rows = GetLong("numrows", 0);

    if (cols && rows)
        grid->CreateGrid(cols, rows, (wxGrid::wxGridSelectionModes) GetLong("selmode", 0));

    if (HasParam("size"))
        grid->SetSize(GetSize());
    if (HasParam("pos"))
        grid->Move(GetPosition());

    SetupWindow(grid);

    return grid;
}

bool wxGridXmlHandler::CanHandle(wxXmlNode* node)
{
    return IsOfClass(node, "wxGrid");
}

static void InitZipFileSystem()
{
    static bool done = false;
    if (!done)
    {
        done = true;
        wxFileSystem::AddHandler(new wxZipFSHandler());
    }
}

extern "C"
{
    EXPORT bool wxXmlResource_Load(wxXmlResource* self, wxString* filemask)
    {
        InitZipFileSystem();
        return self->Load(*filemask);
    }

    EXPORT void wxXmlResource_InitAllHandlers(wxXmlResource* self)
    {
        self->InitAllHandlers();
        self->AddHandler(new wxMDIParentFrameXmlHandler());
        self->AddHandler(new wxMDIChildFrameXmlHandler());
        self->AddHandler(new wxSplitterWindowXmlHandler());
#ifdef wxUSE_STC
        self->AddHandler(new wxStyledTextCtrlXmlHandler());
#endif
        self->AddHandler(new wxGridXmlHandler());
    }

    EXPORT wxXmlResource* wxXmlResource_Create(int flags)
    {
        wxXmlResource* self = wxXmlResource::Get();

        // Calling the wxc variant of InitAllHandlers() ensures additional
        // handlers for splitters etc. get initialized as well.
        wxXmlResource_InitAllHandlers(self);
        self->SetFlags(flags);
        return self;
    }

    EXPORT wxXmlResource* wxXmlResource_CreateFromFile(wxString* filemask, int flags)
    {
        wxXmlResource* self = wxXmlResource_Create(flags);
        if (self->Load(*filemask))
        {
            return self;
        }
        else
        {
            delete self;
            return nullptr;
        }
    }

    EXPORT void wxXmlResource_AddHandler(wxXmlResource* self, wxXmlResourceHandler* handler)
    {
        self->AddHandler(handler);
    }

    EXPORT void wxXmlResource_InsertHandler(wxXmlResource* self, wxXmlResourceHandler* handler)
    {
        self->InsertHandler(handler);
    }

    EXPORT void wxXmlResource_ClearHandlers(wxXmlResource* self)
    {
        self->ClearHandlers();
    }

    EXPORT void wxXmlResource_AddSubclassFactory(wxXmlResource* self, wxXmlSubclassFactory* factory)
    {
        self->AddSubclassFactory(factory);
    }

    EXPORT wxMenu* wxXmlResource_LoadMenu(wxXmlResource* self, wxString* name)
    {
        return self->LoadMenu(*name);
    }

    EXPORT wxMenuBar* wxXmlResource_LoadMenuBar(wxXmlResource* self, wxWindow* parent,
                                                wxString* name)
    {
        return self->LoadMenuBar(parent, *name);
    }

    EXPORT wxToolBar* wxXmlResource_LoadToolBar(wxXmlResource* self, wxWindow* parent,
                                                wxString* name)
    {
        return self->LoadToolBar(parent, *name);
    }

    EXPORT wxDialog* wxXmlResource_LoadDialog(wxXmlResource* self, wxWindow* parent, wxString* name)
    {
        wxDialog* dlg = new wxDialog;
        if (!self->LoadDialog(dlg, parent, *name))
        {
            delete dlg;
            return nullptr;
        }
        else
        {
            return dlg;
        }
    }

    EXPORT wxPanel* wxXmlResource_LoadPanel(wxXmlResource* self, wxWindow* parent, wxString* name)
    {
        return self->LoadPanel(parent, *name);
    }

    EXPORT wxFrame* wxXmlResource_LoadFrame(wxXmlResource* self, wxWindow* parent, wxString* name)
    {
        wxFrame* frame = new wxFrame;
        if (!self->LoadFrame(frame, parent, *name))
        {
            delete frame;
            return nullptr;
        }
        else
        {
            return frame;
        }
    }

    EXPORT void wxXmlResource_LoadBitmap(wxXmlResource* self, wxString* name, wxBitmap* _ref)
    {
        *_ref = self->LoadBitmap(*name);
    }

    EXPORT void wxXmlResource_LoadIcon(wxXmlResource* self, wxString* name, wxIcon* _ref)
    {
        *_ref = self->LoadIcon(*name);
    }

    EXPORT bool wxXmlResource_Unload(wxXmlResource* self, wxString* name)
    {
        return self->Unload(*name);
    }

    EXPORT bool wxXmlResource_AttachUnknownControl(wxXmlResource* self, wxString* name,
                                                   wxWindow* control, wxWindow* parent)
    {
        return self->AttachUnknownControl(*name, control, parent);
    }

    EXPORT int wxXmlResource_GetXRCID(wxXmlResource* self, wxString* str_id, int value_if_not_found)
    {
        return self->GetXRCID(*str_id, value_if_not_found);
    }

    EXPORT long wxXmlResource_GetVersion(wxXmlResource* self)
    {
        return self->GetVersion();
    }

    EXPORT int wxXmlResource_CompareVersion(wxXmlResource* self, int major, int minor, int release,
                                            int revision)
    {
        return self->CompareVersion(major, minor, release, revision);
    }

    EXPORT wxXmlResource* wxXmlResource_Get(wxXmlResource* self)
    {
        return wxXmlResource::Get();
    }

// BUILD_XRCGETCTRL_FN constructs functions for geting control pointers out of
// window hierarchies created from XRC files. The functions themselves
#define BUILD_XRCGETCTRL_FN(_typ)                                                                \
    EXPORT wx##_typ* wxXmlResource_Get##_typ(wxWindow* _win, wxString* _str_id)                  \
    {                                                                                            \
        return reinterpret_cast<wx##_typ*>(_win->FindWindow(wxXmlResource::GetXRCID(*_str_id))); \
    }
    // Construct the XRC control getter functions
    BUILD_XRCGETCTRL_FN(Sizer)
    BUILD_XRCGETCTRL_FN(BoxSizer)
    BUILD_XRCGETCTRL_FN(StaticBoxSizer)
    BUILD_XRCGETCTRL_FN(GridSizer)
    BUILD_XRCGETCTRL_FN(FlexGridSizer)
    BUILD_XRCGETCTRL_FN(BitmapButton)
    BUILD_XRCGETCTRL_FN(Button)
    BUILD_XRCGETCTRL_FN(CalendarCtrl)
    BUILD_XRCGETCTRL_FN(CheckBox)
    BUILD_XRCGETCTRL_FN(CheckListBox)
    BUILD_XRCGETCTRL_FN(Choice)
    BUILD_XRCGETCTRL_FN(ComboBox)
    BUILD_XRCGETCTRL_FN(Gauge)
    BUILD_XRCGETCTRL_FN(Grid)
    BUILD_XRCGETCTRL_FN(HtmlWindow)
    BUILD_XRCGETCTRL_FN(ListBox)
    BUILD_XRCGETCTRL_FN(ListCtrl)
    BUILD_XRCGETCTRL_FN(MDIChildFrame)
    BUILD_XRCGETCTRL_FN(MDIParentFrame)
    BUILD_XRCGETCTRL_FN(Menu)
    BUILD_XRCGETCTRL_FN(MenuBar)
    BUILD_XRCGETCTRL_FN(MenuItem)
    BUILD_XRCGETCTRL_FN(Notebook)
    BUILD_XRCGETCTRL_FN(Panel)
    BUILD_XRCGETCTRL_FN(RadioButton)
    BUILD_XRCGETCTRL_FN(RadioBox)
    BUILD_XRCGETCTRL_FN(ScrollBar)
    BUILD_XRCGETCTRL_FN(ScrolledWindow)
    BUILD_XRCGETCTRL_FN(Slider)
    BUILD_XRCGETCTRL_FN(SpinButton)
    BUILD_XRCGETCTRL_FN(SpinCtrl)
    BUILD_XRCGETCTRL_FN(SplitterWindow)
#ifdef wxUSE_STC
    BUILD_XRCGETCTRL_FN(StyledTextCtrl)
#else
    EXPORT void* wxXmlResource_GetStyledTextCtrl(wxWindow* _win, wxString* _str_id)
    {
        return nullptr;
    }
#endif
    BUILD_XRCGETCTRL_FN(StaticBitmap)
    BUILD_XRCGETCTRL_FN(StaticBox)
    BUILD_XRCGETCTRL_FN(StaticLine)
    BUILD_XRCGETCTRL_FN(StaticText)
    BUILD_XRCGETCTRL_FN(TextCtrl)
    BUILD_XRCGETCTRL_FN(TreeCtrl)

    EXPORT wxXmlResource* wxXmlResource_Set(wxXmlResource* self, wxXmlResource* res)
    {
        return self->Set(res);
    }

    EXPORT wxString* wxXmlResource_GetDomain(wxXmlResource* self)
    {
        wxString* buf = new wxString();
        *buf = self->GetDomain();
        return buf;
    }

    EXPORT void wxXmlResource_SetDomain(wxXmlResource* self, wxString* domain)
    {
        self->SetDomain(*domain);
    }

    EXPORT int wxXmlResource_GetFlags(wxXmlResource* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxXmlResource_SetFlags(wxXmlResource* self, int flags)
    {
        self->SetFlags(flags);
    }
}
