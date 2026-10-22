#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxSecretValue* wxSecretValue_Create(wxString* secret)
    {
        return new wxSecretValue(*secret);
    }

    EXPORT wxSecretValue* wxSecretValue_CreateDefault()
    {
        return new wxSecretValue();
    }

    EXPORT void wxSecretValue_Delete(wxSecretValue* self)
    {
        delete self;
    }

    EXPORT bool wxSecretValue_IsOk(wxSecretValue* self)
    {
        return self->IsOk();
    }

    EXPORT wxString* wxSecretValue_GetAsString(wxSecretValue* self)
    {
        return new wxString(self->GetAsString());
    }

    EXPORT wxSecretStore* wxSecretStore_GetDefault()
    {
        return new wxSecretStore(wxSecretStore::GetDefault());
    }

    EXPORT void wxSecretStore_Delete(wxSecretStore* self)
    {
        delete self;
    }

    EXPORT bool wxSecretStore_IsOk(wxSecretStore* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxSecretStore_IsOkWithError(wxSecretStore* self, wxString* error_message)
    {
        return self->IsOk(error_message);
    }

    EXPORT bool wxSecretStore_Save(wxSecretStore* self, wxString* service, wxString* username,
                                   wxSecretValue* password)
    {
        return self->Save(*service, *username, *password);
    }

    EXPORT bool wxSecretStore_Load(wxSecretStore* self, wxString* service, wxString* username,
                                   wxSecretValue* password)
    {
        return self->Load(*service, *username, *password);
    }

    EXPORT bool wxSecretStore_DeleteSecret(wxSecretStore* self, wxString* service)
    {
        return self->Delete(*service);
    }
}
