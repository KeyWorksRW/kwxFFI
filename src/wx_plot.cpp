#include "kwx_wrapper.h"
#include <wx/plot/plot.h>

extern "C"
{
    typedef int (*TGetPlotInt)(void* pObject);
    typedef double (*TGetPlotDouble)(void* pObject, int x);
}

class kwxPlotCurve : public wxPlotCurve
{
private:
    void* kwxObject;
    TGetPlotInt EGetStartX;
    TGetPlotInt EGetEndX;
    TGetPlotDouble EGetY;

public:
    kwxPlotCurve(void* pObject, void* fnGetStartX, void* endVal, void* y, int offsetY, double startY,
                 double endY) : wxPlotCurve(offsetY, startY, endY)
    {
        kwxObject = pObject;
        EGetStartX = (TGetPlotInt) fnGetStartX;
        EGetEndX = (TGetPlotInt) endVal;
        EGetY = (TGetPlotDouble) y;
    }
    virtual wxInt32 GetStartX() { return (wxInt32) EGetStartX(kwxObject); }

    virtual wxInt32 GetEndX() { return (wxInt32) EGetEndX(kwxObject); }

    virtual double GetY(wxInt32 x) { return EGetY(kwxObject, (int) x); }
};

extern "C"
{
    EXPORT void* wxPlotWindow_Create(void* parent, int id, int x, int y, int width, int height, int flags)
    {
        return (void*) new wxPlotWindow((wxWindow*) parent, (wxWindowID) id, wxPoint(x, y),
                                        wxSize(width, height), flags);
    }

    EXPORT void wxPlotWindow_Add(void* pObject, void* curve)
    {
        ((wxPlotWindow*) pObject)->Add((wxPlotCurve*) curve);
    }

    EXPORT void wxPlotWindow_Delete(void* pObject, void* curve)
    {
        ((wxPlotWindow*) pObject)->Delete((wxPlotCurve*) curve);
    }

    EXPORT int wxPlotWindow_GetCount(void* pObject)
    {
        return (int) ((wxPlotWindow*) pObject)->GetCount();
    }

    EXPORT void* wxPlotWindow_GetAt(void* pObject, int index)
    {
        return (void*) ((wxPlotWindow*) pObject)->GetAt((size_t) index);
    }

    EXPORT void wxPlotWindow_SetCurrentCurve(void* pObject, void* current)
    {
        ((wxPlotWindow*) pObject)->SetCurrentCurve((wxPlotCurve*) current);
    }

    EXPORT void* wxPlotWindow_GetCurrentCurve(void* pObject)
    {
        return (void*) ((wxPlotWindow*) pObject)->GetCurrentCurve();
    }

    EXPORT void wxPlotWindow_AddOnOff(void* pObject, void* curve)
    {
        ((wxPlotWindow*) pObject)->Add((wxPlotOnOffCurve*) curve);
    }

    EXPORT void wxPlotWindow_DeleteOnOff(void* pObject, void* curve)
    {
        ((wxPlotWindow*) pObject)->Delete((wxPlotOnOffCurve*) curve);
    }

    EXPORT int wxPlotWindow_GetOnOffCurveCount(void* pObject)
    {
        return (int) ((wxPlotWindow*) pObject)->GetOnOffCurveCount();
    }

    EXPORT void* wxPlotWindow_GetOnOffCurveAt(void* pObject, int index)
    {
        return (void*) ((wxPlotWindow*) pObject)->GetOnOffCurveAt((size_t) index);
    }

    EXPORT void wxPlotWindow_Move(void* pObject, void* curve, int pixels_up)
    {
        ((wxPlotWindow*) pObject)->Move((wxPlotCurve*) curve, pixels_up);
    }

    EXPORT void wxPlotWindow_Enlarge(void* pObject, void* curve, double factor)
    {
        ((wxPlotWindow*) pObject)->Enlarge((wxPlotCurve*) curve, factor);
    }

    EXPORT void wxPlotWindow_SetUnitsPerValue(void* pObject, double upv)
    {
        ((wxPlotWindow*) pObject)->SetUnitsPerValue(upv);
    }

    EXPORT double wxPlotWindow_GetUnitsPerValue(void* pObject)
    {
        return ((wxPlotWindow*) pObject)->GetUnitsPerValue();
    }

    EXPORT void wxPlotWindow_SetZoom(void* pObject, double zoom)
    {
        ((wxPlotWindow*) pObject)->SetZoom(zoom);
    }

    EXPORT double wxPlotWindow_GetZoom(void* pObject)
    {
        return ((wxPlotWindow*) pObject)->GetZoom();
    }

    EXPORT void wxPlotWindow_SetScrollOnThumbRelease(void* pObject, int scrollOnThumbRelease)
    {
        ((wxPlotWindow*) pObject)->SetScrollOnThumbRelease(scrollOnThumbRelease != 0);
    }

    EXPORT int wxPlotWindow_GetScrollOnThumbRelease(void* pObject)
    {
        return (int) ((wxPlotWindow*) pObject)->GetScrollOnThumbRelease();
    }

    EXPORT void wxPlotWindow_SetEnlargeAroundWindowCentre(void* pObject, int enlargeAroundWindowCentre)
    {
        ((wxPlotWindow*) pObject)->SetEnlargeAroundWindowCentre(enlargeAroundWindowCentre != 0);
    }

    EXPORT int wxPlotWindow_GetEnlargeAroundWindowCentre(void* pObject)
    {
        return (int) ((wxPlotWindow*) pObject)->GetEnlargeAroundWindowCentre();
    }

    EXPORT void wxPlotWindow_RedrawEverything(void* pObject)
    {
        ((wxPlotWindow*) pObject)->RedrawEverything();
    }

    EXPORT void wxPlotWindow_RedrawXAxis(void* pObject)
    {
        ((wxPlotWindow*) pObject)->RedrawXAxis();
    }

    EXPORT void wxPlotWindow_RedrawYAxis(void* pObject)
    {
        ((wxPlotWindow*) pObject)->RedrawYAxis();
    }

    EXPORT void wxPlotWindow_ResetScrollbar(void* pObject)
    {
        ((wxPlotWindow*) pObject)->ResetScrollbar();
    }

    EXPORT void* wxPlotOnOffCurve_Create(int offsetY)
    {
        return (void*) new wxPlotOnOffCurve(offsetY);
    }

    EXPORT void wxPlotOnOffCurve_Delete(void* pObject)
    {
        delete (wxPlotOnOffCurve*) pObject;
    }

    EXPORT int wxPlotOnOffCurve_GetStartX(void* pObject)
    {
        return (int) ((wxPlotOnOffCurve*) pObject)->GetStartX();
    }

    EXPORT int wxPlotOnOffCurve_GetEndX(void* pObject)
    {
        return (int) ((wxPlotOnOffCurve*) pObject)->GetEndX();
    }

    EXPORT void wxPlotOnOffCurve_SetOffsetY(void* pObject, int offsetY)
    {
        ((wxPlotOnOffCurve*) pObject)->SetOffsetY(offsetY);
    }

    EXPORT int wxPlotOnOffCurve_GetOffsetY(void* pObject)
    {
        return ((wxPlotOnOffCurve*) pObject)->GetOffsetY();
    }

    EXPORT void wxPlotOnOffCurve_Add(void* pObject, int onPos, int offPos, void* clientData)
    {
        ((wxPlotOnOffCurve*) pObject)->Add((wxInt32) onPos, (wxInt32) offPos, clientData);
    }

    EXPORT int wxPlotOnOffCurve_GetCount(void* pObject)
    {
        return (int) ((wxPlotOnOffCurve*) pObject)->GetCount();
    }

    EXPORT int wxPlotOnOffCurve_GetOn(void* pObject, int index)
    {
        return (int) ((wxPlotOnOffCurve*) pObject)->GetOn((size_t) index);
    }

    EXPORT int wxPlotOnOffCurve_GetOff(void* pObject, int index)
    {
        return (int) ((wxPlotOnOffCurve*) pObject)->GetOff((size_t) index);
    }

    EXPORT void* wxPlotOnOffCurve_GetClientData(void* pObject, int index)
    {
        return (void*) ((wxPlotOnOffCurve*) pObject)->GetClientData((size_t) index);
    }

    EXPORT void* wxPlotOnOffCurve_GetAt(void* pObject, int index)
    {
        return (void*) ((wxPlotOnOffCurve*) pObject)->GetAt((size_t) index);
    }

    EXPORT void wxPlotOnOffCurve_DrawOnLine(void* pObject, void* dc, int y, int start, int end,
                                            void* clientData)
    {
        ((wxPlotOnOffCurve*) pObject)
            ->DrawOnLine(*((wxDC*) dc), (wxCoord) y, (wxCoord) start, (wxCoord) end, clientData);
    }

    EXPORT void wxPlotOnOffCurve_DrawOffLine(void* pObject, void* dc, int y, int start, int end)
    {
        ((wxPlotOnOffCurve*) pObject)
            ->DrawOffLine(*((wxDC*) dc), (wxCoord) y, (wxCoord) start, (wxCoord) end);
    }

    EXPORT void* kwxPlotCurve_Create(void* pObject, void* fnGetStartX, void* endVal, void* y, int offsetY,
                                     double startY, double endY)
    {
        return (void*) new kwxPlotCurve(pObject, fnGetStartX, endVal, y, offsetY, startY, endY);
    }

    EXPORT void kwxPlotCurve_Delete(void* pObject)
    {
        delete (kwxPlotCurve*) pObject;
    }

    EXPORT void kwxPlotCurve_SetStartY(void* pObject, double startY)
    {
        ((kwxPlotCurve*) pObject)->SetStartY(startY);
    }

    EXPORT double kwxPlotCurve_GetStartY(void* pObject)
    {
        return ((kwxPlotCurve*) pObject)->GetStartY();
    }

    EXPORT void kwxPlotCurve_SetEndY(void* pObject, double endY)
    {
        ((kwxPlotCurve*) pObject)->SetEndY(endY);
    }

    EXPORT double kwxPlotCurve_GetEndY(void* pObject)
    {
        return ((kwxPlotCurve*) pObject)->GetEndY();
    }

    EXPORT void kwxPlotCurve_SetOffsetY(void* pObject, int offsetY)
    {
        ((kwxPlotCurve*) pObject)->SetOffsetY(offsetY);
    }

    EXPORT int kwxPlotCurve_GetOffsetY(void* pObject)
    {
        return ((kwxPlotCurve*) pObject)->GetOffsetY();
    }

    EXPORT void kwxPlotCurve_SetPenNormal(void* pObject, void* pen)
    {
        ((kwxPlotCurve*) pObject)->SetPenNormal(*((wxPen*) pen));
    }

    EXPORT void kwxPlotCurve_SetPenSelected(void* pObject, void* pen)
    {
        ((kwxPlotCurve*) pObject)->SetPenSelected(*((wxPen*) pen));
    }

    EXPORT void* wxPlotEvent_GetCurve(void* pObject)
    {
        return (void*) ((wxPlotEvent*) pObject)->GetCurve();
    }

    EXPORT double wxPlotEvent_GetZoom(void* pObject)
    {
        return ((wxPlotEvent*) pObject)->GetZoom();
    }

    EXPORT void wxPlotEvent_SetZoom(void* pObject, double zoom)
    {
        ((wxPlotEvent*) pObject)->SetZoom(zoom);
    }

    EXPORT int wxPlotEvent_GetPosition(void* pObject)
    {
        return (int) ((wxPlotEvent*) pObject)->GetPosition();
    }

    EXPORT void wxPlotEvent_SetPosition(void* pObject, int pos)
    {
        ((wxPlotEvent*) pObject)->SetPosition((wxInt32) pos);
    }
}
