#include "kwx_wrapper.h"

#include <wx/dialup.h>
#include <wx/fswatcher.h>
#include <wx/html/htmlwin.h>
#include <wx/process.h>

#include <wx/power.h>

#if defined(wxUSE_TAB_DIALOG) && (wxUSE_TAB_DIALOG == 0)
    #undef wxUSE_TAB_DIALOG
#endif

#ifdef USE_CONTRIB
    #include <wx/gizmos/dynamicsash.h>
    #include <wx/plot/plot.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Included as we need event wrappers. All have guards in the headers
// so don't repeat them here...
////////////////////////////////////////////////////////////////////////////////
#include <wx/aui/aui.h>
#include <wx/choicebk.h>
#include <wx/clrpicker.h>
#include <wx/collpane.h>
#include <wx/dataview.h>
#include <wx/fdrepdlg.h>
#include <wx/filectrl.h>
#include <wx/filepicker.h>
#include <wx/fontpicker.h>
#include <wx/fswatcher.h>
#include <wx/headerctrl.h>
#include <wx/hyperlink.h>
#include <wx/listbook.h>
#include <wx/mediactrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/ribbon/bar.h>
#include <wx/ribbon/buttonbar.h>
#include <wx/ribbon/gallery.h>
#include <wx/ribbon/toolbar.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/srchctrl.h>
#include <wx/stc/stc.h>
#include <wx/taskbar.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/toolbook.h>
#include <wx/treebook.h>

