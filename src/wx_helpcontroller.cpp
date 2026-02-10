#include "wrapper.h"

#include <wx/fs_zip.h>
#include <wx/html/helpctrl.h>
#include <wx/image.h>

static void InitZipFileSystem()
{
    static bool done = false;
    if (!done)
    {
        done = true;
        wxFileSystem::AddHandler(new wxZipFSHandler());
    }
}

extern "C"
{
    EXPORT void* wxHtmlHelpController_Create(int style, wxWindow* parentWindow)
    {
        InitZipFileSystem();
        wxInitAllImageHandlers();
        return (void*) new wxHtmlHelpController(style, parentWindow);
    }

    EXPORT void wxHtmlHelpController_Delete(void* self)
    {
        delete (wxHtmlHelpController*) self;
    }

    EXPORT void wxHtmlHelpController_SetTitleFormat(void* self, wxString* format)
    {
        ((wxHtmlHelpController*) self)->SetTitleFormat(*format);
    }

    EXPORT void wxHtmlHelpController_SetTempDir(void* self, wxString* path)
    {
        ((wxHtmlHelpController*) self)->SetTempDir(*path);
    }

    EXPORT bool wxHtmlHelpController_AddBook(wxHtmlHelpController* self, wxString* book,
                                             bool show_wait_msg)
    {
        return self->AddBook(*book, show_wait_msg);
    }

    EXPORT void wxHtmlHelpController_Display(wxHtmlHelpController* self, wxString* x)
    {
        self->Display(*x);
    }

    EXPORT void wxHtmlHelpController_DisplayNumber(wxHtmlHelpController* self, int id)
    {
        self->Display(id);
    }

    EXPORT void wxHtmlHelpController_DisplayContents(wxHtmlHelpController* self)
    {
        self->DisplayContents();
    }

    EXPORT void wxHtmlHelpController_DisplayIndex(wxHtmlHelpController* self)
    {
        self->DisplayIndex();
    }

    EXPORT bool wxHtmlHelpController_KeywordSearch(wxHtmlHelpController* self, wxString* keyword,
                                                   int mode)
    {
        return self->KeywordSearch(*keyword, (wxHelpSearchMode) mode);
    }

    EXPORT void* wxHtmlHelpController_GetFrame(void* self)
    {
        return (void*) ((wxHtmlHelpController*) self)->GetFrame();
    }

    EXPORT void wxHtmlHelpController_UseConfig(void* self, wxConfigBase* config, wxString* rootpath)
    {
        ((wxHtmlHelpController*) self)->UseConfig(config, *rootpath);
    }

    EXPORT void wxHtmlHelpController_ReadCustomization(void* self, wxConfigBase* cfg,
                                                       wxString* path)
    {
        ((wxHtmlHelpController*) self)->ReadCustomization(cfg, *path);
    }

    EXPORT void wxHtmlHelpController_WriteCustomization(void* self, wxConfigBase* cfg,
                                                        wxString* path)
    {
        ((wxHtmlHelpController*) self)->WriteCustomization(cfg, *path);
    }

    EXPORT bool wxHtmlHelpController_Initialize(wxHtmlHelpController* self, wxString* file)
    {
        return self->Initialize(*file);
    }

    EXPORT void wxHtmlHelpController_SetViewer(void* self, wxString* viewer, int flags)
    {
        ((wxHtmlHelpController*) self)->SetViewer(*viewer, (long) flags);
    }

    EXPORT bool wxHtmlHelpController_LoadFile(wxHtmlHelpController* self, wxString* file)
    {
        return self->LoadFile(*file);
    }

    EXPORT bool wxHtmlHelpController_DisplaySectionNumber(wxHtmlHelpController* self, int sectionNo)
    {
        return self->DisplaySection(sectionNo);
    }

    EXPORT bool wxHtmlHelpController_DisplaySection(wxHtmlHelpController* self, wxString* section)
    {
        return self->DisplaySection(*section);
    }

    EXPORT bool wxHtmlHelpController_DisplayBlock(wxHtmlHelpController* self, int blockNo)
    {
        return self->DisplayBlock((long) blockNo);
    }

    EXPORT void wxHtmlHelpController_SetFrameParameters(void* self, wxString* title, int width,
                                                        int height, int pos_x, int pos_y,
                                                        bool newFrameEachTime)
    {
        ((wxHtmlHelpController*) self)
            ->SetFrameParameters(*title, wxSize(width, height), wxPoint(pos_x, pos_y),
                                 newFrameEachTime);
    }

    EXPORT void* wxHtmlHelpController_GetFrameParameters(void* self, void* title, int* width,
                                                         int* height, int* pos_x, int* pos_y,
                                                         int* newFrameEachTime)
    {
        void* result;
        wxPoint pos;
        wxSize size;

        result = (void*) ((wxHtmlHelpController*) self)
                     ->GetFrameParameters(&size, &pos, (bool*) newFrameEachTime);

        *height = size.y;
        *width = size.x;
        *pos_x = pos.x;
        *pos_y = pos.y;

        return result;
    }

    EXPORT bool wxHtmlHelpController_Quit(wxHtmlHelpController* self)
    {
        return self->Quit();
    }
}
