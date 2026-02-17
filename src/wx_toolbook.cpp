#include "wrapper.h"

// wxToolbook inherits from wxBookCtrlBase (wxControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxToolbook* wxToolbook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                         int style)
    {
        return new wxToolbook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxToolbook_GetPageCount(wxToolbook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxToolbook_SetSelection(wxToolbook* self, int nPage)
    {
        return self->SetSelection(nPage);
    }

    EXPORT void wxToolbook_AdvanceSelection(wxToolbook* self, bool bForward)
    {
        self->AdvanceSelection(bForward);
    }

    EXPORT int wxToolbook_GetSelection(wxToolbook* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxToolbook_SetPageText(wxToolbook* self, int nPage, wxString* strText)
    {
        return self->SetPageText(nPage, *strText);
    }

    EXPORT wxString* wxToolbook_GetPageText(wxToolbook* self, int nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT void wxToolbook_SetImageList(wxToolbook* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT wxImageList* wxToolbook_GetImageList(wxToolbook* self)
    {
        return self->GetImageList();
    }

    EXPORT int wxToolbook_GetPageImage(wxToolbook* self, int nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxToolbook_SetPageImage(wxToolbook* self, int nPage, int nImage)
    {
        return self->SetPageImage(nPage, nImage);
    }

    EXPORT bool wxToolbook_DeletePage(wxToolbook* self, int nPage)
    {
        return self->DeletePage(nPage);
    }

    EXPORT bool wxToolbook_RemovePage(wxToolbook* self, int nPage)
    {
        return self->RemovePage(nPage);
    }

    EXPORT bool wxToolbook_DeleteAllPages(wxToolbook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxToolbook_AddPage(wxToolbook* self, wxWindow* pPage, wxString* strText,
                                   bool bSelect, int imageId)
    {
        return self->AddPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxToolbook_InsertPage(wxToolbook* self, int nPage, wxWindow* pPage,
                                      wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT wxWindow* wxToolbook_GetPage(wxToolbook* self, int nPage)
    {
        return self->GetPage(nPage);
    }

    EXPORT wxToolBarBase* wxToolbook_GetToolBar(wxToolbook* self)
    {
        return self->GetToolBar();
    }

    EXPORT int wxToolbook_HitTest(wxToolbook* self, int x, int y, long* flags)
    {
        return self->HitTest(wxPoint(x, y), flags);
    }

    EXPORT int expTBK_BUTTONBAR()
    {
        return (int) wxTBK_BUTTONBAR;
    }

    EXPORT int expTBK_HORZ_LAYOUT()
    {
        return (int) wxTBK_HORZ_LAYOUT;
    }
}
