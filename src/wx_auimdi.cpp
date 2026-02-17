#include "wrapper.h"

// wxAuiMDIParentFrame inherits from wxFrame (wxTopLevelWindow).
// wxAuiMDIChildFrame inherits from wxTDIChildFrame.
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    // ============================================================================
    // wxAuiMDIParentFrame - AUI MDI parent frame
    // ============================================================================

    EXPORT wxAuiMDIParentFrame* wxAuiMDIParentFrame_Create(wxWindow* parent, int id,
                                                           wxString* title, int x, int y, int width,
                                                           int height, int style)
    {
        return new wxAuiMDIParentFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT wxAuiMDIChildFrame* wxAuiMDIParentFrame_GetActiveChild(wxAuiMDIParentFrame* self)
    {
        return self->GetActiveChild();
    }

    EXPORT void wxAuiMDIParentFrame_SetActiveChild(wxAuiMDIParentFrame* self,
                                                   wxAuiMDIChildFrame* child)
    {
        self->SetActiveChild(child);
    }

    EXPORT void wxAuiMDIParentFrame_ActivateNext(wxAuiMDIParentFrame* self)
    {
        self->ActivateNext();
    }

    EXPORT void wxAuiMDIParentFrame_ActivatePrevious(wxAuiMDIParentFrame* self)
    {
        self->ActivatePrevious();
    }

    EXPORT void wxAuiMDIParentFrame_Cascade(wxAuiMDIParentFrame* self)
    {
        self->Cascade();
    }

    EXPORT void wxAuiMDIParentFrame_Tile(wxAuiMDIParentFrame* self, int orient)
    {
        self->Tile((wxOrientation) orient);
    }

    EXPORT wxMenuBar* wxAuiMDIParentFrame_GetMenuBar(wxAuiMDIParentFrame* self)
    {
        return self->GetMenuBar();
    }

    EXPORT void wxAuiMDIParentFrame_SetMenuBar(wxAuiMDIParentFrame* self, wxMenuBar* menuBar)
    {
        self->SetMenuBar(menuBar);
    }

    EXPORT wxStatusBar* wxAuiMDIParentFrame_GetStatusBar(wxAuiMDIParentFrame* self)
    {
        return self->GetStatusBar();
    }

    EXPORT wxStatusBar* wxAuiMDIParentFrame_CreateStatusBar(wxAuiMDIParentFrame* self, int number,
                                                            int style, int id)
    {
        return self->CreateStatusBar(number, style, id);
    }

    EXPORT wxToolBar* wxAuiMDIParentFrame_GetToolBar(wxAuiMDIParentFrame* self)
    {
        return self->GetToolBar();
    }

    EXPORT wxToolBar* wxAuiMDIParentFrame_CreateToolBar(wxAuiMDIParentFrame* self, int style,
                                                        int id)
    {
        return self->CreateToolBar(style, id);
    }

    EXPORT wxAuiNotebook* wxAuiMDIParentFrame_GetNotebook(wxAuiMDIParentFrame* self)
    {
        return self->GetNotebook();
    }

    // ============================================================================
    // wxAuiMDIChildFrame - AUI MDI child frame
    // ============================================================================

    EXPORT wxAuiMDIChildFrame* wxAuiMDIChildFrame_Create(wxAuiMDIParentFrame* parent, int id,
                                                         wxString* title, int x, int y, int width,
                                                         int height, int style)
    {
        return new wxAuiMDIChildFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxAuiMDIChildFrame_Activate(wxAuiMDIChildFrame* self)
    {
        self->Activate();
    }

    EXPORT wxMenuBar* wxAuiMDIChildFrame_GetMenuBar(wxAuiMDIChildFrame* self)
    {
        return self->GetMenuBar();
    }

    EXPORT void wxAuiMDIChildFrame_SetMenuBar(wxAuiMDIChildFrame* self, wxMenuBar* menuBar)
    {
        self->SetMenuBar(menuBar);
    }

    EXPORT wxStatusBar* wxAuiMDIChildFrame_GetStatusBar(wxAuiMDIChildFrame* self)
    {
        return self->GetStatusBar();
    }

    EXPORT wxStatusBar* wxAuiMDIChildFrame_CreateStatusBar(wxAuiMDIChildFrame* self, int number,
                                                           int style, int id)
    {
        return self->CreateStatusBar(number, style, id);
    }

    EXPORT wxToolBar* wxAuiMDIChildFrame_GetToolBar(wxAuiMDIChildFrame* self)
    {
        return self->GetToolBar();
    }

    EXPORT wxToolBar* wxAuiMDIChildFrame_CreateToolBar(wxAuiMDIChildFrame* self, int style, int id)
    {
        return self->CreateToolBar(style, id, wxString(wxEmptyString));
    }

    EXPORT void wxAuiMDIChildFrame_SetTitle(wxAuiMDIChildFrame* self, wxString* title)
    {
        self->SetTitle(*title);
    }

    EXPORT wxString* wxAuiMDIChildFrame_GetTitle(wxAuiMDIChildFrame* self)
    {
        wxString* result = new wxString();
        *result = self->GetTitle();
        return result;
    }

    EXPORT void wxAuiMDIChildFrame_SetIcons(wxAuiMDIChildFrame* self, wxIconBundle* icons)
    {
        self->SetIcons(*icons);
    }

    EXPORT wxIconBundle* wxAuiMDIChildFrame_GetIcons(wxAuiMDIChildFrame* self)
    {
        wxIconBundle* result = new wxIconBundle();
        *result = self->GetIcons();
        return result;
    }

    EXPORT void wxAuiMDIChildFrame_SetIcon(wxAuiMDIChildFrame* self, wxIcon* icon)
    {
        self->SetIcon(*icon);
    }

    EXPORT wxIcon* wxAuiMDIChildFrame_GetIcon(wxAuiMDIChildFrame* self)
    {
        wxIcon* result = new wxIcon();
        *result = self->GetIcon();
        return result;
    }

    EXPORT wxWindow* wxAuiMDIChildFrame_GetMDIParent(wxAuiMDIChildFrame* self)
    {
        return self->GetMDIParent();
    }
}
