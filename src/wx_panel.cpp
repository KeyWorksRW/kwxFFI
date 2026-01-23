#include "wrapper.h"

extern "C"
{
    EXPORT void* wxPanel_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                int style)
    {
        return new wxPanel(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxPanel_InitDialog(void* _obj)
    {
        ((wxPanel*) _obj)->InitDialog();
    }

    EXPORT void* wxPanel_GetDefaultItem(void* _obj)
    {
        return (void*) ((wxTopLevelWindow*) _obj)->GetDefaultItem();
    }

    EXPORT void wxPanel_SetDefaultItem(void* _obj, void* btn)
    {
        ((wxTopLevelWindow*) _obj)->SetDefaultItem((wxButton*) btn);
    }

    EXPORT void wxPanel_SetFocus(void* _obj)
    {
        ((wxPanel*) _obj)->SetFocus();
    }
}
