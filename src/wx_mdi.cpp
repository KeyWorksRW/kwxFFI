#include "wrapper.h"

extern "C"
{
    EXPORT void* wxMDIParentFrame_Create(wxWindow* parent, int id, wxString* title, int x, int y,
                                         int width, int height, int style)
    {
        return new wxMDIParentFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height),
                                    style);
    }

    EXPORT void* wxMDIParentFrame_GetActiveChild(void* _obj)
    {
        return (void*) ((wxMDIParentFrame*) _obj)->GetActiveChild();
    }

    EXPORT void* wxMDIParentFrame_GetClientWindow(void* _obj)
    {
        return (void*) ((wxMDIParentFrame*) _obj)->GetClientWindow();
    }

    EXPORT void* wxMDIParentFrame_OnCreateClient(void* _obj)
    {
        return (void*) ((wxMDIParentFrame*) _obj)->OnCreateClient();
    }

    EXPORT void* wxMDIParentFrame_GetWindowMenu(void* _obj)
    {
#ifdef __WIN32__
        return (void*) ((wxMDIParentFrame*) _obj)->GetWindowMenu();
#else
        return nullptr;
#endif
    }

    EXPORT void wxMDIParentFrame_SetWindowMenu(void* _obj, void* menu)
    {
#ifdef __WIN32__
        ((wxMDIParentFrame*) _obj)->SetWindowMenu((wxMenu*) menu);
#endif
    }

    EXPORT void wxMDIParentFrame_Cascade(void* _obj)
    {
        ((wxMDIParentFrame*) _obj)->Cascade();
    }

    EXPORT void wxMDIParentFrame_Tile(void* _obj, int orient)
    {
        ((wxMDIParentFrame*) _obj)->Tile((wxOrientation) orient);
    }

    EXPORT void wxMDIParentFrame_ArrangeIcons(void* _obj)
    {
        ((wxMDIParentFrame*) _obj)->ArrangeIcons();
    }

    EXPORT void wxMDIParentFrame_ActivateNext(void* _obj)
    {
        ((wxMDIParentFrame*) _obj)->ActivateNext();
    }

    EXPORT void wxMDIParentFrame_ActivatePrevious(void* _obj)
    {
        ((wxMDIParentFrame*) _obj)->ActivatePrevious();
    }

    EXPORT void* wxMDIChildFrame_Create(wxMDIParentFrame* parent, int id, wxString* title, int x,
                                        int y, int width, int height, int style)
    {
        return new wxMDIChildFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxMDIChildFrame_Activate(void* _obj)
    {
        ((wxMDIChildFrame*) _obj)->Activate();
    }
}
