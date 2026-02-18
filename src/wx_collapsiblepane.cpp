// wx_collapsiblepane.cpp
// C wrapper for wxCollapsiblePane

#include "kwx_wrapper.h"

// wxCollapsiblePane inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // Constructor
    EXPORT wxCollapsiblePane* wxCollapsiblePane_Create(wxWindow* parent, int id, wxString* label,
                                                       int x, int y, int width, int height, int style)
    {
        return new wxCollapsiblePane(parent, id, *label, wxPoint(x, y), wxSize(width, height), style);
    }

    // Collapse/Expand
    EXPORT void wxCollapsiblePane_Collapse(wxCollapsiblePane* self, bool collapse)
    {
        self->Collapse(collapse);
    }

    EXPORT void wxCollapsiblePane_Expand(wxCollapsiblePane* self)
    {
        self->Expand();
    }

    EXPORT bool wxCollapsiblePane_IsCollapsed(wxCollapsiblePane* self)
    {
        return self->IsCollapsed();
    }

    EXPORT bool wxCollapsiblePane_IsExpanded(wxCollapsiblePane* self)
    {
        return self->IsExpanded();
    }

    // Get the pane window
    EXPORT wxWindow* wxCollapsiblePane_GetPane(wxCollapsiblePane* self)
    {
        return self->GetPane();
    }

    // Label methods
    EXPORT wxString* wxCollapsiblePane_GetLabel(wxCollapsiblePane* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT void wxCollapsiblePane_SetLabel(wxCollapsiblePane* self, wxString* label)
    {
        self->SetLabel(*label);
    }

    // wxCollapsiblePaneEvent methods
    EXPORT bool wxCollapsiblePaneEvent_GetCollapsed(wxCollapsiblePaneEvent* self)
    {
        return self->GetCollapsed();
    }

    EXPORT void wxCollapsiblePaneEvent_SetCollapsed(wxCollapsiblePaneEvent* self, bool collapsed)
    {
        self->SetCollapsed(collapsed);
    }

    // Event export
    MAKE_EVENT_WRAPPER(EVT_COLLAPSIBLEPANE_CHANGED)

    // Style constants
    WXFFI_CONSTANT_INT(expCP_DEFAULT_STYLE, wxCP_DEFAULT_STYLE)
    WXFFI_CONSTANT_INT(expCP_NO_TLW_RESIZE, wxCP_NO_TLW_RESIZE)
}
