#include "kwx_wrapper.h"

// wxTaskBarButton only exists on MSW and only when wxUSE_TASKBARBUTTON is enabled.
#if defined(__WXMSW__) && wxUSE_TASKBARBUTTON

extern "C"
{
    EXPORT void* wxTaskBarButton_New(wxWindow* parent)
    {
        return static_cast<void*>(wxTaskBarButton::New(parent));
    }

    EXPORT void wxTaskBarButton_SetProgressRange(wxTaskBarButton* self, int range)
    {
        self->SetProgressRange(range);
    }

    EXPORT void wxTaskBarButton_SetProgressValue(wxTaskBarButton* self, int value)
    {
        self->SetProgressValue(value);
    }

    EXPORT void wxTaskBarButton_PulseProgress(wxTaskBarButton* self)
    {
        self->PulseProgress();
    }

    EXPORT void wxTaskBarButton_SetProgressState(wxTaskBarButton* self, int state)
    {
        self->SetProgressState(static_cast<wxTaskBarButtonState>(state));
    }

    EXPORT void wxTaskBarButton_Show(wxTaskBarButton* self, bool show)
    {
        self->Show(show);
    }

    EXPORT void wxTaskBarButton_Hide(wxTaskBarButton* self)
    {
        self->Hide();
    }

    EXPORT void wxTaskBarButton_SetThumbnailTooltip(wxTaskBarButton* self, wxString* tooltip)
    {
        self->SetThumbnailTooltip(*tooltip);
    }

    EXPORT void wxTaskBarButton_SetOverlayIcon(wxTaskBarButton* self, wxIcon* icon,
                                               wxString* description)
    {
        self->SetOverlayIcon(*icon, *description);
    }

    EXPORT void wxTaskBarButton_SetThumbnailClip(wxTaskBarButton* self, int x, int y, int width,
                                                 int height)
    {
        self->SetThumbnailClip(wxRect(x, y, width, height));
    }

    EXPORT void wxTaskBarButton_Realize(wxTaskBarButton* self)
    {
        self->Realize();
    }

    EXPORT void wxTaskBarButton_Delete(wxTaskBarButton* self)
    {
        delete self;
    }
}

#endif  // defined(__WXMSW__) && wxUSE_TASKBARBUTTON
