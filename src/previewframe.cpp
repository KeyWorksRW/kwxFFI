#include "wrapper.h"
#include <wx/print.h>
#include <wx/wx.h>

/*-----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/
extern "C"
{
    /*-----------------------------------------------------------------------------
      PreviewFrame
    -----------------------------------------------------------------------------*/
    EXPORT wxPreviewFrame* wxPreviewFrame_Create(wxPrintPreview* preview, wxFrame* parent,
                                                 wxString* title, int x, int y, int width, int height,
                                                 int style, wxString* name)
    {
        return new wxPreviewFrame(preview, parent, *title, wxPoint(x, y), wxSize(width, height), style,
                                  *name);
    }

    EXPORT void wxPreviewFrame_Delete(wxPreviewFrame* self)
    {
        if (self)
            delete self;
    }

    EXPORT void wxPreviewFrame_Initialize(wxPreviewFrame* self)
    {
        self->Initialize();
    }
}