extern "C"
{
    EXPORT wxCommandEvent* wxCommandEvent_Create(int type, int id)
    {
        return new wxCommandEvent((wxEventType) type, id);
    }

    EXPORT void wxCommandEvent_Delete(wxCommandEvent* self)
    {
        delete self;
    }

    EXPORT int wxEvent_GetTimestamp(wxEvent* self)
    {
        return self->GetTimestamp();
    }

    EXPORT void wxEvent_Skip(wxEvent* self, bool skip)
    {
        self->Skip(skip);
    }

    EXPORT int wxEvent_GetEventType(wxEvent* self)
    {
        return (int) self->GetEventType();
    }

    EXPORT void wxEvent_SetEventType(wxEvent* self, int typ)
    {
        self->SetEventType((wxEventType) typ);
    }

    EXPORT void* wxEvent_GetEventObject(wxEvent* self)
    {
        return (void*) self->GetEventObject();
    }

    EXPORT void wxEvent_SetEventObject(wxEvent* self, wxObject* obj)
    {
        self->SetEventObject(obj);
    }

    EXPORT void wxEvent_SetTimestamp(wxEvent* self, int timestamp)
    {
        self->SetTimestamp((long) timestamp);
    }

    EXPORT int wxEvent_GetId(wxEvent* self)
    {
        return self->GetId();
    }

    EXPORT void wxEvent_SetId(wxEvent* self, int Id)
    {
        self->SetId(Id);
    }

    EXPORT bool wxEvent_GetSkipped(wxEvent* self)
    {
        return self->GetSkipped();
    }

    EXPORT bool wxEvent_IsCommandEvent(wxEvent* self)
    {
        return self->IsCommandEvent();
    }

    EXPORT void wxEvent_CopyObject(wxEvent* self, wxObject* object_dest)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT void wxEvent_SetCallbackUserData(wxEvent* self, wxObject* obj)
    {
        self->m_callbackUserData = obj;
    }

    EXPORT void* wxEvent_GetCallbackUserData(wxEvent* self)
    {
        return (void*) self->m_callbackUserData;
    }

    EXPORT void wxCommandEvent_SetClientData(wxCommandEvent* self, void* clientData)
    {
        self->SetClientData(clientData);
    }

    EXPORT void* wxCommandEvent_GetClientData(wxCommandEvent* self)
    {
        return self->GetClientData();
    }

    EXPORT void wxCommandEvent_SetClientObject(wxCommandEvent* self, void* clientObject)
    {
        self->SetClientObject((wxClientData*) clientObject);
    }

    EXPORT void* wxCommandEvent_GetClientObject(wxCommandEvent* self)
    {
        return (void*) self->GetClientObject();
    }

    EXPORT int wxCommandEvent_GetSelection(wxCommandEvent* self)
    {
        return self->GetSelection();
    }

    EXPORT void wxCommandEvent_SetString(wxCommandEvent* self, wxString* str)
    {
        self->SetString(*str);
    }

    EXPORT wxString* wxCommandEvent_GetString(wxCommandEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetString();
        return result;
    }

    EXPORT bool wxCommandEvent_IsChecked(wxCommandEvent* self)
    {
        return self->IsChecked();
    }

    EXPORT bool wxCommandEvent_IsSelection(wxCommandEvent* self)
    {
        return self->IsSelection();
    }

    EXPORT void wxCommandEvent_SetExtraLong(wxCommandEvent* self, long extraLong)
    {
        self->SetExtraLong(extraLong);
    }

    EXPORT long wxCommandEvent_GetExtraLong(wxCommandEvent* self)
    {
        return self->GetExtraLong();
    }

    EXPORT void wxCommandEvent_SetInt(wxCommandEvent* self, int intValue)
    {
        self->SetInt(intValue);
    }

    EXPORT long wxCommandEvent_GetInt(wxCommandEvent* self)
    {
        return self->GetInt();
    }

    EXPORT void wxCommandEvent_CopyObject(wxCommandEvent* self, wxObject* object_dest)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT void wxNotifyEvent_Veto(wxNotifyEvent* self)
    {
        self->Veto();
    }

    EXPORT void wxNotifyEvent_Allow(wxNotifyEvent* self)
    {
        self->Allow();
    }

    EXPORT bool wxNotifyEvent_IsAllowed(wxNotifyEvent* self)
    {
        return self->IsAllowed();
    }

    EXPORT void wxNotifyEvent_CopyObject(wxNotifyEvent* self, wxObject* object_dest)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT int wxScrollWinEvent_GetOrientation(wxScrollWinEvent* self)
    {
        return self->GetOrientation();
    }

    EXPORT int wxScrollWinEvent_GetPosition(wxScrollWinEvent* self)
    {
        return self->GetPosition();
    }

    EXPORT void wxScrollWinEvent_SetOrientation(wxScrollWinEvent* self, int orient)
    {
        self->SetOrientation(orient);
    }

    EXPORT void wxScrollWinEvent_SetPosition(wxScrollWinEvent* self, int pos)
    {
        self->SetPosition(pos);
    }

    EXPORT bool wxMouseEvent_IsButton(wxMouseEvent* self)
    {
        return self->IsButton();
    }

    EXPORT bool wxMouseEvent_ButtonDown(wxMouseEvent* self, int but)
    {
        return self->ButtonDown((wxMouseButton) but);
    }

    EXPORT bool wxMouseEvent_ButtonDClick(wxMouseEvent* self, int but)
    {
        return self->ButtonDClick((wxMouseButton) but);
    }

    EXPORT bool wxMouseEvent_ButtonUp(wxMouseEvent* self, int but)
    {
        return self->ButtonUp((wxMouseButton) but);
    }

    EXPORT bool wxMouseEvent_Button(wxMouseEvent* self, int but)
    {
        return self->Button((wxMouseButton) but);
    }

    EXPORT bool wxMouseEvent_ButtonIsDown(wxMouseEvent* self, int but)
    {
        return self->ButtonIsDown((wxMouseButton) but);
    }

    EXPORT bool wxMouseEvent_ControlDown(wxMouseEvent* self)
    {
        return self->ControlDown();
    }

    EXPORT bool wxMouseEvent_MetaDown(wxMouseEvent* self)
    {
        return self->MetaDown();
    }

    EXPORT bool wxMouseEvent_AltDown(wxMouseEvent* self)
    {
        return self->AltDown();
    }

    EXPORT bool wxMouseEvent_ShiftDown(wxMouseEvent* self)
    {
        return self->ShiftDown();
    }

    EXPORT bool wxMouseEvent_LeftDown(wxMouseEvent* self)
    {
        return self->LeftDown();
    }

    EXPORT bool wxMouseEvent_MiddleDown(wxMouseEvent* self)
    {
        return self->MiddleDown();
    }

    EXPORT bool wxMouseEvent_RightDown(wxMouseEvent* self)
    {
        return self->RightDown();
    }

    EXPORT bool wxMouseEvent_LeftUp(wxMouseEvent* self)
    {
        return self->LeftUp();
    }

    EXPORT bool wxMouseEvent_MiddleUp(wxMouseEvent* self)
    {
        return self->MiddleUp();
    }

    EXPORT bool wxMouseEvent_RightUp(wxMouseEvent* self)
    {
        return self->RightUp();
    }

    EXPORT bool wxMouseEvent_LeftDClick(wxMouseEvent* self)
    {
        return self->LeftDClick();
    }

    EXPORT bool wxMouseEvent_MiddleDClick(wxMouseEvent* self)
    {
        return self->MiddleDClick();
    }

    EXPORT bool wxMouseEvent_RightDClick(wxMouseEvent* self)
    {
        return self->RightDClick();
    }

    EXPORT bool wxMouseEvent_LeftIsDown(wxMouseEvent* self)
    {
        return self->LeftIsDown();
    }

    EXPORT bool wxMouseEvent_MiddleIsDown(wxMouseEvent* self)
    {
        return self->MiddleIsDown();
    }

    EXPORT bool wxMouseEvent_RightIsDown(wxMouseEvent* self)
    {
        return self->RightIsDown();
    }

    EXPORT bool wxMouseEvent_Dragging(wxMouseEvent* self)
    {
        return self->Dragging();
    }

    EXPORT bool wxMouseEvent_Moving(wxMouseEvent* self)
    {
        return self->Moving();
    }

    EXPORT bool wxMouseEvent_Entering(wxMouseEvent* self)
    {
        return self->Entering();
    }

    EXPORT bool wxMouseEvent_Leaving(wxMouseEvent* self)
    {
        return self->Leaving();
    }

    EXPORT wxPoint* wxMouseEvent_GetPosition(wxMouseEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT wxPoint* wxMouseEvent_GetLogicalPosition(wxMouseEvent* self, wxDC* dc)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetLogicalPosition(*dc);
        return pt;
    }

    EXPORT int wxMouseEvent_GetX(wxMouseEvent* self)
    {
        return self->GetX();
    }

    EXPORT int wxMouseEvent_GetY(wxMouseEvent* self)
    {
        return self->GetY();
    }

    EXPORT void wxMouseEvent_CopyObject(wxMouseEvent* self, wxObject* object_dest)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT wxCoord wxSetCursorEvent_GetX(wxSetCursorEvent* self)
    {
        return self->GetX();
    }

    EXPORT wxCoord wxSetCursorEvent_GetY(wxSetCursorEvent* self)
    {
        return self->GetY();
    }

    EXPORT void wxSetCursorEvent_SetCursor(wxSetCursorEvent* self, wxCursor* cursor)
    {
        self->SetCursor(*cursor);
    }

    EXPORT wxCursor* wxSetCursorEvent_GetCursor(wxSetCursorEvent* self)
    {
        wxCursor* cur = new wxCursor;
        *cur = self->GetCursor();
        return cur;
    }

    EXPORT bool wxSetCursorEvent_HasCursor(wxSetCursorEvent* self)
    {
        return self->HasCursor();
    }

    EXPORT bool wxKeyEvent_ControlDown(wxKeyEvent* self)
    {
        return self->ControlDown();
    }

    EXPORT bool wxKeyEvent_MetaDown(wxKeyEvent* self)
    {
        return self->MetaDown();
    }

    EXPORT bool wxKeyEvent_AltDown(wxKeyEvent* self)
    {
        return self->AltDown();
    }

    EXPORT bool wxKeyEvent_ShiftDown(wxKeyEvent* self)
    {
        return self->ShiftDown();
    }

    EXPORT bool wxKeyEvent_HasModifiers(wxKeyEvent* self)
    {
        return self->HasModifiers();
    }

    EXPORT int wxKeyEvent_GetKeyCode(wxKeyEvent* self)
    {
        return self->GetKeyCode();
    }

    EXPORT int wxKeyEvent_GetModifiers(wxKeyEvent* self)
    {
        return self->GetModifiers();
    }

    EXPORT void wxKeyEvent_SetKeyCode(wxKeyEvent* self, int code)
    {
        self->m_keyCode = code;
    }

    EXPORT wxPoint* wxKeyEvent_GetPosition(wxKeyEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT wxCoord wxKeyEvent_GetX(wxKeyEvent* self)
    {
        return self->GetX();
    }

    EXPORT wxCoord wxKeyEvent_GetY(wxKeyEvent* self)
    {
        return self->GetY();
    }

    EXPORT void wxKeyEvent_CopyObject(wxKeyEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT wxSize* wxSizeEvent_GetSize(wxSizeEvent* self)
    {
        wxSize* s = new wxSize();
        *s = self->GetSize();
        return s;
    }

    EXPORT void wxSizeEvent_CopyObject(wxSizeEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT wxPoint* wxMoveEvent_GetPosition(wxMoveEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT void wxMoveEvent_CopyObject(wxMoveEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT wxDC* wxEraseEvent_GetDC(wxEraseEvent* self)
    {
        return self->GetDC();
    }

    EXPORT void wxEraseEvent_CopyObject(wxEraseEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT bool wxActivateEvent_GetActive(wxActivateEvent* self)
    {
        return self->GetActive();
    }

    EXPORT void wxActivateEvent_CopyObject(wxActivateEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT int wxMenuEvent_GetMenuId(wxMenuEvent* self)
    {
        return self->GetMenuId();
    }

    EXPORT void wxMenuEvent_CopyObject(wxMenuEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT void wxCloseEvent_SetLoggingOff(wxCloseEvent* self, bool logOff)
    {
        self->SetLoggingOff(logOff);
    }

    EXPORT bool wxCloseEvent_GetLoggingOff(wxCloseEvent* self)
    {
        return self->GetLoggingOff();
    }

    EXPORT void wxCloseEvent_Veto(wxCloseEvent* self, bool veto)
    {
        self->Veto(veto);
    }

    EXPORT void wxCloseEvent_SetCanVeto(wxCloseEvent* self, bool canVeto)
    {
        self->SetCanVeto(canVeto);
    }

    EXPORT bool wxCloseEvent_CanVeto(wxCloseEvent* self)
    {
        return self->CanVeto();
    }

    EXPORT bool wxCloseEvent_GetVeto(wxCloseEvent* self)
    {
        return self->GetVeto();
    }

    EXPORT void wxCloseEvent_CopyObject(wxCloseEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT void wxShowEvent_SetShow(wxShowEvent* self, bool show)
    {
        self->SetShow(show);
    }

    EXPORT bool wxShowEvent_IsShown(wxShowEvent* self)
    {
        return self->IsShown();
    }

    EXPORT void wxShowEvent_CopyObject(wxShowEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT wxPoint* wxJoystickEvent_GetPosition(wxJoystickEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT int wxJoystickEvent_GetZPosition(wxJoystickEvent* self)
    {
        return self->GetZPosition();
    }

    EXPORT int wxJoystickEvent_GetButtonState(wxJoystickEvent* self)
    {
        return self->GetButtonState();
    }

    EXPORT int wxJoystickEvent_GetButtonChange(wxJoystickEvent* self)
    {
        return self->GetButtonChange();
    }

    EXPORT int wxJoystickEvent_GetJoystick(wxJoystickEvent* self)
    {
        return self->GetJoystick();
    }

    EXPORT void wxJoystickEvent_SetJoystick(wxJoystickEvent* self, int stick)
    {
        self->SetJoystick(stick);
    }

    EXPORT void wxJoystickEvent_SetButtonState(wxJoystickEvent* self, int state)
    {
        self->SetButtonState(state);
    }

    EXPORT void wxJoystickEvent_SetButtonChange(wxJoystickEvent* self, int change)
    {
        self->SetButtonChange(change);
    }

    EXPORT void wxJoystickEvent_SetPosition(wxJoystickEvent* self, int x, int y)
    {
        wxPoint pos(x, y);
        self->SetPosition(pos);
    }

    EXPORT void wxJoystickEvent_SetZPosition(wxJoystickEvent* self, int zPos)
    {
        self->SetZPosition(zPos);
    }

    EXPORT bool wxJoystickEvent_IsButton(wxJoystickEvent* self)
    {
        return self->IsButton();
    }

    EXPORT bool wxJoystickEvent_IsMove(wxJoystickEvent* self)
    {
        return self->IsMove();
    }

    EXPORT bool wxJoystickEvent_IsZMove(wxJoystickEvent* self)
    {
        return self->IsZMove();
    }

    EXPORT bool wxJoystickEvent_ButtonDown(wxJoystickEvent* self, int but)
    {
        return self->ButtonDown(but);
    }

    EXPORT bool wxJoystickEvent_ButtonUp(wxJoystickEvent* self, int but)
    {
        return self->ButtonUp(but);
    }

    EXPORT bool wxJoystickEvent_ButtonIsDown(wxJoystickEvent* self, int but)
    {
        return self->ButtonIsDown(but);
    }

    EXPORT void wxJoystickEvent_CopyObject(wxJoystickEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT bool wxUpdateUIEvent_GetChecked(wxUpdateUIEvent* self)
    {
        return self->GetChecked();
    }

    EXPORT bool wxUpdateUIEvent_GetEnabled(wxUpdateUIEvent* self)
    {
        return self->GetEnabled();
    }

    EXPORT wxString* wxUpdateUIEvent_GetText(wxUpdateUIEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetText();
        return result;
    }

    EXPORT bool wxUpdateUIEvent_GetSetText(wxUpdateUIEvent* self)
    {
        return self->GetSetText();
    }

    EXPORT bool wxUpdateUIEvent_GetSetChecked(wxUpdateUIEvent* self)
    {
        return self->GetSetChecked();
    }

    EXPORT bool wxUpdateUIEvent_GetSetEnabled(wxUpdateUIEvent* self)
    {
        return self->GetSetEnabled();
    }

    EXPORT void wxUpdateUIEvent_Check(wxUpdateUIEvent* self, bool check)
    {
        self->Check(check);
    }

    EXPORT void wxUpdateUIEvent_Enable(wxUpdateUIEvent* self, bool enable)
    {
        self->Enable(enable);
    }

    EXPORT void wxUpdateUIEvent_SetText(wxUpdateUIEvent* self, wxString* text)
    {
        self->SetText(*text);
    }

    EXPORT void wxUpdateUIEvent_CopyObject(wxUpdateUIEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT void wxPaletteChangedEvent_SetChangedWindow(wxPaletteChangedEvent* self, wxWindow* win)
    {
        self->SetChangedWindow(win);
    }

    EXPORT void* wxPaletteChangedEvent_GetChangedWindow(wxPaletteChangedEvent* self)
    {
        return (void*) self->GetChangedWindow();
    }

    EXPORT void wxPaletteChangedEvent_CopyObject(wxPaletteChangedEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT void wxQueryNewPaletteEvent_SetPaletteRealized(wxQueryNewPaletteEvent* self,
                                                          bool realized)
    {
        self->SetPaletteRealized(realized);
    }

    EXPORT bool wxQueryNewPaletteEvent_GetPaletteRealized(wxQueryNewPaletteEvent* self)
    {
        return self->GetPaletteRealized();
    }

    EXPORT void wxQueryNewPaletteEvent_CopyObject(wxQueryNewPaletteEvent* self, wxObject* obj)
    {
        // CopyObject was removed in wxWidgets 2.4+
    }

    EXPORT bool wxNavigationKeyEvent_GetDirection(wxNavigationKeyEvent* self)
    {
        return self->GetDirection();
    }

    EXPORT void wxNavigationKeyEvent_SetDirection(wxNavigationKeyEvent* self, bool bForward)
    {
        self->SetDirection(bForward);
    }

    EXPORT bool wxNavigationKeyEvent_IsWindowChange(wxNavigationKeyEvent* self)
    {
        return self->IsWindowChange();
    }

    EXPORT void wxNavigationKeyEvent_SetWindowChange(wxNavigationKeyEvent* self, bool bIs)
    {
        self->SetWindowChange(bIs);
    }

    EXPORT bool wxNavigationKeyEvent_ShouldPropagate(wxNavigationKeyEvent* self)
    {
        return self->ShouldPropagate();
    }

    EXPORT void* wxNavigationKeyEvent_GetCurrentFocus(wxNavigationKeyEvent* self)
    {
        return (void*) self->GetCurrentFocus();
    }

    EXPORT void wxNavigationKeyEvent_SetCurrentFocus(wxNavigationKeyEvent* self, wxWindow* win)
    {
        self->SetCurrentFocus(win);
    }

    EXPORT void* wxWindowCreateEvent_GetWindow(wxWindowCreateEvent* self)
    {
        return (void*) self->GetWindow();
    }

    EXPORT void* wxWindowDestroyEvent_GetWindow(wxWindowDestroyEvent* self)
    {
        return (void*) self->GetWindow();
    }

    EXPORT void wxIdleEvent_RequestMore(wxIdleEvent* self, bool needMore)
    {
        self->RequestMore(needMore);
    }

    EXPORT bool wxIdleEvent_MoreRequested(wxIdleEvent* self)
    {
        return self->MoreRequested();
    }

    EXPORT int wxListEvent_GetCode(wxListEvent* self)
    {
        return self->GetKeyCode();
    }

    EXPORT long wxListEvent_GetIndex(wxListEvent* self)
    {
        return self->GetIndex();
    }
    EXPORT int wxListEvent_GetColumn(wxListEvent* self)
    {
        return self->GetColumn();
    }

    EXPORT bool wxListEvent_Cancelled(wxListEvent* self)
    {
        // Cancelled() was removed in wxWidgets 2.4+
        return false;
    }

    EXPORT wxPoint* wxListEvent_GetPoint(wxListEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPoint();
        return pt;
    }

    EXPORT wxString* wxListEvent_GetLabel(wxListEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT wxString* wxListEvent_GetText(wxListEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetText();
        return result;
    }

    EXPORT int wxListEvent_GetImage(wxListEvent* self)
    {
        return self->GetImage();
    }

    EXPORT long wxListEvent_GetData(wxListEvent* self)
    {
        return self->GetData();
    }

    EXPORT long wxListEvent_GetMask(wxListEvent* self)
    {
        return self->GetMask();
    }

    EXPORT void wxListEvent_GetItem(wxListEvent* self, void* ref)
    {
        wxListItem* ret = new wxListItem(self->GetItem());
        *((void**) ref) = (void*) ret;
    }

    EXPORT void wxTreeEvent_GetItem(wxTreeEvent* self, wxTreeItemId* ref)
    {
        *ref = self->GetItem();
    }

    EXPORT void wxTreeEvent_GetOldItem(wxTreeEvent* self, wxTreeItemId* ref)
    {
        *ref = self->GetOldItem();
    }

    EXPORT wxPoint* wxTreeEvent_GetPoint(wxTreeEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPoint();
        return pt;
    }

    EXPORT int wxTreeEvent_GetCode(wxTreeEvent* self)
    {
        return self->GetKeyCode();
    }

    EXPORT wxString* wxTreeEvent_GetLabel(wxTreeEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT int wxSpinEvent_GetPosition(wxSpinEvent* self)
    {
        return self->GetPosition();
    }

    EXPORT void wxSpinEvent_SetPosition(wxSpinEvent* self, int pos)
    {
        self->SetPosition(pos);
    }

    EXPORT int wxTimerEvent_GetInterval(wxTimerEvent* self)
    {
        return self->GetInterval();
    }

    EXPORT int wxCalendarEvent_GetWeekDay(wxCalendarEvent* self)
    {
        return self->GetWeekDay();
    }

    EXPORT void wxCalendarEvent_GetDate(wxCalendarEvent* self, wxDateTime* date)
    {
        *date = self->GetDate();
    }

    EXPORT int wxScrollEvent_GetOrientation(wxScrollEvent* self)
    {
        return self->GetOrientation();
    }

    EXPORT int wxScrollEvent_GetPosition(wxScrollEvent* self)
    {
        return self->GetPosition();
    }

    EXPORT wxPoint* wxHelpEvent_GetPosition(wxHelpEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT void wxHelpEvent_SetPosition(wxHelpEvent* self, int x, int y)
    {
        self->SetPosition(wxPoint(x, y));
    }

    EXPORT wxString* wxHelpEvent_GetLink(wxHelpEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetLink();
        return result;
    }

    EXPORT void wxHelpEvent_SetLink(wxHelpEvent* self, wxString* link)
    {
        self->SetLink(*link);
    }

    EXPORT wxString* wxHelpEvent_GetTarget(wxHelpEvent* self)
    {
        wxString* result = new wxString();
        *result = self->GetTarget();
        return result;
    }

    EXPORT void wxHelpEvent_SetTarget(wxHelpEvent* self, wxString* target)
    {
        self->SetTarget(*target);
    }

    EXPORT bool wxPropertyGridEvent_HasProperty(wxPropertyGridEvent* self)
    {
        return self->GetProperty() != 0;
    }

    EXPORT wxPGProperty* wxPropertyGridEvent_GetProperty(wxPropertyGridEvent* self)
    {
#if defined(wxUSE_PROPGRID)
        return self->GetProperty();
#else
        return nullptr;
#endif
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Event wrappers
    ////////////////////////////////////////////////////////////////////////////////

    MAKE_EVENT_WRAPPER(EVT_NULL)
    MAKE_EVENT_WRAPPER(EVT_FIRST)

#if wxUSE_AUI
    // from aui/auibar.h
    MAKE_EVENT_WRAPPER(EVT_AUITOOLBAR_TOOL_DROPDOWN)
    MAKE_EVENT_WRAPPER(EVT_AUITOOLBAR_OVERFLOW_CLICK)
    MAKE_EVENT_WRAPPER(EVT_AUITOOLBAR_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_AUITOOLBAR_MIDDLE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_AUITOOLBAR_BEGIN_DRAG)

    // from aui/auibook.h
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CLOSE)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CLOSED)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_BUTTON)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_BEGIN_DRAG)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_END_DRAG)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_DRAG_MOTION)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_ALLOW_DND)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_MIDDLE_DOWN)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_MIDDLE_UP)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_RIGHT_DOWN)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_RIGHT_UP)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_DRAG_DONE)
    MAKE_EVENT_WRAPPER(EVT_AUINOTEBOOK_BG_DCLICK)

    // from aui/framemanager.h
    MAKE_EVENT_WRAPPER(EVT_AUI_PANE_BUTTON)
    MAKE_EVENT_WRAPPER(EVT_AUI_PANE_CLOSE)
    MAKE_EVENT_WRAPPER(EVT_AUI_PANE_MAXIMIZE)
    MAKE_EVENT_WRAPPER(EVT_AUI_PANE_RESTORE)
    MAKE_EVENT_WRAPPER(EVT_AUI_RENDER)
    MAKE_EVENT_WRAPPER(EVT_AUI_FIND_MANAGER)
#else
    // from aui/auibar.h
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUITOOLBAR_TOOL_DROPDOWN)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUITOOLBAR_OVERFLOW_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUITOOLBAR_RIGHT_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUITOOLBAR_MIDDLE_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUITOOLBAR_BEGIN_DRAG)

    // from aui/auibook.h
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CLOSE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CHANGING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_PAGE_CLOSED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_BUTTON)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_BEGIN_DRAG)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_END_DRAG)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_DRAG_MOTION)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_ALLOW_DND)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_MIDDLE_DOWN)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_MIDDLE_UP)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_RIGHT_DOWN)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_TAB_RIGHT_UP)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_DRAG_DONE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUINOTEBOOK_BG_DCLICK)

    // from aui/framemanager.h
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUI_PANE_BUTTON)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUI_PANE_CLOSE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUI_PANE_MAXIMIZE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUI_PANE_RESTORE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUI_RENDER)
    MAKE_UNDEFEVENT_WRAPPER(EVT_AUI_FIND_MANAGER)
