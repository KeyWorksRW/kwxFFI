// wx_propgrid.cpp
// C wrapper for the wxPropertyGrid support classes: editors, multi-button editor
// controls, cells, validation info, page state, the shared property grid
// interface, and the typed property classes.

#include "kwx_wrapper.h"

#include <wx/xrc/xh_propgrid.h>

// wxPropertyGridInterface is a mixin base of wxPropertyGrid, wxPropertyGridManager
// and wxPropertyGridPage. It is a non-primary base in all three hierarchies, so a
// wxPropertyGridInterface* is not the same address as the concrete object pointer
// that kwxgen passes in (void*). Cross-cast through wxObject -- the unique
// polymorphic base shared by all three consumers -- with dynamic_cast.
static inline wxPropertyGridInterface* AsPropertyGridInterface(void* self)
{
    return dynamic_cast<wxPropertyGridInterface*>(static_cast<wxObject*>(self));
}

// ===========================================================================
// wxPGEditor
// ===========================================================================

extern "C"
{
    EXPORT wxString* wxPGEditor_GetName(wxPGEditor* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT int wxPGEditor_CanContainCustomImage(wxPGEditor* self)
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

    EXPORT int wxPGCell_HasText(wxPGCell* self)
    {
        return self->HasText();
    }

    EXPORT int wxPGCell_IsInvalid(wxPGCell* self)
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

    EXPORT int wxNumericPropertyValidator_Validate(wxNumericPropertyValidator* self,
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

    EXPORT int wxNumericPropertyValidator_Validate([[maybe_unused]] void* self,
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

    EXPORT int wxPGArrayEditorDialog_IsModified(wxPGArrayEditorDialog* self)
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

    EXPORT int wxPGArrayEditorDialog_IsModified([[maybe_unused]] void* self)
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

    // ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
    EXPORT void wxPGArrayEditorDialog_Init(void* pObject)
    {
        ((wxPGArrayEditorDialog*) pObject)->Init();
    }

    EXPORT void* wxPropertyGridInterface_GetProperty(void* pObject, void* name)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(pObject);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetProperty(*static_cast<wxString*>(name));
    }

    EXPORT void wxPropertyGridInterface_RegisterAdditionalEditors()
    {
        wxPropertyGridInterface::RegisterAdditionalEditors();
    }

    EXPORT void wxPropertyGridInterface_SetPropertyAttributeAll(void* pObject, void* attrName,
                                                                void* value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(pObject);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyAttributeAll(*static_cast<wxString*>(attrName),
                                       *static_cast<wxVariant*>(value));
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

    EXPORT int wxPropertyGridPageState_EnableCategories(wxPropertyGridPageState* self, bool enable)
    {
        return self->EnableCategories(enable);
    }

    EXPORT int wxPropertyGridPageState_IsDisplayed(wxPropertyGridPageState* self)
    {
        return self->IsDisplayed();
    }

    EXPORT int wxPropertyGridPageState_IsInNonCatMode(wxPropertyGridPageState* self)
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

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyByName(void* self, wxString* name)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyByName(*name);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyByName2(void* self, wxString* name,
                                                                    wxString* subname)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyByName(*name, *subname);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyByLabel(void* self, wxString* label)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyByLabel(*label);
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyName(void* self, wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxString();
        }

        return new wxString(iface->GetPropertyName(property));
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyLabel(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxString();
        }

        return new wxString(iface->GetPropertyLabel(id));
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyHelpString(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxString();
        }

        return new wxString(iface->GetPropertyHelpString(id));
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetPropertyParent(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyParent(id);
    }

    EXPORT wxPropertyCategory* wxPropertyGridInterface_GetPropertyCategory(void* self,
                                                                           wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyCategory(id);
    }

    EXPORT wxPGEditor* wxPropertyGridInterface_GetPropertyEditor(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return const_cast<wxPGEditor*>(iface->GetPropertyEditor(id));
    }

    EXPORT wxBitmap* wxPropertyGridInterface_GetPropertyImage(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyImage(id);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetFirstChild(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetFirstChild(id);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetFirst(void* self, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetFirst(flags);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_GetSelection(void* self)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetSelection();
    }

    EXPORT wxPropertyGridPageState* wxPropertyGridInterface_GetState(void* self)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetState();
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_Append(void* self, wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->Append(property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_AppendIn(void* self, wxPGProperty* id,
                                                          wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->AppendIn(id, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_Insert(void* self, wxPGProperty* prior_this,
                                                        wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->Insert(prior_this, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_Insert2(void* self, wxPGProperty* parent,
                                                         int index, wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->Insert(parent, index, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_ReplaceProperty(void* self, wxPGProperty* id,
                                                                 wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->ReplaceProperty(id, property);
    }

    EXPORT wxPGProperty* wxPropertyGridInterface_RemoveProperty(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->RemoveProperty(id);
    }

    EXPORT void wxPropertyGridInterface_DeleteProperty(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->DeleteProperty(id);
    }

    EXPORT void wxPropertyGridInterface_Clear(void* self)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->Clear();
    }

    EXPORT int wxPropertyGridInterface_ClearSelection(void* self, bool validation)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->ClearSelection(validation);
    }

    EXPORT void wxPropertyGridInterface_ClearModifiedStatus(void* self)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->ClearModifiedStatus();
    }

    EXPORT int wxPropertyGridInterface_EditorValidate(void* self)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->EditorValidate();
    }

    EXPORT int wxPropertyGridInterface_Collapse(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->Collapse(id);
    }

    EXPORT int wxPropertyGridInterface_CollapseAll(void* self)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->CollapseAll();
    }

    EXPORT int wxPropertyGridInterface_Expand(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->Expand(id);
    }

    EXPORT int wxPropertyGridInterface_ExpandAll(void* self, bool expand)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->ExpandAll(expand);
    }

    EXPORT int wxPropertyGridInterface_DisableProperty(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->DisableProperty(id);
    }

    EXPORT int wxPropertyGridInterface_EnableProperty(void* self, wxPGProperty* id, bool enable)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->EnableProperty(id, enable);
    }

    EXPORT int wxPropertyGridInterface_HideProperty(void* self, wxPGProperty* id, bool hide,
                                                    int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->HideProperty(id, hide, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_LimitPropertyEditing(void* self, wxPGProperty* id,
                                                             bool limit)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->LimitPropertyEditing(id, limit);
    }

    EXPORT void wxPropertyGridInterface_RefreshGrid(void* self, wxPropertyGridPageState* state)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->RefreshGrid(state);
    }

    EXPORT void wxPropertyGridInterface_RefreshProperty(void* self, wxPGProperty* property)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->RefreshProperty(property);
    }

    EXPORT wxVariant* wxPropertyGridInterface_GetPropertyValue(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxVariant();
        }

        return new wxVariant(iface->GetPropertyValue(id));
    }

    EXPORT wxString* wxPropertyGridInterface_GetPropertyValueAsString(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxString();
        }

        return new wxString(iface->GetPropertyValueAsString(id));
    }

    EXPORT long wxPropertyGridInterface_GetPropertyValueAsLong(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return 0;
        }

        return iface->GetPropertyValueAsLong(id);
    }

    EXPORT int wxPropertyGridInterface_GetPropertyValueAsInt(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return 0;
        }

        return iface->GetPropertyValueAsInt(id);
    }

    EXPORT int wxPropertyGridInterface_GetPropertyValueAsBool(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->GetPropertyValueAsBool(id);
    }

    EXPORT double wxPropertyGridInterface_GetPropertyValueAsDouble(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return 0.0;
        }

        return iface->GetPropertyValueAsDouble(id);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValue(void* self, wxPGProperty* id,
                                                         wxVariant* value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !value)
        {
            return;
        }

        iface->SetPropertyValue(id, *value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueString(void* self, wxPGProperty* id,
                                                               wxString* value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !value)
        {
            return;
        }

        iface->SetPropertyValueString(id, *value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueLong(void* self, wxPGProperty* id,
                                                             long value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueInt(void* self, wxPGProperty* id, int value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueDouble(void* self, wxPGProperty* id,
                                                               double value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueBool(void* self, wxPGProperty* id,
                                                             bool value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyValue(id, value);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValueUnspecified(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyValueUnspecified(id);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyLabel(void* self, wxPGProperty* id,
                                                         wxString* label)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !label)
        {
            return;
        }

        iface->SetPropertyLabel(id, *label);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyName(void* self, wxPGProperty* id,
                                                        wxString* name)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !name)
        {
            return;
        }

        iface->SetPropertyName(id, *name);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyHelpString(void* self, wxPGProperty* id,
                                                              wxString* text)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !text)
        {
            return;
        }

        iface->SetPropertyHelpString(id, *text);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyReadOnly(void* self, wxPGProperty* id,
                                                            bool read_only, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyReadOnly(id, read_only, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_SetPropertyEditor(void* self, wxPGProperty* id,
                                                          wxPGEditor* editor)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyEditor(id, editor);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyEditorByName(void* self, wxPGProperty* id,
                                                                wxString* name)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !name)
        {
            return;
        }

        iface->SetPropertyEditor(id, *name);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyImage(void* self, wxPGProperty* id,
                                                         wxBitmapBundle* bitmap)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !bitmap)
        {
            return;
        }

        iface->SetPropertyImage(id, *bitmap);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyCell(void* self, wxPGProperty* id, int column,
                                                        wxString* text, wxBitmapBundle* bitmap,
                                                        wxColour* fg_col, wxColour* bg_col)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyCell(id, column, text ? *text : wxString(),
                               bitmap ? *bitmap : wxBitmapBundle(), fg_col ? *fg_col : wxColour(),
                               bg_col ? *bg_col : wxColour());
    }

    EXPORT int wxPropertyGridInterface_IsPropertyCategory(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertyCategory(id);
    }

    EXPORT int wxPropertyGridInterface_IsPropertyEnabled(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertyEnabled(id);
    }

    EXPORT int wxPropertyGridInterface_IsPropertyExpanded(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertyExpanded(id);
    }

    EXPORT int wxPropertyGridInterface_IsPropertyModified(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertyModified(id);
    }

    EXPORT int wxPropertyGridInterface_IsPropertySelected(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertySelected(id);
    }

    EXPORT int wxPropertyGridInterface_IsPropertyShown(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertyShown(id);
    }

    EXPORT int wxPropertyGridInterface_IsPropertyValueUnspecified(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->IsPropertyValueUnspecified(id);
    }

    EXPORT int wxPropertyGridInterface_SetColumnProportion(void* self, unsigned int column,
                                                           int proportion)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->SetColumnProportion(column, proportion);
    }

    EXPORT int wxPropertyGridInterface_GetColumnProportion(void* self, unsigned int column)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return 0;
        }

        return iface->GetColumnProportion(column);
    }

    EXPORT wxString* wxPropertyGridInterface_SaveEditableState(void* self, int included_states)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxString();
        }

        return new wxString(iface->SaveEditableState(included_states));
    }

    EXPORT int wxPropertyGridInterface_RestoreEditableState(void* self, wxString* src,
                                                            int restore_states)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !src)
        {
            return false;
        }

        return iface->RestoreEditableState(*src, restore_states);
    }

    EXPORT void wxPropertyGridInterface_Sort(void* self, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->Sort(static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_SortChildren(void* self, wxPGProperty* id, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SortChildren(id, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    // ---- Additional wxPropertyGridInterface methods ----

    EXPORT void wxPropertyGridInterface_BeginAddChildren(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->BeginAddChildren(id);
    }

    EXPORT void wxPropertyGridInterface_EndAddChildren(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->EndAddChildren(id);
    }

    EXPORT int wxPropertyGridInterface_ChangePropertyValue(void* self, wxPGProperty* id,
                                                           wxVariant* value)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !value)
        {
            return false;
        }

        return iface->ChangePropertyValue(id, *value);
    }

    EXPORT wxVariant* wxPropertyGridInterface_GetPropertyAttribute(void* self, wxPGProperty* id,
                                                                   wxString* attrName)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !attrName)
        {
            return new wxVariant();
        }

        return new wxVariant(iface->GetPropertyAttribute(id, *attrName));
    }

    EXPORT void wxPropertyGridInterface_SetPropertyAttribute(void* self, wxPGProperty* id,
                                                             wxString* attrName, wxVariant* value,
                                                             int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !attrName || !value)
        {
            return;
        }

        iface->SetPropertyAttribute(id, *attrName, *value,
                                    static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void* wxPropertyGridInterface_GetPropertyClientData(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyClientData(id);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyClientData(void* self, wxPGProperty* id,
                                                              void* clientData)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyClientData(id, clientData);
    }

    EXPORT wxValidator* wxPropertyGridInterface_GetPropertyValidator(void* self, wxPGProperty* id)
    {
#if wxUSE_VALIDATORS
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return nullptr;
        }

        return iface->GetPropertyValidator(id);
#else
        wxUnusedVar(self);
        wxUnusedVar(id);
        return nullptr;
#endif
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValidator(void* self, wxPGProperty* id,
                                                             wxValidator* validator)
    {
#if wxUSE_VALIDATORS
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !validator)
        {
            return;
        }

        iface->SetPropertyValidator(id, *validator);
#else
        wxUnusedVar(self);
        wxUnusedVar(id);
        wxUnusedVar(validator);
#endif
    }

    EXPORT wxVariant* wxPropertyGridInterface_GetPropertyValues(void* self, wxString* listname,
                                                                wxPGProperty* baseparent, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxVariant();
        }

        return new wxVariant(iface->GetPropertyValues(listname ? *listname : wxString(), baseparent,
                                                      static_cast<wxPGPropertyValuesFlags>(flags)));
    }

    EXPORT void wxPropertyGridInterface_SetPropertyValues(void* self, wxVariant* list,
                                                          wxPGProperty* baseparent)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !list)
        {
            return;
        }

        iface->SetPropertyValues(*list, baseparent);
    }

    EXPORT void wxPropertyGridInterface_SetPropertyBackgroundColour(void* self, wxPGProperty* id,
                                                                    wxColour* colour, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !colour)
        {
            return;
        }

        iface->SetPropertyBackgroundColour(id, *colour,
                                           static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_SetPropertyTextColour(void* self, wxPGProperty* id,
                                                              wxColour* colour, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface || !colour)
        {
            return;
        }

        iface->SetPropertyTextColour(id, *colour, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT void wxPropertyGridInterface_SetPropertyColoursToDefault(void* self, wxPGProperty* id,
                                                                    int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetPropertyColoursToDefault(id, static_cast<wxPGPropertyValuesFlags>(flags));
    }

    EXPORT wxColour* wxPropertyGridInterface_GetPropertyBackgroundColour(void* self,
                                                                         wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxColour();
        }

        return new wxColour(iface->GetPropertyBackgroundColour(id));
    }

    EXPORT wxColour* wxPropertyGridInterface_GetPropertyTextColour(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxColour();
        }

        return new wxColour(iface->GetPropertyTextColour(id));
    }

    EXPORT int wxPropertyGridInterface_SetPropertyMaxLength(void* self, wxPGProperty* id,
                                                            int maxLen)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return false;
        }

        return iface->SetPropertyMaxLength(id, maxLen);
    }

    EXPORT void wxPropertyGridInterface_SetValidationFailureBehavior(void* self, int flags)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return;
        }

        iface->SetValidationFailureBehavior(static_cast<wxPGVFBFlags>(flags));
    }

    EXPORT unsigned long wxPropertyGridInterface_GetPropertyValueAsULong(void* self,
                                                                         wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return 0;
        }

        return iface->GetPropertyValueAsULong(id);
    }

    EXPORT int64_t wxPropertyGridInterface_GetPropertyValueAsLongLong(void* self, wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return 0;
        }

        return iface->GetPropertyValueAsLongLong(id);
    }

    EXPORT wxArrayString* wxPropertyGridInterface_GetPropertyValueAsArrayString(void* self,
                                                                                wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxArrayString();
        }

        return new wxArrayString(iface->GetPropertyValueAsArrayString(id));
    }

    EXPORT wxArrayInt* wxPropertyGridInterface_GetPropertyValueAsArrayInt(void* self,
                                                                          wxPGProperty* id)
    {
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxArrayInt();
        }

        return new wxArrayInt(iface->GetPropertyValueAsArrayInt(id));
    }

    EXPORT wxDateTime* wxPropertyGridInterface_GetPropertyValueAsDateTime(void* self,
                                                                          wxPGProperty* id)
    {
#if wxUSE_DATETIME
        wxPropertyGridInterface* const iface = AsPropertyGridInterface(self);
        if (!iface)
        {
            return new wxDateTime();
        }

        return new wxDateTime(iface->GetPropertyValueAsDateTime(id));
#else
        wxUnusedVar(self);
        wxUnusedVar(id);
        return new wxDateTime();
#endif
    }

    EXPORT wxPGEditor* wxPropertyGridInterface_GetEditorByName(wxString* name)
    {
        return wxPropertyGridInterface::GetEditorByName(*name);
    }

    EXPORT void wxPropertyGridInterface_InitAllTypeHandlers()
    {
        wxPropertyGridInterface::InitAllTypeHandlers();
    }

    EXPORT void wxPropertyGridInterface_SetBoolChoices(wxString* trueChoice, wxString* falseChoice)
    {
        wxPropertyGridInterface::SetBoolChoices(trueChoice ? *trueChoice : wxString(),
                                                falseChoice ? *falseChoice : wxString());
    }

    // =======================================================================
    // wxColourPropertyValue
    // =======================================================================

    EXPORT wxColourPropertyValue* wxColourPropertyValue_Create()
    {
        return new wxColourPropertyValue();
    }

    EXPORT wxColourPropertyValue* wxColourPropertyValue_CreateWithType(unsigned int type,
                                                                       wxColour* colour)
    {
        return new wxColourPropertyValue(type, colour ? *colour : wxColour());
    }

    EXPORT wxColourPropertyValue* wxColourPropertyValue_CreateFromColour(wxColour* colour)
    {
        return new wxColourPropertyValue(colour ? *colour : wxColour());
    }

    EXPORT void wxColourPropertyValue_Delete(wxColourPropertyValue* self)
    {
        delete self;
    }

    EXPORT void wxColourPropertyValue_Init(wxColourPropertyValue* self, unsigned int type,
                                           wxColour* colour)
    {
        self->Init(type, colour ? *colour : wxColour());
    }

    EXPORT unsigned int wxColourPropertyValue_GetType(wxColourPropertyValue* self)
    {
        return self->m_type;
    }

    EXPORT void wxColourPropertyValue_SetType(wxColourPropertyValue* self, unsigned int type)
    {
        self->m_type = type;
    }

    EXPORT wxColour* wxColourPropertyValue_GetColour(wxColourPropertyValue* self)
    {
        return new wxColour(self->m_colour);
    }

    EXPORT void wxColourPropertyValue_SetColour(wxColourPropertyValue* self, wxColour* colour)
    {
        self->m_colour = colour ? *colour : wxColour();
    }

    EXPORT wxColourPropertyValue* wxVariant_GetColourPropertyValue(wxVariant* variant)
    {
        if (!variant || variant->GetType() != "wxColourPropertyValue")
        {
            return nullptr;
        }

        auto* result = new wxColourPropertyValue();
        *result << *variant;
        return result;
    }

    // =======================================================================
    // wxPropertyGridXmlHandler
    // =======================================================================

    EXPORT wxPropertyGridXmlHandler* wxPropertyGridXmlHandler_Create()
    {
        return new wxPropertyGridXmlHandler();
    }

    EXPORT void wxPropertyGridXmlHandler_Delete(wxPropertyGridXmlHandler* self)
    {
        delete self;
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
