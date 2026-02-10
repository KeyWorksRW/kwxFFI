#include "wrapper.h"

extern "C"
{
    // ============================================================================
    // wxDocParentFrame - Document view parent frame
    // ============================================================================

    EXPORT wxDocParentFrame* wxDocParentFrame_Create(wxDocManager* manager, wxFrame* parent, int id,
                                                     wxString* title, int x, int y, int width, int height,
                                                     int style)
    {
        return new wxDocParentFrame(manager, parent, id, *title, wxPoint(x, y), wxSize(width, height),
                                    style);
    }

    EXPORT wxDocManager* wxDocParentFrame_GetDocumentManager(wxDocParentFrame* self)
    {
        return self->GetDocumentManager();
    }

    // ============================================================================
    // wxDocChildFrame - Document view child frame
    // ============================================================================

    EXPORT wxDocChildFrame* wxDocChildFrame_Create(wxDocument* doc, wxView* view, wxFrame* parent,
                                                   int id, wxString* title, int x, int y, int width,
                                                   int height, int style)
    {
        return new wxDocChildFrame(doc, view, parent, id, *title, wxPoint(x, y), wxSize(width, height),
                                   style);
    }

    EXPORT wxDocument* wxDocChildFrame_GetDocument(wxDocChildFrame* self)
    {
        return self->GetDocument();
    }

    EXPORT wxView* wxDocChildFrame_GetView(wxDocChildFrame* self)
    {
        return self->GetView();
    }

    EXPORT void wxDocChildFrame_SetDocument(wxDocChildFrame* self, wxDocument* doc)
    {
        self->SetDocument(doc);
    }

    EXPORT void wxDocChildFrame_SetView(wxDocChildFrame* self, wxView* view)
    {
        self->SetView(view);
    }

    // ============================================================================
    // wxDocMDIParentFrame - MDI document parent frame
    // ============================================================================

    EXPORT wxDocMDIParentFrame* wxDocMDIParentFrame_Create(wxDocManager* manager, wxFrame* parent,
                                                           int id, wxString* title, int x, int y,
                                                           int width, int height, int style)
    {
        return new wxDocMDIParentFrame(manager, parent, id, *title, wxPoint(x, y), wxSize(width, height),
                                       style);
    }

    EXPORT wxDocManager* wxDocMDIParentFrame_GetDocumentManager(wxDocMDIParentFrame* self)
    {
        return self->GetDocumentManager();
    }

    // ============================================================================
    // wxDocMDIChildFrame - MDI document child frame
    // ============================================================================

    EXPORT wxDocMDIChildFrame* wxDocMDIChildFrame_Create(wxDocument* doc, wxView* view,
                                                         wxMDIParentFrame* parent, int id,
                                                         wxString* title, int x, int y, int width,
                                                         int height, int style)
    {
        return new wxDocMDIChildFrame(doc, view, parent, id, *title, wxPoint(x, y), wxSize(width, height),
                                      style);
    }

    EXPORT wxDocument* wxDocMDIChildFrame_GetDocument(wxDocMDIChildFrame* self)
    {
        return self->GetDocument();
    }

    EXPORT wxView* wxDocMDIChildFrame_GetView(wxDocMDIChildFrame* self)
    {
        return self->GetView();
    }

    EXPORT void wxDocMDIChildFrame_SetDocument(wxDocMDIChildFrame* self, wxDocument* doc)
    {
        self->SetDocument(doc);
    }

    EXPORT void wxDocMDIChildFrame_SetView(wxDocMDIChildFrame* self, wxView* view)
    {
        self->SetView(view);
    }
}
