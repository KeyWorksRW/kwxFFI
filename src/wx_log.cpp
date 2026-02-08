#include "wrapper.h"
#include <wx/debug.h>
#include <wx/log.h>

extern "C"
{
    typedef void (*TLogFunc)(void*, int, void*, int);
}

class kwxLog : public wxLog
{
private:
    TLogFunc func;
    void* EiffelObject;

protected:
    virtual void DoLog(wxLogLevel level, const char* szString, time_t t)
    {
        wxString s(szString);
        func(EiffelObject, (int) level, (void*) &s, (int) t);
    }

public:
    kwxLog(void* _obj, void* _fnc) : wxLog()
    {
        func = (TLogFunc) _fnc;
        EiffelObject = _obj;
    }
};

extern "C"
{
    EXPORT void* kwxLog_Create(void* self, void* _fnc)
    {
        return (void*) new kwxLog(self, _fnc);
    }

    EXPORT void kwxLog_Delete(kwxLog* self)
    {
        delete self;
    }

    EXPORT bool kwxLog_IsEnabled(kwxLog* self)
    {
        return self->IsEnabled();
    }

    EXPORT int kwxLog_EnableLogging(kwxLog* self, bool doIt)
    {
        return (int) self->EnableLogging(doIt);
    }

    EXPORT void kwxLog_OnLog(kwxLog* self, int level, void* szString, int t)
    {
        self->OnLog((wxLogLevel) level, (const char*) szString, (time_t) t);
    }

    EXPORT void kwxLog_Flush(kwxLog* self)
    {
        self->Flush();
    }

    EXPORT int kwxLog_HasPendingMessages(kwxLog* self)
    {
        return (int) self->HasPendingMessages();
    }

    EXPORT void kwxLog_FlushActive(kwxLog* self)
    {
        self->FlushActive();
    }

    EXPORT void* kwxLog_GetActiveTarget()
    {
        return (void*) kwxLog::GetActiveTarget();
    }

    EXPORT void* kwxLog_SetActiveTarget(wxLog* pLogger)
    {
        return (void*) kwxLog::SetActiveTarget(pLogger);
    }

    EXPORT void kwxLog_Suspend(kwxLog* self)
    {
        self->Suspend();
    }

    EXPORT void kwxLog_Resume(kwxLog* self)
    {
        self->Resume();
    }

    EXPORT void kwxLog_SetVerbose(kwxLog* self, bool bVerbose)
    {
        self->SetVerbose(bVerbose);
    }

    EXPORT void kwxLog_DontCreateOnDemand(kwxLog* self)
    {
        self->DontCreateOnDemand();
    }

    EXPORT void kwxLog_AddTraceMask(kwxLog* self, void* str)
    {
        self->AddTraceMask((const char*) str);
    }

    EXPORT void kwxLog_RemoveTraceMask(kwxLog* self, void* str)
    {
        self->RemoveTraceMask((const char*) str);
    }

    EXPORT void kwxLog_SetTimestamp(kwxLog* self, void* ts)
    {
        self->SetTimestamp((const char*) ts);
    }

    EXPORT int kwxLog_GetVerbose(kwxLog* self)
    {
        return (int) self->GetVerbose();
    }

    EXPORT bool kwxLog_IsAllowedTraceMask(kwxLog* self, void* mask)
    {
        return self->IsAllowedTraceMask((const char*) mask);
    }

    EXPORT void* kwxLog_GetTimestamp(kwxLog* self)
    {
        wxString retVal = self->GetTimestamp();
        return (void*) strdup(retVal.utf8_str().data());
    }

    EXPORT int kwxSysErrorCode()
    {
        return (int) wxSysErrorCode();
    }

    EXPORT void* kwxSysErrorMsg(int nErrCode)
    {
        return (void*) wxSysErrorMsg((unsigned long) nErrCode);
    }

    EXPORT void LogErrorMsg(wxString* _msg)
    {
        wxLogError(*_msg);
    }

    EXPORT void LogFatalErrorMsg(wxString* _msg)
    {
        wxLogFatalError(*_msg);
    }

    EXPORT void LogWarningMsg(wxString* _msg)
    {
        wxLogWarning(*_msg);
    }

    EXPORT void LogMessageMsg(wxString* _msg)
    {
        wxLogMessage(*_msg);
    }

    EXPORT void* wxLogChain_Create(void* logger)
    {
        return new wxLogChain((wxLog*) logger);
    }

    EXPORT void wxLogChain_Delete(wxLogChain* self)
    {
        delete self;
    }

    EXPORT void wxLogChain_SetLog(wxLogChain* self, wxLog* logger)
    {
        self->SetLog(logger);
    }

    EXPORT void wxLogChain_PassMessages(wxLogChain* self, bool bDoPass)
    {
        self->PassMessages(bDoPass);
    }

    EXPORT bool wxLogChain_IsPassingMessages(wxLogChain* self)
    {
        return self->IsPassingMessages();
    }

    EXPORT void* wxLogChain_GetOldLog(wxLogChain* self)
    {
        return (void*) self->GetOldLog();
    }

    EXPORT void expSetDefaultAssertHandler()
    {
        ::wxSetDefaultAssertHandler();
    }
}
