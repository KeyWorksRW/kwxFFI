#include "wrapper.h"

// wxSpinCtrl inherits from wxControl (via wxSpinButton on MSW).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT void* wxSpinCtrl_Create(wxWindow* parent, int id, wxString* value, int x, int y,
                                   int width, int height, long style, int min, int max, int initial)
    {
        return new wxSpinCtrl(parent, id, *value, wxPoint(x, y), wxSize(width, height), style, min,
                              max, initial);
    }

    EXPORT void wxSpinCtrl_SetValue(void* pObject, int val)
    {
        ((wxSpinCtrl*) pObject)->SetValue(val);
    }

    EXPORT int wxSpinCtrl_GetValue(void* pObject)
    {
        return ((wxSpinCtrl*) pObject)->GetValue();
    }

    EXPORT void wxSpinCtrl_SetRange(void* pObject, int min_val, int max_val)
    {
        ((wxSpinCtrl*) pObject)->SetRange(min_val, max_val);
    }

    EXPORT int wxSpinCtrl_GetMin(void* pObject)
    {
        return ((wxSpinCtrl*) pObject)->GetMin();
    }

    EXPORT int wxSpinCtrl_GetMax(void* pObject)
    {
        return ((wxSpinCtrl*) pObject)->GetMax();
    }

    EXPORT void* wxSpinButton_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                     long style)
    {
        return new wxSpinButton(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxSpinButton_GetValue(void* pObject)
    {
        return ((wxSpinButton*) pObject)->GetValue();
    }

    EXPORT int wxSpinButton_GetMin(void* pObject)
    {
        return ((wxSpinButton*) pObject)->GetMin();
    }

    EXPORT int wxSpinButton_GetMax(void* pObject)
    {
        return ((wxSpinButton*) pObject)->GetMax();
    }

    EXPORT void wxSpinButton_SetValue(void* pObject, int val)
    {
        ((wxSpinButton*) pObject)->SetValue(val);
    }

    EXPORT void wxSpinButton_SetRange(void* pObject, int minVal, int maxVal)
    {
        ((wxSpinButton*) pObject)->SetRange(minVal, maxVal);
    }

    EXPORT int wxSpinCtrl_GetBase(wxSpinCtrl* self)
    {
        return self->GetBase();
    }

    EXPORT bool wxSpinCtrl_SetBase(wxSpinCtrl* self, int base)
    {
        return self->SetBase(base);
    }
}
