#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxCriticalSection_Create()
    {
        return (void*) new wxCriticalSection();
    }

    EXPORT void wxCriticalSection_Delete(wxCriticalSection* self)
    {
        delete self;
    }

    EXPORT void wxCriticalSection_Enter(wxCriticalSection* self)
    {
        self->Enter();
    }

    EXPORT void wxCriticalSection_Leave(wxCriticalSection* self)
    {
        self->Leave();
    }

    EXPORT wxMutex* wxMutex_Create()
    {
        return new wxMutex();
    }

    EXPORT void wxMutex_Delete(wxMutex* self)
    {
        delete self;
    }

    EXPORT int wxMutex_Lock(wxMutex* self)
    {
        return (int) self->Lock();
    }

    EXPORT int wxMutex_TryLock(wxMutex* self)
    {
        return (int) self->TryLock();
    }

    EXPORT int wxMutex_Unlock(wxMutex* self)
    {
        return (int) self->Unlock();
    }

    EXPORT bool wxMutex_IsLocked(wxMutex* self)
    {
        // IsLocked() was removed in wxWidgets 2.4+
        return false;
    }

    EXPORT void* wxCondition_Create(void* mutex)
    {
        return (void*) new wxCondition(*((wxMutex*) mutex));
    }

    EXPORT void wxCondition_Delete(wxCondition* self)
    {
        delete self;
    }

    EXPORT void wxCondition_Wait(wxCondition* self)
    {
        self->Wait();
    }

    EXPORT int wxCondition_WaitFor(wxCondition* self, int sec, int nsec)
    {
        return (int) self->WaitTimeout((unsigned long) nsec);
    }

    EXPORT void wxCondition_Signal(wxCondition* self)
    {
        self->Signal();
    }

    EXPORT void wxCondition_Broadcast(wxCondition* self)
    {
        self->Broadcast();
    }

    EXPORT void wxMutexGui_Enter()
    {
        wxMutexGuiEnter();
    }

    EXPORT void wxMutexGui_Leave()
    {
        wxMutexGuiLeave();
    }
}
