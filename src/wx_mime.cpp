#include "kwx_wrapper.h"
#include <wx/mimetype.h>

extern "C"
{
    EXPORT void* wxMimeTypesManager_Create()
    {
        return (void*) wxTheMimeTypesManager;
    }

    EXPORT void* wxMimeTypesManager_GetFileTypeFromExtension(wxMimeTypesManager* self,
                                                             wxString* extension)
    {
        return (void*) self->GetFileTypeFromExtension(*extension);
    }

    EXPORT void* wxMimeTypesManager_GetFileTypeFromMimeType(wxMimeTypesManager* self,
                                                            wxString* name)
    {
        return (void*) self->GetFileTypeFromMimeType(*name);
    }

    EXPORT int wxMimeTypesManager_EnumAllFileTypes(wxMimeTypesManager* self, void* list)
    {
        wxArrayString arr;
        int result = (int) self->EnumAllFileTypes(arr);

        if (list)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) list)[i] = strdup(arr.Item(i).utf8_string().data());
        }

        return result;
    }

    EXPORT void wxMimeTypesManager_AddFallbacks(wxMimeTypesManager* self, void* types)
    {
        self->AddFallbacks((const wxFileTypeInfo*) types);
    }

    EXPORT bool wxMimeTypesManager_IsOfType(wxMimeTypesManager* self, wxString* type,
                                            wxString* wildcard)
    {
        return self->IsOfType(*type, *wildcard);
    }

    EXPORT wxString* wxFileType_GetMimeType(wxFileType* self)
    {
        wxString* result = new wxString();
        if (self->GetMimeType(result) != true)
            result->Clear();
        return result;
    }

    EXPORT int wxFileType_GetMimeTypes(wxFileType* self, void* list)
    {
        wxArrayString arr;

        if (self->GetMimeTypes(arr) && list)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) list)[i] = strdup(arr.Item(i).utf8_string().data());
        }

        return arr.GetCount();
    }

    EXPORT int wxFileType_GetExtensions(wxFileType* self, void* list)
    {
        wxArrayString arr;

        if (self->GetExtensions(arr) && list)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) list)[i] = strdup(arr.Item(i).utf8_string().data());
        }

        return arr.GetCount();
    }

    EXPORT bool wxFileType_GetIcon(wxFileType* self, wxIcon* icon)
    {
        wxIconLocation iconLoc;
        bool res = self->GetIcon(&iconLoc);
        *icon = wxIcon(iconLoc);
        return res;
    }

    EXPORT wxString* wxFileType_GetDescription(wxFileType* self)
    {
        wxString* result = new wxString();
        if (self->GetDescription(result) != true)
            result->Clear();
        return result;
    }

    EXPORT wxString* wxFileType_GetOpenCommand(wxFileType* self, void* params)
    {
        wxString* result = new wxString();
        if (self->GetOpenCommand(result, *((wxFileType::MessageParameters*) params)) != true)
            result->Clear();
        return result;
    }

    EXPORT wxString* wxFileType_GetPrintCommand(wxFileType* self, void* params)
    {
        wxString* result = new wxString();
        if (self->GetPrintCommand(result, *((wxFileType::MessageParameters*) params)) != true)
            result->Clear();
        return result;
    }

    EXPORT wxString* wxFileType_ExpandCommand(wxFileType* self, void* command, void* params)
    {
        wxString* result = new wxString();
        *result =
            self->ExpandCommand((const char*) command, *((wxFileType::MessageParameters*) params));
        return result;
    }

    EXPORT void wxFileType_Delete(wxFileType* self)
    {
        delete self;
    }
}
