#include "wrapper.h"

#include <wx/mediactrl.h>

// wxMediaCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    MAKE_EVENT_WRAPPER(EVT_MEDIA_FINISHED)
    MAKE_EVENT_WRAPPER(EVT_MEDIA_STOP)
    MAKE_EVENT_WRAPPER(EVT_MEDIA_LOADED)
    MAKE_EVENT_WRAPPER(EVT_MEDIA_STATECHANGED)
    MAKE_EVENT_WRAPPER(EVT_MEDIA_PLAY)
    MAKE_EVENT_WRAPPER(EVT_MEDIA_PAUSE)

    EXPORT wxMediaCtrl* wxMediaCtrl_Create(void* parent, int id, wxString* fileName, int x, int y,
                                           int width, int height, long style, wxString* szBackend,
                                           wxString* name)
    {
        return new wxMediaCtrl((wxWindow*) parent, (wxWindowID) id,
                               (fileName ? *fileName : wxString("")), wxPoint(x, y), wxSize(width, height),
                               style, (szBackend ? *szBackend : wxString("")), wxDefaultValidator,
                               (name ? *name : wxString("MediaCtrl")));
    }

    EXPORT void wxMediaCtrl_Delete(wxMediaCtrl* self)
    {
        if (self)
            delete self;
    }

    EXPORT wxSize* wxMediaCtrl_GetBestSize(wxMediaCtrl* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetBestSize();
        return text;
    }

    EXPORT double wxMediaCtrl_GetPlaybackRate(wxMediaCtrl* self)
    {
        return self->GetPlaybackRate();
    }

    EXPORT double wxMediaCtrl_GetVolume(wxMediaCtrl* self)
    {
        return self->GetVolume();
    }

    EXPORT int wxMediaCtrl_GetState(wxMediaCtrl* self)
    {
        return self->GetState();
    }

    EXPORT wxFileOffset wxMediaCtrl_Length(wxMediaCtrl* self)
    {
        return self->Length();
    }

    EXPORT bool wxMediaCtrl_Load(wxMediaCtrl* self, const wxString* fileName)
    {
        return self->Load(*fileName);
    }

    EXPORT bool wxMediaCtrl_LoadURI(wxMediaCtrl* self, const wxString* uri)
    {
        return self->LoadURI(*uri);
    }

    EXPORT bool wxMediaCtrl_LoadURIWithProxy(wxMediaCtrl* self, const wxString* uri,
                                             const wxString* proxy)
    {
        return self->LoadURIWithProxy(*uri, *proxy);
    }

    EXPORT bool wxMediaCtrl_Pause(wxMediaCtrl* self)
    {
        return self->Pause();
    }

    EXPORT bool wxMediaCtrl_Play(wxMediaCtrl* self)
    {
        return self->Play();
    }

    EXPORT wxFileOffset wxMediaCtrl_Seek(wxMediaCtrl* self, wxFileOffset offsetWhere, int mode)
    {
        return self->Seek(offsetWhere, static_cast<wxSeekMode>(mode));
    }

    EXPORT bool wxMediaCtrl_SetPlaybackRate(wxMediaCtrl* self, double dRate)
    {
        return self->SetPlaybackRate(dRate);
    }

    EXPORT bool wxMediaCtrl_SetVolume(wxMediaCtrl* self, double dVolume)
    {
        return self->SetVolume(dVolume);
    }

    EXPORT bool wxMediaCtrl_ShowPlayerControls(wxMediaCtrl* self, int flags)
    {
        return self->ShowPlayerControls(static_cast<wxMediaCtrlPlayerControls>(flags));
    }

    EXPORT bool wxMediaCtrl_Stop(wxMediaCtrl* self)
    {
        return self->Stop();
    }

    EXPORT wxFileOffset wxMediaCtrl_Tell(wxMediaCtrl* self)
    {
        return self->Tell();
    }
}
