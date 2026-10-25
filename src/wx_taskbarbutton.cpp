#include "kwx_wrapper.h"

// wxTaskBarButton is only implemented on MSW and only when wxUSE_TASKBARBUTTON is enabled.
// Every wrapper is exported on all platforms so the FFI surface is identical; the unsupported
// branches are inert and return neutral values.
extern "C"
{
    EXPORT void* wxTaskBarButton_New(wxWindow* parent)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        return static_cast<void*>(wxTaskBarButton::New(parent));
#else
        wxUnusedVar(parent);
        return nullptr;
#endif
    }

    EXPORT void wxTaskBarButton_SetProgressRange(wxTaskBarButton* self, int range)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->SetProgressRange(range);
#else
        wxUnusedVar(self);
        wxUnusedVar(range);
#endif
    }

    EXPORT void wxTaskBarButton_SetProgressValue(wxTaskBarButton* self, int value)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->SetProgressValue(value);
#else
        wxUnusedVar(self);
        wxUnusedVar(value);
#endif
    }

    EXPORT void wxTaskBarButton_PulseProgress(wxTaskBarButton* self)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->PulseProgress();
#else
        wxUnusedVar(self);
#endif
    }

    EXPORT void wxTaskBarButton_SetProgressState(wxTaskBarButton* self, int state)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->SetProgressState(static_cast<wxTaskBarButtonState>(state));
#else
        wxUnusedVar(self);
        wxUnusedVar(state);
#endif
    }

    EXPORT void wxTaskBarButton_Show(wxTaskBarButton* self, bool show)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->Show(show);
#else
        wxUnusedVar(self);
        wxUnusedVar(show);
#endif
    }

    EXPORT void wxTaskBarButton_Hide(wxTaskBarButton* self)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->Hide();
#else
        wxUnusedVar(self);
#endif
    }

    EXPORT void wxTaskBarButton_SetThumbnailTooltip(wxTaskBarButton* self, wxString* tooltip)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->SetThumbnailTooltip(*tooltip);
#else
        wxUnusedVar(self);
        wxUnusedVar(tooltip);
#endif
    }

    EXPORT void wxTaskBarButton_SetOverlayIcon(wxTaskBarButton* self, wxIcon* icon,
                                               wxString* description)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->SetOverlayIcon(*icon, *description);
#else
        wxUnusedVar(self);
        wxUnusedVar(icon);
        wxUnusedVar(description);
#endif
    }

    EXPORT void wxTaskBarButton_SetThumbnailClip(wxTaskBarButton* self, int x, int y, int width,
                                                 int height)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->SetThumbnailClip(wxRect(x, y, width, height));
#else
        wxUnusedVar(self);
        wxUnusedVar(x);
        wxUnusedVar(y);
        wxUnusedVar(width);
        wxUnusedVar(height);
#endif
    }

    EXPORT void wxTaskBarButton_Realize(wxTaskBarButton* self)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        self->Realize();
#else
        wxUnusedVar(self);
#endif
    }

    EXPORT void wxTaskBarButton_Delete(wxTaskBarButton* self)
    {
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON
        delete self;
#else
        // The pointer can only point to an object created on this platform, and none is ever
        // created here, so there is nothing to release.
        wxUnusedVar(self);
#endif
    }
}
