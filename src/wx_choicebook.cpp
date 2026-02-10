#include "wrapper.h"

extern "C"
{
    EXPORT wxChoicebook* wxChoicebook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                             int style)
    {
        return new wxChoicebook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxChoicebook_GetPageCount(wxChoicebook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxChoicebook_SetSelection(wxChoicebook* self, int nPage)
    {
        return self->SetSelection(nPage);
    }

    EXPORT void wxChoicebook_AdvanceSelection(wxChoicebook* self, bool bForward)
    {
        self->AdvanceSelection(bForward);
    }

    EXPORT int wxChoicebook_GetSelection(wxChoicebook* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxChoicebook_SetPageText(wxChoicebook* self, int nPage, wxString* strText)
    {
        return self->SetPageText(nPage, *strText);
    }

    EXPORT wxString* wxChoicebook_GetPageText(wxChoicebook* self, int nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT void wxChoicebook_SetImageList(wxChoicebook* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT wxImageList* wxChoicebook_GetImageList(wxChoicebook* self)
    {
        return self->GetImageList();
    }

    EXPORT int wxChoicebook_GetPageImage(wxChoicebook* self, int nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxChoicebook_SetPageImage(wxChoicebook* self, int nPage, int nImage)
    {
        return self->SetPageImage(nPage, nImage);
    }

    EXPORT bool wxChoicebook_DeletePage(wxChoicebook* self, int nPage)
    {
        return self->DeletePage(nPage);
    }

    EXPORT bool wxChoicebook_RemovePage(wxChoicebook* self, int nPage)
    {
        return self->RemovePage(nPage);
    }

    EXPORT bool wxChoicebook_DeleteAllPages(wxChoicebook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxChoicebook_AddPage(wxChoicebook* self, wxWindow* pPage, wxString* strText,
                                     bool bSelect, int imageId)
    {
        return self->AddPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxChoicebook_InsertPage(wxChoicebook* self, int nPage, wxWindow* pPage,
                                        wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT wxWindow* wxChoicebook_GetPage(wxChoicebook* self, int nPage)
    {
        return self->GetPage(nPage);
    }

    EXPORT wxChoice* wxChoicebook_GetChoiceCtrl(wxChoicebook* self)
    {
        return self->GetChoiceCtrl();
    }

    EXPORT int wxChoicebook_HitTest(wxChoicebook* self, int x, int y, long* flags)
    {
        return self->HitTest(wxPoint(x, y), flags);
    }

    EXPORT int expCHB_DEFAULT()
    {
        return (int) wxCHB_DEFAULT;
    }

    EXPORT int expCHB_TOP()
    {
        return (int) wxCHB_TOP;
    }

    EXPORT int expCHB_BOTTOM()
    {
        return (int) wxCHB_BOTTOM;
    }

    EXPORT int expCHB_LEFT()
    {
        return (int) wxCHB_LEFT;
    }

    EXPORT int expCHB_RIGHT()
    {
        return (int) wxCHB_RIGHT;
    }
}
