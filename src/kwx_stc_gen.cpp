#include "kwx_wrapper.h"

#include <wx/stc/stc.h>

extern "C" EXPORT void wxStyledTextCtrl_AddText(void* pObject, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->AddText(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_AddStyledText(void* pObject, void* data)
{
    ((wxStyledTextCtrl*) pObject)->AddStyledText(*(wxMemoryBuffer*) data);
}
extern "C" EXPORT void wxStyledTextCtrl_InsertText(void* pObject, int pos, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->InsertText(pos, *text);
}
extern "C" EXPORT void wxStyledTextCtrl_ClearAll(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->ClearAll();
}
extern "C" EXPORT void wxStyledTextCtrl_ClearDocumentStyle(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->ClearDocumentStyle();
}
extern "C" EXPORT int wxStyledTextCtrl_GetLength(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetLength();
}
extern "C" EXPORT int wxStyledTextCtrl_GetCharAt(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->GetCharAt(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCurrentPos(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetCurrentPos();
}
extern "C" EXPORT int wxStyledTextCtrl_GetAnchor(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetAnchor();
}
extern "C" EXPORT int wxStyledTextCtrl_GetStyleAt(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->GetStyleAt(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_Redo(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->Redo();
}
extern "C" EXPORT void wxStyledTextCtrl_SetUndoCollection(void* pObject, bool collectUndo)
{
    ((wxStyledTextCtrl*) pObject)->SetUndoCollection(collectUndo);
}
extern "C" EXPORT void wxStyledTextCtrl_SelectAll(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->SelectAll();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSavePoint(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->SetSavePoint();
}
extern "C" EXPORT bool wxStyledTextCtrl_CanRedo(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->CanRedo();
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerLineFromHandle(void* pObject, int handle)
{
    return ((wxStyledTextCtrl*) pObject)->MarkerLineFromHandle(handle);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDeleteHandle(void* pObject, int handle)
{
    ((wxStyledTextCtrl*) pObject)->MarkerDeleteHandle(handle);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUndoCollection(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetUndoCollection();
}
extern "C" EXPORT int wxStyledTextCtrl_GetViewWhiteSpace(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetViewWhiteSpace();
}
extern "C" EXPORT void wxStyledTextCtrl_SetViewWhiteSpace(void* pObject, int viewWS)
{
    ((wxStyledTextCtrl*) pObject)->SetViewWhiteSpace(viewWS);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionFromPoint(void* pObject, int pt_x, int pt_y)
{
    return ((wxStyledTextCtrl*) pObject)->PositionFromPoint(wxPoint(pt_x, pt_y));
}
extern "C" EXPORT int wxStyledTextCtrl_PositionFromPointClose(void* pObject, int x, int y)
{
    return ((wxStyledTextCtrl*) pObject)->PositionFromPointClose(x, y);
}
extern "C" EXPORT void wxStyledTextCtrl_GotoLine(void* pObject, int line)
{
    ((wxStyledTextCtrl*) pObject)->GotoLine(line);
}
extern "C" EXPORT void wxStyledTextCtrl_GotoPos(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->GotoPos(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetAnchor(void* pObject, int posAnchor)
{
    ((wxStyledTextCtrl*) pObject)->SetAnchor(posAnchor);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEndStyled(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetEndStyled();
}
extern "C" EXPORT void wxStyledTextCtrl_ConvertEOLs(void* pObject, int eolMode)
{
    ((wxStyledTextCtrl*) pObject)->ConvertEOLs(eolMode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEOLMode(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetEOLMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetEOLMode(void* pObject, int eolMode)
{
    ((wxStyledTextCtrl*) pObject)->SetEOLMode(eolMode);
}
extern "C" EXPORT void wxStyledTextCtrl_StartStyling(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->StartStyling(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetStyling(void* pObject, int length, int style)
{
    ((wxStyledTextCtrl*) pObject)->SetStyling(length, style);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetBufferedDraw(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetBufferedDraw();
}
extern "C" EXPORT void wxStyledTextCtrl_SetBufferedDraw(void* pObject, bool buffered)
{
    ((wxStyledTextCtrl*) pObject)->SetBufferedDraw(buffered);
}
extern "C" EXPORT void wxStyledTextCtrl_SetTabWidth(void* pObject, int tabWidth)
{
    ((wxStyledTextCtrl*) pObject)->SetTabWidth(tabWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTabWidth(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetTabWidth();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCodePage(void* pObject, int codePage)
{
    ((wxStyledTextCtrl*) pObject)->SetCodePage(codePage);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDefine(void* pObject, int markerNumber, int markerSymbol,
                                                     int foreground_r, int foreground_g,
                                                     int foreground_b, int background_r,
                                                     int background_g, int background_b)
{
    ((wxStyledTextCtrl*) pObject)
        ->MarkerDefine(markerNumber, markerSymbol,
                       wxColour(foreground_r, foreground_g, foreground_b),
                       wxColour(background_r, background_g, background_b));
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerSetForeground(void* pObject, int markerNumber,
                                                            int fore_r, int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->MarkerSetForeground(markerNumber, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerSetBackground(void* pObject, int markerNumber,
                                                            int back_r, int back_g, int back_b)
{
    ((wxStyledTextCtrl*) pObject)->MarkerSetBackground(markerNumber, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerAdd(void* pObject, int line, int markerNumber)
{
    return ((wxStyledTextCtrl*) pObject)->MarkerAdd(line, markerNumber);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDelete(void* pObject, int line, int markerNumber)
{
    ((wxStyledTextCtrl*) pObject)->MarkerDelete(line, markerNumber);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDeleteAll(void* pObject, int markerNumber)
{
    ((wxStyledTextCtrl*) pObject)->MarkerDeleteAll(markerNumber);
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerGet(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->MarkerGet(line);
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerNext(void* pObject, int lineStart, int markerMask)
{
    return ((wxStyledTextCtrl*) pObject)->MarkerNext(lineStart, markerMask);
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerPrevious(void* pObject, int lineStart, int markerMask)
{
    return ((wxStyledTextCtrl*) pObject)->MarkerPrevious(lineStart, markerMask);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDefineBitmap(void* pObject, int markerNumber, void* bmp)
{
    ((wxStyledTextCtrl*) pObject)->MarkerDefineBitmap(markerNumber, *(wxBitmap*) bmp);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginType(void* pObject, int margin, int marginType)
{
    ((wxStyledTextCtrl*) pObject)->SetMarginType(margin, marginType);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginType(void* pObject, int margin)
{
    return ((wxStyledTextCtrl*) pObject)->GetMarginType(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginWidth(void* pObject, int margin, int pixelWidth)
{
    ((wxStyledTextCtrl*) pObject)->SetMarginWidth(margin, pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginWidth(void* pObject, int margin)
{
    return ((wxStyledTextCtrl*) pObject)->GetMarginWidth(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginMask(void* pObject, int margin, int mask)
{
    ((wxStyledTextCtrl*) pObject)->SetMarginMask(margin, mask);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginMask(void* pObject, int margin)
{
    return ((wxStyledTextCtrl*) pObject)->GetMarginMask(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginSensitive(void* pObject, int margin, bool sensitive)
{
    ((wxStyledTextCtrl*) pObject)->SetMarginSensitive(margin, sensitive);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetMarginSensitive(void* pObject, int margin)
{
    return ((wxStyledTextCtrl*) pObject)->GetMarginSensitive(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleClearAll(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->StyleClearAll();
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetForeground(void* pObject, int style, int fore_r,
                                                           int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetForeground(style, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetBackground(void* pObject, int style, int back_r,
                                                           int back_g, int back_b)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetBackground(style, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetBold(void* pObject, int style, bool bold)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetBold(style, bold);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetItalic(void* pObject, int style, bool italic)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetItalic(style, italic);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetSize(void* pObject, int style, int sizePoints)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetSize(style, sizePoints);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetFaceName(void* pObject, int style, wxString* fontName)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetFaceName(style, *fontName);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetEOLFilled(void* pObject, int style, bool filled)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetEOLFilled(style, filled);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleResetDefault(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->StyleResetDefault();
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetUnderline(void* pObject, int style, bool underline)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetUnderline(style, underline);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetCase(void* pObject, int style, int caseForce)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetCase(style, caseForce);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetCharacterSet(void* pObject, int style,
                                                             int characterSet)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetCharacterSet(style, characterSet);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetHotSpot(void* pObject, int style, bool hotspot)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetHotSpot(style, hotspot);
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelForeground(void* pObject, bool useSetting, int fore_r,
                                                         int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->SetSelForeground(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelBackground(void* pObject, bool useSetting, int back_r,
                                                         int back_g, int back_b)
{
    ((wxStyledTextCtrl*) pObject)->SetSelBackground(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretForeground(void* pObject, int fore_r, int fore_g,
                                                           int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->SetCaretForeground(wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyAssign(void* pObject, int key, int modifiers, int cmd)
{
    ((wxStyledTextCtrl*) pObject)->CmdKeyAssign(key, modifiers, cmd);
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyClear(void* pObject, int key, int modifiers)
{
    ((wxStyledTextCtrl*) pObject)->CmdKeyClear(key, modifiers);
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyClearAll(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->CmdKeyClearAll();
}
extern "C" EXPORT void wxStyledTextCtrl_SetStyleBytes(void* pObject, int length, void* styleBytes)
{
    ((wxStyledTextCtrl*) pObject)->SetStyleBytes(length, *(char**) styleBytes);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetVisible(void* pObject, int style, bool visible)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetVisible(style, visible);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCaretPeriod(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetCaretPeriod();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretPeriod(void* pObject, int periodMilliseconds)
{
    ((wxStyledTextCtrl*) pObject)->SetCaretPeriod(periodMilliseconds);
}
extern "C" EXPORT void wxStyledTextCtrl_SetWordChars(void* pObject, wxString* characters)
{
    ((wxStyledTextCtrl*) pObject)->SetWordChars(*characters);
}
extern "C" EXPORT void wxStyledTextCtrl_BeginUndoAction(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->BeginUndoAction();
}
extern "C" EXPORT void wxStyledTextCtrl_EndUndoAction(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->EndUndoAction();
}
extern "C" EXPORT void wxStyledTextCtrl_IndicatorSetStyle(void* pObject, int indic, int style)
{
    ((wxStyledTextCtrl*) pObject)->IndicatorSetStyle(indic, style);
}
extern "C" EXPORT int wxStyledTextCtrl_IndicatorGetStyle(void* pObject, int indic)
{
    return ((wxStyledTextCtrl*) pObject)->IndicatorGetStyle(indic);
}
extern "C" EXPORT void wxStyledTextCtrl_IndicatorSetForeground(void* pObject, int indic, int fore_r,
                                                               int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->IndicatorSetForeground(indic, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetWhitespaceForeground(void* pObject, bool useSetting,
                                                                int fore_r, int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)
        ->SetWhitespaceForeground(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetWhitespaceBackground(void* pObject, bool useSetting,
                                                                int back_r, int back_g, int back_b)
{
    ((wxStyledTextCtrl*) pObject)
        ->SetWhitespaceBackground(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetLineState(void* pObject, int line, int state)
{
    ((wxStyledTextCtrl*) pObject)->SetLineState(line, state);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineState(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetLineState(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMaxLineState(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetMaxLineState();
}
extern "C" EXPORT bool wxStyledTextCtrl_GetCaretLineVisible(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetCaretLineVisible();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretLineVisible(void* pObject, bool show)
{
    ((wxStyledTextCtrl*) pObject)->SetCaretLineVisible(show);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetChangeable(void* pObject, int style, bool changeable)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetChangeable(style, changeable);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompShow(void* pObject, int lenEntered, wxString* itemList)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompShow(lenEntered, *itemList);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompCancel(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompCancel();
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompActive(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompActive();
}
extern "C" EXPORT int wxStyledTextCtrl_AutoCompPosStart(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompPosStart();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompComplete(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompComplete();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompStops(void* pObject, wxString* characterSet)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompStops(*characterSet);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetSeparator(void* pObject, int separatorCharacter)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetSeparator(separatorCharacter);
}
extern "C" EXPORT int wxStyledTextCtrl_AutoCompGetSeparator(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetSeparator();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSelect(void* pObject, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSelect(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetCancelAtStart(void* pObject, bool cancel)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetCancelAtStart(cancel);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetCancelAtStart(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetCancelAtStart();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetFillUps(void* pObject, wxString* characterSet)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetFillUps(*characterSet);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetChooseSingle(void* pObject, bool chooseSingle)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetChooseSingle(chooseSingle);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetChooseSingle(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetChooseSingle();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetIgnoreCase(void* pObject, bool ignoreCase)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetIgnoreCase(ignoreCase);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetIgnoreCase(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetIgnoreCase();
}
extern "C" EXPORT void wxStyledTextCtrl_UserListShow(void* pObject, int listType, wxString* itemList)
{
    ((wxStyledTextCtrl*) pObject)->UserListShow(listType, *itemList);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetAutoHide(void* pObject, bool autoHide)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetAutoHide(autoHide);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetAutoHide(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetAutoHide();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetDropRestOfWord(void* pObject, bool dropRestOfWord)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetDropRestOfWord(dropRestOfWord);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetDropRestOfWord(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetDropRestOfWord();
}
extern "C" EXPORT void wxStyledTextCtrl_RegisterImage(void* pObject, int type, void* bmp)
{
    ((wxStyledTextCtrl*) pObject)->RegisterImage(type, *(wxBitmap*) bmp);
}
extern "C" EXPORT void wxStyledTextCtrl_ClearRegisteredImages(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->ClearRegisteredImages();
}
extern "C" EXPORT int wxStyledTextCtrl_AutoCompGetTypeSeparator(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->AutoCompGetTypeSeparator();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetTypeSeparator(void* pObject, int separatorCharacter)
{
    ((wxStyledTextCtrl*) pObject)->AutoCompSetTypeSeparator(separatorCharacter);
}
extern "C" EXPORT void wxStyledTextCtrl_SetIndent(void* pObject, int indentSize)
{
    ((wxStyledTextCtrl*) pObject)->SetIndent(indentSize);
}
extern "C" EXPORT int wxStyledTextCtrl_GetIndent(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetIndent();
}
extern "C" EXPORT void wxStyledTextCtrl_SetUseTabs(void* pObject, bool useTabs)
{
    ((wxStyledTextCtrl*) pObject)->SetUseTabs(useTabs);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUseTabs(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetUseTabs();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLineIndentation(void* pObject, int line, int indentSize)
{
    ((wxStyledTextCtrl*) pObject)->SetLineIndentation(line, indentSize);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineIndentation(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetLineIndentation(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineIndentPosition(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetLineIndentPosition(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetColumn(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->GetColumn(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetUseHorizontalScrollBar(void* pObject, bool show)
{
    ((wxStyledTextCtrl*) pObject)->SetUseHorizontalScrollBar(show);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUseHorizontalScrollBar(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetUseHorizontalScrollBar();
}
extern "C" EXPORT void wxStyledTextCtrl_SetIndentationGuides(void* pObject, bool show)
{
    ((wxStyledTextCtrl*) pObject)->SetIndentationGuides(show);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetIndentationGuides(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetIndentationGuides();
}
extern "C" EXPORT void wxStyledTextCtrl_SetHighlightGuide(void* pObject, int column)
{
    ((wxStyledTextCtrl*) pObject)->SetHighlightGuide(column);
}
extern "C" EXPORT int wxStyledTextCtrl_GetHighlightGuide(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetHighlightGuide();
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineEndPosition(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetLineEndPosition(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCodePage(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetCodePage();
}
extern "C" EXPORT bool wxStyledTextCtrl_GetReadOnly(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetReadOnly();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCurrentPos(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->SetCurrentPos(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelectionStart(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->SetSelectionStart(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSelectionStart(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetSelectionStart();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelectionEnd(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->SetSelectionEnd(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSelectionEnd(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetSelectionEnd();
}
extern "C" EXPORT void wxStyledTextCtrl_SetPrintMagnification(void* pObject, int magnification)
{
    ((wxStyledTextCtrl*) pObject)->SetPrintMagnification(magnification);
}
extern "C" EXPORT int wxStyledTextCtrl_GetPrintMagnification(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetPrintMagnification();
}
extern "C" EXPORT void wxStyledTextCtrl_SetPrintColourMode(void* pObject, int mode)
{
    ((wxStyledTextCtrl*) pObject)->SetPrintColourMode(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetPrintColourMode(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetPrintColourMode();
}
extern "C" EXPORT int wxStyledTextCtrl_FindText(void* pObject, int minPos, int maxPos, wxString* text,
                                                int flags)
{
    return ((wxStyledTextCtrl*) pObject)->FindText(minPos, maxPos, *text, flags);
}
extern "C" EXPORT int wxStyledTextCtrl_FormatRange(void* pObject, bool doDraw, int startPos,
                                                   int endPos, void* draw, void* target,
                                                   void* renderRect, void* pageRect)
{
    return ((wxStyledTextCtrl*) pObject)
        ->FormatRange(doDraw, startPos, endPos, *(wxDC**) draw, *(wxDC**) target,
                      *(wxRect*) renderRect, *(wxRect*) pageRect);
}
extern "C" EXPORT int wxStyledTextCtrl_GetFirstVisibleLine(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetFirstVisibleLine();
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineCount(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetLineCount();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginLeft(void* pObject, int pixelWidth)
{
    ((wxStyledTextCtrl*) pObject)->SetMarginLeft(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginLeft(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetMarginLeft();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginRight(void* pObject, int pixelWidth)
{
    ((wxStyledTextCtrl*) pObject)->SetMarginRight(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginRight(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetMarginRight();
}
extern "C" EXPORT bool wxStyledTextCtrl_GetModify(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetModify();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelection(void* pObject, int start, int end)
{
    ((wxStyledTextCtrl*) pObject)->SetSelection(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_HideSelection(void* pObject, bool normal)
{
    ((wxStyledTextCtrl*) pObject)->HideSelection(normal);
}
extern "C" EXPORT int wxStyledTextCtrl_LineFromPosition(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->LineFromPosition(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionFromLine(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->PositionFromLine(line);
}
extern "C" EXPORT void wxStyledTextCtrl_LineScroll(void* pObject, int columns, int lines)
{
    ((wxStyledTextCtrl*) pObject)->LineScroll(columns, lines);
}
extern "C" EXPORT void wxStyledTextCtrl_EnsureCaretVisible(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->EnsureCaretVisible();
}
extern "C" EXPORT void wxStyledTextCtrl_ReplaceSelection(void* pObject, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->ReplaceSelection(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_SetReadOnly(void* pObject, bool readOnly)
{
    ((wxStyledTextCtrl*) pObject)->SetReadOnly(readOnly);
}
extern "C" EXPORT bool wxStyledTextCtrl_CanPaste(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->CanPaste();
}
extern "C" EXPORT bool wxStyledTextCtrl_CanUndo(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->CanUndo();
}
extern "C" EXPORT void wxStyledTextCtrl_EmptyUndoBuffer(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->EmptyUndoBuffer();
}
extern "C" EXPORT void wxStyledTextCtrl_Undo(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->Undo();
}
extern "C" EXPORT void wxStyledTextCtrl_Cut(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->Cut();
}
extern "C" EXPORT void wxStyledTextCtrl_Copy(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->Copy();
}
extern "C" EXPORT void wxStyledTextCtrl_Paste(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->Paste();
}
extern "C" EXPORT void wxStyledTextCtrl_Clear(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->Clear();
}
extern "C" EXPORT void wxStyledTextCtrl_SetText(void* pObject, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->SetText(*text);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTextLength(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetTextLength();
}
extern "C" EXPORT void wxStyledTextCtrl_SetOvertype(void* pObject, bool overtype)
{
    ((wxStyledTextCtrl*) pObject)->SetOvertype(overtype);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetOvertype(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetOvertype();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretWidth(void* pObject, int pixelWidth)
{
    ((wxStyledTextCtrl*) pObject)->SetCaretWidth(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCaretWidth(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetCaretWidth();
}
extern "C" EXPORT void wxStyledTextCtrl_SetTargetStart(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->SetTargetStart(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTargetStart(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetTargetStart();
}
extern "C" EXPORT void wxStyledTextCtrl_SetTargetEnd(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->SetTargetEnd(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTargetEnd(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetTargetEnd();
}
extern "C" EXPORT int wxStyledTextCtrl_ReplaceTarget(void* pObject, wxString* text)
{
    return ((wxStyledTextCtrl*) pObject)->ReplaceTarget(*text);
}
extern "C" EXPORT int wxStyledTextCtrl_ReplaceTargetRE(void* pObject, wxString* text)
{
    return ((wxStyledTextCtrl*) pObject)->ReplaceTargetRE(*text);
}
extern "C" EXPORT int wxStyledTextCtrl_SearchInTarget(void* pObject, wxString* text)
{
    return ((wxStyledTextCtrl*) pObject)->SearchInTarget(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_SetSearchFlags(void* pObject, int flags)
{
    ((wxStyledTextCtrl*) pObject)->SetSearchFlags(flags);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSearchFlags(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetSearchFlags();
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipShow(void* pObject, int pos, wxString* definition)
{
    ((wxStyledTextCtrl*) pObject)->CallTipShow(pos, *definition);
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipCancel(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->CallTipCancel();
}
extern "C" EXPORT bool wxStyledTextCtrl_CallTipActive(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->CallTipActive();
}
extern "C" EXPORT int wxStyledTextCtrl_CallTipPosAtStart(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->CallTipPosAtStart();
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetHighlight(void* pObject, int start, int end)
{
    ((wxStyledTextCtrl*) pObject)->CallTipSetHighlight(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetBackground(void* pObject, int back_r, int back_g,
                                                             int back_b)
{
    ((wxStyledTextCtrl*) pObject)->CallTipSetBackground(wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetForeground(void* pObject, int fore_r, int fore_g,
                                                             int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->CallTipSetForeground(wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetForegroundHighlight(void* pObject, int fore_r,
                                                                      int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->CallTipSetForegroundHighlight(wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT int wxStyledTextCtrl_VisibleFromDocLine(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->VisibleFromDocLine(line);
}
extern "C" EXPORT int wxStyledTextCtrl_DocLineFromVisible(void* pObject, int lineDisplay)
{
    return ((wxStyledTextCtrl*) pObject)->DocLineFromVisible(lineDisplay);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldLevel(void* pObject, int line, int level)
{
    ((wxStyledTextCtrl*) pObject)->SetFoldLevel(line, level);
}
extern "C" EXPORT int wxStyledTextCtrl_GetFoldLevel(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetFoldLevel(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLastChild(void* pObject, int line, int level)
{
    return ((wxStyledTextCtrl*) pObject)->GetLastChild(line, level);
}
extern "C" EXPORT int wxStyledTextCtrl_GetFoldParent(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetFoldParent(line);
}
extern "C" EXPORT void wxStyledTextCtrl_ShowLines(void* pObject, int lineStart, int lineEnd)
{
    ((wxStyledTextCtrl*) pObject)->ShowLines(lineStart, lineEnd);
}
extern "C" EXPORT void wxStyledTextCtrl_HideLines(void* pObject, int lineStart, int lineEnd)
{
    ((wxStyledTextCtrl*) pObject)->HideLines(lineStart, lineEnd);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetLineVisible(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetLineVisible(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldExpanded(void* pObject, int line, bool expanded)
{
    ((wxStyledTextCtrl*) pObject)->SetFoldExpanded(line, expanded);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetFoldExpanded(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->GetFoldExpanded(line);
}
extern "C" EXPORT void wxStyledTextCtrl_ToggleFold(void* pObject, int line)
{
    ((wxStyledTextCtrl*) pObject)->ToggleFold(line);
}
extern "C" EXPORT void wxStyledTextCtrl_EnsureVisible(void* pObject, int line)
{
    ((wxStyledTextCtrl*) pObject)->EnsureVisible(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldFlags(void* pObject, int flags)
{
    ((wxStyledTextCtrl*) pObject)->SetFoldFlags(flags);
}
extern "C" EXPORT void wxStyledTextCtrl_EnsureVisibleEnforcePolicy(void* pObject, int line)
{
    ((wxStyledTextCtrl*) pObject)->EnsureVisibleEnforcePolicy(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetTabIndents(void* pObject, bool tabIndents)
{
    ((wxStyledTextCtrl*) pObject)->SetTabIndents(tabIndents);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetTabIndents(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetTabIndents();
}
extern "C" EXPORT void wxStyledTextCtrl_SetBackSpaceUnIndents(void* pObject, bool bsUnIndents)
{
    ((wxStyledTextCtrl*) pObject)->SetBackSpaceUnIndents(bsUnIndents);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetBackSpaceUnIndents(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetBackSpaceUnIndents();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMouseDwellTime(void* pObject, int periodMilliseconds)
{
    ((wxStyledTextCtrl*) pObject)->SetMouseDwellTime(periodMilliseconds);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMouseDwellTime(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetMouseDwellTime();
}
extern "C" EXPORT int wxStyledTextCtrl_WordStartPosition(void* pObject, int pos,
                                                         bool onlyWordCharacters)
{
    return ((wxStyledTextCtrl*) pObject)->WordStartPosition(pos, onlyWordCharacters);
}
extern "C" EXPORT int wxStyledTextCtrl_WordEndPosition(void* pObject, int pos, bool onlyWordCharacters)
{
    return ((wxStyledTextCtrl*) pObject)->WordEndPosition(pos, onlyWordCharacters);
}
extern "C" EXPORT void wxStyledTextCtrl_SetWrapMode(void* pObject, int mode)
{
    ((wxStyledTextCtrl*) pObject)->SetWrapMode(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetWrapMode(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetWrapMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLayoutCache(void* pObject, int mode)
{
    ((wxStyledTextCtrl*) pObject)->SetLayoutCache(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLayoutCache(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetLayoutCache();
}
extern "C" EXPORT void wxStyledTextCtrl_SetScrollWidth(void* pObject, int pixelWidth)
{
    ((wxStyledTextCtrl*) pObject)->SetScrollWidth(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetScrollWidth(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetScrollWidth();
}
extern "C" EXPORT int wxStyledTextCtrl_TextWidth(void* pObject, int style, wxString* text)
{
    return ((wxStyledTextCtrl*) pObject)->TextWidth(style, *text);
}
extern "C" EXPORT void wxStyledTextCtrl_SetEndAtLastLine(void* pObject, bool endAtLastLine)
{
    ((wxStyledTextCtrl*) pObject)->SetEndAtLastLine(endAtLastLine);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEndAtLastLine(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetEndAtLastLine();
}
extern "C" EXPORT int wxStyledTextCtrl_TextHeight(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->TextHeight(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetUseVerticalScrollBar(void* pObject, bool show)
{
    ((wxStyledTextCtrl*) pObject)->SetUseVerticalScrollBar(show);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUseVerticalScrollBar(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetUseVerticalScrollBar();
}
extern "C" EXPORT void wxStyledTextCtrl_AppendText(void* pObject, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->AppendText(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_TargetFromSelection(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->TargetFromSelection();
}
extern "C" EXPORT void wxStyledTextCtrl_LinesJoin(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->LinesJoin();
}
extern "C" EXPORT void wxStyledTextCtrl_LinesSplit(void* pObject, int pixelWidth)
{
    ((wxStyledTextCtrl*) pObject)->LinesSplit(pixelWidth);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldMarginColour(void* pObject, bool useSetting, int back_r,
                                                            int back_g, int back_b)
{
    ((wxStyledTextCtrl*) pObject)->SetFoldMarginColour(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldMarginHiColour(void* pObject, bool useSetting,
                                                              int fore_r, int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) pObject)->SetFoldMarginHiColour(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_LineDuplicate(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->LineDuplicate();
}
extern "C" EXPORT void wxStyledTextCtrl_HomeDisplay(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->HomeDisplay();
}
extern "C" EXPORT void wxStyledTextCtrl_HomeDisplayExtend(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->HomeDisplayExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_LineEndDisplay(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->LineEndDisplay();
}
extern "C" EXPORT void wxStyledTextCtrl_LineEndDisplayExtend(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->LineEndDisplayExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_LineCopy(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->LineCopy();
}
extern "C" EXPORT void wxStyledTextCtrl_MoveCaretInsideView(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->MoveCaretInsideView();
}
extern "C" EXPORT int wxStyledTextCtrl_LineLength(void* pObject, int line)
{
    return ((wxStyledTextCtrl*) pObject)->LineLength(line);
}
extern "C" EXPORT void wxStyledTextCtrl_BraceHighlight(void* pObject, int pos1, int pos2)
{
    ((wxStyledTextCtrl*) pObject)->BraceHighlight(pos1, pos2);
}
extern "C" EXPORT void wxStyledTextCtrl_BraceBadLight(void* pObject, int pos)
{
    ((wxStyledTextCtrl*) pObject)->BraceBadLight(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_BraceMatch(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->BraceMatch(pos);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetViewEOL(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetViewEOL();
}
extern "C" EXPORT void wxStyledTextCtrl_SetViewEOL(void* pObject, bool visible)
{
    ((wxStyledTextCtrl*) pObject)->SetViewEOL(visible);
}
extern "C" EXPORT void wxStyledTextCtrl_SetDocPointer(void* pObject, void* docPointer)
{
    ((wxStyledTextCtrl*) pObject)->SetDocPointer(docPointer);
}
extern "C" EXPORT void wxStyledTextCtrl_SetModEventMask(void* pObject, int mask)
{
    ((wxStyledTextCtrl*) pObject)->SetModEventMask(mask);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEdgeColumn(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetEdgeColumn();
}
extern "C" EXPORT void wxStyledTextCtrl_SetEdgeColumn(void* pObject, int column)
{
    ((wxStyledTextCtrl*) pObject)->SetEdgeColumn(column);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEdgeMode(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetEdgeMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetEdgeMode(void* pObject, int mode)
{
    ((wxStyledTextCtrl*) pObject)->SetEdgeMode(mode);
}
extern "C" EXPORT void wxStyledTextCtrl_SetEdgeColour(void* pObject, int edgeColour_r,
                                                      int edgeColour_g, int edgeColour_b)
{
    ((wxStyledTextCtrl*) pObject)->SetEdgeColour(wxColour(edgeColour_r, edgeColour_g, edgeColour_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SearchAnchor(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->SearchAnchor();
}
extern "C" EXPORT int wxStyledTextCtrl_SearchNext(void* pObject, int flags, wxString* text)
{
    return ((wxStyledTextCtrl*) pObject)->SearchNext(flags, *text);
}
extern "C" EXPORT int wxStyledTextCtrl_SearchPrev(void* pObject, int flags, wxString* text)
{
    return ((wxStyledTextCtrl*) pObject)->SearchPrev(flags, *text);
}
extern "C" EXPORT int wxStyledTextCtrl_LinesOnScreen(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->LinesOnScreen();
}
extern "C" EXPORT void wxStyledTextCtrl_UsePopUp(void* pObject, bool allowPopUp)
{
    ((wxStyledTextCtrl*) pObject)->UsePopUp(allowPopUp);
}
extern "C" EXPORT bool wxStyledTextCtrl_SelectionIsRectangle(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->SelectionIsRectangle();
}
extern "C" EXPORT void wxStyledTextCtrl_SetZoom(void* pObject, int zoom)
{
    ((wxStyledTextCtrl*) pObject)->SetZoom(zoom);
}
extern "C" EXPORT int wxStyledTextCtrl_GetZoom(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetZoom();
}
extern "C" EXPORT void wxStyledTextCtrl_AddRefDocument(void* pObject, void* docPointer)
{
    ((wxStyledTextCtrl*) pObject)->AddRefDocument(docPointer);
}
extern "C" EXPORT void wxStyledTextCtrl_ReleaseDocument(void* pObject, void* docPointer)
{
    ((wxStyledTextCtrl*) pObject)->ReleaseDocument(docPointer);
}
extern "C" EXPORT int wxStyledTextCtrl_GetModEventMask(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetModEventMask();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSTCFocus(void* pObject, bool focus)
{
    ((wxStyledTextCtrl*) pObject)->SetSTCFocus(focus);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetSTCFocus(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetSTCFocus();
}
extern "C" EXPORT void wxStyledTextCtrl_SetStatus(void* pObject, int statusCode)
{
    ((wxStyledTextCtrl*) pObject)->SetStatus(statusCode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetStatus(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetStatus();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMouseDownCaptures(void* pObject, bool captures)
{
    ((wxStyledTextCtrl*) pObject)->SetMouseDownCaptures(captures);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetMouseDownCaptures(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetMouseDownCaptures();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSTCCursor(void* pObject, int cursorType)
{
    ((wxStyledTextCtrl*) pObject)->SetSTCCursor(cursorType);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSTCCursor(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetSTCCursor();
}
extern "C" EXPORT void wxStyledTextCtrl_SetControlCharSymbol(void* pObject, int symbol)
{
    ((wxStyledTextCtrl*) pObject)->SetControlCharSymbol(symbol);
}
extern "C" EXPORT int wxStyledTextCtrl_GetControlCharSymbol(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetControlCharSymbol();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartLeft(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->WordPartLeft();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartLeftExtend(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->WordPartLeftExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartRight(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->WordPartRight();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartRightExtend(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->WordPartRightExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_SetVisiblePolicy(void* pObject, int visiblePolicy,
                                                         int visibleSlop)
{
    ((wxStyledTextCtrl*) pObject)->SetVisiblePolicy(visiblePolicy, visibleSlop);
}
extern "C" EXPORT void wxStyledTextCtrl_DelLineLeft(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->DelLineLeft();
}
extern "C" EXPORT void wxStyledTextCtrl_DelLineRight(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->DelLineRight();
}
extern "C" EXPORT void wxStyledTextCtrl_SetXOffset(void* pObject, int newOffset)
{
    ((wxStyledTextCtrl*) pObject)->SetXOffset(newOffset);
}
extern "C" EXPORT int wxStyledTextCtrl_GetXOffset(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetXOffset();
}
extern "C" EXPORT void wxStyledTextCtrl_ChooseCaretX(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->ChooseCaretX();
}
extern "C" EXPORT void wxStyledTextCtrl_SetXCaretPolicy(void* pObject, int caretPolicy, int caretSlop)
{
    ((wxStyledTextCtrl*) pObject)->SetXCaretPolicy(caretPolicy, caretSlop);
}
extern "C" EXPORT void wxStyledTextCtrl_SetYCaretPolicy(void* pObject, int caretPolicy, int caretSlop)
{
    ((wxStyledTextCtrl*) pObject)->SetYCaretPolicy(caretPolicy, caretSlop);
}
extern "C" EXPORT void wxStyledTextCtrl_SetPrintWrapMode(void* pObject, int mode)
{
    ((wxStyledTextCtrl*) pObject)->SetPrintWrapMode(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetPrintWrapMode(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetPrintWrapMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetHotspotActiveForeground(void* pObject, bool useSetting,
                                                                   int fore_r, int fore_g,
                                                                   int fore_b)
{
    ((wxStyledTextCtrl*) pObject)
        ->SetHotspotActiveForeground(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetHotspotActiveBackground(void* pObject, bool useSetting,
                                                                   int back_r, int back_g,
                                                                   int back_b)
{
    ((wxStyledTextCtrl*) pObject)
        ->SetHotspotActiveBackground(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetHotspotActiveUnderline(void* pObject, bool underline)
{
    ((wxStyledTextCtrl*) pObject)->SetHotspotActiveUnderline(underline);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionBefore(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->PositionBefore(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionAfter(void* pObject, int pos)
{
    return ((wxStyledTextCtrl*) pObject)->PositionAfter(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_CopyRange(void* pObject, int start, int end)
{
    ((wxStyledTextCtrl*) pObject)->CopyRange(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_CopyText(void* pObject, int length, wxString* text)
{
    ((wxStyledTextCtrl*) pObject)->CopyText(length, *text);
}
extern "C" EXPORT void wxStyledTextCtrl_StartRecord(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->StartRecord();
}
extern "C" EXPORT void wxStyledTextCtrl_StopRecord(void* pObject)
{
    ((wxStyledTextCtrl*) pObject)->StopRecord();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLexer(void* pObject, int lexer)
{
    ((wxStyledTextCtrl*) pObject)->SetLexer(lexer);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLexer(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetLexer();
}
extern "C" EXPORT void wxStyledTextCtrl_Colourise(void* pObject, int start, int end)
{
    ((wxStyledTextCtrl*) pObject)->Colourise(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_SetProperty(void* pObject, wxString* key, wxString* value)
{
    ((wxStyledTextCtrl*) pObject)->SetProperty(*key, *value);
}
extern "C" EXPORT void wxStyledTextCtrl_SetKeyWords(void* pObject, int keywordSet, wxString* keyWords)
{
    ((wxStyledTextCtrl*) pObject)->SetKeyWords(keywordSet, *keyWords);
}
extern "C" EXPORT void wxStyledTextCtrl_SetLexerLanguage(void* pObject, wxString* language)
{
    ((wxStyledTextCtrl*) pObject)->SetLexerLanguage(*language);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCurrentLine(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetCurrentLine();
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetSpec(void* pObject, int styleNum, wxString* spec)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetSpec(styleNum, *spec);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetFont(void* pObject, int styleNum, void* font)
{
    ((wxStyledTextCtrl*) pObject)->StyleSetFont(styleNum, *(wxFont*) font);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetFontAttr(void* pObject, int styleNum, int size,
                                                         wxString* faceName, bool bold, bool italic,
                                                         bool underline)
{
    ((wxStyledTextCtrl*) pObject)
        ->StyleSetFontAttr(styleNum, size, *faceName, bold, italic, underline);
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyExecute(void* pObject, int cmd)
{
    ((wxStyledTextCtrl*) pObject)->CmdKeyExecute(cmd);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMargins(void* pObject, int left, int right)
{
    ((wxStyledTextCtrl*) pObject)->SetMargins(left, right);
}
extern "C" EXPORT void wxStyledTextCtrl_GetSelection(void* pObject, void* startPos, void* endPos)
{
    ((wxStyledTextCtrl*) pObject)->GetSelection(*(int**) startPos, *(int**) endPos);
}
extern "C" EXPORT void wxStyledTextCtrl_ScrollToLine(void* pObject, int line)
{
    ((wxStyledTextCtrl*) pObject)->ScrollToLine(line);
}
extern "C" EXPORT void wxStyledTextCtrl_ScrollToColumn(void* pObject, int column)
{
    ((wxStyledTextCtrl*) pObject)->ScrollToColumn(column);
}
extern "C" EXPORT void wxStyledTextCtrl_SetVScrollBar(void* pObject, void* bar)
{
    ((wxStyledTextCtrl*) pObject)->SetVScrollBar(*(wxScrollBar**) bar);
}
extern "C" EXPORT void wxStyledTextCtrl_SetHScrollBar(void* pObject, void* bar)
{
    ((wxStyledTextCtrl*) pObject)->SetHScrollBar(*(wxScrollBar**) bar);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetLastKeydownProcessed(void* pObject)
{
    return ((wxStyledTextCtrl*) pObject)->GetLastKeydownProcessed();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLastKeydownProcessed(void* pObject, bool val)
{
    ((wxStyledTextCtrl*) pObject)->SetLastKeydownProcessed(val);
}
extern "C" EXPORT bool wxStyledTextCtrl_SaveFile(void* pObject, wxString* filename)
{
    return ((wxStyledTextCtrl*) pObject)->SaveFile(*filename);
}
extern "C" EXPORT bool wxStyledTextCtrl_LoadFile(void* pObject, wxString* filename)
{
    return ((wxStyledTextCtrl*) pObject)->LoadFile(*filename);
}
