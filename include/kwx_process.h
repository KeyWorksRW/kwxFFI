#pragma once

// Process wrappers: wxExecuteEnv, wxProcess, the wxProcessEx callback helper, and
// wxProcessEvent. The free functions that launch processes are declared in
// kwx_constants.h.

// ---------------------------------------------------------------------------
// wxExecuteEnv
// ---------------------------------------------------------------------------

TClassDef(wxExecuteEnv) TClass(wxExecuteEnv) wxExecuteEnv_Create();
void wxExecuteEnv_Delete(TSelf(wxExecuteEnv) pObject);
void wxExecuteEnv_SetCwd(TSelf(wxExecuteEnv) pObject, TClass(wxString) cwd);
TClass(wxString) wxExecuteEnv_GetCwd(TSelf(wxExecuteEnv) pObject);
void wxExecuteEnv_AddEnv(TSelf(wxExecuteEnv) pObject, TClass(wxString) name,
                         TClass(wxString) value);

// ---------------------------------------------------------------------------
// wxProcess
// ---------------------------------------------------------------------------

TClassDefExtend(wxProcess, wxEvtHandler) TClass(wxProcess) wxProcess_CreateFlags(int flags);
TBool wxProcess_Activate(TSelf(wxProcess) pObject);
long wxProcess_GetPid(TSelf(wxProcess) pObject);
void wxProcess_SetPriority(TSelf(wxProcess) pObject, unsigned priority);
unsigned wxProcess_GetPriority(TSelf(wxProcess) pObject);
int wxProcess_Kill(int pid, int sig, int flags, int* rc);
TBool wxProcess_Exists(int pid);
TClass(wxProcess) wxProcess_Open(TClass(wxString) cmd, int flags);
TBool wxProcess_IsInputAvailable(TSelf(wxProcess) pObject);
TBool wxProcess_IsErrorAvailable(TSelf(wxProcess) pObject);
TBool wxProcess_IsInputOpened(TSelf(wxProcess) pObject);

// ---------------------------------------------------------------------------
// wxProcessEx — callback helper derived from wxProcess
// ---------------------------------------------------------------------------

TClassDefExtend(wxProcessEx, wxProcess) TClass(wxProcessEx)
    wxProcessEx_Create(TClass(wxEvtHandler) parent, int id, int flags);
void wxProcessEx_Connect(TSelf(wxProcessEx) pObject, TClass(wxClosure) closure);
TClass(wxClosure) wxProcessEx_GetClosure(TSelf(wxProcessEx) pObject);

// ---------------------------------------------------------------------------
// wxProcessEvent
// ---------------------------------------------------------------------------

TClassDefExtend(wxProcessEvent, wxEvent) TClass(wxProcessEvent)
    wxProcessEvent_Create(int id, int pid, int exitcode);
