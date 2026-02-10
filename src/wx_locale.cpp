#include "wrapper.h"
#include <wx/intl.h>

extern "C"
{
    EXPORT void* wxLocale_Create(int language, int flags)
    {
        return (void*) new wxLocale(language, flags);
    }

    EXPORT void wxLocale_Delete(wxLocale* self)
    {
        delete self;
    }

    EXPORT bool wxLocale_IsOk(wxLocale* self)
    {
        return self->IsOk();
    }

    EXPORT void* wxLocale_GetLocale(wxLocale* self)
    {
        wxString retVal = self->GetLocale();
        return (void*) strdup(retVal.utf8_str().data());
    }

    EXPORT void wxLocale_AddCatalogLookupPathPrefix(wxLocale* self, void* prefix)
    {
        self->AddCatalogLookupPathPrefix((const char*) prefix);
    }

    EXPORT bool wxLocale_AddCatalog(wxLocale* self, void* szDomain, int msgIdLanguage)
    {
        return self->AddCatalog((const char*) szDomain, (wxLanguage) msgIdLanguage);
    }

    EXPORT bool wxLocale_IsLoaded(wxLocale* self, void* szDomain)
    {
        return self->IsLoaded((const char*) szDomain);
    }

    EXPORT void* wxLocale_GetString(wxLocale* self, void* szOrigString, void* szDomain)
    {
        wxString retVal = self->GetString((const char*) szOrigString, (const char*) szDomain);
        return (void*) strdup(retVal.utf8_str().data());
    }

    EXPORT wxString* wxLocale_GetName(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxLocale*) pObject)->GetName();
        return result;
    }

    EXPORT void* wxGetkwxLocale()
    {
        return (void*) wxGetLocale();
    }

    EXPORT void* wxGetkwxTranslation(void* sz)
    {
        wxString retVal = wxGetTranslation((const char*) sz);
        return (void*) strdup(retVal.utf8_str().data());
    }
}
