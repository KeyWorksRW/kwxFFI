#include "wrapper.h"

extern "C"
{
    EXPORT void* wxScrolledWindow_Create(wxWindow* parent, int id, int x, int y, int width,
                                         int height, int style)
    {
        return new wxScrolledWindow(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxScrolledWindow_SetTargetWindow(void* self, wxWindow* target)
    {
        ((wxScrolledWindow*) self)->SetTargetWindow(target);
    }

    EXPORT void* wxScrolledWindow_GetTargetWindow(void* self)
    {
        return (void*) ((wxScrolledWindow*) self)->GetTargetWindow();
    }

    EXPORT void wxScrolledWindow_ShowScrollbars(void* self, int showh, int showv)
    {
        ((wxScrolledWindow*) self)
            ->ShowScrollbars((wxScrollbarVisibility) showh, (wxScrollbarVisibility) showv);
    }

    EXPORT void wxScrolledWindow_SetScrollbars(void* self, int pixelsPerUnitX, int pixelsPerUnitY,
                                               int noUnitsX, int noUnitsY, int xPos, int yPos,
                                               bool noRefresh)
    {
        ((wxScrolledWindow*) self)
            ->SetScrollbars(pixelsPerUnitX, pixelsPerUnitY, noUnitsX, noUnitsY, xPos, yPos,
                            noRefresh);
    }

    EXPORT void wxScrolledWindow_Scroll(void* self, int x_pos, int y_pos)
    {
        ((wxScrolledWindow*) self)->Scroll(x_pos, y_pos);
    }

    EXPORT int wxScrolledWindow_GetScrollPageSize(void* self, int orient)
    {
        return ((wxScrolledWindow*) self)->GetScrollPageSize(orient);
    }

    EXPORT void wxScrolledWindow_SetScrollPageSize(void* self, int orient, int pageSize)
    {
        ((wxScrolledWindow*) self)->SetScrollPageSize(orient, pageSize);
    }

    EXPORT void wxScrolledWindow_GetScrollPixelsPerUnit(void* self, int* x_unit, int* y_unit)
    {
        ((wxScrolledWindow*) self)->GetScrollPixelsPerUnit(x_unit, y_unit);
    }

    EXPORT void wxScrolledWindow_EnableScrolling(void* self, bool x_scrolling, bool y_scrolling)
    {
        ((wxScrolledWindow*) self)->EnableScrolling(x_scrolling, y_scrolling);
    }

    EXPORT void wxScrolledWindow_GetViewStart(void* pObject, void* x, void* y)
    {
        ((wxScrolledWindow*) pObject)->GetViewStart((int*) x, (int*) y);
    }

    EXPORT void wxScrolledWindow_ViewStart(void* pObject, void* x, void* y)
    {
        ((wxScrolledWindow*) pObject)->GetViewStart((int*) x, (int*) y);
    }

    EXPORT void wxScrolledWindow_GetVirtualSize(void* pObject, void* x, void* y)
    {
        ((wxScrolledWindow*) pObject)->GetVirtualSize((int*) x, (int*) y);
    }

    EXPORT void wxScrolledWindow_SetScale(void* self, double xs, double ys)
    {
        ((wxScrolledWindow*) self)->SetScale(xs, ys);
    }

    EXPORT double wxScrolledWindow_GetScaleX(void* self)
    {
        return ((wxScrolledWindow*) self)->GetScaleX();
    }

    EXPORT double wxScrolledWindow_GetScaleY(void* self)
    {
        return ((wxScrolledWindow*) self)->GetScaleY();
    }

    EXPORT void wxScrolledWindow_CalcScrolledPosition(void* self, int x, int y, int* xx, int* yy)
    {
        ((wxScrolledWindow*) self)->CalcScrolledPosition(x, y, xx, yy);
    }

    EXPORT void wxScrolledWindow_CalcUnscrolledPosition(void* self, int x, int y, int* xx, int* yy)
    {
        ((wxScrolledWindow*) self)->CalcUnscrolledPosition(x, y, xx, yy);
    }

    EXPORT void wxScrolledWindow_AdjustScrollbars(void* self)
    {
        ((wxScrolledWindow*) self)->AdjustScrollbars();
    }

    EXPORT void wxScrolledWindow_OnDraw(void* self, wxDC* dc)
    {
        ((wxScrolledWindow*) self)->OnDraw(*dc);
    }

    EXPORT void wxScrolledWindow_PrepareDC(void* self, wxDC* dc)
    {
        ((wxScrolledWindow*) self)->PrepareDC(*dc);
    }
}
