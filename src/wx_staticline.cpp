#include "wrapper.h"

// wxStaticLine inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

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
