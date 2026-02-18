#include "kwx_wrapper.h"

// wxItemContainer/wxItemContainerImmutable is a mixin interface.
// Because it is a non-primary base in a multiple-inheritance hierarchy,
// we cast through wxWindow* and use dynamic_cast.
//
// Controls that inherit from wxItemContainer:
//   wxListBox, wxCheckListBox, wxChoice, wxComboBox, wxBitmapComboBox,
//   wxRearrangeList, wxSimpleHtmlListBox

static inline wxItemContainer* AsItemContainer(void* self)
{
    return dynamic_cast<wxItemContainer*>(static_cast<wxWindow*>(self));
}

extern "C"
{
    // wxItemContainerImmutable methods

    EXPORT unsigned int wxItemContainer_GetCount(void* self)
    {
        return AsItemContainer(self)->GetCount();
    }

    EXPORT bool wxItemContainer_IsEmpty(void* self)
    {
        return AsItemContainer(self)->IsEmpty();
    }

    EXPORT wxString* wxItemContainer_GetString(void* self, unsigned int n)
    {
        auto* result = new wxString();
        *result = AsItemContainer(self)->GetString(n);
        return result;
    }

    EXPORT void wxItemContainer_SetString(void* self, unsigned int n, wxString* s)
    {
        AsItemContainer(self)->SetString(n, *s);
    }

    EXPORT int wxItemContainer_FindString(void* self, wxString* s, bool caseSensitive)
    {
        return AsItemContainer(self)->FindString(*s, caseSensitive);
    }

    EXPORT void wxItemContainer_SetSelection(void* self, int n)
    {
        AsItemContainer(self)->SetSelection(n);
    }

    EXPORT int wxItemContainer_GetSelection(void* self)
    {
        return AsItemContainer(self)->GetSelection();
    }

    EXPORT bool wxItemContainer_SetStringSelection(void* self, wxString* s)
    {
        return AsItemContainer(self)->SetStringSelection(*s);
    }

    EXPORT wxString* wxItemContainer_GetStringSelection(void* self)
    {
        auto* result = new wxString();
        *result = AsItemContainer(self)->GetStringSelection();
        return result;
    }

    EXPORT void wxItemContainer_Select(void* self, int n)
    {
        AsItemContainer(self)->Select(n);
    }

    // wxItemContainer methods (mutable)

    EXPORT int wxItemContainer_Append(void* self, wxString* item)
    {
        return AsItemContainer(self)->Append(*item);
    }

    EXPORT int wxItemContainer_AppendItems(void* self, int count, void* items)
    {
        wxArrayString strings;
        for (int i = 0; i < count; i++)
            strings.Add(((const char**) items)[i]);
        return AsItemContainer(self)->Append(strings);
    }

    EXPORT int wxItemContainer_Insert(void* self, wxString* item, unsigned int pos)
    {
        return AsItemContainer(self)->Insert(*item, pos);
    }

    EXPORT int wxItemContainer_InsertItems(void* self, int count, void* items, unsigned int pos)
    {
        wxArrayString strings;
        for (int i = 0; i < count; i++)
            strings.Add(((const char**) items)[i]);
        return AsItemContainer(self)->Insert(strings, pos);
    }

    EXPORT void wxItemContainer_Set(void* self, int count, void* items)
    {
        wxArrayString strings;
        for (int i = 0; i < count; i++)
            strings.Add(((const char**) items)[i]);
        AsItemContainer(self)->Set(strings);
    }

    EXPORT void wxItemContainer_Clear(void* self)
    {
        AsItemContainer(self)->Clear();
    }

    EXPORT void wxItemContainer_Delete(void* self, unsigned int pos)
    {
        AsItemContainer(self)->Delete(pos);
    }

    EXPORT bool wxItemContainer_IsSorted(void* self)
    {
        return AsItemContainer(self)->IsSorted();
    }

    // Client data (void*) accessors

    EXPORT void wxItemContainer_SetClientData(void* self, unsigned int n, void* clientData)
    {
        AsItemContainer(self)->SetClientData(n, clientData);
    }

    EXPORT void* wxItemContainer_GetClientData(void* self, unsigned int n)
    {
        return AsItemContainer(self)->GetClientData(n);
    }

    EXPORT bool wxItemContainer_HasClientData(void* self)
    {
        return AsItemContainer(self)->HasClientData();
    }
}
