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

    EXPORT int wxSecretValue_IsOk(wxSecretValue* self)
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

    EXPORT int wxSecretStore_IsOk(wxSecretStore* self)
    {
        return self->IsOk();
    }

    EXPORT int wxSecretStore_IsOkWithError(wxSecretStore* self, wxString* error_message)
    {
        return self->IsOk(error_message);
    }

    EXPORT int wxSecretStore_Save(wxSecretStore* self, wxString* service, wxString* username,
                                  wxSecretValue* password)
    {
        return self->Save(*service, *username, *password);
    }

    EXPORT int wxSecretStore_Load(wxSecretStore* self, wxString* service, wxString* username,
                                  wxSecretValue* password)
    {
        return self->Load(*service, *username, *password);
    }

    EXPORT int wxSecretStore_DeleteSecret(wxSecretStore* self, wxString* service)
    {
        return self->Delete(*service);
    }

    // ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
    EXPORT size_t wxSecretValue_GetSize(void* pObject)
    {
        return (size_t) ((wxSecretValue*) pObject)->GetSize();
    }

    EXPORT void wxSecretValue_WipeString(void* str)
    {
        wxSecretValue::WipeString(*(wxString*) str);
    }
}
