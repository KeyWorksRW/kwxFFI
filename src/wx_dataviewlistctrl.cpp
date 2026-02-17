#include "wrapper.h"

// wxDataViewListCtrl inherits from wxDataViewCtrl (wxControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // Constructor
    EXPORT wxDataViewListCtrl* wxDataViewListCtrl_Create(wxWindow* parent, int id, int x, int y,
                                                         int width, int height, int style)
    {
        return new wxDataViewListCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Store access
    EXPORT wxDataViewListStore* wxDataViewListCtrl_GetStore(wxDataViewListCtrl* self)
    {
        return self->GetStore();
    }

    // Column creation - convenience methods
    EXPORT wxDataViewColumn* wxDataViewListCtrl_AppendTextColumn(wxDataViewListCtrl* self,
                                                                 wxString* label, int mode,
                                                                 int width, int align, int flags)
    {
        return self->AppendTextColumn(*label, (wxDataViewCellMode) mode, width, (wxAlignment) align,
                                      flags);
    }

    EXPORT wxDataViewColumn* wxDataViewListCtrl_AppendToggleColumn(wxDataViewListCtrl* self,
                                                                   wxString* label, int mode,
                                                                   int width, int align, int flags)
    {
        return self->AppendToggleColumn(*label, (wxDataViewCellMode) mode, width,
                                        (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewListCtrl_AppendProgressColumn(wxDataViewListCtrl* self,
                                                                     wxString* label, int mode,
                                                                     int width, int align,
                                                                     int flags)
    {
        return self->AppendProgressColumn(*label, (wxDataViewCellMode) mode, width,
                                          (wxAlignment) align, flags);
    }

    EXPORT wxDataViewColumn* wxDataViewListCtrl_AppendIconTextColumn(wxDataViewListCtrl* self,
                                                                     wxString* label, int mode,
                                                                     int width, int align,
                                                                     int flags)
    {
        return self->AppendIconTextColumn(*label, (wxDataViewCellMode) mode, width,
                                          (wxAlignment) align, flags);
    }

    // Row/Item conversion
    EXPORT int wxDataViewListCtrl_ItemToRow(wxDataViewListCtrl* self, wxDataViewItem* item)
    {
        return self->ItemToRow(*item);
    }

    EXPORT void wxDataViewListCtrl_RowToItem(wxDataViewListCtrl* self, int row,
                                             wxDataViewItem* item)
    {
        *item = self->RowToItem(row);
    }

    // Selection by row
    EXPORT int wxDataViewListCtrl_GetSelectedRow(wxDataViewListCtrl* self)
    {
        return self->GetSelectedRow();
    }

    EXPORT void wxDataViewListCtrl_SelectRow(wxDataViewListCtrl* self, unsigned int row)
    {
        self->SelectRow(row);
    }

    EXPORT void wxDataViewListCtrl_UnselectRow(wxDataViewListCtrl* self, unsigned int row)
    {
        self->UnselectRow(row);
    }

    // Item management
    EXPORT void wxDataViewListCtrl_AppendItem(wxDataViewListCtrl* self, wxVector<wxVariant>* values,
                                              wxUIntPtr data)
    {
        self->AppendItem(*values, data);
    }

    EXPORT void wxDataViewListCtrl_PrependItem(wxDataViewListCtrl* self,
                                               wxVector<wxVariant>* values, wxUIntPtr data)
    {
        self->PrependItem(*values, data);
    }

    EXPORT void wxDataViewListCtrl_InsertItem(wxDataViewListCtrl* self, unsigned int row,
                                              wxVector<wxVariant>* values, wxUIntPtr data)
    {
        self->InsertItem(row, *values, data);
    }

    EXPORT void wxDataViewListCtrl_DeleteItem(wxDataViewListCtrl* self, unsigned int row)
    {
        self->DeleteItem(row);
    }

    EXPORT void wxDataViewListCtrl_DeleteAllItems(wxDataViewListCtrl* self)
    {
        self->DeleteAllItems();
    }

    // Value access
    EXPORT void wxDataViewListCtrl_SetValue(wxDataViewListCtrl* self, wxVariant* value,
                                            unsigned int row, unsigned int col)
    {
        self->SetValue(*value, row, col);
    }

    EXPORT void wxDataViewListCtrl_GetValue(wxDataViewListCtrl* self, wxVariant* value,
                                            unsigned int row, unsigned int col)
    {
        self->GetValue(*value, row, col);
    }

    // Text value access
    EXPORT void wxDataViewListCtrl_SetTextValue(wxDataViewListCtrl* self, wxString* value,
                                                unsigned int row, unsigned int col)
    {
        self->SetTextValue(*value, row, col);
    }

    EXPORT wxString* wxDataViewListCtrl_GetTextValue(wxDataViewListCtrl* self, unsigned int row,
                                                     unsigned int col)
    {
        wxString* result = new wxString();
        *result = self->GetTextValue(row, col);
        return result;
    }

    // Toggle value access
    EXPORT void wxDataViewListCtrl_SetToggleValue(wxDataViewListCtrl* self, bool value,
                                                  unsigned int row, unsigned int col)
    {
        self->SetToggleValue(value, row, col);
    }

    EXPORT bool wxDataViewListCtrl_GetToggleValue(wxDataViewListCtrl* self, unsigned int row,
                                                  unsigned int col)
    {
        return self->GetToggleValue(row, col);
    }

    // Item data
    EXPORT void wxDataViewListCtrl_SetItemData(wxDataViewListCtrl* self, wxDataViewItem* item,
                                               wxUIntPtr data)
    {
        self->SetItemData(*item, data);
    }

    EXPORT wxUIntPtr wxDataViewListCtrl_GetItemData(wxDataViewListCtrl* self, wxDataViewItem* item)
    {
        return self->GetItemData(*item);
    }

    // Item count
    EXPORT int wxDataViewListCtrl_GetItemCount(wxDataViewListCtrl* self)
    {
        return self->GetItemCount();
    }

    // wxVector<wxVariant> wrappers for convenience
    EXPORT wxVector<wxVariant>* wxVariantVector_Create()
    {
        return new wxVector<wxVariant>();
    }

    EXPORT void wxVariantVector_Delete(wxVector<wxVariant>* vec)
    {
        delete vec;
    }

    EXPORT void wxVariantVector_Add(wxVector<wxVariant>* vec, wxVariant* value)
    {
        vec->push_back(*value);
    }

    EXPORT void wxVariantVector_AddString(wxVector<wxVariant>* vec, wxString* value)
    {
        vec->push_back(wxVariant(*value));
    }

    EXPORT void wxVariantVector_AddLong(wxVector<wxVariant>* vec, long value)
    {
        vec->push_back(wxVariant(value));
    }

    EXPORT void wxVariantVector_AddBool(wxVector<wxVariant>* vec, bool value)
    {
        vec->push_back(wxVariant(value));
    }

    EXPORT size_t wxVariantVector_GetCount(wxVector<wxVariant>* vec)
    {
        return vec->size();
    }

    EXPORT void wxVariantVector_Clear(wxVector<wxVariant>* vec)
    {
        vec->clear();
    }

    // --- Additional wxDataViewListCtrl methods ---

    EXPORT bool wxDataViewListCtrl_IsRowSelected(wxDataViewListCtrl* self, unsigned row)
    {
        return self->IsRowSelected(row);
    }
}
