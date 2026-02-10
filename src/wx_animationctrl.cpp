#include "wrapper.h"

extern "C"
{
    EXPORT wxAnimationCtrl* wxAnimationCtrl_Create(wxWindow* parent, int id, int x, int y, int width,
                                                   int height, int style)
    {
        return new wxAnimationCtrl(parent, id, wxNullAnimation, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT wxAnimationCtrl* wxAnimationCtrl_CreateWithAnimation(wxWindow* parent, int id,
                                                                wxAnimation* anim, int x, int y,
                                                                int width, int height, int style)
    {
        return new wxAnimationCtrl(parent, id, *anim, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxAnimationCtrl_GetAnimation(wxAnimationCtrl* self, wxAnimation* anim)
    {
        *anim = self->GetAnimation();
    }

    EXPORT void wxAnimationCtrl_GetInactiveBitmap(wxAnimationCtrl* self, wxBitmap* bmp)
    {
        *bmp = self->GetInactiveBitmap();
    }

    EXPORT bool wxAnimationCtrl_IsPlaying(wxAnimationCtrl* self)
    {
        return self->IsPlaying();
    }

    EXPORT bool wxAnimationCtrl_LoadFile(wxAnimationCtrl* self, wxString* filename, int type)
    {
        return self->LoadFile(*filename, static_cast<wxAnimationType>(type));
    }

    EXPORT bool wxAnimationCtrl_Load(wxAnimationCtrl* self, wxInputStream* stream, int type)
    {
        return self->Load(*stream, static_cast<wxAnimationType>(type));
    }

    EXPORT bool wxAnimationCtrl_Play(wxAnimationCtrl* self)
    {
        return self->Play();
    }

    EXPORT void wxAnimationCtrl_SetAnimation(wxAnimationCtrl* self, wxAnimation* anim)
    {
        self->SetAnimation(*anim);
    }

    EXPORT void wxAnimationCtrl_SetInactiveBitmap(wxAnimationCtrl* self, wxBitmap* bmp)
    {
        self->SetInactiveBitmap(*bmp);
    }

    EXPORT void wxAnimationCtrl_Stop(wxAnimationCtrl* self)
    {
        self->Stop();
    }

    // wxAnimation functions
    EXPORT wxAnimation* wxAnimation_Create()
    {
        return new wxAnimation();
    }

    EXPORT wxAnimation* wxAnimation_CreateFromFile(wxString* filename, int type)
    {
        wxAnimation* anim = new wxAnimation();
        if (!anim->LoadFile(*filename, static_cast<wxAnimationType>(type)))
        {
            delete anim;
            return nullptr;
        }
        return anim;
    }

    EXPORT void wxAnimation_Delete(wxAnimation* self)
    {
        delete self;
    }

    EXPORT int wxAnimation_GetDelay(wxAnimation* self, int frame)
    {
        return self->GetDelay(frame);
    }

    EXPORT int wxAnimation_GetFrameCount(wxAnimation* self)
    {
        return self->GetFrameCount();
    }

    EXPORT void wxAnimation_GetFrame(wxAnimation* self, int frame, wxImage* image)
    {
        *image = self->GetFrame(frame);
    }

    EXPORT void wxAnimation_GetSize(wxAnimation* self, int* width, int* height)
    {
        wxSize text = self->GetSize();
        *width = text.GetWidth();
        *height = text.GetHeight();
    }

    EXPORT bool wxAnimation_IsOk(wxAnimation* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxAnimation_LoadFile(wxAnimation* self, wxString* filename, int type)
    {
        return self->LoadFile(*filename, static_cast<wxAnimationType>(type));
    }

    EXPORT bool wxAnimation_Load(wxAnimation* self, wxInputStream* stream, int type)
    {
        return self->Load(*stream, static_cast<wxAnimationType>(type));
    }
}
