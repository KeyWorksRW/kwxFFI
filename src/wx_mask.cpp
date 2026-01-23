#include "wrapper.h"

extern "C"
{
    EXPORT void* wxMask_Create(void* bitmap)
    {
        return (void*) new wxMask(*(wxBitmap*) bitmap);
    }

    EXPORT void* wxMask_CreateColoured(void* bitmap, void* colour)
    {
        return (void*) new wxMask(*(wxBitmap*) bitmap, *(wxColour*) colour);
    }
}