#endif  // wxUSE_AUI

// from calctrl.h
#if wxUSE_CALENDARCTRL
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_SEL_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_DOUBLECLICKED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_WEEKDAY_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_WEEK_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_DAY_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_MONTH_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_CALENDAR_YEAR_CHANGED)
#endif  // wxUSE_CALENDARCTRL

// from choicebook.h
#if wxUSE_CHOICEBOOK
    MAKE_EVENT_WRAPPER(EVT_COMMAND_CHOICEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_CHOICEBOOK_PAGE_CHANGING)
#endif

// from clipbrd.h
#if wxUSE_CLIPBOARD
    MAKE_EVENT_WRAPPER(EVT_CLIPBOARD_CHANGED)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_CLIPBOARD_CHANGED)
#endif

// from clrpicker.h
#if wxUSE_COLOURPICKERCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_COLOURPICKER_CHANGED)
#endif

// from collpane.h
#if wxUSE_COLLPANE
    MAKE_EVENT_WRAPPER(EVT_COMMAND_COLLPANE_CHANGED)
#endif

// from dataview.h
#if wxUSE_DATAVIEWCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_SELECTION_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_ACTIVATED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_COLLAPSED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EXPANDED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_COLLAPSING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EXPANDING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_START_EDITING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EDITING_STARTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_VALUE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_HEADER_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_SORTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_REORDERED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_CACHE_HINT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_DROP)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_SELECTION_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_ACTIVATED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_COLLAPSED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EXPANDED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_COLLAPSING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EXPANDING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_START_EDITING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EDITING_STARTED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_VALUE_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_HEADER_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_SORTED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_COLUMN_REORDERED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_CACHE_HINT)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_DATAVIEW_ITEM_DROP)
#endif

    // from dateevt.h
    MAKE_EVENT_WRAPPER(EVT_DATE_CHANGED)

    // from dialog.h
    MAKE_EVENT_WRAPPER(EVT_WINDOW_MODAL_DIALOG_CLOSED)

