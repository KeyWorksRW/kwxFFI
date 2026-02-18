#include "kwx_wrapper.h"

// wxTextEntry is a mixin interface, not a concrete class.
// Because wxTextEntry is a non-primary base in a multiple-inheritance hierarchy,
// void* cannot be static_cast to wxTextEntry* directly — the pointer offset
// varies per concrete type. We cast through wxWindow* and use dynamic_cast to
// safely cross-cast to wxTextEntry*.
//
// Controls that inherit from wxTextEntry:
//   wxTextCtrl, wxComboBox, wxSearchCtrl, wxSpinCtrl, wxSpinCtrlDouble,
//   wxComboCtrl, wxRichTextCtrl

// Helper: cross-cast wxWindow* -> wxTextEntry* via dynamic_cast.
// The caller must pass a pointer to a wxWindow-derived class that also
// derives from wxTextEntry.
static inline wxTextEntry* AsTextEntry(void* self)
{
    return dynamic_cast<wxTextEntry*>(static_cast<wxWindow*>(self));
}

extern "C"
{
    EXPORT void wxTextEntry_SetValue(void* self, wxString* value)
    {
        AsTextEntry(self)->SetValue(*value);
    }

    EXPORT void wxTextEntry_ChangeValue(void* self, wxString* value)
    {
        AsTextEntry(self)->ChangeValue(*value);
    }

    EXPORT wxString* wxTextEntry_GetValue(void* self)
    {
        auto* result = new wxString();
        *result = AsTextEntry(self)->GetValue();
        return result;
    }

    EXPORT wxString* wxTextEntry_GetRange(void* self, long from, long to)
    {
        auto* result = new wxString();
        *result = AsTextEntry(self)->GetRange(from, to);
        return result;
    }

    EXPORT bool wxTextEntry_IsEmpty(void* self)
    {
        return AsTextEntry(self)->IsEmpty();
    }

    EXPORT void wxTextEntry_WriteText(void* self, wxString* text)
    {
        AsTextEntry(self)->WriteText(*text);
    }

    EXPORT void wxTextEntry_AppendText(void* self, wxString* text)
    {
        AsTextEntry(self)->AppendText(*text);
    }

    EXPORT void wxTextEntry_Replace(void* self, long from, long to, wxString* value)
    {
        AsTextEntry(self)->Replace(from, to, *value);
    }

    EXPORT void wxTextEntry_Remove(void* self, long from, long to)
    {
        AsTextEntry(self)->Remove(from, to);
    }

    EXPORT void wxTextEntry_Clear(void* self)
    {
        AsTextEntry(self)->Clear();
    }

    EXPORT void wxTextEntry_RemoveSelection(void* self)
    {
        AsTextEntry(self)->RemoveSelection();
    }

    EXPORT void wxTextEntry_Copy(void* self)
    {
        AsTextEntry(self)->Copy();
    }

    EXPORT void wxTextEntry_Cut(void* self)
    {
        AsTextEntry(self)->Cut();
    }

    EXPORT void wxTextEntry_Paste(void* self)
    {
        AsTextEntry(self)->Paste();
    }

    EXPORT bool wxTextEntry_CanCopy(void* self)
    {
        return AsTextEntry(self)->CanCopy();
    }

    EXPORT bool wxTextEntry_CanCut(void* self)
    {
        return AsTextEntry(self)->CanCut();
    }

    EXPORT bool wxTextEntry_CanPaste(void* self)
    {
        return AsTextEntry(self)->CanPaste();
    }

    EXPORT void wxTextEntry_Undo(void* self)
    {
        AsTextEntry(self)->Undo();
    }

    EXPORT void wxTextEntry_Redo(void* self)
    {
        AsTextEntry(self)->Redo();
    }

    EXPORT bool wxTextEntry_CanUndo(void* self)
    {
        return AsTextEntry(self)->CanUndo();
    }

    EXPORT bool wxTextEntry_CanRedo(void* self)
    {
        return AsTextEntry(self)->CanRedo();
    }

    EXPORT void wxTextEntry_SetInsertionPoint(void* self, long pos)
    {
        AsTextEntry(self)->SetInsertionPoint(pos);
    }

    EXPORT void wxTextEntry_SetInsertionPointEnd(void* self)
    {
        AsTextEntry(self)->SetInsertionPointEnd();
    }

    EXPORT long wxTextEntry_GetInsertionPoint(void* self)
    {
        return AsTextEntry(self)->GetInsertionPoint();
    }

    EXPORT long wxTextEntry_GetLastPosition(void* self)
    {
        return AsTextEntry(self)->GetLastPosition();
    }

    EXPORT void wxTextEntry_SetSelection(void* self, long from, long to)
    {
        AsTextEntry(self)->SetSelection(from, to);
    }

    EXPORT void wxTextEntry_SelectAll(void* self)
    {
        AsTextEntry(self)->SelectAll();
    }

    EXPORT void wxTextEntry_SelectNone(void* self)
    {
        AsTextEntry(self)->SelectNone();
    }

    EXPORT void wxTextEntry_GetSelection(void* self, long* from, long* to)
    {
        AsTextEntry(self)->GetSelection(from, to);
    }

    EXPORT bool wxTextEntry_HasSelection(void* self)
    {
        return AsTextEntry(self)->HasSelection();
    }

    EXPORT wxString* wxTextEntry_GetStringSelection(void* self)
    {
        auto* result = new wxString();
        *result = AsTextEntry(self)->GetStringSelection();
        return result;
    }

    EXPORT bool wxTextEntry_IsEditable(void* self)
    {
        return AsTextEntry(self)->IsEditable();
    }

    EXPORT void wxTextEntry_SetEditable(void* self, bool editable)
    {
        AsTextEntry(self)->SetEditable(editable);
    }

    EXPORT void wxTextEntry_SetMaxLength(void* self, unsigned long len)
    {
        AsTextEntry(self)->SetMaxLength(len);
    }

    EXPORT void wxTextEntry_ForceUpper(void* self)
    {
        AsTextEntry(self)->ForceUpper();
    }

    EXPORT bool wxTextEntry_SetHint(void* self, wxString* hint)
    {
        return AsTextEntry(self)->SetHint(*hint);
    }

    EXPORT wxString* wxTextEntry_GetHint(void* self)
    {
        auto* result = new wxString();
        *result = AsTextEntry(self)->GetHint();
        return result;
    }

    EXPORT bool wxTextEntry_SetMargins(void* self, int left, int top)
    {
        return AsTextEntry(self)->SetMargins(left, top);
    }

    EXPORT void wxTextEntry_GetMargins(void* self, int* left, int* top)
    {
        wxPoint pt = AsTextEntry(self)->GetMargins();
        *left = pt.x;
        *top = pt.y;
    }

    EXPORT bool wxTextEntry_AutoComplete(void* self, int count, void* items)
    {
        wxArrayString choices;
        for (int i = 0; i < count; i++)
            choices.Add(((const char**) items)[i]);
        return AsTextEntry(self)->AutoComplete(choices);
    }

    EXPORT bool wxTextEntry_AutoCompleteFileNames(void* self)
    {
        return AsTextEntry(self)->AutoCompleteFileNames();
    }

    EXPORT bool wxTextEntry_AutoCompleteDirectories(void* self)
    {
        return AsTextEntry(self)->AutoCompleteDirectories();
    }
}
