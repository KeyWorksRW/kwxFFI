#pragma once

// wxWidgets HTML module (Wx::HTML parity).
// Classes that already have a parent-only block in kwx_classes.h are extended here; kwxgen
// merges repeated class blocks by class name, so a block in this header adds methods to the
// existing class.

TClassDefExtend(wxHtmlWindow,
                wxScrolledWindow) void* wxHtmlWindow_GetParser(TSelf(wxHtmlWindow) pObject);
TBool wxHtmlWindow_LoadFile(TSelf(wxHtmlWindow) pObject, TClass(wxFileName) filename);
void wxHtmlWindow_SelectAll(TSelf(wxHtmlWindow) pObject);
void wxHtmlWindow_SelectLine(TSelf(wxHtmlWindow) pObject, TPoint(x, y));
void wxHtmlWindow_SelectWord(TSelf(wxHtmlWindow) pObject, TPoint(x, y));
TClass(wxString) wxHtmlWindow_SelectionToText(TSelf(wxHtmlWindow) pObject);
void wxHtmlWindow_SetBackgroundImage(TSelf(wxHtmlWindow) pObject, TClass(wxBitmapBundle) bmpBg);
void wxHtmlWindow_SetStandardFonts(TSelf(wxHtmlWindow) pObject, int size,
                                   TClass(wxString) normal_face, TClass(wxString) fixed_face);
TClass(wxString) wxHtmlWindow_ToText(TSelf(wxHtmlWindow) pObject);

TClassDefExtend(wxHtmlCell, wxObject) TClass(wxHtmlCell) wxHtmlCell_Create();
void wxHtmlCell_Delete(TSelf(wxHtmlCell) pObject);
void wxHtmlCell_SetParent(TSelf(wxHtmlCell) pObject, void* parent);
void* wxHtmlCell_GetParent(TSelf(wxHtmlCell) pObject);
int wxHtmlCell_GetPosX(TSelf(wxHtmlCell) pObject);
int wxHtmlCell_GetPosY(TSelf(wxHtmlCell) pObject);
int wxHtmlCell_GetWidth(TSelf(wxHtmlCell) pObject);
int wxHtmlCell_GetMaxTotalWidth(TSelf(wxHtmlCell) pObject);
int wxHtmlCell_GetHeight(TSelf(wxHtmlCell) pObject);
int wxHtmlCell_GetDescent(TSelf(wxHtmlCell) pObject);
void wxHtmlCell_SetCanLiveOnPagebreak(TSelf(wxHtmlCell) pObject, TBool can);
TBool wxHtmlCell_IsLinebreakAllowed(TSelf(wxHtmlCell) pObject);
TBool wxHtmlCell_IsTerminalCell(TSelf(wxHtmlCell) pObject);
void wxHtmlCell_SetScriptMode(TSelf(wxHtmlCell) pObject, int mode, long previousBase);
int wxHtmlCell_GetScriptMode(TSelf(wxHtmlCell) pObject);
long wxHtmlCell_GetScriptBaseline(TSelf(wxHtmlCell) pObject);
TBool wxHtmlCell_IsFormattingCell(TSelf(wxHtmlCell) pObject);
TClass(wxString) wxHtmlCell_GetId(TSelf(wxHtmlCell) pObject);
TBool wxHtmlCell_HasId(TSelf(wxHtmlCell) pObject);
void wxHtmlCell_SetId(TSelf(wxHtmlCell) pObject, TClass(wxString) id);
void* wxHtmlCell_GetLink(TSelf(wxHtmlCell) pObject, TPoint(x, y));
void* wxHtmlCell_GetNext(TSelf(wxHtmlCell) pObject);
void* wxHtmlCell_GetFirstChild(TSelf(wxHtmlCell) pObject);
void wxHtmlCell_SetPos(TSelf(wxHtmlCell) pObject, TPoint(x, y));
void wxHtmlCell_SetLink(TSelf(wxHtmlCell) pObject, void* link);
void wxHtmlCell_SetNext(TSelf(wxHtmlCell) pObject, void* cell);
void wxHtmlCell_Layout(TSelf(wxHtmlCell) pObject, int width);
void* wxHtmlCell_FindCellByPos(TSelf(wxHtmlCell) pObject, int x, int y, unsigned flags);
TClass(wxPoint) wxHtmlCell_GetAbsPos(TSelf(wxHtmlCell) pObject, void* rootCell);
TClass(wxRect) wxHtmlCell_GetRect(TSelf(wxHtmlCell) pObject, void* rootCell);
void* wxHtmlCell_GetRootCell(TSelf(wxHtmlCell) pObject);
void* wxHtmlCell_GetFirstTerminal(TSelf(wxHtmlCell) pObject);
void* wxHtmlCell_GetLastTerminal(TSelf(wxHtmlCell) pObject);
unsigned wxHtmlCell_GetDepth(TSelf(wxHtmlCell) pObject);
TBool wxHtmlCell_IsBefore(TSelf(wxHtmlCell) pObject, void* cell);
TClass(wxString) wxHtmlCell_ConvertToText(TSelf(wxHtmlCell) pObject, void* sel);
TClass(wxString) wxHtmlCell_Dump(TSelf(wxHtmlCell) pObject, int indent);

