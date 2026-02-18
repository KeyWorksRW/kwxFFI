// wx_fontpickerctrl.cpp - wxFontPickerCtrl wrappers
#include "kwx_wrapper.h"

// wxFontPickerCtrl inherits from wxControl (via wxPickerBase).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxFontPickerCtrl* wxFontPickerCtrl_Create(wxWindow* parent, int id, wxFont* initial,
                                                     int x, int y, int width, int height, long style)
    {
        return new wxFontPickerCtrl(parent, id, initial ? *initial : wxNullFont, wxPoint(x, y),
                                    wxSize(width, height), style);
    }

    EXPORT wxFont* wxFontPickerCtrl_GetSelectedFont(wxFontPickerCtrl* self)
    {
        wxFont* result = new wxFont();
        *result = self->GetSelectedFont();
        return result;
    }

    EXPORT void wxFontPickerCtrl_SetSelectedFont(wxFontPickerCtrl* self, wxFont* font)
    {
        if (font)
            self->SetSelectedFont(*font);
    }

    EXPORT int wxFontPickerCtrl_GetMaxPointSize(wxFontPickerCtrl* self)
    {
        return self->GetMaxPointSize();
    }

    EXPORT void wxFontPickerCtrl_SetMaxPointSize(wxFontPickerCtrl* self, int maxSize)
    {
        self->SetMaxPointSize(maxSize);
    }
}
