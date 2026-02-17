#include "wrapper.h"

// wxStaticText inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT void* wxStaticText_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                     int width, int height, int style)
    {
        return (void*) new wxStaticText(parent, id, *text, wxPoint(x, y), wxSize(width, height),
                                        style);
    }

    EXPORT void wxStaticText_Wrap(wxStaticText* self, int width)
    {
        self->Wrap(width);
    }

    EXPORT bool wxStaticText_IsEllipsized(wxStaticText* self)
    {
        return self->IsEllipsized();
    }
}
