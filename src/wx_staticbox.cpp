#include "wrapper.h"

extern "C"
{
    EXPORT void* wxStaticBox_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                    int width, int height, int style)
    {
        return (void*) new wxStaticBox(parent, id, *text, wxPoint(x, y), wxSize(width, height),
                                       style);
    }
}
