// wx_treelistctrl.cpp
// C wrapper for wxTreeListCtrl

#include "kwx_wrapper.h"

// wxTreeListCtrl inherits from wxWindow (not wxControl).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    // wxTreeListItem helper functions
    EXPORT wxTreeListItem* wxTreeListItem_Create()
    {
        return new wxTreeListItem();
    }

    EXPORT void wxTreeListItem_Delete(wxTreeListItem* self)
    {
        delete self;
    }

    EXPORT bool wxTreeListItem_IsOk(wxTreeListItem* self)
    {
        return self->IsOk();
    }

    EXPORT wxTreeListItem* wxTreeListItem_Clone(wxTreeListItem* self)
    {
        wxTreeListItem* clone = new wxTreeListItem();
        *clone = *self;
        return clone;
    }

    // wxTreeListCtrl constructor
    EXPORT wxTreeListCtrl* wxTreeListCtrl_Create(wxWindow* parent, int id, int x, int y, int width,
                                                 int height, int style)
    {
        return new wxTreeListCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Column methods
    EXPORT int wxTreeListCtrl_AppendColumn(wxTreeListCtrl* self, wxString* title, int width,
                                           int align, int flags)
    {
        return self->AppendColumn(*title, width, (wxAlignment) align, flags);
    }

    EXPORT unsigned wxTreeListCtrl_GetColumnCount(wxTreeListCtrl* self)
    {
        return self->GetColumnCount();
    }

    EXPORT bool wxTreeListCtrl_DeleteColumn(wxTreeListCtrl* self, unsigned col)
    {
        return self->DeleteColumn(col);
    }

    EXPORT void wxTreeListCtrl_ClearColumns(wxTreeListCtrl* self)
    {
        self->ClearColumns();
    }

    EXPORT void wxTreeListCtrl_SetColumnWidth(wxTreeListCtrl* self, unsigned col, int width)
    {
        self->SetColumnWidth(col, width);
    }

    EXPORT int wxTreeListCtrl_GetColumnWidth(wxTreeListCtrl* self, unsigned col)
    {
        return self->GetColumnWidth(col);
    }

    EXPORT int wxTreeListCtrl_WidthFor(wxTreeListCtrl* self, wxString* text)
    {
        return self->WidthFor(*text);
    }

    // Item methods
    EXPORT void wxTreeListCtrl_AppendItem(wxTreeListCtrl* self, wxTreeListItem* parent,
                                          wxString* text, int imageClosed, int imageOpened,
                                          wxTreeListItem* result)
    {
        *result = self->AppendItem(*parent, *text, imageClosed, imageOpened, nullptr);
    }

    EXPORT void wxTreeListCtrl_InsertItem(wxTreeListCtrl* self, wxTreeListItem* parent,
                                          wxTreeListItem* previous, wxString* text, int imageClosed,
                                          int imageOpened, wxTreeListItem* result)
    {
        *result = self->InsertItem(*parent, *previous, *text, imageClosed, imageOpened, nullptr);
    }

    EXPORT void wxTreeListCtrl_PrependItem(wxTreeListCtrl* self, wxTreeListItem* parent,
                                           wxString* text, int imageClosed, int imageOpened,
                                           wxTreeListItem* result)
    {
        *result = self->PrependItem(*parent, *text, imageClosed, imageOpened, nullptr);
    }

    EXPORT void wxTreeListCtrl_DeleteItem(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->DeleteItem(*item);
    }

    EXPORT void wxTreeListCtrl_DeleteAllItems(wxTreeListCtrl* self)
    {
        self->DeleteAllItems();
    }

    // Tree navigation
    EXPORT void wxTreeListCtrl_GetRootItem(wxTreeListCtrl* self, wxTreeListItem* result)
    {
        *result = self->GetRootItem();
    }

    EXPORT void wxTreeListCtrl_GetItemParent(wxTreeListCtrl* self, wxTreeListItem* item,
                                             wxTreeListItem* result)
    {
        *result = self->GetItemParent(*item);
    }

    EXPORT void wxTreeListCtrl_GetFirstChild(wxTreeListCtrl* self, wxTreeListItem* item,
                                             wxTreeListItem* result)
    {
        *result = self->GetFirstChild(*item);
    }

    EXPORT void wxTreeListCtrl_GetNextSibling(wxTreeListCtrl* self, wxTreeListItem* item,
                                              wxTreeListItem* result)
    {
        *result = self->GetNextSibling(*item);
    }

    EXPORT void wxTreeListCtrl_GetFirstItem(wxTreeListCtrl* self, wxTreeListItem* result)
    {
        *result = self->GetFirstItem();
    }

    EXPORT void wxTreeListCtrl_GetNextItem(wxTreeListCtrl* self, wxTreeListItem* item,
                                           wxTreeListItem* result)
    {
        *result = self->GetNextItem(*item);
    }

    // Item attributes
    EXPORT wxString* wxTreeListCtrl_GetItemText(wxTreeListCtrl* self, wxTreeListItem* item,
                                                unsigned col)
    {
        wxString* result = new wxString();
        *result = self->GetItemText(*item, col);
        return result;
    }

    EXPORT void wxTreeListCtrl_SetItemText(wxTreeListCtrl* self, wxTreeListItem* item, unsigned col,
                                           wxString* text)
    {
        self->SetItemText(*item, col, *text);
    }

    EXPORT void wxTreeListCtrl_SetItemImage(wxTreeListCtrl* self, wxTreeListItem* item, int closed,
                                            int opened)
    {
        self->SetItemImage(*item, closed, opened);
    }

    // Expanding and collapsing
    EXPORT void wxTreeListCtrl_Expand(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->Expand(*item);
    }

    EXPORT void wxTreeListCtrl_Collapse(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->Collapse(*item);
    }

    EXPORT bool wxTreeListCtrl_IsExpanded(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        return self->IsExpanded(*item);
    }

    // Selection handling
    EXPORT void wxTreeListCtrl_GetSelection(wxTreeListCtrl* self, wxTreeListItem* result)
    {
        *result = self->GetSelection();
    }

    EXPORT void wxTreeListCtrl_Select(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->Select(*item);
    }

    EXPORT void wxTreeListCtrl_Unselect(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->Unselect(*item);
    }

    EXPORT bool wxTreeListCtrl_IsSelected(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        return self->IsSelected(*item);
    }

    EXPORT void wxTreeListCtrl_SelectAll(wxTreeListCtrl* self)
    {
        self->SelectAll();
    }

    EXPORT void wxTreeListCtrl_UnselectAll(wxTreeListCtrl* self)
    {
        self->UnselectAll();
    }

    EXPORT void wxTreeListCtrl_EnsureVisible(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->EnsureVisible(*item);
    }

    // Checkbox handling
    EXPORT void wxTreeListCtrl_CheckItem(wxTreeListCtrl* self, wxTreeListItem* item, int state)
    {
        self->CheckItem(*item, (wxCheckBoxState) state);
    }

    EXPORT void wxTreeListCtrl_UncheckItem(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        self->UncheckItem(*item);
    }

    EXPORT void wxTreeListCtrl_CheckItemRecursively(wxTreeListCtrl* self, wxTreeListItem* item,
                                                    int state)
    {
        self->CheckItemRecursively(*item, (wxCheckBoxState) state);
    }

    EXPORT void wxTreeListCtrl_UpdateItemParentStateRecursively(wxTreeListCtrl* self,
                                                                wxTreeListItem* item)
    {
        self->UpdateItemParentStateRecursively(*item);
    }

    EXPORT int wxTreeListCtrl_GetCheckedState(wxTreeListCtrl* self, wxTreeListItem* item)
    {
        return (int) self->GetCheckedState(*item);
    }

    EXPORT bool wxTreeListCtrl_AreAllChildrenInState(wxTreeListCtrl* self, wxTreeListItem* item,
                                                     int state)
    {
        return self->AreAllChildrenInState(*item, (wxCheckBoxState) state);
    }

    // Sorting
    EXPORT void wxTreeListCtrl_SetSortColumn(wxTreeListCtrl* self, unsigned col,
                                             bool ascendingOrder)
    {
        self->SetSortColumn(col, ascendingOrder);
    }

    EXPORT bool wxTreeListCtrl_GetSortColumn(wxTreeListCtrl* self, unsigned* col,
                                             bool* ascendingOrder)
    {
        return self->GetSortColumn(col, ascendingOrder);
    }

    // View window
    EXPORT wxWindow* wxTreeListCtrl_GetView(wxTreeListCtrl* self)
    {
        return self->GetView();
    }

    EXPORT wxDataViewCtrl* wxTreeListCtrl_GetDataView(wxTreeListCtrl* self)
    {
        return self->GetDataView();
    }

    // wxTreeListEvent methods
    EXPORT void wxTreeListEvent_GetItem(wxTreeListEvent* self, wxTreeListItem* result)
    {
        *result = self->GetItem();
    }

    EXPORT int wxTreeListEvent_GetOldCheckedState(wxTreeListEvent* self)
    {
        return (int) self->GetOldCheckedState();
    }

    EXPORT unsigned wxTreeListEvent_GetColumn(wxTreeListEvent* self)
    {
        return self->GetColumn();
    }

    EXPORT void wxTreeListEvent_Veto(wxTreeListEvent* self)
    {
        self->Veto();
    }

    EXPORT void wxTreeListEvent_Allow(wxTreeListEvent* self)
    {
        self->Allow();
    }

    EXPORT bool wxTreeListEvent_IsAllowed(wxTreeListEvent* self)
    {
        return self->IsAllowed();
    }

    // Event type exports
    MAKE_EVENT_WRAPPER(EVT_TREELIST_SELECTION_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_TREELIST_ITEM_EXPANDING)
    MAKE_EVENT_WRAPPER(EVT_TREELIST_ITEM_EXPANDED)
    MAKE_EVENT_WRAPPER(EVT_TREELIST_ITEM_CHECKED)
    MAKE_EVENT_WRAPPER(EVT_TREELIST_ITEM_ACTIVATED)
    MAKE_EVENT_WRAPPER(EVT_TREELIST_ITEM_CONTEXT_MENU)
    MAKE_EVENT_WRAPPER(EVT_TREELIST_COLUMN_SORTED)

    // Style constants
    WXFFI_CONSTANT_INT(expTL_SINGLE, wxTL_SINGLE)
    WXFFI_CONSTANT_INT(expTL_MULTIPLE, wxTL_MULTIPLE)
    WXFFI_CONSTANT_INT(expTL_CHECKBOX, wxTL_CHECKBOX)
    WXFFI_CONSTANT_INT(expTL_3STATE, wxTL_3STATE)
    WXFFI_CONSTANT_INT(expTL_USER_3STATE, wxTL_USER_3STATE)
    WXFFI_CONSTANT_INT(expTL_NO_HEADER, wxTL_NO_HEADER)
    WXFFI_CONSTANT_INT(expTL_DEFAULT_STYLE, wxTL_DEFAULT_STYLE)
}
