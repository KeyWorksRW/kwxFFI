// wx_timepickerctrl.cpp - wxTimePickerCtrl wrappers
#include "wrapper.h"

extern "C"
{
    EXPORT wxTimePickerCtrl* wxTimePickerCtrl_Create(wxWindow* parent, int id, int x, int y, int w,
                                                     int h, long style)
    {
        return new wxTimePickerCtrl(parent, id, wxDefaultDateTime, wxPoint(x, y), wxSize(w, h),
                                    style);
    }

    EXPORT void wxTimePickerCtrl_SetValue(wxTimePickerCtrl* self, wxDateTime* dt)
    {
        if (dt)
            self->SetValue(*dt);
    }

    EXPORT void wxTimePickerCtrl_GetValue(wxTimePickerCtrl* self, wxDateTime* dt)
    {
        if (dt)
            *dt = self->GetValue();
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
