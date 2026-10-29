#pragma once

// Base-utility thread, synchronization and dynamic-library classes: wxThread (through the
// kwxThread callback helper), wxSemaphore and wxDynamicLibrary, plus the methods missing from
// the existing wxMutex, wxCriticalSection and wxCondition blocks.
//
// These classes are classified `base-utility` in `.private/coverage_expansion_inventory.md`
// and are therefore listed in `GuiExcludedClasses()` (`kwxgen/src/profile.cpp`), so the `gui`
// profile used by the Go and Julia bindings does not emit them.
//
// kwxgen merges repeated `TClassDef`/`TClassDefExtend` blocks, so the wxMutex, wxCriticalSection
// and wxCondition blocks below add methods to the blocks already in `include/kwx_classes.h`
// instead of redefining those classes.

// ---------------------------------------------------------------------------
// wxThread
// ---------------------------------------------------------------------------

// flags is the wxThreadKind value: 0 = wxTHREAD_DETACHED, 1 = wxTHREAD_JOINABLE.
//
// A detached thread deletes itself as soon as it finishes, so the object must not be touched
// after the thread terminates; a runtime that needs to wait for the result or to free the
// object must create a joinable thread instead.
//
// Start() and Run() are synonyms: wxWidgets creates the operating-system thread on the first
// Run() call, so Create() and Run() must not be separated. Both return a wxThreadError value.
// Wait() returns the value the entry callback returned, or (void*)-1 when called on a detached
// thread. The TestDestroy and OnExit callbacks are set with the SetOn* functions; see
// include/kwx_helper_thread.h.
TClassDef(wxThread) TClass(wxThread) wxThread_Create(void* pObject, void* entryFunc, int flags);
void wxThread_Delete(TSelf(wxThread) pObject);
int wxThread_Start(TSelf(wxThread) pObject);
int wxThread_Run(TSelf(wxThread) pObject);
void* wxThread_Wait(TSelf(wxThread) pObject);
int wxThread_Pause(TSelf(wxThread) pObject);
int wxThread_Resume(TSelf(wxThread) pObject);
TBool wxThread_IsAlive(TSelf(wxThread) pObject);
TBool wxThread_IsRunning(TSelf(wxThread) pObject);
TBool wxThread_TestDestroy(TSelf(wxThread) pObject);
TUInt32 wxThread_GetId(TSelf(wxThread) pObject);
void wxThread_SetPriority(TSelf(wxThread) pObject, int priority);
int wxThread_GetPriority(TSelf(wxThread) pObject);
void wxThread_SetOnTestDestroy(TSelf(wxThread) pObject, void* pFunction);
void wxThread_SetOnExit(TSelf(wxThread) pObject, void* pFunction);

// ---------------------------------------------------------------------------
// wxSemaphore
// ---------------------------------------------------------------------------

// A maxCount of 0 means the semaphore has no upper limit. WaitTimeout() takes a timeout in
// milliseconds and returns wxSEMA_TIMEOUT when it elapses; all methods return a wxSemaError
// value.
TClassDef(wxSemaphore) TClass(wxSemaphore) wxSemaphore_Create(int initial, int maxCount);
void wxSemaphore_Delete(TSelf(wxSemaphore) pObject);
int wxSemaphore_Wait(TSelf(wxSemaphore) pObject);
int wxSemaphore_WaitTimeout(TSelf(wxSemaphore) pObject, int milliseconds);
int wxSemaphore_Post(TSelf(wxSemaphore) pObject);

// ---------------------------------------------------------------------------
// wxDynamicLibrary
// ---------------------------------------------------------------------------

// flags is a combination of the wxDLFlags values. GetSymbol() returns the resolved address of
// the named symbol, or nullptr when it is not found. Detach() gives up ownership of the
// platform handle and returns it as an opaque pointer.
//
// wxDynamicLibrary has no name accessor, so GetName() returns the name most recently passed to
// Load() on this object (an empty string when the library was never loaded).
TClassDef(wxDynamicLibrary) TClass(wxDynamicLibrary) wxDynamicLibrary_Create();
void wxDynamicLibrary_Delete(TSelf(wxDynamicLibrary) pObject);
int wxDynamicLibrary_Load(TSelf(wxDynamicLibrary) pObject, TClass(wxString) name, int flags);
void wxDynamicLibrary_Unload(TSelf(wxDynamicLibrary) pObject);
TBool wxDynamicLibrary_IsLoaded(TSelf(wxDynamicLibrary) pObject);
TBool wxDynamicLibrary_HasSymbol(TSelf(wxDynamicLibrary) pObject, TClass(wxString) name);
void* wxDynamicLibrary_GetSymbol(TSelf(wxDynamicLibrary) pObject, TClass(wxString) name);
void* wxDynamicLibrary_Detach(TSelf(wxDynamicLibrary) pObject);
TClass(wxString) wxDynamicLibrary_GetName(TSelf(wxDynamicLibrary) pObject);

// ---------------------------------------------------------------------------
// wxMutex — methods missing from the block in include/kwx_classes.h
// ---------------------------------------------------------------------------

// LockTimeout() takes a timeout in milliseconds and returns wxMUTEX_TIMEOUT when it elapses.
// All methods return a wxMutexError value.
TClassDef(wxMutex) TBool wxMutex_IsOk(TSelf(wxMutex) pObject);
int wxMutex_LockTimeout(TSelf(wxMutex) pObject, int milliseconds);

// ---------------------------------------------------------------------------
// wxCriticalSection — method missing from the block in include/kwx_classes.h
// ---------------------------------------------------------------------------

// TryEnter() returns non-zero when the section was entered and the caller must then call
// wxCriticalSection_Leave().
TClassDef(wxCriticalSection) TBool wxCriticalSection_TryEnter(TSelf(wxCriticalSection) pObject);

// ---------------------------------------------------------------------------
// wxCondition — methods missing from the block in include/kwx_classes.h
// ---------------------------------------------------------------------------

// The associated mutex must be locked before Wait() and WaitTimeout(); WaitTimeout() takes a
// timeout in milliseconds and returns wxCOND_TIMEOUT when it elapses. All methods return a
// wxCondError value.
TClassDef(wxCondition) TBool wxCondition_IsOk(TSelf(wxCondition) pObject);
int wxCondition_WaitTimeout(TSelf(wxCondition) pObject, int milliseconds);
