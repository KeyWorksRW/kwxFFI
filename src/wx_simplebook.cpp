#include "wrapper.h"

extern "C"
{
    EXPORT wxSimplebook* wxSimplebook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                             int style)
    {
        return new wxSimplebook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxSimplebook_GetPageCount(wxSimplebook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxSimplebook_SetSelection(wxSimplebook* self, int nPage)
    {
        return self->SetSelection(nPage);
    }

    EXPORT int wxSimplebook_ChangeSelection(wxSimplebook* self, int nPage)
    {
        return self->ChangeSelection(nPage);
    }

    EXPORT int wxSimplebook_GetSelection(wxSimplebook* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxSimplebook_SetPageText(wxSimplebook* self, int nPage, wxString* strText)
    {
        return self->SetPageText(nPage, *strText);
    }

    EXPORT wxString* wxSimplebook_GetPageText(wxSimplebook* self, int nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT void wxSimplebook_SetImageList(wxSimplebook* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT wxImageList* wxSimplebook_GetImageList(wxSimplebook* self)
    {
        return self->GetImageList();
    }

    EXPORT int wxSimplebook_GetPageImage(wxSimplebook* self, int nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxSimplebook_SetPageImage(wxSimplebook* self, int nPage, int nImage)
    {
        return self->SetPageImage(nPage, nImage);
    }

    EXPORT bool wxSimplebook_DeletePage(wxSimplebook* self, int nPage)
    {
        return self->DeletePage(nPage);
    }

    EXPORT bool wxSimplebook_RemovePage(wxSimplebook* self, int nPage)
    {
        return self->RemovePage(nPage);
    }

    EXPORT bool wxSimplebook_DeleteAllPages(wxSimplebook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxSimplebook_AddPage(wxSimplebook* self, wxWindow* pPage, wxString* strText,
                                     bool bSelect, int imageId)
    {
        return self->AddPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxSimplebook_InsertPage(wxSimplebook* self, int nPage, wxWindow* pPage,
                                        wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT wxWindow* wxSimplebook_GetPage(wxSimplebook* self, int nPage)
    {
        return self->GetPage(nPage);
    }

    EXPORT void wxSimplebook_ShowNewPage(wxSimplebook* self, wxWindow* page)
    {
        self->ShowNewPage(page);
    }
}
