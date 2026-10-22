#pragma once

// Declarations for implementations that previously had no declaration in include/.
// The function list is taken from .private/coverage-baseline.md (`## Undeclared exports`);
// each signature matches the EXPORT definition in the source file that implements it.
// Phase 10 (wxProcess, wxKill) and Phase 13 (wxLog hierarchy) exports are deliberately
// omitted here because those phases own them.

TClassDef(kwxHtmlEvent) TClass(wxString) kwxHtmlEvent_GetHref(TSelf(kwxHtmlEvent) pObject);
void* kwxHtmlEvent_GetHtmlCell(TSelf(kwxHtmlEvent) pObject);
TClass(wxString) kwxHtmlEvent_GetHtmlCellId(TSelf(kwxHtmlEvent) pObject);
TClass(wxPoint) kwxHtmlEvent_GetLogicalPosition(TSelf(kwxHtmlEvent) pObject);
void* kwxHtmlEvent_GetMouseEvent(TSelf(kwxHtmlEvent) pObject);
TClass(wxString) kwxHtmlEvent_GetTarget(TSelf(kwxHtmlEvent) pObject);

TClassDef(kwxHtmlWindow) TClass(kwxHtmlWindow)
    kwxHtmlWindow_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                         long style, TClass(wxString) name);

TClassDef(kwxPrintout) void* kwxPrintout_Create(void* title, void* self, void* fnBeginDocument,
                                                void* fnEndDocument, void* fnBeginPrinting,
                                                void* fnEndPrinting, void* fnPreparePrinting,
                                                void* fnPrintPage, void* fnHasPage,
                                                void* DoOnPageInfo);
void kwxPrintout_Delete(TSelf(kwxPrintout) pObject);
void* kwxPrintout_GetDC(TSelf(kwxPrintout) pObject);
void kwxPrintout_GetPageSizeMM(void* pObject, int* width, int* height);
void kwxPrintout_GetPageSizePixels(void* pObject, int* width, int* height);
void kwxPrintout_GetPPIPrinter(void* pObject, int* x, int* y);
void kwxPrintout_GetPPIScreen(void* pObject, int* x, int* y);
TClass(wxString) kwxPrintout_GetTitle(TSelf(kwxPrintout) pObject);
TBool kwxPrintout_IsPreview(TSelf(kwxPrintout) pObject);
void kwxPrintout_SetDC(TSelf(kwxPrintout) pObject, TClass(wxDC) dc);
void kwxPrintout_SetPageSizeMM(void* pObject, int width, int height);
void kwxPrintout_SetPageSizePixels(void* pObject, int width, int height);
void kwxPrintout_SetPPIPrinter(void* pObject, int x, int y);
void kwxPrintout_SetPPIScreen(void* pObject, int x, int y);

TClassDef(kwxTreeItemData) TClass(kwxTreeItemData)
    kwxTreeItemData_Create(TClass(wxClosure) closure);
TClass(wxClosure) kwxTreeItemData_GetClientClosure(TSelf(kwxTreeItemData) pObject);
void kwxTreeItemData_SetClientClosure(TSelf(kwxTreeItemData) pObject, TClass(wxClosure) closure);

TClassDef(wxAboutDialogInfo) void wxAboutDialogInfo_AddArtist(TSelf(wxAboutDialogInfo) pObject,
                                                              TClass(wxString) artist);
