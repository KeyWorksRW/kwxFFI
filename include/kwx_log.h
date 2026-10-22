#pragma once

// wxLog hierarchy (Phase 13).
// kwxgen merges repeated class blocks by class name, so the blocks below extend the
// parent-only declarations in kwx_classes.h.
//
// Implementations:
//   src/kwx_extra.cpp - legacy wxLog_*, wxLogStderr_Create*, wxLogNull_Create,
//                       wxLogTextCtrl_Create, wxLogWindow_Create/GetFrame and Log* exports.
//                       They are declared here and must not be re-implemented in src/wx_log.cpp.
//   src/wx_log.cpp    - everything else declared in this header.

TClassDefExtend(wxLog, wxObject) TClass(wxLog) wxLog_Create();
void wxLog_Delete(TSelf(wxLog) pObject);
void wxLog_OnLog(TSelf(wxLog) pObject, int level, void* szString, int timestamp);
void wxLog_Flush(TSelf(wxLog) pObject);
TBool wxLog_HasPendingMessages(TSelf(wxLog) pObject);
void wxLog_FlushActive(TSelf(wxLog) pObject);
void* wxLog_GetActiveTarget();
void* wxLog_SetActiveTarget(TClass(wxLog) pLogger);
void wxLog_Suspend(TSelf(wxLog) pObject);
void wxLog_Resume(TSelf(wxLog) pObject);
void wxLog_SetVerbose(TSelf(wxLog) pObject, TBool bVerbose);
TBool wxLog_GetVerbose(TSelf(wxLog) pObject);
void wxLog_DontCreateOnDemand(TSelf(wxLog) pObject);
void wxLog_AddTraceMask(TSelf(wxLog) pObject, void* str);
void wxLog_RemoveTraceMask(TSelf(wxLog) pObject, void* str);
void wxLog_SetTimestamp(TSelf(wxLog) pObject, void* timestamp);
void* wxLog_GetTimestamp(TSelf(wxLog) pObject);
TBool wxLog_IsAllowedTraceMask(TSelf(wxLog) pObject, void* mask);
TBool wxLog_EnableLogging(TBool enable);
TBool wxLog_IsEnabled();
void wxLog_SetLogLevel(int level);
int wxLog_GetLogLevel();
int wxLog_GetComponentLevel(TClass(wxString) component);
void wxLog_SetComponentLevel(TClass(wxString) component, int level);
TBool wxLog_IsLevelEnabled(int level, TClass(wxString) component);

// The parent is already set by the wxLogChain block in kwx_classes.h; a parentless
// TClassDef block adds methods without replacing it.
TClassDef(wxLogChain) void wxLogChain_DetachOldLog(TSelf(wxLogChain) pObject);

TClassDefExtend(wxLogInterposer, wxLogChain) TClass(wxLogInterposer) wxLogInterposer_Create();
void wxLogInterposer_Delete(TSelf(wxLogInterposer) pObject);

TClassDefExtend(wxLogBuffer, wxLog) TClass(wxLogBuffer) wxLogBuffer_Create();
TClass(wxString) wxLogBuffer_GetBuffer(TSelf(wxLogBuffer) pObject);
void wxLogBuffer_Flush(TSelf(wxLogBuffer) pObject);
void wxLogBuffer_Delete(TSelf(wxLogBuffer) pObject);

TClassDefExtend(wxLogGui, wxLog) TClass(wxLogGui) wxLogGui_Create();
void wxLogGui_Flush(TSelf(wxLogGui) pObject);
void wxLogGui_Delete(TSelf(wxLogGui) pObject);

TClassDefExtend(wxLogStderr, wxLog) TClass(wxLogStderr) wxLogStderr_Create();
TClass(wxLogStderr) wxLogStderr_CreateStdOut();
void wxLogStderr_Delete(TSelf(wxLogStderr) pObject);

TClassDefExtend(wxLogNull, wxLog) TClass(wxLogNull) wxLogNull_Create();
void wxLogNull_Delete(TSelf(wxLogNull) pObject);

TClassDefExtend(wxLogTextCtrl, wxLog) TClass(wxLogTextCtrl)
    wxLogTextCtrl_Create(TClass(wxTextCtrl) text);
void wxLogTextCtrl_Delete(TSelf(wxLogTextCtrl) pObject);

TClassDefExtend(wxLogWindow, wxLogInterposer) TClass(wxLogWindow)
    wxLogWindow_Create(TClass(wxFrame) parent, TClass(wxString) title, TBool showit,
                       TBool passthrough);
TClass(wxFrame) wxLogWindow_GetFrame(TSelf(wxLogWindow) pObject);
void wxLogWindow_Delete(TSelf(wxLogWindow) pObject);

// wxLogRecordInfo is a plain struct in wx/log.h; accessors only, do not construct one.
TClassDef(wxLogRecordInfo) TClass(wxString)
    wxLogRecordInfo_GetFilename(TSelf(wxLogRecordInfo) pObject);
int wxLogRecordInfo_GetLine(TSelf(wxLogRecordInfo) pObject);
TClass(wxString) wxLogRecordInfo_GetFunc(TSelf(wxLogRecordInfo) pObject);
TClass(wxString) wxLogRecordInfo_GetComponent(TSelf(wxLogRecordInfo) pObject);
TInt64 wxLogRecordInfo_GetTimestamp(TSelf(wxLogRecordInfo) pObject);
int wxLogRecordInfo_GetLevel(TSelf(wxLogRecordInfo) pObject);
TClass(wxString) wxLogRecordInfo_GetMask(TSelf(wxLogRecordInfo) pObject);
