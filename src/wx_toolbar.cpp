#include "wrapper.h"

extern "C"
{
    EXPORT wxToolBar* wxToolBar_Create(wxWindow* parent, int id, int x, int y, int width,
                                       int height, int style)
    {
        return new wxToolBar(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxToolBar_Delete(wxToolBar* self)
    {
        delete self;
    }

    EXPORT int wxToolBar_AddControl(wxToolBar* self, wxControl* ctrl)
    {
        return self->AddControl(ctrl) != nullptr;
    }

    EXPORT void wxToolBar_AddSeparator(wxToolBar* self)
    {
        self->AddSeparator();
    }

    EXPORT void wxToolBar_AddTool(wxToolBar* self, int toolid, const wxString& label,
                                  const wxBitmap& bitmap, const wxBitmap& bmpDisabled,
                                  wxItemKind kind = wxITEM_NORMAL,
                                  const wxString& shortHelp = wxEmptyString,
                                  const wxString& longHelp = wxEmptyString,
                                  wxObject* data = nullptr)
    {
        // the full AddTool() function
        //
        // If bmpDisabled is wxNullBitmap, a shadowed version of the normal bitmap
        // is created and used as the disabled image.
        self->AddTool(toolid, label, bitmap, bmpDisabled, wxITEM_NORMAL, shortHelp, longHelp, data);
    }

    // Obsolete
    // EWXWEXPORT(void,wxToolBar_AddToolEx)(wxToolBar* self,int id,wxBitmap* bmp1,wxBitmap*
    // bmp2,bool tgl,int x,int y,wxObject* dat,wxString* shelp,wxString* lhelp)

    EXPORT bool wxToolBar_DeleteTool(wxToolBar* self, int id)
    {
        return self->DeleteTool(id);
    }

    EXPORT bool wxToolBar_DeleteToolByPos(wxToolBar* self, int pos)
    {
        return self->DeleteToolByPos(pos);
    }

    EXPORT void wxToolBar_EnableTool(wxToolBar* self, int id, bool enb)
    {
        self->EnableTool(id, enb);
    }

    EXPORT wxSize* wxToolBar_GetToolSize(wxToolBar* self)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetToolSize();
        return sz;
    }

    EXPORT wxSize* wxToolBar_GetToolBitmapSize(wxToolBar* self)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetToolBitmapSize();
        return sz;
    }

    EXPORT wxSize* wxToolBar_GetMargins(wxToolBar* self)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetMargins();
        return sz;
    }

    EXPORT void* wxToolBar_GetToolClientData(wxToolBar* self, int id)
    {
        return (void*) self->GetToolClientData(id);
    }

    EXPORT bool wxToolBar_GetToolEnabled(wxToolBar* self, int id)
    {
        return self->GetToolEnabled(id);
    }

    EXPORT wxString* wxToolBar_GetToolLongHelp(wxToolBar* self, int id)
    {
        wxString* result = new wxString();
        *result = self->GetToolLongHelp(id);
        return result;
    }

    EXPORT int wxToolBar_GetToolPacking(wxToolBar* self)
    {
        return self->GetToolPacking();
    }

    EXPORT wxString* wxToolBar_GetToolShortHelp(wxToolBar* self, int id)
    {
        wxString* result = new wxString();
        *result = self->GetToolShortHelp(id);
        return result;
    }

    EXPORT bool wxToolBar_GetToolState(wxToolBar* self, int id)
    {
        return self->GetToolState(id);
    }

    EXPORT void wxToolBar_InsertControl(wxToolBar* self, int pos, wxControl* ctrl)
    {
        self->InsertControl((size_t) pos, ctrl);
    }

    EXPORT void wxToolBar_InsertSeparator(wxToolBar* self, int pos)
    {
        self->InsertSeparator((size_t) pos);
    }

    // Obsolete
    // EWXWEXPORT(void,wxToolBar_InsertTool)(wxToolBar* self,int pos,int id,wxBitmap* bmp1,wxBitmap*
    // bmp2,bool tgl,wxObject* dat,wxString* shelp,wxString* lhelp)

    EXPORT bool wxToolBar_Realize(wxToolBar* self)
    {
        return self->Realize();
    }

    EXPORT void wxToolBar_RemoveTool(wxToolBar* self, int id)
    {
        self->RemoveTool(id);
    }

    EXPORT void wxToolBar_SetMargins(wxToolBar* self, int x, int y)
    {
#ifdef __WIN32__
        self->SetMargins(wxSize(x, y));
#else
        self->SetMargins(x, y);
#endif
    }

    EXPORT void wxToolBar_SetToolBitmapSize(wxToolBar* self, int x, int y)
    {
        self->SetToolBitmapSize(wxSize(x, y));
    }

    EXPORT void wxToolBar_SetToolClientData(wxToolBar* self, int id, wxObject* dat)
    {
        self->SetToolClientData(id, dat);
    }

    EXPORT void wxToolBar_SetToolLongHelp(wxToolBar* self, int id, wxString* str)
    {
        self->SetToolLongHelp(id, *str);
    }

    EXPORT void wxToolBar_SetToolPacking(wxToolBar* self, int val)
    {
        self->SetToolPacking(val);
    }

    EXPORT void wxToolBar_SetToolShortHelp(wxToolBar* self, int id, wxString* str)
    {
        self->SetToolShortHelp(id, *str);
    }

    EXPORT void wxToolBar_SetToolSeparation(wxToolBar* self, int val)
    {
        self->SetToolSeparation(val);
    }

    EXPORT void wxToolBar_ToggleTool(wxToolBar* self, int id, bool val)
    {
        self->ToggleTool(id, val);
    }
}
