#include "wrapper.h"
#include <wx/dragimag.h>
#include <wx/generic/dragimgg.h>

extern "C"
{
    /*-----------------------------------------------------------------------------
      DragImage
    -----------------------------------------------------------------------------*/
    EXPORT wxDragImage* wxDragImage_Create(wxBitmap* image, int x, int y)
    {
        return new wxDragImage(*image, wxNullCursor);
    }

    EXPORT wxDragImage* wxDragIcon(wxIcon* icon, int x, int y)
    {
        return new wxDragImage(*icon, wxNullCursor);
    }

    EXPORT wxDragImage* wxDragString(wxString* text, int x, int y)
    {
        return new wxDragImage(*text, wxNullCursor);
    }

    EXPORT wxDragImage* wxDragTreeItem(wxTreeCtrl* treeCtrl, wxTreeItemId* id)
    {
        return new wxDragImage(*treeCtrl, *id);
    }

    EXPORT wxDragImage* wxDragListItem(wxListCtrl* listCtrl, long id)
    {
        return new wxDragImage(*listCtrl, id);
    }

    EXPORT wxGenericDragImage* wxGenericDragImage_Create(wxCursor* cursor)
    {
        return new wxGenericDragImage(*cursor);
    }

    EXPORT wxGenericDragImage* wxGenericDragIcon(wxIcon* icon)
    {
        return new wxGenericDragImage(*icon, wxNullCursor);
    }

    EXPORT wxGenericDragImage* wxGenericDragString(wxString* text)
    {
        return new wxGenericDragImage(*text, wxNullCursor);
    }

    EXPORT wxGenericDragImage* wxGenericDragTreeItem(wxTreeCtrl* treeCtrl, wxTreeItemId* id)
    {
        return new wxGenericDragImage(*treeCtrl, *id);
    }

    EXPORT wxGenericDragImage* wxGenericDragListItem(wxListCtrl* listCtrl, long id)
    {
        return new wxGenericDragImage(*listCtrl, id);
    }

    EXPORT void wxDragImage_Delete(wxDragImage* self)
    {
        if (self)
            delete self;
    }

    EXPORT bool wxDragImage_BeginDragFullScreen(wxDragImage* self, int x_pos, int y_pos,
                                                wxWindow* window, bool fullScreen, wxRect* rect)
    {
        return self->BeginDrag(wxPoint(x_pos, y_pos), window, fullScreen, rect);
    }

    EXPORT bool wxDragImage_BeginDrag(wxDragImage* self, int x, int y, wxWindow* window,
                                      wxWindow* boundingWindow)
    {
        return self->BeginDrag(wxPoint(x, y), window, boundingWindow);
    }

    EXPORT bool wxGenericDragImage_DoDrawImage(wxGenericDragImage* self, wxDC* dc, int x, int y)
    {
        return self->DoDrawImage(*dc, wxPoint(x, y));
    }

    EXPORT bool wxDragImage_EndDrag(wxDragImage* self)
    {
        return self->EndDrag();
    }

    EXPORT wxRect* wxGenericDragImage_GetImageRect(wxGenericDragImage* self, int x_pos, int y_pos)
    {
        wxRect* r = new wxRect();
        *r = self->GetImageRect(wxPoint(x_pos, y_pos));
        return r;
    }

    EXPORT bool wxDragImage_Hide(wxDragImage* self)
    {
        return self->Hide();
    }

    EXPORT bool wxDragImage_Move(wxDragImage* self, int x, int y)
    {
        return self->Move(wxPoint(x, y));
    }

    EXPORT bool wxDragImage_Show(wxDragImage* self)
    {
        return self->Show();
    }

    EXPORT bool wxGenericDragImage_UpdateBackingFromWindow(wxGenericDragImage* self, wxDC* windowDC,
                                                           wxMemoryDC* destDC, int x, int y,
                                                           int width, int height, int xdest,
                                                           int ydest, int destWidth, int destHeight)
    {
        return self->UpdateBackingFromWindow(*windowDC, *destDC, wxRect(x, y, width, height),
                                             wxRect(xdest, ydest, destWidth, destHeight));
    }
}
