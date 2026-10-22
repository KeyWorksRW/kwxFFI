#include "kwx_wrapper.h"

#include <wx/fs_zip.h>

static void InitHtmlHelpFileSystem()
{
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        wxFileSystem::AddHandler(new wxZipFSHandler());
    }
}

extern "C"
{
    EXPORT wxHtmlHelpData* wxHtmlHelpData_Create()
    {
        return new wxHtmlHelpData();
    }

    EXPORT void wxHtmlHelpData_Delete(wxHtmlHelpData* self)
    {
        delete self;
    }

    EXPORT bool wxHtmlHelpData_AddBook(wxHtmlHelpData* self, wxString* book)
    {
        InitHtmlHelpFileSystem();
        return self->AddBook(*book);
    }

    EXPORT wxString* wxHtmlHelpData_FindPageById(wxHtmlHelpData* self, int id)
    {
        return new wxString(self->FindPageById(id));
    }

    EXPORT wxString* wxHtmlHelpData_FindPageByName(wxHtmlHelpData* self, wxString* page)
    {
        return new wxString(self->FindPageByName(*page));
    }

    EXPORT void wxHtmlHelpData_SetTempDir(wxHtmlHelpData* self, wxString* path)
    {
        self->SetTempDir(*path);
    }

    EXPORT void* wxHtmlHelpData_GetBookRecArray(wxHtmlHelpData* self)
    {
        return const_cast<wxHtmlBookRecArray*>(&self->GetBookRecArray());
    }

    EXPORT void* wxHtmlHelpData_GetContentsArray(wxHtmlHelpData* self)
    {
        return const_cast<wxHtmlHelpDataItems*>(&self->GetContentsArray());
    }

    EXPORT void* wxHtmlHelpData_GetIndexArray(wxHtmlHelpData* self)
    {
        return const_cast<wxHtmlHelpDataItems*>(&self->GetIndexArray());
    }

    EXPORT wxHtmlHelpWindow* wxHtmlHelpWindow_Create(wxWindow* parent, int id, int x, int y,
                                                     int width, int height, int style,
                                                     int helpStyle)
    {
        InitHtmlHelpFileSystem();
        return new wxHtmlHelpWindow(parent, id, wxPoint(x, y), wxSize(width, height), style,
                                    helpStyle);
    }

    EXPORT void wxHtmlHelpWindow_Delete(wxHtmlHelpWindow* self)
    {
        delete self;
    }

    EXPORT bool wxHtmlHelpWindow_Display(wxHtmlHelpWindow* self, wxString* x)
    {
        return self->Display(*x);
    }

    EXPORT bool wxHtmlHelpWindow_DisplayNumber(wxHtmlHelpWindow* self, int id)
    {
        return self->Display(id);
    }

    EXPORT bool wxHtmlHelpWindow_DisplayContents(wxHtmlHelpWindow* self)
    {
        return self->DisplayContents();
    }

    EXPORT bool wxHtmlHelpWindow_DisplayIndex(wxHtmlHelpWindow* self)
    {
        return self->DisplayIndex();
    }

    EXPORT bool wxHtmlHelpWindow_KeywordSearch(wxHtmlHelpWindow* self, wxString* keyword, int mode)
    {
        return self->KeywordSearch(*keyword, static_cast<wxHelpSearchMode>(mode));
    }

    EXPORT void wxHtmlHelpWindow_ReadCustomization(wxHtmlHelpWindow* self, wxConfigBase* cfg,
                                                   wxString* path)
    {
        self->ReadCustomization(cfg, *path);
    }

    EXPORT void wxHtmlHelpWindow_WriteCustomization(wxHtmlHelpWindow* self, wxConfigBase* cfg,
                                                    wxString* path)
    {
        self->WriteCustomization(cfg, *path);
    }

    EXPORT void wxHtmlHelpWindow_UseConfig(wxHtmlHelpWindow* self, wxConfigBase* config,
                                           wxString* rootPath)
    {
        self->UseConfig(config, *rootPath);
    }

    EXPORT void wxHtmlHelpWindow_NotifyPageChanged(wxHtmlHelpWindow* self)
    {
        self->NotifyPageChanged();
    }

    EXPORT void wxHtmlHelpWindow_RefreshLists(wxHtmlHelpWindow* self)
    {
        self->RefreshLists();
    }

    EXPORT void* wxHtmlHelpWindow_GetData(wxHtmlHelpWindow* self)
    {
        return self->GetData();
    }

    EXPORT void* wxHtmlHelpWindow_GetController(wxHtmlHelpWindow* self)
    {
        return self->GetController();
    }

    EXPORT void wxHtmlHelpWindow_SetController(wxHtmlHelpWindow* self, void* controller)
    {
        self->SetController(static_cast<wxHtmlHelpController*>(controller));
    }

    EXPORT void* wxHtmlHelpWindow_GetHtmlWindow(wxHtmlHelpWindow* self)
    {
        return self->GetHtmlWindow();
    }

    EXPORT void* wxHtmlHelpWindow_GetSplitterWindow(wxHtmlHelpWindow* self)
    {
        return self->GetSplitterWindow();
    }

    EXPORT void* wxHtmlHelpWindow_GetToolBar(wxHtmlHelpWindow* self)
    {
        return self->GetToolBar();
    }

    EXPORT void* wxHtmlHelpWindow_GetTreeCtrl(wxHtmlHelpWindow* self)
    {
        return self->GetTreeCtrl();
    }
}
