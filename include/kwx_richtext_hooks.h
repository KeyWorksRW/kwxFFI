#pragma once

// Rich-text callback hooks — declaration model for the kwx* override classes
// defined in src/kwx_richtext_hooks.cpp.
//
// These are the three rich-text extension points a foreign language could not
// reach: a wxRichTextCtrl that vetoes insertions and deletions, a
// wxRichTextFieldTypeStandard whose field type is defined by the caller, and a
// wxRichTextDrawingHandler that supplies virtual attributes and virtual text.
//
// The callback ABI matches include/kwx_propgrid_hooks.h: every callback is
// void (*)(void* pObject, ...), receives the foreign object first, and takes at
// most two further arguments.  A callback that must produce a value calls the
// matching Set*Result function on the same object before it returns; a callback
// that returns without publishing keeps the base-class behaviour.  An unset
// callback keeps the base-class behaviour too.
//
// "At most two further arguments" is what lets a runtime whose native thunk is
// void (*)(void*, void*, void*) install every hook: a callback that returned a
// value would answer from an undefined return register, and a fourth argument
// could not be delivered at all.
//
// Argument order per callback, after pObject:
//
//   PrepareContent                     (container)
//   CanDeleteRange                     (container, range)
//   CanInsertContent                   (container, position)
//   CanEditProperties                  (field)
//   EditProperties                     (field, parent)
//   GetPropertiesMenuLabel             (field)
//   UpdateField                        (buffer, field)
//   IsTopLevel                         (field)
//   HasVirtualAttributes               (obj)
//   GetVirtualAttributes               (attr, obj)
//   GetVirtualSubobjectAttributesCount (obj)
//   HasVirtualText                     (obj)
//   GetVirtualText                     (obj)
//
// container is a wxRichTextParagraphLayoutBox*, field a wxRichTextField*, parent
// a wxWindow*, buffer a wxRichTextBuffer*, obj a wxRichTextObject* (or a
// wxRichTextPlainText* for the two virtual-text callbacks), attr a
// wxRichTextAttr* that the callback fills in, position a long.
//
// range is a const wxRichTextRange* borrowed for the duration of the callback
// only; read it with wxRichTextRange_GetStart/GetEnd/GetLength.  An
// EditProperties callback is no longer handed the buffer — it reaches it from
// the field with wxRichTextParagraphLayoutBox_GetBuffer.
//
// wxRichTextBuffer_AddFieldType and wxRichTextBuffer_AddDrawingHandler take
// ownership of the object passed to them: do not Delete it afterwards.
//
// kwxgen expands the quoted includes of include/kwx_classes.h, so these blocks
// reach every binding; the C++ class bodies stay in the .cpp, which is
// deliberately absent from that include list.

#include "kwx_types.h"

// ---------------------------------------------------------------------------
// wxRichTextRange — the (start, end) pair the range-taking rich-text methods
// flatten to two longs.  A CanDeleteRange callback receives a range by pointer
// and reads it through these accessors.  The value is borrowed for the duration
// of the callback; never delete it.
// ---------------------------------------------------------------------------

TClassDef(wxRichTextRange) long wxRichTextRange_GetStart(TSelf(wxRichTextRange) pObject);
long wxRichTextRange_GetEnd(TSelf(wxRichTextRange) pObject);
long wxRichTextRange_GetLength(TSelf(wxRichTextRange) pObject);

// ---------------------------------------------------------------------------
// kwxRichTextCtrl — wxRichTextCtrl with callback overrides.
// Create with kwxRichTextCtrl_Create; the caller owns it (kwxRichTextCtrl_Delete).
// ---------------------------------------------------------------------------

TClassDefExtend(kwxRichTextCtrl, wxRichTextCtrl) TClass(kwxRichTextCtrl)
    kwxRichTextCtrl_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                           int style);
void kwxRichTextCtrl_Delete(TSelf(kwxRichTextCtrl) pObject);
void kwxRichTextCtrl_SetOnPrepareContent(TSelf(kwxRichTextCtrl) pObject, void* pFunction);
void kwxRichTextCtrl_SetOnCanDeleteRange(TSelf(kwxRichTextCtrl) pObject, void* pFunction);
void kwxRichTextCtrl_SetOnCanInsertContent(TSelf(kwxRichTextCtrl) pObject, void* pFunction);
void kwxRichTextCtrl_SetCanDeleteRangeResult(TSelf(kwxRichTextCtrl) pObject, TBool result);
void kwxRichTextCtrl_SetCanInsertContentResult(TSelf(kwxRichTextCtrl) pObject, TBool result);

