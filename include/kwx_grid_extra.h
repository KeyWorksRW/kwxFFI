#pragma once

// Grid classes that were missing from include/kwx_classes.h: cell editors,
// cell renderers, and the string table / table message classes.
//
// Declarations for the implementations in src/wx_grid.cpp.

// ---------------------------------------------------------------------------
// wxGridCellEnumEditor / wxGridCellDateEditor
// ---------------------------------------------------------------------------

// The editors are built through _Ctor because Create is the wxWidgets virtual
// that builds the in-place edit control and must stay a member of the class.
TClassDefExtend(wxGridCellEnumEditor, wxGridCellChoiceEditor) TClass(wxGridCellEnumEditor)
    wxGridCellEnumEditor_Ctor(TClass(wxString) choices);
void wxGridCellEnumEditor_Create(TSelf(wxGridCellEnumEditor) pObject, TClass(wxWindow) parent,
                                 int window_id, TClass(wxEvtHandler) evt_handler);
void wxGridCellEnumEditor_SetParameters(TSelf(wxGridCellEnumEditor) pObject,
                                        TClass(wxString) params);
void wxGridCellEnumEditor_Delete(TSelf(wxGridCellEnumEditor) pObject);

TClassDefExtend(wxGridCellDateEditor, wxGridCellEditor) TClass(wxGridCellDateEditor)
    wxGridCellDateEditor_Ctor(TClass(wxString) format);
void wxGridCellDateEditor_Create(TSelf(wxGridCellDateEditor) pObject, TClass(wxWindow) parent,
                                 int window_id, TClass(wxEvtHandler) evt_handler);
void wxGridCellDateEditor_SetParameters(TSelf(wxGridCellDateEditor) pObject,
                                        TClass(wxString) params);
void wxGridCellDateEditor_Delete(TSelf(wxGridCellDateEditor) pObject);

// wxGridCellAutoWrapStringEditor already had an exported _Ctor in
// src/wx_grid.cpp but no declaration, so it was invisible to kwxgen.
TClassDefExtend(wxGridCellAutoWrapStringEditor, wxGridCellTextEditor)
    TClass(wxGridCellAutoWrapStringEditor) wxGridCellAutoWrapStringEditor_Ctor();

// wxGridCellChoiceEditor is already declared complete in include/kwx_classes.h:
// its _Ctor factory is its only wrappable own member and the remaining methods
// are the wxGridCellEditor wrappers reached through the inheritance chain. A
// repeated block here would duplicate the _Ctor declaration in the class model.

// ---------------------------------------------------------------------------
// wxGridCellDateRenderer / wxGridCellDateTimeRenderer / wxGridCellEnumRenderer
// ---------------------------------------------------------------------------

// wxGridCellWorker exposes SetParameters only; wxWidgets has no GetParameters,
// so no parameter getter is declared for the renderers.
TClassDefExtend(wxGridCellDateRenderer, wxGridCellStringRenderer) TClass(wxGridCellDateRenderer)
    wxGridCellDateRenderer_Create(TClass(wxString) out_format);
void wxGridCellDateRenderer_SetParameters(TSelf(wxGridCellDateRenderer) pObject,
                                          TClass(wxString) params);
void wxGridCellDateRenderer_Delete(TSelf(wxGridCellDateRenderer) pObject);

TClassDefExtend(wxGridCellDateTimeRenderer, wxGridCellDateRenderer)
    TClass(wxGridCellDateTimeRenderer)
        wxGridCellDateTimeRenderer_Create(TClass(wxString) out_format, TClass(wxString) in_format);
void wxGridCellDateTimeRenderer_SetParameters(TSelf(wxGridCellDateTimeRenderer) pObject,
                                              TClass(wxString) params);
void wxGridCellDateTimeRenderer_Delete(TSelf(wxGridCellDateTimeRenderer) pObject);

// The C++ parent is wxGridCellChoiceRenderer, which is not a wxRuby3 spec
// class; the recorded chain matches wxRuby3 (EnumRenderer -> StringRenderer).
TClassDefExtend(wxGridCellEnumRenderer, wxGridCellStringRenderer) TClass(wxGridCellEnumRenderer)
    wxGridCellEnumRenderer_Create(TClass(wxString) choices);
void wxGridCellEnumRenderer_SetParameters(TSelf(wxGridCellEnumRenderer) pObject,
                                          TClass(wxString) params);
void wxGridCellEnumRenderer_Delete(TSelf(wxGridCellEnumRenderer) pObject);

// ---------------------------------------------------------------------------
// wxGridStringTable
// ---------------------------------------------------------------------------

TClassDefExtend(wxGridStringTable, wxGridTableBase) TClass(wxGridStringTable)
    wxGridStringTable_Create(int num_rows, int num_cols);