// from dialup.h - does anyone even care about this stuff these days?
#if wxUSE_DIALUP_MANAGER
    MAKE_EVENT_WRAPPER(EVT_DIALUP_CONNECTED)
    MAKE_EVENT_WRAPPER(EVT_DIALUP_DISCONNECTED)
#endif

    // from event.h
    MAKE_EVENT_WRAPPER(EVT_COMMAND_BUTTON_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_CHECKBOX_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_CHOICE_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LISTBOX_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LISTBOX_DOUBLECLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_CHECKLISTBOX_TOGGLED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_MENU_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SLIDER_UPDATED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RADIOBOX_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RADIOBUTTON_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_VLBOX_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_COMBOBOX_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOOL_RCLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOOL_DROPDOWN_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOOL_ENTER)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_COMBOBOX_DROPDOWN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_COMBOBOX_CLOSEUP)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_THREAD)
    MAKE_EVENT_WRAPPER(EVT_LEFT_DOWN)
    MAKE_EVENT_WRAPPER(EVT_LEFT_UP)
    MAKE_EVENT_WRAPPER(EVT_MIDDLE_DOWN)
    MAKE_EVENT_WRAPPER(EVT_MIDDLE_UP)
    MAKE_EVENT_WRAPPER(EVT_RIGHT_DOWN)
    MAKE_EVENT_WRAPPER(EVT_RIGHT_UP)
    MAKE_EVENT_WRAPPER(EVT_MOTION)
    MAKE_EVENT_WRAPPER(EVT_ENTER_WINDOW)
    MAKE_EVENT_WRAPPER(EVT_LEAVE_WINDOW)
    MAKE_EVENT_WRAPPER(EVT_LEFT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_MIDDLE_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_SET_FOCUS)
    MAKE_EVENT_WRAPPER(EVT_KILL_FOCUS)
    MAKE_EVENT_WRAPPER(EVT_CHILD_FOCUS)
    MAKE_EVENT_WRAPPER(EVT_MOUSEWHEEL)
    MAKE_EVENT_WRAPPER(EVT_AUX1_DOWN)
    MAKE_EVENT_WRAPPER(EVT_AUX1_UP)
    MAKE_EVENT_WRAPPER(EVT_AUX1_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_AUX2_DOWN)
    MAKE_EVENT_WRAPPER(EVT_AUX2_UP)
    MAKE_EVENT_WRAPPER(EVT_AUX2_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_CHAR)
    MAKE_EVENT_WRAPPER(EVT_CHAR_HOOK)
    MAKE_EVENT_WRAPPER(EVT_NAVIGATION_KEY)
    MAKE_EVENT_WRAPPER(EVT_KEY_DOWN)
    MAKE_EVENT_WRAPPER(EVT_KEY_UP)

