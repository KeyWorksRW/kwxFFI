#include "wrapper.h"
#include <wx/hyperlink.h>

extern "C"
{
    EXPORT wxHyperlinkCtrl* wxHyperlinkCtrl_Create(wxWindow* parent, int id, const wxString& label,
                                                   const wxString& url, int x, int y, int width, int height,
                                                   int style)
    {
        return new wxHyperlinkCtrl(parent, id, label, url, wxPoint(x, y), wxSize(width, height), style);
    }

// BUGBUG: [Randalphwa - 10-13-2024] C functions cannot return wxColour which is a class.
#if 0
    EXPORT wxColour wxHyperlinkCtrl_GetHoverColour(wxHyperlinkCtrl* self)
    {
        return self->GetHoverColour();
    }

    EXPORT wxColour wxHyperlinkCtrl_GetNormalColour(wxHyperlinkCtrl* self)
    {
        return self->GetNormalColour();
    }

    EXPORT wxString wxHyperlinkCtrl_GetURL(wxHyperlinkCtrl* self)
    {
        return self->GetURL();
    }

    EXPORT bool wxHyperlinkCtrl_GetVisited(wxHyperlinkCtrl* self)
    {
        return self->GetVisited();
    }

    EXPORT wxColour wxHyperlinkCtrl_GetVisitedColour(wxHyperlinkCtrl* self)
    {
        return self->GetVisitedColour();
    }
#endif
    EXPORT void wxHyperlinkCtrl_SetHoverColour(wxHyperlinkCtrl* self, const wxColour& colour)
    {
        self->SetHoverColour(colour);
    }

    EXPORT void wxHyperlinkCtrl_SetNormalColour(wxHyperlinkCtrl* self, const wxColour& colour)
    {
        self->SetNormalColour(colour);
    }

    EXPORT void wxHyperlinkCtrl_SetURL(wxHyperlinkCtrl* self, const wxString& url)
    {
        self->SetURL(url);
    }

    EXPORT void wxHyperlinkCtrl_SetVisited(wxHyperlinkCtrl* self, bool visited)
    {
        self->SetVisited(visited);
    }

    EXPORT void wxHyperlinkCtrl_SetVisitedColour(wxHyperlinkCtrl* self, const wxColour& colour)
    {
        self->SetVisitedColour(colour);
    }
}
