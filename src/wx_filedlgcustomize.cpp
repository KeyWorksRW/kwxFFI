#include "kwx_wrapper.h"

#include <vector>

// kwxFileDialogCustomizeHook is implemented inline in kwx_helper_filedlgcustomize.h;
// this file provides the C entry points for the hook and the custom controls.

extern "C"
{
    EXPORT void* wxFileDialogCustomizeHook_Create(void* pObject,
                                                  FileDialogCustomControlsFunc add_func,
                                                  FileDialogCustomControlsUpdateFunc update_func,
                                                  FileDialogCustomControlsUpdateFunc transfer_func)
    {
        return static_cast<void*>(
            new kwxFileDialogCustomizeHook(pObject, add_func, update_func, transfer_func));
    }

    EXPORT void wxFileDialogCustomizeHook_Delete(wxFileDialogCustomizeHook* self)
    {
        delete self;
    }

    EXPORT void* wxFileDialogCustomize_AddButton(wxFileDialogCustomize* self, wxString* label)
    {
        return static_cast<void*>(self->AddButton(*label));
    }

    EXPORT void* wxFileDialogCustomize_AddCheckBox(wxFileDialogCustomize* self, wxString* label)
    {
        return static_cast<void*>(self->AddCheckBox(*label));
    }

    EXPORT void* wxFileDialogCustomize_AddChoice(wxFileDialogCustomize* self, int n, void* choices)
    {
        std::vector<wxString> items;
        items.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            items.emplace_back(static_cast<char**>(choices)[i]);
        }
        return static_cast<void*>(self->AddChoice(items.size(), items.data()));
    }

    EXPORT void* wxFileDialogCustomize_AddStaticText(wxFileDialogCustomize* self, wxString* label)
    {
        return static_cast<void*>(self->AddStaticText(*label));
    }

    EXPORT void* wxFileDialogCustomize_AddTextCtrl(wxFileDialogCustomize* self, wxString* label)
    {
        return static_cast<void*>(self->AddTextCtrl(*label));
    }

    EXPORT void wxFileDialogCustomControl_Show(wxFileDialogCustomControl* self, bool show)
    {
        self->Show(show);
    }

    EXPORT void wxFileDialogCustomControl_Hide(wxFileDialogCustomControl* self)
    {
        self->Hide();
    }

    EXPORT void wxFileDialogCustomControl_Enable(wxFileDialogCustomControl* self, bool enable)
    {
        self->Enable(enable);
    }

    EXPORT void wxFileDialogCustomControl_Disable(wxFileDialogCustomControl* self)
    {
        self->Disable();
    }

    EXPORT bool wxFileDialogCustomControl_GetValue(wxFileDialogCustomControl* self)
    {
        wxFileDialogCheckBox* check_box = dynamic_cast<wxFileDialogCheckBox*>(self);
        if (!check_box)
        {
            return false;
        }
        return check_box->GetValue();
    }

    EXPORT void wxFileDialogCustomControl_SetValue(wxFileDialogCustomControl* self, bool value)
    {
        wxFileDialogCheckBox* check_box = dynamic_cast<wxFileDialogCheckBox*>(self);
        if (check_box)
        {
            check_box->SetValue(value);
        }
    }

    EXPORT wxString* wxFileDialogCustomControl_GetTextValue(wxFileDialogCustomControl* self)
    {
        wxString* result = new wxString();
        wxFileDialogTextCtrl* text_ctrl = dynamic_cast<wxFileDialogTextCtrl*>(self);
        if (text_ctrl)
        {
            *result = text_ctrl->GetValue();
        }
        return result;
    }

    EXPORT void wxFileDialogCustomControl_SetTextValue(wxFileDialogCustomControl* self,
                                                       wxString* text)
    {
        wxFileDialogTextCtrl* text_ctrl = dynamic_cast<wxFileDialogTextCtrl*>(self);
        if (text_ctrl)
        {
            text_ctrl->SetValue(*text);
        }
    }

    EXPORT int wxFileDialogCustomControl_GetSelection(wxFileDialogCustomControl* self)
    {
        wxFileDialogChoice* choice = dynamic_cast<wxFileDialogChoice*>(self);
        if (!choice)
        {
            return -1;
        }
        return choice->GetSelection();
    }

    EXPORT void wxFileDialogCustomControl_SetSelection(wxFileDialogCustomControl* self,
                                                       int selection)
    {
        wxFileDialogChoice* choice = dynamic_cast<wxFileDialogChoice*>(self);
        if (choice)
        {
            choice->SetSelection(selection);
        }
    }

    EXPORT void wxFileDialogCustomControl_SetLabelText(wxFileDialogCustomControl* self,
                                                       wxString* text)
    {
        wxFileDialogStaticText* static_text = dynamic_cast<wxFileDialogStaticText*>(self);
        if (static_text)
        {
            static_text->SetLabelText(*text);
        }
    }
}
