#include "wrapper.h"

extern "C"
{
    EXPORT wxSplashScreen* wxSplashScreen_Create(wxBitmap bitmap, long splashStyle, int timeout,
                                                 wxWindow* parent, int id, int x, int y, int width,
                                                 int height, long style)
    {
        return new wxSplashScreen(bitmap, splashStyle, timeout, parent, id, wxPoint(x, y),
                                  wxSize(width, height), style);
    }

    EXPORT long wxSplashScreen_GetSplashStyle(wxSplashScreen* self)
    {
        return self->GetSplashStyle();
    }

    EXPORT int wxSplashScreen_GetTimeout(wxSplashScreen* self)
    {
        return self->GetTimeout();
    }
}