// ---------------------------------------------------------------------------
// kwxRichTextFieldTypeStandard — wxRichTextFieldTypeStandard with callback overrides.
// Pass the object to wxRichTextBuffer_AddFieldType, which takes ownership:
// do not Delete it afterwards.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxRichTextFieldTypeStandard, wxRichTextFieldTypeStandard)
    TClass(kwxRichTextFieldTypeStandard)
        kwxRichTextFieldTypeStandard_Create(void* pObject, TClass(wxString) name,
                                            TClass(wxString) label, int displayStyle);
void kwxRichTextFieldTypeStandard_Delete(TSelf(kwxRichTextFieldTypeStandard) pObject);
void kwxRichTextFieldTypeStandard_SetOnCanEditProperties(TSelf(kwxRichTextFieldTypeStandard)
                                                             pObject,
                                                         void* pFunction);
void kwxRichTextFieldTypeStandard_SetOnEditProperties(TSelf(kwxRichTextFieldTypeStandard) pObject,
                                                      void* pFunction);
void kwxRichTextFieldTypeStandard_SetOnGetPropertiesMenuLabel(TSelf(kwxRichTextFieldTypeStandard)
                                                                  pObject,
                                                              void* pFunction);
void kwxRichTextFieldTypeStandard_SetPropertiesMenuLabelResult(TSelf(kwxRichTextFieldTypeStandard)
                                                                   pObject,
                                                               TClass(wxString) label);
void kwxRichTextFieldTypeStandard_SetCanEditPropertiesResult(TSelf(kwxRichTextFieldTypeStandard)
                                                                 pObject,
                                                             TBool result);
void kwxRichTextFieldTypeStandard_SetEditPropertiesResult(TSelf(kwxRichTextFieldTypeStandard)
                                                              pObject,
                                                          TBool result);
void kwxRichTextFieldTypeStandard_SetUpdateFieldResult(TSelf(kwxRichTextFieldTypeStandard) pObject,
                                                       TBool result);
void kwxRichTextFieldTypeStandard_SetIsTopLevelResult(TSelf(kwxRichTextFieldTypeStandard) pObject,
                                                      TBool result);
void kwxRichTextFieldTypeStandard_SetOnUpdateField(TSelf(kwxRichTextFieldTypeStandard) pObject,
                                                   void* pFunction);
void kwxRichTextFieldTypeStandard_SetOnIsTopLevel(TSelf(kwxRichTextFieldTypeStandard) pObject,
                                                  void* pFunction);

// ---------------------------------------------------------------------------
// kwxRichTextDrawingHandler — wxRichTextDrawingHandler with callback overrides.
// Pass the object to wxRichTextBuffer_AddDrawingHandler, which takes ownership.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxRichTextDrawingHandler, wxRichTextDrawingHandler)
    TClass(kwxRichTextDrawingHandler)
        kwxRichTextDrawingHandler_Create(void* pObject, TClass(wxString) name);
void kwxRichTextDrawingHandler_Delete(TSelf(kwxRichTextDrawingHandler) pObject);
void kwxRichTextDrawingHandler_SetOnHasVirtualAttributes(TSelf(kwxRichTextDrawingHandler) pObject,
                                                         void* pFunction);
void kwxRichTextDrawingHandler_SetOnGetVirtualAttributes(TSelf(kwxRichTextDrawingHandler) pObject,
                                                         void* pFunction);
void kwxRichTextDrawingHandler_SetOnGetVirtualSubobjectAttributesCount(
    TSelf(kwxRichTextDrawingHandler) pObject, void* pFunction);
void kwxRichTextDrawingHandler_SetOnHasVirtualText(TSelf(kwxRichTextDrawingHandler) pObject,
                                                   void* pFunction);
void kwxRichTextDrawingHandler_SetOnGetVirtualText(TSelf(kwxRichTextDrawingHandler) pObject,
                                                   void* pFunction);
void kwxRichTextDrawingHandler_SetVirtualTextResult(TSelf(kwxRichTextDrawingHandler) pObject,
                                                    TClass(wxString) text);
void kwxRichTextDrawingHandler_SetHasVirtualAttributesResult(TSelf(kwxRichTextDrawingHandler)
                                                                 pObject,
                                                             TBool result);
void kwxRichTextDrawingHandler_SetGetVirtualAttributesResult(TSelf(kwxRichTextDrawingHandler)
                                                                 pObject,
                                                             TBool result);
void kwxRichTextDrawingHandler_SetGetVirtualSubobjectAttributesCountResult(
    TSelf(kwxRichTextDrawingHandler) pObject, int result);
void kwxRichTextDrawingHandler_SetHasVirtualTextResult(TSelf(kwxRichTextDrawingHandler) pObject,
                                                       TBool result);
