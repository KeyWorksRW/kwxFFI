#include "kwx_wrapper.h"
#include <wx/headerctrl.h>

// wxHeaderCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    // wxHeaderColumn - abstract base, typically accessed through wxHeaderCtrl

    // wxHeaderColumnSimple

    EXPORT void* wxHeaderColumnSimple_Create(wxString* title, int width, int align, int flags)
    {
        return (void*) new wxHeaderColumnSimple(*title, width, static_cast<wxAlignment>(align),
                                                flags);
    }

    EXPORT void* wxHeaderColumnSimple_CreateWithBitmap(wxBitmapBundle* bitmap, int width, int align,
                                                       int flags)
    {
        return (void*) new wxHeaderColumnSimple(*bitmap, width, static_cast<wxAlignment>(align),
                                                flags);
    }

    EXPORT void wxHeaderColumnSimple_Delete(wxHeaderColumnSimple* self)
    {
        delete self;
    }

    EXPORT void wxHeaderColumnSimple_SetTitle(wxHeaderColumnSimple* self, wxString* title)
    {
        self->SetTitle(*title);
    }

    EXPORT wxString* wxHeaderColumnSimple_GetTitle(wxHeaderColumnSimple* self)
    {
        wxString* result = new wxString();
        *result = self->GetTitle();
        return result;
    }

    EXPORT void wxHeaderColumnSimple_SetBitmap(wxHeaderColumnSimple* self, wxBitmapBundle* bitmap)
    {
        self->SetBitmap(*bitmap);
    }

    EXPORT void wxHeaderColumnSimple_SetWidth(wxHeaderColumnSimple* self, int width)
    {
        self->SetWidth(width);
    }

    EXPORT int wxHeaderColumnSimple_GetWidth(wxHeaderColumnSimple* self)
    {
        return self->GetWidth();
    }

    EXPORT void wxHeaderColumnSimple_SetMinWidth(wxHeaderColumnSimple* self, int minWidth)
    {
        self->SetMinWidth(minWidth);
    }

    EXPORT int wxHeaderColumnSimple_GetMinWidth(wxHeaderColumnSimple* self)
    {
        return self->GetMinWidth();
    }

    EXPORT void wxHeaderColumnSimple_SetAlignment(wxHeaderColumnSimple* self, int align)
    {
        self->SetAlignment(static_cast<wxAlignment>(align));
    }

    EXPORT int wxHeaderColumnSimple_GetAlignment(wxHeaderColumnSimple* self)
    {
        return static_cast<int>(self->GetAlignment());
    }

    EXPORT void wxHeaderColumnSimple_SetFlags(wxHeaderColumnSimple* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT int wxHeaderColumnSimple_GetFlags(wxHeaderColumnSimple* self)
    {
        return self->GetFlags();
    }

    EXPORT bool wxHeaderColumnSimple_IsSortKey(wxHeaderColumnSimple* self)
    {
        return self->IsSortKey();
    }

    EXPORT void wxHeaderColumnSimple_SetSortOrder(wxHeaderColumnSimple* self, bool ascending)
    {
        self->SetSortOrder(ascending);
    }

    EXPORT bool wxHeaderColumnSimple_IsSortOrderAscending(wxHeaderColumnSimple* self)
    {
        return self->IsSortOrderAscending();
    }

    // wxHeaderCtrlSimple

    EXPORT void* wxHeaderCtrlSimple_Create(wxWindow* parent, int id, int x, int y, int width,
                                           int height, long style)
    {
        return (void*) new wxHeaderCtrlSimple(parent, id, wxPoint(x, y), wxSize(width, height),
                                              style);
    }

    EXPORT void wxHeaderCtrlSimple_AppendColumn(wxHeaderCtrlSimple* self, wxHeaderColumnSimple* col)
    {
        self->AppendColumn(*col);
    }

    EXPORT void wxHeaderCtrlSimple_InsertColumn(wxHeaderCtrlSimple* self, wxHeaderColumnSimple* col,
                                                unsigned int idx)
    {
        self->InsertColumn(*col, idx);
    }

    EXPORT void wxHeaderCtrlSimple_DeleteColumn(wxHeaderCtrlSimple* self, unsigned int idx)
    {
        self->DeleteColumn(idx);
    }

    EXPORT void wxHeaderCtrlSimple_ShowColumn(wxHeaderCtrlSimple* self, unsigned int idx, bool show)
    {
        self->ShowColumn(idx, show);
    }

    EXPORT void wxHeaderCtrlSimple_HideColumn(wxHeaderCtrlSimple* self, unsigned int idx)
    {
        self->HideColumn(idx);
    }

    EXPORT void wxHeaderCtrlSimple_ShowSortIndicator(wxHeaderCtrlSimple* self, unsigned int idx,
                                                     bool ascending)
    {
        self->ShowSortIndicator(idx, ascending);
    }

    EXPORT void wxHeaderCtrlSimple_RemoveSortIndicator(wxHeaderCtrlSimple* self)
    {
        self->RemoveSortIndicator();
    }

    // General wxHeaderCtrl base methods (work on both)

    EXPORT unsigned int wxHeaderCtrl_GetColumnCount(wxHeaderCtrl* self)
    {
        return self->GetColumnCount();
    }

    EXPORT bool wxHeaderCtrl_IsEmpty(wxHeaderCtrl* self)
    {
        return self->IsEmpty();
    }

    EXPORT void wxHeaderCtrl_UpdateColumn(wxHeaderCtrl* self, unsigned int idx)
    {
        self->UpdateColumn(idx);
    }

    EXPORT void wxHeaderCtrl_SetColumnCount(wxHeaderCtrl* self, unsigned int count)
    {
        self->SetColumnCount(count);
    }

    EXPORT unsigned int wxHeaderCtrl_GetColumnAt(wxHeaderCtrl* self, unsigned int pos)
    {
        return self->GetColumnAt(pos);
    }

    EXPORT unsigned int wxHeaderCtrl_GetColumnPos(wxHeaderCtrl* self, unsigned int idx)
    {
        return self->GetColumnPos(idx);
    }

    EXPORT void wxHeaderCtrl_ResetColumnsOrder(wxHeaderCtrl* self)
    {
        self->ResetColumnsOrder();
    }

    EXPORT void wxHeaderCtrl_MoveColumnInOrderArray(wxHeaderCtrl* self, unsigned int idx,
                                                    unsigned int pos)
    {
        wxArrayInt order = self->GetColumnsOrder();
        wxHeaderCtrl::MoveColumnInOrderArray(order, idx, pos);
        self->SetColumnsOrder(order);
    }

    // Events
    MAKE_EVENT_WRAPPER(EVT_HEADER_CLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_MIDDLE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_MIDDLE_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_SEPARATOR_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_HEADER_BEGIN_RESIZE)
    MAKE_EVENT_WRAPPER(EVT_HEADER_RESIZING)
    MAKE_EVENT_WRAPPER(EVT_HEADER_END_RESIZE)
    MAKE_EVENT_WRAPPER(EVT_HEADER_BEGIN_REORDER)
    MAKE_EVENT_WRAPPER(EVT_HEADER_END_REORDER)
    MAKE_EVENT_WRAPPER(EVT_HEADER_DRAGGING_CANCELLED)
}
