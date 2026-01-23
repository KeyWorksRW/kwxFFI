#include "wrapper.h"

extern "C"
{
    EXPORT wxBannerWindow* wxBannerWindow_Create(wxWindow* parent, int id, int dir, int x, int y,
                                                 int w, int h, int style)
    {
        return new wxBannerWindow(parent, id, static_cast<wxDirection>(dir), wxPoint(x, y),
                                  wxSize(w, h), style);
    }

    EXPORT void wxBannerWindow_SetBitmap(wxBannerWindow* self, wxBitmap* bmp)
    {
        self->SetBitmap(*bmp);
    }

    EXPORT void wxBannerWindow_SetText(wxBannerWindow* self, wxString* title, wxString* message)
    {
        self->SetText(*title, *message);
    }

    EXPORT void wxBannerWindow_SetGradient(wxBannerWindow* self, wxColour* start, wxColour* end)
    {
        self->SetGradient(*start, *end);
    }
}
