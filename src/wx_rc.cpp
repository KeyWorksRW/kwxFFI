#include "wrapper.h"

#include <wx/fs_zip.h>
#include <wx/html/htmlwin.h>
#include <wx/xrc/xmlres.h>

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
    }

    EXPORT wxXmlResource* wxXmlResource_Create(int flags)
    {
        wxXmlResource* self = wxXmlResource::Get();
        self->InitAllHandlers();
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

    EXPORT void wxXmlResource_LoadBitmap(wxXmlResource* self, wxString* name, wxBitmap* ref)
    {
        *ref = self->LoadBitmap(*name);
    }

    EXPORT void wxXmlResource_LoadIcon(wxXmlResource* self, wxString* name, wxIcon* ref)
    {
        *ref = self->LoadIcon(*name);
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
#define BUILD_XRCGETCTRL_FN(type)                                                             \
    EXPORT wx##type* wxXmlResource_Get##type(wxWindow* win, wxString* strId)                  \
    {                                                                                         \
        return reinterpret_cast<wx##type*>(win->FindWindow(wxXmlResource::GetXRCID(*strId))); \
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
    // StyledTextCtrl requires wx/stc/stc.h which may not be available
    EXPORT void* wxXmlResource_GetStyledTextCtrl(wxWindow* win, wxString* strId)
    {
        return win->FindWindow(wxXmlResource::GetXRCID(*strId));
    }
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
