#pragma once

// PropertyGrid callback hooks — declaration model for the kwx* override classes
// defined in src/kwx_propgrid_hooks.cpp.
//
// These are the three PropertyGrid extension points a foreign language could
// not reach: a custom wxPGProperty subclass, a wxPGTextCtrlEditor that adds
// extra buttons, and a wxPropertyGridPage that controls event propagation.
//
// The callback ABI matches include/kwx_hook_exports.h: every callback is
// void (*)(void* pObject, ...) and a callback that must produce a value calls
// the matching Set*Result function on the same object before it returns.  An
// unset callback keeps the base-class behaviour.
//
// kwxgen expands the quoted includes of include/kwx_classes.h, so these blocks
// reach every binding; the C++ class bodies stay in the .cpp, which is
// deliberately absent from that include list.

#include "kwx_types.h"

// ---------------------------------------------------------------------------
// kwxPGProperty — wxPGProperty whose virtuals forward to callbacks.
//
// ChildChanged and DoGetValue publish a wxVariant, ValueToString a wxString,
// StringToValue and ValidateValue a TBool.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxPGProperty, wxPGProperty) TClass(kwxPGProperty)
    kwxPGProperty_Create(void* pObject, TClass(wxString) label, TClass(wxString) name,
                         TClass(wxVariant) value);
void kwxPGProperty_Delete(TSelf(kwxPGProperty) pObject);
void kwxPGProperty_SetOnChildChanged(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetOnRefreshChildren(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetOnOnSetValue(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetOnDoGetValue(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetOnValueToString(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetOnStringToValue(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetOnValidateValue(TSelf(kwxPGProperty) pObject, void* pFunction);
void kwxPGProperty_SetChildChangedResult(TSelf(kwxPGProperty) pObject, TClass(wxVariant) value);
void kwxPGProperty_SetDoGetValueResult(TSelf(kwxPGProperty) pObject, TClass(wxVariant) value);
void kwxPGProperty_SetValueToStringResult(TSelf(kwxPGProperty) pObject, TClass(wxString) value);
void kwxPGProperty_SetStringToValueResult(TSelf(kwxPGProperty) pObject, TBool result);
void kwxPGProperty_SetValidateValueResult(TSelf(kwxPGProperty) pObject, TBool result);

// ---------------------------------------------------------------------------
// kwxPGTextCtrlEditor — wxPGTextCtrlEditor with callback overrides.
//
// The editor is dynamically allocated and passed to
// wxPropertyGrid_RegisterEditorClass, which takes ownership: do not delete it
// after registering.  The CreateControls callback builds the extra buttons with
// wxPGMultiButton_Create and publishes that widget with
// kwxPGTextCtrlEditor_SetCreateControlsResult.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxPGTextCtrlEditor, wxPGTextCtrlEditor) TClass(kwxPGTextCtrlEditor)
    kwxPGTextCtrlEditor_Create(void* pObject);
void kwxPGTextCtrlEditor_Delete(TSelf(kwxPGTextCtrlEditor) pObject);
void kwxPGTextCtrlEditor_SetOnCreateControls(TSelf(kwxPGTextCtrlEditor) pObject, void* pFunction);
void kwxPGTextCtrlEditor_SetOnOnEvent(TSelf(kwxPGTextCtrlEditor) pObject, void* pFunction);
void kwxPGTextCtrlEditor_SetCreateControlsResult(TSelf(kwxPGTextCtrlEditor) pObject,
                                                 TClass(wxWindow) secondary);
void kwxPGTextCtrlEditor_SetOnEventResult(TSelf(kwxPGTextCtrlEditor) pObject, TBool result);

// ---------------------------------------------------------------------------
// kwxPropertyGridPage — wxPropertyGridPage with callback overrides.
//
// kwxPropertyGridPage_Create returns a page whose lifetime the manager owns:
// once the handle is passed to wxPropertyGridManager_AddPageObject the manager
// deletes it, so the page must not be deleted afterwards.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxPropertyGridPage, wxPropertyGridPage) TClass(kwxPropertyGridPage)
    kwxPropertyGridPage_Create(void* pObject);
void kwxPropertyGridPage_Delete(TSelf(kwxPropertyGridPage) pObject);
void kwxPropertyGridPage_SetOnIsHandlingAllEvents(TSelf(kwxPropertyGridPage) pObject,
                                                  void* pFunction);
void kwxPropertyGridPage_SetIsHandlingAllEventsResult(TSelf(kwxPropertyGridPage) pObject,
                                                      TBool result);
void kwxPropertyGridPage_SetOnInit(TSelf(kwxPropertyGridPage) pObject, void* pFunction);
void kwxPropertyGridPage_SetOnOnShow(TSelf(kwxPropertyGridPage) pObject, void* pFunction);

// ---------------------------------------------------------------------------
// wxPGTextCtrlEditor — parent-only block, so a binding can name the editor
// base that kwxPGTextCtrlEditor extends.  It carries no functions of its own.
// This block is last on purpose: clang-format folds a following declaration
// into a bare TClassDefExtend line as a macro continuation.
// ---------------------------------------------------------------------------

TClassDefExtend(wxPGTextCtrlEditor, wxPGEditor)
