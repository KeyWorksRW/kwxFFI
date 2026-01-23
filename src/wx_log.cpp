#include "wrapper.h"
#include <wx/log.h>

extern "C"
{
    typedef void (*TLogFunc)(void*, int, void*, int);
}

class ELJLog : public wxLog
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
    ELJLog(void* _obj, void* _fnc) : wxLog()
    {
        func = (TLogFunc) _fnc;
        EiffelObject = _obj;
    }
};

extern "C"
{
    EXPORT void* ELJLog_Create(void* self, void* _fnc)
    {
        return (void*) new ELJLog(self, _fnc);
    }

    EXPORT void ELJLog_Delete(ELJLog* self)
    {
        delete self;
    }

    EXPORT bool ELJLog_IsEnabled(ELJLog* self)
    {
        return self->IsEnabled();
    }

    EXPORT int ELJLog_EnableLogging(ELJLog* self, bool doIt)
    {
        return (int) self->EnableLogging(doIt);
    }

    EXPORT void ELJLog_OnLog(ELJLog* self, int level, void* szString, int t)
    {
        self->OnLog((wxLogLevel) level, (const char*) szString, (time_t) t);
    }

    EXPORT void ELJLog_Flush(ELJLog* self)
    {
        self->Flush();
    }

    EXPORT int ELJLog_HasPendingMessages(ELJLog* self)
    {
        return (int) self->HasPendingMessages();
    }

    EXPORT void ELJLog_FlushActive(ELJLog* self)
    {
        self->FlushActive();
    }

    EXPORT void* ELJLog_GetActiveTarget()
    {
        return (void*) ELJLog::GetActiveTarget();
    }

    EXPORT void* ELJLog_SetActiveTarget(wxLog* pLogger)
    {
        return (void*) ELJLog::SetActiveTarget(pLogger);
    }

    EXPORT void ELJLog_Suspend(ELJLog* self)
    {
        self->Suspend();
    }

    EXPORT void ELJLog_Resume(ELJLog* self)
    {
        self->Resume();
    }

    EXPORT void ELJLog_SetVerbose(ELJLog* self, bool bVerbose)
    {
        self->SetVerbose(bVerbose);
    }

    EXPORT void ELJLog_DontCreateOnDemand(ELJLog* self)
    {
        self->DontCreateOnDemand();
    }

    EXPORT void ELJLog_AddTraceMask(ELJLog* self, void* str)
    {
        self->AddTraceMask((const char*) str);
    }

    EXPORT void ELJLog_RemoveTraceMask(ELJLog* self, void* str)
    {
        self->RemoveTraceMask((const char*) str);
    }

    EXPORT void ELJLog_SetTimestamp(ELJLog* self, void* ts)
    {
        self->SetTimestamp((const char*) ts);
    }

    EXPORT int ELJLog_GetVerbose(ELJLog* self)
    {
        return (int) self->GetVerbose();
    }

    EXPORT bool ELJLog_IsAllowedTraceMask(ELJLog* self, void* mask)
    {
        return self->IsAllowedTraceMask((const char*) mask);
    }

    EXPORT void* ELJLog_GetTimestamp(ELJLog* self)
    {
        wxString retVal = self->GetTimestamp();
        return (void*) strdup(retVal.utf8_str().data());
    }

    EXPORT int ELJSysErrorCode()
    {
        return (int) wxSysErrorCode();
    }

    EXPORT void* ELJSysErrorMsg(int nErrCode)
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
}