void wxGridStringTable_Delete(TSelf(wxGridStringTable) pObject);
int wxGridStringTable_GetNumberRows(TSelf(wxGridStringTable) pObject);
int wxGridStringTable_GetNumberCols(TSelf(wxGridStringTable) pObject);
TClass(wxString) wxGridStringTable_GetValue(TSelf(wxGridStringTable) pObject, int row, int col);
void wxGridStringTable_SetValue(TSelf(wxGridStringTable) pObject, int row, int col,
                                TClass(wxString) value);
void wxGridStringTable_Clear(TSelf(wxGridStringTable) pObject);
TBool wxGridStringTable_InsertRows(TSelf(wxGridStringTable) pObject, int pos, int num_rows);
TBool wxGridStringTable_AppendRows(TSelf(wxGridStringTable) pObject, int num_rows);
TBool wxGridStringTable_DeleteRows(TSelf(wxGridStringTable) pObject, int pos, int num_rows);
TBool wxGridStringTable_InsertCols(TSelf(wxGridStringTable) pObject, int pos, int num_cols);
TBool wxGridStringTable_AppendCols(TSelf(wxGridStringTable) pObject, int num_cols);
TBool wxGridStringTable_DeleteCols(TSelf(wxGridStringTable) pObject, int pos, int num_cols);
void wxGridStringTable_SetRowLabelValue(TSelf(wxGridStringTable) pObject, int row,
                                        TClass(wxString) label);
void wxGridStringTable_SetColLabelValue(TSelf(wxGridStringTable) pObject, int col,
                                        TClass(wxString) label);
TClass(wxString) wxGridStringTable_GetRowLabelValue(TSelf(wxGridStringTable) pObject, int row);
TClass(wxString) wxGridStringTable_GetColLabelValue(TSelf(wxGridStringTable) pObject, int col);

// ---------------------------------------------------------------------------
// wxGridTableMessage
// ---------------------------------------------------------------------------

TClassDef(wxGridTableMessage) TClass(wxGridTableMessage)
    wxGridTableMessage_Create(TClass(wxGridTableBase) table, int message_id, int command_int,
                              int command_int2);
void wxGridTableMessage_Delete(TSelf(wxGridTableMessage) pObject);
TClass(wxGridTableBase) wxGridTableMessage_GetTableObject(TSelf(wxGridTableMessage) pObject);
int wxGridTableMessage_GetCommandInt(TSelf(wxGridTableMessage) pObject);
int wxGridTableMessage_GetCommandInt2(TSelf(wxGridTableMessage) pObject);
void wxGridTableMessage_SetTableObject(TSelf(wxGridTableMessage) pObject,
                                       TClass(wxGridTableBase) table);
void wxGridTableMessage_SetCommandInt(TSelf(wxGridTableMessage) pObject, int command_int);
void wxGridTableMessage_SetCommandInt2(TSelf(wxGridTableMessage) pObject, int command_int2);

// ---------------------------------------------------------------------------
// Grid override hooks
//
// These classes forward the grid extension points a foreign language cannot
// derive from itself to callbacks.  The C++ class bodies live in
// src/wx_grid.cpp; every callback receives the foreign object first, and a
// callback that must produce a value publishes it with the matching
// Set*Result function before returning.  An unset callback keeps the base
// class behaviour.  Pointers passed to a callback are valid only for the
// duration of that callback; copy any data the binding must keep.
//
// Ownership: a renderer created by kwxGridCellRendererHook_Create is owned by
// the cell attribute or grid it is passed to, an editor by the grid, and a
// provider by the table, so none of them has a _Delete.  The renderer returned
// by the provider callback is not owned by the provider and must outlive it.
// ---------------------------------------------------------------------------

// clang-format off

// Parents that have no wrapper block of their own.  They are named here so the
// hook classes below resolve their hierarchy.
TClassDef(wxGridHeaderLabelsRenderer)
TClassDefExtend(wxGridColumnHeaderRenderer, wxGridHeaderLabelsRenderer)
TClassDefExtend(wxGridCellActivatableEditor, wxGridCellEditor)

// Cell renderer.  The hook derives from wxGridCellStringRenderer, so a callback
// that wants the ordinary text rendering first calls
// wxGridCellStringRenderer_Draw() on this object.
TClassDefExtend(kwxGridCellRendererHook, wxGridCellStringRenderer)
    TClass(kwxGridCellRendererHook) kwxGridCellRendererHook_Create(void* pObject);
void kwxGridCellRendererHook_SetOnDraw(TSelf(kwxGridCellRendererHook) pObject, void* pFunction);
void kwxGridCellRendererHook_SetOnGetBestSize(TSelf(kwxGridCellRendererHook) pObject,
                                              void* pFunction);
// Called from the GetBestSize callback with the size to return.
void kwxGridCellRendererHook_SetGetBestSizeResult(TSelf(kwxGridCellRendererHook) pObject, int width,
                                                  int height);

