#include "wrapper.h"

extern "C"
{
    EXPORT void* wxSplitterWindow_Create(wxWindow* parent, int id, int x, int y, int width,
                                         int height, int style)
    {
        return new wxSplitterWindow(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void* wxSplitterWindow_GetWindow1(void* self)
    {
        return (void*) ((wxSplitterWindow*) self)->GetWindow1();
    }

    EXPORT void* wxSplitterWindow_GetWindow2(void* self)
    {
        return (void*) ((wxSplitterWindow*) self)->GetWindow2();
    }

    EXPORT void wxSplitterWindow_SetSplitMode(void* self, int mode)
    {
        ((wxSplitterWindow*) self)->SetSplitMode(mode);
    }

    EXPORT int wxSplitterWindow_GetSplitMode(void* self)
    {
        return ((wxSplitterWindow*) self)->GetSplitMode();
    }

    EXPORT void wxSplitterWindow_Initialize(void* self, wxWindow* window)
    {
        ((wxSplitterWindow*) self)->Initialize(window);
    }

    EXPORT bool wxSplitterWindow_SplitVertically(wxSplitterWindow* self, wxWindow* window1,
                                                 wxWindow* window2, int sashPosition)
    {
        return self->SplitVertically(window1, window2, sashPosition);
    }

    EXPORT int wxSplitterWindow_SplitHorizontally(void* self, wxWindow* window1, wxWindow* window2,
                                                  int sashPosition)
    {
        return (int) ((wxSplitterWindow*) self)->SplitHorizontally(window1, window2, sashPosition);
    }

    EXPORT int wxSplitterWindow_Unsplit(void* self, wxWindow* toRemove)
    {
        return (int) ((wxSplitterWindow*) self)->Unsplit(toRemove);
    }

    EXPORT int wxSplitterWindow_ReplaceWindow(void* self, wxWindow* winOld, wxWindow* winNew)
    {
        return (int) ((wxSplitterWindow*) self)->ReplaceWindow(winOld, winNew);
    }

    EXPORT bool wxSplitterWindow_IsSplit(wxSplitterWindow* self)
    {
        return self->IsSplit();
    }

    // Obsolete
    // EWXWEXPORT(void,wxSplitterWindow_SetSashSize)(void* self,int width)

    EXPORT void wxSplitterWindow_SetBorderSize(void* self, int width)
    {
        ((wxSplitterWindow*) self)->SetBorderSize(width);
    }

    EXPORT int wxSplitterWindow_GetSashSize(void* self)
    {
        return ((wxSplitterWindow*) self)->GetSashSize();
    }

    EXPORT int wxSplitterWindow_GetBorderSize(void* self)
    {
        return ((wxSplitterWindow*) self)->GetBorderSize();
    }

    EXPORT void wxSplitterWindow_SetSashPosition(void* self, int position, bool redraw)
    {
        ((wxSplitterWindow*) self)->SetSashPosition(position, redraw);
    }

    EXPORT int wxSplitterWindow_GetSashPosition(void* self)
    {
        return ((wxSplitterWindow*) self)->GetSashPosition();
    }

    EXPORT void wxSplitterWindow_SetMinimumPaneSize(void* self, int min)
    {
        ((wxSplitterWindow*) self)->SetMinimumPaneSize(min);
    }

    EXPORT int wxSplitterWindow_GetMinimumPaneSize(void* self)
    {
        return ((wxSplitterWindow*) self)->GetMinimumPaneSize();
    }

    EXPORT double wxSplitterWindow_GetSashGravity(void* self)
    {
        return ((wxSplitterWindow*) self)->GetSashGravity();
    }

    EXPORT void wxSplitterWindow_SetSashGravity(void* self, double gravity)
    {
        return ((wxSplitterWindow*) self)->SetSashGravity(gravity);
    }
}