#if wxUSE_HOTKEY
    MAKE_EVENT_WRAPPER(EVT_HOTKEY)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_HOTKEY)
#endif

    MAKE_EVENT_WRAPPER(EVT_SET_CURSOR)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_TOP)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_BOTTOM)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_LINEUP)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_LINEDOWN)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_PAGEUP)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_PAGEDOWN)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_THUMBTRACK)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_THUMBRELEASE)
    MAKE_EVENT_WRAPPER(EVT_SCROLL_CHANGED)

#if wxUSE_SPINBTN
    MAKE_EVENT_WRAPPER(EVT_SPIN_UP)
    MAKE_EVENT_WRAPPER(EVT_SPIN_DOWN)
    MAKE_EVENT_WRAPPER(EVT_SPIN)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_SPIN_UP)
    MAKE_UNDEFEVENT_WRAPPER(EVT_SPIN_DOWN)
    MAKE_UNDEFEVENT_WRAPPER(EVT_SPIN)
#endif

    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_TOP)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_BOTTOM)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_LINEUP)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_LINEDOWN)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_PAGEUP)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_PAGEDOWN)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_THUMBTRACK)
    MAKE_EVENT_WRAPPER(EVT_SCROLLWIN_THUMBRELEASE)
    MAKE_EVENT_WRAPPER(EVT_SIZE)
    MAKE_EVENT_WRAPPER(EVT_MOVE)
    MAKE_EVENT_WRAPPER(EVT_CLOSE_WINDOW)
    MAKE_EVENT_WRAPPER(EVT_END_SESSION)
    MAKE_EVENT_WRAPPER(EVT_QUERY_END_SESSION)
    MAKE_EVENT_WRAPPER(EVT_ACTIVATE_APP)
    MAKE_EVENT_WRAPPER(EVT_ACTIVATE)
    MAKE_EVENT_WRAPPER(EVT_CREATE)
    MAKE_EVENT_WRAPPER(EVT_DESTROY)
    MAKE_EVENT_WRAPPER(EVT_SHOW)
    MAKE_EVENT_WRAPPER(EVT_ICONIZE)
    MAKE_EVENT_WRAPPER(EVT_MAXIMIZE)
    MAKE_EVENT_WRAPPER(EVT_MOUSE_CAPTURE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_MOUSE_CAPTURE_LOST)
    MAKE_EVENT_WRAPPER(EVT_PAINT)
    MAKE_EVENT_WRAPPER(EVT_ERASE_BACKGROUND)
    MAKE_EVENT_WRAPPER(EVT_NC_PAINT)
    MAKE_EVENT_WRAPPER(EVT_MENU_OPEN)
    MAKE_EVENT_WRAPPER(EVT_MENU_CLOSE)
    MAKE_EVENT_WRAPPER(EVT_MENU_HIGHLIGHT)
    MAKE_EVENT_WRAPPER(EVT_CONTEXT_MENU)
    MAKE_EVENT_WRAPPER(EVT_SYS_COLOUR_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_DISPLAY_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_QUERY_NEW_PALETTE)
    MAKE_EVENT_WRAPPER(EVT_PALETTE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_JOY_BUTTON_DOWN)
    MAKE_EVENT_WRAPPER(EVT_JOY_BUTTON_UP)
    MAKE_EVENT_WRAPPER(EVT_JOY_MOVE)
    MAKE_EVENT_WRAPPER(EVT_JOY_ZMOVE)
    MAKE_EVENT_WRAPPER(EVT_DROP_FILES)
    MAKE_EVENT_WRAPPER(EVT_INIT_DIALOG)
    MAKE_EVENT_WRAPPER(EVT_IDLE)
    MAKE_EVENT_WRAPPER(EVT_UPDATE_UI)
    MAKE_EVENT_WRAPPER(EVT_SIZING)
    MAKE_EVENT_WRAPPER(EVT_MOVING)
    MAKE_EVENT_WRAPPER(EVT_MOVE_START)
    MAKE_EVENT_WRAPPER(EVT_MOVE_END)
    MAKE_EVENT_WRAPPER(EVT_HIBERNATE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_COPY)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_CUT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_PASTE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LEFT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LEFT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SET_FOCUS)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_KILL_FOCUS)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_ENTER)
    MAKE_EVENT_WRAPPER(EVT_HELP)
    MAKE_EVENT_WRAPPER(EVT_DETAILED_HELP)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOOL_CLICKED)

    // Short-form event type aliases (wx 3.0+ style)
    // These are convenience aliases that wxWidgets provides for the longer COMMAND names
    MAKE_EVENT_WRAPPER(EVT_BUTTON)
    MAKE_EVENT_WRAPPER(EVT_CHECKBOX)
    MAKE_EVENT_WRAPPER(EVT_CHOICE)
    MAKE_EVENT_WRAPPER(EVT_LISTBOX)
    MAKE_EVENT_WRAPPER(EVT_LISTBOX_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_CHECKLISTBOX)
    MAKE_EVENT_WRAPPER(EVT_MENU)
    MAKE_EVENT_WRAPPER(EVT_SLIDER)
    MAKE_EVENT_WRAPPER(EVT_RADIOBOX)
    MAKE_EVENT_WRAPPER(EVT_RADIOBUTTON)
    MAKE_EVENT_WRAPPER(EVT_COMBOBOX)
    MAKE_EVENT_WRAPPER(EVT_TOOL)
    MAKE_EVENT_WRAPPER(EVT_TOOL_RCLICKED)
    MAKE_EVENT_WRAPPER(EVT_TOOL_DROPDOWN)
    MAKE_EVENT_WRAPPER(EVT_TOOL_ENTER)
    MAKE_EVENT_WRAPPER(EVT_COMBOBOX_DROPDOWN)
    MAKE_EVENT_WRAPPER(EVT_COMBOBOX_CLOSEUP)
    MAKE_EVENT_WRAPPER(EVT_TEXT)
    MAKE_EVENT_WRAPPER(EVT_TEXT_ENTER)
    MAKE_EVENT_WRAPPER(EVT_TEXT_URL)
    MAKE_EVENT_WRAPPER(EVT_TEXT_MAXLEN)
    MAKE_EVENT_WRAPPER(EVT_SPINCTRL)
    MAKE_EVENT_WRAPPER(EVT_SPINCTRLDOUBLE)
    MAKE_EVENT_WRAPPER(EVT_TOGGLEBUTTON)
    MAKE_EVENT_WRAPPER(EVT_VLBOX)
    MAKE_EVENT_WRAPPER(EVT_THREAD)
    MAKE_EVENT_WRAPPER(EVT_TEXT_COPY)
    MAKE_EVENT_WRAPPER(EVT_TEXT_CUT)
    MAKE_EVENT_WRAPPER(EVT_TEXT_PASTE)
    MAKE_EVENT_WRAPPER(EVT_SEARCHCTRL_SEARCH_BTN)
    MAKE_EVENT_WRAPPER(EVT_SEARCHCTRL_CANCEL_BTN)
    MAKE_EVENT_WRAPPER(EVT_SPLITTER_SASH_POS_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_SPLITTER_SASH_POS_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_SPLITTER_UNSPLIT)
    MAKE_EVENT_WRAPPER(EVT_SPLITTER_DOUBLECLICKED)
    MAKE_EVENT_WRAPPER(EVT_NOTEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_NOTEBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_LISTBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_LISTBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_CHOICEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_CHOICEBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_TREEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_TREEBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_TREEBOOK_NODE_COLLAPSED)
    MAKE_EVENT_WRAPPER(EVT_TREEBOOK_NODE_EXPANDED)
    MAKE_EVENT_WRAPPER(EVT_TOOLBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_TOOLBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_COLOURPICKER_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_FILEPICKER_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_DIRPICKER_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_FONTPICKER_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_HYPERLINK)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_SELECTION_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_ACTIVATED)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_COLLAPSED)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_EXPANDED)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_COLLAPSING)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_EXPANDING)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_EDITING_STARTED)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_EDITING_DONE)
    MAKE_EVENT_WRAPPER(EVT_DATAVIEW_ITEM_VALUE_CHANGED)

