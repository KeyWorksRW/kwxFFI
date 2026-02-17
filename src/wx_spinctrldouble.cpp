#include "wrapper.h"

// wxSpinCtrlDouble inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxSpinCtrlDouble* wxSpinCtrlDouble_Create(wxWindow* parent, int id, wxString* value,
                                                     int x, int y, int width, int height, int style,
                                                     double min, double max, double initial,
                                                     double inc)
    {
        return new wxSpinCtrlDouble(parent, id, *value, wxPoint(x, y), wxSize(width, height), style, min,
                                    max, initial, inc);
    }

    EXPORT double wxSpinCtrlDouble_GetValue(wxSpinCtrlDouble* self)
    {
        return self->GetValue();
    }

    EXPORT void wxSpinCtrlDouble_SetValue(wxSpinCtrlDouble* self, double value)
    {
        self->SetValue(value);
    }

    EXPORT void wxSpinCtrlDouble_SetValueString(wxSpinCtrlDouble* self, wxString* value)
    {
        self->SetValue(*value);
    }

    EXPORT void wxSpinCtrlDouble_SetRange(wxSpinCtrlDouble* self, double minVal, double maxVal)
    {
        self->SetRange(minVal, maxVal);
    }

    EXPORT double wxSpinCtrlDouble_GetMin(wxSpinCtrlDouble* self)
    {
        return self->GetMin();
    }

    EXPORT double wxSpinCtrlDouble_GetMax(wxSpinCtrlDouble* self)
    {
        return self->GetMax();
    }

    EXPORT void wxSpinCtrlDouble_SetIncrement(wxSpinCtrlDouble* self, double inc)
    {
        self->SetIncrement(inc);
    }

    EXPORT double wxSpinCtrlDouble_GetIncrement(wxSpinCtrlDouble* self)
    {
        return self->GetIncrement();
    }

    EXPORT void wxSpinCtrlDouble_SetDigits(wxSpinCtrlDouble* self, unsigned int digits)
    {
        self->SetDigits(digits);
    }

    EXPORT unsigned int wxSpinCtrlDouble_GetDigits(wxSpinCtrlDouble* self)
    {
        return self->GetDigits();
    }
}
