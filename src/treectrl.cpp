#include "wrapper.h"

class wxcTreeItemData : public wxTreeItemData
{
private:
    wxClosure* m_closure;

public:
    wxcTreeItemData(wxClosure* closure) { m_closure = closure; }

    ~wxcTreeItemData()
    {
        if (m_closure)
            delete m_closure;
    }

    wxClosure* GetClientClosure() { return m_closure; }

    void SetClientClosure(wxClosure* closure)
    {
        if (m_closure)
            delete m_closure;
        m_closure = closure;
    }
};

extern "C"
{
    EXPORT wxcTreeItemData* wxcTreeItemData_Create(wxClosure* closure)
    {
        return new wxcTreeItemData(closure);
    }

    EXPORT wxClosure* wxcTreeItemData_GetClientClosure(wxcTreeItemData* self)
    {
        return self->GetClientClosure();
    }

    EXPORT void wxcTreeItemData_SetClientClosure(wxcTreeItemData* self, wxClosure* closure)
    {
        self->SetClientClosure(closure);
    }

    EXPORT void* wxTreeItemId_Create()
    {
        return new wxTreeItemId();
    }

    EXPORT void wxTreeItemId_Delete(wxTreeItemId* self)
    {
        delete self;
    }

    EXPORT bool wxTreeItemId_IsOk(wxTreeItemId* self)
    {
        return self->IsOk();
    }

    EXPORT wxTreeItemId* wxTreeItemId_Clone(wxTreeItemId* self)
    {
        wxTreeItemId* clone = new wxTreeItemId();
        *clone = *self;
        return clone;
    }

    // FIXME: wxHaskell uses this function in Graphics.UI.WXCore.WxcTypes.withTreeItemIdPtr
    // to make wxTreeItemId.
    //
    // But wxWidgets' document says: wxTreemItemIds are not meant to be constructed
    // explicitly by the user; they are returned by the wxTreeCtrl functions instead.
    //
    // http://www.wxwindows.org/manuals/2.8/wx_wxtreeitemid.html#wxtreeitemid
    //
    // So we must remove this function and replace treeItemId implementation in the
    // funture.
    EXPORT wxTreeItemId* wxTreeItemId_CreateFromValue(intptr_t value)
    {
        // TODO: This function should be removed. No longer any equivalent in wxWidgets
        wxTreeItemId* item = new wxTreeItemId();
        item->m_pItem = reinterpret_cast<wxTreeItemIdValue>(value);
        return item;
    }

    EXPORT intptr_t wxTreeItemId_GetValue(wxTreeItemId* self)
    {
        return (intptr_t) (self->m_pItem);
    }

    EXPORT wxKeyEvent* wxTreeEvent_GetKeyEvent(wxTreeEvent* self)
    {
        return (wxKeyEvent*) &(self->GetKeyEvent());
    }

    EXPORT bool wxTreeEvent_IsEditCancelled(wxTreeEvent* self)
    {
        return self->IsEditCancelled();
    }

    EXPORT void wxTreeEvent_Allow(wxTreeEvent* self)
    {
        self->Allow();
    }

    EXPORT wxTreeCtrl* wxTreeCtrl_Create(void* pObject, void* compareFunc, wxWindow* parent, int id,
                                         int x, int y, int width, int height, int style)
    {
        return new wxTreeCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style,
                              wxDefaultValidator);
    }

    EXPORT wxTreeCtrl* wxTreeCtrl_Create2(wxWindow* parent, int id, int x, int y, int width,
                                          int height, int style)
    {
        return new wxTreeCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style,
                              wxDefaultValidator);
    }

    EXPORT int wxTreeCtrl_GetCount(wxTreeCtrl* self)
    {
        int result = (int) self->GetCount();
#ifdef __WXGTK__
        wxTreeItemId t = self->GetRootItem();
        if (t.IsOk())
            result++;
#endif
        return result;
    }

    EXPORT int wxTreeCtrl_GetIndent(wxTreeCtrl* self)
    {
        return self->GetIndent();
    }

    EXPORT void wxTreeCtrl_SetIndent(wxTreeCtrl* self, int indent)
    {
        self->SetIndent(indent);
    }

    EXPORT int wxTreeCtrl_GetSpacing(wxTreeCtrl* self)
    {
        return (int) self->GetSpacing();
    }

    EXPORT void wxTreeCtrl_SetSpacing(wxTreeCtrl* self, int spacing)
    {
        self->SetSpacing(spacing);
    }

    EXPORT wxImageList* wxTreeCtrl_GetImageList(wxTreeCtrl* self)
    {
        return self->GetImageList();
    }

    EXPORT wxImageList* wxTreeCtrl_GetStateImageList(wxTreeCtrl* self)
    {
        return self->GetStateImageList();
    }

    EXPORT void wxTreeCtrl_AssignImageList(wxTreeCtrl* self, wxImageList* imageList)
    {
        self->AssignImageList(imageList);
    }

    EXPORT void wxTreeCtrl_AssignStateImageList(wxTreeCtrl* self, wxImageList* imageList)
    {
        self->AssignStateImageList(imageList);
    }

    EXPORT void wxTreeCtrl_SetImageList(wxTreeCtrl* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT void wxTreeCtrl_SetStateImageList(wxTreeCtrl* self, wxImageList* imageList)
    {
        self->SetStateImageList(imageList);
    }

    EXPORT wxString* wxTreeCtrl_GetItemText(wxTreeCtrl* self, void* item)
    {
        wxString* result = new wxString();
        *result = self->GetItemText(*(wxTreeItemId*) item);
        return result;
    }

    EXPORT int wxTreeCtrl_GetItemImage(wxTreeCtrl* self, wxTreeItemId* item, int which)
    {
        return self->GetItemImage(*item, (wxTreeItemIcon) which);
    }

    EXPORT void* wxTreeCtrl_GetItemData(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return ((wxcTreeItemData*) self->GetItemData(*item))->GetClientClosure();
    }

    EXPORT void* wxTreeCtrl_GetItemClientClosure(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return ((wxcTreeItemData*) self->GetItemData(*item))->GetClientClosure();
    }

    EXPORT void wxTreeCtrl_SetItemText(wxTreeCtrl* self, wxTreeItemId* item, wxString* text)
    {
        self->SetItemText(*item, *text);
    }

    EXPORT void wxTreeCtrl_SetItemImage(wxTreeCtrl* self, wxTreeItemId* item, int image, int which)
    {
        self->SetItemImage(*item, image, (wxTreeItemIcon) which);
    }

    EXPORT void wxTreeCtrl_SetItemData(wxTreeCtrl* self, wxTreeItemId* item, wxClosure* closure)
    {
        self->SetItemData(*item, new wxcTreeItemData(closure));
    }

    EXPORT void wxTreeCtrl_SetItemClientClosure(wxTreeCtrl* self, wxTreeItemId* item,
                                                wxClosure* closure)
    {
        wxTreeItemData* oldData = self->GetItemData(*item);
        /* bit unsafe: might delete twice but it is definitely ok on MSW 2.4.1 */
        if (oldData)
            delete oldData;
        self->SetItemData(*item, new wxcTreeItemData(closure));
    }

    EXPORT void wxTreeCtrl_SetItemHasChildren(wxTreeCtrl* self, wxTreeItemId* item, bool has)
    {
        self->SetItemHasChildren(*item, has);
    }

    EXPORT void wxTreeCtrl_SetItemBold(wxTreeCtrl* self, wxTreeItemId* item, bool bold)
    {
        self->SetItemBold(*item, bold);
    }

    EXPORT void wxTreeCtrl_SetItemDropHighlight(wxTreeCtrl* self, wxTreeItemId* item,
                                                bool highlight)
    {
#ifdef __WIN32__
        self->SetItemDropHighlight(*item, highlight);
#endif
    }

    EXPORT void wxTreeCtrl_SetItemTextColour(wxTreeCtrl* self, wxTreeItemId* item, wxColour* col)
    {
        self->SetItemTextColour(*item, *col);
    }

    EXPORT void wxTreeCtrl_SetItemBackgroundColour(wxTreeCtrl* self, wxTreeItemId* item,
                                                   wxColour* col)
    {
        self->SetItemBackgroundColour(*item, *col);
    }

    EXPORT void wxTreeCtrl_SetItemFont(wxTreeCtrl* self, wxTreeItemId* item, wxFont* font)
    {
        self->SetItemFont(*item, *font);
    }

    EXPORT bool wxTreeCtrl_IsVisible(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return self->IsVisible(*item);
    }

    EXPORT int wxTreeCtrl_ItemHasChildren(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return (int) self->ItemHasChildren(*item);
    }

    EXPORT bool wxTreeCtrl_IsExpanded(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return self->IsExpanded(*item);
    }

    EXPORT bool wxTreeCtrl_IsSelected(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return self->IsSelected(*item);
    }

    EXPORT bool wxTreeCtrl_IsBold(wxTreeCtrl* self, wxTreeItemId* item)
    {
        return self->IsBold(*item);
    }

    EXPORT int wxTreeCtrl_GetChildrenCount(wxTreeCtrl* self, wxTreeItemId* item, int recursively)
    {
        return self->GetChildrenCount(*item, recursively);
    }

    EXPORT void wxTreeCtrl_GetRootItem(wxTreeCtrl* self, wxTreeItemId* item)
    {
        *item = self->GetRootItem();
    }

    EXPORT void wxTreeCtrl_GetSelection(wxTreeCtrl* self, wxTreeItemId* item)
    {
        *item = self->GetSelection();
    }

    EXPORT int wxTreeCtrl_GetSelections(wxTreeCtrl* self, intptr_t* selections)
    {
        int result = 0;
        wxArrayTreeItemIds sel;
        result = self->GetSelections(sel);

        if (selections)
        {
            for (int i = 0; i < result; i++)
            {
                /*
                 *(((wxTreeItemId**)selections)[i]) = sel[i];
                 */
                selections[i] = (intptr_t) (((wxTreeItemId) sel[i]).m_pItem);
            }
        }
        return result;
    }

    EXPORT void wxTreeCtrl_GetParent(wxTreeCtrl* self, wxTreeItemId* inputItem,
                                     wxTreeItemId* result)
    {
        *result = self->GetItemParent(*inputItem);
    }

    EXPORT void wxTreeCtrl_GetFirstChild(wxTreeCtrl* self, wxTreeItemId* inputItem, void* cookie,
                                         wxTreeItemId* result)
    {
        *result = self->GetFirstChild(*inputItem, cookie);
    }

    EXPORT void wxTreeCtrl_GetNextChild(wxTreeCtrl* self, wxTreeItemId* inputItem, void* cookie,
                                        wxTreeItemId* result)
    {
        *result = self->GetNextChild(*inputItem, cookie);
    }

    EXPORT void wxTreeCtrl_GetLastChild(wxTreeCtrl* self, wxTreeItemId* inputItem,
                                        wxTreeItemId* result)
    {
        *result = self->GetLastChild(*inputItem);
    }

    EXPORT void wxTreeCtrl_GetNextSibling(wxTreeCtrl* self, wxTreeItemId* inputItem,
                                          wxTreeItemId* result)
    {
        *result = self->GetNextSibling(*inputItem);
    }

    EXPORT void wxTreeCtrl_GetPrevSibling(wxTreeCtrl* self, wxTreeItemId* inputItem,
                                          wxTreeItemId* result)
    {
        *result = self->GetPrevSibling(*inputItem);
    }

    EXPORT void wxTreeCtrl_GetFirstVisibleItem(wxTreeCtrl* self, wxTreeItemId* item)
    {
        *item = self->GetFirstVisibleItem();
    }

    EXPORT void wxTreeCtrl_GetNextVisible(wxTreeCtrl* self, wxTreeItemId* inputItem,
                                          wxTreeItemId* result)
    {
        *result = self->GetNextVisible(*inputItem);
    }

    EXPORT void wxTreeCtrl_GetPrevVisible(wxTreeCtrl* self, wxTreeItemId* inputItem,
                                          wxTreeItemId* result)
    {
        *result = self->GetPrevVisible(*inputItem);
    }

    EXPORT void wxTreeCtrl_AddRoot(wxTreeCtrl* self, wxString* text, int image, int selectedImage,
                                   wxClosure* data, wxTreeItemId* item)
    {
        *item = self->AddRoot(*text, image, selectedImage, new wxcTreeItemData(data));
    }

    EXPORT void wxTreeCtrl_PrependItem(wxTreeCtrl* self, wxTreeItemId* parent, wxString* text,
                                       int image, int selectedImage, wxClosure* data,
                                       wxTreeItemId* item)
    {
        *item = self->PrependItem(*parent, *text, image, selectedImage, new wxcTreeItemData(data));
    }

    EXPORT void wxTreeCtrl_InsertItem(wxTreeCtrl* self, wxTreeItemId* parent,
                                      wxTreeItemId* idPrevious, wxString* text, int image,
                                      int selectedImage, wxClosure* data, wxTreeItemId* item)
    {
        *item = self->InsertItem(*parent, *idPrevious, *text, image, selectedImage,
                                 new wxcTreeItemData(data));
    }

    EXPORT void wxTreeCtrl_InsertItem2(wxTreeCtrl* self, wxTreeItemId* parent,
                                       wxTreeItemId* idPrevious, wxString* text, int image,
                                       int selectedImage, wxClosure* closure, wxTreeItemId* item)
    {
        *item = self->InsertItem(*parent, *idPrevious, *text, image, selectedImage,
                                 new wxcTreeItemData(closure));
    }

    EXPORT void wxTreeCtrl_InsertItemByIndex(wxTreeCtrl* self, wxTreeItemId* parent, int index,
                                             wxString* text, int image, int selectedImage,
                                             wxClosure* data, wxTreeItemId* item)
    {
        *item = self->InsertItem(*parent, index, *text, image, selectedImage,
                                 new wxcTreeItemData(data));
    }

    EXPORT void wxTreeCtrl_InsertItemByIndex2(wxTreeCtrl* self, wxTreeItemId* parent, int index,
                                              wxString* text, int image, int selectedImage,
                                              wxClosure* data, wxTreeItemId* item)
    {
        *item = self->InsertItem(*parent, index, *text, image, selectedImage,
                                 new wxcTreeItemData(data));
    }

    EXPORT void wxTreeCtrl_AppendItem(wxTreeCtrl* self, wxTreeItemId* parent, wxString* text,
                                      int image, int selectedImage, wxClosure* data,
                                      wxTreeItemId* item)
    {
        *item = self->AppendItem(*parent, *text, image, selectedImage, new wxcTreeItemData(data));
    }

    EXPORT void wxTreeCtrl_Delete(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->Delete(*item);
    }

    EXPORT void wxTreeCtrl_DeleteChildren(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->DeleteChildren(*item);
    }

    EXPORT void wxTreeCtrl_DeleteAllItems(wxTreeCtrl* self)
    {
        self->DeleteAllItems();
    }

    EXPORT void wxTreeCtrl_Expand(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->Expand(*item);
    }

    EXPORT void wxTreeCtrl_Collapse(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->Collapse(*item);
    }

    EXPORT void wxTreeCtrl_CollapseAndReset(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->CollapseAndReset(*item);
    }

    EXPORT void wxTreeCtrl_Toggle(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->Toggle(*item);
    }

    EXPORT void wxTreeCtrl_Unselect(wxTreeCtrl* self)
    {
        self->Unselect();
    }

    EXPORT void wxTreeCtrl_UnselectAll(wxTreeCtrl* self)
    {
        self->UnselectAll();
    }

    EXPORT void wxTreeCtrl_SelectItem(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->SelectItem(*item);
    }

    EXPORT void wxTreeCtrl_EnsureVisible(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->EnsureVisible(*item);
    }

    EXPORT void wxTreeCtrl_ScrollTo(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->ScrollTo(*item);
    }

    EXPORT void wxTreeCtrl_EditLabel(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->EditLabel(*item);
    }

    EXPORT void* wxTreeCtrl_GetEditControl(wxTreeCtrl* self)
    {
#ifdef __WIN32__
        return (void*) self->GetEditControl();
#else
        return nullptr;
#endif
    }

    EXPORT void wxTreeCtrl_EndEditLabel(wxTreeCtrl* self, wxTreeItemId* item, bool discardChanges)
    {
#ifdef __WIN32__
        self->EndEditLabel(*item, discardChanges);
#endif
    }

    EXPORT int wxTreeCtrl_OnCompareItems(wxTreeCtrl* self, wxTreeItemId* item1, wxTreeItemId* item2)
    {
        return self->OnCompareItems(*item1, *item2);
    }

    EXPORT void wxTreeCtrl_SortChildren(wxTreeCtrl* self, wxTreeItemId* item)
    {
        self->SortChildren(*item);
    }

    EXPORT void wxTreeCtrl_HitTest(wxTreeCtrl* self, int x, int y, void* flags, wxTreeItemId* item)
    {
        *item = self->HitTest(wxPoint(x, y), *((int*) flags));
    }

    EXPORT wxRect* wxTreeCtrl_GetBoundingRect(wxTreeCtrl* self, wxTreeItemId* item, bool textOnly)
    {
        wxRect* const rct = new wxRect(-1, -1, -1, -1);
        self->GetBoundingRect(*item, *rct, textOnly);
        return rct;
    }
}
