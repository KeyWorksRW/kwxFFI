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
TClass(kwxLocale) wxGetkwxLocale();
void* wxGetkwxTranslation(TStringVoid text);
void wxMutexGui_Enter();
void wxMutexGui_Leave();


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
