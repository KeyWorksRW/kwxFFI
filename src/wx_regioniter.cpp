#include "wrapper.h"

extern "C"
{
    EXPORT void* wxRegionIterator_Create()
    {
        return (void*) new wxRegionIterator();
    }

    EXPORT void* wxRegionIterator_CreateFromRegion(void* region)
    {
        return (void*) new wxRegionIterator(*((wxRegion*) region));
    }

    EXPORT void wxRegionIterator_Delete(wxRegionIterator* self)
    {
        delete self;
    }

    EXPORT void wxRegionIterator_Reset(wxRegionIterator* self)
    {
        self->Reset();
    }

    EXPORT void wxRegionIterator_ResetToRegion(wxRegionIterator* self, wxRegion* region)
    {
        self->Reset(*region);
    }

    EXPORT bool wxRegionIterator_HaveRects(wxRegionIterator* self)
    {
        return self->HaveRects();
    }

    EXPORT void wxRegionIterator_Next(wxRegionIterator* self)
    {
        (*self)++;
    }

    EXPORT int wxRegionIterator_GetX(wxRegionIterator* self)
    {
        return self->GetX();
    }

    EXPORT int wxRegionIterator_GetY(wxRegionIterator* self)
    {
        return self->GetY();
    }

    EXPORT int wxRegionIterator_GetWidth(wxRegionIterator* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxRegionIterator_GetHeight(wxRegionIterator* self)
    {
        return self->GetHeight();
    }
}
