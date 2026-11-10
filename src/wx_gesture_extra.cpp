// Gesture events and wxPoint2DDouble.
//
// The event wrappers only read and write the objects wxWidgets creates, so
// there is no Create/Delete pair for the event classes: a handler wraps the
// pointer it receives.  wxPoint2DDouble is a heap object owned by the caller.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

extern "C"
{
    // ---- wxGestureEvent ------------------------------------------------------

    EXPORT wxPoint* wxGestureEvent_GetPosition(wxGestureEvent* self)
    {
        return new wxPoint(self->GetPosition());
    }

    EXPORT void wxGestureEvent_SetPosition(wxGestureEvent* self, wxPoint* pos)
    {
        if (pos)
        {
            self->SetPosition(*pos);
        }
    }

    EXPORT int wxGestureEvent_IsGestureStart(wxGestureEvent* self)
    {
        return self->IsGestureStart();
    }

    EXPORT void wxGestureEvent_SetGestureStart(wxGestureEvent* self, bool is_start)
    {
        self->SetGestureStart(is_start);
    }

    EXPORT int wxGestureEvent_IsGestureEnd(wxGestureEvent* self)
    {
        return self->IsGestureEnd();
    }

    EXPORT void wxGestureEvent_SetGestureEnd(wxGestureEvent* self, bool is_end)
    {
        self->SetGestureEnd(is_end);
    }

    // ---- wxPanGestureEvent ---------------------------------------------------

    EXPORT wxPoint* wxPanGestureEvent_GetDelta(wxPanGestureEvent* self)
    {
        return new wxPoint(self->GetDelta());
    }

    EXPORT void wxPanGestureEvent_SetDelta(wxPanGestureEvent* self, wxPoint* delta)
    {
        if (delta)
        {
            self->SetDelta(*delta);
        }
    }

    // ---- wxZoomGestureEvent --------------------------------------------------

    EXPORT double wxZoomGestureEvent_GetZoomFactor(wxZoomGestureEvent* self)
    {
        return self->GetZoomFactor();
    }

    EXPORT void wxZoomGestureEvent_SetZoomFactor(wxZoomGestureEvent* self, double zoom_factor)
    {
        self->SetZoomFactor(zoom_factor);
    }

    // ---- wxRotateGestureEvent ------------------------------------------------

    EXPORT double wxRotateGestureEvent_GetRotationAngle(wxRotateGestureEvent* self)
    {
        return self->GetRotationAngle();
    }

    EXPORT void wxRotateGestureEvent_SetRotationAngle(wxRotateGestureEvent* self,
                                                      double rotation_angle)
    {
        self->SetRotationAngle(rotation_angle);
    }

    // ---- wxPoint2DDouble -----------------------------------------------------

    EXPORT wxPoint2DDouble* wxPoint2DDouble_Create(double x, double y)
    {
        return new wxPoint2DDouble(x, y);
    }

    EXPORT wxPoint2DDouble* wxPoint2DDouble_CreateFromPoint(wxPoint* pt)
    {
        if (!pt)
        {
            return new wxPoint2DDouble();
        }
        return new wxPoint2DDouble(*pt);
    }

    EXPORT void wxPoint2DDouble_Delete(wxPoint2DDouble* self)
    {
        delete self;
    }

    EXPORT double wxPoint2DDouble_GetX(wxPoint2DDouble* self)
    {
        return self->m_x;
    }

    EXPORT double wxPoint2DDouble_GetY(wxPoint2DDouble* self)
    {
        return self->m_y;
    }

    EXPORT void wxPoint2DDouble_SetX(wxPoint2DDouble* self, double x)
    {
        self->m_x = x;
    }

    EXPORT void wxPoint2DDouble_SetY(wxPoint2DDouble* self, double y)
    {
        self->m_y = y;
    }

    EXPORT void wxPoint2DDouble_Add(wxPoint2DDouble* self, double dx, double dy)
    {
        *self += wxPoint2DDouble(dx, dy);
    }

    EXPORT void wxPoint2DDouble_Subtract(wxPoint2DDouble* self, double dx, double dy)
    {
        *self -= wxPoint2DDouble(dx, dy);
    }
}
