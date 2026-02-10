#include "wrapper.h"

extern "C"
{
    EXPORT wxColourData* wxColourData_Create()
    {
        return new wxColourData();
    }

    EXPORT void wxColourData_Delete(wxColourData* self)
    {
        delete self;
    }

    EXPORT void wxColourData_SetChooseFull(wxColourData* self, bool flag)
    {
        self->SetChooseFull(flag);
    }

    EXPORT bool wxColourData_GetChooseFull(wxColourData* self)
    {
        return self->GetChooseFull();
    }

    EXPORT void wxColourData_SetColour(wxColourData* self, wxColour* colour)
    {
        self->SetColour(*colour);
    }

    EXPORT void wxColourData_GetColour(wxColourData* self, wxColour* ref)
    {
        *ref = self->GetColour();
    }

    EXPORT void wxColourData_SetCustomColour(wxColourData* self, int index, wxColour* colour)
    {
        self->SetCustomColour(index, *colour);
    }

    EXPORT void wxColourData_GetCustomColour(wxColourData* self, int index, wxColour* ref)
    {
        *ref = self->GetCustomColour(index);
    }
}
