// wx_ribbonpanel.cpp - wxRibbonPanel wrapper
#include "wrapper.h"

extern "C"
{
    // Constructor
    EXPORT wxRibbonPanel* wxRibbonPanel_Create(wxWindow* parent, int id, wxString* label,
                                               wxBitmap* icon, int x, int y, int width, int height,
                                               int style)
    {
        return new wxRibbonPanel(parent, id, *label, icon ? *icon : wxNullBitmap, wxPoint(x, y),
                                 wxSize(width, height), style);
    }

    // Properties
    EXPORT wxString* wxRibbonPanel_GetLabel(wxRibbonPanel* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    // State
    EXPORT bool wxRibbonPanel_IsMinimised(wxRibbonPanel* self)
    {
        return self->IsMinimised();
    }

    EXPORT bool wxRibbonPanel_IsMinimised_AtSize(wxRibbonPanel* self, int width, int height)
    {
        return self->IsMinimised(wxSize(width, height));
    }

    EXPORT bool wxRibbonPanel_IsHovered(wxRibbonPanel* self)
    {
        return self->IsHovered();
    }

    EXPORT bool wxRibbonPanel_IsExtButtonHovered(wxRibbonPanel* self)
    {
        return self->IsExtButtonHovered();
    }

    EXPORT bool wxRibbonPanel_CanAutoMinimise(wxRibbonPanel* self)
    {
        return self->CanAutoMinimise();
    }

    // Display
    EXPORT bool wxRibbonPanel_ShowExpanded(wxRibbonPanel* self)
    {
        return self->ShowExpanded();
    }

    EXPORT bool wxRibbonPanel_HideExpanded(wxRibbonPanel* self)
    {
        return self->HideExpanded();
    }

    // Layout
    EXPORT void wxRibbonPanel_Realize(wxRibbonPanel* self)
    {
        self->Realize();
    }

    EXPORT wxSize* wxRibbonPanel_GetMinSize(wxRibbonPanel* self)
    {
        wxSize* result = new wxSize();
        *result = self->GetMinSize();
        return result;
    }

    // Art provider
    EXPORT void wxRibbonPanel_SetArtProvider(wxRibbonPanel* self, wxRibbonArtProvider* art)
    {
        self->SetArtProvider(art);
    }

    EXPORT wxRibbonArtProvider* wxRibbonPanel_GetArtProvider(wxRibbonPanel* self)
    {
        return self->GetArtProvider();
    }

    // Events
    MAKE_EVENT_WRAPPER(EVT_RIBBONPANEL_EXTBUTTON_ACTIVATED);

    // Style constants
    WXFFI_EXPORT(int, expRIBBON_PANEL_DEFAULT_STYLE)()
    {
        return wxRIBBON_PANEL_DEFAULT_STYLE;
    }
    WXFFI_EXPORT(int, expRIBBON_PANEL_NO_AUTO_MINIMISE)()
    {
        return wxRIBBON_PANEL_NO_AUTO_MINIMISE;
    }
    WXFFI_EXPORT(int, expRIBBON_PANEL_EXT_BUTTON)()
    {
        return wxRIBBON_PANEL_EXT_BUTTON;
    }
    WXFFI_EXPORT(int, expRIBBON_PANEL_MINIMISE_BUTTON)()
    {
        return wxRIBBON_PANEL_MINIMISE_BUTTON;
    }
    WXFFI_EXPORT(int, expRIBBON_PANEL_STRETCH)()
    {
        return wxRIBBON_PANEL_STRETCH;
    }
    WXFFI_EXPORT(int, expRIBBON_PANEL_FLEXIBLE)()
    {
        return wxRIBBON_PANEL_FLEXIBLE;
    }
}
