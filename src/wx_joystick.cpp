#include "kwx_wrapper.h"
#include <wx/joystick.h>

extern "C"
{
#if wxUSE_JOYSTICK

    EXPORT wxJoystick* wxJoystick_Create(int joystick)
    {
        return new wxJoystick(joystick);
    }

    EXPORT void wxJoystick_Delete(wxJoystick* self)
    {
        delete self;
    }

    EXPORT wxPoint* wxJoystick_GetPosition(wxJoystick* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT int wxJoystick_GetZPosition(wxJoystick* self)
    {
        return self->GetZPosition();
    }

    EXPORT int wxJoystick_GetButtonState(wxJoystick* self)
    {
        return self->GetButtonState();
    }

    EXPORT int wxJoystick_GetPOVPosition(wxJoystick* self)
    {
        return self->GetPOVPosition();
    }

    EXPORT int wxJoystick_GetPOVCTSPosition(wxJoystick* self)
    {
        return self->GetPOVCTSPosition();
    }

    EXPORT int wxJoystick_GetRudderPosition(wxJoystick* self)
    {
        return self->GetRudderPosition();
    }

    EXPORT int wxJoystick_GetUPosition(wxJoystick* self)
    {
        return self->GetUPosition();
    }

    EXPORT int wxJoystick_GetVPosition(wxJoystick* self)
    {
        return self->GetVPosition();
    }

    EXPORT int wxJoystick_GetMovementThreshold(wxJoystick* self)
    {
        return self->GetMovementThreshold();
    }

    EXPORT void wxJoystick_SetMovementThreshold(wxJoystick* self, int threshold)
    {
        self->SetMovementThreshold(threshold);
    }

    EXPORT bool wxJoystick_IsOk(wxJoystick* self)
    {
        return self->IsOk();
    }

    EXPORT int wxJoystick_GetNumberJoysticks(wxJoystick* self)
    {
        return self->GetNumberJoysticks();
    }

    EXPORT int wxJoystick_GetManufacturerId(wxJoystick* self)
    {
        return self->GetManufacturerId();
    }

    EXPORT int wxJoystick_GetProductId(wxJoystick* self)
    {
        return self->GetProductId();
    }

    EXPORT wxString* wxJoystick_GetProductName(wxJoystick* pObject)
    {
        wxString* result = new wxString();
        *result = pObject->GetProductName();
        return result;
    }

    EXPORT int wxJoystick_GetXMin(wxJoystick* self)
    {
        return self->GetXMin();
    }

    EXPORT int wxJoystick_GetYMin(wxJoystick* self)
    {
        return self->GetYMin();
    }

    EXPORT int wxJoystick_GetZMin(wxJoystick* self)
    {
        return self->GetZMin();
    }

    EXPORT int wxJoystick_GetXMax(wxJoystick* self)
    {
        return self->GetXMax();
    }

    EXPORT int wxJoystick_GetYMax(wxJoystick* self)
    {
        return self->GetYMax();
    }

    EXPORT int wxJoystick_GetZMax(wxJoystick* self)
    {
        return self->GetZMax();
    }

    EXPORT int wxJoystick_GetNumberButtons(wxJoystick* self)
    {
        return self->GetNumberButtons();
    }

    EXPORT int wxJoystick_GetNumberAxes(wxJoystick* self)
    {
        return self->GetNumberAxes();
    }

    EXPORT int wxJoystick_GetMaxButtons(wxJoystick* self)
    {
        return self->GetMaxButtons();
    }

    EXPORT int wxJoystick_GetMaxAxes(wxJoystick* self)
    {
        return self->GetMaxAxes();
    }

    EXPORT int wxJoystick_GetPollingMin(wxJoystick* self)
    {
        return self->GetPollingMin();
    }

    EXPORT int wxJoystick_GetPollingMax(wxJoystick* self)
    {
        return self->GetPollingMax();
    }

    EXPORT int wxJoystick_GetRudderMin(wxJoystick* self)
    {
        return self->GetRudderMin();
    }

    EXPORT int wxJoystick_GetRudderMax(wxJoystick* self)
    {
        return self->GetRudderMax();
    }

    EXPORT int wxJoystick_GetUMin(wxJoystick* self)
    {
        return self->GetUMin();
    }

    EXPORT int wxJoystick_GetUMax(wxJoystick* self)
    {
        return self->GetUMax();
    }

    EXPORT int wxJoystick_GetVMin(wxJoystick* self)
    {
        return self->GetVMin();
    }

    EXPORT int wxJoystick_GetVMax(wxJoystick* self)
    {
        return self->GetVMax();
    }

    EXPORT bool wxJoystick_HasRudder(wxJoystick* self)
    {
        return self->HasRudder();
    }

    EXPORT bool wxJoystick_HasZ(wxJoystick* self)
    {
        return self->HasZ();
    }

    EXPORT bool wxJoystick_HasU(wxJoystick* self)
    {
        return self->HasU();
    }

    EXPORT bool wxJoystick_HasV(wxJoystick* self)
    {
        return self->HasV();
    }

    EXPORT bool wxJoystick_HasPOV(wxJoystick* self)
    {
        return self->HasPOV();
    }

    EXPORT bool wxJoystick_HasPOV4Dir(wxJoystick* self)
    {
        return self->HasPOV4Dir();
    }

    EXPORT bool wxJoystick_HasPOVCTS(wxJoystick* self)
    {
        return self->HasPOVCTS();
    }

    EXPORT bool wxJoystick_SetCapture(wxJoystick* self, wxWindow* win, int pollingFreq)
    {
        return self->SetCapture(win, pollingFreq);
    }

    EXPORT bool wxJoystick_ReleaseCapture(wxJoystick* self)
    {
        return self->ReleaseCapture();
    }

#else

    EXPORT void* wxJoystick_Create(int joystick)
    {
        return nullptr;
    }

    EXPORT void wxJoystick_Delete(void* pObject) {}

    EXPORT void wxJoystick_GetPosition(void* pObject, void* x, void* y) {}

    EXPORT int wxJoystick_GetZPosition(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetButtonState(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetPOVPosition(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetPOVCTSPosition(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetRudderPosition(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetUPosition(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetVPosition(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetMovementThreshold(void* pObject)
    {
        return 0;
    }

    EXPORT void wxJoystick_SetMovementThreshold(void* pObject, int threshold) {}

    EXPORT bool wxJoystick_IsOk(wxJoystick* pObject)
    {
        return pObject->isOk();
    }

    EXPORT int wxJoystick_GetNumberJoysticks(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetManufacturerId(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetProductId(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetProductName(void* pObject, void* buffer)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetXMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetYMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetZMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetXMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetYMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetZMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetNumberButtons(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetNumberAxes(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetMaxButtons(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetMaxAxes(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetPollingMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetPollingMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetRudderMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetRudderMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetUMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetUMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetVMin(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_GetVMax(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasRudder(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasZ(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasU(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasV(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasPOV(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasPOV4Dir(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_HasPOVCTS(void* pObject)
    {
        return 0;
    }

    EXPORT int wxJoystick_SetCapture(void* pObject, void* win, int pollingFreq)
    {
        return 0;
    }

    EXPORT int wxJoystick_ReleaseCapture(void* pObject)
    {
        return 0;
    }

#endif
}
