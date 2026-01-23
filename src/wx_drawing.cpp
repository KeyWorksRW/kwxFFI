#include "wrapper.h"

extern "C"
{
    EXPORT void* wxDrawWindow_Create(void* parent, int id, int x, int y, int width, int height,
                                     int style)
    {
        return (void*) new wxWindow((wxWindow*) parent, id, wxPoint(x, y), wxSize(width, height),
                                    style);
    }

    EXPORT void* wxDrawControl_Create(void* parent, int id, int x, int y, int width, int height,
                                      int style)
    {
        return (void*) new wxControl((wxWindow*) parent, id, wxPoint(x, y), wxSize(width, height),
                                     style);
    }
}
