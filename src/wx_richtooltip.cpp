#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxRichToolTip_Create(wxString* title, wxString* message)
    {
        return static_cast<void*>(new wxRichToolTip(*title, *message));
    }

    EXPORT void wxRichToolTip_SetBackgroundColour(wxRichToolTip* self, wxColour* colour,
                                                  wxColour* colour_end)
    {
        const wxColour end_colour = colour_end ? *colour_end : wxColour();
        self->SetBackgroundColour(*colour, end_colour);
    }

    EXPORT void wxRichToolTip_SetIcon(wxRichToolTip* self, int icon)
    {
        self->SetIcon(icon);
    }

    EXPORT void wxRichToolTip_SetTimeout(wxRichToolTip* self, unsigned milliseconds,
                                         unsigned show_delay)
    {
        self->SetTimeout(milliseconds, show_delay);
    }

    EXPORT void wxRichToolTip_ShowFor(wxRichToolTip* self, wxWindow* window, wxRect* rect)
    {
        self->ShowFor(window, rect);
    }

    EXPORT void wxRichToolTip_Delete(wxRichToolTip* self)
    {
        delete self;
    }
}
