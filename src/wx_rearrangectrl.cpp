#include "wrapper.h"

extern "C"
{
    EXPORT wxRearrangeCtrl* wxRearrangeCtrl_Create(wxWindow* parent, int id, int x, int y, int w,
                                                   int h, wxArrayInt* order, wxArrayString* items,
                                                   int style)
    {
        return new wxRearrangeCtrl(parent, id, wxPoint(x, y), wxSize(w, h), *order, *items, style);
    }

    EXPORT wxArrayInt* wxRearrangeCtrl_GetCurrentOrder(wxRearrangeCtrl* self)
    {
        wxArrayInt* result = new wxArrayInt();
        *result = self->GetList()->GetCurrentOrder();
        return result;
    }

    EXPORT wxRearrangeList* wxRearrangeCtrl_GetList(wxRearrangeCtrl* self)
    {
        return self->GetList();
    }

    EXPORT bool wxRearrangeCtrl_CanMoveCurrentUp(wxRearrangeCtrl* self)
    {
        return self->GetList()->CanMoveCurrentUp();
    }

    EXPORT bool wxRearrangeCtrl_CanMoveCurrentDown(wxRearrangeCtrl* self)
    {
        return self->GetList()->CanMoveCurrentDown();
    }

    EXPORT bool wxRearrangeCtrl_MoveCurrentUp(wxRearrangeCtrl* self)
    {
        return self->GetList()->MoveCurrentUp();
    }

    EXPORT bool wxRearrangeCtrl_MoveCurrentDown(wxRearrangeCtrl* self)
    {
        return self->GetList()->MoveCurrentDown();
    }
}
