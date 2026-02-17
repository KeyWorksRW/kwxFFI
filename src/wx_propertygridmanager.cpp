// wx_propertygridmanager.cpp
// C wrapper for wxPropertyGridManager

#include "wrapper.h"

// wxPropertyGridManager inherits from wxPanel (wxWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    // Constructor
    EXPORT wxPropertyGridManager* wxPropertyGridManager_Create(wxWindow* parent, int id, int x,
                                                               int y, int width, int height, int style)
    {
        return new wxPropertyGridManager(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Page management
    EXPORT wxPropertyGridPage* wxPropertyGridManager_AddPage(wxPropertyGridManager* self,
                                                             wxString* label, wxBitmapBundle* bmp)
    {
        return self->AddPage(*label, bmp ? *bmp : wxBitmapBundle(), nullptr);
    }

    EXPORT wxPropertyGridPage* wxPropertyGridManager_InsertPage(wxPropertyGridManager* self,
                                                                int index, wxString* label,
                                                                wxBitmapBundle* bmp)
    {
        return self->InsertPage(index, *label, bmp ? *bmp : wxBitmapBundle(), nullptr);
    }

    EXPORT bool wxPropertyGridManager_RemovePage(wxPropertyGridManager* self, int page)
    {
        return self->RemovePage(page);
    }

    EXPORT void wxPropertyGridManager_ClearPage(wxPropertyGridManager* self, int page)
    {
        self->ClearPage(page);
    }

    EXPORT int wxPropertyGridManager_GetPageCount(wxPropertyGridManager* self)
    {
        return (int) self->GetPageCount();
    }

    EXPORT wxPropertyGridPage* wxPropertyGridManager_GetPage(wxPropertyGridManager* self,
                                                             unsigned int index)
    {
        return self->GetPage(index);
    }

    EXPORT int wxPropertyGridManager_GetPageByName(wxPropertyGridManager* self, wxString* name)
    {
        return self->GetPageByName(*name);
    }

    EXPORT wxString* wxPropertyGridManager_GetPageName(wxPropertyGridManager* self, int index)
    {
        wxString* result = new wxString();
        *result = self->GetPageName(index);
        return result;
    }

    EXPORT int wxPropertyGridManager_GetSelectedPage(wxPropertyGridManager* self)
    {
        return self->GetSelectedPage();
    }

    EXPORT void wxPropertyGridManager_SelectPage(wxPropertyGridManager* self, int index)
    {
        self->SelectPage(index);
    }

    EXPORT void wxPropertyGridManager_SelectPageByLabel(wxPropertyGridManager* self,
                                                        wxString* label)
    {
        self->SelectPage(*label);
    }

    // Property grid access
    EXPORT wxPropertyGrid* wxPropertyGridManager_GetGrid(wxPropertyGridManager* self)
    {
        return self->GetGrid();
    }

    EXPORT wxPropertyGridPage* wxPropertyGridManager_GetCurrentPage(wxPropertyGridManager* self)
    {
        return self->GetCurrentPage();
    }

    // Toolbar methods
    EXPORT wxToolBar* wxPropertyGridManager_GetToolBar(wxPropertyGridManager* self)
    {
        return self->GetToolBar();
    }

    // Description box
    EXPORT void wxPropertyGridManager_SetDescBoxHeight(wxPropertyGridManager* self, int descBoxHeight,
                                                       bool refresh)
    {
        self->SetDescBoxHeight(descBoxHeight, refresh);
    }

    EXPORT int wxPropertyGridManager_GetDescBoxHeight(wxPropertyGridManager* self)
    {
        return self->GetDescBoxHeight();
    }

    EXPORT void wxPropertyGridManager_ShowHeader(wxPropertyGridManager* self, bool show)
    {
        self->ShowHeader(show);
    }

    EXPORT bool wxPropertyGridManager_IsAnyModified(wxPropertyGridManager* self)
    {
        return self->IsAnyModified();
    }

    EXPORT bool wxPropertyGridManager_IsPageModified(wxPropertyGridManager* self, size_t index)
    {
        return self->IsPageModified(index);
    }

    EXPORT void wxPropertyGridManager_Clear(wxPropertyGridManager* self)
    {
        self->Clear();
    }

    // wxPropertyGridPage methods
    EXPORT void wxPropertyGridPage_Clear(wxPropertyGridPage* self)
    {
        self->Clear();
    }

    EXPORT int wxPropertyGridPage_GetIndex(wxPropertyGridPage* self)
    {
        return self->GetIndex();
    }

    EXPORT wxPGProperty* wxPropertyGridPage_GetRoot(wxPropertyGridPage* self)
    {
        return self->GetRoot();
    }

    EXPORT int wxPropertyGridPage_GetSplitterPosition(wxPropertyGridPage* self, int col)
    {
        return self->GetSplitterPosition(col);
    }

    EXPORT void wxPropertyGridPage_SetSplitterPosition(wxPropertyGridPage* self, int splitterPos,
                                                       int col)
    {
        self->SetSplitterPosition(splitterPos, col);
    }

    // Style constants
    WXFFI_CONSTANT_INT(expPGMAN_DEFAULT_STYLE, wxPGMAN_DEFAULT_STYLE)
}
