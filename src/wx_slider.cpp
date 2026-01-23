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

    EXPORT int wxSlider_GetValue(void* _obj)
    {
        return ((wxSlider*) _obj)->GetValue();
    }

    EXPORT void wxSlider_SetValue(void* _obj, int value)
    {
        ((wxSlider*) _obj)->SetValue(value);
    }

    EXPORT void wxSlider_SetRange(void* _obj, int minValue, int maxValue)
    {
        ((wxSlider*) _obj)->SetRange(minValue, maxValue);
    }

    EXPORT int wxSlider_GetMin(void* _obj)
    {
        return ((wxSlider*) _obj)->GetMin();
    }

    EXPORT int wxSlider_GetMax(void* _obj)
    {
        return ((wxSlider*) _obj)->GetMax();
    }

    // Obsolete
    // EWXWEXPORT(void,wxSlider_SetTickFreq)(void* _obj, int n, int pos)

    EXPORT int wxSlider_GetTickFreq(void* _obj)
    {
        return ((wxSlider*) _obj)->GetTickFreq();
    }

    EXPORT void wxSlider_SetPageSize(void* _obj, int pageSize)
    {
        ((wxSlider*) _obj)->SetPageSize(pageSize);
    }

    EXPORT int wxSlider_GetPageSize(void* _obj)
    {
        return ((wxSlider*) _obj)->GetPageSize();
    }

    EXPORT void wxSlider_ClearSel(void* _obj)
    {
        ((wxSlider*) _obj)->ClearSel();
    }

    EXPORT void wxSlider_ClearTicks(void* _obj)
    {
        ((wxSlider*) _obj)->ClearTicks();
    }

    EXPORT void wxSlider_SetLineSize(void* _obj, int lineSize)
    {
        ((wxSlider*) _obj)->SetLineSize(lineSize);
    }

    EXPORT int wxSlider_GetLineSize(void* _obj)
    {
        return ((wxSlider*) _obj)->GetLineSize();
    }

    EXPORT int wxSlider_GetSelEnd(void* _obj)
    {
        return ((wxSlider*) _obj)->GetSelEnd();
    }

    EXPORT int wxSlider_GetSelStart(void* _obj)
    {
        return ((wxSlider*) _obj)->GetSelStart();
    }

    EXPORT void wxSlider_SetSelection(void* _obj, int minPos, int maxPos)
    {
        ((wxSlider*) _obj)->SetSelection(minPos, maxPos);
    }

    EXPORT void wxSlider_SetThumbLength(void* _obj, int len)
    {
        ((wxSlider*) _obj)->SetThumbLength(len);
    }

    EXPORT int wxSlider_GetThumbLength(void* _obj)
    {
        return ((wxSlider*) _obj)->GetThumbLength();
    }

    EXPORT void wxSlider_SetTick(void* _obj, int tickPos)
    {
        ((wxSlider*) _obj)->SetTick(tickPos);
    }
}
