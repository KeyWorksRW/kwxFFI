#include "wrapper.h"

extern "C"
{
    EXPORT void* wxCriticalSection_Create()
    {
        return (void*) new wxCriticalSection();
    }

    EXPORT void wxCriticalSection_Delete(void* self)
    {
        delete (wxCriticalSection*) self;
    }

    EXPORT void wxCriticalSection_Enter(void* self)
    {
        ((wxCriticalSection*) self)->Enter();
    }

    EXPORT void wxCriticalSection_Leave(void* self)
    {
        ((wxCriticalSection*) self)->Leave();
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

    EXPORT void* wxCondition_Create(void* _mutex)
    {
        return (void*) new wxCondition(*((wxMutex*) _mutex));
    }

    EXPORT void wxCondition_Delete(void* self)
    {
        delete (wxCondition*) self;
    }

    EXPORT void wxCondition_Wait(void* self)
    {
        ((wxCondition*) self)->Wait();
    }

    EXPORT int wxCondition_WaitFor(void* self, int sec, int nsec)
    {
        return (int) ((wxCondition*) self)->WaitTimeout((unsigned long) nsec);
    }

    EXPORT void wxCondition_Signal(void* self)
    {
        ((wxCondition*) self)->Signal();
    }

    EXPORT void wxCondition_Broadcast(void* self)
    {
        ((wxCondition*) self)->Broadcast();
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