// from filectrl.h
#if wxUSE_FILECTRL
    MAKE_EVENT_WRAPPER(EVT_FILECTRL_SELECTIONCHANGED)
    MAKE_EVENT_WRAPPER(EVT_FILECTRL_FILEACTIVATED)
    MAKE_EVENT_WRAPPER(EVT_FILECTRL_FOLDERCHANGED)
    MAKE_EVENT_WRAPPER(EVT_FILECTRL_FILTERCHANGED)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_FILECTRL_SELECTIONCHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_FILECTRL_FILEACTIVATED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_FILECTRL_FOLDERCHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_FILECTRL_FILTERCHANGED)
#endif

// from filepicker.h
#if wxUSE_FILEPICKERCTRL || wxUSE_DIRPICKERCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FILEPICKER_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_DIRPICKER_CHANGED)
#endif

// from fontpicker.h
#if wxUSE_FONTPICKERCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FONTPICKER_CHANGED)
#endif

// from fswatcher.h
#if wxUSE_FSWATCHER
    MAKE_EVENT_WRAPPER(EVT_FSWATCHER)
#endif

// from generic/grid.h
#if wxUSE_GRID
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_LEFT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_LEFT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_LABEL_LEFT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_LABEL_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_LABEL_LEFT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_LABEL_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_GRID_ROW_SIZE)
    MAKE_EVENT_WRAPPER(EVT_GRID_COL_SIZE)
    MAKE_EVENT_WRAPPER(EVT_GRID_RANGE_SELECT)
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_GRID_SELECT_CELL)
    MAKE_EVENT_WRAPPER(EVT_GRID_EDITOR_SHOWN)
    MAKE_EVENT_WRAPPER(EVT_GRID_EDITOR_HIDDEN)
    MAKE_EVENT_WRAPPER(EVT_GRID_EDITOR_CREATED)
    MAKE_EVENT_WRAPPER(EVT_GRID_CELL_BEGIN_DRAG)
    MAKE_EVENT_WRAPPER(EVT_GRID_COL_MOVE)
    MAKE_EVENT_WRAPPER(EVT_GRID_COL_SORT)
