// wx_timepickerctrl.cpp - wxTimePickerCtrl wrappers
#include "wrapper.h"

extern "C"
{
    EXPORT wxTimePickerCtrl* wxTimePickerCtrl_Create(wxWindow* parent, int id, int x, int y,
                                                     int width, int height, long style)
    {
        return new wxTimePickerCtrl(parent, id, wxDefaultDateTime, wxPoint(x, y),
                                    wxSize(width, height), style);
    }

    EXPORT void wxTimePickerCtrl_SetValue(wxTimePickerCtrl* self, wxDateTime* dateTime)
    {
        if (dateTime)
            self->SetValue(*dateTime);
    }

    EXPORT void wxTimePickerCtrl_GetValue(wxTimePickerCtrl* self, wxDateTime* dateTime)
    {
        if (dateTime)
            *dateTime = self->GetValue();
    }

    EXPORT void wxTimePickerCtrl_SetTime(wxTimePickerCtrl* self, int hour, int min, int sec)
    {
        self->SetTime(hour, min, sec);
    }

    EXPORT bool wxTimePickerCtrl_GetTime(wxTimePickerCtrl* self, int* hour, int* min, int* sec)
    {
        return self->GetTime(hour, min, sec);
    }
}
