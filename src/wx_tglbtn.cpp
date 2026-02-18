#include "kwx_wrapper.h"
#include <wx/tglbtn.h>

// wxToggleButton inherits from wxControl (via wxAnyButton).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT void* wxToggleButton_Create(wxWindow* parent, int id, wxString* label, int x, int y,
                                       int width, int height, int style)
    {
        return (void*) new wxToggleButton(parent, (wxWindowID) id, *label, wxPoint(x, y),
                                          wxSize(width, height), (long) style);
    }

    EXPORT void wxToggleButton_SetValue(wxToggleButton* self, bool state)
    {
        self->SetValue(state);
    }

    EXPORT bool wxToggleButton_GetValue(wxToggleButton* self)
    {
        return self->GetValue();
    }

    EXPORT void wxToggleButton_SetLabel(wxToggleButton* self, wxString* label)
    {
        self->SetLabel(*label);
    }

    EXPORT bool wxToggleButton_Enable(wxToggleButton* self, bool enable)
    {
        return self->Enable(enable);
    }

    EXPORT wxBitmapToggleButton* wxBitmapToggleButton_Create(wxWindow* parent, int id,
                                                             wxBitmap* bitmap, int x, int y,
                                                             int width, int height, int style)
    {
        return new wxBitmapToggleButton(parent, id, *bitmap, wxPoint(x, y), wxSize(width, height),
                                        style, wxDefaultValidator);
    }

    EXPORT void wxBitmapToggleButton_SetValue(wxBitmapToggleButton* self, bool state)
    {
        self->SetValue(state);
    }

    EXPORT bool wxBitmapToggleButton_GetValue(wxBitmapToggleButton* self)
    {
        return self->GetValue();
    }

    EXPORT bool wxBitmapToggleButton_Enable(wxBitmapToggleButton* self, bool enable)
    {
        return self->Enable(enable);
    }

    EXPORT void wxBitmapToggleButton_SetBitmapLabel(wxBitmapToggleButton* self, wxBitmap* bitmap)
    {
        self->SetBitmapLabel(*bitmap);
    }
}
