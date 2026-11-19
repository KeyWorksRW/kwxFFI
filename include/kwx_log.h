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
// ---- Phase 6: override hooks for the pair's own base ----
// The homonymous spellings the portability matrix resolves an ovh row to.  The
// receiver is the kwxLog helper object of src/wx_log.cpp.
EXPORT void wxLog_SetOnDoLogRecord(TSelf(wxLog) pObject, void* pFunction);
EXPORT void wxLog_SetOnDoLogTextAtLevel(TSelf(wxLog) pObject, void* pFunction);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
void wxLog_LogTextAtLevel(TSelf(wxLog) pObject, int level, TClass(wxString) msg);
TClass(wxLog) wxLog_SetThreadActiveTarget(void* logger);
void wxLog_Delete(TSelf(wxLog) pObject);
void wxLog_OnLog(TSelf(wxLog) pObject, int level, void* szString, int timestamp);
void wxLog_Flush(TSelf(wxLog) pObject);
TBool wxLog_HasPendingMessages(TSelf(wxLog) pObject);
void wxLog_FlushActive(TSelf(wxLog) pObject);
TClass(wxLog) wxLog_GetActiveTarget();
// Returns the previously installed target.  wxWidgets hands ownership of it to
// the caller, so the declaration is marked TClassOwned: the generated binding
// returns a wrapper whose Delete() actually frees it.
TClassOwned(wxLog) wxLog_SetActiveTarget(TClass(wxLog) pLogger);
void wxLog_Suspend(TSelf(wxLog) pObject);
void wxLog_Resume(TSelf(wxLog) pObject);
void wxLog_SetVerbose(TSelf(wxLog) pObject, TBool bVerbose);
TBool wxLog_GetVerbose(TSelf(wxLog) pObject);
void wxLog_DontCreateOnDemand(TSelf(wxLog) pObject);
void wxLog_AddTraceMask(TSelf(wxLog) pObject, TString str);
void wxLog_RemoveTraceMask(TSelf(wxLog) pObject, TString str);
void wxLog_SetTimestamp(TSelf(wxLog) pObject, TString timestamp);
void* wxLog_GetTimestamp(TSelf(wxLog) pObject);
TBool wxLog_IsAllowedTraceMask(TSelf(wxLog) pObject, TString mask);
TBool wxLog_EnableLogging(TBool enable);
TBool wxLog_IsEnabled();
void wxLog_SetLogLevel(int level);
int wxLog_GetLogLevel();
// wxLog::DisableTimestamp() is a static one-liner (SetTimestamp(wxEmptyString))
// that the samples need to keep log output identical to the C++ original.
void wxLog_DisableTimestamp();
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

// kwxLogGui is a callback-driven wxLogGui.  wxLogGui's DoShowSingleLogMessage()
// is private, so only a derived class can customize the single-message dialog
// (as MyLogGui does in the dialogs sample).  The callback receives
// (pObject, message, title); the two strings are const wxString* valid only for
// the call.  DoShowSingleLogMessage's style argument is exposed by
// kwxLogGui_GetPendingStyle() because the FFI callback ABI has only three
// pointer slots.
TClassDefExtend(kwxLogGui, wxLogGui) EXPORT TClass(kwxLogGui) kwxLogGui_Create(void* pObject);
EXPORT void kwxLogGui_SetOnDoShowSingleLogMessage(TSelf(kwxLogGui) pObject, void* pFunction);
EXPORT int kwxLogGui_GetPendingStyle(TSelf(kwxLogGui) pObject);
EXPORT void kwxLogGui_Delete(TSelf(kwxLogGui) pObject);

TClassDefExtend(wxLogStderr, wxLog) TClass(wxLogStderr) wxLogStderr_Create();
TClass(wxLogStderr) wxLogStderr_CreateStdOut();
void wxLogStderr_Delete(TSelf(wxLogStderr) pObject);

TClassDefExtend(wxLogNull, wxLog) TClass(wxLogNull) wxLogNull_Create();
void wxLogNull_Delete(TSelf(wxLogNull) pObject);

TClassDefExtend(wxLogTextCtrl, wxLog) TClass(wxLogTextCtrl)
    wxLogTextCtrl_Create(TClass(wxTextCtrl) text);
void wxLogTextCtrl_Delete(TSelf(wxLogTextCtrl) pObject);
// wxLogTextCtrl has no DisableTimestamp() of its own: wxWidgets inherits the static
// wxLog::DisableTimestamp(), so logger->DisableTimestamp() works on the text-control
// log target in C++.  The flat Julia/Lua wrappers cannot inherit it, so give every
// port the same call shape instead of forcing wxLog::SetTimestamp(wxEmptyString).
void wxLogTextCtrl_DisableTimestamp(TSelf(wxLogTextCtrl) pObject);

TClassDefExtend(wxLogWindow, wxLogInterposer) TClass(wxLogWindow)
    wxLogWindow_Create(TClass(wxFrame) parent, TClass(wxString) title, TBool showit,
                       TBool passthrough);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
void wxLogWindow_Show(TSelf(wxLogWindow) pObject, TBool bShow);
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

// Prints text to the current output, equivalent to wxPrintf("%s", text).  The C
// ABI cannot express wxPrintf's variadic arguments, so callers format the text
// before calling this function.
//
// wxPrintf(), wxCmdLineParser::Usage() and wxCmdLineParser::Parse() error
// messages all write through the process-wide wxMessageOutput.  The
// kwxMessageOutput* helpers install a heap-allocated wxMessageOutputStderr (or
// stdout) target that wxWidgets deletes during wxEntryCleanup();
// kwxMessageOutputReset() installs null and disposes of the previous target, so
// the traits default is created again on the next wxMessageOutput::Get().  A
// console application needs none of these calls: its traits already create
// wxMessageOutputBest, which writes to stderr whenever one is attached.  The
// helpers exist for a GUI-subsystem host whose default would raise a message
// box.
int wxPrintf(TClass(wxString) text);
// wxPrintf() for text whose trailing blanks are significant and whose byte count the caller
// states explicitly: exactly `len` bytes of `text` are used (the buffer need not be
// NUL-terminated) and are interpreted as UTF-8, like wxString_CreateLen().  A binding whose
// string -> wxString conversion trims padding -- a Fortran character variable is blank-padded
// -- cannot reach the space that ends a prompt through wxPrintf(); this companion takes the
// length instead.
int wxPrintfLen(TString text, int len);
void kwxMessageOutputUseStderr();
void kwxMessageOutputUseStdout();
void kwxMessageOutputReset();

// Installs a log target that writes each record to stderr exactly once and disposes
// of the target it replaces, so a GUI-subsystem host running a console-style sample
// prints one line per LogError()/LogWarning() call.  wxLogStderr is not usable there:
// when the executable has no stderr of its own (wxGUIAppTraits::HasStderr() is false
// for a GUI-subsystem program on MSW) wxLogStderr::DoLogText() writes the record a
// second time through wxMessageOutputDebug(), which on MSW also goes to stderr.  A
// console-subsystem program needs no call at all.  The installed object is owned by
// wxWidgets; do not keep a wrapper to the previous target, it is deleted here.
void kwxLogUseStderr();
