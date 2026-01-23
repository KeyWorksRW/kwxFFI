#include "wrapper.h"

extern "C"
{
    EXPORT void* wxGauge_Create(wxWindow* parent, int id, int range, int x, int y, int width,
                                int height, int style)
    {
        return new wxGauge(parent, id, range, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxGauge_SetShadowWidth(void* _obj, int w)
    {
        ((wxGauge*) _obj)->SetShadowWidth(w);
    }

    EXPORT void wxGauge_SetBezelFace(void* _obj, int w)
    {
        ((wxGauge*) _obj)->SetBezelFace(w);
    }

    EXPORT void wxGauge_SetRange(void* _obj, int r)
    {
        ((wxGauge*) _obj)->SetRange(r);
    }

    EXPORT void wxGauge_SetValue(void* _obj, int pos)
    {
        ((wxGauge*) _obj)->SetValue(pos);
    }

    EXPORT int wxGauge_GetShadowWidth(void* _obj)
    {
        return ((wxGauge*) _obj)->GetShadowWidth();
    }

    EXPORT int wxGauge_GetBezelFace(void* _obj)
    {
        return ((wxGauge*) _obj)->GetBezelFace();
    }

    EXPORT int wxGauge_GetRange(void* _obj)
    {
        return ((wxGauge*) _obj)->GetRange();
    }

    EXPORT int wxGauge_GetValue(void* _obj)
    {
        return ((wxGauge*) _obj)->GetValue();
    }
}
