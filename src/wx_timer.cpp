#include "wrapper.h"

extern "C"
{
    EXPORT wxTimer* wxTimer_Create(wxEvtHandler* owner, int id)
    {
        return new wxTimer(owner, id);
    }

    EXPORT void wxTimer_Delete(wxTimer* self)
    {
        delete self;
    }

    EXPORT bool wxTimer_Start(wxTimer* self, int milliseconds, bool oneShot)
    {
        return self->Start(milliseconds, oneShot);
    }

    EXPORT void wxTimer_Stop(wxTimer* self)
    {
        self->Stop();
    }

    EXPORT bool wxTimer_IsRuning(wxTimer* self)
    {
        return self->IsRunning();
    }

    EXPORT bool wxTimer_IsOneShot(wxTimer* self)
    {
        return self->IsOneShot();
    }

    EXPORT int wxTimer_GetInterval(wxTimer* self)
    {
        return self->GetInterval();
    }

    EXPORT wxStopWatch* wxStopWatch_Create()
    {
        return new wxStopWatch();
    }

    EXPORT void wxStopWatch_Delete(wxStopWatch* self)
    {
        delete self;
    }

    EXPORT void wxStopWatch_Start(wxStopWatch* self, int milliseconds)
    {
        self->Start((long) milliseconds);
    }

    EXPORT void wxStopWatch_Pause(wxStopWatch* self)
    {
        self->Pause();
    }

    EXPORT void wxStopWatch_Resume(wxStopWatch* self)
    {
        self->Resume();
    }

    EXPORT long wxStopWatch_Time(wxStopWatch* self)
    {
        return self->Time();
    }
}
