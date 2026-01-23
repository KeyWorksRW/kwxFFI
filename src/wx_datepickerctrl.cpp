// wx_datepickerctrl.cpp - wxDatePickerCtrl wrappers
#include "wrapper.h"

extern "C"
{
    EXPORT wxDatePickerCtrl* wxDatePickerCtrl_Create(wxWindow* parent, int id, int x, int y, int w,
                                                     int h, long style)
    {
        return new wxDatePickerCtrl(parent, id, wxDefaultDateTime, wxPoint(x, y), wxSize(w, h),
                                    style);
    }

    EXPORT void wxDatePickerCtrl_SetValue(wxDatePickerCtrl* self, wxDateTime* dt)
    {
        if (dt)
            self->SetValue(*dt);
    }

    EXPORT void wxDatePickerCtrl_GetValue(wxDatePickerCtrl* self, wxDateTime* dt)
    {
        if (dt)
            *dt = self->GetValue();
    }

    EXPORT void wxDatePickerCtrl_SetRange(wxDatePickerCtrl* self, wxDateTime* dt1, wxDateTime* dt2)
    {
        self->SetRange(dt1 ? *dt1 : wxDefaultDateTime, dt2 ? *dt2 : wxDefaultDateTime);
    }

    EXPORT bool wxDatePickerCtrl_GetRange(wxDatePickerCtrl* self, wxDateTime* dt1, wxDateTime* dt2)
    {
        return self->GetRange(dt1, dt2);
    }
}
