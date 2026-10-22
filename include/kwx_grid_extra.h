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
