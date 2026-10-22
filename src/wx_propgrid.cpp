// wx_propgrid.cpp
// C wrapper for the wxPropertyGrid support classes: editors, multi-button editor
// controls, cells, validation info, page state, the shared property grid
// interface, and the typed property classes.

#include "kwx_wrapper.h"

// ===========================================================================
// wxPGEditor
// ===========================================================================

extern "C"
{
    EXPORT wxString* wxPGEditor_GetName(wxPGEditor* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT bool wxPGEditor_CanContainCustomImage(wxPGEditor* self)
    {
        return self->CanContainCustomImage();
    }

    // =======================================================================
    // wxPGMultiButton
    // =======================================================================

    EXPORT wxPGMultiButton* wxPGMultiButton_Create(wxPropertyGrid* propgrid, int width, int height)
    {
        return new wxPGMultiButton(propgrid, wxSize(width, height));
    }

    EXPORT void wxPGMultiButton_Delete(wxPGMultiButton* self)
    {
        delete self;
    }

    EXPORT wxWindow* wxPGMultiButton_GetButton(wxPGMultiButton* self, unsigned int index)
    {
        return self->GetButton(index);
    }

    EXPORT int wxPGMultiButton_GetButtonId(wxPGMultiButton* self, unsigned int index)
    {
        return self->GetButtonId(index);
    }

    EXPORT int wxPGMultiButton_GetCount(wxPGMultiButton* self)
    {
        return static_cast<int>(self->GetCount());
    }

    EXPORT void wxPGMultiButton_Add(wxPGMultiButton* self, wxString* label, int id)
    {
        self->Add(*label, id);
    }

    EXPORT void wxPGMultiButton_AddBitmap(wxPGMultiButton* self, wxBitmapBundle* bitmap, int id)
    {
#if wxUSE_BMPBUTTON
        self->Add(*bitmap, id);
#else
        wxUnusedVar(self);
        wxUnusedVar(bitmap);
        wxUnusedVar(id);
#endif
    }

    EXPORT wxSize* wxPGMultiButton_GetPrimarySize(wxPGMultiButton* self)
    {
        return new wxSize(self->GetPrimarySize());
    }

    EXPORT void wxPGMultiButton_Finalize(wxPGMultiButton* self, wxPropertyGrid* propgrid, int x,
                                         int y)
    {
        self->Finalize(propgrid, wxPoint(x, y));
    }

    // =======================================================================
    // wxPGCell
    // =======================================================================

    EXPORT wxPGCell* wxPGCell_Create()
    {
        return new wxPGCell();
    }

    EXPORT wxPGCell* wxPGCell_CreateWithText(wxString* text)
    {
        return new wxPGCell(*text);
    }

    EXPORT void wxPGCell_Delete(wxPGCell* self)
    {
        delete self;
    }

    EXPORT bool wxPGCell_HasText(wxPGCell* self)
    {
        return self->HasText();
    }

    EXPORT bool wxPGCell_IsInvalid(wxPGCell* self)
    {
        return self->IsInvalid();
    }

    EXPORT void wxPGCell_SetEmptyData(wxPGCell* self)
    {
        self->SetEmptyData();
    }

    EXPORT void wxPGCell_MergeFrom(wxPGCell* self, wxPGCell* src_cell)
    {
        self->MergeFrom(*src_cell);
    }

    EXPORT void wxPGCell_SetText(wxPGCell* self, wxString* text)
    {
        self->SetText(*text);
    }

    EXPORT void wxPGCell_SetBitmap(wxPGCell* self, wxBitmapBundle* bitmap)
    {
        self->SetBitmap(*bitmap);
    }

    EXPORT void wxPGCell_SetFgCol(wxPGCell* self, wxColour* colour)
    {
        self->SetFgCol(*colour);
    }

    EXPORT void wxPGCell_SetBgCol(wxPGCell* self, wxColour* colour)
    {
        self->SetBgCol(*colour);
    }

    EXPORT void wxPGCell_SetFont(wxPGCell* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    // The getters below dereference the cell data, which is null for a default
    // constructed cell. Return neutral values in that case instead of crashing.
    EXPORT wxString* wxPGCell_GetText(wxPGCell* self)
    {
        if (self->IsInvalid())
        {
            return new wxString();
        }

        return new wxString(self->GetText());
    }

    EXPORT wxBitmapBundle* wxPGCell_GetBitmap(wxPGCell* self)
    {
        if (self->IsInvalid())
        {
            return new wxBitmapBundle();
        }

        return new wxBitmapBundle(self->GetBitmap());
    }

    EXPORT wxColour* wxPGCell_GetFgCol(wxPGCell* self)
    {
        if (self->IsInvalid())
        {
            return new wxColour();
        }

        return new wxColour(self->GetFgCol());
    }

    EXPORT wxColour* wxPGCell_GetBgCol(wxPGCell* self)
    {
        if (self->IsInvalid())
        {
            return new wxColour();
        }

        return new wxColour(self->GetBgCol());
    }

    EXPORT wxFont* wxPGCell_GetFont(wxPGCell* self)
    {
        if (self->IsInvalid())
        {
            return new wxFont();
        }

        return new wxFont(self->GetFont());
    }

    // =======================================================================
    // wxNumericPropertyValidator
    // =======================================================================

#if wxUSE_VALIDATORS

    EXPORT wxNumericPropertyValidator* wxNumericPropertyValidator_Create(int numeric_type, int base)
    {
        return new wxNumericPropertyValidator(
            static_cast<wxNumericPropertyValidator::NumericType>(numeric_type), base);
    }

    EXPORT void wxNumericPropertyValidator_Delete(wxNumericPropertyValidator* self)
    {
        delete self;
    }

    EXPORT bool wxNumericPropertyValidator_Validate(wxNumericPropertyValidator* self,
                                                    wxWindow* parent)
    {
        return self->Validate(parent);
    }

#else

    EXPORT void* wxNumericPropertyValidator_Create([[maybe_unused]] int numeric_type,
                                                   [[maybe_unused]] int base)
    {
        return nullptr;
    }

    EXPORT void wxNumericPropertyValidator_Delete([[maybe_unused]] void* self) {}

    EXPORT bool wxNumericPropertyValidator_Validate([[maybe_unused]] void* self,
                                                    [[maybe_unused]] wxWindow* parent)
    {
        return false;
    }

#endif  // wxUSE_VALIDATORS

    // =======================================================================
    // wxPGArrayEditorDialog
    // =======================================================================

#if wxUSE_EDITABLELISTBOX

    EXPORT void wxPGArrayEditorDialog_SetDialogValue(wxPGArrayEditorDialog* self, wxVariant* value)
    {
        self->SetDialogValue(*value);
    }

    EXPORT wxVariant* wxPGArrayEditorDialog_GetDialogValue(wxPGArrayEditorDialog* self)
    {
        return new wxVariant(self->GetDialogValue());
    }

    EXPORT void wxPGArrayEditorDialog_EnableCustomNewAction(wxPGArrayEditorDialog* self)
    {
        self->EnableCustomNewAction();
    }

    EXPORT void wxPGArrayEditorDialog_SetNewButtonText(wxPGArrayEditorDialog* self, wxString* text)
    {
        self->SetNewButtonText(*text);
    }

    EXPORT bool wxPGArrayEditorDialog_IsModified(wxPGArrayEditorDialog* self)
    {
        return self->IsModified();
    }

    EXPORT int wxPGArrayEditorDialog_GetSelection(wxPGArrayEditorDialog* self)
    {
        return self->GetSelection();
    }

#else

    EXPORT void wxPGArrayEditorDialog_SetDialogValue([[maybe_unused]] void* self,
                                                     [[maybe_unused]] wxVariant* value)
    {
    }

    EXPORT wxVariant* wxPGArrayEditorDialog_GetDialogValue([[maybe_unused]] void* self)
    {
        return new wxVariant();
    }

    EXPORT void wxPGArrayEditorDialog_EnableCustomNewAction([[maybe_unused]] void* self) {}

    EXPORT void wxPGArrayEditorDialog_SetNewButtonText([[maybe_unused]] void* self,
                                                       [[maybe_unused]] wxString* text)
    {
    }

    EXPORT bool wxPGArrayEditorDialog_IsModified([[maybe_unused]] void* self)
    {
        return false;
    }

    EXPORT int wxPGArrayEditorDialog_GetSelection([[maybe_unused]] void* self)
    {
        return -1;
    }

#endif  // wxUSE_EDITABLELISTBOX

    // =======================================================================
    // wxPGValidationInfo
    // =======================================================================

    EXPORT wxPGValidationInfo* wxPGValidationInfo_Create()
    {
        return new wxPGValidationInfo();
    }

    EXPORT void wxPGValidationInfo_Delete(wxPGValidationInfo* self)
    {
        delete self;
    }

    EXPORT int wxPGValidationInfo_GetFailureBehavior(wxPGValidationInfo* self)
    {
        return static_cast<int>(self->GetFailureBehavior());
    }

    EXPORT void wxPGValidationInfo_SetFailureBehavior(wxPGValidationInfo* self,
                                                      int failure_behavior)
    {
        self->SetFailureBehavior(static_cast<wxPGVFBFlags>(failure_behavior));
    }

    EXPORT wxString* wxPGValidationInfo_GetFailureMessage(wxPGValidationInfo* self)
    {
        return new wxString(self->GetFailureMessage());
    }

    EXPORT void wxPGValidationInfo_SetFailureMessage(wxPGValidationInfo* self, wxString* message)
    {
        self->SetFailureMessage(*message);
    }

    // SetValue() is private in wxPGValidationInfo and is only reachable by
    // wxPropertyGrid; it is deliberately not wrapped.
    EXPORT wxVariant* wxPGValidationInfo_GetValue(wxPGValidationInfo* self)
    {
        return new wxVariant(self->GetValue());
    }
}

// ===========================================================================
// wxPropertyGridPageState
// ===========================================================================

extern "C"
{
    EXPORT wxPropertyGridPageState* wxPropertyGridPageState_Create()
    {
        return new wxPropertyGridPageState();
    }

    EXPORT void wxPropertyGridPageState_Delete(wxPropertyGridPageState* self)
    {
        delete self;
    }

    EXPORT wxPropertyGrid* wxPropertyGridPageState_GetGrid(wxPropertyGridPageState* self)
    {
        return self->GetGrid();
    }

    EXPORT int wxPropertyGridPageState_GetColumnCount(wxPropertyGridPageState* self)
    {
        return static_cast<int>(self->GetColumnCount());
    }

    EXPORT int wxPropertyGridPageState_GetColumnMinWidth(wxPropertyGridPageState* self, int column)
    {
        return self->GetColumnMinWidth(column);
    }

    EXPORT int wxPropertyGridPageState_GetColumnWidth(wxPropertyGridPageState* self,
                                                      unsigned int column)
    {
        return self->GetColumnWidth(column);
    }

    EXPORT int wxPropertyGridPageState_GetVirtualWidth(wxPropertyGridPageState* self)
    {
        return self->GetVirtualWidth();
    }

    EXPORT int wxPropertyGridPageState_GetVirtualHeight(wxPropertyGridPageState* self)
    {
        return static_cast<int>(self->GetVirtualHeight());
    }

    EXPORT int wxPropertyGridPageState_GetActualVirtualHeight(wxPropertyGridPageState* self)
    {
        return static_cast<int>(self->GetActualVirtualHeight());
    }

    EXPORT wxPGProperty* wxPropertyGridPageState_GetLastItem(wxPropertyGridPageState* self,
                                                             int flags)
    {
        return self->GetLastItem(flags);
    }

    EXPORT wxPGProperty* wxPropertyGridPageState_GetSelection(wxPropertyGridPageState* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxPropertyGridPageState_EnableCategories(wxPropertyGridPageState* self, bool enable)
    {
        return self->EnableCategories(enable);
    }

    EXPORT bool wxPropertyGridPageState_IsDisplayed(wxPropertyGridPageState* self)
    {
        return self->IsDisplayed();
    }

    EXPORT bool wxPropertyGridPageState_IsInNonCatMode(wxPropertyGridPageState* self)
    {
        return self->IsInNonCatMode();
    }

    EXPORT void wxPropertyGridPageState_CheckColumnWidths(wxPropertyGridPageState* self,
                                                          int width_change)
    {
        self->CheckColumnWidths(width_change);
    }

    EXPORT void wxPropertyGridPageState_VirtualHeightChanged(wxPropertyGridPageState* self)
    {
        self->VirtualHeightChanged();
    }

    // =======================================================================
    // wxPropertyGridInterface
    // =======================================================================

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyByName(wxPropertyGridInterface* self,
                                                                   wxString* name)
    {
        return self->GetPropertyByName(*name);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyByName2(wxPropertyGridInterface* self,
                                                                    wxString* name,
                                                                    wxString* subname)
    {
        return self->GetPropertyByName(*name, *subname);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyByLabel(wxPropertyGridInterface* self,
                                                                    wxString* label)
    {
        return self->GetPropertyByLabel(*label);
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyName(wxPropertyGridInterface* self,
                                                             wxPGProperty* property)
    {
        return new wxString(self->GetPropertyName(property));
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyLabel(wxPropertyGridInterface* self,
                                                              wxPGProperty* id)
    {
        return new wxString(self->GetPropertyLabel(id));
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyHelpString(wxPropertyGridInterface* self,
                                                                   wxPGProperty* id)
    {
        return new wxString(self->GetPropertyHelpString(id));
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyParent(wxPropertyGridInterface* self,
                                                                   wxPGProperty* id)
    {
        return self->GetPropertyParent(id);
    }

    EXPORT wxPropertyCategory*
        wxPropertyGridInterface_GetPropertyCategory(wxPropertyGridInterface* self, wxPGProperty* id)
    {
        return self->GetPropertyCategory(id);
    }

    EXPORT wxPGEditor* wxPropertyGridInterface_GetPropertyEditor(wxPropertyGridInterface* self,
                                                                 wxPGProperty* id)
    {
        return const_cast<wxPGEditor*>(self->GetPropertyEditor(id));
    }

    EXPORT wxBitmap* wxPropertyGridInterface_GetPropertyImage(wxPropertyGridInterface* self,
                                                              wxPGProperty* id)
    {
        return self->GetPropertyImage(id);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetFirstChild(wxPropertyGridInterface* self,
                                                               wxPGProperty* id)
    {
        return self->GetFirstChild(id);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetFirst(wxPropertyGridInterface* self, int flags)
    {
        return self->GetFirst(flags);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetSelection(wxPropertyGridInterface* self)
    {
        return self->GetSelection();
    }

    EXPORT wxPropertyGridPageState* wxPropertyGridInterface_GetState(wxPropertyGridInterface* self)
    {
        return self->GetState();
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_Append(wxPropertyGridInterface* self,
                                                        wxPGProperty* property)
    {
        return self->Append(property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_AppendIn(wxPropertyGridInterface* self,
                                                          wxPGProperty* id, wxPGProperty* property)
    {
        return self->AppendIn(id, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_Insert(wxPropertyGridInterface* self,
                                                        wxPGProperty* prior_this,
                                                        wxPGProperty* property)
    {
        return self->Insert(prior_this, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_Insert2(wxPropertyGridInterface* self,
                                                         wxPGProperty* parent, int index,
                                                         wxPGProperty* property)
    {
        return self->Insert(parent, index, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_ReplaceProperty(wxPropertyGridInterface* self,
                                                                 wxPGProperty* id,
                                                                 wxPGProperty* property)
    {
        return self->ReplaceProperty(id, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_RemoveProperty(wxPropertyGridInterface* self,
                                                                wxPGProperty* id)
    {
        return self->RemoveProperty(id);
    }

    EXPORT void wxPropertyGridInterface_DeleteProperty(wxPropertyGridInterface* self,
                                                       wxPGProperty* id)
    {
        self->DeleteProperty(id);
    }

    EXPORT void wxPropertyGridInterface_Clear(wxPropertyGridInterface* self)
    {
        self->Clear();
    }

    EXPORT bool wxPropertyGridInterface_ClearSelection(wxPropertyGridInterface* self,
                                                       bool validation)
    {
        return self->ClearSelection(validation);
    }

    EXPORT void wxPropertyGridInterface_ClearModifiedStatus(wxPropertyGridInterface* self)
    {
        self->ClearModifiedStatus();
    }

    EXPORT bool wxPropertyGridInterface_EditorValidate(wxPropertyGridInterface* self)
    {
        return self->EditorValidate();
    }

    EXPORT bool wxPropertyGridInterface_Collapse(wxPropertyGridInterface* self, wxPGProperty* id)
    {
        return self->Collapse(id);
    }

    EXPORT bool wxPropertyGridInterface_CollapseAll(wxPropertyGridInterface* self)
    {
        return self->CollapseAll();
    }

    EXPORT bool wxPropertyGridInterface_Expand(wxPropertyGridInterface* self, wxPGProperty* id)
    {
        return self->Expand(id);
    }

    EXPORT bool wxPropertyGridInterface_ExpandAll(wxPropertyGridInterface* self, bool expand)
    {
        return self->ExpandAll(expand);
    }

    EXPORT bool wxPropertyGridInterface_DisableProperty(wxPropertyGridInterface* self,
                                                        wxPGProperty* id)
    {
        return self->DisableProperty(id);
    }

    EXPORT bool wxPropertyGridInterface_EnableProperty(wxPropertyGridInterface* self,
                                                       wxPGProperty* id, bool enable)
    {
        return self->EnableProperty(id, enable);
    }

    EXPORT bool wxPropertyGridInterface_HideProperty(wxPropertyGridInterface* self,
                                                     wxPGProperty* id, bool hide, int flags)
    {
        return self->HideProperty(id, hide, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_LimitPropertyEditing(wxPropertyGridInterface* self,
                                                             wxPGProperty* id, bool limit)
    {
        self->LimitPropertyEditing(id, limit);
    }

    EXPORT void wxPropertyGridInterface_RefreshGrid(wxPropertyGridInterface* self,
                                                    wxPropertyGridPageState* state)
    {
        self->RefreshGrid(state);
    }

    EXPORT void wxPropertyGridInterface_RefreshProperty(wxPropertyGridInterface* self,
                                                        wxPGProperty* property)
    {
        self->RefreshProperty(property);
    }

    EXPORT wxVariant* wxPropertyGridInterface_GetPropertyValue(wxPropertyGridInterface* self,
                                                               wxPGProperty* id)
    {
        return new wxVariant(self->GetPropertyValue(id));
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyValueAsString(wxPropertyGridInterface* self,
                                                                      wxPGProperty* id)
    {
        return new wxString(self->GetPropertyValueAsString(id));
    }

    EXPORT long wxPropertyGridInterface_GetPropertyValueAsLong(wxPropertyGridInterface* self,
                                                               wxPGProperty* id)
    {
        return self->GetPropertyValueAsLong(id);
    }

    EXPORT int wxPropertyGridInterface_GetPropertyValueAsInt(wxPropertyGridInterface* self,
                                                             wxPGProperty* id)
    {
        return self->GetPropertyValueAsInt(id);
    }

    EXPORT bool wxPropertyGridInterface_GetPropertyValueAsBool(wxPropertyGridInterface* self,
                                                               wxPGProperty* id)
    {
        return self->GetPropertyValueAsBool(id);
    }

    EXPORT double wxPropertyGridInterface_GetPropertyValueAsDouble(wxPropertyGridInterface* self,
                                                                   wxPGProperty* id)
    {
        return self->GetPropertyValueAsDouble(id);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValue(wxPropertyGridInterface* self,
                                                         wxPGProperty* id, wxVariant* value)
    {
        self->SetPropertyValue(id, *value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueString(wxPropertyGridInterface* self,
                                                               wxPGProperty* id, wxString* value)
    {
        self->SetPropertyValueString(id, *value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueLong(wxPropertyGridInterface* self,
                                                             wxPGProperty* id, long value)
    {
        self->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueInt(wxPropertyGridInterface* self,
                                                            wxPGProperty* id, int value)
    {
        self->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueDouble(wxPropertyGridInterface* self,
                                                               wxPGProperty* id, double value)
    {
        self->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueBool(wxPropertyGridInterface* self,
                                                             wxPGProperty* id, bool value)
    {
        self->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueUnspecified(wxPropertyGridInterface* self,
                                                                    wxPGProperty* id)
    {
        self->SetPropertyValueUnspecified(id);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyLabel(wxPropertyGridInterface* self,
                                                         wxPGProperty* id, wxString* label)
    {
        self->SetPropertyLabel(id, *label);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyName(wxPropertyGridInterface* self,
                                                        wxPGProperty* id, wxString* name)
    {
        self->SetPropertyName(id, *name);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyHelpString(wxPropertyGridInterface* self,
                                                              wxPGProperty* id, wxString* text)
    {
        self->SetPropertyHelpString(id, *text);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyReadOnly(wxPropertyGridInterface* self,
                                                            wxPGProperty* id, bool read_only,
                                                            int flags)
    {
        self->SetPropertyReadOnly(id, read_only, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_SetPropertyEditor(wxPropertyGridInterface* self,
                                                          wxPGProperty* id, wxPGEditor* editor)
    {
        self->SetPropertyEditor(id, editor);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyEditorByName(wxPropertyGridInterface* self,
                                                                wxPGProperty* id, wxString* name)
    {
        self->SetPropertyEditor(id, *name);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyImage(wxPropertyGridInterface* self,
                                                         wxPGProperty* id, wxBitmapBundle* bitmap)
    {
        self->SetPropertyImage(id, *bitmap);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyCell(wxPropertyGridInterface* self,
                                                        wxPGProperty* id, int column,
                                                        wxString* text, wxBitmapBundle* bitmap,
                                                        wxColour* fg_col, wxColour* bg_col)
    {
        self->SetPropertyCell(id, column, *text, *bitmap, *fg_col, *bg_col);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertyCategory(wxPropertyGridInterface* self,
                                                           wxPGProperty* id)
    {
        return self->IsPropertyCategory(id);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertyEnabled(wxPropertyGridInterface* self,
                                                          wxPGProperty* id)
    {
        return self->IsPropertyEnabled(id);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertyExpanded(wxPropertyGridInterface* self,
                                                           wxPGProperty* id)
    {
        return self->IsPropertyExpanded(id);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertyModified(wxPropertyGridInterface* self,
                                                           wxPGProperty* id)
    {
        return self->IsPropertyModified(id);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertySelected(wxPropertyGridInterface* self,
                                                           wxPGProperty* id)
    {
        return self->IsPropertySelected(id);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertyShown(wxPropertyGridInterface* self,
                                                        wxPGProperty* id)
    {
        return self->IsPropertyShown(id);
    }

    EXPORT bool wxPropertyGridInterface_IsPropertyValueUnspecified(wxPropertyGridInterface* self,
                                                                   wxPGProperty* id)
    {
        return self->IsPropertyValueUnspecified(id);
    }

    EXPORT bool wxPropertyGridInterface_SetColumnProportion(wxPropertyGridInterface* self,
                                                            unsigned int column, int proportion)
    {
        return self->SetColumnProportion(column, proportion);
    }

    EXPORT int wxPropertyGridInterface_GetColumnProportion(wxPropertyGridInterface* self,
                                                           unsigned int column)
    {
        return self->GetColumnProportion(column);
    }

    EXPORT wxString* wxPropertyGridInterface_SaveEditableState(wxPropertyGridInterface* self,
                                                               int included_states)
    {
        return new wxString(self->SaveEditableState(included_states));
    }

    EXPORT bool wxPropertyGridInterface_RestoreEditableState(wxPropertyGridInterface* self,
                                                             wxString* src, int restore_states)
    {
        return self->RestoreEditableState(*src, restore_states);
    }

    EXPORT void wxPropertyGridInterface_Sort(wxPropertyGridInterface* self, int flags)
    {
        self->Sort(static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_SortChildren(wxPropertyGridInterface* self,
                                                     wxPGProperty* id, int flags)
    {
        self->SortChildren(id, static_cast<wxPGPropertyValuesFlags>(flags));
    }
}

// =======================================================================
// Typed property classes
// =======================================================================
extern "C"
{
    EXPORT void wxStringProperty_Delete(wxStringProperty* self)
    {
        delete self;
    }

    EXPORT void wxIntProperty_Delete(wxIntProperty* self)
    {
        delete self;
    }

    EXPORT void wxBoolProperty_Delete(wxBoolProperty* self)
    {
        delete self;
    }

    EXPORT void wxFloatProperty_Delete(wxFloatProperty* self)
    {
        delete self;
    }

    EXPORT void wxDateProperty_Delete(wxDateProperty* self)
    {
        delete self;
    }

    EXPORT void wxFileProperty_Delete(wxFileProperty* self)
    {
        delete self;
    }

    EXPORT void wxPropertyCategory_Delete(wxPropertyCategory* self)
    {
        delete self;
    }

    EXPORT wxUIntProperty* wxUIntProperty_Create(wxString* label, wxString* name,
                                                 unsigned long value)
    {
        return new wxUIntProperty(*label, *name, value);
    }

    EXPORT void wxUIntProperty_Delete(wxUIntProperty* self)
    {
        delete self;
    }

    EXPORT wxLongStringProperty* wxLongStringProperty_Create(wxString* label, wxString* name,
                                                             wxString* value)
    {
        return new wxLongStringProperty(*label, *name, *value);
    }

    EXPORT void wxLongStringProperty_Delete(wxLongStringProperty* self)
    {
        delete self;
    }

    EXPORT wxDirProperty* wxDirProperty_Create(wxString* label, wxString* name, wxString* value)
    {
        return new wxDirProperty(*label, *name, *value);
    }

    EXPORT void wxDirProperty_Delete(wxDirProperty* self)
    {
        delete self;
    }

    EXPORT wxArrayStringProperty* wxArrayStringProperty_Create(wxString* label, wxString* name,
                                                               int count, void* values)
    {
        wxArrayString property_values;
        for (int i = 0; i < count; ++i)
        {
            property_values.Add(static_cast<char**>(values)[i]);
        }

        return new wxArrayStringProperty(*label, *name, property_values);
    }

    EXPORT void wxArrayStringProperty_Delete(wxArrayStringProperty* self)
    {
        delete self;
    }

    EXPORT wxFontProperty* wxFontProperty_Create(wxString* label, wxString* name, wxFont* value)
    {
        return new wxFontProperty(*label, *name, *value);
    }

    EXPORT void wxFontProperty_Delete(wxFontProperty* self)
    {
        delete self;
    }

    EXPORT wxColourProperty* wxColourProperty_Create(wxString* label, wxString* name,
                                                     wxColour* value)
    {
        return new wxColourProperty(*label, *name, *value);
    }

    EXPORT void wxColourProperty_Delete(wxColourProperty* self)
    {
        delete self;
    }

#if wxUSE_CHOICEDLG

    EXPORT wxMultiChoiceProperty* wxMultiChoiceProperty_Create(wxString* label, wxString* name,
                                                               int count, void* values)
    {
        wxArrayString property_values;
        for (int i = 0; i < count; ++i)
        {
            property_values.Add(static_cast<char**>(values)[i]);
        }

        return new wxMultiChoiceProperty(*label, *name, property_values);
    }

    EXPORT void wxMultiChoiceProperty_Delete(wxMultiChoiceProperty* self)
    {
        delete self;
    }

#else

    EXPORT void* wxMultiChoiceProperty_Create([[maybe_unused]] wxString* label,
                                              [[maybe_unused]] wxString* name,
                                              [[maybe_unused]] int count,
                                              [[maybe_unused]] void* values)
    {
        return nullptr;
    }

    EXPORT void wxMultiChoiceProperty_Delete([[maybe_unused]] void* self) {}

#endif  // wxUSE_CHOICEDLG

    EXPORT wxEnumProperty* wxEnumProperty_Create(wxString* label, wxString* name, int label_count,
                                                 void* labels, int value_count, int* values,
                                                 int value)
    {
        wxArrayString property_labels;
        for (int i = 0; i < label_count; ++i)
        {
            property_labels.Add(static_cast<char**>(labels)[i]);
        }

        wxArrayInt property_values;
        for (int i = 0; i < value_count; ++i)
        {
            property_values.Add(values[i]);
        }

        return new wxEnumProperty(*label, *name, property_labels, property_values, value);
    }

    EXPORT void wxEnumProperty_Delete(wxEnumProperty* self)
    {
        delete self;
    }

    EXPORT wxEditEnumProperty* wxEditEnumProperty_Create(wxString* label, wxString* name,
                                                         int label_count, void* labels,
                                                         int value_count, int* values,
                                                         wxString* value)
    {
        wxArrayString property_labels;
        for (int i = 0; i < label_count; ++i)
        {
            property_labels.Add(static_cast<char**>(labels)[i]);
        }

        wxArrayInt property_values;
        for (int i = 0; i < value_count; ++i)
        {
            property_values.Add(values[i]);
        }

        return new wxEditEnumProperty(*label, *name, property_labels, property_values, *value);
    }

    EXPORT void wxEditEnumProperty_Delete(wxEditEnumProperty* self)
    {
        delete self;
    }

    EXPORT wxFlagsProperty* wxFlagsProperty_Create(wxString* label, wxString* name, int label_count,
                                                   void* labels, int value_count, int* values,
                                                   int value)
    {
        wxArrayString property_labels;
        for (int i = 0; i < label_count; ++i)
        {
            property_labels.Add(static_cast<char**>(labels)[i]);
        }

        wxArrayInt property_values;
        for (int i = 0; i < value_count; ++i)
        {
            property_values.Add(values[i]);
        }

        return new wxFlagsProperty(*label, *name, property_labels, property_values, value);
    }

    EXPORT void wxFlagsProperty_Delete(wxFlagsProperty* self)
    {
        delete self;
    }

#if wxUSE_IMAGE

    EXPORT wxImageFileProperty* wxImageFileProperty_Create(wxString* label, wxString* name,
                                                           wxString* value)
    {
        return new wxImageFileProperty(*label, *name, *value);
    }

    EXPORT void wxImageFileProperty_Delete(wxImageFileProperty* self)
    {
        delete self;
    }

#else

    EXPORT void* wxImageFileProperty_Create([[maybe_unused]] wxString* label,
                                            [[maybe_unused]] wxString* name,
                                            [[maybe_unused]] wxString* value)
    {
        return nullptr;
    }

    EXPORT void wxImageFileProperty_Delete([[maybe_unused]] void* self) {}

#endif  // wxUSE_IMAGE
}
