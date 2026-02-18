#include "kwx_wrapper.h"
#include <wx/tipwin.h>

// wxTipWindow inherits from wxWindow (via wxPopupTransientWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxTipWindow_Create(wxWindow* parent, wxString* text, int maxLength)
    {
        auto ref = wxTipWindow::New(parent, *text, (wxCoord) maxLength);
        return ref ? (void*) ref.operator->() : nullptr;
    }

    EXPORT void wxTipWindow_SetTipWindowPtr(void* pObject, void* windowPtr)
    {
        ((wxTipWindow*) pObject)->SetTipWindowPtr((wxTipWindow**) windowPtr);
    }

    EXPORT void wxTipWindow_SetBoundingRect(void* pObject, int x, int y, int width, int height)
    {
        ((wxTipWindow*) pObject)->SetBoundingRect(wxRect(x, y, width, height));
    }

    EXPORT void wxTipWindow_Close(void* pObject)
    {
        ((wxTipWindow*) pObject)->Close();
    }
}
