#include "wrapper.h"

// wxMessageDialog inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxMessageDialog_Create(wxWindow* parent, wxString* message, wxString* caption,
                                        int style)
    {
        return new wxMessageDialog(parent, *message, *caption, style);
    }

    EXPORT void wxMessageDialog_Delete(void* pObject)
    {
        delete (wxMessageDialog*) pObject;
    }

    EXPORT int wxMessageDialog_ShowModal(void* pObject)
    {
        return ((wxMessageDialog*) pObject)->ShowModal();
    }

    EXPORT int kwxMessageBox(wxString* message, wxString* caption, int style, wxWindow* parent,
                             int x, int y)
    {
        return wxMessageBox(*message, *caption, style, parent, x, y);
    }

    EXPORT void wxMessageDialog_SetMessage(wxMessageDialog* self, wxString* message)
    {
        self->SetMessage(*message);
    }

    EXPORT wxString* wxMessageDialog_GetMessage(wxMessageDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetMessage();
        return result;
    }

    EXPORT void wxMessageDialog_SetExtendedMessage(wxMessageDialog* self, wxString* message)
    {
        self->SetExtendedMessage(*message);
    }

    EXPORT wxString* wxMessageDialog_GetExtendedMessage(wxMessageDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetExtendedMessage();
        return result;
    }

    EXPORT bool wxMessageDialog_SetOKLabel(wxMessageDialog* self, wxString* label)
    {
        return self->SetOKLabel(*label);
    }

    EXPORT bool wxMessageDialog_SetOKCancelLabels(wxMessageDialog* self, wxString* ok,
                                                  wxString* cancel)
    {
        return self->SetOKCancelLabels(*ok, *cancel);
    }

    EXPORT bool wxMessageDialog_SetYesNoLabels(wxMessageDialog* self, wxString* yes, wxString* no)
    {
        return self->SetYesNoLabels(*yes, *no);
    }

    EXPORT bool wxMessageDialog_SetYesNoCancelLabels(wxMessageDialog* self, wxString* yes,
                                                     wxString* no, wxString* cancel)
    {
        return self->SetYesNoCancelLabels(*yes, *no, *cancel);
    }

    EXPORT bool wxMessageDialog_SetHelpLabel(wxMessageDialog* self, wxString* label)
    {
        return self->SetHelpLabel(*label);
    }
}
