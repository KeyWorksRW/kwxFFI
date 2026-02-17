// wx_ribbonbar.cpp - wxRibbonBar wrapper
#include "wrapper.h"

// wxRibbonBar inherits from wxControl (via wxRibbonControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // Constructor
    EXPORT wxRibbonBar* wxRibbonBar_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                           int style)
    {
        return new wxRibbonBar(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Page management - Note: AddPage is protected, not exposed
    EXPORT void wxRibbonBar_DismissExpandedPanel(wxRibbonBar* self)
    {
        self->DismissExpandedPanel();
    }

    EXPORT wxRibbonPage* wxRibbonBar_GetPage(wxRibbonBar* self, int index)
    {
        return self->GetPage(index);
    }

    EXPORT size_t wxRibbonBar_GetPageCount(wxRibbonBar* self)
    {
        return self->GetPageCount();
    }

    EXPORT bool wxRibbonBar_DeletePage(wxRibbonBar* self, size_t index)
    {
        self->DeletePage(index);
        return true;  // Always succeeds if it doesn't throw
    }

    EXPORT void wxRibbonBar_ClearPages(wxRibbonBar* self)
    {
        self->ClearPages();
    }

    // Active page
    EXPORT int wxRibbonBar_GetActivePage(wxRibbonBar* self)
    {
        return self->GetActivePage();
    }

    EXPORT void wxRibbonBar_SetActivePage_ByIndex(wxRibbonBar* self, size_t page)
    {
        self->SetActivePage(page);
    }

    EXPORT void wxRibbonBar_SetActivePage_ByPtr(wxRibbonBar* self, wxRibbonPage* page)
    {
        self->SetActivePage(page);
    }

    // Layout
    EXPORT void wxRibbonBar_Realize(wxRibbonBar* self)
    {
        self->Realize();
    }

    // Art provider
    EXPORT void wxRibbonBar_SetArtProvider(wxRibbonBar* self, wxRibbonArtProvider* art)
    {
        self->SetArtProvider(art);
    }

    EXPORT wxRibbonArtProvider* wxRibbonBar_GetArtProvider(wxRibbonBar* self)
    {
        return self->GetArtProvider();
    }

    // Events
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_PAGE_CHANGED);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_PAGE_CHANGING);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_TAB_MIDDLE_DOWN);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_TAB_MIDDLE_UP);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_TAB_RIGHT_DOWN);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_TAB_RIGHT_UP);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_TAB_LEFT_DCLICK);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_TOGGLED);
    MAKE_EVENT_WRAPPER(EVT_RIBBONBAR_HELP_CLICK);

    // Style constants
    WXFFI_EXPORT(int, expRIBBON_BAR_DEFAULT_STYLE)()
    {
        return wxRIBBON_BAR_DEFAULT_STYLE;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_FOLDBAR_STYLE)()
    {
        return wxRIBBON_BAR_FOLDBAR_STYLE;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PAGE_LABELS)()
    {
        return wxRIBBON_BAR_SHOW_PAGE_LABELS;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PAGE_ICONS)()
    {
        return wxRIBBON_BAR_SHOW_PAGE_ICONS;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_FLOW_HORIZONTAL)()
    {
        return wxRIBBON_BAR_FLOW_HORIZONTAL;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_FLOW_VERTICAL)()
    {
        return wxRIBBON_BAR_FLOW_VERTICAL;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS)()
    {
        return wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PANEL_MINIMISE_BUTTONS)()
    {
        return wxRIBBON_BAR_SHOW_PANEL_MINIMISE_BUTTONS;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_ALWAYS_SHOW_TABS)()
    {
        return wxRIBBON_BAR_ALWAYS_SHOW_TABS;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_TOGGLE_BUTTON)()
    {
        return wxRIBBON_BAR_SHOW_TOGGLE_BUTTON;
    }
    WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_HELP_BUTTON)()
    {
        return wxRIBBON_BAR_SHOW_HELP_BUTTON;
    }
}