#endif

    // from laywin.h
    MAKE_EVENT_WRAPPER(EVT_QUERY_LAYOUT_INFO)
    MAKE_EVENT_WRAPPER(EVT_CALCULATE_LAYOUT)

// from sashwin.h
#if wxUSE_SASH
    MAKE_EVENT_WRAPPER(EVT_SASH_DRAGGED)
#endif

// from headerctrl.h
#if wxUSE_HEADERCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_MIDDLE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_MIDDLE_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_SEPARATOR_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_BEGIN_RESIZE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_RESIZING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_END_RESIZE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_BEGIN_REORDER)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_END_REORDER)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HEADER_DRAGGING_CANCELLED)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_RIGHT_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_MIDDLE_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_DCLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_RIGHT_DCLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_MIDDLE_DCLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_SEPARATOR_DCLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_BEGIN_RESIZE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_RESIZING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_END_RESIZE)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_BEGIN_REORDER)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_END_REORDER)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_HEADER_DRAGGING_CANCELLED)
#endif

// from html/htmlwin.h
#if wxUSE_HTML
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HTML_CELL_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HTML_CELL_HOVER)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HTML_LINK_CLICKED)
#endif

// from hyperlink.h
#if wxUSE_HYPERLINKCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_HYPERLINK)
#endif

    // from listbase.h
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_BEGIN_DRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_BEGIN_RDRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_BEGIN_LABEL_EDIT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_END_LABEL_EDIT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_DELETE_ITEM)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_DELETE_ALL_ITEMS)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_ITEM_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_ITEM_DESELECTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_KEY_DOWN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_INSERT_ITEM)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_COL_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_ITEM_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_ITEM_MIDDLE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_ITEM_ACTIVATED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_CACHE_HINT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_COL_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_COL_BEGIN_DRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_COL_DRAGGING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_COL_END_DRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LIST_ITEM_FOCUSED)

// from listbook.h
#if wxUSE_LISTBOOK
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LISTBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_LISTBOOK_PAGE_CHANGING)
#endif

// from notebook.h
#if wxUSE_NOTEBOOK
    MAKE_EVENT_WRAPPER(EVT_COMMAND_NOTEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_NOTEBOOK_PAGE_CHANGING)
#endif

// from power.h
#ifdef wxHAS_POWER_EVENTS
    MAKE_EVENT_WRAPPER(EVT_POWER_SUSPENDING)
    MAKE_EVENT_WRAPPER(EVT_POWER_SUSPENDED)
    MAKE_EVENT_WRAPPER(EVT_POWER_SUSPEND_CANCEL)
    MAKE_EVENT_WRAPPER(EVT_POWER_RESUME)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_POWER_SUSPENDING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_POWER_SUSPENDED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_POWER_SUSPEND_CANCEL)
    MAKE_UNDEFEVENT_WRAPPER(EVT_POWER_RESUME)
#endif

    // from process.h
    MAKE_EVENT_WRAPPER(EVT_END_PROCESS)

// from propgrid/propgrid.h
#if wxUSE_PROPGRID
    MAKE_EVENT_WRAPPER(EVT_PG_SELECTED)
    MAKE_EVENT_WRAPPER(EVT_PG_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_PG_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_PG_HIGHLIGHTED)
    MAKE_EVENT_WRAPPER(EVT_PG_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_PG_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_PG_ITEM_COLLAPSED)
    MAKE_EVENT_WRAPPER(EVT_PG_ITEM_EXPANDED)
    MAKE_EVENT_WRAPPER(EVT_PG_DOUBLE_CLICK)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_SELECTED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_CHANGING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_HIGHLIGHTED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_RIGHT_CLICK)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_PAGE_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_ITEM_COLLAPSED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_ITEM_EXPANDED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_PG_DOUBLE_CLICK)
#endif

// from ribbon/bar.h
#if wxUSE_RIBBON
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP)

    // from ribbon/buttonbar.h
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBUTTON_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED)

    // from ribbon/gallery.h
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONGALLERY_HOVER_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONGALLERY_SELECTED)

    // from ribbon/toolbar.h
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONTOOL_CLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RIBBONTOOL_DROPDOWN_CLICKED)
#else
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_PAGE_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_PAGE_CHANGING)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP)

    // from ribbon/buttonbar.h
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBUTTON_CLICKED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED)

    // from ribbon/gallery.h
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONGALLERY_HOVER_CHANGED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONGALLERY_SELECTED)

    // from ribbon/toolbar.h
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONTOOL_CLICKED)
    MAKE_UNDEFEVENT_WRAPPER(EVT_COMMAND_RIBBONTOOL_DROPDOWN_CLICKED)
#endif

// from richtext/richtextctrl.h
#if wxUSE_RICHTEXT
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_LEFT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_MIDDLE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_LEFT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_RETURN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_CHARACTER)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_DELETE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_STYLESHEET_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_STYLESHEET_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_STYLESHEET_REPLACING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_STYLESHEET_REPLACED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_CONTENT_INSERTED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_CONTENT_DELETED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_STYLE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_SELECTION_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_RICHTEXT_BUFFER_RESET)
#endif

// from socket.h
#if wxUSE_SOCKETS
    MAKE_EVENT_WRAPPER(EVT_SOCKET)
#endif

// from spinctrl.h
#if wxUSE_SPINCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SPINCTRL_UPDATED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SPINCTRLDOUBLE_UPDATED)
#endif

    // from splitter.h
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SPLITTER_SASH_POS_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SPLITTER_SASH_POS_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SPLITTER_DOUBLECLICKED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SPLITTER_UNSPLIT)

// from srchctrl.h
#if wxUSE_SEARCHCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SEARCHCTRL_CANCEL_BTN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_SEARCHCTRL_SEARCH_BTN)
#endif

// from textctrl.h
#if wxUSE_TEXTCTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_UPDATED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_ENTER)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_URL)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TEXT_MAXLEN)
#endif

// from tglbtn.h
#if wxUSE_TOGGLEBTN
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOGGLEBUTTON_CLICKED)
#endif

// from timer.h
#if wxUSE_TIMER
    MAKE_EVENT_WRAPPER(EVT_TIMER)
#endif

// from toolbook.h
#if wxUSE_TOOLBOOK
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOOLBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TOOLBOOK_PAGE_CHANGING)
#endif

// from treebase.h
#if wxUSE_TREECTRL
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_BEGIN_DRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_BEGIN_RDRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_BEGIN_LABEL_EDIT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_END_LABEL_EDIT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_DELETE_ITEM)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_GET_INFO)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_SET_INFO)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_EXPANDED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_EXPANDING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_COLLAPSED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_COLLAPSING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_SEL_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_SEL_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_KEY_DOWN)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_ACTIVATED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_RIGHT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_MIDDLE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_END_DRAG)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_STATE_IMAGE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_GETTOOLTIP)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREE_ITEM_MENU)
#endif

