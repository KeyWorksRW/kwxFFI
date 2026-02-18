#include "kwx_wrapper.h"

// wxMDIParentFrame and wxMDIChildFrame inherit from wxFrame (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxMDIParentFrame_Create(wxWindow* parent, int id, wxString* title, int x, int y,
                                         int width, int height, int style)
    {
        return new wxMDIParentFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height),
                                    style);
    }

    EXPORT void* wxMDIParentFrame_GetActiveChild(void* pObject)
    {
        return (void*) ((wxMDIParentFrame*) pObject)->GetActiveChild();
    }

    EXPORT void* wxMDIParentFrame_GetClientWindow(void* pObject)
    {
        return (void*) ((wxMDIParentFrame*) pObject)->GetClientWindow();
    }

    EXPORT void* wxMDIParentFrame_OnCreateClient(void* pObject)
    {
        return (void*) ((wxMDIParentFrame*) pObject)->OnCreateClient();
    }

    EXPORT void* wxMDIParentFrame_GetWindowMenu(void* pObject)
    {
#ifdef __WIN32__
        return (void*) ((wxMDIParentFrame*) pObject)->GetWindowMenu();
#else
        return nullptr;
#endif
    }

    EXPORT void wxMDIParentFrame_SetWindowMenu(void* pObject, void* menu)
    {
#ifdef __WIN32__
        ((wxMDIParentFrame*) pObject)->SetWindowMenu((wxMenu*) menu);
#endif
    }

    EXPORT void wxMDIParentFrame_Cascade(void* pObject)
    {
        ((wxMDIParentFrame*) pObject)->Cascade();
    }

    EXPORT void wxMDIParentFrame_Tile(void* pObject, int orient)
    {
        ((wxMDIParentFrame*) pObject)->Tile((wxOrientation) orient);
    }

    EXPORT void wxMDIParentFrame_ArrangeIcons(void* pObject)
    {
        ((wxMDIParentFrame*) pObject)->ArrangeIcons();
    }

    EXPORT void wxMDIParentFrame_ActivateNext(void* pObject)
    {
        ((wxMDIParentFrame*) pObject)->ActivateNext();
    }

    EXPORT void wxMDIParentFrame_ActivatePrevious(void* pObject)
    {
        ((wxMDIParentFrame*) pObject)->ActivatePrevious();
    }

    EXPORT void* wxMDIChildFrame_Create(wxMDIParentFrame* parent, int id, wxString* title, int x,
                                        int y, int width, int height, int style)
    {
        return new wxMDIChildFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxMDIChildFrame_Activate(void* pObject)
    {
        ((wxMDIChildFrame*) pObject)->Activate();
    }

    EXPORT void* wxMDIChildFrame_GetMDIParent(wxMDIChildFrame* self)
    {
        return (void*) self->GetMDIParent();
    }
}
