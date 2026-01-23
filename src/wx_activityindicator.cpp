#include "wrapper.h"

extern "C"
{
    EXPORT wxActivityIndicator* wxActivityIndicator_Create(wxWindow* parent, int id, int x, int y,
                                                           int w, int h, int style)
    {
        return new wxActivityIndicator(parent, id, wxPoint(x, y), wxSize(w, h), style);
    }

    EXPORT bool wxActivityIndicator_IsRunning(wxActivityIndicator* self)
    {
        return self->IsRunning();
    }

    EXPORT void wxActivityIndicator_Start(wxActivityIndicator* self)
    {
        self->Start();
    }

    EXPORT void wxActivityIndicator_Stop(wxActivityIndicator* self)
    {
        self->Stop();
    }
}
