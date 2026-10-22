#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxCredentialEntryDialog_Create(wxWindow* parent, wxString* message,
                                                wxString* title, wxString* user, wxString* password)
    {
        const wxWebCredentials credentials(*user, wxSecretValue(*password));
        wxCredentialEntryDialog* dialog = new wxCredentialEntryDialog();
        if (!dialog->Create(parent, *message, *title, credentials))
        {
            delete dialog;
            return nullptr;
        }
        return static_cast<void*>(dialog);
    }

    EXPORT wxString* wxCredentialEntryDialog_GetUser(wxCredentialEntryDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetCredentials().GetUser();
        return result;
    }

    EXPORT wxString* wxCredentialEntryDialog_GetPassword(wxCredentialEntryDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetCredentials().GetPassword().GetAsString();
        return result;
    }

    EXPORT void wxCredentialEntryDialog_SetUser(wxCredentialEntryDialog* self, wxString* user)
    {
        self->SetUser(*user);
    }

    EXPORT void wxCredentialEntryDialog_SetPassword(wxCredentialEntryDialog* self,
                                                    wxString* password)
    {
        self->SetPassword(*password);
    }

    EXPORT void wxCredentialEntryDialog_Delete(wxCredentialEntryDialog* self)
    {
        delete self;
    }
}
