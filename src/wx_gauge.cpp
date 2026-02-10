#include "wrapper.h"

extern "C"
{
    EXPORT void* wxGauge_Create(wxWindow* parent, int id, int range, int x, int y, int width,
                                int height, int style)
    {
        return new wxGauge(parent, id, range, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxGauge_SetRange(void* pObject, int range)
    {
        ((wxGauge*) pObject)->SetRange(range);
    }

    EXPORT void wxGauge_SetValue(void* pObject, int pos)
    {
        ((wxGauge*) pObject)->SetValue(pos);
    }

    EXPORT int wxGauge_GetRange(void* pObject)
    {
        return ((wxGauge*) pObject)->GetRange();
    }

    EXPORT int wxGauge_GetValue(void* pObject)
    {
        return ((wxGauge*) pObject)->GetValue();
    }
}
