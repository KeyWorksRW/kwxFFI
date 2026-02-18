// wxPropertySheetDialog - Property sheet dialog with book control
#include "kwx_wrapper.h"

// wxPropertySheetDialog inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    // Constructor
    EXPORT wxPropertySheetDialog* wxPropertySheetDialog_Create(wxWindow* parent, int id,
                                                               wxString* title, int x, int y, int width,
                                                               int height, int style)
    {
        return new wxPropertySheetDialog(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    // Create buttons
    EXPORT void wxPropertySheetDialog_CreateButtons(wxPropertySheetDialog* self, int flags)
    {
        self->CreateButtons(flags);
    }

    // Get book control
    EXPORT wxBookCtrlBase* wxPropertySheetDialog_GetBookCtrl(wxPropertySheetDialog* self)
    {
        return self->GetBookCtrl();
    }

    // Get inner sizer
    EXPORT wxSizer* wxPropertySheetDialog_GetInnerSizer(wxPropertySheetDialog* self)
    {
        return self->GetInnerSizer();
    }

    // Set inner sizer
    EXPORT void wxPropertySheetDialog_SetInnerSizer(wxPropertySheetDialog* self, wxSizer* sizer)
    {
        self->SetInnerSizer(sizer);
    }

    // Layout
    EXPORT void wxPropertySheetDialog_LayoutDialog(wxPropertySheetDialog* self, int centreFlags)
    {
        self->LayoutDialog(centreFlags);
    }

    // Get sheet style
    EXPORT int wxPropertySheetDialog_GetSheetStyle(wxPropertySheetDialog* self)
    {
        return self->GetSheetStyle();
    }

    // Set sheet style
    EXPORT void wxPropertySheetDialog_SetSheetStyle(wxPropertySheetDialog* self, int style)
    {
        self->SetSheetStyle(style);
    }

    // Get sheet outer border
    EXPORT int wxPropertySheetDialog_GetSheetOuterBorder(wxPropertySheetDialog* self)
    {
        return self->GetSheetOuterBorder();
    }

    // Set sheet outer border
    EXPORT void wxPropertySheetDialog_SetSheetOuterBorder(wxPropertySheetDialog* self, int border)
    {
        self->SetSheetOuterBorder(border);
    }

    // Get sheet inner border
    EXPORT int wxPropertySheetDialog_GetSheetInnerBorder(wxPropertySheetDialog* self)
    {
        return self->GetSheetInnerBorder();
    }

    // Set sheet inner border
    EXPORT void wxPropertySheetDialog_SetSheetInnerBorder(wxPropertySheetDialog* self, int border)
    {
        self->SetSheetInnerBorder(border);
    }

    // Export style constants
    WXFFI_EXPORT(int, expPROPSHEET_DEFAULT)()
    {
        return wxPROPSHEET_DEFAULT;
    }
    WXFFI_EXPORT(int, expPROPSHEET_NOTEBOOK)()
    {
        return wxPROPSHEET_NOTEBOOK;
    }
    WXFFI_EXPORT(int, expPROPSHEET_TOOLBOOK)()
    {
        return wxPROPSHEET_TOOLBOOK;
    }
    WXFFI_EXPORT(int, expPROPSHEET_CHOICEBOOK)()
    {
        return wxPROPSHEET_CHOICEBOOK;
    }
    WXFFI_EXPORT(int, expPROPSHEET_LISTBOOK)()
    {
        return wxPROPSHEET_LISTBOOK;
    }
    WXFFI_EXPORT(int, expPROPSHEET_BUTTONTOOLBOOK)()
    {
        return wxPROPSHEET_BUTTONTOOLBOOK;
    }
    WXFFI_EXPORT(int, expPROPSHEET_TREEBOOK)()
    {
        return wxPROPSHEET_TREEBOOK;
    }
    WXFFI_EXPORT(int, expPROPSHEET_SHRINKTOFIT)()
    {
        return wxPROPSHEET_SHRINKTOFIT;
    }
}
