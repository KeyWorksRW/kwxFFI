#pragma once

#include "kwx_types.h"

TClass(wxAcceleratorTable) Null_AcceleratorTable();
TClass(wxBitmap) Null_Bitmap();
TClass(wxBrush) Null_Brush();
TClass(wxColour) Null_Colour();
TClass(wxCursor) Null_Cursor();
TClass(wxFont) Null_Font();
TClass(wxIcon) Null_Icon();
TClass(wxPalette) Null_Palette();
TClass(wxPen) Null_Pen();

int kwxSysErrorCode();
void* kwxSysErrorMsg(int nErrCode);
void LogErrorMsg(TClass(wxString) message);
void LogFatalErrorMsg(TClass(wxString) message);
void LogMessageMsg(TClass(wxString) message);
void LogWarningMsg(TClass(wxString) message);
void expSetDefaultAssertHandler();
TBool Quantize(TClass(wxImage) src, TClass(wxImage) dest, int desiredNoColours, void* eightBitData,
               int flags);
TBool QuantizePalette(TClass(wxImage) src, TClass(wxImage) dest, void* pPalette,
                      int desiredNoColours, void* eightBitData, int flags);
void wxCFree(void* pointer);
TClass(wxLocale) wxGetkwxLocale();
void* wxGetkwxTranslation(TStringVoid text);
void wxMutexGui_Enter();
void wxMutexGui_Leave();

// UTF-8 buffer helper — wraps a wxString's UTF-8 content for safe extraction.
// Usage: buf = kwxUtf8Buffer_Create(str); data = kwxUtf8Buffer_Data(buf);
// kwxUtf8Buffer_Delete(buf);
void* kwxUtf8Buffer_Create(TClass(wxString) str);
TString kwxUtf8Buffer_Data(void* buf);
void kwxUtf8Buffer_Delete(void* buf);

// ---------------------------------------------------------------------------
// System information
// ---------------------------------------------------------------------------

TClass(wxString) wxGetOsDescription();
int wxGetOsVersion(int* major, int* minor, int* micro);
TBool wxCheckOsVersion(int major, int minor, int micro);
TBool wxIsPlatformLittleEndian();
TBool wxIsPlatform64Bit();
TClass(wxString) wxGetCpuArchitectureName();
TClass(wxString) wxGetNativeCpuArchitectureName();
TClass(wxString) wxNow();
TClass(wxString) wxGetInstallPrefix();
TClass(wxString) wxGetDataDir();
TInt64 wxGetFreeMemory();
TBool wxHandleFatalExceptions(TBool doit);

// ---------------------------------------------------------------------------
// GUI and system helpers
// ---------------------------------------------------------------------------

TBool wxGetKeyState(int key);
TBool wxSetDetectableAutoRepeat(TBool flag);
void wxGetMousePosition(int* x, int* y);
void wxInfoMessageBox(TClass(wxWindow) parent);
void wxRegisterId(int id);
int wxGetCurrentId();
int wxNewId();
int wxHexToDec(TClass(wxString) buf);
TClass(wxString) wxDecToHex(int dec);
void wxSecureZeroMemory(void* data, unsigned count);

// ---------------------------------------------------------------------------
// Environment variables
// ---------------------------------------------------------------------------

TBool wxGetEnv(TClass(wxString) var, TClass(wxString) value);
TBool wxSetEnv(TClass(wxString) var, TClass(wxString) value);
TBool wxUnsetEnv(TClass(wxString) var);
TBool wxGetEnvMap(TClass(wxArrayString) env_map);

// ---------------------------------------------------------------------------
// User, network and disk information
// ---------------------------------------------------------------------------

TClass(wxString) wxGetEmailAddress();
TClass(wxString) wxGetHostName();
TClass(wxString) wxGetFullHostName();
TClass(wxString) wxGetUserId();
TClass(wxString) wxGetUserName();
TClass(wxString) wxGetHomeDir();
TClass(wxString) wxGetUserHome(TClass(wxString) user);
TBool wxGetDiskSpace(TClass(wxString) path, TInt64* total_bytes, TInt64* free_bytes);

// ---------------------------------------------------------------------------
// Process management
// ---------------------------------------------------------------------------

long wxExecute(TClass(wxString) command, int flags, TClass(wxProcess) process,
               TClass(wxExecuteEnv) execute_env);
long wxExecuteWithOutput(TClass(wxString) command, TClass(wxArrayString) output, int flags,
                         TClass(wxExecuteEnv) execute_env);
long wxExecuteWithOutputAndError(TClass(wxString) command, TClass(wxArrayString) output,
                                 TClass(wxArrayString) errors, int flags,
                                 TClass(wxExecuteEnv) execute_env);
long wxExecuteArgv(TArrayString(n, argv), int flags, TClass(wxProcess) process,
                   TClass(wxExecuteEnv) execute_env);
