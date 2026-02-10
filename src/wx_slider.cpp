#include "wrapper.h"
#include <wx/slider.h>

extern "C"
{
    EXPORT void* wxSlider_Create(wxWindow* parent, int id, int value, int min, int max, int x,
                                 int y, int width, int height, long style)
    {
        return new wxSlider(parent, id, value, min, max, wxPoint(x, y), wxSize(width, height),
                            style);
    }

    EXPORT int wxSlider_GetValue(void* pObject)
    {
        return ((wxSlider*) pObject)->GetValue();
    }

    EXPORT void wxSlider_SetValue(void* pObject, int value)
    {
        ((wxSlider*) pObject)->SetValue(value);
    }

    EXPORT void wxSlider_SetRange(void* pObject, int minValue, int maxValue)
    {
        ((wxSlider*) pObject)->SetRange(minValue, maxValue);
    }

    EXPORT int wxSlider_GetMin(void* pObject)
    {
        return ((wxSlider*) pObject)->GetMin();
    }

    EXPORT int wxSlider_GetMax(void* pObject)
    {
        return ((wxSlider*) pObject)->GetMax();
    }

    // Obsolete
    // EWXWEXPORT(void,wxSlider_SetTickFreq)(void* pObject, int n, int pos)

    EXPORT int wxSlider_GetTickFreq(void* pObject)
    {
        return ((wxSlider*) pObject)->GetTickFreq();
    }

    EXPORT void wxSlider_SetPageSize(void* pObject, int pageSize)
    {
        ((wxSlider*) pObject)->SetPageSize(pageSize);
    }

    EXPORT int wxSlider_GetPageSize(void* pObject)
    {
        return ((wxSlider*) pObject)->GetPageSize();
    }

    EXPORT void wxSlider_ClearSel(void* pObject)
    {
        ((wxSlider*) pObject)->ClearSel();
    }

    EXPORT void wxSlider_ClearTicks(void* pObject)
    {
        ((wxSlider*) pObject)->ClearTicks();
    }

    EXPORT void wxSlider_SetLineSize(void* pObject, int lineSize)
    {
        ((wxSlider*) pObject)->SetLineSize(lineSize);
    }

    EXPORT int wxSlider_GetLineSize(void* pObject)
    {
        return ((wxSlider*) pObject)->GetLineSize();
    }

    EXPORT int wxSlider_GetSelEnd(void* pObject)
    {
        return ((wxSlider*) pObject)->GetSelEnd();
    }

    EXPORT int wxSlider_GetSelStart(void* pObject)
    {
        return ((wxSlider*) pObject)->GetSelStart();
    }

    EXPORT void wxSlider_SetSelection(void* pObject, int minPos, int maxPos)
    {
        ((wxSlider*) pObject)->SetSelection(minPos, maxPos);
    }

    EXPORT void wxSlider_SetThumbLength(void* pObject, int len)
    {
        ((wxSlider*) pObject)->SetThumbLength(len);
    }

    EXPORT int wxSlider_GetThumbLength(void* pObject)
    {
        return ((wxSlider*) pObject)->GetThumbLength();
    }

    EXPORT void wxSlider_SetTick(void* pObject, int tickPos)
    {
        ((wxSlider*) pObject)->SetTick(tickPos);
    }
}
