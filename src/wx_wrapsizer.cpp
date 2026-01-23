// wxWrapSizer - Wrapping sizer that automatically wraps to next line
#include "wrapper.h"

extern "C"
{
    // Constructor
    EXPORT wxWrapSizer* wxWrapSizer_Create(int orient, int flags)
    {
        return new wxWrapSizer(orient, flags);
    }

    // Get orientation
    EXPORT int wxWrapSizer_GetOrientation(wxWrapSizer* self)
    {
        return self->GetOrientation();
    }

    // Set orientation
    EXPORT void wxWrapSizer_SetOrientation(wxWrapSizer* self, int orient)
    {
        self->SetOrientation(orient);
    }

    // Check if wrap needed
    EXPORT bool wxWrapSizer_InformFirstDirection(wxWrapSizer* self, int direction, int size,
                                                 int availableOtherDir)
    {
        return self->InformFirstDirection(direction, size, availableOtherDir);
    }
}