TBool wxExecuteDDE(TClass(wxString) server, TClass(wxString) topic, TClass(wxString) command);
TBool wxShutdown(int flags);
int wxKill(long pid, int sig, int* rc, int flags);
TBool wxShell(TClass(wxString) command);
TBool wxShellWithOutput(TClass(wxString) command, TClass(wxArrayString) output);
void wxSleep(int seconds);
void wxMilliSleep(unsigned long milliseconds);
void wxMicroSleep(unsigned long microseconds);
unsigned long wxGetProcessId();

// ---------------------------------------------------------------------------
// GUI helpers
// ---------------------------------------------------------------------------

TBool wxLaunchDefaultBrowser(TClass(wxString) url, int flags);
TBool wxLaunchDefaultApplication(TClass(wxString) path, int flags);
TClass(wxString) wxStripMenuCodes(TClass(wxString) text, int flags);
int wxFindMenuItemId(TClass(wxFrame) frame, TClass(wxString) menu_string,
                     TClass(wxString) item_string);
TClass(wxWindow) wxGenericFindWindowAtPoint(int x, int y);
TClass(wxWindow) wxFindWindowAtPoint(int x, int y);
TClass(wxWindow) wxFindWindowByLabel(TClass(wxString) title, TClass(wxWindow) parent);
TClass(wxWindow) wxFindWindowByName(TClass(wxString) name, TClass(wxWindow) parent);
TBool wxSafeYield(TClass(wxWindow) window, TBool only_if_needed);
void wxEnableTopLevelWindows(TBool enable);
TBool wxCheckForInterrupt(TClass(wxWindow) window);
void wxFlushEvents();
TBool wxYield();
TBool wxYieldIfNeeded();
TBool wxMSWIsOnSecureScreen();

// ---------------------------------------------------------------------------
// File selectors and stock items (wxFunctions surface)
// ---------------------------------------------------------------------------

TClass(wxString)
    wxFileSelector(TClass(wxString) message, TClass(wxString) default_path,
                   TClass(wxString) default_filename, TClass(wxString) default_extension,
                   TClass(wxString) wildcard, int flags, TClass(wxWindow) parent, int x, int y);
TClass(wxString)
    wxFileSelectorEx(TClass(wxString) message, TClass(wxString) default_path,
                     TClass(wxString) default_filename, int* index_default_extension,
                     TClass(wxString) wildcard, int flags, TClass(wxWindow) parent, int x, int y);
TClass(wxString) wxLoadFileSelector(TClass(wxString) what, TClass(wxString) extension,
                                    TClass(wxString) default_name, TClass(wxWindow) parent);
TClass(wxString) wxSaveFileSelector(TClass(wxString) what, TClass(wxString) extension,
                                    TClass(wxString) default_name, TClass(wxWindow) parent);
TBool wxIsStockID(int id);
TBool wxIsStockLabel(int id, TClass(wxString) label);
TClass(wxString) wxGetStockLabel(int id, long flags);
TClass(wxAcceleratorEntry) wxGetStockAccelerator(int id);
TClass(wxString) wxGetStockHelpString(int id, int client);

WXFFI_EXPORT(int, expRIBBON_BAR_DEFAULT_STYLE)();
WXFFI_EXPORT(int, expRIBBON_BAR_FOLDBAR_STYLE)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PAGE_LABELS)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PAGE_ICONS)();
WXFFI_EXPORT(int, expRIBBON_BAR_FLOW_HORIZONTAL)();
WXFFI_EXPORT(int, expRIBBON_BAR_FLOW_VERTICAL)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PANEL_MINIMISE_BUTTONS)();
WXFFI_EXPORT(int, expRIBBON_BAR_ALWAYS_SHOW_TABS)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_TOGGLE_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_HELP_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_PANEL_DEFAULT_STYLE)();
WXFFI_EXPORT(int, expRIBBON_PANEL_NO_AUTO_MINIMISE)();
WXFFI_EXPORT(int, expRIBBON_PANEL_EXT_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_PANEL_MINIMISE_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_PANEL_STRETCH)();
WXFFI_EXPORT(int, expRIBBON_PANEL_FLEXIBLE)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_NORMAL)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_DROPDOWN)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_HYBRID)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_TOGGLE)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTONBAR_BUTTON_SMALL)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTONBAR_BUTTON_MEDIUM)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTONBAR_BUTTON_LARGE)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_NORMAL)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_HOVERED)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_ACTIVE)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_DISABLED)();

// Legacy wxLog free functions (Phase 13); implementations live in src/kwx_extra.cpp.
void LogError(TClass(wxString) message);
void LogFatalError(TClass(wxString) message);
void LogWarning(TClass(wxString) message);
void LogMessage(TClass(wxString) message);
void LogVerbose(TClass(wxString) message);
void LogStatus(TClass(wxString) message);
void LogSysError(TClass(wxString) message);
void LogDebug(TClass(wxString) message);
void LogTrace(TClass(wxString) mask, TClass(wxString) message);
