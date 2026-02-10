#include "wrapper.h"

extern "C"
{
    EXPORT wxListbook* wxListbook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                         int style)
    {
        return new wxListbook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxListbook_GetPageCount(wxListbook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxListbook_SetSelection(wxListbook* self, int nPage)
    {
        return self->SetSelection(nPage);
    }

    EXPORT void wxListbook_AdvanceSelection(wxListbook* self, bool bForward)
    {
        self->AdvanceSelection(bForward);
    }

    EXPORT int wxListbook_GetSelection(wxListbook* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxListbook_SetPageText(wxListbook* self, int nPage, wxString* strText)
    {
        return self->SetPageText(nPage, *strText);
    }

    EXPORT wxString* wxListbook_GetPageText(wxListbook* self, int nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT void wxListbook_SetImageList(wxListbook* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT wxImageList* wxListbook_GetImageList(wxListbook* self)
    {
        return self->GetImageList();
    }

    EXPORT int wxListbook_GetPageImage(wxListbook* self, int nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxListbook_SetPageImage(wxListbook* self, int nPage, int nImage)
    {
        return self->SetPageImage(nPage, nImage);
    }

    EXPORT bool wxListbook_DeletePage(wxListbook* self, int nPage)
    {
        return self->DeletePage(nPage);
    }

    EXPORT bool wxListbook_RemovePage(wxListbook* self, int nPage)
    {
        return self->RemovePage(nPage);
    }

    EXPORT bool wxListbook_DeleteAllPages(wxListbook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxListbook_AddPage(wxListbook* self, wxWindow* pPage, wxString* strText,
                                   bool bSelect, int imageId)
    {
        return self->AddPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxListbook_InsertPage(wxListbook* self, int nPage, wxWindow* pPage,
                                      wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT wxWindow* wxListbook_GetPage(wxListbook* self, int nPage)
    {
        return self->GetPage(nPage);
    }

    EXPORT wxListView* wxListbook_GetListView(wxListbook* self)
    {
        return self->GetListView();
    }

    EXPORT int wxListbook_HitTest(wxListbook* self, int x, int y, long* flags)
    {
        return self->HitTest(wxPoint(x, y), flags);
    }

    EXPORT int expLB_DEFAULT()
    {
        return (int) wxLB_DEFAULT;
    }

    EXPORT int expLB_TOP()
    {
        return (int) wxLB_TOP;
    }

    EXPORT int expLB_BOTTOM()
    {
        return (int) wxLB_BOTTOM;
    }

    EXPORT int expLB_LEFT()
    {
        return (int) wxLB_LEFT;
    }

    EXPORT int expLB_RIGHT()
    {
        return (int) wxLB_RIGHT;
    }
}
