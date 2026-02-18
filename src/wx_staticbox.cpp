#include "kwx_wrapper.h"

// wxStaticBox inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT void* wxStaticBox_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                    int width, int height, int style)
    {
        return (void*) new wxStaticBox(parent, id, *text, wxPoint(x, y), wxSize(width, height),
                                       style);
    }

    EXPORT void wxStaticBox_GetBordersForSizer(wxStaticBox* self, int* borderTop, int* borderOther)
    {
        self->GetBordersForSizer(borderTop, borderOther);
    }
}
