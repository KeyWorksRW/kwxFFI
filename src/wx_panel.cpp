#include "kwx_wrapper.h"

// wxPanel inherits from wxWindow (not wxControl).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxPanel_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                int style)
    {
        return new wxPanel(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxPanel_InitDialog(void* pObject)
    {
        ((wxPanel*) pObject)->InitDialog();
    }

    EXPORT void* wxPanel_GetDefaultItem(void* pObject)
    {
        return (void*) ((wxTopLevelWindow*) pObject)->GetDefaultItem();
    }

    EXPORT void wxPanel_SetDefaultItem(void* pObject, void* btn)
    {
        ((wxTopLevelWindow*) pObject)->SetDefaultItem((wxButton*) btn);
    }

    EXPORT void wxPanel_SetFocus(void* pObject)
    {
        ((wxPanel*) pObject)->SetFocus();
    }

    EXPORT void wxPanel_SetFocusIgnoringChildren(wxPanel* self)
    {
        self->SetFocusIgnoringChildren();
    }
}
