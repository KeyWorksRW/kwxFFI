#pragma once

// Gesture events (wx/event.h:2026-2211) and the wxPoint2DDouble value type.
//
// wxWidgets delivers multi-touch input through six wxGestureEvent subclasses.
// wxWindow_EnableTouchEvents() (include/kwx_methods_window.h) turns the events
// on; these declarations expose what the handlers need to read.
//
// The event objects are created by wxWidgets and travel through the event
// dispatch chain, so there is no Create function: a foreign language wraps the
// pointer it receives in the handler.
//
// Position and delta are returned as a newly allocated wxPoint, matching
// wxMouseEvent_GetPosition(); the declaration is TClassOwned so the generated
// wrapper's Delete() frees it.

// ---------------------------------------------------------------------------
// wxGestureEvent
// ---------------------------------------------------------------------------

TClassDefExtend(wxGestureEvent, wxEvent) TClassOwned(wxPoint)
    wxGestureEvent_GetPosition(TSelf(wxGestureEvent) pObject);
void wxGestureEvent_SetPosition(TSelf(wxGestureEvent) pObject, TClass(wxPoint) pos);
TBool wxGestureEvent_IsGestureStart(TSelf(wxGestureEvent) pObject);
void wxGestureEvent_SetGestureStart(TSelf(wxGestureEvent) pObject, TBool is_start);
TBool wxGestureEvent_IsGestureEnd(TSelf(wxGestureEvent) pObject);
void wxGestureEvent_SetGestureEnd(TSelf(wxGestureEvent) pObject, TBool is_end);

// ---------------------------------------------------------------------------
// Gesture event subclasses
// ---------------------------------------------------------------------------

TClassDefExtend(wxPanGestureEvent, wxGestureEvent) TClassOwned(wxPoint)
    wxPanGestureEvent_GetDelta(TSelf(wxPanGestureEvent) pObject);
void wxPanGestureEvent_SetDelta(TSelf(wxPanGestureEvent) pObject, TClass(wxPoint) delta);

TClassDefExtend(wxZoomGestureEvent,
                wxGestureEvent) double wxZoomGestureEvent_GetZoomFactor(TSelf(wxZoomGestureEvent)
                                                                            pObject);
void wxZoomGestureEvent_SetZoomFactor(TSelf(wxZoomGestureEvent) pObject, double zoom_factor);

TClassDefExtend(wxRotateGestureEvent, wxGestureEvent) double wxRotateGestureEvent_GetRotationAngle(
    TSelf(wxRotateGestureEvent) pObject);
void wxRotateGestureEvent_SetRotationAngle(TSelf(wxRotateGestureEvent) pObject,
                                           double rotation_angle);

// These three add no members of their own; the inherited wxGestureEvent
// accessors are all a handler needs.
TClassDefExtend(wxTwoFingerTapEvent, wxGestureEvent)

    TClassDefExtend(wxLongPressEvent, wxGestureEvent)

        TClassDefExtend(wxPressAndTapEvent, wxGestureEvent)

    // ---------------------------------------------------------------------------
    // wxPoint2DDouble
    // ---------------------------------------------------------------------------
    //
    // A value type in wxWidgets (wx/geometry.h:280).  It crosses the ABI as an
    // opaque heap object, the same treatment wxPoint gets, and the arithmetic it
    // supports is exposed through the two mutators below plus the scalar pair
    // accessors.  The pan/zoom/rotate handlers of the wxWidgets event sample need
    // exactly this: accumulate a translation, hand it to wxAffineMatrix2D.

    TClassDef(wxPoint2DDouble) TClass(wxPoint2DDouble) wxPoint2DDouble_Create(double x, double y);
TClass(wxPoint2DDouble) wxPoint2DDouble_CreateFromPoint(TClass(wxPoint) pt);
void wxPoint2DDouble_Delete(TSelf(wxPoint2DDouble) pObject);
double wxPoint2DDouble_GetX(TSelf(wxPoint2DDouble) pObject);
double wxPoint2DDouble_GetY(TSelf(wxPoint2DDouble) pObject);
void wxPoint2DDouble_SetX(TSelf(wxPoint2DDouble) pObject, double x);
void wxPoint2DDouble_SetY(TSelf(wxPoint2DDouble) pObject, double y);
void wxPoint2DDouble_Add(TSelf(wxPoint2DDouble) pObject, double dx, double dy);
void wxPoint2DDouble_Subtract(TSelf(wxPoint2DDouble) pObject, double dx, double dy);
