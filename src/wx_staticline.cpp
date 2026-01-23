#include "wrapper.h"

extern "C"
{
    EXPORT void* wxStaticLine_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                     int style)
    {
        return (void*) new wxStaticLine(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT bool wxStaticLine_IsVertical(wxStaticLine* self)
    {
        return self->IsVertical();
    }

    EXPORT int wxStaticLine_GetDefaultSize(wxStaticLine* self)
    {
        return self->GetDefaultSize();
    }
}
