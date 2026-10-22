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

    EXPORT bool wxExtHelpController_Initialize(wxExtHelpController* self, wxString* dir)
    {
        return self->Initialize(*dir);
    }

    EXPORT bool wxExtHelpController_LoadFile(wxExtHelpController* self, wxString* file)
    {
        return self->LoadFile(*file);
    }

    EXPORT bool wxExtHelpController_DisplayContents(wxExtHelpController* self)
    {
        return self->DisplayContents();
    }

    EXPORT bool wxExtHelpController_DisplaySection(wxExtHelpController* self, int section_no)
    {
        return self->DisplaySection(section_no);
    }

    EXPORT bool wxExtHelpController_DisplaySectionName(wxExtHelpController* self, wxString* section)
    {
        return self->DisplaySection(*section);
    }

    EXPORT bool wxExtHelpController_DisplayBlock(wxExtHelpController* self, long block_no)
    {
        return self->DisplayBlock(block_no);
    }

    EXPORT bool wxExtHelpController_KeywordSearch(wxExtHelpController* self, wxString* keyword,
                                                  int mode)
    {
        return self->KeywordSearch(*keyword, static_cast<wxHelpSearchMode>(mode));
    }

    EXPORT bool wxExtHelpController_Quit(wxExtHelpController* self)
    {
        return self->Quit();
    }

    EXPORT void wxExtHelpController_Delete(wxExtHelpController* self)
    {
        delete self;
    }
}
