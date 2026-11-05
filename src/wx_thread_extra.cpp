// Base-utility thread, synchronization and dynamic-library wrappers: the kwxThread callback
// subclass, wxSemaphore, wxDynamicLibrary, and the methods missing from the wxMutex,
// wxCriticalSection and wxCondition blocks.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/dynlib.h>

#include <bit>
#include <cstdint>
#include <tuple>
#include <unordered_map>

// wxDynamicLibrary has no accessor for the name it was loaded from, so the wrappers remember
// the name of the most recent successful Load() per object. The map is keyed by the object
// pointer and guarded by a critical section because Load() may be called from any thread.
//
// wxCriticalSection is safe as a static global: its constructor does not allocate memory.
static wxCriticalSection s_library_names_crit_section;
static std::unordered_map<const wxDynamicLibrary*, wxString> s_library_names;

static void RememberLibraryName(const wxDynamicLibrary* library, const wxString& library_name)
{
    const wxCriticalSectionLocker locker(s_library_names_crit_section);
    s_library_names[library] = library_name;
}

static wxString LookupLibraryName(const wxDynamicLibrary* library)
{
    const wxCriticalSectionLocker locker(s_library_names_crit_section);
    const std::unordered_map<const wxDynamicLibrary*, wxString>::const_iterator iter =
        s_library_names.find(library);
    if (iter == s_library_names.end())
    {
        return wxString();
    }
    return iter->second;
}

static void ForgetLibraryName(const wxDynamicLibrary* library)
{
    const wxCriticalSectionLocker locker(s_library_names_crit_section);
    std::ignore = s_library_names.erase(library);
}

// ---------------------------------------------------------------------------
// kwxThread
// ---------------------------------------------------------------------------

kwxThread::kwxThread(void* pObject, void* entryFunc, wxThreadKind kind) : wxThread(kind)
{
    m_object = pObject;
    m_entry_func = std::bit_cast<kwxThreadEntryFunc>(entryFunc);
    m_test_destroy_func = nullptr;
    m_on_exit_func = nullptr;
}

wxThread::ExitCode kwxThread::Entry()
{
    if (!m_entry_func)
    {
        return nullptr;
    }
    return m_entry_func(m_object);
}

bool kwxThread::TestDestroy()
{
    // A registered callback decides whether the thread should stop; that is what makes Pause()
    // and Delete() work, because the base implementation only reports a cancellation the thread
    // already observed. Without a callback the wxWidgets default behavior applies.
    if (!m_test_destroy_func)
    {
        return wxThread::TestDestroy();
    }
    return m_test_destroy_func(m_object) != 0;
}

void kwxThread::OnExit()
{
    if (m_on_exit_func)
    {
        m_on_exit_func(m_object);
    }
}

