#include "wrapper.h"

// wxTreebook inherits from wxBookCtrlBase (wxControl).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxTreebook* wxTreebook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                         int style)
    {
        return new wxTreebook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxTreebook_GetPageCount(wxTreebook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxTreebook_SetSelection(wxTreebook* self, int nPage)
    {
        return self->SetSelection(nPage);
    }

    EXPORT void wxTreebook_AdvanceSelection(wxTreebook* self, bool bForward)
    {
        self->AdvanceSelection(bForward);
    }

    EXPORT int wxTreebook_GetSelection(wxTreebook* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxTreebook_SetPageText(wxTreebook* self, int nPage, wxString* strText)
    {
        return self->SetPageText(nPage, *strText);
    }

    EXPORT wxString* wxTreebook_GetPageText(wxTreebook* self, int nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT void wxTreebook_SetImageList(wxTreebook* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT wxImageList* wxTreebook_GetImageList(wxTreebook* self)
    {
        return self->GetImageList();
    }

    EXPORT int wxTreebook_GetPageImage(wxTreebook* self, int nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxTreebook_SetPageImage(wxTreebook* self, int nPage, int nImage)
    {
        return self->SetPageImage(nPage, nImage);
    }

    EXPORT bool wxTreebook_DeletePage(wxTreebook* self, int nPage)
    {
        return self->DeletePage(nPage);
    }

    EXPORT bool wxTreebook_RemovePage(wxTreebook* self, int nPage)
    {
        return self->RemovePage(nPage);
    }

    EXPORT bool wxTreebook_DeleteAllPages(wxTreebook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxTreebook_AddPage(wxTreebook* self, wxWindow* pPage, wxString* strText,
                                   bool bSelect, int imageId)
    {
        return self->AddPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxTreebook_InsertPage(wxTreebook* self, int nPage, wxWindow* pPage,
                                      wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxTreebook_InsertSubPage(wxTreebook* self, int nPage, wxWindow* pPage,
                                         wxString* strText, bool bSelect, int imageId)
    {
        return self->InsertSubPage(nPage, pPage, *strText, bSelect, imageId);
    }

    EXPORT bool wxTreebook_AddSubPage(wxTreebook* self, wxWindow* pPage, wxString* strText,
                                      bool bSelect, int imageId)
    {
        return self->AddSubPage(pPage, *strText, bSelect, imageId);
    }

    EXPORT wxWindow* wxTreebook_GetPage(wxTreebook* self, int nPage)
    {
        return self->GetPage(nPage);
    }

    EXPORT int wxTreebook_GetPageParent(wxTreebook* self, int nPage)
    {
        return self->GetPageParent(nPage);
    }

    EXPORT wxTreeCtrl* wxTreebook_GetTreeCtrl(wxTreebook* self)
    {
        return self->GetTreeCtrl();
    }

    EXPORT void wxTreebook_ExpandNode(wxTreebook* self, int nPage, bool expand)
    {
        self->ExpandNode(nPage, expand);
    }

    EXPORT bool wxTreebook_IsNodeExpanded(wxTreebook* self, int nPage)
    {
        return self->IsNodeExpanded(nPage);
    }

    EXPORT int wxTreebook_HitTest(wxTreebook* self, int x, int y, long* flags)
    {
        return self->HitTest(wxPoint(x, y), flags);
    }

    EXPORT bool wxTreebook_CollapseNode(wxTreebook* self, int nPage)
    {
        return self->CollapseNode(nPage);
    }
}
