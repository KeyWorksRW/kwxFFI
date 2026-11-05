#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxExtHelpController_Create(wxWindow* parent_window)
    {
        return static_cast<void*>(new wxExtHelpController(parent_window));
    }

    EXPORT void wxExtHelpController_SetViewer(wxExtHelpController* self, wxString* viewer,
                                              long flags)
    {
        self->SetViewer(*viewer, flags);
    }

    EXPORT int wxExtHelpController_Initialize(wxExtHelpController* self, wxString* dir)
    {
        return self->Initialize(*dir);
    }

    EXPORT int wxExtHelpController_LoadFile(wxExtHelpController* self, wxString* file)
    {
        return self->LoadFile(*file);
    }

    EXPORT int wxExtHelpController_DisplayContents(wxExtHelpController* self)
    {
        return self->DisplayContents();
    }

    EXPORT int wxExtHelpController_DisplaySection(wxExtHelpController* self, int section_no)
    {
        return self->DisplaySection(section_no);
    }

    EXPORT int wxExtHelpController_DisplaySectionName(wxExtHelpController* self, wxString* section)
    {
        return self->DisplaySection(*section);
    }

    EXPORT int wxExtHelpController_DisplayBlock(wxExtHelpController* self, long block_no)
    {
        return self->DisplayBlock(block_no);
    }

    EXPORT int wxExtHelpController_KeywordSearch(wxExtHelpController* self, wxString* keyword,
                                                 int mode)
    {
        return self->KeywordSearch(*keyword, static_cast<wxHelpSearchMode>(mode));
    }

    EXPORT int wxExtHelpController_Quit(wxExtHelpController* self)
    {
        return self->Quit();
    }

    EXPORT void wxExtHelpController_Delete(wxExtHelpController* self)
    {
        delete self;
    }
}
