#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxMenuBar_Create(int style)
    {
        return new wxMenuBar(style);
    }

    EXPORT void wxMenuBar_DeletePointer(wxMenuBar* self)
    {
        delete self;
    }

    EXPORT bool wxMenuBar_Append(wxMenuBar* self, wxMenu* menu, wxString* title)
    {
        return self->Append(menu, *title);
    }

    EXPORT bool wxMenuBar_Insert(wxMenuBar* self, int pos, wxMenu* menu, wxString* title)
    {
        return self->Insert((size_t) pos, menu, *title);
    }

    EXPORT int wxMenuBar_GetMenuCount(wxMenuBar* self)
    {
        return self->GetMenuCount();
    }

    EXPORT wxMenu* wxMenuBar_GetMenu(wxMenuBar* self, size_t pos)
    {
        return self->GetMenu(pos);
    }

    EXPORT void* wxMenuBar_Replace(wxMenuBar* self, int pos, wxMenu* menu, wxString* title)
    {
        return (void*) self->Replace((size_t) pos, menu, *title);
    }

    EXPORT void* wxMenuBar_Remove(wxMenuBar* self, int pos)
    {
        return (void*) self->Remove((size_t) pos);
    }

    EXPORT void wxMenuBar_EnableTop(wxMenuBar* self, int pos, bool enable)
    {
        self->EnableTop((size_t) pos, enable);
    }

    EXPORT void wxMenuBar_SetMenuLabel(wxMenuBar* self, int pos, wxString* label)
    {
        self->SetMenuLabel((size_t) pos, *label);
    }

    EXPORT wxString* wxMenuBar_GetMenuLabel(wxMenuBar* self, int pos)
    {
        wxString* result = new wxString();
        *result = self->GetMenuLabel((size_t) pos);
        return result;
    }

    EXPORT int wxMenuBar_FindMenuItem(wxMenuBar* self, wxString* menuString, wxString* itemString)
    {
        return self->FindMenuItem(*menuString, *itemString);
    }

    EXPORT void* wxMenuBar_FindItem(wxMenuBar* self, int id)
    {
        wxMenu* foo = new wxMenu;
        return (void*) self->FindItem(id, &foo);
    }

    EXPORT int wxMenuBar_FindMenu(wxMenuBar* self, wxString* title)
    {
        return self->FindMenu(*title);
    }

    EXPORT void wxMenuBar_EnableItem(wxMenuBar* self, int id, bool enable)
    {
        self->Enable(id, enable);
    }

    EXPORT void wxMenuBar_Check(wxMenuBar* self, int id, bool check)
    {
        self->Check(id, check);
    }

    EXPORT bool wxMenuBar_IsChecked(wxMenuBar* self, int id)
    {
        return self->IsChecked(id);
    }

    EXPORT bool wxMenuBar_IsEnabled(wxMenuBar* self, int id)
    {
        return self->IsEnabled(id);
    }

    EXPORT void wxMenuBar_SetItemLabel(wxMenuBar* self, int id, wxString* label)
    {
        self->SetLabel(id, *label);
    }

    EXPORT wxString* wxMenuBar_GetLabel(void* pObject, int id)
    {
        wxString* result = new wxString();
        *result = ((wxMenuBar*) pObject)->GetLabel(id);
        return result;
    }

    EXPORT void wxMenuBar_SetHelpString(wxMenuBar* self, int id, wxString* helpString)
    {
        self->SetHelpString(id, *helpString);
    }

    EXPORT wxString* wxMenuBar_GetHelpString(void* pObject, int id)
    {
        wxString* result = new wxString();
        *result = ((wxMenuBar*) pObject)->GetHelpString(id);
        return result;
    }

    EXPORT void wxMenuBar_Enable(wxMenuBar* self, bool enable)
    {
        self->Enable(enable);
    }

    EXPORT void wxMenuBar_SetLabel(wxMenuBar* self, wxString* str)
    {
        self->SetLabel(*str);
    }

    EXPORT bool wxMenuBar_IsEnabledTop(wxMenuBar* self, int pos)
    {
        return self->IsEnabledTop(pos);
    }

    EXPORT wxString* wxMenuBar_GetMenuLabelText(wxMenuBar* self, int pos)
    {
        wxString* result = new wxString();
        *result = self->GetMenuLabelText(pos);
        return result;
    }

    EXPORT void wxMenuBar_UpdateMenus(wxMenuBar* self)
    {
        self->UpdateMenus();
    }
}