TClassDefExtend(wxHtmlCellEvent,
                wxCommandEvent) void* wxHtmlCellEvent_GetCell(TSelf(wxHtmlCellEvent) pObject);
TClass(wxPoint) wxHtmlCellEvent_GetPoint(TSelf(wxHtmlCellEvent) pObject);
void* wxHtmlCellEvent_GetMouseEvent(TSelf(wxHtmlCellEvent) pObject);
void wxHtmlCellEvent_SetLinkClicked(TSelf(wxHtmlCellEvent) pObject, TBool linkClicked);
TBool wxHtmlCellEvent_GetLinkClicked(TSelf(wxHtmlCellEvent) pObject);

TClassDefExtend(wxHtmlLinkEvent,
                wxCommandEvent) void* wxHtmlLinkEvent_GetLinkInfo(TSelf(wxHtmlLinkEvent) pObject);

TClassDefExtend(wxHtmlHelpData, wxObject) TClass(wxHtmlHelpData) wxHtmlHelpData_Create();
void wxHtmlHelpData_Delete(TSelf(wxHtmlHelpData) pObject);
TBool wxHtmlHelpData_AddBook(TSelf(wxHtmlHelpData) pObject, TClass(wxString) book);
TClass(wxString) wxHtmlHelpData_FindPageById(TSelf(wxHtmlHelpData) pObject, int id);
TClass(wxString)
    wxHtmlHelpData_FindPageByName(TSelf(wxHtmlHelpData) pObject, TClass(wxString) page);
void wxHtmlHelpData_SetTempDir(TSelf(wxHtmlHelpData) pObject, TClass(wxString) path);
void* wxHtmlHelpData_GetBookRecArray(TSelf(wxHtmlHelpData) pObject);
void* wxHtmlHelpData_GetContentsArray(TSelf(wxHtmlHelpData) pObject);
void* wxHtmlHelpData_GetIndexArray(TSelf(wxHtmlHelpData) pObject);

TClassDefExtend(wxHtmlHelpWindow, wxWindow) TClass(wxHtmlHelpWindow)
    wxHtmlHelpWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style,
                            int helpStyle);
void wxHtmlHelpWindow_Delete(TSelf(wxHtmlHelpWindow) pObject);
TBool wxHtmlHelpWindow_Display(TSelf(wxHtmlHelpWindow) pObject, TClass(wxString) x);
TBool wxHtmlHelpWindow_DisplayNumber(TSelf(wxHtmlHelpWindow) pObject, int id);
TBool wxHtmlHelpWindow_DisplayContents(TSelf(wxHtmlHelpWindow) pObject);
TBool wxHtmlHelpWindow_DisplayIndex(TSelf(wxHtmlHelpWindow) pObject);
TBool wxHtmlHelpWindow_KeywordSearch(TSelf(wxHtmlHelpWindow) pObject, TClass(wxString) keyword,
                                     int mode);
void wxHtmlHelpWindow_ReadCustomization(TSelf(wxHtmlHelpWindow) pObject, TClass(wxConfigBase) cfg,
                                        TClass(wxString) path);
void wxHtmlHelpWindow_WriteCustomization(TSelf(wxHtmlHelpWindow) pObject, TClass(wxConfigBase) cfg,
                                         TClass(wxString) path);
void wxHtmlHelpWindow_UseConfig(TSelf(wxHtmlHelpWindow) pObject, TClass(wxConfigBase) config,
                                TClass(wxString) rootPath);
void wxHtmlHelpWindow_NotifyPageChanged(TSelf(wxHtmlHelpWindow) pObject);
void wxHtmlHelpWindow_RefreshLists(TSelf(wxHtmlHelpWindow) pObject);
void* wxHtmlHelpWindow_GetData(TSelf(wxHtmlHelpWindow) pObject);
void* wxHtmlHelpWindow_GetController(TSelf(wxHtmlHelpWindow) pObject);
void wxHtmlHelpWindow_SetController(TSelf(wxHtmlHelpWindow) pObject, void* controller);
void* wxHtmlHelpWindow_GetHtmlWindow(TSelf(wxHtmlHelpWindow) pObject);
void* wxHtmlHelpWindow_GetSplitterWindow(TSelf(wxHtmlHelpWindow) pObject);
void* wxHtmlHelpWindow_GetToolBar(TSelf(wxHtmlHelpWindow) pObject);
void* wxHtmlHelpWindow_GetTreeCtrl(TSelf(wxHtmlHelpWindow) pObject);

