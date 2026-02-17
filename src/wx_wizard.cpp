#include "wrapper.h"

// wxWizard inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxWizard_Create(wxWindow* parent, int id, wxString* title, wxBitmap* bitmap, int x,
                                 int y, int width, int height, long style)
    {
        wxBitmap bmp = wxNullBitmap;
        if (bitmap)
            bmp = *bitmap;
        return (void*) new wxWizard(parent, id, *title, bmp, wxPoint(x, y), style);
    }

    EXPORT bool wxWizard_RunWizard(wxWizard* self, wxWizardPage* firstPage)
    {
        return self->RunWizard(firstPage);
    }

    EXPORT void* wxWizard_GetCurrentPage(wxWizard* self)
    {
        return (void*) self->GetCurrentPage();
    }

    EXPORT void wxWizard_Chain(void* first, void* second)
    {
        wxWizardPageSimple::Chain((wxWizardPageSimple*) first, (wxWizardPageSimple*) second);
    }

    EXPORT void wxWizard_SetPageSize(wxWizard* self, int width, int height)
    {
        self->SetPageSize(wxSize(width, height));
    }

    EXPORT wxSize* wxWizard_GetPageSize(wxWizard* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetPageSize();
        return text;
    }

    EXPORT void* wxWizardPageSimple_Create(wxWizard* parent, wxWizardPage* prev, wxWizardPage* next,
                                           wxBitmap* bitmap)
    {
        wxBitmapBundle bmp;
        if (bitmap)
            bmp = *bitmap;
        return (void*) new wxWizardPageSimple(parent, prev, next, bmp);
    }

    EXPORT void* wxWizardPageSimple_GetPrev(void* self)
    {
        return (void*) ((wxWizardPageSimple*) self)->GetPrev();
    }

    EXPORT void* wxWizardPageSimple_GetNext(void* self)
    {
        return (void*) ((wxWizardPageSimple*) self)->GetNext();
    }

    EXPORT void wxWizardPageSimple_GetBitmap(void* self, wxBitmap* bitmap)
    {
        *bitmap = ((wxWizardPageSimple*) self)->GetBitmap();
    }

    EXPORT void wxWizardPageSimple_SetPrev(void* self, void* prev)
    {
        ((wxWizardPageSimple*) self)->SetPrev((wxWizardPage*) prev);
    }

    EXPORT void wxWizardPageSimple_SetNext(void* self, void* next)
    {
        ((wxWizardPageSimple*) self)->SetNext((wxWizardPage*) next);
    }

    EXPORT bool wxWizardEvent_GetDirection(wxWizardEvent* self)
    {
        return self->GetDirection();
    }

    EXPORT void* wxWizard_GetPageAreaSizer(wxWizard* self)
    {
        return (void*) self->GetPageAreaSizer();
    }

    EXPORT void wxWizard_SetBorder(wxWizard* self, int border)
    {
        self->SetBorder(border);
    }

    EXPORT void wxWizard_FitToPage(wxWizard* self, wxWizardPage* firstPage)
    {
        self->FitToPage(firstPage);
    }

    EXPORT bool wxWizard_HasNextPage(wxWizard* self, wxWizardPage* page)
    {
        return self->HasNextPage(page);
    }

    EXPORT bool wxWizard_HasPrevPage(wxWizard* self, wxWizardPage* page)
    {
        return self->HasPrevPage(page);
    }

    EXPORT void wxWizard_GetBitmap(wxWizard* self, wxBitmap* bitmap)
    {
        // wxWizard doesn't have GetBitmap directly, use the page bitmap via GetCurrentPage
        wxWizardPage* page = self->GetCurrentPage();
        if (page)
            *bitmap = page->GetBitmap();
    }
}
