#pragma once

// Wx::RTC declarations (Phase 5).
// Implementations live in:
//   src/wx_richtext.cpp        - object hierarchy, buffer operations, file handlers
//   src/wx_richtextctrl.cpp    - wxRichTextCtrl additions and wxRichTextEvent
//   src/wx_richtextdlg.cpp     - symbol picker, formatting dialog, style organiser
//   src/wx_richtextprint.cpp   - header/footer data and printing
//   src/wx_richtextstyles.cpp  - style list box and buffer data object
// kwxgen merges these blocks with the existing wxRichTextCtrl block in kwx_classes.h.

TClassDefExtend(wxRichTextObject, wxObject)

    TClass(wxRichTextObject) wxRichTextObject_GetParent(TSelf(wxRichTextObject) self);
TClass(wxRichTextObject) wxRichTextObject_GetFirstChild(TSelf(wxRichTextObject) self);
TClass(wxRichTextObject) wxRichTextObject_GetNextSibling(TSelf(wxRichTextObject) self);
void wxRichTextObject_GetPosition(TSelf(wxRichTextObject) self, TPointOut(x, y));
void wxRichTextObject_SetPosition(TSelf(wxRichTextObject) self, TPoint(x, y));
void wxRichTextObject_GetSize(TSelf(wxRichTextObject) self, TSizeOut(w, h));
void wxRichTextObject_SetSize(TSelf(wxRichTextObject) self, TSize(w, h));
void wxRichTextObject_GetRect(TSelf(wxRichTextObject) self, TRectOut(x, y, w, h));
void wxRichTextObject_GetRange(TSelf(wxRichTextObject) self, long* start, long* end);
void wxRichTextObject_SetRange(TSelf(wxRichTextObject) self, long start, long end);
void wxRichTextObject_GetAttributes(TSelf(wxRichTextObject) self, TClass(wxRichTextAttr) attr);
void wxRichTextObject_SetAttributes(TSelf(wxRichTextObject) self, TClass(wxRichTextAttr) attr);
TClass(wxString) wxRichTextObject_GetName(TSelf(wxRichTextObject) self);
void wxRichTextObject_SetName(TSelf(wxRichTextObject) self, TClass(wxString) name);
TClass(wxString)
    wxRichTextObject_GetTextForRange(TSelf(wxRichTextObject) self, long start, long end);
TBool wxRichTextObject_IsComposite(TSelf(wxRichTextObject) self);
TBool wxRichTextObject_IsEmpty(TSelf(wxRichTextObject) self);
TBool wxRichTextObject_IsTopLevel(TSelf(wxRichTextObject) self);
TBool wxRichTextObject_IsShown(TSelf(wxRichTextObject) self);
void wxRichTextObject_Show(TSelf(wxRichTextObject) self, TBool show);
void wxRichTextObject_Delete(TSelf(wxRichTextObject) self);

TClassDefExtend(wxRichTextCompositeObject, wxRichTextObject)

    size_t wxRichTextCompositeObject_GetChildCount(TSelf(wxRichTextCompositeObject) self);
TClass(wxRichTextObject)
    wxRichTextCompositeObject_GetChild(TSelf(wxRichTextCompositeObject) self, size_t index);
TClass(wxRichTextObject)
    wxRichTextCompositeObject_GetChildAtPosition(TSelf(wxRichTextCompositeObject) self,
                                                 long position);
size_t wxRichTextCompositeObject_AppendChild(TSelf(wxRichTextCompositeObject) self,
                                             TClass(wxRichTextObject) child);
TBool wxRichTextCompositeObject_InsertChild(TSelf(wxRichTextCompositeObject) self,
                                            TClass(wxRichTextObject) child,
                                            TClass(wxRichTextObject) inFrontOf);
TBool wxRichTextCompositeObject_RemoveChild(TSelf(wxRichTextCompositeObject) self,
                                            TClass(wxRichTextObject) child, TBool deleteChild);
TBool wxRichTextCompositeObject_DeleteChildren(TSelf(wxRichTextCompositeObject) self);
void wxRichTextCompositeObject_Delete(TSelf(wxRichTextCompositeObject) self);

TClassDefExtend(wxRichTextParagraphLayoutBox, wxRichTextCompositeObject)

    wxRichTextParagraphLayoutBox_Create(TClass(wxRichTextObject) parent);
