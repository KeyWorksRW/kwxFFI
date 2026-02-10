#include "wrapper.h"

extern "C"
{
    EXPORT void* wxLayoutConstraints_left(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->left);
    }

    EXPORT void* wxLayoutConstraints_top(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->top);
    }

    EXPORT void* wxLayoutConstraints_right(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->right);
    }

    EXPORT void* wxLayoutConstraints_bottom(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->bottom);
    }

    EXPORT void* wxLayoutConstraints_width(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->width);
    }

    EXPORT void* wxLayoutConstraints_height(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->height);
    }

    EXPORT void* wxLayoutConstraints_centreX(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->centreX);
    }

    EXPORT void* wxLayoutConstraints_centreY(void* self)
    {
        return (void*) (&((wxLayoutConstraints*) self)->centreY);
    }

    EXPORT void* wxLayoutConstraints_Create()
    {
        return (void*) new wxLayoutConstraints();
    }

    EXPORT void wxIndividualLayoutConstraint_Set(void* self, int rel, wxWindowBase* otherW,
                                                 int otherE, int val, int marg)
    {
        ((wxIndividualLayoutConstraint*) self)
            ->Set((wxRelationship) rel, otherW, (wxEdge) otherE, val, marg);
    }

    EXPORT void wxIndividualLayoutConstraint_LeftOf(void* self, wxWindowBase* sibling, int marg)
    {
        ((wxIndividualLayoutConstraint*) self)->LeftOf(sibling, (wxEdge) marg);
    }

    EXPORT void wxIndividualLayoutConstraint_RightOf(void* self, wxWindowBase* sibling, int marg)
    {
        ((wxIndividualLayoutConstraint*) self)->RightOf(sibling, (wxEdge) marg);
    }

    EXPORT void wxIndividualLayoutConstraint_Above(void* self, wxWindow* sibling, int marg)
    {
        ((wxIndividualLayoutConstraint*) self)->Above(sibling, marg);
    }

    EXPORT void wxIndividualLayoutConstraint_Below(void* self, wxWindow* sibling, int marg)
    {
        ((wxIndividualLayoutConstraint*) self)->Below(sibling, marg);
    }

    EXPORT void wxIndividualLayoutConstraint_SameAs(void* self, wxWindowBase* otherW, int edge,
                                                    int marg)
    {
        ((wxIndividualLayoutConstraint*) self)->SameAs(otherW, (wxEdge) edge, (wxEdge) marg);
    }

    EXPORT void wxIndividualLayoutConstraint_PercentOf(void* self, wxWindowBase* otherW, int which,
                                                       int per)
    {
        ((wxIndividualLayoutConstraint*) self)->PercentOf(otherW, (wxEdge) which, per);
    }

    EXPORT void wxIndividualLayoutConstraint_Absolute(void* self, int val)
    {
        ((wxIndividualLayoutConstraint*) self)->Absolute(val);
    }

    EXPORT void wxIndividualLayoutConstraint_Unconstrained(void* self)
    {
        ((wxIndividualLayoutConstraint*) self)->Unconstrained();
    }

    EXPORT void wxIndividualLayoutConstraint_AsIs(void* self)
    {
        ((wxIndividualLayoutConstraint*) self)->AsIs();
    }

    EXPORT void* wxIndividualLayoutConstraint_GetOtherWindow(void* self)
    {
        return (void*) ((wxIndividualLayoutConstraint*) self)->GetOtherWindow();
    }

    EXPORT int wxIndividualLayoutConstraint_GetMyEdge(wxIndividualLayoutConstraint* self)
    {
        return (int) self->GetMyEdge();
    }

    EXPORT void wxIndividualLayoutConstraint_SetEdge(void* self, int which)
    {
        ((wxIndividualLayoutConstraint*) self)->SetEdge((wxEdge) which);
    }

    EXPORT void wxIndividualLayoutConstraint_SetValue(void* self, int value)
    {
        ((wxIndividualLayoutConstraint*) self)->SetValue(value);
    }

    EXPORT int wxIndividualLayoutConstraint_GetMargin(void* self)
    {
        return ((wxIndividualLayoutConstraint*) self)->GetMargin();
    }

    EXPORT void wxIndividualLayoutConstraint_SetMargin(void* self, int margin)
    {
        ((wxIndividualLayoutConstraint*) self)->SetMargin(margin);
    }

    EXPORT int wxIndividualLayoutConstraint_GetValue(void* self)
    {
        return ((wxIndividualLayoutConstraint*) self)->GetValue();
    }

    EXPORT int wxIndividualLayoutConstraint_GetPercent(void* self)
    {
        return ((wxIndividualLayoutConstraint*) self)->GetPercent();
    }

    EXPORT int wxIndividualLayoutConstraint_GetOtherEdge(void* self)
    {
        return ((wxIndividualLayoutConstraint*) self)->GetOtherEdge();
    }

    EXPORT bool wxIndividualLayoutConstraint_GetDone(wxIndividualLayoutConstraint* self)
    {
        return self->GetDone();
    }

    EXPORT void wxIndividualLayoutConstraint_SetDone(void* self, bool done)
    {
        ((wxIndividualLayoutConstraint*) self)->SetDone(done);
    }

    EXPORT int wxIndividualLayoutConstraint_GetRelationship(void* self)
    {
        return ((wxIndividualLayoutConstraint*) self)->GetRelationship();
    }

    EXPORT void wxIndividualLayoutConstraint_SetRelationship(void* self, int relationship)
    {
        ((wxIndividualLayoutConstraint*) self)->SetRelationship((wxRelationship) relationship);
    }

    EXPORT bool wxIndividualLayoutConstraint_ResetIfWin(wxIndividualLayoutConstraint* self,
                                                        wxWindowBase* otherW)
    {
        return self->ResetIfWin(otherW);
    }

    EXPORT bool wxIndividualLayoutConstraint_SatisfyConstraint(wxIndividualLayoutConstraint* self,
                                                               void* constraints, wxWindowBase* win)
    {
        return self->SatisfyConstraint((wxLayoutConstraints*) constraints, win);
    }

    EXPORT int wxIndividualLayoutConstraint_GetEdge(void* self, int which, wxWindowBase* thisWin,
                                                    wxWindowBase* other)
    {
        return ((wxIndividualLayoutConstraint*) self)->GetEdge((wxEdge) which, thisWin, other);
    }
}
