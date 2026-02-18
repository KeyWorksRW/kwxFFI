#include "kwx_wrapper.h"

// wxSplitterWindow inherits from wxWindow (not wxControl).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxSplitterWindow_Create(wxWindow* parent, int id, int x, int y, int width,
                                         int height, int style)
    {
        return new wxSplitterWindow(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void* wxSplitterWindow_GetWindow1(wxSplitterWindow* self)
    {
        return (void*) self->GetWindow1();
    }

    EXPORT void* wxSplitterWindow_GetWindow2(wxSplitterWindow* self)
    {
        return (void*) self->GetWindow2();
    }

    EXPORT void wxSplitterWindow_SetSplitMode(wxSplitterWindow* self, int mode)
    {
        self->SetSplitMode(mode);
    }

    EXPORT int wxSplitterWindow_GetSplitMode(wxSplitterWindow* self)
    {
        return self->GetSplitMode();
    }

    EXPORT void wxSplitterWindow_Initialize(wxSplitterWindow* self, wxWindow* window)
    {
        self->Initialize(window);
    }

    EXPORT bool wxSplitterWindow_SplitVertically(wxSplitterWindow* self, wxWindow* window1,
                                                 wxWindow* window2, int sashPosition)
    {
        return self->SplitVertically(window1, window2, sashPosition);
    }

    EXPORT int wxSplitterWindow_SplitHorizontally(wxSplitterWindow* self, wxWindow* window1,
                                                  wxWindow* window2, int sashPosition)
    {
        return (int) self->SplitHorizontally(window1, window2, sashPosition);
    }

    EXPORT int wxSplitterWindow_Unsplit(wxSplitterWindow* self, wxWindow* toRemove)
    {
        return (int) self->Unsplit(toRemove);
    }

    EXPORT int wxSplitterWindow_ReplaceWindow(wxSplitterWindow* self, wxWindow* winOld,
                                              wxWindow* winNew)
    {
        return (int) self->ReplaceWindow(winOld, winNew);
    }

    EXPORT bool wxSplitterWindow_IsSplit(wxSplitterWindow* self)
    {
        return self->IsSplit();
    }

    EXPORT void wxSplitterWindow_SetBorderSize(wxSplitterWindow* self, int width)
    {
        self->SetBorderSize(width);
    }

    EXPORT int wxSplitterWindow_GetSashSize(wxSplitterWindow* self)
    {
        return self->GetSashSize();
    }

    EXPORT int wxSplitterWindow_GetBorderSize(wxSplitterWindow* self)
    {
        return self->GetBorderSize();
    }

    EXPORT void wxSplitterWindow_SetSashPosition(wxSplitterWindow* self, int position, bool redraw)
    {
        self->SetSashPosition(position, redraw);
    }

    EXPORT int wxSplitterWindow_GetSashPosition(wxSplitterWindow* self)
    {
        return self->GetSashPosition();
    }

    EXPORT void wxSplitterWindow_SetMinimumPaneSize(wxSplitterWindow* self, int min)
    {
        self->SetMinimumPaneSize(min);
    }

    EXPORT int wxSplitterWindow_GetMinimumPaneSize(wxSplitterWindow* self)
    {
        return self->GetMinimumPaneSize();
    }

    EXPORT double wxSplitterWindow_GetSashGravity(wxSplitterWindow* self)
    {
        return self->GetSashGravity();
    }

    EXPORT void wxSplitterWindow_SetSashGravity(wxSplitterWindow* self, double gravity)
    {
        return self->SetSashGravity(gravity);
    }

    EXPORT void wxSplitterWindow_UpdateSize(wxSplitterWindow* self)
    {
        self->UpdateSize();
    }

    EXPORT void wxSplitterWindow_SetSashInvisible(wxSplitterWindow* self, bool invisible)
    {
        self->SetSashInvisible(invisible);
    }

    EXPORT bool wxSplitterWindow_IsSashInvisible(wxSplitterWindow* self)
    {
        return self->IsSashInvisible();
    }

    EXPORT int wxSplitterWindow_GetDefaultSashSize(wxSplitterWindow* self)
    {
        return self->GetDefaultSashSize();
    }
}