extern "C"
{
    // -----------------------------------------------------------------------
    // wxThread
    // -----------------------------------------------------------------------

    EXPORT wxThread* wxThread_Create(void* pObject, void* entryFunc, int flags)
    {
        const wxThreadKind kind =
            (flags == wxTHREAD_JOINABLE) ? wxTHREAD_JOINABLE : wxTHREAD_DETACHED;
        return new kwxThread(pObject, entryFunc, kind);
    }

    EXPORT void wxThread_Delete(wxThread* self)
    {
        if (self == nullptr)
        {
            return;
        }

        // Delete() asks the thread to stop and, for a detached thread, also destroys the
        // wxThread object itself. A joinable thread stays owned by the caller and is deleted
        // below.
        const bool is_detached = self->IsDetached();
        std::ignore = self->Delete();
        if (!is_detached)
        {
            delete self;
        }
    }

    EXPORT int wxThread_Start(wxThread* self)
    {
        return static_cast<int>(self->Run());
    }

    EXPORT int wxThread_Run(wxThread* self)
    {
        return static_cast<int>(self->Run());
    }

    EXPORT void* wxThread_Wait(wxThread* self)
    {
        return self->Wait();
    }

    EXPORT int wxThread_Pause(wxThread* self)
    {
        return static_cast<int>(self->Pause());
    }

    EXPORT int wxThread_Resume(wxThread* self)
    {
        return static_cast<int>(self->Resume());
    }

    EXPORT int wxThread_IsAlive(wxThread* self)
    {
        return self->IsAlive();
    }

    EXPORT int wxThread_IsRunning(wxThread* self)
    {
        return self->IsRunning();
    }

    EXPORT int wxThread_TestDestroy(wxThread* self)
    {
        return self->TestDestroy();
    }

    EXPORT uint32_t wxThread_GetId(wxThread* self)
    {
        return static_cast<uint32_t>(self->GetId());
    }

    EXPORT void wxThread_SetPriority(wxThread* self, int priority)
    {
        // Valid values are 0..100; wxWidgets asserts on anything outside that range.
        self->SetPriority(static_cast<unsigned int>(priority));
    }

    EXPORT int wxThread_GetPriority(wxThread* self)
    {
        return static_cast<int>(self->GetPriority());
    }

    EXPORT void wxThread_SetOnTestDestroy(wxThread* self, void* pFunction)
    {
        kwxThread* thread = static_cast<kwxThread*>(self);
        thread->SetOnTestDestroy(pFunction);
    }

    EXPORT void wxThread_SetOnExit(wxThread* self, void* pFunction)
    {
        kwxThread* thread = static_cast<kwxThread*>(self);
        thread->SetOnExit(pFunction);
    }

    // -----------------------------------------------------------------------
    // wxSemaphore
    // -----------------------------------------------------------------------

    EXPORT wxSemaphore* wxSemaphore_Create(int initial, int maxCount)
    {
        return new wxSemaphore(initial, maxCount);
    }

    EXPORT void wxSemaphore_Delete(wxSemaphore* self)
    {
        delete self;
    }

    EXPORT int wxSemaphore_Wait(wxSemaphore* self)
    {
        return static_cast<int>(self->Wait());
    }

    EXPORT int wxSemaphore_WaitTimeout(wxSemaphore* self, int milliseconds)
    {
        return static_cast<int>(self->WaitTimeout(static_cast<unsigned long>(milliseconds)));
    }

    EXPORT int wxSemaphore_Post(wxSemaphore* self)
    {
        return static_cast<int>(self->Post());
    }

    // -----------------------------------------------------------------------
    // wxDynamicLibrary
    // -----------------------------------------------------------------------

    EXPORT wxDynamicLibrary* wxDynamicLibrary_Create()
    {
        return new wxDynamicLibrary();
    }

    EXPORT void wxDynamicLibrary_Delete(wxDynamicLibrary* self)
    {
        if (self == nullptr)
        {
            return;
        }
        ForgetLibraryName(self);
        delete self;
    }

    EXPORT int wxDynamicLibrary_Load(wxDynamicLibrary* self, wxString* name, int flags)
    {
        const bool loaded = self->Load(*name, flags);
        if (loaded)
        {
            RememberLibraryName(self, *name);
        }
        return loaded ? 1 : 0;
    }

    EXPORT void wxDynamicLibrary_Unload(wxDynamicLibrary* self)
    {
        self->Unload();
        ForgetLibraryName(self);
    }

    EXPORT int wxDynamicLibrary_IsLoaded(wxDynamicLibrary* self)
    {
        return self->IsLoaded();
    }

    EXPORT int wxDynamicLibrary_HasSymbol(wxDynamicLibrary* self, wxString* name)
    {
        return self->HasSymbol(*name);
    }

    EXPORT void* wxDynamicLibrary_GetSymbol(wxDynamicLibrary* self, wxString* name)
    {
        return self->GetSymbol(*name);
    }

    EXPORT void* wxDynamicLibrary_Detach(wxDynamicLibrary* self)
    {
        return self->Detach();
    }

    EXPORT wxString* wxDynamicLibrary_GetName(wxDynamicLibrary* self)
    {
        return new wxString(LookupLibraryName(self));
    }

    // -----------------------------------------------------------------------
    // wxMutex
    // -----------------------------------------------------------------------

    EXPORT int wxMutex_IsOk(wxMutex* self)
    {
        return self->IsOk();
    }

    EXPORT int wxMutex_LockTimeout(wxMutex* self, int milliseconds)
    {
        return static_cast<int>(self->LockTimeout(static_cast<unsigned long>(milliseconds)));
    }

    // -----------------------------------------------------------------------
    // wxCriticalSection
    // -----------------------------------------------------------------------

    EXPORT int wxCriticalSection_TryEnter(wxCriticalSection* self)
    {
        return self->TryEnter();
    }

    // -----------------------------------------------------------------------
    // wxCondition
    // -----------------------------------------------------------------------

    EXPORT int wxCondition_IsOk(wxCondition* self)
    {
        return self->IsOk();
    }

    EXPORT int wxCondition_WaitTimeout(wxCondition* self, int milliseconds)
    {
        return static_cast<int>(self->WaitTimeout(static_cast<unsigned long>(milliseconds)));
    }

    // ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
    EXPORT int wxThread_GetCPUCount()
    {
        return wxThread::GetCPUCount();
    }

    EXPORT int wxThread_GetCurrentId()
    {
        return (int) wxThread::GetCurrentId();
    }

    EXPORT int wxThread_GetMainId()
    {
        return (int) wxThread::GetMainId();
    }

    EXPORT int wxThread_IsPaused(void* pObject)
    {
        return ((wxThread*) pObject)->IsPaused();
    }

    EXPORT void wxThread_Sleep(unsigned long milliseconds)
    {
        wxThread::Sleep(milliseconds);
    }
}
