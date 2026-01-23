#include "wrapper.h"

extern "C"
{
    EXPORT void* wxStaticText_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                     int width, int height, int style)
    {
        return (void*) new wxStaticText(parent, id, *text, wxPoint(x, y), wxSize(width, height),
                                        style);
    }
}
