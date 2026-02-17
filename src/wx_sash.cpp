#include "wrapper.h"

// wxSashWindow inherits from wxWindow.
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxSashWindow_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                     int style)
    {
        return new wxSashWindow(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxSashWindow_SetSashVisible(wxSashWindow* self, int edge, bool sash)
    {
        self->SetSashVisible((wxSashEdgePosition) edge, sash);
    }

    EXPORT bool wxSashWindow_GetSashVisible(wxSashWindow* self, int edge)
    {
        return self->GetSashVisible((wxSashEdgePosition) edge);
    }

    EXPORT void wxSashWindow_SetSashBorder(wxSashWindow* self, int edge, bool border)
    {
#if WXWIN_COMPATIBILITY_2_6
        self->SetSashBorder((wxSashEdgePosition) edge, border);
#endif
    }

    EXPORT bool wxSashWindow_HasBorder(wxSashWindow* self, int edge)
    {
#if WXWIN_COMPATIBILITY_2_6
        return self->HasBorder((wxSashEdgePosition) edge);
#else
        return false;
#endif
    }

    EXPORT int wxSashWindow_GetEdgeMargin(wxSashWindow* self, int edge)
    {
        return self->GetEdgeMargin((wxSashEdgePosition) edge);
    }

    EXPORT void wxSashWindow_SetDefaultBorderSize(wxSashWindow* self, int width)
    {
        self->SetDefaultBorderSize(width);
    }

    EXPORT int wxSashWindow_GetDefaultBorderSize(wxSashWindow* self)
    {
        return self->GetDefaultBorderSize();
    }

    EXPORT void wxSashWindow_SetExtraBorderSize(wxSashWindow* self, int width)
    {
        self->SetExtraBorderSize(width);
    }

    EXPORT int wxSashWindow_GetExtraBorderSize(wxSashWindow* self)
    {
        return self->GetExtraBorderSize();
    }

    EXPORT void wxSashWindow_SetMinimumSizeX(wxSashWindow* self, int min)
    {
        self->SetMinimumSizeX(min);
    }

    EXPORT void wxSashWindow_SetMinimumSizeY(wxSashWindow* self, int min)
    {
        self->SetMinimumSizeY(min);
    }

    EXPORT int wxSashWindow_GetMinimumSizeX(wxSashWindow* self)
    {
        return self->GetMinimumSizeX();
    }

    EXPORT int wxSashWindow_GetMinimumSizeY(wxSashWindow* self)
    {
        return self->GetMinimumSizeY();
    }

    EXPORT void wxSashWindow_SetMaximumSizeX(wxSashWindow* self, int max)
    {
        self->SetMaximumSizeX(max);
    }

    EXPORT void wxSashWindow_SetMaximumSizeY(wxSashWindow* self, int max)
    {
        self->SetMaximumSizeY(max);
    }

    EXPORT int wxSashWindow_GetMaximumSizeX(wxSashWindow* self)
    {
        return self->GetMaximumSizeX();
    }

    EXPORT int wxSashWindow_GetMaximumSizeY(wxSashWindow* self)
    {
        return self->GetMaximumSizeY();
    }

    EXPORT void* wxSashEvent_Create(int id, int edge)
    {
        return (void*) new wxSashEvent(id, (wxSashEdgePosition) edge);
    }

    EXPORT void wxSashEvent_SetEdge(wxSashEvent* self, int edge)
    {
        self->SetEdge((wxSashEdgePosition) edge);
    }

    EXPORT int wxSashEvent_GetEdge(wxSashEvent* self)
    {
        return (int) self->GetEdge();
    }

    EXPORT void wxSashEvent_SetDragRect(wxSashEvent* self, int x, int y, int width, int height)
    {
        self->SetDragRect(wxRect(x, y, width, height));
    }

    EXPORT wxRect* wxSashEvent_GetDragRect(wxSashEvent* self)
    {
        wxRect* rct = new wxRect();
        *rct = self->GetDragRect();
        return rct;
    }

    EXPORT void wxSashEvent_SetDragStatus(wxSashEvent* self, int status)
    {
        self->SetDragStatus((wxSashDragStatus) status);
    }

    EXPORT int wxSashEvent_GetDragStatus(wxSashEvent* self)
    {
        return (int) self->GetDragStatus();
    }

    EXPORT void* wxSashLayoutWindow_Create(wxWindow* parent, int id, int style)
    {
        return new wxSashLayoutWindow(parent, id, wxDefaultPosition, wxDefaultSize, style);
    }

    EXPORT int wxSashLayoutWindow_GetAlignment(wxSashLayoutWindow* self)
    {
        return (int) self->GetAlignment();
    }

    EXPORT int wxSashLayoutWindow_GetOrientation(wxSashLayoutWindow* self)
    {
        return (int) self->GetOrientation();
    }

    EXPORT void wxSashLayoutWindow_SetAlignment(wxSashLayoutWindow* self, int align)
    {
        self->SetAlignment((wxLayoutAlignment) align);
    }

    EXPORT void wxSashLayoutWindow_SetOrientation(wxSashLayoutWindow* self, int orient)
    {
        self->SetOrientation((wxLayoutOrientation) orient);
    }

    EXPORT void wxSashLayoutWindow_SetDefaultSize(wxSashLayoutWindow* self, int width, int height)
    {
        self->SetDefaultSize(wxSize(width, height));
    }

    EXPORT void* wxQueryLayoutInfoEvent_Create(int id)
    {
        return (void*) new wxQueryLayoutInfoEvent(id);
    }

    EXPORT void wxQueryLayoutInfoEvent_SetRequestedLength(wxQueryLayoutInfoEvent* self, int length)
    {
        self->SetRequestedLength(length);
    }

    EXPORT int wxQueryLayoutInfoEvent_GetRequestedLength(wxQueryLayoutInfoEvent* self)
    {
        return self->GetRequestedLength();
    }

    EXPORT void wxQueryLayoutInfoEvent_SetFlags(wxQueryLayoutInfoEvent* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT int wxQueryLayoutInfoEvent_GetFlags(wxQueryLayoutInfoEvent* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxQueryLayoutInfoEvent_SetSize(wxQueryLayoutInfoEvent* self, int width, int height)
    {
        self->SetSize(wxSize(width, height));
    }

    EXPORT wxSize* wxQueryLayoutInfoEvent_GetSize(wxQueryLayoutInfoEvent* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetSize();
        return text;
    }

    EXPORT void wxQueryLayoutInfoEvent_SetOrientation(wxQueryLayoutInfoEvent* self, int orient)
    {
        self->SetOrientation((wxLayoutOrientation) orient);
    }

    EXPORT int wxQueryLayoutInfoEvent_GetOrientation(wxQueryLayoutInfoEvent* self)
    {
        return (int) self->GetOrientation();
    }

    EXPORT void wxQueryLayoutInfoEvent_SetAlignment(wxQueryLayoutInfoEvent* self, int align)
    {
        self->SetAlignment((wxLayoutAlignment) align);
    }

    EXPORT int wxQueryLayoutInfoEvent_GetAlignment(wxQueryLayoutInfoEvent* self)
    {
        return (int) self->GetAlignment();
    }

    EXPORT void* wxCalculateLayoutEvent_Create(int id)
    {
        return (void*) new wxCalculateLayoutEvent(id);
    }

    EXPORT void wxCalculateLayoutEvent_SetFlags(wxCalculateLayoutEvent* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT int wxCalculateLayoutEvent_GetFlags(wxCalculateLayoutEvent* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxCalculateLayoutEvent_SetRect(wxCalculateLayoutEvent* self, int x, int y, int width,
                                               int height)
    {
        self->SetRect(wxRect(x, y, width, height));
    }

    EXPORT wxRect* wxCalculateLayoutEvent_GetRect(wxCalculateLayoutEvent* self)
    {
        wxRect* rct = new wxRect();
        *rct = self->GetRect();
        return rct;
    }

    EXPORT void* wxLayoutAlgorithm_Create()
    {
        return (void*) new wxLayoutAlgorithm();
    }

    EXPORT void wxLayoutAlgorithm_Delete(wxLayoutAlgorithm* self)
    {
        delete self;
    }

    EXPORT bool wxLayoutAlgorithm_LayoutMDIFrame(wxLayoutAlgorithm* self, wxMDIParentFrame* frame,
                                                 int x, int y, int width, int height, int use)
    {
        wxRect* r = nullptr;
        if (use)
            r = new wxRect(x, y, width, height);

        bool result = self->LayoutMDIFrame(frame, r);

        if (r)
            delete r;
        return result;
    }

    EXPORT bool wxLayoutAlgorithm_LayoutFrame(wxLayoutAlgorithm* self, wxFrame* frame,
                                              wxWindow* mainWindow)
    {
        return self->LayoutFrame(frame, mainWindow);
    }

    EXPORT bool wxLayoutAlgorithm_LayoutWindow(wxLayoutAlgorithm* self, wxFrame* frame,
                                               wxWindow* mainWindow)
    {
        return self->LayoutWindow(frame, mainWindow);
    }
}