// from treebook.h
#if wxUSE_TREEBOOK
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREEBOOK_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREEBOOK_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREEBOOK_NODE_COLLAPSED)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_TREEBOOK_NODE_EXPANDED)
#endif

// from wizard.h
#if wxUSE_WIZARDDLG
    MAKE_EVENT_WRAPPER(EVT_WIZARD_PAGE_CHANGED)
    MAKE_EVENT_WRAPPER(EVT_WIZARD_PAGE_CHANGING)
    MAKE_EVENT_WRAPPER(EVT_WIZARD_CANCEL)
    MAKE_EVENT_WRAPPER(EVT_WIZARD_HELP)
    MAKE_EVENT_WRAPPER(EVT_WIZARD_FINISHED)
    MAKE_EVENT_WRAPPER(EVT_WIZARD_PAGE_SHOWN)
#endif

    ////////////////////////////////////////////////////////////////////////////////
    // Keypress wrappers
    ////////////////////////////////////////////////////////////////////////////////

#define MAKE_KEYPRESS_WRAPPER(key) \
    EXPORT int exp##key()          \
    {                              \
        return (int) WX##key;      \
    }

    MAKE_KEYPRESS_WRAPPER(K_BACK)
    MAKE_KEYPRESS_WRAPPER(K_TAB)
    MAKE_KEYPRESS_WRAPPER(K_RETURN)
    MAKE_KEYPRESS_WRAPPER(K_ESCAPE)
    MAKE_KEYPRESS_WRAPPER(K_SPACE)
    MAKE_KEYPRESS_WRAPPER(K_DELETE)
    MAKE_KEYPRESS_WRAPPER(K_START)
    MAKE_KEYPRESS_WRAPPER(K_LBUTTON)
    MAKE_KEYPRESS_WRAPPER(K_RBUTTON)
    MAKE_KEYPRESS_WRAPPER(K_CANCEL)
    MAKE_KEYPRESS_WRAPPER(K_MBUTTON)
    MAKE_KEYPRESS_WRAPPER(K_CLEAR)
    MAKE_KEYPRESS_WRAPPER(K_SHIFT)
    MAKE_KEYPRESS_WRAPPER(K_ALT)
    MAKE_KEYPRESS_WRAPPER(K_CONTROL)
    MAKE_KEYPRESS_WRAPPER(K_MENU)
    MAKE_KEYPRESS_WRAPPER(K_PAUSE)
    MAKE_KEYPRESS_WRAPPER(K_CAPITAL)
    MAKE_KEYPRESS_WRAPPER(K_END)
    MAKE_KEYPRESS_WRAPPER(K_HOME)
    MAKE_KEYPRESS_WRAPPER(K_LEFT)
    MAKE_KEYPRESS_WRAPPER(K_UP)
    MAKE_KEYPRESS_WRAPPER(K_RIGHT)
    MAKE_KEYPRESS_WRAPPER(K_DOWN)
    MAKE_KEYPRESS_WRAPPER(K_SELECT)
    MAKE_KEYPRESS_WRAPPER(K_PRINT)
    MAKE_KEYPRESS_WRAPPER(K_EXECUTE)
    MAKE_KEYPRESS_WRAPPER(K_SNAPSHOT)
    MAKE_KEYPRESS_WRAPPER(K_INSERT)
    MAKE_KEYPRESS_WRAPPER(K_HELP)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD0)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD1)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD2)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD3)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD4)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD5)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD6)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD7)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD8)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD9)
    MAKE_KEYPRESS_WRAPPER(K_MULTIPLY)
    MAKE_KEYPRESS_WRAPPER(K_ADD)
    MAKE_KEYPRESS_WRAPPER(K_SEPARATOR)
    MAKE_KEYPRESS_WRAPPER(K_SUBTRACT)
    MAKE_KEYPRESS_WRAPPER(K_DECIMAL)
    MAKE_KEYPRESS_WRAPPER(K_DIVIDE)
    MAKE_KEYPRESS_WRAPPER(K_F1)
    MAKE_KEYPRESS_WRAPPER(K_F2)
    MAKE_KEYPRESS_WRAPPER(K_F3)
    MAKE_KEYPRESS_WRAPPER(K_F4)
    MAKE_KEYPRESS_WRAPPER(K_F5)
    MAKE_KEYPRESS_WRAPPER(K_F6)
    MAKE_KEYPRESS_WRAPPER(K_F7)
    MAKE_KEYPRESS_WRAPPER(K_F8)
    MAKE_KEYPRESS_WRAPPER(K_F9)
    MAKE_KEYPRESS_WRAPPER(K_F10)
    MAKE_KEYPRESS_WRAPPER(K_F11)
    MAKE_KEYPRESS_WRAPPER(K_F12)
    MAKE_KEYPRESS_WRAPPER(K_F13)
    MAKE_KEYPRESS_WRAPPER(K_F14)
    MAKE_KEYPRESS_WRAPPER(K_F15)
    MAKE_KEYPRESS_WRAPPER(K_F16)
    MAKE_KEYPRESS_WRAPPER(K_F17)
    MAKE_KEYPRESS_WRAPPER(K_F18)
    MAKE_KEYPRESS_WRAPPER(K_F19)
    MAKE_KEYPRESS_WRAPPER(K_F20)
    MAKE_KEYPRESS_WRAPPER(K_F21)
    MAKE_KEYPRESS_WRAPPER(K_F22)
    MAKE_KEYPRESS_WRAPPER(K_F23)
    MAKE_KEYPRESS_WRAPPER(K_F24)
    MAKE_KEYPRESS_WRAPPER(K_NUMLOCK)
    MAKE_KEYPRESS_WRAPPER(K_SCROLL)
    MAKE_KEYPRESS_WRAPPER(K_PAGEUP)
    MAKE_KEYPRESS_WRAPPER(K_PAGEDOWN)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_SPACE)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_TAB)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_ENTER)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_F1)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_F2)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_F3)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_F4)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_HOME)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_LEFT)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_UP)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_RIGHT)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_DOWN)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_PAGEUP)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_PAGEDOWN)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_END)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_BEGIN)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_INSERT)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_DELETE)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_EQUAL)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_MULTIPLY)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_ADD)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_SEPARATOR)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_SUBTRACT)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_DECIMAL)
    MAKE_KEYPRESS_WRAPPER(K_NUMPAD_DIVIDE)
    MAKE_KEYPRESS_WRAPPER(K_WINDOWS_LEFT)
    MAKE_KEYPRESS_WRAPPER(K_WINDOWS_RIGHT)
    MAKE_KEYPRESS_WRAPPER(K_WINDOWS_MENU)
    MAKE_KEYPRESS_WRAPPER(K_COMMAND)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL1)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL2)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL3)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL4)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL5)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL6)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL7)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL8)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL9)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL10)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL11)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL12)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL13)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL14)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL15)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL16)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL17)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL18)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL19)
    MAKE_KEYPRESS_WRAPPER(K_SPECIAL20)
}
