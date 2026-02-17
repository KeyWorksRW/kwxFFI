#include "wrapper.h"

// wxSimpleHtmlListBox inherits from wxWindow and wxItemContainer (not wxControl).
// Additional methods available via:
//   wxWindow_*         — base window methods (see wx_window.cpp)
//   wxItemContainer_*  — item management, selection (see wx_itemcontainer.cpp)

extern "C"
{
    // Constructor
    EXPORT wxSimpleHtmlListBox* wxSimpleHtmlListBox_Create(wxWindow* parent, int id, int x, int y,
                                                           int width, int height, int style)
    {
        return new wxSimpleHtmlListBox(parent, id, wxPoint(x, y), wxSize(width, height), 0, nullptr,
                                       style, wxDefaultValidator);
    }

    // Clear all items
    EXPORT void wxSimpleHtmlListBox_Clear(wxSimpleHtmlListBox* self)
    {
        self->Clear();
    }

    // Delete an item
    EXPORT void wxSimpleHtmlListBox_Delete(wxSimpleHtmlListBox* self, int index)
    {
        self->Delete(index);
    }

    // Get count
    EXPORT int wxSimpleHtmlListBox_GetCount(wxSimpleHtmlListBox* self)
    {
        return self->GetCount();
    }

    // Get item string
    EXPORT wxString* wxSimpleHtmlListBox_GetString(wxSimpleHtmlListBox* self, int index)
    {
        wxString* result = new wxString();
        *result = self->GetString(index);
        return result;
    }

    // Set item string
    EXPORT void wxSimpleHtmlListBox_SetString(wxSimpleHtmlListBox* self, int index, wxString* str)
    {
        self->SetString(index, *str);
    }

    // Get selection
    EXPORT int wxSimpleHtmlListBox_GetSelection(wxSimpleHtmlListBox* self)
    {
        return self->GetSelection();
    }

    // Set selection
    EXPORT void wxSimpleHtmlListBox_SetSelection(wxSimpleHtmlListBox* self, int index)
    {
        self->SetSelection(index);
    }

    // Append item
    EXPORT int wxSimpleHtmlListBox_Append(wxSimpleHtmlListBox* self, wxString* item)
    {
        return self->Append(*item);
    }

    // Append with data
    EXPORT int wxSimpleHtmlListBox_AppendData(wxSimpleHtmlListBox* self, wxString* item, void* data)
    {
        return self->Append(*item, data);
    }

    // Insert item
    EXPORT int wxSimpleHtmlListBox_Insert(wxSimpleHtmlListBox* self, wxString* item, int pos)
    {
        return self->Insert(*item, pos);
    }

    // Insert with data
    EXPORT int wxSimpleHtmlListBox_InsertData(wxSimpleHtmlListBox* self, wxString* item, int pos,
                                              void* data)
    {
        return self->Insert(*item, pos, data);
    }

    // Find string
    EXPORT int wxSimpleHtmlListBox_FindString(wxSimpleHtmlListBox* self, wxString* str,
                                              bool caseSensitive)
    {
        return self->FindString(*str, caseSensitive);
    }

    // Get/Set item data
    EXPORT void* wxSimpleHtmlListBox_GetClientData(wxSimpleHtmlListBox* self, int index)
    {
        return self->GetClientData(index);
    }

    EXPORT void wxSimpleHtmlListBox_SetClientData(wxSimpleHtmlListBox* self, int index, void* data)
    {
        self->SetClientData(index, data);
    }

    // Check if empty
    EXPORT bool wxSimpleHtmlListBox_IsEmpty(wxSimpleHtmlListBox* self)
    {
        return self->IsEmpty();
    }

    // Get item count (for consistency with other list controls)
    EXPORT int wxSimpleHtmlListBox_GetItemCount(wxSimpleHtmlListBox* self)
    {
        return self->GetCount();
    }
}
