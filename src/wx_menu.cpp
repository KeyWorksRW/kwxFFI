#include "wrapper.h"

extern "C"
{
    EXPORT wxMenu* wxMenu_Create(wxString* title, long style)
    {
        return new wxMenu(*title, style);
    }

    EXPORT void wxMenu_DeletePointer(wxMenu* self)
    {
        delete self;
    }

    EXPORT void wxMenu_AppendSeparator(wxMenu* self)
    {
        self->AppendSeparator();
    }

    EXPORT void wxMenu_Append(wxMenu* self, int id, wxString* text, wxString* help,
                              bool isCheckable)
    {
        self->Append(id, *text, *help, isCheckable);
    }

    EXPORT void wxMenu_AppendSub(wxMenu* self, int id, wxString* text, wxMenu* submenu,
                                 wxString* help)
    {
        self->Append(id, *text, submenu, *help);
    }

    EXPORT void wxMenu_AppendItem(wxMenu* self, wxMenuItem* _itm)
    {
        self->Append(_itm);
    }

    EXPORT void wxMenu_Break(wxMenu* self)
    {
        self->Break();
    }

    EXPORT void wxMenu_Insert(wxMenu* self, size_t pos, int id, wxString* text, wxString* help,
                              bool isCheckable)
    {
        self->Insert(pos, id, *text, *help, isCheckable);
    }

    EXPORT void wxMenu_InsertSub(wxMenu* self, size_t pos, int id, wxString* text, wxMenu* submenu,
                                 wxString* help)
    {
        self->Insert(pos, id, *text, submenu, *help);
    }

    EXPORT void wxMenu_InsertItem(wxMenu* self, int pos, wxMenuItem* _itm)
    {
        self->Insert((size_t) pos, _itm);
    }

    EXPORT void wxMenu_Prepend(wxMenu* self, int id, wxString* text, wxString* help,
                               bool isCheckable)
    {
        self->Prepend(id, *text, *help, isCheckable);
    }

    EXPORT void wxMenu_PrependSub(wxMenu* self, int id, wxString* text, wxMenu* submenu,
                                  wxString* help)
    {
        self->Prepend(id, *text, submenu, *help);
    }

    EXPORT void wxMenu_PrependItem(wxMenu* self, wxMenuItem* _itm)
    {
        self->Prepend(_itm);
    }

    EXPORT void wxMenu_RemoveByItem(wxMenu* self, wxMenuItem* item)
    {
        self->Remove(item);
    }

    EXPORT void wxMenu_RemoveById(wxMenu* self, int id, void* _itm)
    {
        *((void**) _itm) = (void*) self->Remove(id);
    }

    EXPORT void wxMenu_DeleteById(wxMenu* self, int id)
    {
        self->Delete(id);
    }

    EXPORT void wxMenu_DeleteByItem(wxMenu* self, wxMenuItem* _itm)
    {
        self->Delete(_itm);
    }

    EXPORT void wxMenu_DestroyById(wxMenu* self, int id)
    {
        self->Destroy(id);
    }

    EXPORT void wxMenu_DestroyByItem(wxMenu* self, wxMenuItem* _itm)
    {
        self->Destroy(_itm);
    }

    EXPORT size_t wxMenu_GetMenuItemCount(wxMenu* self)
    {
        return self->GetMenuItemCount();
    }

    EXPORT int wxMenu_GetMenuItems(wxMenu* self, void* _lst)
    {
        if (_lst)
        {
            for (unsigned int i = 0; i < self->GetMenuItems().GetCount(); i++)
                ((void**) _lst)[i] = self->GetMenuItems().Item(i)->GetData();
        }
        return self->GetMenuItems().GetCount();
    }

    EXPORT int wxMenu_FindItemByLabel(wxMenu* self, wxString* itemString)
    {
        return self->FindItem(*itemString);
    }

    EXPORT wxMenuItem* wxMenu_FindItem(wxMenu* self, int id)
    {
        return self->FindItem(id);
    }

    EXPORT void wxMenu_Enable(wxMenu* self, int id, bool enable)
    {
        self->Enable(id, enable);
    }

    EXPORT bool wxMenu_IsEnabled(wxMenu* self, int id)
    {
        return self->IsEnabled(id);
    }

    EXPORT void wxMenu_Check(wxMenu* self, int id, bool check)
    {
        self->Check(id, check);
    }

    EXPORT bool wxMenu_IsChecked(wxMenu* self, int id)
    {
        return self->IsChecked(id);
    }

    EXPORT void wxMenu_SetLabel(wxMenu* self, int id, wxString* label)
    {
        self->SetLabel(id, *label);
    }

    EXPORT wxString* wxMenu_GetLabelText(wxMenu* self, int id)
    {
        wxString* result = new wxString();
        *result = self->GetLabelText(id);
        return result;
    }

    EXPORT void wxMenu_SetHelpString(wxMenu* self, int id, wxString* helpString)
    {
        self->SetHelpString(id, *helpString);
    }

    EXPORT wxString* wxMenu_GetHelpString(wxMenu* self, int id)
    {
        wxString* result = new wxString();
        *result = self->GetHelpString(id);
        return result;
    }

    EXPORT void wxMenu_SetTitle(void* _obj, wxString* title)
    {
        ((wxMenu*) _obj)->SetTitle(*title);
    }

    EXPORT wxString* wxMenu_GetTitle(wxMenu* self)
    {
        wxString* result = new wxString();
        *result = self->GetTitle();
        return result;
    }

    EXPORT void wxMenu_SetClientData(wxMenu* self, void* clientData)
    {
        self->SetClientData(clientData);
    }

    EXPORT void* wxMenu_GetClientData(wxMenu* self)
    {
        return (void*) self->GetClientData();
    }

    EXPORT void wxMenu_SetEventHandler(wxMenu* self, wxEvtHandler* handler)
    {
        self->SetEventHandler(handler);
    }

    EXPORT void wxMenu_SetInvokingWindow(wxMenu* self, wxWindow* win)
    {
        self->SetInvokingWindow(win);
    }

    EXPORT void* wxMenu_GetInvokingWindow(wxMenu* self)
    {
        return (void*) self->GetInvokingWindow();
    }

    EXPORT int wxMenu_GetStyle(wxMenu* self)
    {
        return self->GetStyle();
    }

    EXPORT void wxMenu_UpdateUI(wxMenu* self, wxEvtHandler* source)
    {
        self->UpdateUI(source);
    }

    EXPORT bool wxMenu_IsAttached(wxMenu* self)
    {
        return self->IsAttached();
    }

    EXPORT void wxMenu_SetParent(wxMenu* self, wxMenu* parent)
    {
        self->SetParent(parent);
    }

    EXPORT void* wxMenu_GetParent(wxMenu* self)
    {
        return (void*) self->GetParent();
    }

    EXPORT wxMenuItem* wxMenuItem_Create()
    {
        return new wxMenuItem();
    }

    EXPORT void wxMenuItem_Delete(wxMenuItem* self)
    {
        delete self;
    }

    EXPORT wxMenu* wxMenuItem_GetMenu(wxMenuItem* self)
    {
        return self->GetMenu();
    }

    EXPORT void wxMenuItem_SetId(wxMenuItem* self, int id)
    {
        self->SetId(id);
    }

    EXPORT int wxMenuItem_GetId(wxMenuItem* self)
    {
        return self->GetId();
    }

    EXPORT bool wxMenuItem_IsSeparator(wxMenuItem* self)
    {
        return self->IsSeparator();
    }

    EXPORT void wxMenuItem_SetItemLabel(wxMenuItem* self, wxString* str)
    {
        self->SetItemLabel(*str);
    }

    EXPORT wxString* wxMenuItem_GetItemLabelText(wxMenuItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetItemLabelText();
        return result;
    }

    EXPORT wxString* wxMenuItem_GetItemLabel(wxMenuItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetItemLabel();
        return result;
    }

    EXPORT wxString* wxMenuItem_GetLabelText(wxString* text)
    {
        wxString* result = new wxString();
        *result = wxMenuItem::GetLabelText(*text);
        return result;
    }

    EXPORT void wxMenuItem_SetCheckable(wxMenuItem* self, bool checkable)
    {
        self->SetCheckable(checkable);
    }

    EXPORT bool wxMenuItem_IsCheckable(wxMenuItem* self)
    {
        return self->IsCheckable();
    }

    EXPORT bool wxMenuItem_IsSubMenu(wxMenuItem* self)
    {
        return self->IsSubMenu();
    }

    EXPORT void wxMenuItem_SetSubMenu(wxMenuItem* self, wxMenu* menu)
    {
        self->SetSubMenu(menu);
    }

    EXPORT wxMenu* wxMenuItem_GetSubMenu(wxMenuItem* self)
    {
        return self->GetSubMenu();
    }

    EXPORT void wxMenuItem_Enable(wxMenuItem* self, bool enable)
    {
        self->Enable(enable);
    }

    EXPORT bool wxMenuItem_IsEnabled(wxMenuItem* self)
    {
        return self->IsEnabled();
    }

    EXPORT void wxMenuItem_Check(wxMenuItem* self, bool check)
    {
        self->Check(check);
    }

    EXPORT bool wxMenuItem_IsChecked(wxMenuItem* self)
    {
        return self->IsChecked();
    }

    EXPORT void wxMenuItem_SetHelp(wxMenuItem* self, wxString* str)
    {
        self->SetHelp(*str);
    }

    EXPORT wxString* wxMenuItem_GetHelp(wxMenuItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetHelp();
        return result;
    }
}
