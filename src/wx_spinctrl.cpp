#include "wrapper.h"

extern "C"
{
    EXPORT void* wxSpinCtrl_Create(wxWindow* parent, int id, wxString* value, int x, int y,
                                   int width, int height, long style, int min, int max, int initial)
    {
        return new wxSpinCtrl(parent, id, *value, wxPoint(x, y), wxSize(width, height), style, min,
                              max, initial);
    }

    EXPORT void wxSpinCtrl_SetValue(void* _obj, int val)
    {
        ((wxSpinCtrl*) _obj)->SetValue(val);
    }

    EXPORT int wxSpinCtrl_GetValue(void* _obj)
    {
        return ((wxSpinCtrl*) _obj)->GetValue();
    }

    EXPORT void wxSpinCtrl_SetRange(void* _obj, int min_val, int max_val)
    {
        ((wxSpinCtrl*) _obj)->SetRange(min_val, max_val);
    }

    EXPORT int wxSpinCtrl_GetMin(void* _obj)
    {
        return ((wxSpinCtrl*) _obj)->GetMin();
    }

    EXPORT int wxSpinCtrl_GetMax(void* _obj)
    {
        return ((wxSpinCtrl*) _obj)->GetMax();
    }

    EXPORT void* wxSpinButton_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                     long style)
    {
        return new wxSpinButton(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxSpinButton_GetValue(void* _obj)
    {
        return ((wxSpinButton*) _obj)->GetValue();
    }

    EXPORT int wxSpinButton_GetMin(void* _obj)
    {
        return ((wxSpinButton*) _obj)->GetMin();
    }

    EXPORT int wxSpinButton_GetMax(void* _obj)
    {
        return ((wxSpinButton*) _obj)->GetMax();
    }

    EXPORT void wxSpinButton_SetValue(void* _obj, int val)
    {
        ((wxSpinButton*) _obj)->SetValue(val);
    }

    EXPORT void wxSpinButton_SetRange(void* _obj, int minVal, int maxVal)
    {
        ((wxSpinButton*) _obj)->SetRange(minVal, maxVal);
    }
}
