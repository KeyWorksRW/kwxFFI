#include "kwx_wrapper.h"

// wxColourDialog inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT wxColourDialog* wxColourDialog_Create(wxWindow* parent, wxColourData* col)
    {
        return new wxColourDialog(parent, col);
    }

    EXPORT void wxColourDialog_GetColourData(wxColourDialog* self, wxColourData* col)
    {
        *col = self->GetColourData();
    }
}
