#include "wrapper.h"

extern "C"
{
    EXPORT void* wxMiniFrame_Create(wxWindow* parent, int id, wxString* title, int x, int y,
                                    int width, int height, int style)
    {
        return new wxMiniFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }
}
