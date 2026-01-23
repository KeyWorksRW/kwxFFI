#include "wrapper.h"

#include <wx/aboutdlg.h>

extern "C"
{
    EXPORT void* wxAboutDialogInfo_Create()
    {
        return (void*) new wxAboutDialogInfo();
    }

    EXPORT void wxAboutDialogInfo_Delete(wxAboutDialogInfo* self)
    {
        delete self;
    }

    EXPORT void wxAboutDialogInfo_SetName(wxAboutDialogInfo* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxAboutDialogInfo_GetName(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxAboutDialogInfo_SetVersion(wxAboutDialogInfo* self, wxString* version,
                                             wxString* longVersion)
    {
        wxString lv = longVersion ? *longVersion : wxString();
        self->SetVersion(*version, lv);
    }

    EXPORT wxString* wxAboutDialogInfo_GetVersion(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetVersion();
        return result;
    }

    EXPORT wxString* wxAboutDialogInfo_GetLongVersion(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetLongVersion();
        return result;
    }

    EXPORT void wxAboutDialogInfo_SetDescription(wxAboutDialogInfo* self, wxString* desc)
    {
        self->SetDescription(*desc);
    }

    EXPORT wxString* wxAboutDialogInfo_GetDescription(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetDescription();
        return result;
    }

    EXPORT void wxAboutDialogInfo_SetCopyright(wxAboutDialogInfo* self, wxString* copyright)
    {
        self->SetCopyright(*copyright);
    }

    EXPORT wxString* wxAboutDialogInfo_GetCopyright(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetCopyright();
        return result;
    }

    EXPORT void wxAboutDialogInfo_SetLicence(wxAboutDialogInfo* self, wxString* licence)
    {
        self->SetLicence(*licence);
    }

    EXPORT void wxAboutDialogInfo_SetLicense(wxAboutDialogInfo* self, wxString* licence)
    {
        self->SetLicense(*licence);
    }

    EXPORT wxString* wxAboutDialogInfo_GetLicence(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetLicence();
        return result;
    }

    EXPORT void wxAboutDialogInfo_SetIcon(wxAboutDialogInfo* self, wxIcon* icon)
    {
        self->SetIcon(*icon);
    }

    EXPORT bool wxAboutDialogInfo_HasIcon(wxAboutDialogInfo* self)
    {
        return self->HasIcon();
    }

    EXPORT void wxAboutDialogInfo_SetWebSite(wxAboutDialogInfo* self, wxString* url, wxString* desc)
    {
        wxString d = desc ? *desc : wxString();
        self->SetWebSite(*url, d);
    }

    EXPORT wxString* wxAboutDialogInfo_GetWebSiteURL(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetWebSiteURL();
        return result;
    }

    EXPORT wxString* wxAboutDialogInfo_GetWebSiteDescription(wxAboutDialogInfo* self)
    {
        wxString* result = new wxString();
        *result = self->GetWebSiteDescription();
        return result;
    }

    EXPORT void wxAboutDialogInfo_AddDeveloper(wxAboutDialogInfo* self, wxString* developer)
    {
        self->AddDeveloper(*developer);
    }

    EXPORT void wxAboutDialogInfo_AddDocWriter(wxAboutDialogInfo* self, wxString* docwriter)
    {
        self->AddDocWriter(*docwriter);
    }

    EXPORT void wxAboutDialogInfo_AddArtist(wxAboutDialogInfo* self, wxString* artist)
    {
        self->AddArtist(*artist);
    }

    EXPORT void wxAboutDialogInfo_AddTranslator(wxAboutDialogInfo* self, wxString* translator)
    {
        self->AddTranslator(*translator);
    }

    EXPORT bool wxAboutDialogInfo_HasDevelopers(wxAboutDialogInfo* self)
    {
        return self->HasDevelopers();
    }

    EXPORT bool wxAboutDialogInfo_HasDocWriters(wxAboutDialogInfo* self)
    {
        return self->HasDocWriters();
    }

    EXPORT bool wxAboutDialogInfo_HasArtists(wxAboutDialogInfo* self)
    {
        return self->HasArtists();
    }

    EXPORT bool wxAboutDialogInfo_HasTranslators(wxAboutDialogInfo* self)
    {
        return self->HasTranslators();
    }

    EXPORT bool wxAboutDialogInfo_HasLicence(wxAboutDialogInfo* self)
    {
        return self->HasLicence();
    }

    EXPORT bool wxAboutDialogInfo_HasWebSite(wxAboutDialogInfo* self)
    {
        return self->HasWebSite();
    }

    // The main function to show the about dialog
    EXPORT void wxAboutBox(wxAboutDialogInfo* info, wxWindow* parent)
    {
        ::wxAboutBox(*info, parent);
    }
}
