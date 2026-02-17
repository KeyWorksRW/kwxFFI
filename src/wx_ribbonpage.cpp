// wx_ribbonpage.cpp - wxRibbonPage wrapper
#include "wrapper.h"

// wxRibbonPage inherits from wxControl (via wxRibbonControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // Constructor
    EXPORT wxRibbonPage* wxRibbonPage_Create(wxRibbonBar* parent, int id, wxString* label,
                                             wxBitmap* icon, int style)
    {
        return new wxRibbonPage(parent, id, *label, icon ? *icon : wxNullBitmap, style);
    }

    // Panel management
    EXPORT void wxRibbonPage_DismissExpandedPanel(wxRibbonPage* self)
    {
        self->DismissExpandedPanel();
    }

    EXPORT bool wxRibbonPage_ScrollLines(wxRibbonPage* self, int lines)
    {
        return self->ScrollLines(lines);
    }

    EXPORT bool wxRibbonPage_ScrollPixels(wxRibbonPage* self, int pixels)
    {
        return self->ScrollPixels(pixels);
    }

    // Properties
    EXPORT wxString* wxRibbonPage_GetLabel(wxRibbonPage* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    // Layout
    EXPORT void wxRibbonPage_Realize(wxRibbonPage* self)
    {
        self->Realize();
    }

    EXPORT wxSize* wxRibbonPage_GetMinSize(wxRibbonPage* self)
    {
        wxSize* result = new wxSize();
        *result = self->GetMinSize();
        return result;
    }

    // Art provider
    EXPORT void wxRibbonPage_SetArtProvider(wxRibbonPage* self, wxRibbonArtProvider* art)
    {
        self->SetArtProvider(art);
    }

    EXPORT wxRibbonArtProvider* wxRibbonPage_GetArtProvider(wxRibbonPage* self)
    {
        return self->GetArtProvider();
    }
}