TClassDefExtend(wxHtmlEasyPrinting, wxObject) TClass(wxHtmlEasyPrinting)
    wxHtmlEasyPrinting_Create(TClass(wxString) name, TClass(wxWindow) parentWindow);
void wxHtmlEasyPrinting_Delete(TSelf(wxHtmlEasyPrinting) pObject);
TBool wxHtmlEasyPrinting_PreviewFile(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) htmlfile);
TBool wxHtmlEasyPrinting_PreviewText(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) htmltext,
                                     TClass(wxString) basepath);
TBool wxHtmlEasyPrinting_PrintFile(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) htmlfile);
TBool wxHtmlEasyPrinting_PrintText(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) htmltext,
                                   TClass(wxString) basepath);
void wxHtmlEasyPrinting_PageSetup(TSelf(wxHtmlEasyPrinting) pObject);
void wxHtmlEasyPrinting_SetHeader(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) header,
                                  int pg);
void wxHtmlEasyPrinting_SetFooter(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) footer,
                                  int pg);
void wxHtmlEasyPrinting_SetFonts(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) normal_face,
                                 TClass(wxString) fixed_face, int* sizes);
void wxHtmlEasyPrinting_SetStandardFonts(TSelf(wxHtmlEasyPrinting) pObject, int size,
                                         TClass(wxString) normal_face, TClass(wxString) fixed_face);
void* wxHtmlEasyPrinting_GetPrintData(TSelf(wxHtmlEasyPrinting) pObject);
void* wxHtmlEasyPrinting_GetPageSetupData(TSelf(wxHtmlEasyPrinting) pObject);
void* wxHtmlEasyPrinting_GetParentWindow(TSelf(wxHtmlEasyPrinting) pObject);
void wxHtmlEasyPrinting_SetParentWindow(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxWindow) window);
TClass(wxString) wxHtmlEasyPrinting_GetName(TSelf(wxHtmlEasyPrinting) pObject);
void wxHtmlEasyPrinting_SetName(TSelf(wxHtmlEasyPrinting) pObject, TClass(wxString) name);
void wxHtmlEasyPrinting_SetPromptMode(TSelf(wxHtmlEasyPrinting) pObject, int promptMode);

TClassDefExtend(wxHtmlPrintout, wxPrintout) TClass(wxHtmlPrintout)
    wxHtmlPrintout_Create(TClass(wxString) title);
void wxHtmlPrintout_Delete(TSelf(wxHtmlPrintout) pObject);
void wxHtmlPrintout_SetHtmlFile(TSelf(wxHtmlPrintout) pObject, TClass(wxString) htmlfile);
void wxHtmlPrintout_SetHtmlText(TSelf(wxHtmlPrintout) pObject, TClass(wxString) html,
                                TClass(wxString) basepath, TBool isdir);
void wxHtmlPrintout_SetHeader(TSelf(wxHtmlPrintout) pObject, TClass(wxString) header, int pg);
void wxHtmlPrintout_SetFooter(TSelf(wxHtmlPrintout) pObject, TClass(wxString) footer, int pg);
void wxHtmlPrintout_SetFonts(TSelf(wxHtmlPrintout) pObject, TClass(wxString) normal_face,
                             TClass(wxString) fixed_face, int* sizes);
void wxHtmlPrintout_SetStandardFonts(TSelf(wxHtmlPrintout) pObject, int size,
                                     TClass(wxString) normal_face, TClass(wxString) fixed_face);
void wxHtmlPrintout_SetMargins(TSelf(wxHtmlPrintout) pObject, float top, float bottom, float left,
                               float right, float spaces);

TClassDefExtend(wxHtmlListBox, wxVListBox) void wxHtmlListBox_RefreshRow(TSelf(wxHtmlListBox)
                                                                             pObject,
                                                                         size_t line);
void wxHtmlListBox_RefreshRows(TSelf(wxHtmlListBox) pObject, size_t from, size_t toPos);
void wxHtmlListBox_RefreshAll(TSelf(wxHtmlListBox) pObject);
void wxHtmlListBox_SetItemCount(TSelf(wxHtmlListBox) pObject, size_t count);
void* wxHtmlListBox_GetFileSystem(TSelf(wxHtmlListBox) pObject);

TClassDefExtend(wxHTMLDataObject, wxDataObjectSimple) TClass(wxHTMLDataObject)
    wxHTMLDataObject_Create(TClass(wxString) html);
void wxHTMLDataObject_Delete(TSelf(wxHTMLDataObject) pObject);
TClass(wxString) wxHTMLDataObject_GetHTML(TSelf(wxHTMLDataObject) pObject);
void wxHTMLDataObject_SetHTML(TSelf(wxHTMLDataObject) pObject, TClass(wxString) html);
size_t wxHTMLDataObject_GetLength(TSelf(wxHTMLDataObject) pObject);
