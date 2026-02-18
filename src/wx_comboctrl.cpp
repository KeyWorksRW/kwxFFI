#include "kwx_wrapper.h"
#include <wx/combo.h>
#include <wx/odcombo.h>

// wxComboCtrl inherits from wxControl and wxTextEntry.
// Additional methods available via:
//   wxWindow_*    — base window methods (see wx_window.cpp)
//   wxControl_*   — label, alignment (see wx_control.cpp)
//   wxTextEntry_* — text editing, hints, margins, selection, auto-complete (see wx_textentry.cpp)

extern "C"
{
    // wxComboCtrl

    EXPORT void* wxComboCtrl_Create(wxWindow* parent, int id, wxString* value, int x, int y,
                                    int width, int height, long style)
    {
        wxString val = value ? *value : wxString();
        return (void*) new wxComboCtrl(parent, id, val, wxPoint(x, y), wxSize(width, height),
                                       style);
    }

    EXPORT void wxComboCtrl_Dismiss(wxComboCtrl* self)
    {
        self->Dismiss();
    }

    EXPORT void wxComboCtrl_EnablePopupAnimation(wxComboCtrl* self, bool enable)
    {
        self->EnablePopupAnimation(enable);
    }

    EXPORT bool wxComboCtrl_IsPopupWindowState(wxComboCtrl* self, int state)
    {
        return self->IsPopupWindowState(state);
    }

    EXPORT void wxComboCtrl_Popup(wxComboCtrl* self)
    {
        self->Popup();
    }

    EXPORT void wxComboCtrl_SetButtonBitmaps(wxComboCtrl* self, wxBitmapBundle* bmpNormal,
                                             bool pushButtonBg, wxBitmapBundle* bmpPressed,
                                             wxBitmapBundle* bmpHover, wxBitmapBundle* bmpDisabled)
    {
        self->SetButtonBitmaps(
            *bmpNormal, pushButtonBg, bmpPressed ? *bmpPressed : wxBitmapBundle(),
            bmpHover ? *bmpHover : wxBitmapBundle(), bmpDisabled ? *bmpDisabled : wxBitmapBundle());
    }

    EXPORT void wxComboCtrl_SetButtonPosition(wxComboCtrl* self, int width, int height, int side,
                                              int spacingX)
    {
        self->SetButtonPosition(width, height, side, spacingX);
    }

    EXPORT void wxComboCtrl_SetCustomPaintWidth(wxComboCtrl* self, int width)
    {
        self->SetCustomPaintWidth(width);
    }

    EXPORT void wxComboCtrl_SetMargins(wxComboCtrl* self, int left, int top)
    {
        self->SetMargins(wxPoint(left, top));
    }

    EXPORT void wxComboCtrl_SetPopupAnchor(wxComboCtrl* self, int anchorSide)
    {
        self->SetPopupAnchor(anchorSide);
    }

    EXPORT void wxComboCtrl_SetPopupExtents(wxComboCtrl* self, int extLeft, int extRight)
    {
        self->SetPopupExtents(extLeft, extRight);
    }

    EXPORT void wxComboCtrl_SetPopupMaxHeight(wxComboCtrl* self, int height)
    {
        self->SetPopupMaxHeight(height);
    }

    EXPORT void wxComboCtrl_SetPopupMinWidth(wxComboCtrl* self, int width)
    {
        self->SetPopupMinWidth(width);
    }

    EXPORT void wxComboCtrl_SetText(wxComboCtrl* self, wxString* value)
    {
        self->SetText(*value);
    }

    EXPORT void wxComboCtrl_SetTextCtrlStyle(wxComboCtrl* self, int style)
    {
        self->SetTextCtrlStyle(style);
    }

    EXPORT void wxComboCtrl_SetValue(wxComboCtrl* self, wxString* value)
    {
        self->SetValue(*value);
    }

    EXPORT void wxComboCtrl_ShowPopup(wxComboCtrl* self)
    {
        self->ShowPopup();
    }

    EXPORT void wxComboCtrl_HidePopup(wxComboCtrl* self, bool generateEvent)
    {
        self->HidePopup(generateEvent);
    }

    EXPORT bool wxComboCtrl_IsPopupShown(wxComboCtrl* self)
    {
        return self->IsPopupShown();
    }

    EXPORT wxString* wxComboCtrl_GetValue(wxComboCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetValue();
        return result;
    }

    EXPORT void* wxComboCtrl_GetTextCtrl(wxComboCtrl* self)
    {
        return (void*) self->GetTextCtrl();
    }

    EXPORT void* wxComboCtrl_GetPopupWindow(wxComboCtrl* self)
    {
        return (void*) self->GetPopupWindow();
    }

    EXPORT int wxComboCtrl_GetPopupWindowState(wxComboCtrl* self)
    {
        return self->GetPopupWindowState();
    }

    EXPORT int wxComboCtrl_GetCustomPaintWidth(wxComboCtrl* self)
    {
        return self->GetCustomPaintWidth();
    }

    EXPORT void wxComboCtrl_Copy(wxComboCtrl* self)
    {
        self->Copy();
    }

    EXPORT void wxComboCtrl_Cut(wxComboCtrl* self)
    {
        self->Cut();
    }

    EXPORT void wxComboCtrl_Paste(wxComboCtrl* self)
    {
        self->Paste();
    }

    EXPORT void wxComboCtrl_SelectAll(wxComboCtrl* self)
    {
        self->SelectAll();
    }

    EXPORT void wxComboCtrl_Undo(wxComboCtrl* self)
    {
        self->Undo();
    }

    EXPORT void wxComboCtrl_SetSelection(wxComboCtrl* self, long from, long toPos)
    {
        self->SetSelection(from, toPos);
    }

    EXPORT void wxComboCtrl_SetInsertionPoint(wxComboCtrl* self, long pos)
    {
        self->SetInsertionPoint(pos);
    }

    EXPORT void wxComboCtrl_SetInsertionPointEnd(wxComboCtrl* self)
    {
        self->SetInsertionPointEnd();
    }

    EXPORT long wxComboCtrl_GetInsertionPoint(wxComboCtrl* self)
    {
        return self->GetInsertionPoint();
    }

    EXPORT long wxComboCtrl_GetLastPosition(wxComboCtrl* self)
    {
        return self->GetLastPosition();
    }

    EXPORT void wxComboCtrl_Replace(wxComboCtrl* self, long from, long toPos, wxString* value)
    {
        self->Replace(from, toPos, *value);
    }

    EXPORT void wxComboCtrl_Remove(wxComboCtrl* self, long from, long toPos)
    {
        self->Remove(from, toPos);
    }

    EXPORT bool wxComboCtrl_IsEditable(wxComboCtrl* self)
    {
        return self->IsEditable();
    }

    // wxOwnerDrawnComboBox

    EXPORT void* wxOwnerDrawnComboBox_Create(wxWindow* parent, int id, wxString* value, int x,
                                             int y, int width, int height, long style)
    {
        wxString val = value ? *value : wxString();
        return (void*) new wxOwnerDrawnComboBox(parent, id, val, wxPoint(x, y),
                                                wxSize(width, height), wxArrayString(), style);
    }

    EXPORT void* wxOwnerDrawnComboBox_CreateWithChoices(wxWindow* parent, int id, wxString* value,
                                                        int x, int y, int width, int height,
                                                        int count, wxString** choices, long style)
    {
        wxString val = value ? *value : wxString();
        wxArrayString arr;
        for (int i = 0; i < count; i++)
            arr.Add(*choices[i]);
        return (void*) new wxOwnerDrawnComboBox(parent, id, val, wxPoint(x, y),
                                                wxSize(width, height), arr, style);
    }

    EXPORT int wxOwnerDrawnComboBox_Append(wxOwnerDrawnComboBox* self, wxString* item)
    {
        return self->Append(*item);
    }

    EXPORT int wxOwnerDrawnComboBox_AppendWithClientData(wxOwnerDrawnComboBox* self, wxString* item,
                                                         void* clientData)
    {
        return self->Append(*item, clientData);
    }

    EXPORT void wxOwnerDrawnComboBox_Clear(wxOwnerDrawnComboBox* self)
    {
        self->Clear();
    }

    EXPORT void wxOwnerDrawnComboBox_Delete(wxOwnerDrawnComboBox* self, unsigned int index)
    {
        self->Delete(index);
    }

    EXPORT unsigned int wxOwnerDrawnComboBox_GetCount(wxOwnerDrawnComboBox* self)
    {
        return self->GetCount();
    }

    EXPORT int wxOwnerDrawnComboBox_GetSelection(wxOwnerDrawnComboBox* self)
    {
        return self->GetSelection();
    }

    EXPORT wxString* wxOwnerDrawnComboBox_GetString(wxOwnerDrawnComboBox* self, unsigned int index)
    {
        wxString* result = new wxString();
        *result = self->GetString(index);
        return result;
    }

    EXPORT wxString* wxOwnerDrawnComboBox_GetStringSelection(wxOwnerDrawnComboBox* self)
    {
        wxString* result = new wxString();
        int sel = self->GetSelection();
        if (sel != wxNOT_FOUND)
            *result = self->GetString(sel);
        return result;
    }

    EXPORT void wxOwnerDrawnComboBox_SetSelection(wxOwnerDrawnComboBox* self, int index)
    {
        self->SetSelection(index);
    }

    EXPORT void wxOwnerDrawnComboBox_SetString(wxOwnerDrawnComboBox* self, unsigned int index,
                                               wxString* str)
    {
        self->SetString(index, *str);
    }

    EXPORT void wxOwnerDrawnComboBox_SetStringSelection(wxOwnerDrawnComboBox* self, wxString* str)
    {
        self->SetStringSelection(*str);
    }

    EXPORT int wxOwnerDrawnComboBox_FindString(wxOwnerDrawnComboBox* self, wxString* str,
                                               bool caseSensitive)
    {
        return self->FindString(*str, caseSensitive);
    }

    EXPORT int wxOwnerDrawnComboBox_Insert(wxOwnerDrawnComboBox* self, wxString* item,
                                           unsigned int pos)
    {
        return self->Insert(*item, pos);
    }

    EXPORT int wxOwnerDrawnComboBox_InsertWithClientData(wxOwnerDrawnComboBox* self, wxString* item,
                                                         unsigned int pos, void* clientData)
    {
        return self->Insert(*item, pos, clientData);
    }

    EXPORT void* wxOwnerDrawnComboBox_GetClientData(wxOwnerDrawnComboBox* self, unsigned int index)
    {
        return self->GetClientData(index);
    }

    EXPORT void wxOwnerDrawnComboBox_SetClientData(wxOwnerDrawnComboBox* self, unsigned int index,
                                                   void* data)
    {
        self->SetClientData(index, data);
    }

    EXPORT bool wxOwnerDrawnComboBox_IsListEmpty(wxOwnerDrawnComboBox* self)
    {
        return self->IsListEmpty();
    }

    EXPORT bool wxOwnerDrawnComboBox_IsTextEmpty(wxOwnerDrawnComboBox* self)
    {
        return self->IsTextEmpty();
    }
}
