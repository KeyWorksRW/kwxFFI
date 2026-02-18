// wx_ribbontoolbar.cpp - wxRibbonToolBar wrapper
#include "kwx_wrapper.h"

// wxRibbonToolBar inherits from wxControl (via wxRibbonControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // Constructor
    EXPORT wxRibbonToolBar* wxRibbonToolBar_Create(wxWindow* parent, int id, int x, int y, int width,
                                                   int height, int style)
    {
        return new wxRibbonToolBar(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Tool management - Add methods
    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_AddTool(wxRibbonToolBar* self, int tool_id,
                                                            wxBitmap* bitmap,
                                                            wxBitmap* bitmap_disabled,
                                                            wxString* help_string, int kind,
                                                            void* client_data)
    {
        wxBitmap bmpDisabled = bitmap_disabled ? *bitmap_disabled : wxNullBitmap;
        return self->AddTool(tool_id, *bitmap, bmpDisabled, *help_string, (wxRibbonButtonKind) kind,
                             (wxObject*) client_data);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_AddDropdownTool(wxRibbonToolBar* self,
                                                                    int tool_id, wxBitmap* bitmap,
                                                                    wxString* help_string)
    {
        return self->AddDropdownTool(tool_id, *bitmap, *help_string);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_AddHybridTool(wxRibbonToolBar* self,
                                                                  int tool_id, wxBitmap* bitmap,
                                                                  wxString* help_string)
    {
        return self->AddHybridTool(tool_id, *bitmap, *help_string);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_AddToggleTool(wxRibbonToolBar* self,
                                                                  int tool_id, wxBitmap* bitmap,
                                                                  wxString* help_string)
    {
        return self->AddToggleTool(tool_id, *bitmap, *help_string);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_AddSeparator(wxRibbonToolBar* self)
    {
        return self->AddSeparator();
    }

    // Tool management - Insert methods
    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_InsertTool(wxRibbonToolBar* self, size_t pos,
                                                               int tool_id, wxBitmap* bitmap,
                                                               wxBitmap* bitmap_disabled,
                                                               wxString* help_string, int kind,
                                                               void* client_data)
    {
        wxBitmap bmpDisabled = bitmap_disabled ? *bitmap_disabled : wxNullBitmap;
        return self->InsertTool(pos, tool_id, *bitmap, bmpDisabled, *help_string,
                                (wxRibbonButtonKind) kind, (wxObject*) client_data);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_InsertDropdownTool(wxRibbonToolBar* self,
                                                                       size_t pos, int tool_id,
                                                                       wxBitmap* bitmap,
                                                                       wxString* help_string)
    {
        return self->InsertDropdownTool(pos, tool_id, *bitmap, *help_string);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_InsertHybridTool(wxRibbonToolBar* self,
                                                                     size_t pos, int tool_id,
                                                                     wxBitmap* bitmap,
                                                                     wxString* help_string)
    {
        return self->InsertHybridTool(pos, tool_id, *bitmap, *help_string);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_InsertToggleTool(wxRibbonToolBar* self,
                                                                     size_t pos, int tool_id,
                                                                     wxBitmap* bitmap,
                                                                     wxString* help_string)
    {
        return self->InsertToggleTool(pos, tool_id, *bitmap, *help_string);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_InsertSeparator(wxRibbonToolBar* self,
                                                                    size_t pos)
    {
        return self->InsertSeparator(pos);
    }

    // Tool management - Delete/Clear
    EXPORT void wxRibbonToolBar_ClearTools(wxRibbonToolBar* self)
    {
        self->ClearTools();
    }

    EXPORT bool wxRibbonToolBar_DeleteTool(wxRibbonToolBar* self, int tool_id)
    {
        return self->DeleteTool(tool_id);
    }

    EXPORT bool wxRibbonToolBar_DeleteToolByPos(wxRibbonToolBar* self, size_t pos)
    {
        return self->DeleteToolByPos(pos);
    }

    // Tool access
    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_FindById(wxRibbonToolBar* self, int tool_id)
    {
        return self->FindById(tool_id);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_GetToolByPos(wxRibbonToolBar* self, size_t pos)
    {
        return self->GetToolByPos(pos);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_GetToolByPos_Coords(wxRibbonToolBar* self,
                                                                        int x, int y)
    {
        return self->GetToolByPos(x, y);
    }

    EXPORT size_t wxRibbonToolBar_GetToolCount(wxRibbonToolBar* self)
    {
        return self->GetToolCount();
    }

    EXPORT int wxRibbonToolBar_GetToolId(wxRibbonToolBar* self, wxRibbonToolBarToolBase* tool)
    {
        return self->GetToolId(tool);
    }

    EXPORT wxRibbonToolBarToolBase* wxRibbonToolBar_GetActiveTool(wxRibbonToolBar* self)
    {
        return self->GetActiveTool();
    }

    EXPORT int wxRibbonToolBar_GetToolPos(wxRibbonToolBar* self, int tool_id)
    {
        return self->GetToolPos(tool_id);
    }

    EXPORT void wxRibbonToolBar_GetToolRect(wxRibbonToolBar* self, int tool_id, int* x, int* y,
                                            int* width, int* height)
    {
        wxRect r = self->GetToolRect(tool_id);
        *x = r.x;
        *y = r.y;
        *width = r.width;
        *height = r.height;
    }

    // Tool properties
    EXPORT void wxRibbonToolBar_EnableTool(wxRibbonToolBar* self, int tool_id, bool enable)
    {
        self->EnableTool(tool_id, enable);
    }

    EXPORT bool wxRibbonToolBar_GetToolEnabled(wxRibbonToolBar* self, int tool_id)
    {
        return self->GetToolEnabled(tool_id);
    }

    EXPORT wxString* wxRibbonToolBar_GetToolHelpString(wxRibbonToolBar* self, int tool_id)
    {
        wxString* result = new wxString();
        *result = self->GetToolHelpString(tool_id);
        return result;
    }

    EXPORT void wxRibbonToolBar_SetToolHelpString(wxRibbonToolBar* self, int tool_id,
                                                  wxString* help_string)
    {
        self->SetToolHelpString(tool_id, *help_string);
    }

    EXPORT int wxRibbonToolBar_GetToolKind(wxRibbonToolBar* self, int tool_id)
    {
        return (int) self->GetToolKind(tool_id);
    }

    EXPORT bool wxRibbonToolBar_GetToolState(wxRibbonToolBar* self, int tool_id)
    {
        return self->GetToolState(tool_id);
    }

    EXPORT void wxRibbonToolBar_SetToolNormalBitmap(wxRibbonToolBar* self, int tool_id,
                                                    wxBitmap* bitmap)
    {
        self->SetToolNormalBitmap(tool_id, *bitmap);
    }

    EXPORT void wxRibbonToolBar_SetToolDisabledBitmap(wxRibbonToolBar* self, int tool_id,
                                                      wxBitmap* bitmap)
    {
        self->SetToolDisabledBitmap(tool_id, *bitmap);
    }

    // Client data
    EXPORT void wxRibbonToolBar_SetToolClientData(wxRibbonToolBar* self, int tool_id,
                                                  wxObject* clientData)
    {
        self->SetToolClientData(tool_id, clientData);
    }

    EXPORT wxObject* wxRibbonToolBar_GetToolClientData(wxRibbonToolBar* self, int tool_id)
    {
        return self->GetToolClientData(tool_id);
    }

    // Layout
    EXPORT void wxRibbonToolBar_SetRows(wxRibbonToolBar* self, int nMin, int nMax)
    {
        self->SetRows(nMin, nMax);
    }

    EXPORT void wxRibbonToolBar_Realize(wxRibbonToolBar* self)
    {
        self->Realize();
    }

    // Art provider
    EXPORT void wxRibbonToolBar_SetArtProvider(wxRibbonToolBar* self, wxRibbonArtProvider* art)
    {
        self->SetArtProvider(art);
    }

    EXPORT wxRibbonArtProvider* wxRibbonToolBar_GetArtProvider(wxRibbonToolBar* self)
    {
        return self->GetArtProvider();
    }

    // Events
    EXPORT int expEVT_RIBBONTOOLBAR_CLICKED()
    {
        return wxEVT_RIBBONTOOLBAR_CLICKED;
    }

    EXPORT int expEVT_RIBBONTOOLBAR_DROPDOWN_CLICKED()
    {
        return wxEVT_RIBBONTOOLBAR_DROPDOWN_CLICKED;
    }

}  // extern "C"