void wxAboutDialogInfo_AddDeveloper(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) developer);
void wxAboutDialogInfo_AddDocWriter(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) docwriter);
void wxAboutDialogInfo_AddTranslator(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) translator);
void* wxAboutDialogInfo_Create();
void wxAboutDialogInfo_Delete(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetCopyright(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetDescription(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetLicence(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetLongVersion(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetName(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetVersion(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetWebSiteDescription(TSelf(wxAboutDialogInfo) pObject);
TClass(wxString) wxAboutDialogInfo_GetWebSiteURL(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasArtists(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasDevelopers(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasDocWriters(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasIcon(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasLicence(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasTranslators(TSelf(wxAboutDialogInfo) pObject);
TBool wxAboutDialogInfo_HasWebSite(TSelf(wxAboutDialogInfo) pObject);
void wxAboutDialogInfo_SetCopyright(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) copyright);
void wxAboutDialogInfo_SetDescription(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) desc);
void wxAboutDialogInfo_SetIcon(TSelf(wxAboutDialogInfo) pObject, TClass(wxIcon) icon);
void wxAboutDialogInfo_SetLicence(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) licence);
void wxAboutDialogInfo_SetLicense(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) licence);
void wxAboutDialogInfo_SetName(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) name);
void wxAboutDialogInfo_SetVersion(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) version,
                                  TClass(wxString) longVersion);
void wxAboutDialogInfo_SetWebSite(TSelf(wxAboutDialogInfo) pObject, TClass(wxString) url,
                                  TClass(wxString) desc);

TClassDef(wxBitmap) TClass(wxBitmap) wxBitmap_CreateFromImage(TClass(wxImage) image, int depth);

TClassDef(wxClassInfo) TClass(wxClassInfo) wxClassInfo_FindClass(TClass(wxString) name);
TClass(wxString) wxClassInfo_GetBaseClassName1(TSelf(wxClassInfo) pObject);
TClass(wxString) wxClassInfo_GetBaseClassName2(TSelf(wxClassInfo) pObject);
TClass(wxString) wxClassInfo_GetClassNameEx(TSelf(wxClassInfo) pObject);
int wxClassInfo_GetSize(TSelf(wxClassInfo) pObject);
TBool wxClassInfo_IsKindOfEx(TSelf(wxClassInfo) pObject, TClass(wxClassInfo) classInfo);

TClassDef(wxClipboard) void wxClipboard_Delete(TSelf(wxClipboard) pObject);

TClassDefExtend(wxColorPickerCtrl, wxControl) TClass(wxColourPickerCtrl)
    wxColorPickerCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxColour) colour, int x, int y,
                             int width, int height, int style);
void wxColorPickerCtrl_GetColour(TSelf(wxColorPickerCtrl) pObject, TClass(wxColour) colour);
void wxColorPickerCtrl_SetColour(TSelf(wxColorPickerCtrl) pObject, TClass(wxColour) colour);

TClassDef(wxColour) TClass(wxColour) wxColour_CreateFromInt(int rgb);
TClass(wxColour) wxColour_CreateFromUnsignedInt(unsigned int rgba);
int wxColour_GetInt(TSelf(wxColour) pObject);
unsigned int wxColour_GetUnsignedInt(TSelf(wxColour) pObject);

TClassDef(wxComboCtrl) void wxComboCtrl_Copy(TSelf(wxComboCtrl) pObject);
void* wxComboCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) value, int x, int y,
                         int width, int height, long style);
void wxComboCtrl_Cut(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_Dismiss(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_EnablePopupAnimation(TSelf(wxComboCtrl) pObject, TBool enable);
int wxComboCtrl_GetCustomPaintWidth(TSelf(wxComboCtrl) pObject);
long wxComboCtrl_GetInsertionPoint(TSelf(wxComboCtrl) pObject);
long wxComboCtrl_GetLastPosition(TSelf(wxComboCtrl) pObject);
void* wxComboCtrl_GetPopupWindow(TSelf(wxComboCtrl) pObject);
int wxComboCtrl_GetPopupWindowState(TSelf(wxComboCtrl) pObject);
void* wxComboCtrl_GetTextCtrl(TSelf(wxComboCtrl) pObject);
TClass(wxString) wxComboCtrl_GetValue(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_HidePopup(TSelf(wxComboCtrl) pObject, TBool generateEvent);
TBool wxComboCtrl_IsEditable(TSelf(wxComboCtrl) pObject);
TBool wxComboCtrl_IsPopupShown(TSelf(wxComboCtrl) pObject);
TBool wxComboCtrl_IsPopupWindowState(TSelf(wxComboCtrl) pObject, int state);
void wxComboCtrl_Paste(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_Popup(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_Remove(TSelf(wxComboCtrl) pObject, long from, long toPos);
void wxComboCtrl_Replace(TSelf(wxComboCtrl) pObject, long from, long toPos, TClass(wxString) value);
void wxComboCtrl_SelectAll(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_SetButtonBitmaps(TSelf(wxComboCtrl) pObject, TClass(wxBitmapBundle) bmpNormal,
                                  TBool pushButtonBg, TClass(wxBitmapBundle) bmpPressed,
                                  TClass(wxBitmapBundle) bmpHover,
                                  TClass(wxBitmapBundle) bmpDisabled);
void wxComboCtrl_SetButtonPosition(TSelf(wxComboCtrl) pObject, int width, int height, int side,
                                   int spacingX);
void wxComboCtrl_SetCustomPaintWidth(TSelf(wxComboCtrl) pObject, int width);
void wxComboCtrl_SetInsertionPoint(TSelf(wxComboCtrl) pObject, long pos);
void wxComboCtrl_SetInsertionPointEnd(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_SetMargins(TSelf(wxComboCtrl) pObject, int left, int top);
void wxComboCtrl_SetPopupAnchor(TSelf(wxComboCtrl) pObject, int anchorSide);
void wxComboCtrl_SetPopupExtents(TSelf(wxComboCtrl) pObject, int extLeft, int extRight);
void wxComboCtrl_SetPopupMaxHeight(TSelf(wxComboCtrl) pObject, int height);
void wxComboCtrl_SetPopupMinWidth(TSelf(wxComboCtrl) pObject, int width);
void wxComboCtrl_SetSelection(TSelf(wxComboCtrl) pObject, long from, long toPos);
void wxComboCtrl_SetText(TSelf(wxComboCtrl) pObject, TClass(wxString) value);
void wxComboCtrl_SetTextCtrlStyle(TSelf(wxComboCtrl) pObject, int style);
void wxComboCtrl_SetValue(TSelf(wxComboCtrl) pObject, TClass(wxString) value);
void wxComboCtrl_ShowPopup(TSelf(wxComboCtrl) pObject);
void wxComboCtrl_Undo(TSelf(wxComboCtrl) pObject);

TClassDef(wxConfigBase) TClass(wxConfigBase) wxConfigBase_Get();
void wxConfigBase_Set(TSelf(wxConfigBase) pObject);

TClassDef(wxcPrintEvent) TBool wxcPrintEvent_GetContinue(TSelf(wxcPrintEvent) pObject);
int wxcPrintEvent_GetEndPage(TSelf(wxcPrintEvent) pObject);
int wxcPrintEvent_GetPage(TSelf(wxcPrintEvent) pObject);
TClass(wxcPrintout) wxcPrintEvent_GetPrintout(TSelf(wxcPrintEvent) pObject);
void wxcPrintEvent_SetContinue(TSelf(wxcPrintEvent) pObject, TBool cont);
void wxcPrintEvent_SetPageLimits(TSelf(wxcPrintEvent) pObject, int startPage, int endPage,
                                 int fromPage, int toPage);

TClassDef(wxcPrintout) TClass(wxcPrintout) wxcPrintout_Create(TClass(wxString) title);
void wxcPrintout_Delete(TSelf(wxcPrintout) pObject);
TClass(wxEvtHandler) wxcPrintout_GetEvtHandler(TSelf(wxcPrintout) pObject);
void wxcPrintout_SetPageLimits(TSelf(wxcPrintout) pObject, int startPage, int endPage, int fromPage,
                               int toPage);

TClassDef(wxCursor) void wxCursor_Delete(TSelf(wxCursor) pObject);

TClassDef(wxDateTime) void wxDateTime_Delete(TSelf(wxDateTime) pObject);

TClassDef(wxDC) void wxDC_GetPixel2(TSelf(wxDC) pObject, int x, int y, TClass(wxColour) col);
double wxDC_GetUserScaleX(TSelf(wxDC) pObject);
double wxDC_GetUserScaleY(TSelf(wxDC) pObject);

TClassDef(wxDisplay) void* wxDisplay_Create(unsigned int index);
void* wxDisplay_CreateFromWindow(TClass(wxWindow) win);
void wxDisplay_Delete(TSelf(wxDisplay) pObject);
void wxDisplay_GetClientArea(TSelf(wxDisplay) pObject, int* x, int* y, int* width, int* height);
int wxDisplay_GetCount();
void* wxDisplay_GetCurrentMode(TSelf(wxDisplay) pObject);
int wxDisplay_GetFromPoint(int x, int y);
int wxDisplay_GetFromWindow(TClass(wxWindow) win);
void wxDisplay_GetGeometry(TSelf(wxDisplay) pObject, int* x, int* y, int* width, int* height);
TClass(wxString) wxDisplay_GetName(TSelf(wxDisplay) pObject);
void wxDisplay_GetPPI(TSelf(wxDisplay) pObject, int* width, int* height);
double wxDisplay_GetScaleFactor(TSelf(wxDisplay) pObject);
TBool wxDisplay_IsOk(TSelf(wxDisplay) pObject);
TBool wxDisplay_IsPrimary(TSelf(wxDisplay) pObject);

TClassDef(wxDragImage) TBool
    wxDragImage_BeginDrag(TSelf(wxDragImage) pObject, int x, int y, TClass(wxWindow) window,
                          TClass(wxWindow) boundingWindow);
TBool wxDragImage_BeginDragFullScreen(TSelf(wxDragImage) pObject, int x_pos, int y_pos,
                                      TClass(wxWindow) window, TBool fullScreen,
                                      TClass(wxRect) rect);
TClass(wxDragImage) wxDragImage_Create(TClass(wxBitmap) image, int x, int y);
void wxDragImage_Delete(TSelf(wxDragImage) pObject);
TBool wxDragImage_EndDrag(TSelf(wxDragImage) pObject);
TBool wxDragImage_Hide(TSelf(wxDragImage) pObject);
TBool wxDragImage_Move(TSelf(wxDragImage) pObject, int x, int y);
TBool wxDragImage_Show(TSelf(wxDragImage) pObject);

TClassDef(wxEvent) void* wxEvent_GetCallbackUserData(TSelf(wxEvent) pObject);
void wxEvent_SetCallbackUserData(TSelf(wxEvent) pObject, TClass(wxObject) obj);

TClassDef(wxEvtHandler) void* wxEvtHandler_GetClientClosure(void* pObject);
void wxEvtHandler_SetClientClosure(void* pObject, TClass(wxClosure) closure);

TClassDef(wxFileConfig) TClass(wxFileConfig) wxFileConfig_Create(TClass(wxInputStream) inp);

TClassDef(wxFileInputStream) TClass(wxFileInputStream)
    wxFileInputStream_Create(TClass(wxString) ofileName);
void wxFileInputStream_Delete(TSelf(wxFileInputStream) pObject);
TBool wxFileInputStream_IsOk(TSelf(wxFileInputStream) pObject);

TClassDef(wxFileOutputStream) TClass(wxFileOutputStream)
    wxFileOutputStream_Create(TClass(wxString) ofileName);
void wxFileOutputStream_Delete(TSelf(wxFileOutputStream) pObject);
TBool wxFileOutputStream_IsOk(TSelf(wxFileOutputStream) pObject);

TClassDef(wxFrame) void wxFrame_Centre(TSelf(wxFrame) pObject, int orientation);
void* wxFrame_GetIcon(TSelf(wxFrame) pObject);
TClass(wxString) wxFrame_GetTitle(TSelf(wxFrame) pObject);
TBool wxFrame_Iconize(TSelf(wxFrame) pObject);
TBool wxFrame_IsFullScreen(TSelf(wxFrame) pObject);
TBool wxFrame_IsIconized(TSelf(wxFrame) pObject);
TBool wxFrame_IsMaximized(TSelf(wxFrame) pObject);
void wxFrame_Maximize(TSelf(wxFrame) pObject);
void wxFrame_SetIcon(TSelf(wxFrame) pObject, TClass(wxIcon) icon);
TBool wxFrame_SetShape(TSelf(wxFrame) pObject, TClass(wxRegion) region);
void wxFrame_SetTitle(TSelf(wxFrame) pObject, TClass(wxString) text);
TBool wxFrame_ShowFullScreen(TSelf(wxFrame) pObject, TBool show, int style);

TClassDefExtend(wxGCDC, wxDC) TClass(wxGCDC) wxGCDC_Create(TClass(wxWindowDC) dc);
TClass(wxGCDC) wxGCDC_CreateFromMemory(TClass(wxMemoryDC) dc);
TClass(wxGCDC) wxGCDC_CreateFromPrinter(TClass(wxPrinterDC) dc);
void wxGCDC_Delete(TSelf(wxGCDC) pObject);
TClass(wxGraphicsContext) wxGCDC_GetGraphicsContext(TSelf(wxGCDC) pObject);
void wxGCDC_SetGraphicsContext(TSelf(wxGCDC) pObject, TClass(wxGraphicsContext) gc);

TClassDef(wxGenericDirCtrl) TBool
    wxGenericDirCtrl_CollapsePath(TSelf(wxGenericDirCtrl) pObject, TClass(wxString) path);
void wxGenericDirCtrl_CollapseTree(TSelf(wxGenericDirCtrl) pObject);
void* wxGenericDirCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) dir, int x, int y,
                              int width, int height, long style, TClass(wxString) filter,
                              int defaultFilter);
TBool wxGenericDirCtrl_ExpandPath(TSelf(wxGenericDirCtrl) pObject, TClass(wxString) path);
TClass(wxString) wxGenericDirCtrl_GetDefaultPath(TSelf(wxGenericDirCtrl) pObject);
TClass(wxString) wxGenericDirCtrl_GetFilePath(TSelf(wxGenericDirCtrl) pObject);
void wxGenericDirCtrl_GetFilePaths(TSelf(wxGenericDirCtrl) pObject, TClass(wxArrayString) paths);
TClass(wxString) wxGenericDirCtrl_GetFilter(TSelf(wxGenericDirCtrl) pObject);
int wxGenericDirCtrl_GetFilterIndex(TSelf(wxGenericDirCtrl) pObject);
void* wxGenericDirCtrl_GetFilterListCtrl(TSelf(wxGenericDirCtrl) pObject);
TClass(wxString) wxGenericDirCtrl_GetPath(TSelf(wxGenericDirCtrl) pObject);
void wxGenericDirCtrl_GetPaths(TSelf(wxGenericDirCtrl) pObject, TClass(wxArrayString) paths);
void* wxGenericDirCtrl_GetTreeCtrl(TSelf(wxGenericDirCtrl) pObject);
void wxGenericDirCtrl_ReCreateTree(TSelf(wxGenericDirCtrl) pObject);
void wxGenericDirCtrl_SelectPath(TSelf(wxGenericDirCtrl) pObject, TClass(wxString) path,
                                 TBool select);
void wxGenericDirCtrl_SelectPaths(TSelf(wxGenericDirCtrl) pObject, TClass(wxArrayString) paths);
void wxGenericDirCtrl_SetDefaultPath(TSelf(wxGenericDirCtrl) pObject, TClass(wxString) path);
void wxGenericDirCtrl_SetFilter(TSelf(wxGenericDirCtrl) pObject, TClass(wxString) filter);
void wxGenericDirCtrl_SetFilterIndex(TSelf(wxGenericDirCtrl) pObject, int index);
void wxGenericDirCtrl_SetPath(TSelf(wxGenericDirCtrl) pObject, TClass(wxString) path);
void wxGenericDirCtrl_ShowHidden(TSelf(wxGenericDirCtrl) pObject, TBool show);
void wxGenericDirCtrl_UnselectAll(TSelf(wxGenericDirCtrl) pObject);

TClassDef(wxGenericDragImage) TClass(wxGenericDragImage)
    wxGenericDragImage_Create(TClass(wxCursor) cursor);
TBool wxGenericDragImage_DoDrawImage(TSelf(wxGenericDragImage) pObject, TClass(wxDC) dc, int x,
                                     int y);
TClass(wxRect)
    wxGenericDragImage_GetImageRect(TSelf(wxGenericDragImage) pObject, int x_pos, int y_pos);
TBool wxGenericDragImage_UpdateBackingFromWindow(TSelf(wxGenericDragImage) pObject,
                                                 TClass(wxDC) windowDC, TClass(wxMemoryDC) destDC,
                                                 int x, int y, int width, int height, int xdest,
                                                 int ydest, int destWidth, int destHeight);

TClassDef(wxGLCanvas) TClass(wxGLCanvas)
    wxGLCanvas_Create(TClass(wxWindow) parent, int windowID, int* attributes, int x, int y,
                      int width, int height, int style, TClass(wxString) title,
                      TClass(wxPalette) palette);
TBool wxGLCanvas_IsDisplaySupported(int* attributes);
TBool wxGLCanvas_IsExtensionSupported(TClass(wxString) extension);
TBool wxGLCanvas_SetColour(TSelf(wxGLCanvas) pObject, TClass(wxColour) colour);
TBool wxGLCanvas_SetCurrent(TSelf(wxGLCanvas) pObject, TClass(wxGLContext) ctxt);
TBool wxGLCanvas_SwapBuffers(TSelf(wxGLCanvas) pObject);

TClassDef(wxGLContext) TClass(wxGLContext)
    wxGLContext_Create(TClass(wxGLCanvas) win, TClass(wxGLContext) other);
TClass(wxGLContext) wxGLContext_CreateFromNull(TClass(wxGLCanvas) win);
TBool wxGLContext_SetCurrent(TSelf(wxGLContext) pObject, TClass(wxGLCanvas) win);

TClassDef(wxGraphicsBrush) TClass(wxGraphicsBrush) wxGraphicsBrush_Create();
void wxGraphicsBrush_Delete(TSelf(wxGraphicsBrush) pObject);

TClassDef(wxGraphicsContext) void wxGraphicsContext_Clip(TSelf(wxGraphicsContext) pObject,
                                                         TClass(wxRegion) region);
void wxGraphicsContext_ClipByRectangle(TSelf(wxGraphicsContext) pObject, double x, double y,
                                       double width, double height);
void wxGraphicsContext_ConcatTransform(TSelf(wxGraphicsContext) pObject,
                                       TClass(wxGraphicsMatrix) matrix);
TClass(wxGraphicsContext) wxGraphicsContext_Create(TClass(wxWindowDC) dc);
TClass(wxGraphicsMatrix) wxGraphicsContext_CreateDefaultMatrix(TSelf(wxGraphicsContext) pObject);
TClass(wxGraphicsContext) wxGraphicsContext_CreateFromMemory(TClass(wxMemoryDC) dc);
TClass(wxGraphicsContext) wxGraphicsContext_CreateFromNative(void* context);
TClass(wxGraphicsContext) wxGraphicsContext_CreateFromNativeWindow(void* window);
TClass(wxGraphicsContext) wxGraphicsContext_CreateFromPrinter(TClass(wxPrinterDC) dc);
TClass(wxGraphicsContext) wxGraphicsContext_CreateFromWindow(TClass(wxWindow) window);
TClass(wxGraphicsMatrix)
    wxGraphicsContext_CreateMatrix(TSelf(wxGraphicsContext) pObject, double a, double b, double c,
                                   double d, double tx, double ty);
TClass(wxGraphicsPath) wxGraphicsContext_CreatePath(TSelf(wxGraphicsContext) pObject);
void wxGraphicsContext_Delete(TSelf(wxGraphicsContext) pObject);
void wxGraphicsContext_DrawBitmap(TSelf(wxGraphicsContext) pObject, TClass(wxBitmap) bmp, double x,
                                  double y, double width, double height);
void wxGraphicsContext_DrawEllipse(TSelf(wxGraphicsContext) pObject, double x, double y,
                                   double width, double height);
void wxGraphicsContext_DrawIcon(TSelf(wxGraphicsContext) pObject, TClass(wxIcon) icon, double x,
                                double y, double width, double height);
void wxGraphicsContext_DrawLines(TSelf(wxGraphicsContext) pObject, size_t count, TClass(wxDouble) x,
                                 TClass(wxDouble) y, int fillStyle);
void wxGraphicsContext_DrawPath(TSelf(wxGraphicsContext) pObject, TClass(wxGraphicsPath) path,
                                int fillStyle);
void wxGraphicsContext_DrawRectangle(TSelf(wxGraphicsContext) pObject, double x, double y,
                                     double width, double height);
void wxGraphicsContext_DrawRoundedRectangle(TSelf(wxGraphicsContext) pObject, double x, double y,
                                            double width, double height, double radius);
void wxGraphicsContext_DrawText(TSelf(wxGraphicsContext) pObject, TClass(wxString) str, double x,
                                double y);
void wxGraphicsContext_DrawTextWithAngle(TSelf(wxGraphicsContext) pObject, TClass(wxString) str,
                                         double x, double y, double angle);
void wxGraphicsContext_FillPath(TSelf(wxGraphicsContext) pObject, TClass(wxGraphicsPath) path,
                                int fillStyle);
void* wxGraphicsContext_GetNativeContext(TSelf(wxGraphicsContext) pObject);
void wxGraphicsContext_GetPartialTextExtents(TSelf(wxGraphicsContext) pObject,
                                             TClass(wxString) text, double* widths, size_t count);
void wxGraphicsContext_GetTextExtent(TSelf(wxGraphicsContext) pObject, TClass(wxString) text,
                                     TClass(wxDouble) width, TClass(wxDouble) height,
                                     TClass(wxDouble) descent, TClass(wxDouble) externalLeading);
void wxGraphicsContext_PopState(TSelf(wxGraphicsContext) pObject);
void wxGraphicsContext_PushState(TSelf(wxGraphicsContext) pObject);
void wxGraphicsContext_ResetClip(TSelf(wxGraphicsContext) pObject);
void wxGraphicsContext_Rotate(TSelf(wxGraphicsContext) pObject, double angle);
void wxGraphicsContext_Scale(TSelf(wxGraphicsContext) pObject, double xScale, double yScale);
void wxGraphicsContext_SetBrush(TSelf(wxGraphicsContext) pObject, TClass(wxBrush) brush);
void wxGraphicsContext_SetFont(TSelf(wxGraphicsContext) pObject, TClass(wxFont) font,
                               TClass(wxColour) colour);
void wxGraphicsContext_SetGraphicsBrush(TSelf(wxGraphicsContext) pObject,
                                        TClass(wxGraphicsBrush) brush);
void wxGraphicsContext_SetGraphicsFont(TSelf(wxGraphicsContext) pObject,
                                       TClass(wxGraphicsFont) font);
void wxGraphicsContext_SetGraphicsPen(TSelf(wxGraphicsContext) pObject, TClass(wxGraphicsPen) pen);
void wxGraphicsContext_SetPen(TSelf(wxGraphicsContext) pObject, TClass(wxPen) pen);
void wxGraphicsContext_SetTransform(TSelf(wxGraphicsContext) pObject,
                                    TClass(wxGraphicsMatrix) matrix);
void wxGraphicsContext_StrokeLine(TSelf(wxGraphicsContext) pObject, double x1, double y1, double x2,
                                  double y2);
void wxGraphicsContext_StrokeLines(TSelf(wxGraphicsContext) pObject, size_t count,
                                   TClass(wxDouble) x, TClass(wxDouble) y, int fillStyle);
void wxGraphicsContext_StrokeLinesStartAndEnd(TSelf(wxGraphicsContext) pObject, size_t count,
                                              TClass(wxPoint2DDouble) beginPoints,
                                              TClass(wxPoint2DDouble) endPoints);
void wxGraphicsContext_StrokePath(TSelf(wxGraphicsContext) pObject, TClass(wxGraphicsPath) path);
void wxGraphicsContext_Translate(TSelf(wxGraphicsContext) pObject, double dx, double dy);

TClassDef(wxGraphicsFont) TClass(wxGraphicsFont) wxGraphicsFont_Create();
void wxGraphicsFont_Delete(TSelf(wxGraphicsFont) pObject);

TClassDef(wxGraphicsMatrix) void wxGraphicsMatrix_Concat(TSelf(wxGraphicsMatrix) pObject,
                                                         TClass(wxGraphicsMatrix) matrix);
TClass(wxGraphicsMatrix) wxGraphicsMatrix_Create();
void wxGraphicsMatrix_Delete(TSelf(wxGraphicsMatrix) pObject);
void wxGraphicsMatrix_Get(TSelf(wxGraphicsMatrix) pObject, TClass(wxDouble) a, TClass(wxDouble) b,
                          TClass(wxDouble) c, TClass(wxDouble) d, TClass(wxDouble) tx,
                          TClass(wxDouble) ty);
void* wxGraphicsMatrix_GetNativeMatrix(TSelf(wxGraphicsMatrix) pObject);
void wxGraphicsMatrix_Invert(TSelf(wxGraphicsMatrix) pObject);
TBool wxGraphicsMatrix_IsEqual(TSelf(wxGraphicsMatrix) pObject, TClass(wxGraphicsMatrix) t);
TBool wxGraphicsMatrix_IsIdentity(TSelf(wxGraphicsMatrix) pObject);
void wxGraphicsMatrix_Rotate(TSelf(wxGraphicsMatrix) pObject, double angle);
void wxGraphicsMatrix_Scale(TSelf(wxGraphicsMatrix) pObject, double xScale, double yScale);
void wxGraphicsMatrix_Set(TSelf(wxGraphicsMatrix) pObject, double a, double b, double c, double d,
                          double tx, double ty);
void wxGraphicsMatrix_TransformDistance(TSelf(wxGraphicsMatrix) pObject, TClass(wxDouble) dx,
                                        TClass(wxDouble) dy);
void wxGraphicsMatrix_TransformPoint(TSelf(wxGraphicsMatrix) pObject, TClass(wxDouble) x,
                                     TClass(wxDouble) y);
void wxGraphicsMatrix_Translate(TSelf(wxGraphicsMatrix) pObject, double dx, double dy);

TClassDef(wxGraphicsObject) TClass(wxGraphicsObject) wxGraphicsObject_Create();
void wxGraphicsObject_Delete(TSelf(wxGraphicsObject) pObject);
TClass(wxGraphicsRenderer) wxGraphicsObject_GetRenderer(TSelf(wxGraphicsObject) pObject);
TBool wxGraphicsObject_IsNull(TSelf(wxGraphicsObject) pObject);

TClassDef(wxGraphicsPath) void wxGraphicsPath_AddArc(TSelf(wxGraphicsPath) pObject, double x,
                                                     double y, double r, double startAngle,
                                                     double endAngle, TBool clockwise);
void wxGraphicsPath_AddArcToPoint(TSelf(wxGraphicsPath) pObject, double x1, double y1, double x2,
                                  double y2, double r);
void wxGraphicsPath_AddCircle(TSelf(wxGraphicsPath) pObject, double x, double y, double r);
void wxGraphicsPath_AddCurveToPoint(TSelf(wxGraphicsPath) pObject, double cx1, double cy1,
                                    double cx2, double cy2, double x, double y);
void wxGraphicsPath_AddEllipse(TSelf(wxGraphicsPath) pObject, double x, double y, double width,
                               double height);
void wxGraphicsPath_AddLineToPoint(TSelf(wxGraphicsPath) pObject, double x, double y);
void wxGraphicsPath_AddPath(TSelf(wxGraphicsPath) pObject, TClass(wxGraphicsPath) path);
void wxGraphicsPath_AddQuadCurveToPoint(TSelf(wxGraphicsPath) pObject, double cx, double cy,
                                        double x, double y);
void wxGraphicsPath_AddRectangle(TSelf(wxGraphicsPath) pObject, double x, double y, double width,
                                 double height);
void wxGraphicsPath_AddRoundedRectangle(TSelf(wxGraphicsPath) pObject, double x, double y,
                                        double width, double height, double radius);
void wxGraphicsPath_CloseSubpath(TSelf(wxGraphicsPath) pObject);
void wxGraphicsPath_Contains(TSelf(wxGraphicsPath) pObject, double x, double y, int fillStyle);
void wxGraphicsPath_Delete(TSelf(wxGraphicsPath) pObject);
void wxGraphicsPath_GetBox(TSelf(wxGraphicsPath) pObject, TClass(wxDouble) x, TClass(wxDouble) y,
                           TClass(wxDouble) width, TClass(wxDouble) height);
void wxGraphicsPath_GetCurrentPoint(TSelf(wxGraphicsPath) pObject, TClass(wxDouble) x,
                                    TClass(wxDouble) y);
void* wxGraphicsPath_GetNativePath(TSelf(wxGraphicsPath) pObject);
void wxGraphicsPath_MoveToPoint(TSelf(wxGraphicsPath) pObject, double x, double y);
void wxGraphicsPath_Transform(TSelf(wxGraphicsPath) pObject, TClass(wxGraphicsMatrix) matrix);
void wxGraphicsPath_UnGetNativePath(TSelf(wxGraphicsPath) pObject, void* nativePath);

TClassDef(wxGraphicsPen) TClass(wxGraphicsPen) wxGraphicsPen_Create();
void wxGraphicsPen_Delete(TSelf(wxGraphicsPen) pObject);

TClassDef(wxGraphicsRenderer) TClass(wxGraphicsRenderer) wxGraphicsRenderer_Create();
TClass(wxGraphicsContext)
    wxGraphicsRenderer_CreateContext(TSelf(wxGraphicsRenderer) pObject, TClass(wxWindowDC) dc);
TClass(wxGraphicsContext)
    wxGraphicsRenderer_CreateContextFromWindow(TSelf(wxGraphicsRenderer) pObject,
                                               TClass(wxWindow) window);
TClass(wxGraphicsContext)
    wxGraphicsRenderer_CreateContextFromNativeContext(TSelf(wxGraphicsRenderer) pObject,
                                                      void* context);
TClass(wxGraphicsContext)
    wxGraphicsRenderer_CreateContextFromNativeWindow(TSelf(wxGraphicsRenderer) pObject,
                                                     void* window);
TClass(wxGraphicsPath) wxGraphicsRenderer_CreatePath(TSelf(wxGraphicsRenderer) pObject);
void wxGraphicsRenderer_Delete(TSelf(wxGraphicsRenderer) pObject);
TClass(wxGraphicsRenderer) wxGraphicsRenderer_GetDefaultRenderer(TSelf(wxGraphicsRenderer) pObject);

TClassDef(wxGridCellTextEnterEditor) TClass(wxGridCellTextEnterEditor)
    wxGridCellTextEnterEditor_Ctor();

TClassDef(wxHeaderColumnSimple) void* wxHeaderColumnSimple_Create(TClass(wxString) title, int width,
                                                                  int align, int flags);
void* wxHeaderColumnSimple_CreateWithBitmap(TClass(wxBitmapBundle) bitmap, int width, int align,
                                            int flags);
void wxHeaderColumnSimple_Delete(TSelf(wxHeaderColumnSimple) pObject);
int wxHeaderColumnSimple_GetAlignment(TSelf(wxHeaderColumnSimple) pObject);
int wxHeaderColumnSimple_GetFlags(TSelf(wxHeaderColumnSimple) pObject);
int wxHeaderColumnSimple_GetMinWidth(TSelf(wxHeaderColumnSimple) pObject);
TClass(wxString) wxHeaderColumnSimple_GetTitle(TSelf(wxHeaderColumnSimple) pObject);
int wxHeaderColumnSimple_GetWidth(TSelf(wxHeaderColumnSimple) pObject);
TBool wxHeaderColumnSimple_IsSortKey(TSelf(wxHeaderColumnSimple) pObject);
TBool wxHeaderColumnSimple_IsSortOrderAscending(TSelf(wxHeaderColumnSimple) pObject);
void wxHeaderColumnSimple_SetAlignment(TSelf(wxHeaderColumnSimple) pObject, int align);
void wxHeaderColumnSimple_SetBitmap(TSelf(wxHeaderColumnSimple) pObject,
                                    TClass(wxBitmapBundle) bitmap);
void wxHeaderColumnSimple_SetFlags(TSelf(wxHeaderColumnSimple) pObject, int flags);
void wxHeaderColumnSimple_SetMinWidth(TSelf(wxHeaderColumnSimple) pObject, int minWidth);
void wxHeaderColumnSimple_SetSortOrder(TSelf(wxHeaderColumnSimple) pObject, TBool ascending);
void wxHeaderColumnSimple_SetTitle(TSelf(wxHeaderColumnSimple) pObject, TClass(wxString) title);
void wxHeaderColumnSimple_SetWidth(TSelf(wxHeaderColumnSimple) pObject, int width);

TClassDef(wxHeaderCtrl) unsigned int wxHeaderCtrl_GetColumnAt(TSelf(wxHeaderCtrl) pObject,
                                                              unsigned int pos);
unsigned int wxHeaderCtrl_GetColumnCount(TSelf(wxHeaderCtrl) pObject);
unsigned int wxHeaderCtrl_GetColumnPos(TSelf(wxHeaderCtrl) pObject, unsigned int idx);
TBool wxHeaderCtrl_IsEmpty(TSelf(wxHeaderCtrl) pObject);
void wxHeaderCtrl_MoveColumnInOrderArray(TSelf(wxHeaderCtrl) pObject, unsigned int idx,
                                         unsigned int pos);
void wxHeaderCtrl_ResetColumnsOrder(TSelf(wxHeaderCtrl) pObject);
void wxHeaderCtrl_SetColumnCount(TSelf(wxHeaderCtrl) pObject, unsigned int count);
void wxHeaderCtrl_UpdateColumn(TSelf(wxHeaderCtrl) pObject, unsigned int idx);

TClassDef(wxHeaderCtrlSimple) void wxHeaderCtrlSimple_AppendColumn(TSelf(wxHeaderCtrlSimple)
                                                                       pObject,
                                                                   TClass(wxHeaderColumnSimple)
                                                                       col);
void* wxHeaderCtrlSimple_Create(TClass(wxWindow) parent, int id, int x, int y, int width,
                                int height, long style);
void wxHeaderCtrlSimple_DeleteColumn(TSelf(wxHeaderCtrlSimple) pObject, unsigned int idx);
void wxHeaderCtrlSimple_HideColumn(TSelf(wxHeaderCtrlSimple) pObject, unsigned int idx);
void wxHeaderCtrlSimple_InsertColumn(TSelf(wxHeaderCtrlSimple) pObject,
                                     TClass(wxHeaderColumnSimple) col, unsigned int idx);
void wxHeaderCtrlSimple_RemoveSortIndicator(TSelf(wxHeaderCtrlSimple) pObject);
void wxHeaderCtrlSimple_ShowColumn(TSelf(wxHeaderCtrlSimple) pObject, unsigned int idx, TBool show);
void wxHeaderCtrlSimple_ShowSortIndicator(TSelf(wxHeaderCtrlSimple) pObject, unsigned int idx,
                                          TBool ascending);

TClassDef(wxHScrolledWindow) TBool
    wxHScrolledWindow_Create(TSelf(wxHScrolledWindow) pObject, TClass(wxWindow) parent, int id,
                             int x, int y, int width, int height, long style,
                             TClass(wxString) name);
size_t wxHScrolledWindow_GetColumnCount(TSelf(wxHScrolledWindow) pObject);
size_t wxHScrolledWindow_GetVisibleColumnsBegin(TSelf(wxHScrolledWindow) pObject);
size_t wxHScrolledWindow_GetVisibleColumnsEnd(TSelf(wxHScrolledWindow) pObject);
TBool wxHScrolledWindow_IsColumnVisible(TSelf(wxHScrolledWindow) pObject, size_t column);
void wxHScrolledWindow_RefreshColumn(TSelf(wxHScrolledWindow) pObject, size_t column);
void wxHScrolledWindow_RefreshColumns(TSelf(wxHScrolledWindow) pObject, size_t from, size_t toPos);
TBool wxHScrolledWindow_ScrollColumnPages(TSelf(wxHScrolledWindow) pObject, int pages);
TBool wxHScrolledWindow_ScrollColumns(TSelf(wxHScrolledWindow) pObject, int columns);
TBool wxHScrolledWindow_ScrollToColumn(TSelf(wxHScrolledWindow) pObject, size_t column);
void wxHScrolledWindow_SetColumnCount(TSelf(wxHScrolledWindow) pObject, size_t columnCount);

TClassDef(wxHtmlWindow) TBool
    wxHtmlWindow_AppendToPage(TSelf(wxHtmlWindow) pObject, TClass(wxString) source);
TClass(wxHtmlWindow) wxHtmlWindow_Create(TClass(wxWindow) parent, int id, int x, int y, int width,
                                         int height, long style, TClass(wxString) name);
void* wxHtmlWindow_GetInternalRepresentation(TSelf(wxHtmlWindow) pObject);
TClass(wxString) wxHtmlWindow_GetOpenedAnchor(TSelf(wxHtmlWindow) pObject);
TClass(wxString) wxHtmlWindow_GetOpenedPage(TSelf(wxHtmlWindow) pObject);
TClass(wxString) wxHtmlWindow_GetOpenedPageTitle(TSelf(wxHtmlWindow) pObject);
void* wxHtmlWindow_GetRelatedFrame(TSelf(wxHtmlWindow) pObject);
TBool wxHtmlWindow_HistoryBack(TSelf(wxHtmlWindow) pObject);
TBool wxHtmlWindow_HistoryCanBack(TSelf(wxHtmlWindow) pObject);
TBool wxHtmlWindow_HistoryCanForward(TSelf(wxHtmlWindow) pObject);
void wxHtmlWindow_HistoryClear(TSelf(wxHtmlWindow) pObject);
TBool wxHtmlWindow_HistoryForward(TSelf(wxHtmlWindow) pObject);
TBool wxHtmlWindow_LoadPage(TSelf(wxHtmlWindow) pObject, TClass(wxString) location);
void wxHtmlWindow_ReadCustomization(TSelf(wxHtmlWindow) pObject, TClass(wxConfigBase) cfg,
                                    TClass(wxString) path);
void wxHtmlWindow_SetBorders(TSelf(wxHtmlWindow) pObject, int borders);
void wxHtmlWindow_SetFonts(TSelf(wxHtmlWindow) pObject, TClass(wxString) normal_face,
                           TClass(wxString) fixed_face, int* sizes);
int wxHtmlWindow_SetPage(TSelf(wxHtmlWindow) pObject, TClass(wxString) source);
void wxHtmlWindow_SetRelatedFrame(TSelf(wxHtmlWindow) pObject, TClass(wxFrame) frame,
                                  TClass(wxString) format);
void wxHtmlWindow_SetRelatedStatusBar(TSelf(wxHtmlWindow) pObject, int bar);
void wxHtmlWindow_WriteCustomization(TSelf(wxHtmlWindow) pObject, TClass(wxConfigBase) cfg,
                                     TClass(wxString) path);

TClassDef(wxHVScrolledWindow) TBool
    wxHVScrolledWindow_Create(TSelf(wxHVScrolledWindow) pObject, TClass(wxWindow) parent, int id,
                              int x, int y, int width, int height, long style,
                              TClass(wxString) name);
void wxHVScrolledWindow_RefreshRowColumn(TSelf(wxHVScrolledWindow) pObject, size_t row,
                                         size_t column);
void wxHVScrolledWindow_RefreshRowsColumns(TSelf(wxHVScrolledWindow) pObject, size_t fromRow,
                                           size_t toRow, size_t fromCol, size_t toCol);
TBool wxHVScrolledWindow_ScrollToRowColumn(TSelf(wxHVScrolledWindow) pObject, size_t row,
                                           size_t column);

TClassDef(wxHyperlinkCtrl) TClass(wxHyperlinkCtrl)
    wxHyperlinkCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) label,
                           TClass(wxString) url, int x, int y, int width, int height, int style);
TClass(wxColour) wxHyperlinkCtrl_GetHoverColour(TSelf(wxHyperlinkCtrl) pObject);
TClass(wxColour) wxHyperlinkCtrl_GetNormalColour(TSelf(wxHyperlinkCtrl) pObject);
TClass(wxString) wxHyperlinkCtrl_GetURL(TSelf(wxHyperlinkCtrl) pObject);
TBool wxHyperlinkCtrl_GetVisited(TSelf(wxHyperlinkCtrl) pObject);
TClass(wxColour) wxHyperlinkCtrl_GetVisitedColour(TSelf(wxHyperlinkCtrl) pObject);
void wxHyperlinkCtrl_SetHoverColour(TSelf(wxHyperlinkCtrl) pObject, TClass(wxColour) colour);
void wxHyperlinkCtrl_SetNormalColour(TSelf(wxHyperlinkCtrl) pObject, TClass(wxColour) colour);
void wxHyperlinkCtrl_SetURL(TSelf(wxHyperlinkCtrl) pObject, TClass(wxString) url);
void wxHyperlinkCtrl_SetVisited(TSelf(wxHyperlinkCtrl) pObject, TBool visited);
void wxHyperlinkCtrl_SetVisitedColour(TSelf(wxHyperlinkCtrl) pObject, TClass(wxColour) colour);

TClassDef(wxImage) TClass(wxImage)
    wxImage_CreateFromDataEx(int width, int height, TClass(wxUint8) data, TBool isStaticData);
void wxImage_Delete(TSelf(wxImage) pObject);

TClassDef(wxInputSink) TClass(wxInputSink)
    wxInputSink_Create(TClass(wxInputStream) input, TClass(wxEvtHandler) evtHandler, int bufferLen);
int wxInputSink_GetId(TSelf(wxInputSink) pObject);
void wxInputSink_Start(TSelf(wxInputSink) pObject);

TClassDef(wxInputSinkEvent) int wxInputSinkEvent_LastError(TSelf(wxInputSinkEvent) pObject);
TString wxInputSinkEvent_LastInput(TSelf(wxInputSinkEvent) pObject);
int wxInputSinkEvent_LastRead(TSelf(wxInputSinkEvent) pObject);

TClassDef(wxInputStream) TBool wxInputStream_CanRead(TSelf(wxInputStream) pObject);

TClassDef(wxIPaddress) TBool wxIPaddress_AnyAddress(TSelf(wxIPaddress) pObject);
TClass(wxString) wxIPaddress_Hostname(TSelf(wxIPaddress) pObject);
TBool wxIPaddress_HostnameSet(TSelf(wxIPaddress) pObject, TClass(wxString) hostname);
TClass(wxString) wxIPaddress_IPAddress(TSelf(wxIPaddress) pObject);
TBool wxIPaddress_IsLocalHost(TSelf(wxIPaddress) pObject);
TBool wxIPaddress_LocalHost(TSelf(wxIPaddress) pObject);
unsigned short wxIPaddress_Service(TSelf(wxIPaddress) pObject);
TBool wxIPaddress_ServiceSet(TSelf(wxIPaddress) pObject, TClass(wxString) service);
TBool wxIPaddress_ServiceSetPort(TSelf(wxIPaddress) pObject, unsigned short service);

TClassDef(wxIPV4address) TClass(wxIPV4address) wxIPV4address_Create();
void wxIPV4address_Delete(TSelf(wxIPV4address) pObject);

TClassDef(wxListCtrl) void wxListCtrl_AssignImageList(TSelf(wxListCtrl) pObject,
                                                      TClass(wxImageList) images, int which);
void wxListCtrl_GetColumn2(TSelf(wxListCtrl) pObject, int col, TClass(wxListItem) item);
void wxListCtrl_GetItem2(TSelf(wxListCtrl) pObject, TClass(wxListItem) info);
TClass(wxPoint) wxListCtrl_GetItemPosition2(TSelf(wxListCtrl) pObject, int item);
void wxListCtrl_RefreshItems(TSelf(wxListCtrl) pObject, long from, long toPos);
TBool wxListCtrl_SortItems2(TSelf(wxListCtrl) pObject, TClass(wxClosure) closure);

TClassDef(wxListEvent) int wxListEvent_GetCacheFrom(TSelf(wxListEvent) pObject);
int wxListEvent_GetCacheTo(TSelf(wxListEvent) pObject);

TClassDef(wxMediaCtrl) TClass(wxMediaCtrl)
    wxMediaCtrl_Create(void* parent, int id, TClass(wxString) fileName, int x, int y, int width,
                       int height, long style, TClass(wxString) szBackend, TClass(wxString) name);
void wxMediaCtrl_Delete(TSelf(wxMediaCtrl) pObject);
TClass(wxSize) wxMediaCtrl_GetBestSize(TSelf(wxMediaCtrl) pObject);
double wxMediaCtrl_GetPlaybackRate(TSelf(wxMediaCtrl) pObject);
int wxMediaCtrl_GetState(TSelf(wxMediaCtrl) pObject);
double wxMediaCtrl_GetVolume(TSelf(wxMediaCtrl) pObject);
TInt64 wxMediaCtrl_Length(TSelf(wxMediaCtrl) pObject);
TBool wxMediaCtrl_Load(TSelf(wxMediaCtrl) pObject, TClass(wxString) fileName);
TBool wxMediaCtrl_LoadURI(TSelf(wxMediaCtrl) pObject, TClass(wxString) uri);
TBool wxMediaCtrl_LoadURIWithProxy(TSelf(wxMediaCtrl) pObject, TClass(wxString) uri,
                                   TClass(wxString) proxy);
TBool wxMediaCtrl_Pause(TSelf(wxMediaCtrl) pObject);
TBool wxMediaCtrl_Play(TSelf(wxMediaCtrl) pObject);
TInt64 wxMediaCtrl_Seek(TSelf(wxMediaCtrl) pObject, TInt64 offsetWhere, int mode);
TBool wxMediaCtrl_SetPlaybackRate(TSelf(wxMediaCtrl) pObject, double dRate);
TBool wxMediaCtrl_SetVolume(TSelf(wxMediaCtrl) pObject, double dVolume);
TBool wxMediaCtrl_ShowPlayerControls(TSelf(wxMediaCtrl) pObject, int flags);
TBool wxMediaCtrl_Stop(TSelf(wxMediaCtrl) pObject);
TInt64 wxMediaCtrl_Tell(TSelf(wxMediaCtrl) pObject);

TClassDef(wxMemoryInputStream) TClass(wxMemoryInputStream)
    wxMemoryInputStream_Create(void* data, int len);
void wxMemoryInputStream_Delete(TSelf(wxMemoryInputStream) pObject);

TClassDef(wxMenu) TClass(wxMenuBar) wxMenu_GetMenuBar(TSelf(wxMenu) pObject);

TClassDef(wxMenuBar) TClass(wxFrame) wxMenuBar_GetFrame(TSelf(wxMenuBar) pObject);

TClassDef(wxMenuItem) TClass(wxMenuItem)
    wxMenuItem_CreateEx(int id, TClass(wxString) text, TClass(wxString) helpstr, int itemkind,
                        TClass(wxMenu) submenu);
TClass(wxMenuItem) wxMenuItem_CreateSeparator();

TClassDef(wxMouseEvent) int wxMouseEvent_GetButton(TSelf(wxMouseEvent) pObject);
int wxMouseEvent_GetWheelDelta(TSelf(wxMouseEvent) pObject);
int wxMouseEvent_GetWheelRotation(TSelf(wxMouseEvent) pObject);

TClassDef(wxNotebook) void wxNotebook_AssignImageList(TSelf(wxNotebook) pObject,
                                                      TClass(wxImageList) imageList);

TClassDef(wxNotificationMessage) TBool
    wxNotificationMessage_AddAction(TSelf(wxNotificationMessage) pObject, int actionid,
                                    TClass(wxString) label);
TBool wxNotificationMessage_Close(TSelf(wxNotificationMessage) pObject);
void* wxNotificationMessage_Create(TClass(wxString) title, TClass(wxString) message,
                                   TClass(wxWindow) parent, int flags);
void wxNotificationMessage_Delete(TSelf(wxNotificationMessage) pObject);
TBool wxNotificationMessage_MSWUseToasts(TClass(wxString) shortcutPath, TClass(wxString) appId);
void wxNotificationMessage_SetFlags(TSelf(wxNotificationMessage) pObject, int flags);
void wxNotificationMessage_SetIcon(TSelf(wxNotificationMessage) pObject, TClass(wxIcon) icon);
void wxNotificationMessage_SetMessage(TSelf(wxNotificationMessage) pObject,
                                      TClass(wxString) message);
void wxNotificationMessage_SetParent(TSelf(wxNotificationMessage) pObject, TClass(wxWindow) parent);
void wxNotificationMessage_SetTitle(TSelf(wxNotificationMessage) pObject, TClass(wxString) title);
TBool wxNotificationMessage_Show(TSelf(wxNotificationMessage) pObject, int timeout);
TBool wxNotificationMessage_UseTaskBarIcon(TClass(wxTaskBarIcon) icon);

TClassDef(wxObject) void wxObject_Delete(TSelf(wxObject) pObject);
TClass(wxClassInfo) wxObject_GetClassInfo(TSelf(wxObject) pObject);
TClass(wxClosure) wxObject_GetClientClosure(TSelf(wxObject) pObject);
TBool wxObject_IsKindOf(TSelf(wxObject) pObject, TClass(wxClassInfo) classInfo);
TBool wxObject_IsScrolledWindow(TSelf(wxObject) pObject);
void wxObject_SetClientClosure(TSelf(wxObject) pObject, TClass(wxClosure) closure);

TClassDef(wxOwnerDrawnComboBox) int wxOwnerDrawnComboBox_Append(TSelf(wxOwnerDrawnComboBox) pObject,
                                                                TClass(wxString) item);
int wxOwnerDrawnComboBox_AppendWithClientData(TSelf(wxOwnerDrawnComboBox) pObject,
                                              TClass(wxString) item, void* clientData);
void wxOwnerDrawnComboBox_Clear(TSelf(wxOwnerDrawnComboBox) pObject);
void* wxOwnerDrawnComboBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) value, int x,
                                  int y, int width, int height, long style);
void* wxOwnerDrawnComboBox_CreateWithChoices(TClass(wxWindow) parent, int id,
                                             TClass(wxString) value, int x, int y, int width,
                                             int height, int count, TClass(wxString) * choices,
                                             long style);
void wxOwnerDrawnComboBox_Delete(TSelf(wxOwnerDrawnComboBox) pObject, unsigned int index);
int wxOwnerDrawnComboBox_FindString(TSelf(wxOwnerDrawnComboBox) pObject, TClass(wxString) str,
                                    TBool caseSensitive);
void* wxOwnerDrawnComboBox_GetClientData(TSelf(wxOwnerDrawnComboBox) pObject, unsigned int index);
unsigned int wxOwnerDrawnComboBox_GetCount(TSelf(wxOwnerDrawnComboBox) pObject);
int wxOwnerDrawnComboBox_GetSelection(TSelf(wxOwnerDrawnComboBox) pObject);
TClass(wxString)
    wxOwnerDrawnComboBox_GetString(TSelf(wxOwnerDrawnComboBox) pObject, unsigned int index);
TClass(wxString) wxOwnerDrawnComboBox_GetStringSelection(TSelf(wxOwnerDrawnComboBox) pObject);
int wxOwnerDrawnComboBox_Insert(TSelf(wxOwnerDrawnComboBox) pObject, TClass(wxString) item,
                                unsigned int pos);
int wxOwnerDrawnComboBox_InsertWithClientData(TSelf(wxOwnerDrawnComboBox) pObject,
                                              TClass(wxString) item, unsigned int pos,
                                              void* clientData);
TBool wxOwnerDrawnComboBox_IsListEmpty(TSelf(wxOwnerDrawnComboBox) pObject);
TBool wxOwnerDrawnComboBox_IsTextEmpty(TSelf(wxOwnerDrawnComboBox) pObject);
void wxOwnerDrawnComboBox_SetClientData(TSelf(wxOwnerDrawnComboBox) pObject, unsigned int index,
                                        void* data);
void wxOwnerDrawnComboBox_SetSelection(TSelf(wxOwnerDrawnComboBox) pObject, int index);
void wxOwnerDrawnComboBox_SetString(TSelf(wxOwnerDrawnComboBox) pObject, unsigned int index,
                                    TClass(wxString) str);
void wxOwnerDrawnComboBox_SetStringSelection(TSelf(wxOwnerDrawnComboBox) pObject,
                                             TClass(wxString) str);

TClassDef(wxPanel) void* wxPanel_GetDefaultItem(void* pObject);
void wxPanel_SetDefaultItem(void* pObject, void* btn);

TClassDef(wxPopupTransientWindow) void* wxPopupTransientWindow_Create(TClass(wxWindow) parent,
                                                                      int flags);
void wxPopupTransientWindow_Dismiss(TSelf(wxPopupTransientWindow) pObject);
void wxPopupTransientWindow_Popup(TSelf(wxPopupTransientWindow) pObject, TClass(wxWindow) focus);

TClassDef(wxPopupWindow) void* wxPopupWindow_Create(TClass(wxWindow) parent, int flags);
TBool wxPopupWindow_Create2(TSelf(wxPopupWindow) pObject, TClass(wxWindow) parent, int flags);
void wxPopupWindow_Position(TSelf(wxPopupWindow) pObject, int ptOriginX, int ptOriginY, int sizeW,
                            int sizeH);

TClassDef(wxPreviewFrame) TClass(wxPreviewFrame)
    wxPreviewFrame_Create(TClass(wxPrintPreview) preview, TClass(wxFrame) parent,
                          TClass(wxString) title, int x, int y, int width, int height, int style,
                          TClass(wxString) name);
void wxPreviewFrame_Delete(TSelf(wxPreviewFrame) pObject);
void wxPreviewFrame_Initialize(TSelf(wxPreviewFrame) pObject);

TClassDef(wxPrintout) void* wxPrintout_GetDC(void* pObject);
void wxPrintout_GetPageSizeMM(void* pObject, int* width, int* height);
void wxPrintout_GetPageSizePixels(void* pObject, int* width, int* height);
void wxPrintout_GetPPIPrinter(void* pObject, int* x, int* y);
void wxPrintout_GetPPIScreen(void* pObject, int* x, int* y);
TClass(wxString) wxPrintout_GetTitle(void* pObject);
TBool wxPrintout_IsPreview(TSelf(wxPrintout) pObject);
void wxPrintout_SetDC(void* pObject, void* dc);
void wxPrintout_SetPageSizeMM(void* pObject, int width, int height);
void wxPrintout_SetPageSizePixels(void* pObject, int width, int height);
void wxPrintout_SetPPIPrinter(void* pObject, int x, int y);
void wxPrintout_SetPPIScreen(void* pObject, int x, int y);

TClassDef(wxProgressDialog) TClass(wxProgressDialog)
    wxProgressDialog_Create(TClass(wxString) title, TClass(wxString) message, int max,
                            TClass(wxWindow) parent, int style);
void wxProgressDialog_Resume(TSelf(wxProgressDialog) pObject);
TBool wxProgressDialog_Update(TSelf(wxProgressDialog) pObject, int value);
TBool wxProgressDialog_UpdateWithMessage(TSelf(wxProgressDialog) pObject, int value,
                                         TClass(wxString) message);

TClassDef(wxRect) void* wxRect_Create(int x, int y, int width, int height);
void wxRect_Delete(void* pObject);
int wxRect_GetHeight(TSelf(wxRect) pObject);
int wxRect_GetWidth(TSelf(wxRect) pObject);
int wxRect_GetX(TSelf(wxRect) pObject);
int wxRect_GetY(TSelf(wxRect) pObject);
void wxRect_SetHeight(TSelf(wxRect) pObject, int height);
void wxRect_SetWidth(TSelf(wxRect) pObject, int width);
void wxRect_SetX(TSelf(wxRect) pObject, int x);
void wxRect_SetY(TSelf(wxRect) pObject, int y);

TClassDef(wxScrolledWindow) void wxScrolledWindow_SetScrollRate(TSelf(wxScrolledWindow) pObject,
                                                                int xstep, int ystep);

TClassDef(wxSockAddress) void wxSockAddress_Clear(TSelf(wxSockAddress) pObject);
void wxSockAddress_Delete(TSelf(wxSockAddress) pObject);

TClassDef(wxSocketBase) void wxSocketBase_Close(TSelf(wxSocketBase) pObject);
void wxSocketBase_Delete(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_Destroy(TSelf(wxSocketBase) pObject);
TClass(wxSocketBase) wxSocketBase_Discard(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_Error(TSelf(wxSocketBase) pObject);
void* wxSocketBase_GetClientData(TSelf(wxSocketBase) pObject);
int wxSocketBase_GetFlags(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_GetLocal(TSelf(wxSocketBase) pObject, TClass(wxSockAddress) addr);
TBool wxSocketBase_GetPeer(TSelf(wxSocketBase) pObject, TClass(wxSockAddress) addr);
void wxSocketBase_InterruptWait(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_IsConnected(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_IsData(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_IsDisconnected(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_IsOk(TSelf(wxSocketBase) pObject);
TUInt32 wxSocketBase_LastCount(TSelf(wxSocketBase) pObject);
int wxSocketBase_LastError(TSelf(wxSocketBase) pObject);
void wxSocketBase_Notify(TSelf(wxSocketBase) pObject, TBool notify);
TClass(wxSocketBase) wxSocketBase_Peek(TSelf(wxSocketBase) pObject, void* buffer, TUInt32 nbytes);
TClass(wxSocketBase) wxSocketBase_Read(TSelf(wxSocketBase) pObject, void* buffer, TUInt32 nbytes);
TClass(wxSocketBase)
    wxSocketBase_ReadMsg(TSelf(wxSocketBase) pObject, void* buffer, TUInt32 nbytes);
void wxSocketBase_RestoreState(TSelf(wxSocketBase) pObject);
void wxSocketBase_SaveState(TSelf(wxSocketBase) pObject);
void wxSocketBase_SetClientData(TSelf(wxSocketBase) pObject, void* data);
void wxSocketBase_SetEventHandler(TSelf(wxSocketBase) pObject, TClass(wxEvtHandler) handler,
                                  int id);
void wxSocketBase_SetFlags(TSelf(wxSocketBase) pObject, int flags);
TBool wxSocketBase_SetLocal(TSelf(wxSocketBase) pObject, TClass(wxIPV4address) local);
void wxSocketBase_SetNotify(TSelf(wxSocketBase) pObject, int flags);
void wxSocketBase_SetTimeout(TSelf(wxSocketBase) pObject, int seconds);
TClass(wxSocketBase) wxSocketBase_Unread(TSelf(wxSocketBase) pObject, void* buffer, TUInt32 nbytes);
TBool wxSocketBase_Wait(TSelf(wxSocketBase) pObject, long seconds, long millisecond);
TBool wxSocketBase_WaitForLost(TSelf(wxSocketBase) pObject, long seconds, long millisecond);
TBool wxSocketBase_WaitForRead(TSelf(wxSocketBase) pObject, long seconds, long millisecond);
TBool wxSocketBase_WaitForWrite(TSelf(wxSocketBase) pObject, long seconds, long millisecond);
TClass(wxSocketBase) wxSocketBase_Write(TSelf(wxSocketBase) pObject, void* buffer, TUInt32 nbytes);
TClass(wxSocketBase)
    wxSocketBase_WriteMsg(TSelf(wxSocketBase) pObject, void* buffer, TUInt32 nbytes);

TClassDef(wxSocketClient) TBool wxSocketClient_Connect(TSelf(wxSocketClient) pObject,
                                                       TClass(wxSockAddress) address, TBool wait);
TBool wxSocketClient_ConnectLocal(TSelf(wxSocketClient) pObject, TClass(wxSockAddress) address,
                                  TClass(wxSockAddress) local, TBool wait);
TClass(wxSocketClient) wxSocketClient_Create(int flags);
void wxSocketClient_Delete(TSelf(wxSocketClient) pObject);
TBool wxSocketClient_WaitOnConnect(TSelf(wxSocketClient) pObject, long seconds, long millisecond);

TClassDef(wxSocketEvent) TClass(wxSocketEvent) wxSocketEvent_Create(int id);
void wxSocketEvent_Delete(TSelf(wxSocketEvent) pObject);
void* wxSocketEvent_GetClientData(TSelf(wxSocketEvent) pObject);
TClass(wxSocketBase) wxSocketEvent_GetSocket(TSelf(wxSocketEvent) pObject);
int wxSocketEvent_GetSocketEvent(TSelf(wxSocketEvent) pObject);

TClassDef(wxSocketServer) TClass(wxSocketBase)
    wxSocketServer_Accept(TSelf(wxSocketServer) pObject, TBool wait);
TBool wxSocketServer_AcceptWith(TSelf(wxSocketServer) pObject, TClass(wxSocketBase) socket,
                                TBool wait);
TClass(wxSocketServer) wxSocketServer_Create(TClass(wxSockAddress) address, int flags);
void wxSocketServer_Delete(TSelf(wxSocketServer) pObject);
TBool wxSocketServer_WaitForAccept(TSelf(wxSocketServer) pObject, long seconds, long millisecond);

TClassDef(wxSound) TClass(wxSound) wxSound_Create(TClass(wxString) fileName, TBool isResource);
void wxSound_Delete(TSelf(wxSound) pObject);
TBool wxSound_IsOk(TSelf(wxSound) pObject);
TBool wxSound_Play(TSelf(wxSound) pObject, unsigned flag);
void wxSound_Stop(TSelf(wxSound) pObject);

TClassDef(wxStreamBase) void wxStreamBase_Delete(TSelf(wxStreamBase) pObject);

TClassDef(wxStyledTextCtrl) void wxStyledTextCtrl_AddRefDocument(void* pObject, void* docPointer);
void wxStyledTextCtrl_AddStyledText(void* pObject, void* data);
void wxStyledTextCtrl_AddText(void* pObject, TClass(wxString) text);
void wxStyledTextCtrl_AppendText(void* pObject, TClass(wxString) text);
TBool wxStyledTextCtrl_AutoCompActive(void* pObject);
void wxStyledTextCtrl_AutoCompCancel(void* pObject);
void wxStyledTextCtrl_AutoCompComplete(void* pObject);
TBool wxStyledTextCtrl_AutoCompGetAutoHide(void* pObject);
TBool wxStyledTextCtrl_AutoCompGetCancelAtStart(void* pObject);
TBool wxStyledTextCtrl_AutoCompGetChooseSingle(void* pObject);
TBool wxStyledTextCtrl_AutoCompGetDropRestOfWord(void* pObject);
TBool wxStyledTextCtrl_AutoCompGetIgnoreCase(void* pObject);
int wxStyledTextCtrl_AutoCompGetSeparator(void* pObject);
int wxStyledTextCtrl_AutoCompGetTypeSeparator(void* pObject);
int wxStyledTextCtrl_AutoCompPosStart(void* pObject);
void wxStyledTextCtrl_AutoCompSelect(void* pObject, TClass(wxString) text);
void wxStyledTextCtrl_AutoCompSetAutoHide(void* pObject, TBool autoHide);
void wxStyledTextCtrl_AutoCompSetCancelAtStart(void* pObject, TBool cancel);
void wxStyledTextCtrl_AutoCompSetChooseSingle(void* pObject, TBool chooseSingle);
void wxStyledTextCtrl_AutoCompSetDropRestOfWord(void* pObject, TBool dropRestOfWord);
void wxStyledTextCtrl_AutoCompSetFillUps(void* pObject, TClass(wxString) characterSet);
void wxStyledTextCtrl_AutoCompSetIgnoreCase(void* pObject, TBool ignoreCase);
void wxStyledTextCtrl_AutoCompSetSeparator(void* pObject, int separatorCharacter);
void wxStyledTextCtrl_AutoCompSetTypeSeparator(void* pObject, int separatorCharacter);
void wxStyledTextCtrl_AutoCompShow(void* pObject, int lenEntered, TClass(wxString) itemList);
void wxStyledTextCtrl_AutoCompStops(void* pObject, TClass(wxString) characterSet);
void wxStyledTextCtrl_BeginUndoAction(void* pObject);
void wxStyledTextCtrl_BraceBadLight(void* pObject, int pos);
void wxStyledTextCtrl_BraceHighlight(void* pObject, int pos1, int pos2);
int wxStyledTextCtrl_BraceMatch(void* pObject, int pos);
TBool wxStyledTextCtrl_CallTipActive(void* pObject);
void wxStyledTextCtrl_CallTipCancel(void* pObject);
int wxStyledTextCtrl_CallTipPosAtStart(void* pObject);
void wxStyledTextCtrl_CallTipSetBackground(void* pObject, int back_r, int back_g, int back_b);
void wxStyledTextCtrl_CallTipSetForeground(void* pObject, int fore_r, int fore_g, int fore_b);
void wxStyledTextCtrl_CallTipSetForegroundHighlight(void* pObject, int fore_r, int fore_g,
                                                    int fore_b);
void wxStyledTextCtrl_CallTipSetHighlight(void* pObject, int start, int end);
void wxStyledTextCtrl_CallTipShow(void* pObject, int pos, TClass(wxString) definition);
TBool wxStyledTextCtrl_CanPaste(void* pObject);
TBool wxStyledTextCtrl_CanRedo(void* pObject);
TBool wxStyledTextCtrl_CanUndo(void* pObject);
void wxStyledTextCtrl_ChooseCaretX(void* pObject);
void wxStyledTextCtrl_Clear(void* pObject);
void wxStyledTextCtrl_ClearAll(void* pObject);
void wxStyledTextCtrl_ClearDocumentStyle(void* pObject);
void wxStyledTextCtrl_ClearRegisteredImages(void* pObject);
void wxStyledTextCtrl_CmdKeyAssign(void* pObject, int key, int modifiers, int cmd);
void wxStyledTextCtrl_CmdKeyClear(void* pObject, int key, int modifiers);
void wxStyledTextCtrl_CmdKeyClearAll(void* pObject);
void wxStyledTextCtrl_CmdKeyExecute(void* pObject, int cmd);
void wxStyledTextCtrl_Colourise(void* pObject, int start, int end);
void wxStyledTextCtrl_ConvertEOLs(void* pObject, int eolMode);
void wxStyledTextCtrl_Copy(void* pObject);
void wxStyledTextCtrl_CopyRange(void* pObject, int start, int end);
void wxStyledTextCtrl_CopyText(void* pObject, int length, TClass(wxString) text);
void* wxStyledTextCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) text, int x, int y,
                              int width, int height, int style);
void* wxStyledTextCtrl_CreateDocument(void* pObject);
void wxStyledTextCtrl_Cut(void* pObject);
void wxStyledTextCtrl_DelLineLeft(void* pObject);
void wxStyledTextCtrl_DelLineRight(void* pObject);
int wxStyledTextCtrl_DocLineFromVisible(void* pObject, int lineDisplay);
void wxStyledTextCtrl_EmptyUndoBuffer(void* pObject);
void wxStyledTextCtrl_EndUndoAction(void* pObject);
void wxStyledTextCtrl_EnsureCaretVisible(void* pObject);
void wxStyledTextCtrl_EnsureVisible(void* pObject, int line);
void wxStyledTextCtrl_EnsureVisibleEnforcePolicy(void* pObject, int line);
int wxStyledTextCtrl_FindText(void* pObject, int minPos, int maxPos, TClass(wxString) text,
                              int flags);
int wxStyledTextCtrl_FormatRange(void* pObject, TBool doDraw, int startPos, int endPos, void* draw,
                                 void* target, void* renderRect, void* pageRect);
int wxStyledTextCtrl_GetAnchor(void* pObject);
TBool wxStyledTextCtrl_GetBackSpaceUnIndents(void* pObject);
TBool wxStyledTextCtrl_GetBufferedDraw(void* pObject);
void* wxStyledTextCtrl_GetCaretForeground(void* pObject);
void* wxStyledTextCtrl_GetCaretLineBackground(void* pObject);
TBool wxStyledTextCtrl_GetCaretLineVisible(void* pObject);
int wxStyledTextCtrl_GetCaretPeriod(void* pObject);
int wxStyledTextCtrl_GetCaretWidth(void* pObject);
int wxStyledTextCtrl_GetCharAt(void* pObject, int pos);
int wxStyledTextCtrl_GetCodePage(void* pObject);
int wxStyledTextCtrl_GetColumn(void* pObject, int pos);
int wxStyledTextCtrl_GetControlCharSymbol(void* pObject);
int wxStyledTextCtrl_GetCurrentLine(void* pObject);
int wxStyledTextCtrl_GetCurrentPos(void* pObject);
void* wxStyledTextCtrl_GetDocPointer(void* pObject);
void* wxStyledTextCtrl_GetEdgeColour(void* pObject);
int wxStyledTextCtrl_GetEdgeColumn(void* pObject);
int wxStyledTextCtrl_GetEdgeMode(void* pObject);
int wxStyledTextCtrl_GetEndAtLastLine(void* pObject);
int wxStyledTextCtrl_GetEndStyled(void* pObject);
int wxStyledTextCtrl_GetEOLMode(void* pObject);
int wxStyledTextCtrl_GetFirstVisibleLine(void* pObject);
TBool wxStyledTextCtrl_GetFoldExpanded(void* pObject, int line);
int wxStyledTextCtrl_GetFoldLevel(void* pObject, int line);
int wxStyledTextCtrl_GetFoldParent(void* pObject, int line);
int wxStyledTextCtrl_GetHighlightGuide(void* pObject);
int wxStyledTextCtrl_GetIndent(void* pObject);
TBool wxStyledTextCtrl_GetIndentationGuides(void* pObject);
int wxStyledTextCtrl_GetLastChild(void* pObject, int line, int level);
TBool wxStyledTextCtrl_GetLastKeydownProcessed(void* pObject);
int wxStyledTextCtrl_GetLayoutCache(void* pObject);
int wxStyledTextCtrl_GetLength(void* pObject);
int wxStyledTextCtrl_GetLexer(void* pObject);
void* wxStyledTextCtrl_GetLine(void* pObject, int line);
int wxStyledTextCtrl_GetLineCount(void* pObject);
int wxStyledTextCtrl_GetLineEndPosition(void* pObject, int line);
int wxStyledTextCtrl_GetLineIndentation(void* pObject, int line);
int wxStyledTextCtrl_GetLineIndentPosition(void* pObject, int line);
int wxStyledTextCtrl_GetLineState(void* pObject, int line);
TBool wxStyledTextCtrl_GetLineVisible(void* pObject, int line);
int wxStyledTextCtrl_GetMarginLeft(void* pObject);
int wxStyledTextCtrl_GetMarginMask(void* pObject, int margin);
int wxStyledTextCtrl_GetMarginRight(void* pObject);
TBool wxStyledTextCtrl_GetMarginSensitive(void* pObject, int margin);
int wxStyledTextCtrl_GetMarginType(void* pObject, int margin);
int wxStyledTextCtrl_GetMarginWidth(void* pObject, int margin);
int wxStyledTextCtrl_GetMaxLineState(void* pObject);
int wxStyledTextCtrl_GetModEventMask(void* pObject);
TBool wxStyledTextCtrl_GetModify(void* pObject);
TBool wxStyledTextCtrl_GetMouseDownCaptures(void* pObject);
int wxStyledTextCtrl_GetMouseDwellTime(void* pObject);
TBool wxStyledTextCtrl_GetOvertype(void* pObject);
int wxStyledTextCtrl_GetPrintColourMode(void* pObject);
int wxStyledTextCtrl_GetPrintMagnification(void* pObject);
int wxStyledTextCtrl_GetPrintWrapMode(void* pObject);
TBool wxStyledTextCtrl_GetReadOnly(void* pObject);
int wxStyledTextCtrl_GetScrollWidth(void* pObject);
int wxStyledTextCtrl_GetSearchFlags(void* pObject);
void* wxStyledTextCtrl_GetSelectedText(void* pObject);
void wxStyledTextCtrl_GetSelection(void* pObject, void* startPos, void* endPos);
int wxStyledTextCtrl_GetSelectionEnd(void* pObject);
int wxStyledTextCtrl_GetSelectionStart(void* pObject);
int wxStyledTextCtrl_GetStatus(void* pObject);
int wxStyledTextCtrl_GetSTCCursor(void* pObject);
TBool wxStyledTextCtrl_GetSTCFocus(void* pObject);
int wxStyledTextCtrl_GetStyleAt(void* pObject, int pos);
TBool wxStyledTextCtrl_GetTabIndents(void* pObject);
int wxStyledTextCtrl_GetTabWidth(void* pObject);
int wxStyledTextCtrl_GetTargetEnd(void* pObject);
int wxStyledTextCtrl_GetTargetStart(void* pObject);
void* wxStyledTextCtrl_GetText(void* pObject);
int wxStyledTextCtrl_GetTextLength(void* pObject);
void* wxStyledTextCtrl_GetTextRange(void* pObject, int startPos, int endPos);
TBool wxStyledTextCtrl_GetUndoCollection(void* pObject);
TBool wxStyledTextCtrl_GetUseHorizontalScrollBar(void* pObject);
TBool wxStyledTextCtrl_GetUseTabs(void* pObject);
TBool wxStyledTextCtrl_GetUseVerticalScrollBar(void* pObject);
TBool wxStyledTextCtrl_GetViewEOL(void* pObject);
int wxStyledTextCtrl_GetViewWhiteSpace(void* pObject);
int wxStyledTextCtrl_GetWrapMode(void* pObject);
int wxStyledTextCtrl_GetXOffset(void* pObject);
int wxStyledTextCtrl_GetZoom(void* pObject);
void wxStyledTextCtrl_GotoLine(void* pObject, int line);
void wxStyledTextCtrl_GotoPos(void* pObject, int pos);
void wxStyledTextCtrl_HideLines(void* pObject, int lineStart, int lineEnd);
void wxStyledTextCtrl_HideSelection(void* pObject, TBool normal);
void wxStyledTextCtrl_HomeDisplay(void* pObject);
void wxStyledTextCtrl_HomeDisplayExtend(void* pObject);
void* wxStyledTextCtrl_IndicatorGetForeground(void* pObject, int indic);
int wxStyledTextCtrl_IndicatorGetStyle(void* pObject, int indic);
void wxStyledTextCtrl_IndicatorSetForeground(void* pObject, int indic, int fore_r, int fore_g,
                                             int fore_b);
void wxStyledTextCtrl_IndicatorSetStyle(void* pObject, int indic, int style);
void wxStyledTextCtrl_InsertText(void* pObject, int pos, TClass(wxString) text);
void wxStyledTextCtrl_LineCopy(void* pObject);
void wxStyledTextCtrl_LineDuplicate(void* pObject);
void wxStyledTextCtrl_LineEndDisplay(void* pObject);
void wxStyledTextCtrl_LineEndDisplayExtend(void* pObject);
int wxStyledTextCtrl_LineFromPosition(void* pObject, int pos);
int wxStyledTextCtrl_LineLength(void* pObject, int line);
void wxStyledTextCtrl_LineScroll(void* pObject, int columns, int lines);
void wxStyledTextCtrl_LinesJoin(void* pObject);
int wxStyledTextCtrl_LinesOnScreen(void* pObject);
void wxStyledTextCtrl_LinesSplit(void* pObject, int pixelWidth);
TBool wxStyledTextCtrl_LoadFile(void* pObject, TClass(wxString) filename);
int wxStyledTextCtrl_MarkerAdd(void* pObject, int line, int markerNumber);
void wxStyledTextCtrl_MarkerDefine(void* pObject, int markerNumber, int markerSymbol,
                                   int foreground_r, int foreground_g, int foreground_b,
                                   int background_r, int background_g, int background_b);
void wxStyledTextCtrl_MarkerDefineBitmap(void* pObject, int markerNumber, void* bmp);
void wxStyledTextCtrl_MarkerDelete(void* pObject, int line, int markerNumber);
void wxStyledTextCtrl_MarkerDeleteAll(void* pObject, int markerNumber);
void wxStyledTextCtrl_MarkerDeleteHandle(void* pObject, int handle);
int wxStyledTextCtrl_MarkerGet(void* pObject, int line);
int wxStyledTextCtrl_MarkerLineFromHandle(void* pObject, int handle);
int wxStyledTextCtrl_MarkerNext(void* pObject, int lineStart, int markerMask);
int wxStyledTextCtrl_MarkerPrevious(void* pObject, int lineStart, int markerMask);
void wxStyledTextCtrl_MarkerSetBackground(void* pObject, int markerNumber, int back_r, int back_g,
                                          int back_b);
void wxStyledTextCtrl_MarkerSetForeground(void* pObject, int markerNumber, int fore_r, int fore_g,
                                          int fore_b);
void wxStyledTextCtrl_MoveCaretInsideView(void* pObject);
void wxStyledTextCtrl_Paste(void* pObject);
void* wxStyledTextCtrl_PointFromPosition(void* pObject, int pos);
int wxStyledTextCtrl_PositionAfter(void* pObject, int pos);
int wxStyledTextCtrl_PositionBefore(void* pObject, int pos);
int wxStyledTextCtrl_PositionFromLine(void* pObject, int line);
int wxStyledTextCtrl_PositionFromPoint(void* pObject, int pt_x, int pt_y);
int wxStyledTextCtrl_PositionFromPointClose(void* pObject, int x, int y);
void wxStyledTextCtrl_Redo(void* pObject);
void wxStyledTextCtrl_RegisterImage(void* pObject, int type, void* bmp);
void wxStyledTextCtrl_ReleaseDocument(void* pObject, void* docPointer);
void wxStyledTextCtrl_ReplaceSelection(void* pObject, TClass(wxString) text);
int wxStyledTextCtrl_ReplaceTarget(void* pObject, TClass(wxString) text);
int wxStyledTextCtrl_ReplaceTargetRE(void* pObject, TClass(wxString) text);
TBool wxStyledTextCtrl_SaveFile(void* pObject, TClass(wxString) filename);
void wxStyledTextCtrl_ScrollToColumn(void* pObject, int column);
void wxStyledTextCtrl_ScrollToLine(void* pObject, int line);
void wxStyledTextCtrl_SearchAnchor(void* pObject);
int wxStyledTextCtrl_SearchInTarget(void* pObject, TClass(wxString) text);
int wxStyledTextCtrl_SearchNext(void* pObject, int flags, TClass(wxString) text);
int wxStyledTextCtrl_SearchPrev(void* pObject, int flags, TClass(wxString) text);
void wxStyledTextCtrl_SelectAll(void* pObject);
TBool wxStyledTextCtrl_SelectionIsRectangle(void* pObject);
void wxStyledTextCtrl_SetAnchor(void* pObject, int posAnchor);
void wxStyledTextCtrl_SetBackSpaceUnIndents(void* pObject, TBool bsUnIndents);
void wxStyledTextCtrl_SetBufferedDraw(void* pObject, TBool buffered);
void wxStyledTextCtrl_SetCaretForeground(void* pObject, int fore_r, int fore_g, int fore_b);
void wxStyledTextCtrl_SetCaretLineBackground(void* pObject, int back_r, int back_g, int back_b);
void wxStyledTextCtrl_SetCaretLineVisible(void* pObject, TBool show);
void wxStyledTextCtrl_SetCaretPeriod(void* pObject, int periodMilliseconds);
void wxStyledTextCtrl_SetCaretWidth(void* pObject, int pixelWidth);
void wxStyledTextCtrl_SetCodePage(void* pObject, int codePage);
void wxStyledTextCtrl_SetControlCharSymbol(void* pObject, int symbol);
void wxStyledTextCtrl_SetCurrentPos(void* pObject, int pos);
void wxStyledTextCtrl_SetDocPointer(void* pObject, void* docPointer);
void wxStyledTextCtrl_SetEdgeColour(void* pObject, int edgeColour_r, int edgeColour_g,
                                    int edgeColour_b);
void wxStyledTextCtrl_SetEdgeColumn(void* pObject, int column);
void wxStyledTextCtrl_SetEdgeMode(void* pObject, int mode);
void wxStyledTextCtrl_SetEndAtLastLine(void* pObject, TBool endAtLastLine);
void wxStyledTextCtrl_SetEOLMode(void* pObject, int eolMode);
void wxStyledTextCtrl_SetFoldExpanded(void* pObject, int line, TBool expanded);
void wxStyledTextCtrl_SetFoldFlags(void* pObject, int flags);
void wxStyledTextCtrl_SetFoldLevel(void* pObject, int line, int level);
void wxStyledTextCtrl_SetFoldMarginColour(void* pObject, TBool useSetting, int back_r, int back_g,
                                          int back_b);
void wxStyledTextCtrl_SetFoldMarginHiColour(void* pObject, TBool useSetting, int fore_r, int fore_g,
                                            int fore_b);
void wxStyledTextCtrl_SetHighlightGuide(void* pObject, int column);
void wxStyledTextCtrl_SetHotspotActiveBackground(void* pObject, TBool useSetting, int back_r,
                                                 int back_g, int back_b);
void wxStyledTextCtrl_SetHotspotActiveForeground(void* pObject, TBool useSetting, int fore_r,
                                                 int fore_g, int fore_b);
void wxStyledTextCtrl_SetHotspotActiveUnderline(void* pObject, TBool underline);
void wxStyledTextCtrl_SetHScrollBar(void* pObject, void* bar);
void wxStyledTextCtrl_SetIndent(void* pObject, int indentSize);
void wxStyledTextCtrl_SetIndentationGuides(void* pObject, TBool show);
void wxStyledTextCtrl_SetKeyWords(void* pObject, int keywordSet, TClass(wxString) keyWords);
void wxStyledTextCtrl_SetLastKeydownProcessed(void* pObject, TBool val);
void wxStyledTextCtrl_SetLayoutCache(void* pObject, int mode);
void wxStyledTextCtrl_SetLexer(void* pObject, int lexer);
void wxStyledTextCtrl_SetLexerLanguage(void* pObject, TClass(wxString) language);
void wxStyledTextCtrl_SetLineIndentation(void* pObject, int line, int indentSize);
void wxStyledTextCtrl_SetLineState(void* pObject, int line, int state);
void wxStyledTextCtrl_SetMarginLeft(void* pObject, int pixelWidth);
void wxStyledTextCtrl_SetMarginMask(void* pObject, int margin, int mask);
void wxStyledTextCtrl_SetMarginRight(void* pObject, int pixelWidth);
void wxStyledTextCtrl_SetMargins(void* pObject, int left, int right);
void wxStyledTextCtrl_SetMarginSensitive(void* pObject, int margin, TBool sensitive);
void wxStyledTextCtrl_SetMarginType(void* pObject, int margin, int marginType);
void wxStyledTextCtrl_SetMarginWidth(void* pObject, int margin, int pixelWidth);
void wxStyledTextCtrl_SetModEventMask(void* pObject, int mask);
void wxStyledTextCtrl_SetMouseDownCaptures(void* pObject, TBool captures);
void wxStyledTextCtrl_SetMouseDwellTime(void* pObject, int periodMilliseconds);
void wxStyledTextCtrl_SetOvertype(void* pObject, TBool overtype);
void wxStyledTextCtrl_SetPrintColourMode(void* pObject, int mode);
void wxStyledTextCtrl_SetPrintMagnification(void* pObject, int magnification);
void wxStyledTextCtrl_SetPrintWrapMode(void* pObject, int mode);
void wxStyledTextCtrl_SetProperty(void* pObject, TClass(wxString) key, TClass(wxString) value);
void wxStyledTextCtrl_SetReadOnly(void* pObject, TBool readOnly);
void wxStyledTextCtrl_SetSavePoint(void* pObject);
void wxStyledTextCtrl_SetScrollWidth(void* pObject, int pixelWidth);
void wxStyledTextCtrl_SetSearchFlags(void* pObject, int flags);
void wxStyledTextCtrl_SetSelBackground(void* pObject, TBool useSetting, int back_r, int back_g,
                                       int back_b);
void wxStyledTextCtrl_SetSelection(void* pObject, int start, int end);
void wxStyledTextCtrl_SetSelectionEnd(void* pObject, int pos);
void wxStyledTextCtrl_SetSelectionStart(void* pObject, int pos);
void wxStyledTextCtrl_SetSelForeground(void* pObject, TBool useSetting, int fore_r, int fore_g,
                                       int fore_b);
void wxStyledTextCtrl_SetStatus(void* pObject, int statusCode);
void wxStyledTextCtrl_SetSTCCursor(void* pObject, int cursorType);
void wxStyledTextCtrl_SetSTCFocus(void* pObject, TBool focus);
void wxStyledTextCtrl_SetStyleBytes(void* pObject, int length, void* styleBytes);
void wxStyledTextCtrl_SetStyling(void* pObject, int length, int style);
void wxStyledTextCtrl_SetTabIndents(void* pObject, TBool tabIndents);
void wxStyledTextCtrl_SetTabWidth(void* pObject, int tabWidth);
void wxStyledTextCtrl_SetTargetEnd(void* pObject, int pos);
void wxStyledTextCtrl_SetTargetStart(void* pObject, int pos);
void wxStyledTextCtrl_SetText(void* pObject, TClass(wxString) text);
void wxStyledTextCtrl_SetUndoCollection(void* pObject, TBool collectUndo);
void wxStyledTextCtrl_SetUseHorizontalScrollBar(void* pObject, TBool show);
void wxStyledTextCtrl_SetUseTabs(void* pObject, TBool useTabs);
void wxStyledTextCtrl_SetUseVerticalScrollBar(void* pObject, TBool show);
void wxStyledTextCtrl_SetViewEOL(void* pObject, TBool visible);
void wxStyledTextCtrl_SetViewWhiteSpace(void* pObject, int viewWS);
void wxStyledTextCtrl_SetVisiblePolicy(void* pObject, int visiblePolicy, int visibleSlop);
void wxStyledTextCtrl_SetVScrollBar(void* pObject, void* bar);
void wxStyledTextCtrl_SetWhitespaceBackground(void* pObject, TBool useSetting, int back_r,
                                              int back_g, int back_b);
void wxStyledTextCtrl_SetWhitespaceForeground(void* pObject, TBool useSetting, int fore_r,
                                              int fore_g, int fore_b);
void wxStyledTextCtrl_SetWordChars(void* pObject, TClass(wxString) characters);
void wxStyledTextCtrl_SetWrapMode(void* pObject, int mode);
void wxStyledTextCtrl_SetXCaretPolicy(void* pObject, int caretPolicy, int caretSlop);
void wxStyledTextCtrl_SetXOffset(void* pObject, int newOffset);
void wxStyledTextCtrl_SetYCaretPolicy(void* pObject, int caretPolicy, int caretSlop);
void wxStyledTextCtrl_SetZoom(void* pObject, int zoom);
void wxStyledTextCtrl_ShowLines(void* pObject, int lineStart, int lineEnd);
void wxStyledTextCtrl_StartRecord(void* pObject);
void wxStyledTextCtrl_StartStyling(void* pObject, int pos);
void wxStyledTextCtrl_StopRecord(void* pObject);
void wxStyledTextCtrl_StyleClearAll(void* pObject);
void wxStyledTextCtrl_StyleResetDefault(void* pObject);
void wxStyledTextCtrl_StyleSetBackground(void* pObject, int style, int back_r, int back_g,
                                         int back_b);
void wxStyledTextCtrl_StyleSetBold(void* pObject, int style, TBool bold);
void wxStyledTextCtrl_StyleSetCase(void* pObject, int style, int caseForce);
void wxStyledTextCtrl_StyleSetChangeable(void* pObject, int style, TBool changeable);
void wxStyledTextCtrl_StyleSetCharacterSet(void* pObject, int style, int characterSet);
void wxStyledTextCtrl_StyleSetEOLFilled(void* pObject, int style, TBool filled);
void wxStyledTextCtrl_StyleSetFaceName(void* pObject, int style, TClass(wxString) fontName);
void wxStyledTextCtrl_StyleSetFont(void* pObject, int styleNum, void* font);
void wxStyledTextCtrl_StyleSetFontAttr(void* pObject, int styleNum, int size,
                                       TClass(wxString) faceName, TBool bold, TBool italic,
                                       TBool underline);
void wxStyledTextCtrl_StyleSetForeground(void* pObject, int style, int fore_r, int fore_g,
                                         int fore_b);
void wxStyledTextCtrl_StyleSetHotSpot(void* pObject, int style, TBool hotspot);
void wxStyledTextCtrl_StyleSetItalic(void* pObject, int style, TBool italic);
void wxStyledTextCtrl_StyleSetSize(void* pObject, int style, int sizePoints);
void wxStyledTextCtrl_StyleSetSpec(void* pObject, int styleNum, TClass(wxString) spec);
void wxStyledTextCtrl_StyleSetUnderline(void* pObject, int style, TBool underline);
void wxStyledTextCtrl_StyleSetVisible(void* pObject, int style, TBool visible);
void wxStyledTextCtrl_TargetFromSelection(void* pObject);
int wxStyledTextCtrl_TextHeight(void* pObject, int line);
int wxStyledTextCtrl_TextWidth(void* pObject, int style, TClass(wxString) text);
void wxStyledTextCtrl_ToggleFold(void* pObject, int line);
void wxStyledTextCtrl_Undo(void* pObject);
void wxStyledTextCtrl_UsePopUp(void* pObject, TBool allowPopUp);
void wxStyledTextCtrl_UserListShow(void* pObject, int listType, TClass(wxString) itemList);
int wxStyledTextCtrl_VisibleFromDocLine(void* pObject, int line);
int wxStyledTextCtrl_WordEndPosition(void* pObject, int pos, TBool onlyWordCharacters);
void wxStyledTextCtrl_WordPartLeft(void* pObject);
void wxStyledTextCtrl_WordPartLeftExtend(void* pObject);
void wxStyledTextCtrl_WordPartRight(void* pObject);
void wxStyledTextCtrl_WordPartRightExtend(void* pObject);
int wxStyledTextCtrl_WordStartPosition(void* pObject, int pos, TBool onlyWordCharacters);

TClassDef(wxStyledTextEvent) void* wxStyledTextEvent_Clone(void* pObject);
TBool wxStyledTextEvent_GetAlt(void* pObject);
TBool wxStyledTextEvent_GetControl(void* pObject);
TBool wxStyledTextEvent_GetDragAllowMove(void* pObject);
int wxStyledTextEvent_GetDragResult(void* pObject);
void* wxStyledTextEvent_GetDragText(void* pObject);
int wxStyledTextEvent_GetFoldLevelNow(void* pObject);
int wxStyledTextEvent_GetFoldLevelPrev(void* pObject);
int wxStyledTextEvent_GetKey(void* pObject);
int wxStyledTextEvent_GetLength(void* pObject);
int wxStyledTextEvent_GetLine(void* pObject);
int wxStyledTextEvent_GetLinesAdded(void* pObject);
int wxStyledTextEvent_GetListType(void* pObject);
int wxStyledTextEvent_GetLParam(void* pObject);
int wxStyledTextEvent_GetMargin(void* pObject);
int wxStyledTextEvent_GetMessage(void* pObject);
int wxStyledTextEvent_GetModificationType(void* pObject);
int wxStyledTextEvent_GetModifiers(void* pObject);
int wxStyledTextEvent_GetPosition(void* pObject);
TBool wxStyledTextEvent_GetShift(void* pObject);
void* wxStyledTextEvent_GetText(void* pObject);
int wxStyledTextEvent_GetWParam(void* pObject);
int wxStyledTextEvent_GetX(void* pObject);
int wxStyledTextEvent_GetY(void* pObject);
void wxStyledTextEvent_SetDragAllowMove(void* pObject, int val);
void wxStyledTextEvent_SetDragResult(void* pObject, int val);
void wxStyledTextEvent_SetDragText(void* pObject, void* val);
void wxStyledTextEvent_SetFoldLevelNow(void* pObject, int val);
void wxStyledTextEvent_SetFoldLevelPrev(void* pObject, int val);
void wxStyledTextEvent_SetKey(void* pObject, int keyCode);
void wxStyledTextEvent_SetLength(void* pObject, int len);
void wxStyledTextEvent_SetLine(void* pObject, int val);
void wxStyledTextEvent_SetLinesAdded(void* pObject, int num);
void wxStyledTextEvent_SetListType(void* pObject, int val);
void wxStyledTextEvent_SetLParam(void* pObject, int val);
void wxStyledTextEvent_SetMargin(void* pObject, int val);
void wxStyledTextEvent_SetMessage(void* pObject, int val);
void wxStyledTextEvent_SetModificationType(void* pObject, int modType);
void wxStyledTextEvent_SetModifiers(void* pObject, int modifiers);
void wxStyledTextEvent_SetPosition(void* pObject, int pos);
void wxStyledTextEvent_SetText(void* pObject, void* text);
void wxStyledTextEvent_SetWParam(void* pObject, int val);
void wxStyledTextEvent_SetX(void* pObject, int val);
void wxStyledTextEvent_SetY(void* pObject, int val);

TClassDef(wxTextAttr) TClass(wxTextAttr)
    wxTextAttr_Create(TClass(wxColour) colText, TClass(wxColour) colBack, TClass(wxFont) font);
TClass(wxTextAttr) wxTextAttr_CreateDefault();
void wxTextAttr_Delete(TSelf(wxTextAttr) pObject);
void wxTextAttr_GetBackgroundColour(TSelf(wxTextAttr) pObject, TClass(wxColour) colour);
void wxTextAttr_GetFont(TSelf(wxTextAttr) pObject, TClass(wxFont) font);
void wxTextAttr_GetTextColour(TSelf(wxTextAttr) pObject, TClass(wxColour) colour);
TBool wxTextAttr_HasBackgroundColour(TSelf(wxTextAttr) pObject);
TBool wxTextAttr_HasFont(TSelf(wxTextAttr) pObject);
TBool wxTextAttr_HasTextColour(TSelf(wxTextAttr) pObject);
TBool wxTextAttr_IsDefault(TSelf(wxTextAttr) pObject);
void wxTextAttr_SetBackgroundColour(TSelf(wxTextAttr) pObject, TClass(wxColour) colour);
void wxTextAttr_SetFont(TSelf(wxTextAttr) pObject, TClass(wxFont) font);
void wxTextAttr_SetTextColour(TSelf(wxTextAttr) pObject, TClass(wxColour) colour);

TClassDef(wxTextCtrl) int wxTextCtrl_EmulateKeyPress(TSelf(wxTextCtrl) pObject,
                                                     TClass(wxKeyEvent) keyevent);
TClass(wxString) wxTextCtrl_GetRange(TSelf(wxTextCtrl) pObject, long from, long toPos);
TClass(wxString) wxTextCtrl_GetStringSelection(TSelf(wxTextCtrl) pObject);

TClassDef(wxTextInputStream) TClass(wxTextInputStream)
    wxTextInputStream_Create(TClass(wxInputStream) inputStream, TClass(wxString) sep);
void wxTextInputStream_Delete(TSelf(wxTextInputStream) pObject);
TClass(wxString) wxTextInputStream_ReadLine(TSelf(wxTextInputStream) pObject);

TClassDef(wxTextOutputStream) TClass(wxTextOutputStream)
    wxTextOutputStream_Create(TClass(wxOutputStream) outputStream, int mode);
void wxTextOutputStream_Delete(TSelf(wxTextOutputStream) pObject);
void wxTextOutputStream_WriteString(TSelf(wxTextOutputStream) pObject, TClass(wxString) txt);

TClassDef(wxTimerEx) void wxTimerEx_Connect(TSelf(wxTimerEx) pObject, TClass(wxClosure) closure);
TClass(wxTimerEx) wxTimerEx_Create();
TClass(wxClosure) wxTimerEx_GetClosure(TSelf(wxTimerEx) pObject);

TClassDef(wxToolBar) void wxToolBar_AddTool2(TSelf(wxToolBar) pObject, int toolId,
                                             TClass(wxString) label, TClass(wxBitmap) bmp,
                                             TClass(wxBitmap) bmpDisabled, int itemKind,
                                             TClass(wxString) shortHelp, TClass(wxString) longHelp);

TClassDef(wxToolTip) void* wxToolTip_Create(TClass(wxString) tip);
void wxToolTip_Enable(TBool flag);
TClass(wxString) wxToolTip_GetTip(TSelf(wxToolTip) pObject);
void* wxToolTip_GetWindow(TSelf(wxToolTip) pObject);
void wxToolTip_SetAutoPop(long milliseconds);
void wxToolTip_SetDelay(long milliseconds);
void wxToolTip_SetMaxWidth(int width);
void wxToolTip_SetReshow(long milliseconds);
void wxToolTip_SetTip(TSelf(wxToolTip) pObject, TClass(wxString) tip);

TClassDef(wxTreeCtrl) void wxTreeCtrl_AssignImageList(TSelf(wxTreeCtrl) pObject,
                                                      TClass(wxImageList) imageList);
void wxTreeCtrl_AssignStateImageList(TSelf(wxTreeCtrl) pObject, TClass(wxImageList) imageList);
TClass(wxTreeCtrl) wxTreeCtrl_Create2(TClass(wxWindow) parent, int id, int x, int y, int width,
                                      int height, int style);
void* wxTreeCtrl_GetItemClientClosure(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_InsertItem2(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) parent,
                            TClass(wxTreeItemId) idPrevious, TClass(wxString) text, int image,
                            int selectedImage, TClass(wxClosure) closure,
                            TClass(wxTreeItemId) item);
void wxTreeCtrl_InsertItemByIndex2(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) parent,
                                   int index, TClass(wxString) text, int image, int selectedImage,
                                   TClass(wxClosure) data, TClass(wxTreeItemId) item);
void wxTreeCtrl_SetItemClientClosure(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                     TClass(wxClosure) closure);

TClassDef(wxTreeEvent) void wxTreeEvent_Allow(TSelf(wxTreeEvent) pObject);
TClass(wxKeyEvent) wxTreeEvent_GetKeyEvent(TSelf(wxTreeEvent) pObject);
TBool wxTreeEvent_IsEditCancelled(TSelf(wxTreeEvent) pObject);

TClassDef(wxTreeItemId) TClass(wxTreeItemId) wxTreeItemId_Clone(TSelf(wxTreeItemId) pObject);
TClass(wxTreeItemId) wxTreeItemId_CreateFromValue(intptr_t value);
intptr_t wxTreeItemId_GetValue(TSelf(wxTreeItemId) pObject);

TClassDef(wxUIActionSimulator) TBool
    wxUIActionSimulator_Char(TSelf(wxUIActionSimulator) pObject, int keycode, int modifiers);
void* wxUIActionSimulator_Create();
void wxUIActionSimulator_Delete(TSelf(wxUIActionSimulator) pObject);
TBool wxUIActionSimulator_KeyDown(TSelf(wxUIActionSimulator) pObject, int keycode, int modifiers);
TBool wxUIActionSimulator_KeyUp(TSelf(wxUIActionSimulator) pObject, int keycode, int modifiers);
TBool wxUIActionSimulator_MouseClick(TSelf(wxUIActionSimulator) pObject, int button);
TBool wxUIActionSimulator_MouseDblClick(TSelf(wxUIActionSimulator) pObject, int button);
TBool wxUIActionSimulator_MouseDown(TSelf(wxUIActionSimulator) pObject, int button);
TBool wxUIActionSimulator_MouseDragDrop(TSelf(wxUIActionSimulator) pObject, int x1, int y1, int x2,
                                        int y2, int button);
TBool wxUIActionSimulator_MouseMove(TSelf(wxUIActionSimulator) pObject, int x, int y);
TBool wxUIActionSimulator_MouseMoveToWindow(TSelf(wxUIActionSimulator) pObject,
                                            TClass(wxWindow) window, int x, int y);
TBool wxUIActionSimulator_MouseUp(TSelf(wxUIActionSimulator) pObject, int button);
TBool wxUIActionSimulator_Select(TSelf(wxUIActionSimulator) pObject, TClass(wxString) text);
TBool wxUIActionSimulator_Text(TSelf(wxUIActionSimulator) pObject, TClass(wxString) text);

TClassDef(wxVideoMode) void* wxVideoMode_Create(int width, int height, int depth, int freq);
void wxVideoMode_Delete(TSelf(wxVideoMode) pObject);
int wxVideoMode_GetDepth(TSelf(wxVideoMode) pObject);
int wxVideoMode_GetHeight(TSelf(wxVideoMode) pObject);
int wxVideoMode_GetWidth(TSelf(wxVideoMode) pObject);
TBool wxVideoMode_IsOk(TSelf(wxVideoMode) pObject);
TBool wxVideoMode_Matches(TSelf(wxVideoMode) pObject, TClass(wxVideoMode) other);

TClassDefExtend(wxVListBox, wxVScrolledWindow) void wxVListBox_Clear(TSelf(wxVListBox) pObject);
TBool wxVListBox_Create(TSelf(wxVListBox) pObject, TClass(wxWindow) parent, int id, int x, int y,
                        int width, int height, long style, TClass(wxString) name);
TBool wxVListBox_DeselectAll(TSelf(wxVListBox) pObject);
int wxVListBox_GetFirstSelected(TSelf(wxVListBox) pObject, unsigned long* cookie);
size_t wxVListBox_GetItemCount(TSelf(wxVListBox) pObject);
void wxVListBox_GetItemRect(TSelf(wxVListBox) pObject, size_t item, int* x, int* y, int* width,
                            int* height);
int wxVListBox_GetNextSelected(TSelf(wxVListBox) pObject, unsigned long* cookie);
size_t wxVListBox_GetSelectedCount(TSelf(wxVListBox) pObject);
int wxVListBox_GetSelection(TSelf(wxVListBox) pObject);
void wxVListBox_GetSelectionBackground(TSelf(wxVListBox) pObject, TClass(wxColour) colour);
TBool wxVListBox_HasMultipleSelection(TSelf(wxVListBox) pObject);
TBool wxVListBox_IsCurrent(TSelf(wxVListBox) pObject, size_t item);
TBool wxVListBox_IsSelected(TSelf(wxVListBox) pObject, size_t item);
TBool wxVListBox_Select(TSelf(wxVListBox) pObject, size_t item, TBool select);
TBool wxVListBox_SelectAll(TSelf(wxVListBox) pObject);
TBool wxVListBox_SelectRange(TSelf(wxVListBox) pObject, size_t from, size_t toPos);
void wxVListBox_SetItemCount(TSelf(wxVListBox) pObject, size_t count);
void wxVListBox_SetMargins(TSelf(wxVListBox) pObject, int x, int y);
void wxVListBox_SetSelection(TSelf(wxVListBox) pObject, int selection);
void wxVListBox_SetSelectionBackground(TSelf(wxVListBox) pObject, TClass(wxColour) col);
void wxVListBox_Toggle(TSelf(wxVListBox) pObject, size_t item);

TClassDefExtend(wxVScrolledWindow, wxPanel) TBool
    wxVScrolledWindow_Create(TSelf(wxVScrolledWindow) pObject, TClass(wxWindow) parent, int id,
                             int x, int y, int width, int height, long style,
                             TClass(wxString) name);
size_t wxVScrolledWindow_GetRowCount(TSelf(wxVScrolledWindow) pObject);
size_t wxVScrolledWindow_GetVisibleRowsBegin(TSelf(wxVScrolledWindow) pObject);
size_t wxVScrolledWindow_GetVisibleRowsEnd(TSelf(wxVScrolledWindow) pObject);
TBool wxVScrolledWindow_IsRowVisible(TSelf(wxVScrolledWindow) pObject, size_t row);
void wxVScrolledWindow_RefreshRow(TSelf(wxVScrolledWindow) pObject, size_t row);
void wxVScrolledWindow_RefreshRows(TSelf(wxVScrolledWindow) pObject, size_t from, size_t toPos);
TBool wxVScrolledWindow_ScrollRowPages(TSelf(wxVScrolledWindow) pObject, int pages);
TBool wxVScrolledWindow_ScrollRows(TSelf(wxVScrolledWindow) pObject, int rows);
TBool wxVScrolledWindow_ScrollToRow(TSelf(wxVScrolledWindow) pObject, size_t row);
void wxVScrolledWindow_SetRowCount(TSelf(wxVScrolledWindow) pObject, size_t rowCount);

TClassDef(wxWindow) TClass(wxPoint)
    wxWindow_ConvertDialogToPixelsEx(TSelf(wxWindow) pObject, int x, int y);
TClass(wxPoint) wxWindow_ConvertPixelsToDialogEx(TSelf(wxWindow) pObject, int x, int y);
TClass(wxPoint) wxWindow_ScreenToClient2(TSelf(wxWindow) pObject, int x, int y);

TClassDef(wxWindowDisabler) void* wxWindowDisabler_Create(TClass(wxWindow) winToSkip);
void wxWindowDisabler_Delete(TSelf(wxWindowDisabler) pObject);

TClassDef(wxXmlResource) void* wxXmlResource_GetStyledTextCtrl(TClass(wxWindow) win,
                                                               TClass(wxString) strId);

// Free functions (no class prefix). These must follow a class block so that the
// class parser records them as free functions.
void kwxBeginBusyCursor();
void kwxBell();
void kwxEndBusyCursor();
void kwxFree(void* pObject);
TClass(wxPoint) kwxGetMousePosition();
int kwxGetPixelRGB(TClass(wxUint8) buffer, int width, int x, int y);
int kwxGetPixelRGBA(TClass(wxUint8) buffer, int width, int x, int y);
void kwxInitPixelsRGB(TClass(wxUint8) buffer, int width, int height, int rgb);
void kwxInitPixelsRGBA(TClass(wxUint8) buffer, int width, int height, int rgba);
int kwxIsBusy();
void* kwxMalloc(int size);
void kwxSetPixelRGB(TClass(wxUint8) buffer, int width, int x, int y, int rgb);
void kwxSetPixelRGBA(TClass(wxUint8) buffer, int width, int x, int y, unsigned int rgba);
void kwxSetPixelRowRGB(TClass(wxUint8) buffer, int width, int x, int y, int rgb0, int rgb1,
                       int count);
void kwxSetPixelRowRGBA(TClass(wxUint8) buffer, int width, int x, int y, unsigned int rgba0,
                        unsigned int rgba1, unsigned int count);
TClass(wxColour) kwxSystemSettingsGetColour(int systemColour);
void kwxWakeUpIdle();
void wxAboutBox(TClass(wxAboutDialogInfo) info, TClass(wxWindow) parent);
TClass(wxDragImage) wxDragIcon(TClass(wxIcon) icon, int x, int y);
TClass(wxDragImage) wxDragListItem(TClass(wxListCtrl) listCtrl, long id);
TClass(wxDragImage) wxDragString(TClass(wxString) text, int x, int y);
TClass(wxDragImage) wxDragTreeItem(TClass(wxTreeCtrl) treeCtrl, TClass(wxTreeItemId) id);
TClass(wxGenericDragImage) wxGenericDragIcon(TClass(wxIcon) icon);
TClass(wxGenericDragImage) wxGenericDragListItem(TClass(wxListCtrl) listCtrl, long id);
TClass(wxGenericDragImage) wxGenericDragString(TClass(wxString) text);
TClass(wxGenericDragImage)
    wxGenericDragTreeItem(TClass(wxTreeCtrl) treeCtrl, TClass(wxTreeItemId) id);
TClass(wxString) wxGetApplicationDir();
TClass(wxString) wxGetApplicationPath();
void wxGetColourFromUser(TClass(wxWindow) parent, TClass(wxColour) colInit,
                         TClass(wxColour) colour);
void wxGetFontFromUser(TClass(wxWindow) parent, TClass(wxFont) fontInit, TClass(wxFont) font);
long wxGetNumberFromUser(TClass(wxString) message, TClass(wxString) prompt,
                         TClass(wxString) caption, long value, long min, long max,
                         TClass(wxWindow) parent, int x, int y);
int wxGetPasswordFromUser(TString message, TString caption, TString defaultText,
                          TClass(wxWindow) parent, TString buffer);
int wxGetTextFromUser(TString message, TString caption, TString defaultText,
                      TClass(wxWindow) parent, int x, int y, int center, TString buffer);
int wxIsDefined(TString name);
int wxVersionNumber();
TClass(wxString) wxVersionString();
