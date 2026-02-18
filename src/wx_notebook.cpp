#include "kwx_wrapper.h"

// wxNotebook inherits from wxBookCtrlBase (wxControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT int expNB_TOP()
    {
        return (int) wxNB_TOP;
    }

    EXPORT int expNB_BOTTOM()
    {
        return (int) wxNB_BOTTOM;
    }

    EXPORT int expNB_LEFT()
    {
        return (int) wxNB_LEFT;
    }

    EXPORT int expNB_RIGHT()
    {
        return (int) wxNB_RIGHT;
    }

    EXPORT void* wxNotebook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                   int style)
    {
        return new wxNotebook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxNotebook_GetPageCount(wxNotebook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxNotebook_SetSelection(wxNotebook* self, int nPage)
    {
        return self->SetSelection(nPage);
    }

    EXPORT void wxNotebook_AdvanceSelection(wxNotebook* self, bool bForward)
    {
        self->AdvanceSelection(bForward);
    }

    EXPORT int wxNotebook_GetSelection(wxNotebook* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxNotebook_SetPageText(wxNotebook* self, int nPage, wxString* strText)
    {
        return self->SetPageText(nPage, *strText);
    }

    EXPORT wxString* wxNotebook_GetPageText(wxNotebook* self, int nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT void wxNotebook_SetImageList(wxNotebook* self, void* imageList)
    {
        self->SetImageList((wxImageList*) imageList);
    }

    EXPORT void* wxNotebook_GetImageList(wxNotebook* self)
    {
        return (void*) self->GetImageList();
    }

    EXPORT int wxNotebook_GetPageImage(wxNotebook* self, int nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxNotebook_SetPageImage(wxNotebook* self, int nPage, int nImage)
    {
        return self->SetPageImage(nPage, nImage);
    }

    EXPORT int wxNotebook_GetRowCount(wxNotebook* self)
    {
        return self->GetRowCount();
    }

    EXPORT void wxNotebook_SetPageSize(wxNotebook* self, int width, int height)
    {
        self->SetPageSize(wxSize(width, height));
    }

    EXPORT void wxNotebook_SetPadding(wxNotebook* self, int width, int height)
    {
        self->SetPadding(wxSize(width, height));
    }

    EXPORT int wxNotebook_HitTest(wxNotebook* self, int x, int y, long* flags)
    {
        return self->HitTest(wxPoint(x, y), flags);
    }

    EXPORT int expBK_HITTEST_NOWHERE()
    {
        return (int) wxBK_HITTEST_NOWHERE;
    }

    EXPORT int expBK_HITTEST_ONICON()
    {
        return (int) wxBK_HITTEST_ONICON;
    }

    EXPORT int expBK_HITTEST_ONLABEL()
    {
        return (int) wxBK_HITTEST_ONLABEL;
    }

    EXPORT int expBK_HITTEST_ONITEM()
    {
        return (int) wxBK_HITTEST_ONITEM;
    }

    EXPORT int expBK_HITTEST_ONPAGE()
    {
        return (int) wxBK_HITTEST_ONPAGE;
    }

    EXPORT bool wxNotebook_DeletePage(wxNotebook* self, int nPage)
    {
        return self->DeletePage(nPage);
    }

    EXPORT bool wxNotebook_RemovePage(wxNotebook* self, int nPage)
    {
        return self->RemovePage(nPage);
    }

    EXPORT bool wxNotebook_DeleteAllPages(wxNotebook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxNotebook_AddPage(wxNotebook* self, wxNotebookPage* pPage, wxString* strText,
                                   bool bSelect, int imageId)
    {
        return self->AddPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxNotebook_InsertPage(wxNotebook* self, int nPage, wxNotebookPage* pPage,
                                      wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT void* wxNotebook_GetPage(wxNotebook* self, int nPage)
    {
        return (void*) self->GetPage(nPage);
    }
}
