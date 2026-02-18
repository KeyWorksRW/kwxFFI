#include "kwx_wrapper.h"

// wxDataViewCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // Constructor
    EXPORT wxDataViewCtrl* wxDataViewCtrl_Create(wxWindow* parent, int id, int x, int y, int width,
                                                 int height, int style)
    {
        return new wxDataViewCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Model management
    EXPORT bool wxDataViewCtrl_AssociateModel(wxDataViewCtrl* self, wxDataViewModel* model)
    {
        return self->AssociateModel(model);
    }

    EXPORT wxDataViewModel* wxDataViewCtrl_GetModel(wxDataViewCtrl* self)
    {
        return self->GetModel();
    }

    // Column management
    EXPORT wxDataViewColumn* wxDataViewCtrl_AppendTextColumn(wxDataViewCtrl* self, wxString* label,
                                                             unsigned int model_column, int mode,
                                                             int width, int align, int flags)
    {
        return self->AppendTextColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                      (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_AppendToggleColumn(wxDataViewCtrl* self,
                                                               wxString* label,
                                                               unsigned int model_column, int mode,
                                                               int width, int align, int flags)
    {
        return self->AppendToggleColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                        (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_AppendProgressColumn(wxDataViewCtrl* self,
                                                                 wxString* label,
                                                                 unsigned int model_column,
                                                                 int mode, int width, int align,
                                                                 int flags)
    {
        return self->AppendProgressColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                          (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_AppendBitmapColumn(wxDataViewCtrl* self,
                                                               wxString* label,
                                                               unsigned int model_column, int mode,
                                                               int width, int align, int flags)
    {
        return self->AppendBitmapColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                        (wxAlignment) align, flags);
    }

    EXPORT bool wxDataViewCtrl_AppendColumn(wxDataViewCtrl* self, wxDataViewColumn* col)
    {
        return self->AppendColumn(col);
    }

    EXPORT bool wxDataViewCtrl_PrependColumn(wxDataViewCtrl* self, wxDataViewColumn* col)
    {
        return self->PrependColumn(col);
    }

    EXPORT bool wxDataViewCtrl_InsertColumn(wxDataViewCtrl* self, unsigned int pos,
                                            wxDataViewColumn* col)
    {
        return self->InsertColumn(pos, col);
    }

    EXPORT unsigned int wxDataViewCtrl_GetColumnCount(wxDataViewCtrl* self)
    {
        return self->GetColumnCount();
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_GetColumn(wxDataViewCtrl* self, unsigned int pos)
    {
        return self->GetColumn(pos);
    }

    EXPORT int wxDataViewCtrl_GetColumnPosition(wxDataViewCtrl* self, wxDataViewColumn* column)
    {
        return self->GetColumnPosition(column);
    }

    EXPORT bool wxDataViewCtrl_DeleteColumn(wxDataViewCtrl* self, wxDataViewColumn* column)
    {
        return self->DeleteColumn(column);
    }

    EXPORT bool wxDataViewCtrl_ClearColumns(wxDataViewCtrl* self)
    {
        return self->ClearColumns();
    }

    EXPORT void wxDataViewCtrl_SetExpanderColumn(wxDataViewCtrl* self, wxDataViewColumn* col)
    {
        self->SetExpanderColumn(col);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_GetExpanderColumn(wxDataViewCtrl* self)
    {
        return self->GetExpanderColumn();
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_GetSortingColumn(wxDataViewCtrl* self)
    {
        return self->GetSortingColumn();
    }

    // Item management
    EXPORT void wxDataViewCtrl_SetIndent(wxDataViewCtrl* self, int indent)
    {
        self->SetIndent(indent);
    }

    EXPORT int wxDataViewCtrl_GetIndent(wxDataViewCtrl* self)
    {
        return self->GetIndent();
    }

    EXPORT void wxDataViewCtrl_GetCurrentItem(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        *item = self->GetCurrentItem();
    }

    EXPORT void wxDataViewCtrl_SetCurrentItem(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->SetCurrentItem(*item);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_GetCurrentColumn(wxDataViewCtrl* self)
    {
        return self->GetCurrentColumn();
    }

    // Selection
    EXPORT int wxDataViewCtrl_GetSelectedItemsCount(wxDataViewCtrl* self)
    {
        return self->GetSelectedItemsCount();
    }

    EXPORT bool wxDataViewCtrl_HasSelection(wxDataViewCtrl* self)
    {
        return self->HasSelection();
    }

    EXPORT void wxDataViewCtrl_GetSelection(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        *item = self->GetSelection();
    }

    EXPORT int wxDataViewCtrl_GetSelections(wxDataViewCtrl* self, wxDataViewItemArray* sel)
    {
        return self->GetSelections(*sel);
    }

    EXPORT void wxDataViewCtrl_SetSelections(wxDataViewCtrl* self, wxDataViewItemArray* sel)
    {
        self->SetSelections(*sel);
    }

    EXPORT void wxDataViewCtrl_Select(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->Select(*item);
    }

    EXPORT void wxDataViewCtrl_Unselect(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->Unselect(*item);
    }

    EXPORT bool wxDataViewCtrl_IsSelected(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        return self->IsSelected(*item);
    }

    EXPORT void wxDataViewCtrl_SelectAll(wxDataViewCtrl* self)
    {
        self->SelectAll();
    }

    EXPORT void wxDataViewCtrl_UnselectAll(wxDataViewCtrl* self)
    {
        self->UnselectAll();
    }

    // Expanding/collapsing
    EXPORT void wxDataViewCtrl_Expand(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->Expand(*item);
    }

    EXPORT void wxDataViewCtrl_Collapse(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->Collapse(*item);
    }

    EXPORT bool wxDataViewCtrl_IsExpanded(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        return self->IsExpanded(*item);
    }

    // Visibility
    EXPORT void wxDataViewCtrl_EnsureVisible(wxDataViewCtrl* self, wxDataViewItem* item,
                                             wxDataViewColumn* column)
    {
        self->EnsureVisible(*item, column);
    }

    EXPORT void wxDataViewCtrl_HitTest(wxDataViewCtrl* self, int x, int y, wxDataViewItem* item,
                                       wxDataViewColumn** col)
    {
        wxPoint pt(x, y);
        self->HitTest(pt, *item, *col);
    }

    EXPORT void wxDataViewCtrl_GetItemRect(wxDataViewCtrl* self, wxDataViewItem* item,
                                           wxDataViewColumn* column, int* x, int* y, int* width, int* height)
    {
        wxRect rect = self->GetItemRect(*item, column);
        *x = rect.x;
        *y = rect.y;
        *width = rect.width;
        *height = rect.height;
    }

    // Editing
    EXPORT void wxDataViewCtrl_EditItem(wxDataViewCtrl* self, wxDataViewItem* item,
                                        wxDataViewColumn* column)
    {
        self->EditItem(*item, column);
    }

    // DataViewItem wrappers
    EXPORT wxDataViewItem* wxDataViewItem_Create(void* id)
    {
        return new wxDataViewItem(id);
    }

    EXPORT void wxDataViewItem_Delete(wxDataViewItem* item)
    {
        delete item;
    }

    EXPORT void* wxDataViewItem_GetID(wxDataViewItem* item)
    {
        return item->GetID();
    }

    EXPORT bool wxDataViewItem_IsOk(wxDataViewItem* item)
    {
        return item->IsOk();
    }

    // DataViewItemArray wrappers
    EXPORT wxDataViewItemArray* wxDataViewItemArray_Create()
    {
        return new wxDataViewItemArray();
    }

    EXPORT void wxDataViewItemArray_Delete(wxDataViewItemArray* arr)
    {
        delete arr;
    }

    EXPORT size_t wxDataViewItemArray_GetCount(wxDataViewItemArray* arr)
    {
        return arr->GetCount();
    }

    EXPORT void wxDataViewItemArray_Item(wxDataViewItemArray* arr, size_t index,
                                         wxDataViewItem* item)
    {
        *item = (*arr)[index];
    }

    EXPORT void wxDataViewItemArray_Add(wxDataViewItemArray* arr, wxDataViewItem* item)
    {
        arr->Add(*item);
    }

    EXPORT void wxDataViewItemArray_Clear(wxDataViewItemArray* arr)
    {
        arr->Clear();
    }

    // --- Additional wxDataViewCtrl methods ---

    EXPORT int wxDataViewCtrl_GetCountPerPage(wxDataViewCtrl* self)
    {
        return self->GetCountPerPage();
    }

    EXPORT void wxDataViewCtrl_GetTopItem(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        *item = self->GetTopItem();
    }

    EXPORT void wxDataViewCtrl_ExpandChildren(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->ExpandChildren(*item);
    }

    EXPORT void wxDataViewCtrl_ExpandAncestors(wxDataViewCtrl* self, wxDataViewItem* item)
    {
        self->ExpandAncestors(*item);
    }

    EXPORT bool wxDataViewCtrl_AllowMultiColumnSort(wxDataViewCtrl* self, bool allow)
    {
        return self->AllowMultiColumnSort(allow);
    }

    EXPORT bool wxDataViewCtrl_IsMultiColumnSortAllowed(wxDataViewCtrl* self)
    {
        return self->IsMultiColumnSortAllowed();
    }

    EXPORT void wxDataViewCtrl_ToggleSortByColumn(wxDataViewCtrl* self, int column)
    {
        self->ToggleSortByColumn(column);
    }

    EXPORT bool wxDataViewCtrl_SetRowHeight(wxDataViewCtrl* self, int rowHeight)
    {
        return self->SetRowHeight(rowHeight);
    }

    EXPORT bool wxDataViewCtrl_SetAlternateRowColour(wxDataViewCtrl* self, wxColour* colour)
    {
        return self->SetAlternateRowColour(*colour);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_AppendIconTextColumn(wxDataViewCtrl* self,
                                                                  wxString* label,
                                                                  unsigned int model_column,
                                                                  int mode, int width, int align,
                                                                  int flags)
    {
        return self->AppendIconTextColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                          (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_AppendDateColumn(wxDataViewCtrl* self, wxString* label,
                                                              unsigned int model_column, int mode,
                                                              int width, int align, int flags)
    {
        return self->AppendDateColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                      (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_PrependTextColumn(wxDataViewCtrl* self, wxString* label,
                                                               unsigned int model_column, int mode,
                                                               int width, int align, int flags)
    {
        return self->PrependTextColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                       (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_PrependIconTextColumn(wxDataViewCtrl* self,
                                                                   wxString* label,
                                                                   unsigned int model_column,
                                                                   int mode, int width, int align,
                                                                   int flags)
    {
        return self->PrependIconTextColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                           (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_PrependToggleColumn(wxDataViewCtrl* self,
                                                                 wxString* label,
                                                                 unsigned int model_column,
                                                                 int mode, int width, int align,
                                                                 int flags)
    {
        return self->PrependToggleColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                         (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_PrependProgressColumn(wxDataViewCtrl* self,
                                                                   wxString* label,
                                                                   unsigned int model_column,
                                                                   int mode, int width, int align,
                                                                   int flags)
    {
        return self->PrependProgressColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                           (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_PrependDateColumn(wxDataViewCtrl* self, wxString* label,
                                                               unsigned int model_column, int mode,
                                                               int width, int align, int flags)
    {
        return self->PrependDateColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                       (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewCtrl_PrependBitmapColumn(wxDataViewCtrl* self,
                                                                 wxString* label,
                                                                 unsigned int model_column,
                                                                 int mode, int width, int align,
                                                                 int flags)
    {
        return self->PrependBitmapColumn(*label, model_column, (wxDataViewCellMode) mode, width,
                                         (wxAlignment) align, flags);
    }
}
