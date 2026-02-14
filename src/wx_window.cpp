#include "wrapper.h"
#include <wx/tooltip.h>

extern "C"
{
    EXPORT void* wxWindow_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                 int style)
    {
        return (void*) new wxWindow(parent, (wxWindowID) id, wxPoint(x, y), wxSize(width, height),
                                    (long) style);
    }

    EXPORT bool wxWindow_Close(wxWindow* self, bool force)
    {
        return self->Close(force);
    }

    EXPORT bool wxWindow_Destroy(wxWindow* self)
    {
        return self->Destroy();
    }

    EXPORT void wxWindow_ClearBackground(wxWindow* self)
    {
        self->ClearBackground();
    }

    EXPORT void wxWindow_Fit(wxWindow* self)
    {
        self->Fit();
    }

    EXPORT void wxWindow_DestroyChildren(wxWindow* self)
    {
        self->DestroyChildren();
    }

    EXPORT bool wxWindow_IsBeingDeleted(wxWindow* self)
    {
        return self->IsBeingDeleted();
    }

    EXPORT void wxWindow_SetLabel(wxWindow* self, wxString* label)
    {
        self->SetLabel(*label);
    }

    EXPORT wxString* wxWindow_GetLabel(wxWindow* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT bool wxWindow_GetLabelEmpty(wxWindow* self)
    {
        return self->GetLabel().IsEmpty();
    }

    EXPORT void wxWindow_SetName(wxWindow* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxWindow_GetName(wxWindow* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxWindow_SetId(wxWindow* self, int id)
    {
        self->SetId(id);
    }

    EXPORT int wxWindow_GetId(wxWindow* self)
    {
        return self->GetId();
    }

    EXPORT void wxWindow_SetSize(wxWindow* self, int x, int y, int width, int height, int sizeFlags)
    {
        self->SetSize(x, y, width, height, sizeFlags);
    }

    EXPORT void wxWindow_Move(wxWindow* self, int x, int y, int flags)
    {
        self->Move(x, y, flags);
    }

    EXPORT void wxWindow_Raise(wxWindow* self)
    {
        self->Raise();
    }

    EXPORT void wxWindow_Lower(wxWindow* self)
    {
        self->Lower();
    }

    EXPORT void wxWindow_SetClientSize(wxWindow* self, int width, int height)
    {
        self->SetClientSize(width, height);
    }

    EXPORT wxPoint* wxWindow_GetPosition(wxWindow* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT wxSize* wxWindow_GetSize(wxWindow* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetSize();
        return text;
    }

    EXPORT wxRect* wxWindow_GetRect(wxWindow* self)
    {
        wxRect* rct = new wxRect();
        *rct = self->GetRect();
        return rct;
    }

    EXPORT wxSize* wxWindow_GetClientSize(wxWindow* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetClientSize();
        return text;
    }

    EXPORT wxSize* wxWindow_GetBestSize(wxWindow* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetBestSize();
        return text;
    }

    EXPORT void wxWindow_Center(wxWindow* self, int direction)
    {
        self->Center(direction);
    }

    EXPORT void wxWindow_CenterOnParent(wxWindow* self, int dir)
    {
        self->CenterOnParent(dir);
    }

    EXPORT void wxWindow_SetSizeHints(wxWindow* self, int minW, int minH, int maxW, int maxH,
                                      int incW, int incH)
    {
        self->SetSizeHints(minW, minH, maxW, maxH, incW, incH);
    }

    EXPORT int wxWindow_GetMinWidth(wxWindow* self)
    {
        return self->GetMinWidth();
    }

    EXPORT int wxWindow_GetMinHeight(wxWindow* self)
    {
        return self->GetMinHeight();
    }

    EXPORT int wxWindow_GetMaxWidth(wxWindow* self)
    {
        return self->GetMaxWidth();
    }

    EXPORT int wxWindow_GetMaxHeight(wxWindow* self)
    {
        return self->GetMaxHeight();
    }

    EXPORT bool wxWindow_Show(wxWindow* self)
    {
        return self->Show();
    }

    EXPORT bool wxWindow_Hide(wxWindow* self)
    {
        return self->Hide();
    }

    EXPORT bool wxWindow_Enable(wxWindow* self)
    {
        return self->Enable();
    }

    EXPORT bool wxWindow_Disable(wxWindow* self)
    {
        return self->Disable();
    }

    EXPORT bool wxWindow_IsShown(wxWindow* self)
    {
        return self->IsShown();
    }

    EXPORT bool wxWindow_IsEnabled(wxWindow* self)
    {
        return self->IsEnabled();
    }

    EXPORT void wxWindow_SetWindowStyleFlag(wxWindow* self, long style)
    {
        self->SetWindowStyleFlag(style);
    }

    EXPORT int wxWindow_GetWindowStyleFlag(wxWindow* self)
    {
        return (int) self->GetWindowStyleFlag();
    }

    EXPORT bool wxWindow_HasFlag(wxWindow* self, int flag)
    {
        return self->HasFlag(flag);
    }

    EXPORT void wxWindow_SetExtraStyle(wxWindow* self, long exStyle)
    {
        self->SetExtraStyle(exStyle);
    }

    // Obsolete
    // EWXWEXPORT(void,wxWindow_MakeModal)(wxWindow* self,bool modal)

    EXPORT bool wxWindow_HasFocus(wxWindow* self)
    {
        return self->HasFocus();
    }

    EXPORT void wxWindow_SetFocus(wxWindow* self)
    {
        self->SetFocus();
    }

    EXPORT void* wxWindow_FindFocus(wxWindow* self)
    {
        return (void*) self->FindFocus();
    }

    EXPORT int wxWindow_GetChildren(wxWindow* self, void* result, int count)
    {
        if (result && (unsigned int) count == self->GetChildren().GetCount())
        {
            unsigned int i = 0;
            wxWindowList::compatibility_iterator node = self->GetChildren().GetFirst();
            while (node)
            {
                ((void**) result)[i++] = (void*) (node->GetData());
                node = node->GetNext();
            }

            return i;
        }
        else
            return self->GetChildren().GetCount();
    }

    EXPORT void* wxWindow_GetParent(wxWindow* self)
    {
        return (void*) self->GetParent();
    }

    EXPORT bool wxWindow_IsTopLevel(wxWindow* self)
    {
        return self->IsTopLevel();
    }

    EXPORT void* wxWindow_FindWindow(wxWindow* self, wxString* name)
    {
        return (void*) self->FindWindow(*name);
    }

    EXPORT void wxWindow_AddChild(wxWindow* self, wxWindowBase* child)
    {
        self->AddChild(child);
    }

    EXPORT void wxWindow_RemoveChild(wxWindow* self, wxWindowBase* child)
    {
        self->RemoveChild(child);
    }

    EXPORT void* wxWindow_GetEventHandler(wxWindow* self)
    {
        return (void*) self->GetEventHandler();
    }

    EXPORT void wxWindow_PushEventHandler(wxWindow* self, wxEvtHandler* handler)
    {
        self->PushEventHandler(handler);
    }

    EXPORT void* wxWindow_PopEventHandler(wxWindow* self, bool deleteHandler)
    {
        return (void*) self->PopEventHandler(deleteHandler);
    }

    EXPORT void wxWindow_SetValidator(wxWindow* self, void* validator)
    {
        self->SetValidator(*((wxValidator*) validator));
    }

    EXPORT void* wxWindow_GetValidator(wxWindow* self)
    {
        return (void*) self->GetValidator();
    }

    EXPORT void wxWindow_SetClientData(wxWindow* self, void* data)
    {
        self->SetClientData(data);
    }

    EXPORT void* wxWindow_GetClientData(wxWindow* self)
    {
        return (void*) self->GetClientData();
    }

    EXPORT bool wxWindow_Validate(wxWindow* self)
    {
        return self->Validate();
    }

    EXPORT bool wxWindow_TransferDataToWindow(wxWindow* self)
    {
        return self->TransferDataToWindow();
    }

    EXPORT bool wxWindow_TransferDataFromWindow(wxWindow* self)
    {
        return self->TransferDataFromWindow();
    }

    EXPORT void wxWindow_InitDialog(wxWindow* self)
    {
        self->InitDialog();
    }

    EXPORT void wxWindow_SetAcceleratorTable(wxWindow* self, void* accel)
    {
        self->SetAcceleratorTable(*((wxAcceleratorTable*) accel));
    }

    EXPORT wxPoint* wxWindow_ConvertPixelsToDialog(wxWindow* self, int x, int y)
    {
        const wxPoint pos(x, y);
        wxPoint* pt = new wxPoint();
        *pt = self->ConvertPixelsToDialog(pos);
        return pt;
    }

    EXPORT wxPoint* wxWindow_ConvertDialogToPixels(wxWindow* self, int x, int y)
    {
        const wxPoint pos(x, y);
        wxPoint* pt = new wxPoint();
        *pt = self->ConvertDialogToPixels(pos);
        return pt;
    }

    EXPORT void wxWindow_WarpPointer(wxWindow* self, int x, int y)
    {
        self->WarpPointer(x, y);
    }

    EXPORT void wxWindow_CaptureMouse(wxWindow* self)
    {
        self->CaptureMouse();
    }

    EXPORT void wxWindow_ReleaseMouse(wxWindow* self)
    {
        self->ReleaseMouse();
    }

    EXPORT void wxWindow_Refresh(wxWindow* self, bool eraseBackground)
    {
        self->Refresh(eraseBackground, (const wxRect*) nullptr);
    }

    EXPORT void wxWindow_RefreshRect(wxWindow* self, bool eraseBackground, int x, int y, int width,
                                     int height)
    {
        const wxRect rect(x, y, width, height);
        self->Refresh(eraseBackground, &rect);
    }

    EXPORT void wxWindow_PrepareDC(wxWindow* self, wxDC* dc)
    {
        self->PrepareDC(*dc);
    }

    EXPORT void* wxWindow_GetUpdateRegion(wxWindow* self)
    {
        return (void*) (&self->GetUpdateRegion());
    }

    EXPORT bool wxWindow_IsExposed(wxWindow* self, int x, int y, int width, int height)
    {
        return self->IsExposed(x, y, width, height);
    }

    EXPORT bool wxWindow_SetBackgroundColour(wxWindow* self, wxColour* colour)
    {
        return self->SetBackgroundColour(*colour);
    }

    EXPORT void wxWindow_SetForegroundColour(wxWindow* self, wxColour* colour)
    {
        self->SetForegroundColour(*colour);
    }

    EXPORT void wxWindow_GetBackgroundColour(wxWindow* self, wxColour* colour)
    {
        *colour = self->GetBackgroundColour();
    }

    EXPORT void wxWindow_GetForegroundColour(wxWindow* self, wxColour* colour)
    {
        *colour = self->GetForegroundColour();
    }

    EXPORT void wxWindow_SetCursor(wxWindow* self, wxCursor* cursor)
    {
        self->SetCursor(*cursor);
    }

    EXPORT wxCursor* wxWindow_GetCursor(wxWindow* self)
    {
        wxCursor* cur = new wxCursor();
        *cur = self->GetCursor();
        return cur;
    }

    EXPORT void wxWindow_SetFont(wxWindow* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxWindow_GetFont(wxWindow* self, wxFont* font)
    {
        *font = self->GetFont();
    }

    EXPORT void wxWindow_SetCaret(wxWindow* self, wxCaret* caret)
    {
        self->SetCaret(caret);
    }

    EXPORT wxCaret* wxWindow_GetCaret(wxWindow* self)
    {
        return self->GetCaret();
    }

    EXPORT int wxWindow_GetCharHeight(wxWindow* self)
    {
        return self->GetCharHeight();
    }

    EXPORT int wxWindow_GetCharWidth(wxWindow* self)
    {
        return self->GetCharWidth();
    }

    EXPORT void wxWindow_GetTextExtent(wxWindow* self, wxString* string, int* x, int* y,
                                       int* descent, int* externalLeading, wxFont* theFont)
    {
        self->GetTextExtent(*string, x, y, descent, externalLeading, theFont);
    }

    EXPORT wxPoint* wxWindow_ScreenToClient(wxWindow* self, int x, int y)
    {
        const wxPoint pos(x, y);
        wxPoint* pt = new wxPoint();
        *pt = self->ScreenToClient(pos);
        return pt;
    }

    EXPORT void wxWindow_Update(wxWindow* self)
    {
        self->Update();
    }

    EXPORT void wxWindow_UpdateWindowUI(wxWindow* self, long flags)
    {
        self->UpdateWindowUI(flags);
    }

    EXPORT bool wxWindow_PopupMenu(wxWindow* self, wxMenu* menu, int x, int y)
    {
        return self->PopupMenu(menu, x, y);
    }

    EXPORT void wxWindow_SetScrollPos(wxWindow* self, int orient, int pos, bool refresh)
    {
        self->SetScrollPos(orient, pos, refresh);
    }

    EXPORT int wxWindow_GetScrollPos(wxWindow* self, int orient)
    {
        return self->GetScrollPos(orient);
    }

    EXPORT int wxWindow_GetScrollThumb(wxWindow* self, int orient)
    {
        return self->GetScrollThumb(orient);
    }

    EXPORT int wxWindow_GetScrollRange(wxWindow* self, int orient)
    {
        return self->GetScrollRange(orient);
    }

    EXPORT void wxWindow_ScrollWindow(wxWindow* self, int dx, int dy)
    {
        self->ScrollWindow(dx, dy, (const wxRect*) nullptr);
    }

    EXPORT void wxWindow_ScrollWindowRect(wxWindow* self, int dx, int dy, int x, int y, int width,
                                          int height)
    {
        const wxRect rect(x, y, width, height);
        self->ScrollWindow(dx, dy, &rect);
    }

    EXPORT void wxWindow_SetToolTip(wxWindow* self, wxString* tip)
    {
        self->SetToolTip(*tip);
    }

    EXPORT wxString* wxWindow_GetToolTip(wxWindow* self)
    {
        wxToolTip* tip = self->GetToolTip();

        if (tip)
        {
            wxString* result = new wxString();
            *result = tip->GetTip();
            return result;
        }
        return nullptr;
    }

    EXPORT void wxWindow_SetDropTarget(wxWindow* self, void* dropTarget)
    {
        self->SetDropTarget((wxDropTarget*) dropTarget);
    }

    EXPORT void* wxWindow_GetDropTarget(wxWindow* self)
    {
        return (void*) self->GetDropTarget();
    }

    EXPORT void wxWindow_SetConstraints(wxWindow* self, void* constraints)
    {
        self->SetConstraints((wxLayoutConstraints*) constraints);
    }

    EXPORT void* wxWindow_GetConstraints(wxWindow* self)
    {
        return (void*) self->GetConstraints();
    }

    EXPORT void wxWindow_SetAutoLayout(wxWindow* self, bool autoLayout)
    {
        self->SetAutoLayout(autoLayout);
    }

    EXPORT int wxWindow_GetAutoLayout(wxWindow* self)
    {
        return (int) self->GetAutoLayout();
    }

    EXPORT void wxWindow_Layout(wxWindow* self)
    {
        self->Layout();
    }

    EXPORT void wxWindow_UnsetConstraints(wxWindow* self, void* constraints)
    {
        self->UnsetConstraints((wxLayoutConstraints*) constraints);
    }

    EXPORT void* wxWindow_GetConstraintsInvolvedIn(wxWindow* self)
    {
        return (void*) self->GetConstraintsInvolvedIn();
    }

    EXPORT void wxWindow_AddConstraintReference(wxWindow* self, wxWindowBase* otherWin)
    {
        self->AddConstraintReference(otherWin);
    }

    EXPORT void wxWindow_RemoveConstraintReference(wxWindow* self, wxWindowBase* otherWin)
    {
        self->RemoveConstraintReference(otherWin);
    }

    EXPORT void wxWindow_DeleteRelatedConstraints(wxWindow* self)
    {
        self->DeleteRelatedConstraints();
    }

    EXPORT void wxWindow_ResetConstraints(wxWindow* self)
    {
        self->ResetConstraints();
    }

    EXPORT void wxWindow_SetConstraintSizes(wxWindow* self, bool recurse)
    {
        self->SetConstraintSizes(recurse);
    }

    EXPORT int wxWindow_LayoutPhase1(wxWindow* self, int* noChanges)
    {
        return (int) self->LayoutPhase1(noChanges);
    }

    EXPORT int wxWindow_LayoutPhase2(wxWindow* self, int* noChanges)
    {
        return (int) self->LayoutPhase2(noChanges);
    }

    EXPORT int wxWindow_DoPhase(wxWindow* self, int phase)
    {
        return (int) self->DoPhase(phase);
    }

    EXPORT void wxWindow_SetSizeConstraint(wxWindow* self, int x, int y, int width, int height)
    {
        self->SetSizeConstraint(x, y, width, height);
    }

    EXPORT void wxWindow_MoveConstraint(wxWindow* self, int x, int y)
    {
        self->MoveConstraint(x, y);
    }

    EXPORT void wxWindow_GetSizeConstraint(wxWindow* self, int* width, int* height)
    {
        self->GetSizeConstraint(width, height);
    }

    EXPORT void wxWindow_GetClientSizeConstraint(wxWindow* self, int* width, int* height)
    {
        self->GetClientSizeConstraint(width, height);
    }

    EXPORT void wxWindow_GetPositionConstraint(wxWindow* self, int* x, int* y)
    {
        self->GetPositionConstraint(x, y);
    }

    EXPORT void wxWindow_SetSizer(wxWindow* self, wxSizer* sizer, bool deleteOld)
    {
        self->SetSizer(sizer, deleteOld);
    }

    EXPORT void wxWindow_SetSizerAndFit(wxWindow* self, wxSizer* sizer, bool deleteOld)
    {
        self->SetSizerAndFit(sizer, deleteOld);
    }

    EXPORT void* wxWindow_GetSizer(wxWindow* self)
    {
        return (void*) self->GetSizer();
    }

    EXPORT void* wxWindow_GetHandle(wxWindow* self)
    {
        return (void*) self->GetHandle();
    }

    EXPORT void wxWindow_SetScrollbar(wxWindow* self, int orient, int pos, int thumbVisible,
                                      int range, bool refresh)
    {
        self->SetScrollbar(orient, pos, thumbVisible, range, refresh);
    }

    EXPORT bool wxWindow_Reparent(wxWindow* self, wxWindow* parent)
    {
        return self->Reparent(parent);
    }

    EXPORT wxSize* wxWindow_GetEffectiveMinSize(wxWindow* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetEffectiveMinSize();
        return text;
    }

    EXPORT void wxWindow_Freeze(wxWindow* self)
    {
        self->Freeze();
    }

    EXPORT void wxWindow_Thaw(wxWindow* self)
    {
        self->Thaw();
    }

    EXPORT wxPoint* wxWindow_ClientToScreen(wxWindow* self, int x, int y)
    {
        const wxPoint pos(x, y);
        wxPoint* pt = new wxPoint();
        *pt = self->ClientToScreen(pos);
        return pt;
    }

    EXPORT void wxWindow_FitInside(wxWindow* self)
    {
        self->FitInside();
    }

    EXPORT void wxWindow_SetVirtualSize(wxWindow* self, int width, int height)
    {
        self->SetVirtualSize(width, height);
    }

    EXPORT wxSize* wxWindow_GetVirtualSize(wxWindow* self)
    {
        wxSize* text = new wxSize();
        *text = self->GetVirtualSize();
        return text;
    }

    EXPORT void wxWindow_SetMinSize(wxWindow* self, int width, int height)
    {
        self->SetMinSize(wxSize(width, height));
    }

    EXPORT void wxWindow_SetMaxSize(wxWindow* self, int width, int height)
    {
        self->SetMaxSize(wxSize(width, height));
    }
}
