// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/custombgwin.h>
#include <wx/scrolwin.h>

// wxCustomBackgroundWindow<W> is a template mixin (wx/custombgwin.h): a template cannot appear in
// the generated model, so the scrolled-window instantiation gets its own wrapper class here.
// The mixin declares only a default constructor, hence default-construct + Create() below.
class kwxCustomBackgroundWindow : public wxCustomBackgroundWindow<wxScrolledWindow>
{
};

extern "C"
{
    EXPORT void* kwxCustomBackgroundWindow_Create(wxWindow* parent, int id, int x, int y, int width,
                                                  int height, int style)
    {
        auto* window = new kwxCustomBackgroundWindow();
        if (!window->Create(parent, (wxWindowID) id, wxPoint(x, y), wxSize(width, height),
                            (long) style))
        {
            delete window;
            return nullptr;
        }

        return (void*) window;
    }

    EXPORT void* kwxCustomBackgroundWindow_CreateDefault(wxWindow* parent, int id)
    {
        auto* window = new kwxCustomBackgroundWindow();
        if (!window->Create(parent, (wxWindowID) id, wxDefaultPosition, wxDefaultSize,
                            wxScrolledWindowStyle))
        {
            delete window;
            return nullptr;
        }

        return (void*) window;
    }

    EXPORT void kwxCustomBackgroundWindow_SetBackgroundBitmap(kwxCustomBackgroundWindow* self,
                                                              wxBitmap* bitmap)
    {
        // An invalid bitmap clears the custom background, exactly as wxBitmap() does in the
        // wxWidgets erase sample.
        self->SetBackgroundBitmap(bitmap ? *bitmap : wxBitmap());
    }

    EXPORT void kwxCustomBackgroundWindow_ClearBackgroundBitmap(kwxCustomBackgroundWindow* self)
    {
        self->SetBackgroundBitmap(wxBitmap());
    }
}
