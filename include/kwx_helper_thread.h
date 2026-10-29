#pragma once

// kwxThread — callback-based wxThread implementation.
//
// wxThread::Entry() is pure virtual and protected, so a foreign language cannot derive from
// wxThread to supply the thread body. kwxThread stores the foreign object pointer and an entry
// callback; Entry() calls that callback in the context of the new thread and returns its result
// as the wxThread exit code.
//
// TestDestroy() and OnExit() are virtual hooks as well:
//   * wxWidgets polls the TestDestroy callback while the thread runs, and a non-zero result
//     asks the thread to stop. This is also what makes Pause() and Delete() work, because the
//     base implementation never returns true unless the thread called TestDestroy() itself.
//   * the OnExit callback runs on the exiting thread before it terminates.
// Both callbacks are optional; a null callback keeps the wxWidgets default behavior.
//
// The callbacks arrive as void* from the foreign runtime and are cast to the typedefs below,
// following the same convention as include/kwx_helper_accessible.h.

#include <wx/thread.h>

// Entry callback: receives the foreign object, returns the thread exit code.
typedef void* (*kwxThreadEntryFunc)(void* pObject);

// TestDestroy callback: a non-zero result asks the thread to stop.
typedef int (*kwxThreadTestDestroyFunc)(void* pObject);

// OnExit callback: runs in the context of the exiting thread.
typedef void (*kwxThreadOnExitFunc)(void* pObject);

class kwxThread : public wxThread
{
private:
    void* m_object;
    kwxThreadEntryFunc m_entry_func;
    kwxThreadTestDestroyFunc m_test_destroy_func;
    kwxThreadOnExitFunc m_on_exit_func;

public:
    kwxThread(void* pObject, void* entryFunc, wxThreadKind kind = wxTHREAD_DETACHED);
    ~kwxThread() override = default;

    void SetOnTestDestroy(void* pFunction)
    {
        m_test_destroy_func = (kwxThreadTestDestroyFunc) pFunction;
    }
    void SetOnExit(void* pFunction) { m_on_exit_func = (kwxThreadOnExitFunc) pFunction; }

    ExitCode Entry() override;
    bool TestDestroy() override;

protected:
    void OnExit() override;
};
