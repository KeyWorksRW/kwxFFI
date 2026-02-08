#include "wrapper.h"

#include <wx/stc/stc.h>

extern "C" EXPORT void wxStyledTextCtrl_AddText(void* _obj, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->AddText(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_AddStyledText(void* _obj, void* data)
{
    ((wxStyledTextCtrl*) _obj)->AddStyledText(*(wxMemoryBuffer*) data);
}
extern "C" EXPORT void wxStyledTextCtrl_InsertText(void* _obj, int pos, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->InsertText(pos, *text);
}
extern "C" EXPORT void wxStyledTextCtrl_ClearAll(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->ClearAll();
}
extern "C" EXPORT void wxStyledTextCtrl_ClearDocumentStyle(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->ClearDocumentStyle();
}
extern "C" EXPORT int wxStyledTextCtrl_GetLength(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetLength();
}
extern "C" EXPORT int wxStyledTextCtrl_GetCharAt(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->GetCharAt(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCurrentPos(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetCurrentPos();
}
extern "C" EXPORT int wxStyledTextCtrl_GetAnchor(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetAnchor();
}
extern "C" EXPORT int wxStyledTextCtrl_GetStyleAt(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->GetStyleAt(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_Redo(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->Redo();
}
extern "C" EXPORT void wxStyledTextCtrl_SetUndoCollection(void* _obj, bool collectUndo)
{
    ((wxStyledTextCtrl*) _obj)->SetUndoCollection(collectUndo);
}
extern "C" EXPORT void wxStyledTextCtrl_SelectAll(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->SelectAll();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSavePoint(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->SetSavePoint();
}
extern "C" EXPORT bool wxStyledTextCtrl_CanRedo(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->CanRedo();
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerLineFromHandle(void* _obj, int handle)
{
    return ((wxStyledTextCtrl*) _obj)->MarkerLineFromHandle(handle);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDeleteHandle(void* _obj, int handle)
{
    ((wxStyledTextCtrl*) _obj)->MarkerDeleteHandle(handle);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUndoCollection(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetUndoCollection();
}
extern "C" EXPORT int wxStyledTextCtrl_GetViewWhiteSpace(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetViewWhiteSpace();
}
extern "C" EXPORT void wxStyledTextCtrl_SetViewWhiteSpace(void* _obj, int viewWS)
{
    ((wxStyledTextCtrl*) _obj)->SetViewWhiteSpace(viewWS);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionFromPoint(void* _obj, int pt_x, int pt_y)
{
    return ((wxStyledTextCtrl*) _obj)->PositionFromPoint(wxPoint(pt_x, pt_y));
}
extern "C" EXPORT int wxStyledTextCtrl_PositionFromPointClose(void* _obj, int x, int y)
{
    return ((wxStyledTextCtrl*) _obj)->PositionFromPointClose(x, y);
}
extern "C" EXPORT void wxStyledTextCtrl_GotoLine(void* _obj, int line)
{
    ((wxStyledTextCtrl*) _obj)->GotoLine(line);
}
extern "C" EXPORT void wxStyledTextCtrl_GotoPos(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->GotoPos(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetAnchor(void* _obj, int posAnchor)
{
    ((wxStyledTextCtrl*) _obj)->SetAnchor(posAnchor);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEndStyled(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetEndStyled();
}
extern "C" EXPORT void wxStyledTextCtrl_ConvertEOLs(void* _obj, int eolMode)
{
    ((wxStyledTextCtrl*) _obj)->ConvertEOLs(eolMode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEOLMode(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetEOLMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetEOLMode(void* _obj, int eolMode)
{
    ((wxStyledTextCtrl*) _obj)->SetEOLMode(eolMode);
}
extern "C" EXPORT void wxStyledTextCtrl_StartStyling(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->StartStyling(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetStyling(void* _obj, int length, int style)
{
    ((wxStyledTextCtrl*) _obj)->SetStyling(length, style);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetBufferedDraw(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetBufferedDraw();
}
extern "C" EXPORT void wxStyledTextCtrl_SetBufferedDraw(void* _obj, bool buffered)
{
    ((wxStyledTextCtrl*) _obj)->SetBufferedDraw(buffered);
}
extern "C" EXPORT void wxStyledTextCtrl_SetTabWidth(void* _obj, int tabWidth)
{
    ((wxStyledTextCtrl*) _obj)->SetTabWidth(tabWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTabWidth(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetTabWidth();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCodePage(void* _obj, int codePage)
{
    ((wxStyledTextCtrl*) _obj)->SetCodePage(codePage);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDefine(void* _obj, int markerNumber, int markerSymbol,
                                                     int foreground_r, int foreground_g,
                                                     int foreground_b, int background_r,
                                                     int background_g, int background_b)
{
    ((wxStyledTextCtrl*) _obj)
        ->MarkerDefine(markerNumber, markerSymbol,
                       wxColour(foreground_r, foreground_g, foreground_b),
                       wxColour(background_r, background_g, background_b));
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerSetForeground(void* _obj, int markerNumber,
                                                            int fore_r, int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->MarkerSetForeground(markerNumber, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerSetBackground(void* _obj, int markerNumber,
                                                            int back_r, int back_g, int back_b)
{
    ((wxStyledTextCtrl*) _obj)->MarkerSetBackground(markerNumber, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerAdd(void* _obj, int line, int markerNumber)
{
    return ((wxStyledTextCtrl*) _obj)->MarkerAdd(line, markerNumber);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDelete(void* _obj, int line, int markerNumber)
{
    ((wxStyledTextCtrl*) _obj)->MarkerDelete(line, markerNumber);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDeleteAll(void* _obj, int markerNumber)
{
    ((wxStyledTextCtrl*) _obj)->MarkerDeleteAll(markerNumber);
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerGet(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->MarkerGet(line);
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerNext(void* _obj, int lineStart, int markerMask)
{
    return ((wxStyledTextCtrl*) _obj)->MarkerNext(lineStart, markerMask);
}
extern "C" EXPORT int wxStyledTextCtrl_MarkerPrevious(void* _obj, int lineStart, int markerMask)
{
    return ((wxStyledTextCtrl*) _obj)->MarkerPrevious(lineStart, markerMask);
}
extern "C" EXPORT void wxStyledTextCtrl_MarkerDefineBitmap(void* _obj, int markerNumber, void* bmp)
{
    ((wxStyledTextCtrl*) _obj)->MarkerDefineBitmap(markerNumber, *(wxBitmap*) bmp);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginType(void* _obj, int margin, int marginType)
{
    ((wxStyledTextCtrl*) _obj)->SetMarginType(margin, marginType);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginType(void* _obj, int margin)
{
    return ((wxStyledTextCtrl*) _obj)->GetMarginType(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginWidth(void* _obj, int margin, int pixelWidth)
{
    ((wxStyledTextCtrl*) _obj)->SetMarginWidth(margin, pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginWidth(void* _obj, int margin)
{
    return ((wxStyledTextCtrl*) _obj)->GetMarginWidth(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginMask(void* _obj, int margin, int mask)
{
    ((wxStyledTextCtrl*) _obj)->SetMarginMask(margin, mask);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginMask(void* _obj, int margin)
{
    return ((wxStyledTextCtrl*) _obj)->GetMarginMask(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginSensitive(void* _obj, int margin, bool sensitive)
{
    ((wxStyledTextCtrl*) _obj)->SetMarginSensitive(margin, sensitive);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetMarginSensitive(void* _obj, int margin)
{
    return ((wxStyledTextCtrl*) _obj)->GetMarginSensitive(margin);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleClearAll(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->StyleClearAll();
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetForeground(void* _obj, int style, int fore_r,
                                                           int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetForeground(style, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetBackground(void* _obj, int style, int back_r,
                                                           int back_g, int back_b)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetBackground(style, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetBold(void* _obj, int style, bool bold)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetBold(style, bold);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetItalic(void* _obj, int style, bool italic)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetItalic(style, italic);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetSize(void* _obj, int style, int sizePoints)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetSize(style, sizePoints);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetFaceName(void* _obj, int style, wxString* fontName)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetFaceName(style, *fontName);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetEOLFilled(void* _obj, int style, bool filled)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetEOLFilled(style, filled);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleResetDefault(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->StyleResetDefault();
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetUnderline(void* _obj, int style, bool underline)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetUnderline(style, underline);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetCase(void* _obj, int style, int caseForce)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetCase(style, caseForce);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetCharacterSet(void* _obj, int style,
                                                             int characterSet)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetCharacterSet(style, characterSet);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetHotSpot(void* _obj, int style, bool hotspot)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetHotSpot(style, hotspot);
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelForeground(void* _obj, bool useSetting, int fore_r,
                                                         int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->SetSelForeground(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelBackground(void* _obj, bool useSetting, int back_r,
                                                         int back_g, int back_b)
{
    ((wxStyledTextCtrl*) _obj)->SetSelBackground(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretForeground(void* _obj, int fore_r, int fore_g,
                                                           int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->SetCaretForeground(wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyAssign(void* _obj, int key, int modifiers, int cmd)
{
    ((wxStyledTextCtrl*) _obj)->CmdKeyAssign(key, modifiers, cmd);
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyClear(void* _obj, int key, int modifiers)
{
    ((wxStyledTextCtrl*) _obj)->CmdKeyClear(key, modifiers);
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyClearAll(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->CmdKeyClearAll();
}
extern "C" EXPORT void wxStyledTextCtrl_SetStyleBytes(void* _obj, int length, void* styleBytes)
{
    ((wxStyledTextCtrl*) _obj)->SetStyleBytes(length, *(char**) styleBytes);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetVisible(void* _obj, int style, bool visible)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetVisible(style, visible);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCaretPeriod(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetCaretPeriod();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretPeriod(void* _obj, int periodMilliseconds)
{
    ((wxStyledTextCtrl*) _obj)->SetCaretPeriod(periodMilliseconds);
}
extern "C" EXPORT void wxStyledTextCtrl_SetWordChars(void* _obj, wxString* characters)
{
    ((wxStyledTextCtrl*) _obj)->SetWordChars(*characters);
}
extern "C" EXPORT void wxStyledTextCtrl_BeginUndoAction(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->BeginUndoAction();
}
extern "C" EXPORT void wxStyledTextCtrl_EndUndoAction(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->EndUndoAction();
}
extern "C" EXPORT void wxStyledTextCtrl_IndicatorSetStyle(void* _obj, int indic, int style)
{
    ((wxStyledTextCtrl*) _obj)->IndicatorSetStyle(indic, style);
}
extern "C" EXPORT int wxStyledTextCtrl_IndicatorGetStyle(void* _obj, int indic)
{
    return ((wxStyledTextCtrl*) _obj)->IndicatorGetStyle(indic);
}
extern "C" EXPORT void wxStyledTextCtrl_IndicatorSetForeground(void* _obj, int indic, int fore_r,
                                                               int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->IndicatorSetForeground(indic, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetWhitespaceForeground(void* _obj, bool useSetting,
                                                                int fore_r, int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)
        ->SetWhitespaceForeground(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetWhitespaceBackground(void* _obj, bool useSetting,
                                                                int back_r, int back_g, int back_b)
{
    ((wxStyledTextCtrl*) _obj)
        ->SetWhitespaceBackground(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetLineState(void* _obj, int line, int state)
{
    ((wxStyledTextCtrl*) _obj)->SetLineState(line, state);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineState(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetLineState(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMaxLineState(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetMaxLineState();
}
extern "C" EXPORT bool wxStyledTextCtrl_GetCaretLineVisible(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetCaretLineVisible();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretLineVisible(void* _obj, bool show)
{
    ((wxStyledTextCtrl*) _obj)->SetCaretLineVisible(show);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetChangeable(void* _obj, int style, bool changeable)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetChangeable(style, changeable);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompShow(void* _obj, int lenEntered, wxString* itemList)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompShow(lenEntered, *itemList);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompCancel(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompCancel();
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompActive(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompActive();
}
extern "C" EXPORT int wxStyledTextCtrl_AutoCompPosStart(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompPosStart();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompComplete(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompComplete();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompStops(void* _obj, wxString* characterSet)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompStops(*characterSet);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetSeparator(void* _obj, int separatorCharacter)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetSeparator(separatorCharacter);
}
extern "C" EXPORT int wxStyledTextCtrl_AutoCompGetSeparator(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetSeparator();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSelect(void* _obj, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSelect(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetCancelAtStart(void* _obj, bool cancel)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetCancelAtStart(cancel);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetCancelAtStart(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetCancelAtStart();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetFillUps(void* _obj, wxString* characterSet)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetFillUps(*characterSet);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetChooseSingle(void* _obj, bool chooseSingle)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetChooseSingle(chooseSingle);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetChooseSingle(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetChooseSingle();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetIgnoreCase(void* _obj, bool ignoreCase)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetIgnoreCase(ignoreCase);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetIgnoreCase(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetIgnoreCase();
}
extern "C" EXPORT void wxStyledTextCtrl_UserListShow(void* _obj, int listType, wxString* itemList)
{
    ((wxStyledTextCtrl*) _obj)->UserListShow(listType, *itemList);
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetAutoHide(void* _obj, bool autoHide)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetAutoHide(autoHide);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetAutoHide(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetAutoHide();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetDropRestOfWord(void* _obj, bool dropRestOfWord)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetDropRestOfWord(dropRestOfWord);
}
extern "C" EXPORT bool wxStyledTextCtrl_AutoCompGetDropRestOfWord(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetDropRestOfWord();
}
extern "C" EXPORT void wxStyledTextCtrl_RegisterImage(void* _obj, int type, void* bmp)
{
    ((wxStyledTextCtrl*) _obj)->RegisterImage(type, *(wxBitmap*) bmp);
}
extern "C" EXPORT void wxStyledTextCtrl_ClearRegisteredImages(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->ClearRegisteredImages();
}
extern "C" EXPORT int wxStyledTextCtrl_AutoCompGetTypeSeparator(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->AutoCompGetTypeSeparator();
}
extern "C" EXPORT void wxStyledTextCtrl_AutoCompSetTypeSeparator(void* _obj, int separatorCharacter)
{
    ((wxStyledTextCtrl*) _obj)->AutoCompSetTypeSeparator(separatorCharacter);
}
extern "C" EXPORT void wxStyledTextCtrl_SetIndent(void* _obj, int indentSize)
{
    ((wxStyledTextCtrl*) _obj)->SetIndent(indentSize);
}
extern "C" EXPORT int wxStyledTextCtrl_GetIndent(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetIndent();
}
extern "C" EXPORT void wxStyledTextCtrl_SetUseTabs(void* _obj, bool useTabs)
{
    ((wxStyledTextCtrl*) _obj)->SetUseTabs(useTabs);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUseTabs(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetUseTabs();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLineIndentation(void* _obj, int line, int indentSize)
{
    ((wxStyledTextCtrl*) _obj)->SetLineIndentation(line, indentSize);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineIndentation(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetLineIndentation(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineIndentPosition(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetLineIndentPosition(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetColumn(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->GetColumn(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetUseHorizontalScrollBar(void* _obj, bool show)
{
    ((wxStyledTextCtrl*) _obj)->SetUseHorizontalScrollBar(show);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUseHorizontalScrollBar(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetUseHorizontalScrollBar();
}
extern "C" EXPORT void wxStyledTextCtrl_SetIndentationGuides(void* _obj, bool show)
{
    ((wxStyledTextCtrl*) _obj)->SetIndentationGuides(show);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetIndentationGuides(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetIndentationGuides();
}
extern "C" EXPORT void wxStyledTextCtrl_SetHighlightGuide(void* _obj, int column)
{
    ((wxStyledTextCtrl*) _obj)->SetHighlightGuide(column);
}
extern "C" EXPORT int wxStyledTextCtrl_GetHighlightGuide(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetHighlightGuide();
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineEndPosition(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetLineEndPosition(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCodePage(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetCodePage();
}
extern "C" EXPORT bool wxStyledTextCtrl_GetReadOnly(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetReadOnly();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCurrentPos(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->SetCurrentPos(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelectionStart(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->SetSelectionStart(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSelectionStart(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetSelectionStart();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelectionEnd(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->SetSelectionEnd(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSelectionEnd(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetSelectionEnd();
}
extern "C" EXPORT void wxStyledTextCtrl_SetPrintMagnification(void* _obj, int magnification)
{
    ((wxStyledTextCtrl*) _obj)->SetPrintMagnification(magnification);
}
extern "C" EXPORT int wxStyledTextCtrl_GetPrintMagnification(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetPrintMagnification();
}
extern "C" EXPORT void wxStyledTextCtrl_SetPrintColourMode(void* _obj, int mode)
{
    ((wxStyledTextCtrl*) _obj)->SetPrintColourMode(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetPrintColourMode(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetPrintColourMode();
}
extern "C" EXPORT int wxStyledTextCtrl_FindText(void* _obj, int minPos, int maxPos, wxString* text,
                                                int flags)
{
    return ((wxStyledTextCtrl*) _obj)->FindText(minPos, maxPos, *text, flags);
}
extern "C" EXPORT int wxStyledTextCtrl_FormatRange(void* _obj, bool doDraw, int startPos,
                                                   int endPos, void* draw, void* target,
                                                   void* renderRect, void* pageRect)
{
    return ((wxStyledTextCtrl*) _obj)
        ->FormatRange(doDraw, startPos, endPos, *(wxDC**) draw, *(wxDC**) target,
                      *(wxRect*) renderRect, *(wxRect*) pageRect);
}
extern "C" EXPORT int wxStyledTextCtrl_GetFirstVisibleLine(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetFirstVisibleLine();
}
extern "C" EXPORT int wxStyledTextCtrl_GetLineCount(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetLineCount();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginLeft(void* _obj, int pixelWidth)
{
    ((wxStyledTextCtrl*) _obj)->SetMarginLeft(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginLeft(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetMarginLeft();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMarginRight(void* _obj, int pixelWidth)
{
    ((wxStyledTextCtrl*) _obj)->SetMarginRight(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMarginRight(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetMarginRight();
}
extern "C" EXPORT bool wxStyledTextCtrl_GetModify(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetModify();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSelection(void* _obj, int start, int end)
{
    ((wxStyledTextCtrl*) _obj)->SetSelection(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_HideSelection(void* _obj, bool normal)
{
    ((wxStyledTextCtrl*) _obj)->HideSelection(normal);
}
extern "C" EXPORT int wxStyledTextCtrl_LineFromPosition(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->LineFromPosition(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionFromLine(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->PositionFromLine(line);
}
extern "C" EXPORT void wxStyledTextCtrl_LineScroll(void* _obj, int columns, int lines)
{
    ((wxStyledTextCtrl*) _obj)->LineScroll(columns, lines);
}
extern "C" EXPORT void wxStyledTextCtrl_EnsureCaretVisible(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->EnsureCaretVisible();
}
extern "C" EXPORT void wxStyledTextCtrl_ReplaceSelection(void* _obj, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->ReplaceSelection(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_SetReadOnly(void* _obj, bool readOnly)
{
    ((wxStyledTextCtrl*) _obj)->SetReadOnly(readOnly);
}
extern "C" EXPORT bool wxStyledTextCtrl_CanPaste(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->CanPaste();
}
extern "C" EXPORT bool wxStyledTextCtrl_CanUndo(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->CanUndo();
}
extern "C" EXPORT void wxStyledTextCtrl_EmptyUndoBuffer(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->EmptyUndoBuffer();
}
extern "C" EXPORT void wxStyledTextCtrl_Undo(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->Undo();
}
extern "C" EXPORT void wxStyledTextCtrl_Cut(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->Cut();
}
extern "C" EXPORT void wxStyledTextCtrl_Copy(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->Copy();
}
extern "C" EXPORT void wxStyledTextCtrl_Paste(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->Paste();
}
extern "C" EXPORT void wxStyledTextCtrl_Clear(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->Clear();
}
extern "C" EXPORT void wxStyledTextCtrl_SetText(void* _obj, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->SetText(*text);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTextLength(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetTextLength();
}
extern "C" EXPORT void wxStyledTextCtrl_SetOvertype(void* _obj, bool overtype)
{
    ((wxStyledTextCtrl*) _obj)->SetOvertype(overtype);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetOvertype(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetOvertype();
}
extern "C" EXPORT void wxStyledTextCtrl_SetCaretWidth(void* _obj, int pixelWidth)
{
    ((wxStyledTextCtrl*) _obj)->SetCaretWidth(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCaretWidth(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetCaretWidth();
}
extern "C" EXPORT void wxStyledTextCtrl_SetTargetStart(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->SetTargetStart(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTargetStart(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetTargetStart();
}
extern "C" EXPORT void wxStyledTextCtrl_SetTargetEnd(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->SetTargetEnd(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_GetTargetEnd(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetTargetEnd();
}
extern "C" EXPORT int wxStyledTextCtrl_ReplaceTarget(void* _obj, wxString* text)
{
    return ((wxStyledTextCtrl*) _obj)->ReplaceTarget(*text);
}
extern "C" EXPORT int wxStyledTextCtrl_ReplaceTargetRE(void* _obj, wxString* text)
{
    return ((wxStyledTextCtrl*) _obj)->ReplaceTargetRE(*text);
}
extern "C" EXPORT int wxStyledTextCtrl_SearchInTarget(void* _obj, wxString* text)
{
    return ((wxStyledTextCtrl*) _obj)->SearchInTarget(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_SetSearchFlags(void* _obj, int flags)
{
    ((wxStyledTextCtrl*) _obj)->SetSearchFlags(flags);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSearchFlags(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetSearchFlags();
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipShow(void* _obj, int pos, wxString* definition)
{
    ((wxStyledTextCtrl*) _obj)->CallTipShow(pos, *definition);
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipCancel(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->CallTipCancel();
}
extern "C" EXPORT bool wxStyledTextCtrl_CallTipActive(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->CallTipActive();
}
extern "C" EXPORT int wxStyledTextCtrl_CallTipPosAtStart(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->CallTipPosAtStart();
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetHighlight(void* _obj, int start, int end)
{
    ((wxStyledTextCtrl*) _obj)->CallTipSetHighlight(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetBackground(void* _obj, int back_r, int back_g,
                                                             int back_b)
{
    ((wxStyledTextCtrl*) _obj)->CallTipSetBackground(wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetForeground(void* _obj, int fore_r, int fore_g,
                                                             int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->CallTipSetForeground(wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_CallTipSetForegroundHighlight(void* _obj, int fore_r,
                                                                      int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->CallTipSetForegroundHighlight(wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT int wxStyledTextCtrl_VisibleFromDocLine(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->VisibleFromDocLine(line);
}
extern "C" EXPORT int wxStyledTextCtrl_DocLineFromVisible(void* _obj, int lineDisplay)
{
    return ((wxStyledTextCtrl*) _obj)->DocLineFromVisible(lineDisplay);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldLevel(void* _obj, int line, int level)
{
    ((wxStyledTextCtrl*) _obj)->SetFoldLevel(line, level);
}
extern "C" EXPORT int wxStyledTextCtrl_GetFoldLevel(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetFoldLevel(line);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLastChild(void* _obj, int line, int level)
{
    return ((wxStyledTextCtrl*) _obj)->GetLastChild(line, level);
}
extern "C" EXPORT int wxStyledTextCtrl_GetFoldParent(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetFoldParent(line);
}
extern "C" EXPORT void wxStyledTextCtrl_ShowLines(void* _obj, int lineStart, int lineEnd)
{
    ((wxStyledTextCtrl*) _obj)->ShowLines(lineStart, lineEnd);
}
extern "C" EXPORT void wxStyledTextCtrl_HideLines(void* _obj, int lineStart, int lineEnd)
{
    ((wxStyledTextCtrl*) _obj)->HideLines(lineStart, lineEnd);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetLineVisible(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetLineVisible(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldExpanded(void* _obj, int line, bool expanded)
{
    ((wxStyledTextCtrl*) _obj)->SetFoldExpanded(line, expanded);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetFoldExpanded(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->GetFoldExpanded(line);
}
extern "C" EXPORT void wxStyledTextCtrl_ToggleFold(void* _obj, int line)
{
    ((wxStyledTextCtrl*) _obj)->ToggleFold(line);
}
extern "C" EXPORT void wxStyledTextCtrl_EnsureVisible(void* _obj, int line)
{
    ((wxStyledTextCtrl*) _obj)->EnsureVisible(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldFlags(void* _obj, int flags)
{
    ((wxStyledTextCtrl*) _obj)->SetFoldFlags(flags);
}
extern "C" EXPORT void wxStyledTextCtrl_EnsureVisibleEnforcePolicy(void* _obj, int line)
{
    ((wxStyledTextCtrl*) _obj)->EnsureVisibleEnforcePolicy(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetTabIndents(void* _obj, bool tabIndents)
{
    ((wxStyledTextCtrl*) _obj)->SetTabIndents(tabIndents);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetTabIndents(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetTabIndents();
}
extern "C" EXPORT void wxStyledTextCtrl_SetBackSpaceUnIndents(void* _obj, bool bsUnIndents)
{
    ((wxStyledTextCtrl*) _obj)->SetBackSpaceUnIndents(bsUnIndents);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetBackSpaceUnIndents(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetBackSpaceUnIndents();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMouseDwellTime(void* _obj, int periodMilliseconds)
{
    ((wxStyledTextCtrl*) _obj)->SetMouseDwellTime(periodMilliseconds);
}
extern "C" EXPORT int wxStyledTextCtrl_GetMouseDwellTime(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetMouseDwellTime();
}
extern "C" EXPORT int wxStyledTextCtrl_WordStartPosition(void* _obj, int pos,
                                                         bool onlyWordCharacters)
{
    return ((wxStyledTextCtrl*) _obj)->WordStartPosition(pos, onlyWordCharacters);
}
extern "C" EXPORT int wxStyledTextCtrl_WordEndPosition(void* _obj, int pos, bool onlyWordCharacters)
{
    return ((wxStyledTextCtrl*) _obj)->WordEndPosition(pos, onlyWordCharacters);
}
extern "C" EXPORT void wxStyledTextCtrl_SetWrapMode(void* _obj, int mode)
{
    ((wxStyledTextCtrl*) _obj)->SetWrapMode(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetWrapMode(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetWrapMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLayoutCache(void* _obj, int mode)
{
    ((wxStyledTextCtrl*) _obj)->SetLayoutCache(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLayoutCache(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetLayoutCache();
}
extern "C" EXPORT void wxStyledTextCtrl_SetScrollWidth(void* _obj, int pixelWidth)
{
    ((wxStyledTextCtrl*) _obj)->SetScrollWidth(pixelWidth);
}
extern "C" EXPORT int wxStyledTextCtrl_GetScrollWidth(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetScrollWidth();
}
extern "C" EXPORT int wxStyledTextCtrl_TextWidth(void* _obj, int style, wxString* text)
{
    return ((wxStyledTextCtrl*) _obj)->TextWidth(style, *text);
}
extern "C" EXPORT void wxStyledTextCtrl_SetEndAtLastLine(void* _obj, bool endAtLastLine)
{
    ((wxStyledTextCtrl*) _obj)->SetEndAtLastLine(endAtLastLine);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEndAtLastLine(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetEndAtLastLine();
}
extern "C" EXPORT int wxStyledTextCtrl_TextHeight(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->TextHeight(line);
}
extern "C" EXPORT void wxStyledTextCtrl_SetUseVerticalScrollBar(void* _obj, bool show)
{
    ((wxStyledTextCtrl*) _obj)->SetUseVerticalScrollBar(show);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetUseVerticalScrollBar(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetUseVerticalScrollBar();
}
extern "C" EXPORT void wxStyledTextCtrl_AppendText(void* _obj, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->AppendText(*text);
}
extern "C" EXPORT void wxStyledTextCtrl_TargetFromSelection(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->TargetFromSelection();
}
extern "C" EXPORT void wxStyledTextCtrl_LinesJoin(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->LinesJoin();
}
extern "C" EXPORT void wxStyledTextCtrl_LinesSplit(void* _obj, int pixelWidth)
{
    ((wxStyledTextCtrl*) _obj)->LinesSplit(pixelWidth);
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldMarginColour(void* _obj, bool useSetting, int back_r,
                                                            int back_g, int back_b)
{
    ((wxStyledTextCtrl*) _obj)->SetFoldMarginColour(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetFoldMarginHiColour(void* _obj, bool useSetting,
                                                              int fore_r, int fore_g, int fore_b)
{
    ((wxStyledTextCtrl*) _obj)->SetFoldMarginHiColour(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_LineDuplicate(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->LineDuplicate();
}
extern "C" EXPORT void wxStyledTextCtrl_HomeDisplay(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->HomeDisplay();
}
extern "C" EXPORT void wxStyledTextCtrl_HomeDisplayExtend(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->HomeDisplayExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_LineEndDisplay(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->LineEndDisplay();
}
extern "C" EXPORT void wxStyledTextCtrl_LineEndDisplayExtend(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->LineEndDisplayExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_LineCopy(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->LineCopy();
}
extern "C" EXPORT void wxStyledTextCtrl_MoveCaretInsideView(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->MoveCaretInsideView();
}
extern "C" EXPORT int wxStyledTextCtrl_LineLength(void* _obj, int line)
{
    return ((wxStyledTextCtrl*) _obj)->LineLength(line);
}
extern "C" EXPORT void wxStyledTextCtrl_BraceHighlight(void* _obj, int pos1, int pos2)
{
    ((wxStyledTextCtrl*) _obj)->BraceHighlight(pos1, pos2);
}
extern "C" EXPORT void wxStyledTextCtrl_BraceBadLight(void* _obj, int pos)
{
    ((wxStyledTextCtrl*) _obj)->BraceBadLight(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_BraceMatch(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->BraceMatch(pos);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetViewEOL(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetViewEOL();
}
extern "C" EXPORT void wxStyledTextCtrl_SetViewEOL(void* _obj, bool visible)
{
    ((wxStyledTextCtrl*) _obj)->SetViewEOL(visible);
}
extern "C" EXPORT void wxStyledTextCtrl_SetDocPointer(void* _obj, void* docPointer)
{
    ((wxStyledTextCtrl*) _obj)->SetDocPointer(docPointer);
}
extern "C" EXPORT void wxStyledTextCtrl_SetModEventMask(void* _obj, int mask)
{
    ((wxStyledTextCtrl*) _obj)->SetModEventMask(mask);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEdgeColumn(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetEdgeColumn();
}
extern "C" EXPORT void wxStyledTextCtrl_SetEdgeColumn(void* _obj, int column)
{
    ((wxStyledTextCtrl*) _obj)->SetEdgeColumn(column);
}
extern "C" EXPORT int wxStyledTextCtrl_GetEdgeMode(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetEdgeMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetEdgeMode(void* _obj, int mode)
{
    ((wxStyledTextCtrl*) _obj)->SetEdgeMode(mode);
}
extern "C" EXPORT void wxStyledTextCtrl_SetEdgeColour(void* _obj, int edgeColour_r,
                                                      int edgeColour_g, int edgeColour_b)
{
    ((wxStyledTextCtrl*) _obj)->SetEdgeColour(wxColour(edgeColour_r, edgeColour_g, edgeColour_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SearchAnchor(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->SearchAnchor();
}
extern "C" EXPORT int wxStyledTextCtrl_SearchNext(void* _obj, int flags, wxString* text)
{
    return ((wxStyledTextCtrl*) _obj)->SearchNext(flags, *text);
}
extern "C" EXPORT int wxStyledTextCtrl_SearchPrev(void* _obj, int flags, wxString* text)
{
    return ((wxStyledTextCtrl*) _obj)->SearchPrev(flags, *text);
}
extern "C" EXPORT int wxStyledTextCtrl_LinesOnScreen(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->LinesOnScreen();
}
extern "C" EXPORT void wxStyledTextCtrl_UsePopUp(void* _obj, bool allowPopUp)
{
    ((wxStyledTextCtrl*) _obj)->UsePopUp(allowPopUp);
}
extern "C" EXPORT bool wxStyledTextCtrl_SelectionIsRectangle(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->SelectionIsRectangle();
}
extern "C" EXPORT void wxStyledTextCtrl_SetZoom(void* _obj, int zoom)
{
    ((wxStyledTextCtrl*) _obj)->SetZoom(zoom);
}
extern "C" EXPORT int wxStyledTextCtrl_GetZoom(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetZoom();
}
extern "C" EXPORT void wxStyledTextCtrl_AddRefDocument(void* _obj, void* docPointer)
{
    ((wxStyledTextCtrl*) _obj)->AddRefDocument(docPointer);
}
extern "C" EXPORT void wxStyledTextCtrl_ReleaseDocument(void* _obj, void* docPointer)
{
    ((wxStyledTextCtrl*) _obj)->ReleaseDocument(docPointer);
}
extern "C" EXPORT int wxStyledTextCtrl_GetModEventMask(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetModEventMask();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSTCFocus(void* _obj, bool focus)
{
    ((wxStyledTextCtrl*) _obj)->SetSTCFocus(focus);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetSTCFocus(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetSTCFocus();
}
extern "C" EXPORT void wxStyledTextCtrl_SetStatus(void* _obj, int statusCode)
{
    ((wxStyledTextCtrl*) _obj)->SetStatus(statusCode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetStatus(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetStatus();
}
extern "C" EXPORT void wxStyledTextCtrl_SetMouseDownCaptures(void* _obj, bool captures)
{
    ((wxStyledTextCtrl*) _obj)->SetMouseDownCaptures(captures);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetMouseDownCaptures(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetMouseDownCaptures();
}
extern "C" EXPORT void wxStyledTextCtrl_SetSTCCursor(void* _obj, int cursorType)
{
    ((wxStyledTextCtrl*) _obj)->SetSTCCursor(cursorType);
}
extern "C" EXPORT int wxStyledTextCtrl_GetSTCCursor(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetSTCCursor();
}
extern "C" EXPORT void wxStyledTextCtrl_SetControlCharSymbol(void* _obj, int symbol)
{
    ((wxStyledTextCtrl*) _obj)->SetControlCharSymbol(symbol);
}
extern "C" EXPORT int wxStyledTextCtrl_GetControlCharSymbol(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetControlCharSymbol();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartLeft(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->WordPartLeft();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartLeftExtend(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->WordPartLeftExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartRight(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->WordPartRight();
}
extern "C" EXPORT void wxStyledTextCtrl_WordPartRightExtend(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->WordPartRightExtend();
}
extern "C" EXPORT void wxStyledTextCtrl_SetVisiblePolicy(void* _obj, int visiblePolicy,
                                                         int visibleSlop)
{
    ((wxStyledTextCtrl*) _obj)->SetVisiblePolicy(visiblePolicy, visibleSlop);
}
extern "C" EXPORT void wxStyledTextCtrl_DelLineLeft(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->DelLineLeft();
}
extern "C" EXPORT void wxStyledTextCtrl_DelLineRight(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->DelLineRight();
}
extern "C" EXPORT void wxStyledTextCtrl_SetXOffset(void* _obj, int newOffset)
{
    ((wxStyledTextCtrl*) _obj)->SetXOffset(newOffset);
}
extern "C" EXPORT int wxStyledTextCtrl_GetXOffset(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetXOffset();
}
extern "C" EXPORT void wxStyledTextCtrl_ChooseCaretX(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->ChooseCaretX();
}
extern "C" EXPORT void wxStyledTextCtrl_SetXCaretPolicy(void* _obj, int caretPolicy, int caretSlop)
{
    ((wxStyledTextCtrl*) _obj)->SetXCaretPolicy(caretPolicy, caretSlop);
}
extern "C" EXPORT void wxStyledTextCtrl_SetYCaretPolicy(void* _obj, int caretPolicy, int caretSlop)
{
    ((wxStyledTextCtrl*) _obj)->SetYCaretPolicy(caretPolicy, caretSlop);
}
extern "C" EXPORT void wxStyledTextCtrl_SetPrintWrapMode(void* _obj, int mode)
{
    ((wxStyledTextCtrl*) _obj)->SetPrintWrapMode(mode);
}
extern "C" EXPORT int wxStyledTextCtrl_GetPrintWrapMode(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetPrintWrapMode();
}
extern "C" EXPORT void wxStyledTextCtrl_SetHotspotActiveForeground(void* _obj, bool useSetting,
                                                                   int fore_r, int fore_g,
                                                                   int fore_b)
{
    ((wxStyledTextCtrl*) _obj)
        ->SetHotspotActiveForeground(useSetting, wxColour(fore_r, fore_g, fore_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetHotspotActiveBackground(void* _obj, bool useSetting,
                                                                   int back_r, int back_g,
                                                                   int back_b)
{
    ((wxStyledTextCtrl*) _obj)
        ->SetHotspotActiveBackground(useSetting, wxColour(back_r, back_g, back_b));
}
extern "C" EXPORT void wxStyledTextCtrl_SetHotspotActiveUnderline(void* _obj, bool underline)
{
    ((wxStyledTextCtrl*) _obj)->SetHotspotActiveUnderline(underline);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionBefore(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->PositionBefore(pos);
}
extern "C" EXPORT int wxStyledTextCtrl_PositionAfter(void* _obj, int pos)
{
    return ((wxStyledTextCtrl*) _obj)->PositionAfter(pos);
}
extern "C" EXPORT void wxStyledTextCtrl_CopyRange(void* _obj, int start, int end)
{
    ((wxStyledTextCtrl*) _obj)->CopyRange(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_CopyText(void* _obj, int length, wxString* text)
{
    ((wxStyledTextCtrl*) _obj)->CopyText(length, *text);
}
extern "C" EXPORT void wxStyledTextCtrl_StartRecord(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->StartRecord();
}
extern "C" EXPORT void wxStyledTextCtrl_StopRecord(void* _obj)
{
    ((wxStyledTextCtrl*) _obj)->StopRecord();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLexer(void* _obj, int lexer)
{
    ((wxStyledTextCtrl*) _obj)->SetLexer(lexer);
}
extern "C" EXPORT int wxStyledTextCtrl_GetLexer(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetLexer();
}
extern "C" EXPORT void wxStyledTextCtrl_Colourise(void* _obj, int start, int end)
{
    ((wxStyledTextCtrl*) _obj)->Colourise(start, end);
}
extern "C" EXPORT void wxStyledTextCtrl_SetProperty(void* _obj, wxString* key, wxString* value)
{
    ((wxStyledTextCtrl*) _obj)->SetProperty(*key, *value);
}
extern "C" EXPORT void wxStyledTextCtrl_SetKeyWords(void* _obj, int keywordSet, wxString* keyWords)
{
    ((wxStyledTextCtrl*) _obj)->SetKeyWords(keywordSet, *keyWords);
}
extern "C" EXPORT void wxStyledTextCtrl_SetLexerLanguage(void* _obj, wxString* language)
{
    ((wxStyledTextCtrl*) _obj)->SetLexerLanguage(*language);
}
extern "C" EXPORT int wxStyledTextCtrl_GetCurrentLine(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetCurrentLine();
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetSpec(void* _obj, int styleNum, wxString* spec)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetSpec(styleNum, *spec);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetFont(void* _obj, int styleNum, void* font)
{
    ((wxStyledTextCtrl*) _obj)->StyleSetFont(styleNum, *(wxFont*) font);
}
extern "C" EXPORT void wxStyledTextCtrl_StyleSetFontAttr(void* _obj, int styleNum, int size,
                                                         wxString* faceName, bool bold, bool italic,
                                                         bool underline)
{
    ((wxStyledTextCtrl*) _obj)
        ->StyleSetFontAttr(styleNum, size, *faceName, bold, italic, underline);
}
extern "C" EXPORT void wxStyledTextCtrl_CmdKeyExecute(void* _obj, int cmd)
{
    ((wxStyledTextCtrl*) _obj)->CmdKeyExecute(cmd);
}
extern "C" EXPORT void wxStyledTextCtrl_SetMargins(void* _obj, int left, int right)
{
    ((wxStyledTextCtrl*) _obj)->SetMargins(left, right);
}
extern "C" EXPORT void wxStyledTextCtrl_GetSelection(void* _obj, void* startPos, void* endPos)
{
    ((wxStyledTextCtrl*) _obj)->GetSelection(*(int**) startPos, *(int**) endPos);
}
extern "C" EXPORT void wxStyledTextCtrl_ScrollToLine(void* _obj, int line)
{
    ((wxStyledTextCtrl*) _obj)->ScrollToLine(line);
}
extern "C" EXPORT void wxStyledTextCtrl_ScrollToColumn(void* _obj, int column)
{
    ((wxStyledTextCtrl*) _obj)->ScrollToColumn(column);
}
extern "C" EXPORT void wxStyledTextCtrl_SetVScrollBar(void* _obj, void* bar)
{
    ((wxStyledTextCtrl*) _obj)->SetVScrollBar(*(wxScrollBar**) bar);
}
extern "C" EXPORT void wxStyledTextCtrl_SetHScrollBar(void* _obj, void* bar)
{
    ((wxStyledTextCtrl*) _obj)->SetHScrollBar(*(wxScrollBar**) bar);
}
extern "C" EXPORT bool wxStyledTextCtrl_GetLastKeydownProcessed(void* _obj)
{
    return ((wxStyledTextCtrl*) _obj)->GetLastKeydownProcessed();
}
extern "C" EXPORT void wxStyledTextCtrl_SetLastKeydownProcessed(void* _obj, bool val)
{
    ((wxStyledTextCtrl*) _obj)->SetLastKeydownProcessed(val);
}
extern "C" EXPORT bool wxStyledTextCtrl_SaveFile(void* _obj, wxString* filename)
{
    return ((wxStyledTextCtrl*) _obj)->SaveFile(*filename);
}
extern "C" EXPORT bool wxStyledTextCtrl_LoadFile(void* _obj, wxString* filename)
{
    return ((wxStyledTextCtrl*) _obj)->LoadFile(*filename);
}
