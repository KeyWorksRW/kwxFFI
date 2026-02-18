#include "kwx_wrapper.h"

// wxListCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    typedef int (*kwxSortFunc)(void* obj, int data1, int data2);

    typedef struct fnSort
    {
        void* obj;
        kwxSortFunc fnc;
    } kwxSort;

    int wxCALLBACK ListCmp(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
    {
        return ((kwxSort*) sortData)->fnc(((kwxSort*) sortData)->obj, (int) item1, (int) item2);
    }

    EXPORT wxListItem* wxListItem_Create()
    {
        return new wxListItem();
    }

    EXPORT void wxListItem_Delete(wxListItem* self)
    {
        delete self;
    }

    EXPORT void wxListItem_Clear(wxListItem* self)
    {
        self->Clear();
    }

    EXPORT void wxListItem_ClearAttributes(wxListItem* self)
    {
        self->ClearAttributes();
    }

    EXPORT void wxListItem_SetMask(wxListItem* self, int mask)
    {
        self->SetMask((long) mask);
    }

    EXPORT void wxListItem_SetId(wxListItem* self, int id)
    {
        self->SetId((long) id);
    }

    EXPORT void wxListItem_SetColumn(wxListItem* self, int col)
    {
        self->SetColumn(col);
    }

    EXPORT void wxListItem_SetState(wxListItem* self, int state)
    {
        self->SetState((long) state);
    }

    EXPORT void wxListItem_SetStateMask(wxListItem* self, int stateMask)
    {
        self->SetStateMask((long) stateMask);
    }

    EXPORT void wxListItem_SetText(wxListItem* self, wxString* text)
    {
        self->SetText(*text);
    }

    EXPORT void wxListItem_SetImage(wxListItem* self, int image)
    {
        self->SetImage(image);
    }

    EXPORT void wxListItem_SetData(wxListItem* self, int data)
    {
        self->SetData((long) data);
    }

    EXPORT void wxListItem_SetDataPointer(wxListItem* self, void* data)
    {
        self->SetData(data);
    }

    EXPORT void wxListItem_SetWidth(wxListItem* self, int width)
    {
        self->SetWidth(width);
    }

    EXPORT void wxListItem_SetAlign(wxListItem* self, int align)
    {
        self->SetAlign((wxListColumnFormat) align);
    }

    EXPORT void wxListItem_SetTextColour(wxListItem* self, wxColour* colText)
    {
        self->SetTextColour(*colText);
    }

    EXPORT void wxListItem_SetBackgroundColour(wxListItem* self, wxColour* colBack)
    {
        self->SetBackgroundColour(*colBack);
    }

    EXPORT void wxListItem_SetFont(wxListItem* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT long wxListItem_GetMask(wxListItem* self)
    {
        return self->GetMask();
    }

    EXPORT long wxListItem_GetId(wxListItem* self)
    {
        return self->GetId();
    }

    EXPORT int wxListItem_GetColumn(wxListItem* self)
    {
        return self->GetColumn();
    }

    EXPORT long wxListItem_GetState(wxListItem* self)
    {
        return self->GetState();
    }

    EXPORT wxString* wxListItem_GetText(wxListItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetText();
        return result;
    }

    EXPORT int wxListItem_GetImage(wxListItem* self)
    {
        return self->GetImage();
    }

    EXPORT long wxListItem_GetData(wxListItem* self)
    {
        return self->GetData();
    }

    EXPORT int wxListItem_GetWidth(wxListItem* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxListItem_GetAlign(wxListItem* self)
    {
        return (int) self->GetAlign();
    }

    EXPORT void* wxListItem_GetAttributes(wxListItem* self)
    {
        return (void*) self->GetAttributes();
    }

    EXPORT int wxListItem_HasAttributes(wxListItem* self)
    {
        return (int) self->HasAttributes();
    }

    EXPORT void wxListItem_GetTextColour(wxListItem* self, wxColour* colour)
    {
        *colour = self->GetTextColour();
    }

    EXPORT void wxListItem_GetBackgroundColour(wxListItem* self, wxColour* colour)
    {
        *colour = self->GetBackgroundColour();
    }

    EXPORT void wxListItem_GetFont(wxListItem* self, wxFont* font)
    {
        *font = self->GetFont();
    }

    EXPORT void* wxListCtrl_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                   int style)
    {
        return new wxListCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxListCtrl_SetForegroundColour(wxListCtrl* self, wxColour* col)
    {
        return (int) self->SetForegroundColour(*col);
    }

    EXPORT int wxListCtrl_SetBackgroundColour(wxListCtrl* self, wxColour* col)
    {
        return (int) self->SetBackgroundColour(*col);
    }

    EXPORT int wxListCtrl_GetColumn(wxListCtrl* self, int col, wxListItem* item)
    {
        return (int) self->GetColumn(col, *item);
    }

    EXPORT int wxListCtrl_SetColumn(wxListCtrl* self, int col, wxListItem* item)
    {
        return (int) self->SetColumn(col, *item);
    }

    EXPORT int wxListCtrl_GetColumnWidth(wxListCtrl* self, int col)
    {
        return self->GetColumnWidth(col);
    }

    EXPORT bool wxListCtrl_SetColumnWidth(wxListCtrl* self, int col, int width)
    {
        return self->SetColumnWidth(col, width);
    }

    EXPORT int wxListCtrl_GetCountPerPage(wxListCtrl* self)
    {
        return self->GetCountPerPage();
    }

    EXPORT void* wxListCtrl_GetEditControl(wxListCtrl* self)
    {
#ifdef __WIN32__
        return (void*) self->GetEditControl();
#else
        return nullptr;
#endif
    }

    EXPORT int wxListCtrl_GetItem(wxListCtrl* self, wxListItem* info)
    {
        return (int) self->GetItem(*info);
    }

    EXPORT bool wxListCtrl_SetItemFromInfo(wxListCtrl* self, wxListItem* info)
    {
        return self->SetItem(*info);
    }

    EXPORT bool wxListCtrl_SetItem(wxListCtrl* self, int index, int col, wxString* label,
                                   int imageId)
    {
        return self->SetItem((long) index, col, *label, imageId);
    }

    EXPORT int wxListCtrl_GetItemState(wxListCtrl* self, int item, int stateMask)
    {
        return self->GetItemState((long) item, (long) stateMask);
    }

    EXPORT bool wxListCtrl_SetItemState(wxListCtrl* self, int item, int state, int stateMask)
    {
        return self->SetItemState((long) item, (long) state, (long) stateMask);
    }

    EXPORT bool wxListCtrl_SetItemImage(wxListCtrl* self, int item, int image, int selImage)
    {
        return self->SetItemImage((long) item, image, selImage);
    }

    EXPORT wxString* wxListCtrl_GetItemText(wxListCtrl* self, int item, int col)
    {
        wxString* result = new wxString();
        *result = self->GetItemText((long) item, col);
        return result;
    }

    EXPORT void wxListCtrl_SetItemText(wxListCtrl* self, int item, wxString* str)
    {
        self->SetItemText((long) item, *str);
    }

    EXPORT int wxListCtrl_GetItemData(wxListCtrl* self, int item)
    {
        return (int) self->GetItemData((long) item);
    }

    EXPORT bool wxListCtrl_SetItemData(wxListCtrl* self, int item, int data)
    {
        return self->SetItemData((long) item, (long) data);
    }

    EXPORT wxRect* wxListCtrl_GetItemRect(wxListCtrl* self, int item, int code)
    {
        wxRect* rct = new wxRect();
        bool result = self->GetItemRect((long) item, *rct, code);
        if (result)
        {
            return rct;
        }
        return nullptr;
    }

    EXPORT wxPoint* wxListCtrl_GetItemPosition(wxListCtrl* self, int item)
    {
        wxPoint* pos = new wxPoint();
        bool result = self->GetItemPosition((long) item, *pos);
        if (result)
        {
            return pos;
        }
        return nullptr;
    }

    EXPORT int wxListCtrl_SetItemPosition(wxListCtrl* self, int item, int x, int y)
    {
        return self->SetItemPosition((long) item, wxPoint(x, y));
    }

    EXPORT int wxListCtrl_GetItemCount(wxListCtrl* self)
    {
        return self->GetItemCount();
    }

    EXPORT int wxListCtrl_GetColumnCount(wxListCtrl* self)
    {
        return self->GetColumnCount();
    }

    EXPORT wxSize* wxListCtrl_GetItemSpacing(wxListCtrl* self, bool isSmall)
    {
        wxSize* text = new wxSize();
        *text = self->GetItemSpacing();
        return text;
    }

    EXPORT int wxListCtrl_GetSelectedItemCount(wxListCtrl* self)
    {
        return self->GetSelectedItemCount();
    }

    EXPORT void wxListCtrl_GetTextColour(wxListCtrl* self, wxColour* colour)
    {
        *colour = self->GetTextColour();
    }

    EXPORT void wxListCtrl_SetTextColour(wxListCtrl* self, wxColour* col)
    {
        self->SetTextColour(*col);
    }

    EXPORT int wxListCtrl_GetTopItem(wxListCtrl* self)
    {
        return (int) self->GetTopItem();
    }

    EXPORT void wxListCtrl_SetSingleStyle(wxListCtrl* self, int style, bool add)
    {
        self->SetSingleStyle((long) style, add);
    }

    EXPORT void wxListCtrl_SetWindowStyleFlag(wxListCtrl* self, int style)
    {
        self->SetWindowStyleFlag((long) style);
    }

    EXPORT int wxListCtrl_GetNextItem(wxListCtrl* self, int item, int geometry, int state)
    {
        return self->GetNextItem((long) item, geometry, state);
    }

    EXPORT void* wxListCtrl_GetImageList(wxListCtrl* self, int which)
    {
        return (void*) self->GetImageList(which);
    }

    EXPORT void wxListCtrl_SetImageList(wxListCtrl* self, void* imageList, int which)
    {
        self->SetImageList((wxImageList*) imageList, which);
    }

    EXPORT bool wxListCtrl_Arrange(wxListCtrl* self, int flag)
    {
        return self->Arrange(flag);
    }

    EXPORT bool wxListCtrl_DeleteItem(wxListCtrl* self, int item)
    {
        return self->DeleteItem((long) item);
    }

    EXPORT bool wxListCtrl_DeleteAllItems(wxListCtrl* self)
    {
        return self->DeleteAllItems();
    }

    EXPORT bool wxListCtrl_DeleteColumn(wxListCtrl* self, int col)
    {
        return self->DeleteColumn(col);
    }

    EXPORT int wxListCtrl_DeleteAllColumns(wxListCtrl* self)
    {
        return (int) self->DeleteAllColumns();
    }

    EXPORT void wxListCtrl_ClearAll(wxListCtrl* self)
    {
        self->ClearAll();
    }

    EXPORT void wxListCtrl_EditLabel(wxListCtrl* self, int item)
    {
        self->EditLabel((long) item);
    }

    EXPORT bool wxListCtrl_EndEditLabel(wxListCtrl* self, bool cancel)
    {
#ifdef __WIN32__
        return self->EndEditLabel(cancel);
#else
        return false;
#endif
    }

    EXPORT bool wxListCtrl_EnsureVisible(wxListCtrl* self, int item)
    {
        return self->EnsureVisible((long) item);
    }

    EXPORT int wxListCtrl_FindItem(wxListCtrl* self, int start, wxString* str, bool partial)
    {
        return (long) self->FindItem((long) start, *str, partial);
    }

    EXPORT int wxListCtrl_FindItemByData(wxListCtrl* self, int start, int data)
    {
        return (int) self->FindItem((long) start, (long) data);
    }

    EXPORT int wxListCtrl_FindItemByPosition(wxListCtrl* self, int start, int x, int y,
                                             int direction)
    {
        return (int) self->FindItem((long) start, wxPoint(x, y), direction);
    }

    EXPORT int wxListCtrl_HitTest(wxListCtrl* self, int x, int y, void* flags, long* pSubItem)
    {
        return self->HitTest(wxPoint(x, y), *((int*) flags), pSubItem);
    }

    EXPORT int wxListCtrl_InsertItem(wxListCtrl* self, wxListItem* info)
    {
        return (int) self->InsertItem(*info);
    }

    EXPORT int wxListCtrl_InsertItemWithData(wxListCtrl* self, int index, wxString* label)
    {
        return (int) self->InsertItem((long) index, *label);
    }

    EXPORT int wxListCtrl_InsertItemWithImage(wxListCtrl* self, int index, int imageIndex)
    {
        return (int) self->InsertItem((long) index, imageIndex);
    }

    EXPORT int wxListCtrl_InsertItemWithLabel(wxListCtrl* self, int index, wxString* label,
                                              int imageIndex)
    {
        return (int) self->InsertItem((long) index, *label, imageIndex);
    }

    EXPORT int wxListCtrl_InsertColumnFromInfo(wxListCtrl* self, int col, wxListItem* info)
    {
        return (int) self->InsertColumn((long) col, *info);
    }

    EXPORT int wxListCtrl_InsertColumn(wxListCtrl* self, int col, wxString* heading, int format,
                                       int width)
    {
        return (int) self->InsertColumn((long) col, *heading, format, width);
    }

    EXPORT bool wxListCtrl_ScrollList(wxListCtrl* self, int dx, int dy)
    {
        return self->ScrollList(dx, dy);
    }

    EXPORT bool wxListCtrl_SortItems(wxListCtrl* self, void* fnc, void* obj)
    {
        kwxSort srt = { obj, (kwxSortFunc) fnc };
        return self->SortItems(ListCmp, (wxIntPtr) &srt);
    }

    EXPORT wxFont* wxListCtrl_GetItemFont(wxListCtrl* self, long item)
    {
        wxFont* fnt = new wxFont;
        *fnt = self->GetItemFont(item);
        return fnt;
    }

    EXPORT bool wxListCtrl_IsVirtual(wxListCtrl* self)
    {
        return self->IsVirtual();
    }

    EXPORT void wxListCtrl_RefreshItem(wxListCtrl* self, long item)
    {
        self->RefreshItem(item);
    }

    EXPORT void wxListCtrl_RefreshItems(wxListCtrl* self, long from, long toPos)
    {
        self->RefreshItems(from, toPos);
    }

    EXPORT bool wxListCtrl_GetSubItemRect(wxListCtrl* self, long item, long subItem, int* x, int* y,
                                          int* width, int* height, int code)
    {
        wxRect rect;
        bool result = self->GetSubItemRect(item, subItem, rect, code);
        *x = rect.x;
        *y = rect.y;
        *width = rect.width;
        *height = rect.height;
        return result;
    }

    EXPORT void wxListCtrl_GetViewRect(wxListCtrl* self, int* x, int* y, int* width, int* height)
    {
        wxRect rect = self->GetViewRect();
        *x = rect.x;
        *y = rect.y;
        *width = rect.width;
        *height = rect.height;
    }

    EXPORT bool wxListCtrl_HasCheckBoxes(wxListCtrl* self)
    {
        return self->HasCheckBoxes();
    }

    EXPORT bool wxListCtrl_EnableCheckBoxes(wxListCtrl* self, bool enable)
    {
        return self->EnableCheckBoxes(enable);
    }

    EXPORT bool wxListCtrl_IsItemChecked(wxListCtrl* self, long item)
    {
        return self->IsItemChecked(item);
    }

    EXPORT void wxListCtrl_CheckItem(wxListCtrl* self, long item, bool check)
    {
        self->CheckItem(item, check);
    }

    EXPORT void wxListCtrl_ShowSortIndicator(wxListCtrl* self, int col, bool ascending)
    {
        self->ShowSortIndicator(col, ascending);
    }

    EXPORT int wxListCtrl_GetSortIndicator(wxListCtrl* self)
    {
        return self->GetSortIndicator();
    }

    EXPORT bool wxListCtrl_IsAscendingSortIndicator(wxListCtrl* self)
    {
        return self->IsAscendingSortIndicator();
    }

    EXPORT bool wxListCtrl_IsVisible(wxListCtrl* self, long item)
    {
        return self->IsVisible(item);
    }

    EXPORT void wxListCtrl_SetItemCount(wxListCtrl* self, long count)
    {
        self->SetItemCount(count);
    }

    EXPORT bool wxListCtrl_SetHeaderAttr(wxListCtrl* self, wxItemAttr* attr)
    {
        return self->SetHeaderAttr(*attr);
    }
}