void wxRichTextParagraphLayoutBox_Delete(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_Clear(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_Reset(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_AddParagraph(TSelf(wxRichTextParagraphLayoutBox) self,
                                               TClass(wxString) text,
                                               TClass(wxRichTextAttr) paraStyle, long* start,
                                               long* end);
void wxRichTextParagraphLayoutBox_AddParagraphs(TSelf(wxRichTextParagraphLayoutBox) self,
                                                TClass(wxString) text,
                                                TClass(wxRichTextAttr) paraStyle, long* start,
                                                long* end);
void wxRichTextParagraphLayoutBox_AddImage(TSelf(wxRichTextParagraphLayoutBox) self,
                                           TClass(wxImage) image, TClass(wxRichTextAttr) paraStyle,
                                           long* start, long* end);
TClass(wxString) wxRichTextParagraphLayoutBox_GetText(TSelf(wxRichTextParagraphLayoutBox) self);
TBool wxRichTextParagraphLayoutBox_DeleteRange(TSelf(wxRichTextParagraphLayoutBox) self, long start,
                                               long end);
TBool wxRichTextParagraphLayoutBox_SetStyle(TSelf(wxRichTextParagraphLayoutBox) self, long start,
                                            long end, TClass(wxRichTextAttr) style, int flags);
TBool wxRichTextParagraphLayoutBox_GetStyle(TSelf(wxRichTextParagraphLayoutBox) self, long position,
                                            TClass(wxRichTextAttr) style);
TBool wxRichTextParagraphLayoutBox_GetUncombinedStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                      long position, TClass(wxRichTextAttr) style);
int wxRichTextParagraphLayoutBox_GetParagraphCount(TSelf(wxRichTextParagraphLayoutBox) self);
TClass(wxString)
    wxRichTextParagraphLayoutBox_GetParagraphText(TSelf(wxRichTextParagraphLayoutBox) self,
                                                  long paragraphNumber);
int wxRichTextParagraphLayoutBox_GetParagraphLength(TSelf(wxRichTextParagraphLayoutBox) self,
                                                    long paragraphNumber);
long wxRichTextParagraphLayoutBox_XYToPosition(TSelf(wxRichTextParagraphLayoutBox) self, long x,
                                               long y);
TBool wxRichTextParagraphLayoutBox_PositionToXY(TSelf(wxRichTextParagraphLayoutBox) self,
                                                long position, long* x, long* y);
TBool wxRichTextParagraphLayoutBox_SetDefaultStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                   TClass(wxRichTextAttr) style);
void wxRichTextParagraphLayoutBox_GetDefaultStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                  TClass(wxRichTextAttr) style);
void wxRichTextParagraphLayoutBox_SetBasicStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                TClass(wxRichTextAttr) style);
void wxRichTextParagraphLayoutBox_GetBasicStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                TClass(wxRichTextAttr) style);
TClass(wxRichTextStyleSheet)
    wxRichTextParagraphLayoutBox_GetStyleSheet(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_SetRichTextCtrl(TSelf(wxRichTextParagraphLayoutBox) self,
                                                  TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl)
    wxRichTextParagraphLayoutBox_GetRichTextCtrl(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_SetPartialParagraph(TSelf(wxRichTextParagraphLayoutBox) self,
                                                      TBool partialParagraph);
TBool wxRichTextParagraphLayoutBox_GetPartialParagraph(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_UpdateRanges(TSelf(wxRichTextParagraphLayoutBox) self);

TClassDefExtend(wxRichTextBox, wxRichTextParagraphLayoutBox)

    wxRichTextBox_Create(TClass(wxRichTextObject) parent);
void wxRichTextBox_Delete(TSelf(wxRichTextBox) self);
TClass(wxString) wxRichTextBox_GetXMLNodeName(TSelf(wxRichTextBox) self);

TClassDefExtend(wxRichTextImage, wxRichTextObject)

    wxRichTextImage_Create(TClass(wxRichTextObject) parent);
wxRichTextImage_CreateFromImage(TClass(wxImage) image, TClass(wxRichTextObject) parent,
                                TClass(wxRichTextAttr) charStyle);
wxRichTextImage_CreateFromImageBlock(TClass(wxRichTextImageBlock) imageBlock,
                                     TClass(wxRichTextObject) parent,
                                     TClass(wxRichTextAttr) charStyle);
void wxRichTextImage_Delete(TSelf(wxRichTextImage) self);
void wxRichTextImage_GetImageCache(TSelf(wxRichTextImage) self, TClass(wxBitmap) bitmap);
void wxRichTextImage_SetImageCache(TSelf(wxRichTextImage) self, TClass(wxBitmap) bitmap);
TClass(wxRichTextImageBlock) wxRichTextImage_GetImageBlock(TSelf(wxRichTextImage) self);
void wxRichTextImage_GetOriginalImageSize(TSelf(wxRichTextImage) self, TSizeOut(w, h));
void wxRichTextImage_SetOriginalImageSize(TSelf(wxRichTextImage) self, TSize(w, h));
int wxRichTextImage_GetImageState(TSelf(wxRichTextImage) self);
void wxRichTextImage_SetImageState(TSelf(wxRichTextImage) self, int state);

TClassDef(wxRichTextImageBlock)

    wxRichTextImageBlock_Create();
void wxRichTextImageBlock_Delete(TSelf(wxRichTextImageBlock) self);
void wxRichTextImageBlock_Clear(TSelf(wxRichTextImageBlock) self);
TBool wxRichTextImageBlock_IsOk(TSelf(wxRichTextImageBlock) self);
size_t wxRichTextImageBlock_GetDataSize(TSelf(wxRichTextImageBlock) self);

TClassDefExtend(wxRichTextBuffer, wxRichTextParagraphLayoutBox)

    wxRichTextBuffer_Create();
void wxRichTextBuffer_Delete(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_AddParagraph(TSelf(wxRichTextBuffer) self, TClass(wxString) text,
                                   TClass(wxRichTextAttr) paraStyle, long* start, long* end);
TBool wxRichTextBuffer_DeleteRange(TSelf(wxRichTextBuffer) self, long start, long end);
void wxRichTextBuffer_GetRange(TSelf(wxRichTextBuffer) self, long* start, long* end);
TClass(wxString) wxRichTextBuffer_GetText(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_Clear(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_LoadFile(TSelf(wxRichTextBuffer) self, TClass(wxString) filename, int type);
TBool wxRichTextBuffer_SaveFile(TSelf(wxRichTextBuffer) self, TClass(wxString) filename, int type);
void wxRichTextBuffer_ResetAndClearCommands(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetStyleSheet(TSelf(wxRichTextBuffer) self,
                                    TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet) wxRichTextBuffer_GetStyleSheet(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_SetStyleSheetAndNotify(TSelf(wxRichTextBuffer) self,
                                              TClass(wxRichTextStyleSheet) sheet);
TBool wxRichTextBuffer_PushStyleSheet(TSelf(wxRichTextBuffer) self,
                                      TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet) wxRichTextBuffer_PopStyleSheet(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetHandlerFlags(TSelf(wxRichTextBuffer) self, int flags);
int wxRichTextBuffer_GetHandlerFlags(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetFontScale(TSelf(wxRichTextBuffer) self, double fontScale);
double wxRichTextBuffer_GetFontScale(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetDimensionScale(TSelf(wxRichTextBuffer) self, double dimScale);
double wxRichTextBuffer_GetDimensionScale(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_BeginBatchUndo(TSelf(wxRichTextBuffer) self, TClass(wxString) cmdName);
TBool wxRichTextBuffer_EndBatchUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_BatchingUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_BeginSuppressUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_EndSuppressUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_SuppressingUndo(TSelf(wxRichTextBuffer) self);

TClassDefExtend(wxRichTextFileHandler, wxObject)

    TClass(wxString) wxRichTextFileHandler_GetName(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetName(TSelf(wxRichTextFileHandler) self, TClass(wxString) name);
TClass(wxString) wxRichTextFileHandler_GetExtension(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetExtension(TSelf(wxRichTextFileHandler) self, TClass(wxString) ext);
int wxRichTextFileHandler_GetType(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetType(TSelf(wxRichTextFileHandler) self, int type);
int wxRichTextFileHandler_GetFlags(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetFlags(TSelf(wxRichTextFileHandler) self, int flags);
void wxRichTextFileHandler_SetEncoding(TSelf(wxRichTextFileHandler) self,
                                       TClass(wxString) encoding);
TClass(wxString) wxRichTextFileHandler_GetEncoding(TSelf(wxRichTextFileHandler) self);
TBool wxRichTextFileHandler_CanHandle(TSelf(wxRichTextFileHandler) self, TClass(wxString) filename);
TBool wxRichTextFileHandler_CanLoad(TSelf(wxRichTextFileHandler) self);
TBool wxRichTextFileHandler_CanSave(TSelf(wxRichTextFileHandler) self);
TBool wxRichTextFileHandler_IsVisible(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetVisible(TSelf(wxRichTextFileHandler) self, TBool visible);
void wxRichTextFileHandler_Delete(TSelf(wxRichTextFileHandler) self);

TClassDefExtend(wxRichTextXMLHandler, wxRichTextFileHandler)

    wxRichTextXMLHandler_Create(TClass(wxString) name, TClass(wxString) ext, int type);
void wxRichTextXMLHandler_Delete(TSelf(wxRichTextXMLHandler) self);

TClassDefExtend(wxRichTextHTMLHandler, wxRichTextFileHandler)

    wxRichTextHTMLHandler_Create(TClass(wxString) name, TClass(wxString) ext, int type);
void wxRichTextHTMLHandler_Delete(TSelf(wxRichTextHTMLHandler) self);
TBool wxRichTextHTMLHandler_CanHandle(TSelf(wxRichTextHTMLHandler) self, TClass(wxString) filename);
void wxRichTextHTMLHandler_ClearTemporaryImageLocations(TSelf(wxRichTextHTMLHandler) self);
TBool wxRichTextHTMLHandler_DeleteTemporaryImages(TSelf(wxRichTextHTMLHandler) self);
void wxRichTextHTMLHandler_SetTempDir(TSelf(wxRichTextHTMLHandler) self, TClass(wxString) tempDir);
TClass(wxString) wxRichTextHTMLHandler_GetTempDir(TSelf(wxRichTextHTMLHandler) self);

TClassDefExtend(wxRichTextEvent, wxNotifyEvent)

    long wxRichTextEvent_GetPosition(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetPosition(TSelf(wxRichTextEvent) self, long position);
int wxRichTextEvent_GetFlags(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetFlags(TSelf(wxRichTextEvent) self, int flags);
TClass(wxRichTextStyleSheet) wxRichTextEvent_GetOldStyleSheet(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetOldStyleSheet(TSelf(wxRichTextEvent) self,
                                      TClass(wxRichTextStyleSheet) sheet);
TClass(wxRichTextStyleSheet) wxRichTextEvent_GetNewStyleSheet(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetNewStyleSheet(TSelf(wxRichTextEvent) self,
                                      TClass(wxRichTextStyleSheet) sheet);
void wxRichTextEvent_GetRange(TSelf(wxRichTextEvent) self, long* start, long* end);
void wxRichTextEvent_SetRange(TSelf(wxRichTextEvent) self, long start, long end);
int wxRichTextEvent_GetCharacter(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetCharacter(TSelf(wxRichTextEvent) self, int character);
TClass(wxRichTextParagraphLayoutBox) wxRichTextEvent_GetContainer(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetContainer(TSelf(wxRichTextEvent) self,
                                  TClass(wxRichTextParagraphLayoutBox) container);
TClass(wxRichTextParagraphLayoutBox) wxRichTextEvent_GetOldContainer(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetOldContainer(TSelf(wxRichTextEvent) self,
                                     TClass(wxRichTextParagraphLayoutBox) container);

TClassDefExtend(wxRichTextCtrl, wxControl)

    TClass(wxRichTextBuffer) wxRichTextCtrl_GetBuffer(TSelf(wxRichTextCtrl) self);
TClass(wxRichTextParagraphLayoutBox) wxRichTextCtrl_GetFocusObject(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_SetFocusObject(TSelf(wxRichTextCtrl) self,
                                    TClass(wxRichTextParagraphLayoutBox) obj,
                                    TBool setCaretPosition);
TBool wxRichTextCtrl_IsSingleLine(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsMultiLine(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_HasSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_HasUnfocusedSelection(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_GetSelectionRange(TSelf(wxRichTextCtrl) self, long* start, long* end);
void wxRichTextCtrl_SetSelectionRange(TSelf(wxRichTextCtrl) self, long start, long end);
void wxRichTextCtrl_GetInternalSelectionRange(TSelf(wxRichTextCtrl) self, long* start, long* end);
void wxRichTextCtrl_SetInternalSelectionRange(TSelf(wxRichTextCtrl) self, long start, long end);
TBool wxRichTextCtrl_SelectWord(TSelf(wxRichTextCtrl) self, long position);
long wxRichTextCtrl_GetDelayedLayoutThreshold(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetDelayedLayoutThreshold(TSelf(wxRichTextCtrl) self, long threshold);
TBool wxRichTextCtrl_GetFullLayoutRequired(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFullLayoutRequired(TSelf(wxRichTextCtrl) self, TBool required);
long wxRichTextCtrl_GetFullLayoutSavedPosition(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFullLayoutSavedPosition(TSelf(wxRichTextCtrl) self, long position);
TBool wxRichTextCtrl_GetCaretAtLineStart(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetCaretAtLineStart(TSelf(wxRichTextCtrl) self, TBool atStart);
TBool wxRichTextCtrl_GetVerticalScrollbarEnabled(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EnableVerticalScrollbar(TSelf(wxRichTextCtrl) self, TBool enable);
TBool wxRichTextCtrl_GetVirtualAttributesEnabled(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EnableVirtualAttributes(TSelf(wxRichTextCtrl) self, TBool enable);
double wxRichTextCtrl_GetFontScale(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFontScale(TSelf(wxRichTextCtrl) self, double fontScale, TBool refresh);
double wxRichTextCtrl_GetDimensionScale(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetDimensionScale(TSelf(wxRichTextCtrl) self, double dimScale, TBool refresh);
double wxRichTextCtrl_GetScale(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetScale(TSelf(wxRichTextCtrl) self, double scale, TBool refresh);
void wxRichTextCtrl_GetBasicStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
void wxRichTextCtrl_SetBasicStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
void wxRichTextCtrl_GetDefaultStyleEx(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
int wxRichTextCtrl_GetHandlerFlags(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetHandlerFlags(TSelf(wxRichTextCtrl) self, int flags);
TClass(wxRichTextStyleSheet) wxRichTextCtrl_GetStyleSheet(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetStyleSheet(TSelf(wxRichTextCtrl) self,
                                  TClass(wxRichTextStyleSheet) styleSheet);
TBool wxRichTextCtrl_PushStyleSheet(TSelf(wxRichTextCtrl) self,
                                    TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet) wxRichTextCtrl_PopStyleSheet(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyStyleSheet(TSelf(wxRichTextCtrl) self,
                                     TClass(wxRichTextStyleSheet) styleSheet);
TBool wxRichTextCtrl_SetDefaultStyleToCursorStyle(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_AddParagraph(TSelf(wxRichTextCtrl) self, TClass(wxString) text, long* start,
                                 long* end);
void wxRichTextCtrl_AddImage(TSelf(wxRichTextCtrl) self, TClass(wxImage) image, long* start,
                             long* end);
TBool wxRichTextCtrl_WriteImageBitmap(TSelf(wxRichTextCtrl) self, TClass(wxBitmap) bitmap,
                                      int bitmapType, TClass(wxRichTextAttr) textAttr);
TBool wxRichTextCtrl_WriteImageBlock(TSelf(wxRichTextCtrl) self,
                                     TClass(wxRichTextImageBlock) imageBlock,
                                     TClass(wxRichTextAttr) textAttr);
TBool wxRichTextCtrl_DeleteRange(TSelf(wxRichTextCtrl) self, long start, long end);
TBool wxRichTextCtrl_SetStyleEx(TSelf(wxRichTextCtrl) self, long start, long end,
                                TClass(wxRichTextAttr) style, int flags);
TBool wxRichTextCtrl_GetUncombinedStyle(TSelf(wxRichTextCtrl) self, long position,
                                        TClass(wxRichTextAttr) style);
TBool wxRichTextCtrl_GetStyleForRange(TSelf(wxRichTextCtrl) self, long start, long end,
                                      TClass(wxRichTextAttr) style);
TBool wxRichTextCtrl_BeginStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
TBool wxRichTextCtrl_EndStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_EndAllStyles(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginCharacterStyle(TSelf(wxRichTextCtrl) self, TClass(wxString) name);
TBool wxRichTextCtrl_EndCharacterStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginParagraphStyle(TSelf(wxRichTextCtrl) self, TClass(wxString) name);
TBool wxRichTextCtrl_EndParagraphStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginListStyle(TSelf(wxRichTextCtrl) self, TClass(wxString) name, int level,
                                    int number);
TBool wxRichTextCtrl_EndListStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_SetListStyle(TSelf(wxRichTextCtrl) self, long start, long end,
                                  TClass(wxString) defName, int flags, int startFrom,
                                  int specifiedLevel);
TBool wxRichTextCtrl_ClearListStyle(TSelf(wxRichTextCtrl) self, long start, long end, int flags);
TBool wxRichTextCtrl_NumberList(TSelf(wxRichTextCtrl) self, long start, long end,
                                TClass(wxString) defName, int flags, int startFrom,
                                int specifiedLevel);
TBool wxRichTextCtrl_PromoteList(TSelf(wxRichTextCtrl) self, int promoteBy, long start, long end,
                                 TClass(wxString) defName, int flags, int specifiedLevel);
TBool wxRichTextCtrl_ApplyStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextStyleDefinition) def);
TBool wxRichTextCtrl_MoveCaret(TSelf(wxRichTextCtrl) self, long position, TBool showAtLineStart);
TBool wxRichTextCtrl_MoveRight(TSelf(wxRichTextCtrl) self, int noPositions, int flags);
TBool wxRichTextCtrl_MoveLeft(TSelf(wxRichTextCtrl) self, int noPositions, int flags);
TBool wxRichTextCtrl_MoveUp(TSelf(wxRichTextCtrl) self, int noLines, int flags);
TBool wxRichTextCtrl_MoveDown(TSelf(wxRichTextCtrl) self, int noLines, int flags);
TBool wxRichTextCtrl_MoveToLineEnd(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveToLineStart(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveToParagraphEnd(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveToParagraphStart(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveHome(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveEnd(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_PageUp(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_PageDown(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_WordLeft(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_WordRight(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_IsSelectionBold(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsSelectionItalics(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsSelectionUnderlined(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_DoesSelectionHaveTextEffectFlag(TSelf(wxRichTextCtrl) self, int flag);
TBool wxRichTextCtrl_IsSelectionAligned(TSelf(wxRichTextCtrl) self, int alignment);
TBool wxRichTextCtrl_ApplyBoldToSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyItalicToSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyUnderlineToSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyTextEffectToSelection(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_ApplyAlignmentToSelection(TSelf(wxRichTextCtrl) self, int alignment);
TBool wxRichTextCtrl_ShowContextMenu(TSelf(wxRichTextCtrl) self, TClass(wxMenu) menu, TPoint(x, y),
                                     TBool addPropertyCommands);
int wxRichTextCtrl_PrepareContextMenu(TSelf(wxRichTextCtrl) self, TClass(wxMenu) menu, TPoint(x, y),
                                      TBool addPropertyCommands);
void wxRichTextCtrl_SetContextMenu(TSelf(wxRichTextCtrl) self, TClass(wxMenu) menu);
TClass(wxMenu) wxRichTextCtrl_GetContextMenu(TSelf(wxRichTextCtrl) self);
long wxRichTextCtrl_GetSelectionAnchor(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetSelectionAnchor(TSelf(wxRichTextCtrl) self, long anchor);
TClass(wxRichTextObject) wxRichTextCtrl_GetSelectionAnchorObject(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Freeze(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Thaw(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsFrozen(TSelf(wxRichTextCtrl) self);
int wxRichTextCtrl_HitTest(TSelf(wxRichTextCtrl) self, TPoint(x, y), long* position);
void wxRichTextCtrl_SetCaretPosition(TSelf(wxRichTextCtrl) self, long position,
                                     TBool showAtLineStart);
long wxRichTextCtrl_GetAdjustedCaretPosition(TSelf(wxRichTextCtrl) self, long caretPosition);
long wxRichTextCtrl_FindNextWordPosition(TSelf(wxRichTextCtrl) self, int direction);
TBool wxRichTextCtrl_IsPositionVisible(TSelf(wxRichTextCtrl) self, long position);
long wxRichTextCtrl_GetFirstVisiblePosition(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_GetFirstVisiblePoint(TSelf(wxRichTextCtrl) self, TPointOut(x, y));

TClassDefExtend(wxRichTextHeaderFooterData, wxObject)

    wxRichTextHeaderFooterData_Create();
void wxRichTextHeaderFooterData_Delete(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_SetHeaderText(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxString) text, int page, int location);
TClass(wxString) wxRichTextHeaderFooterData_GetHeaderText(TSelf(wxRichTextHeaderFooterData) self,
                                                          int page, int location);
void wxRichTextHeaderFooterData_SetFooterText(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxString) text, int page, int location);
TClass(wxString) wxRichTextHeaderFooterData_GetFooterText(TSelf(wxRichTextHeaderFooterData) self,
                                                          int page, int location);
void wxRichTextHeaderFooterData_SetText(TSelf(wxRichTextHeaderFooterData) self,
                                        TClass(wxString) text, int headerFooter, int page,
                                        int location);
TClass(wxString) wxRichTextHeaderFooterData_GetText(TSelf(wxRichTextHeaderFooterData) self,
                                                    int headerFooter, int page, int location);
void wxRichTextHeaderFooterData_SetMargins(TSelf(wxRichTextHeaderFooterData) self, int headerMargin,
                                           int footerMargin);
int wxRichTextHeaderFooterData_GetHeaderMargin(TSelf(wxRichTextHeaderFooterData) self);
int wxRichTextHeaderFooterData_GetFooterMargin(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_SetShowOnFirstPage(TSelf(wxRichTextHeaderFooterData) self,
                                                   TBool showOnFirstPage);
TBool wxRichTextHeaderFooterData_GetShowOnFirstPage(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_Clear(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_SetFont(TSelf(wxRichTextHeaderFooterData) self,
                                        TClass(wxFont) font);
void wxRichTextHeaderFooterData_GetFont(TSelf(wxRichTextHeaderFooterData) self,
                                        TClass(wxFont) font);
void wxRichTextHeaderFooterData_SetTextColour(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxColour) colour);
void wxRichTextHeaderFooterData_GetTextColour(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxColour) colour);

TClassDefExtend(wxRichTextPrinting, wxObject)

    wxRichTextPrinting_Create(TClass(wxString) name, TClass(wxWindow) parentWindow);
void wxRichTextPrinting_Delete(TSelf(wxRichTextPrinting) self);
TBool wxRichTextPrinting_PreviewFile(TSelf(wxRichTextPrinting) self, TClass(wxString) richTextFile);
TBool wxRichTextPrinting_PrintFile(TSelf(wxRichTextPrinting) self, TClass(wxString) richTextFile,
                                   TBool showPrintDialog);
void wxRichTextPrinting_PageSetup(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetHeaderFooterData(TSelf(wxRichTextPrinting) self,
                                            TClass(wxRichTextHeaderFooterData) data);
void wxRichTextPrinting_GetHeaderFooterData(TSelf(wxRichTextPrinting) self,
                                            TClass(wxRichTextHeaderFooterData) data);
void wxRichTextPrinting_SetHeaderText(TSelf(wxRichTextPrinting) self, TClass(wxString) text,
                                      int page, int location);
TClass(wxString)
    wxRichTextPrinting_GetHeaderText(TSelf(wxRichTextPrinting) self, int page, int location);
void wxRichTextPrinting_SetFooterText(TSelf(wxRichTextPrinting) self, TClass(wxString) text,
                                      int page, int location);
TClass(wxString)
    wxRichTextPrinting_GetFooterText(TSelf(wxRichTextPrinting) self, int page, int location);
void wxRichTextPrinting_SetShowOnFirstPage(TSelf(wxRichTextPrinting) self, TBool show);
void wxRichTextPrinting_SetHeaderFooterFont(TSelf(wxRichTextPrinting) self, TClass(wxFont) font);
void wxRichTextPrinting_SetHeaderFooterTextColour(TSelf(wxRichTextPrinting) self,
                                                  TClass(wxColour) colour);
TClass(wxPrintData) wxRichTextPrinting_GetPrintData(TSelf(wxRichTextPrinting) self);
TClass(wxPageSetupDialogData) wxRichTextPrinting_GetPageSetupData(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetPrintData(TSelf(wxRichTextPrinting) self, TClass(wxPrintData) printData);
void wxRichTextPrinting_SetPageSetupData(TSelf(wxRichTextPrinting) self,
                                         TClass(wxPageSetupDialogData) pageSetupData);
void wxRichTextPrinting_SetRichTextBufferPreview(TSelf(wxRichTextPrinting) self,
                                                 TClass(wxRichTextBuffer) buffer);
TClass(wxRichTextBuffer)
    wxRichTextPrinting_GetRichTextBufferPreview(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetRichTextBufferPrinting(TSelf(wxRichTextPrinting) self,
                                                  TClass(wxRichTextBuffer) buffer);
TClass(wxRichTextBuffer)
    wxRichTextPrinting_GetRichTextBufferPrinting(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetParentWindow(TSelf(wxRichTextPrinting) self, TClass(wxWindow) parent);
TClass(wxWindow) wxRichTextPrinting_GetParentWindow(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetTitle(TSelf(wxRichTextPrinting) self, TClass(wxString) title);
TClass(wxString) wxRichTextPrinting_GetTitle(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetPreviewRect(TSelf(wxRichTextPrinting) self, TRect(x, y, w, h));
void wxRichTextPrinting_GetPreviewRect(TSelf(wxRichTextPrinting) self, TRectOut(x, y, w, h));

TClassDefExtend(wxSymbolPickerDialog, wxDialog)

    wxSymbolPickerDialog_Create(TClass(wxString) symbol, TClass(wxString) fontName,
                                TClass(wxString) normalTextFont, TClass(wxWindow) parent, int id,
                                TClass(wxString) caption, TRect(x, y, w, h), long style);
void wxSymbolPickerDialog_Delete(TSelf(wxSymbolPickerDialog) self);
int wxSymbolPickerDialog_GetSymbolChar(TSelf(wxSymbolPickerDialog) self);
TBool wxSymbolPickerDialog_HasSelection(TSelf(wxSymbolPickerDialog) self);
TBool wxSymbolPickerDialog_UseNormalFont(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetUnicodeMode(TSelf(wxSymbolPickerDialog) self, TBool unicodeMode);
void wxSymbolPickerDialog_ShowAtSubset(TSelf(wxSymbolPickerDialog) self);
TClass(wxString) wxSymbolPickerDialog_GetSymbol(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetSymbol(TSelf(wxSymbolPickerDialog) self, TClass(wxString) symbol);
TClass(wxString) wxSymbolPickerDialog_GetFontName(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetFontName(TSelf(wxSymbolPickerDialog) self, TClass(wxString) fontName);
TBool wxSymbolPickerDialog_GetFromUnicode(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetFromUnicode(TSelf(wxSymbolPickerDialog) self, TBool fromUnicode);
TClass(wxString) wxSymbolPickerDialog_GetNormalTextFontName(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetNormalTextFontName(TSelf(wxSymbolPickerDialog) self,
                                                TClass(wxString) fontName);

TClassDefExtend(wxRichTextFormattingDialog, wxPropertySheetDialog)

    wxRichTextFormattingDialog_Create(long flags, TClass(wxWindow) parent, TClass(wxString) title,
                                      int id, TRect(x, y, w, h), long style);
void wxRichTextFormattingDialog_Delete(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_GetStyle(TSelf(wxRichTextFormattingDialog) self,
                                          TClass(wxRichTextCtrl) ctrl, long start, long end);
TBool wxRichTextFormattingDialog_SetStyle(TSelf(wxRichTextFormattingDialog) self,
                                          TClass(wxRichTextAttr) style, TBool update);
TBool wxRichTextFormattingDialog_SetStyleDefinition(TSelf(wxRichTextFormattingDialog) self,
                                                    TClass(wxRichTextStyleDefinition) styleDef,
                                                    TClass(wxRichTextStyleSheet) sheet,
                                                    TBool update);
TClass(wxRichTextStyleDefinition)
    wxRichTextFormattingDialog_GetStyleDefinition(TSelf(wxRichTextFormattingDialog) self);
TClass(wxRichTextStyleSheet)
    wxRichTextFormattingDialog_GetStyleSheet(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_UpdateDisplay(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_ApplyStyle(TSelf(wxRichTextFormattingDialog) self,
                                            TClass(wxRichTextCtrl) ctrl, long start, long end,
                                            int flags);
void wxRichTextFormattingDialog_GetAttributes(TSelf(wxRichTextFormattingDialog) self,
                                              TClass(wxRichTextAttr) attr);
void wxRichTextFormattingDialog_SetAttributes(TSelf(wxRichTextFormattingDialog) self,
                                              TClass(wxRichTextAttr) attr);
void wxRichTextFormattingDialog_SetOptions(TSelf(wxRichTextFormattingDialog) self, int options);
int wxRichTextFormattingDialog_GetOptions(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_HasOption(TSelf(wxRichTextFormattingDialog) self, int option);
TClass(wxRichTextObject)
    wxRichTextFormattingDialog_GetObject(TSelf(wxRichTextFormattingDialog) self);
void wxRichTextFormattingDialog_SetObject(TSelf(wxRichTextFormattingDialog) self,
                                          TClass(wxRichTextObject) obj);
TBool wxRichTextFormattingDialog_TransferDataToWindow(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_TransferDataFromWindow(TSelf(wxRichTextFormattingDialog) self);

TClassDefExtend(wxRichTextStyleOrganiserDialog, wxDialog)

    wxRichTextStyleOrganiserDialog_Create(int flags, TClass(wxRichTextStyleSheet) sheet,
                                          TClass(wxRichTextCtrl) ctrl, TClass(wxWindow) parent,
                                          int id, TClass(wxString) caption, TRect(x, y, w, h),
                                          long style);
void wxRichTextStyleOrganiserDialog_Delete(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_SetStyleSheet(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                  TClass(wxRichTextStyleSheet) sheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleOrganiserDialog_GetStyleSheet(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_SetRichTextCtrl(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                    TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl)
    wxRichTextStyleOrganiserDialog_GetRichTextCtrl(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_SetFlags(TSelf(wxRichTextStyleOrganiserDialog) self, int flags);
int wxRichTextStyleOrganiserDialog_GetFlags(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_ShowPreview(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                int sel);
void wxRichTextStyleOrganiserDialog_ClearPreview(TSelf(wxRichTextStyleOrganiserDialog) self);
TBool wxRichTextStyleOrganiserDialog_GetRestartNumbering(TSelf(wxRichTextStyleOrganiserDialog)
                                                             self);
void wxRichTextStyleOrganiserDialog_SetRestartNumbering(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                        TBool restartNumbering);
TClass(wxString)
    wxRichTextStyleOrganiserDialog_GetSelectedStyle(TSelf(wxRichTextStyleOrganiserDialog) self);
TClass(wxRichTextStyleDefinition)
    wxRichTextStyleOrganiserDialog_GetSelectedStyleDefinition(TSelf(wxRichTextStyleOrganiserDialog)
                                                                  self);
TBool wxRichTextStyleOrganiserDialog_ApplyStyle(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                TClass(wxRichTextCtrl) ctrl);

TClassDefExtend(wxRichTextStyleListBox, wxHtmlListBox)

    wxRichTextStyleListBox_Create(TClass(wxWindow) parent, int id, TRect(x, y, w, h), long style);
void wxRichTextStyleListBox_Delete(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetStyleSheet(TSelf(wxRichTextStyleListBox) self,
                                          TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleListBox_GetStyleSheet(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetRichTextCtrl(TSelf(wxRichTextStyleListBox) self,
                                            TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl) wxRichTextStyleListBox_GetRichTextCtrl(TSelf(wxRichTextStyleListBox) self);
TClass(wxRichTextStyleDefinition)
    wxRichTextStyleListBox_GetStyle(TSelf(wxRichTextStyleListBox) self, size_t index);
int wxRichTextStyleListBox_GetIndexForStyle(TSelf(wxRichTextStyleListBox) self,
                                            TClass(wxString) name);
int wxRichTextStyleListBox_SetStyleSelection(TSelf(wxRichTextStyleListBox) self,
                                             TClass(wxString) name);
void wxRichTextStyleListBox_UpdateStyles(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_ApplyStyle(TSelf(wxRichTextStyleListBox) self, int index);
void wxRichTextStyleListBox_SetApplyOnSelection(TSelf(wxRichTextStyleListBox) self,
                                                TBool applyOnSelection);
TBool wxRichTextStyleListBox_GetApplyOnSelection(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetStyleType(TSelf(wxRichTextStyleListBox) self, int styleType);
int wxRichTextStyleListBox_GetStyleType(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetAutoSetSelection(TSelf(wxRichTextStyleListBox) self, TBool autoSet);
TBool wxRichTextStyleListBox_CanAutoSetSelection(TSelf(wxRichTextStyleListBox) self);

TClassDefExtend(wxRichTextBufferDataObject, wxDataObjectSimple)

    wxRichTextBufferDataObject_Create(TClass(wxRichTextBuffer) richTextBuffer);
void wxRichTextBufferDataObject_Delete(TSelf(wxRichTextBufferDataObject) self);
TClass(wxRichTextBuffer)
    wxRichTextBufferDataObject_GetRichTextBuffer(TSelf(wxRichTextBufferDataObject) self);
TClass(wxString)
    wxRichTextBufferDataObject_GetRichTextBufferFormatId(TSelf(wxRichTextBufferDataObject) self);
size_t wxRichTextBufferDataObject_GetDataSize(TSelf(wxRichTextBufferDataObject) self);
