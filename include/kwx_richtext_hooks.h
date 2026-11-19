#pragma once

// Rich-text callback hooks — declaration model for the kwx* override classes
// defined in src/kwx_richtext_hooks.cpp.
//
// These are the three rich-text extension points a foreign language could not
// reach: a wxRichTextCtrl that vetoes insertions and deletions, a
// wxRichTextFieldTypeStandard whose field type is defined by the caller, and a
// wxRichTextDrawingHandler that supplies virtual attributes and virtual text.
//
// Two callback families are declared below.
//
// The plain SetOn… family keeps a per-hook C signature.  Every such callback
// returns void, receives the object-level callback token first — the value given
// to kwxRichTextCtrl_SetCallbackObject, or the pObject passed to the field-type
// and drawing-handler constructors — and takes at most two further arguments.
//
// The …WithData family is the uniform single-thunk form.  Its callback type is
//
//     void (*)(void* data, void* arg1, void* arg2)
//
// where data is the per-hook token passed to that same …WithData setter and
// arg1/arg2 are the hook arguments; an unused position is NULL.  The token — not
// the object-level callback token — identifies the hook, so a runtime with
// exactly one native 3-argument thunk installs every hook by handing each
// …WithData setter that one thunk plus a distinct token.  A …WithData setter
// takes precedence over the plain setter for the same hook.
//
// Both families publish results the same way: a callback that must produce a
// value calls the matching Set*Result function on the same object before it
// returns, and a callback that publishes nothing keeps the base-class
// behaviour.  An unset callback keeps the base-class behaviour too.
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
// In the …WithData family those same arguments arrive as arg1 and arg2; an
// unused position is NULL.  CanInsertContent delivers the long position as
// (void*)(intptr_t)position:
//
//   PrepareContent                     (&container, NULL)
//   CanDeleteRange                     (&container, &range)
//   CanInsertContent                   (&container, (void*)(intptr_t)position)
//   CanEditProperties                  (obj, NULL)
//   EditProperties                     (obj, parent)
//   GetPropertiesMenuLabel             (obj, NULL)
//   UpdateField                        (buffer, obj)
//   IsTopLevel                         (obj, NULL)
//   HasVirtualAttributes               (obj, NULL)
//   GetVirtualAttributes               (&attr, obj)
//   GetVirtualSubobjectAttributesCount (obj, NULL)
//   HasVirtualText                     (obj, NULL)
//   GetVirtualText                     (obj, NULL)
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

// Uniform single-thunk variants; the third argument is the per-hook token.
void kwxRichTextCtrl_SetOnPrepareContentWithData(TSelf(kwxRichTextCtrl) pObject, void* pFunction,
                                                 void* data);
void kwxRichTextCtrl_SetOnCanDeleteRangeWithData(TSelf(kwxRichTextCtrl) pObject, void* pFunction,
                                                 void* data);
void kwxRichTextCtrl_SetOnCanInsertContentWithData(TSelf(kwxRichTextCtrl) pObject, void* pFunction,
                                                   void* data);

void kwxRichTextCtrl_SetCanDeleteRangeResult(TSelf(kwxRichTextCtrl) pObject, TBool result);
void kwxRichTextCtrl_SetCanInsertContentResult(TSelf(kwxRichTextCtrl) pObject, TBool result);

// The foreign object handed to every callback. kwxRichTextCtrl_Create leaves it null;
// call this once so the callbacks can identify the control they belong to.
void kwxRichTextCtrl_SetCallbackObject(TSelf(kwxRichTextCtrl) pObject, void* object);
void* kwxRichTextCtrl_GetCallbackObject(TSelf(kwxRichTextCtrl) pObject);

// Locked-content state, mirroring MyRichTextCtrl in wxSamples/src/richtext/richtext.cpp.
// BeginLock increments the lock id and marks the control locked. While locked,
// PrepareContent tags every child object of every paragraph in the container with the
// long property "Lock" = current id (richtext.cpp:2152-2175); EndLock clears the flag.
// CanDeleteRange / CanInsertContent can then test the property on the leaf objects.
void kwxRichTextCtrl_SetLockId(TSelf(kwxRichTextCtrl) pObject, long id);
long kwxRichTextCtrl_GetLockId(TSelf(kwxRichTextCtrl) pObject);
void kwxRichTextCtrl_BeginLock(TSelf(kwxRichTextCtrl) pObject);
void kwxRichTextCtrl_EndLock(TSelf(kwxRichTextCtrl) pObject);
TBool kwxRichTextCtrl_IsLocked(TSelf(kwxRichTextCtrl) pObject);

// ---------------------------------------------------------------------------
// kwxRichTextFieldTypeStandard — wxRichTextFieldTypeStandard with callback overrides.
// Pass the object to wxRichTextBuffer_AddFieldType, which takes ownership:
// do not Delete it afterwards.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxRichTextFieldTypeStandard, wxRichTextFieldTypeStandard)
    TClass(kwxRichTextFieldTypeStandard)
        kwxRichTextFieldTypeStandard_Create(void* pObject, TClass(wxString) name,
                                            TClass(wxString) label, int displayStyle);
TClass(kwxRichTextFieldTypeStandard)
    kwxRichTextFieldTypeStandard_CreateWithBitmap(void* pObject, TClass(wxString) name,
                                                  TClass(wxBitmap) bitmap, int displayStyle);
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

// Uniform single-thunk variants; the third argument is the per-hook token.
void kwxRichTextFieldTypeStandard_SetOnCanEditPropertiesWithData(TSelf(kwxRichTextFieldTypeStandard)
                                                                     pObject,
                                                                 void* pFunction, void* data);
void kwxRichTextFieldTypeStandard_SetOnEditPropertiesWithData(TSelf(kwxRichTextFieldTypeStandard)
                                                                  pObject,
                                                              void* pFunction, void* data);
void kwxRichTextFieldTypeStandard_SetOnGetPropertiesMenuLabelWithData(
    TSelf(kwxRichTextFieldTypeStandard) pObject, void* pFunction, void* data);
void kwxRichTextFieldTypeStandard_SetOnUpdateFieldWithData(TSelf(kwxRichTextFieldTypeStandard)
                                                               pObject,
                                                           void* pFunction, void* data);
void kwxRichTextFieldTypeStandard_SetOnIsTopLevelWithData(TSelf(kwxRichTextFieldTypeStandard)
                                                              pObject,
                                                          void* pFunction, void* data);

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

// Uniform single-thunk variants; the third argument is the per-hook token.
void kwxRichTextDrawingHandler_SetOnHasVirtualAttributesWithData(TSelf(kwxRichTextDrawingHandler)
                                                                     pObject,
                                                                 void* pFunction, void* data);
void kwxRichTextDrawingHandler_SetOnGetVirtualAttributesWithData(TSelf(kwxRichTextDrawingHandler)
                                                                     pObject,
                                                                 void* pFunction, void* data);
void kwxRichTextDrawingHandler_SetOnGetVirtualSubobjectAttributesCountWithData(
    TSelf(kwxRichTextDrawingHandler) pObject, void* pFunction, void* data);
void kwxRichTextDrawingHandler_SetOnHasVirtualTextWithData(TSelf(kwxRichTextDrawingHandler) pObject,
                                                           void* pFunction, void* data);
void kwxRichTextDrawingHandler_SetOnGetVirtualTextWithData(TSelf(kwxRichTextDrawingHandler) pObject,
                                                           void* pFunction, void* data);
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
