#include "wrapper.h"

#include <wx/stc/stc.h>

// wxStyledTextCtrl inherits from wxControl and wxTextEntry.
// Additional methods available via:
//   wxWindow_*    — base window methods (see wx_window.cpp)
//   wxControl_*   — label, alignment (see wx_control.cpp)
//   wxTextEntry_* — text editing, hints, margins, selection, auto-complete (see wx_textentry.cpp)

extern "C"
{
    ////////////////////////////////////////////////////////////////////////////////
    // Event Handlers
    ////////////////////////////////////////////////////////////////////////////////

    MAKE_EVENT_WRAPPER(EVT_STC_CHANGE)
    MAKE_EVENT_WRAPPER(EVT_STC_STYLENEEDED)
    MAKE_EVENT_WRAPPER(EVT_STC_CHARADDED)
    MAKE_EVENT_WRAPPER(EVT_STC_SAVEPOINTREACHED)
    MAKE_EVENT_WRAPPER(EVT_STC_SAVEPOINTLEFT)
    MAKE_EVENT_WRAPPER(EVT_STC_ROMODIFYATTEMPT)
    MAKE_EVENT_WRAPPER(EVT_STC_DOUBLECLICK)
    MAKE_EVENT_WRAPPER(EVT_STC_UPDATEUI)
    MAKE_EVENT_WRAPPER(EVT_STC_MODIFIED)
    MAKE_EVENT_WRAPPER(EVT_STC_MACRORECORD)
    MAKE_EVENT_WRAPPER(EVT_STC_MARGINCLICK)
    MAKE_EVENT_WRAPPER(EVT_STC_NEEDSHOWN)
    MAKE_EVENT_WRAPPER(EVT_STC_PAINTED)
    MAKE_EVENT_WRAPPER(EVT_STC_USERLISTSELECTION)
    MAKE_EVENT_WRAPPER(EVT_STC_DWELLSTART)
    MAKE_EVENT_WRAPPER(EVT_STC_DWELLEND)
    MAKE_EVENT_WRAPPER(EVT_STC_START_DRAG)
    MAKE_EVENT_WRAPPER(EVT_STC_DRAG_OVER)
    MAKE_EVENT_WRAPPER(EVT_STC_DO_DROP)
    MAKE_EVENT_WRAPPER(EVT_STC_ZOOM)
    MAKE_EVENT_WRAPPER(EVT_STC_HOTSPOT_CLICK)
    MAKE_EVENT_WRAPPER(EVT_STC_HOTSPOT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_STC_CALLTIP_CLICK)
    MAKE_EVENT_WRAPPER(EVT_STC_AUTOCOMP_SELECTION)
    MAKE_EVENT_WRAPPER(EVT_STC_INDICATOR_CLICK)
    MAKE_EVENT_WRAPPER(EVT_STC_INDICATOR_RELEASE)
    MAKE_EVENT_WRAPPER(EVT_STC_AUTOCOMP_CANCELLED)
    MAKE_EVENT_WRAPPER(EVT_STC_AUTOCOMP_CHAR_DELETED)

    ////////////////////////////////////////////////////////////////////////////////
    // Wrappers
    ////////////////////////////////////////////////////////////////////////////////

#include "stc_gen.cpp"

    // wxStyledTextCtrl

    EXPORT void* wxStyledTextCtrl_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                         int width, int height, int style)
    {
#ifdef wxUSE_STC
        return (void*) new wxStyledTextCtrl(parent, id, wxPoint(x, y), wxSize(width, height), style,
                                            *text);
#else
        return nullptr;
#endif
    }

    // tricky handwritten functions

    EXPORT void* wxStyledTextCtrl_IndicatorGetForeground(void* pObject, int indic)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) pObject)->IndicatorGetForeground(indic);
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }
    EXPORT void* wxStyledTextCtrl_GetCaretLineBackground(void* pObject)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) pObject)->GetCaretLineBackground();
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }
    EXPORT void wxStyledTextCtrl_SetCaretLineBackground(void* pObject, int back_r, int back_g,
                                                        int back_b)
    {
#ifdef wxUSE_STC
        // SetCaretLineBack is changed name to SetCaretLineBackground.
        // So I avoid to use stc_gen.cpp for backward compatibility.
        ((wxStyledTextCtrl*) pObject)->SetCaretLineBackground(wxColour(back_r, back_g, back_b));
#endif
    }
    EXPORT void* wxStyledTextCtrl_GetCaretForeground(void* pObject)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) pObject)->GetCaretForeground();
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }
    EXPORT void* wxStyledTextCtrl_GetLine(void* pObject, int line)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) pObject)->GetLine(line);
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetText(void* pObject)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) pObject)->GetText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetSelectedText(void* pObject)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) pObject)->GetSelectedText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetTextRange(void* pObject, int startPos, int endPos)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) pObject)->GetTextRange(startPos, endPos);
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_CreateDocument(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextCtrl*) pObject)->CreateDocument();
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetEdgeColour(void* pObject)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) pObject)->GetEdgeColour();
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetDocPointer(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextCtrl*) pObject)->GetDocPointer();
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_PointFromPosition(void* pObject, int pos)
    {
#ifdef wxUSE_STC
        wxPoint p = ((wxStyledTextCtrl*) pObject)->PointFromPosition(pos);
        wxPoint* pp = new wxPoint(p);
        return pp;
#else
        return nullptr;
#endif
    }

    // wxStyledTextEvent's get functions

    EXPORT int wxStyledTextEvent_GetPosition(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetPosition();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetKey(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetKey();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetModifiers(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetModifiers();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetModificationType(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetModificationType();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLength(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetLength();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLinesAdded(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetLinesAdded();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLine(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetLine();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetFoldLevelNow(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetFoldLevelNow();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetFoldLevelPrev(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetFoldLevelPrev();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetMargin(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetMargin();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetMessage(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetMessage();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetWParam(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetWParam();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLParam(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetLParam();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetListType(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetListType();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetX(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetX();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetY(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetY();
#else
        return 0;
#endif
    }

    EXPORT void* wxStyledTextEvent_GetDragText(void* pObject)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextEvent*) pObject)->GetDragText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetDragAllowMove(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetDragAllowMove();
#else
        return false;
#endif
    }

    EXPORT int wxStyledTextEvent_GetDragResult(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetDragResult();
#else
        return false;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetShift(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetShift();
#else
        return false;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetControl(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetControl();
#else
        return false;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetAlt(void* pObject)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) pObject)->GetAlt();
#else
        return false;
#endif
    }

    EXPORT void* wxStyledTextEvent_GetText(void* pObject)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextEvent*) pObject)->GetText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextEvent_Clone(void* pObject)
    {
#ifdef wxUSE_STC
        return (void*) ((wxStyledTextEvent*) pObject)->Clone();
#else
        return nullptr;
#endif
    }

    // wxStyledTextEvent's set functions

    EXPORT void wxStyledTextEvent_SetPosition(void* pObject, int pos)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetPosition(pos);
#endif
    }

    EXPORT void wxStyledTextEvent_SetKey(void* pObject, int keyCode)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetKey(keyCode);
#endif
    }

    EXPORT void wxStyledTextEvent_SetModifiers(void* pObject, int modifiers)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetModifiers(modifiers);
#endif
    }

    EXPORT void wxStyledTextEvent_SetModificationType(void* pObject, int modType)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetModificationType(modType);
#endif
    }

    EXPORT void wxStyledTextEvent_SetText(void* pObject, void* text)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetText(*(wxString*) text);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLength(void* pObject, int len)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetLength(len);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLinesAdded(void* pObject, int num)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetLinesAdded(num);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLine(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetLine(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetFoldLevelNow(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetFoldLevelNow(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetFoldLevelPrev(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetFoldLevelPrev(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetMargin(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetMargin(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetMessage(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetMessage(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetWParam(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetWParam(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLParam(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetLParam(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetListType(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetListType(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetX(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetX(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetY(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetY(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetDragText(void* pObject, void* val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetDragText(*(wxString*) val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetDragAllowMove(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetDragAllowMove(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetDragResult(void* pObject, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) pObject)->SetDragResult(static_cast<wxDragResult>(val));
#endif
    }
}
