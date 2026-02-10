#include "wrapper.h"

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

    EXPORT void wxWizard_Chain(void* f, void* s)
    {
        wxWizardPageSimple::Chain((wxWizardPageSimple*) f, (wxWizardPageSimple*) s);
    }

    EXPORT void wxWizard_SetPageSize(wxWizard* self, int w, int h)
    {
        self->SetPageSize(wxSize(w, h));
    }

    EXPORT wxSize* wxWizard_GetPageSize(wxWizard* self)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetPageSize();
        return sz;
    }

    EXPORT void* wxWizardPageSimple_Create(wxWizard* _prt, wxWizardPage* prev, wxWizardPage* next,
                                           wxBitmap* bitmap)
    {
        wxBitmapBundle bmp;
        if (bitmap)
            bmp = *bitmap;
        return (void*) new wxWizardPageSimple(_prt, prev, next, bmp);
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
}