// Activatable editor: TryActivate() reports an action and, for Change, the new
// cell value.  The callback receives the activation origin (one of
// wxGridActivationSource::Origin) and the key or mouse event, or null for the
// Program origin.
TClassDefExtend(kwxGridCellActivatableEditorHook, wxGridCellActivatableEditor)
    TClass(kwxGridCellActivatableEditorHook) kwxGridCellActivatableEditorHook_Create(void* pObject);
void kwxGridCellActivatableEditorHook_SetOnTryActivate(
    TSelf(kwxGridCellActivatableEditorHook) pObject, void* pFunction);
void kwxGridCellActivatableEditorHook_SetOnDoActivate(
    TSelf(kwxGridCellActivatableEditorHook) pObject, void* pFunction);
// Action is one of wxGridActivationResult::Action.
void kwxGridCellActivatableEditorHook_SetTryActivateResult(
    TSelf(kwxGridCellActivatableEditorHook) pObject, int action);
// Only used with the Change action.
void kwxGridCellActivatableEditorHook_SetTryActivateValue(
    TSelf(kwxGridCellActivatableEditorHook) pObject, TClass(wxString) value);

// Column header renderer.  DrawBorder has no base implementation, so without a
// callback the border is not drawn at all.
TClassDefExtend(kwxGridColumnHeaderRendererHook, wxGridColumnHeaderRenderer)
    TClass(kwxGridColumnHeaderRendererHook) kwxGridColumnHeaderRendererHook_Create(void* pObject);
void kwxGridColumnHeaderRendererHook_SetOnDrawLabel(
    TSelf(kwxGridColumnHeaderRendererHook) pObject, void* pFunction);
void kwxGridColumnHeaderRendererHook_SetOnDrawBorder(
    TSelf(kwxGridColumnHeaderRendererHook) pObject, void* pFunction);
void kwxGridColumnHeaderRendererHook_SetOnDrawHighlighted(
    TSelf(kwxGridColumnHeaderRendererHook) pObject, void* pFunction);

// Attribute provider that chooses the column header renderer per column and
// can supply the cell attributes.
TClassDefExtend(kwxGridCellAttrProviderHook, wxGridCellAttrProvider)
    TClass(kwxGridCellAttrProviderHook) kwxGridCellAttrProviderHook_Create(void* pObject);
void kwxGridCellAttrProviderHook_SetOnGetColumnHeaderRenderer(
    TSelf(kwxGridCellAttrProviderHook) pObject, void* pFunction);
// Called from the GetColumnHeaderRenderer callback with the renderer to return
// for the column; not calling it keeps the default renderer.
void kwxGridCellAttrProviderHook_SetGetColumnHeaderRendererResult(
    TSelf(kwxGridCellAttrProviderHook) pObject, TClass(wxGridColumnHeaderRenderer) renderer);
// Called for every cell attribute lookup.  kind is a
// wxGridCellAttr::wxAttrKind value.  The callback publishes the attribute to
// return with SetGetAttrResult; leaving the result unset keeps the provider's
// own attribute.  The returned pointer is reference-counted: the callback owns
// the caller's reference and must IncRef a shared attribute before returning it.
void kwxGridCellAttrProviderHook_SetOnGetAttr(TSelf(kwxGridCellAttrProviderHook) pObject,
                                              void* pFunction);
void kwxGridCellAttrProviderHook_SetGetAttrResult(TSelf(kwxGridCellAttrProviderHook) pObject,
                                                  TClass(wxGridCellAttr) attr);
// The attribute wxGridCellAttrProvider would return for row/col/kind.  The
// caller owns the reference and must DecRef it.
TClass(wxGridCellAttr) kwxGridCellAttrProviderHook_GetBaseAttr(
    TSelf(kwxGridCellAttrProviderHook) pObject, int row, int col, int kind);

// wxGridBlocks is a range with a private constructor, so the FFI copies the
// selected blocks into a heap vector that a binding can index.  Each entry is a
// wxGridBlockCoords (top-left and bottom-right cell).
TClassDef(wxGridBlockCoordsArray)
TClass(wxGridBlockCoordsArray) wxGridBlockCoordsArray_Create();
void wxGridBlockCoordsArray_Delete(TSelf(wxGridBlockCoordsArray) pObject);
int wxGridBlockCoordsArray_GetCount(TSelf(wxGridBlockCoordsArray) pObject);
void wxGridBlockCoordsArray_ItemTopLeft(TSelf(wxGridBlockCoordsArray) pObject, int index,
                                        TPointOut(row, col));
void wxGridBlockCoordsArray_ItemBottomRight(TSelf(wxGridBlockCoordsArray) pObject, int index,
                                            TPointOut(row, col));

// clang-format on
