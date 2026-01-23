/*==============================================================================
 * stc.cpp
 *
 * C wrapper for wxStyledTextCtrl
 *
 * (C) 2002-2011 wxEiffel and wxHaskell contributors. See contributors.txt
 *
 *==============================================================================*/

#include "wrapper.h"

#ifdef wxUSE_STC
    #include <wx/stc/stc.h>
#endif

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

    /* wxStyledTextCtrl */

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

    /* tricky handwritten functions */

    EXPORT void* wxStyledTextCtrl_IndicatorGetForeground(void* _obj, int indic)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) _obj)->IndicatorGetForeground(indic);
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }
    EXPORT void* wxStyledTextCtrl_GetCaretLineBackground(void* _obj)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) _obj)->GetCaretLineBackground();
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }
    EXPORT void wxStyledTextCtrl_SetCaretLineBackground(void* _obj, int back_r, int back_g,
                                                        int back_b)
    {
#ifdef wxUSE_STC
        /* SetCaretLineBack is changed name to SetCaretLineBackground.
           So I avoid to use stc_gen.cpp for backward compatibility. */
        ((wxStyledTextCtrl*) _obj)->SetCaretLineBackground(wxColour(back_r, back_g, back_b));
#endif
    }
    EXPORT void* wxStyledTextCtrl_GetCaretForeground(void* _obj)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) _obj)->GetCaretForeground();
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }
    EXPORT void* wxStyledTextCtrl_GetLine(void* _obj, int line)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) _obj)->GetLine(line);
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetText(void* _obj)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) _obj)->GetText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetSelectedText(void* _obj)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) _obj)->GetSelectedText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetTextRange(void* _obj, int startPos, int endPos)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextCtrl*) _obj)->GetTextRange(startPos, endPos);
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_CreateDocument(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextCtrl*) _obj)->CreateDocument();
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetEdgeColour(void* _obj)
    {
#ifdef wxUSE_STC
        wxColour c = ((wxStyledTextCtrl*) _obj)->GetEdgeColour();
        wxColour* cc = new wxColour(c);
        return cc;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_GetDocPointer(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextCtrl*) _obj)->GetDocPointer();
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextCtrl_PointFromPosition(void* _obj, int pos)
    {
#ifdef wxUSE_STC
        wxPoint p = ((wxStyledTextCtrl*) _obj)->PointFromPosition(pos);
        wxPoint* pp = new wxPoint(p);
        return pp;
#else
        return nullptr;
#endif
    }

    /*************************************/
    /* wxStyledTextEvent's get functions */
    /*************************************/

    EXPORT int wxStyledTextEvent_GetPosition(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetPosition();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetKey(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetKey();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetModifiers(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetModifiers();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetModificationType(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetModificationType();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLength(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetLength();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLinesAdded(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetLinesAdded();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLine(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetLine();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetFoldLevelNow(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetFoldLevelNow();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetFoldLevelPrev(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetFoldLevelPrev();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetMargin(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetMargin();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetMessage(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetMessage();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetWParam(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetWParam();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetLParam(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetLParam();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetListType(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetListType();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetX(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetX();
#else
        return 0;
#endif
    }

    EXPORT int wxStyledTextEvent_GetY(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetY();
#else
        return 0;
#endif
    }

    EXPORT void* wxStyledTextEvent_GetDragText(void* _obj)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextEvent*) _obj)->GetDragText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetDragAllowMove(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetDragAllowMove();
#else
        return false;
#endif
    }

    EXPORT int wxStyledTextEvent_GetDragResult(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetDragResult();
#else
        return false;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetShift(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetShift();
#else
        return false;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetControl(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetControl();
#else
        return false;
#endif
    }

    EXPORT bool wxStyledTextEvent_GetAlt(void* _obj)
    {
#ifdef wxUSE_STC
        return ((wxStyledTextEvent*) _obj)->GetAlt();
#else
        return false;
#endif
    }

    EXPORT void* wxStyledTextEvent_GetText(void* _obj)
    {
#ifdef wxUSE_STC
        wxString s = ((wxStyledTextEvent*) _obj)->GetText();
        wxString* ss = new wxString(s);
        return ss;
#else
        return nullptr;
#endif
    }

    EXPORT void* wxStyledTextEvent_Clone(void* _obj)
    {
#ifdef wxUSE_STC
        return (void*) ((wxStyledTextEvent*) _obj)->Clone();
#else
        return nullptr;
#endif
    }

    /*************************************/
    /* wxStyledTextEvent's set functions */
    /*************************************/

    EXPORT void wxStyledTextEvent_SetPosition(void* _obj, int pos)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetPosition(pos);
#endif
    }

    EXPORT void wxStyledTextEvent_SetKey(void* _obj, int k)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetKey(k);
#endif
    }

    EXPORT void wxStyledTextEvent_SetModifiers(void* _obj, int m)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetModifiers(m);
#endif
    }

    EXPORT void wxStyledTextEvent_SetModificationType(void* _obj, int t)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetModificationType(t);
#endif
    }

    EXPORT void wxStyledTextEvent_SetText(void* _obj, void* t)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetText(*(wxString*) t);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLength(void* _obj, int len)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetLength(len);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLinesAdded(void* _obj, int num)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetLinesAdded(num);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLine(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetLine(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetFoldLevelNow(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetFoldLevelNow(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetFoldLevelPrev(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetFoldLevelPrev(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetMargin(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetMargin(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetMessage(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetMessage(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetWParam(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetWParam(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetLParam(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetLParam(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetListType(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetListType(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetX(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetX(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetY(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetY(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetDragText(void* _obj, void* val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetDragText(*(wxString*) val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetDragAllowMove(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetDragAllowMove(val);
#endif
    }

    EXPORT void wxStyledTextEvent_SetDragResult(void* _obj, int val)
    {
#ifdef wxUSE_STC
        ((wxStyledTextEvent*) _obj)->SetDragResult(static_cast<wxDragResult>(val));
#endif
    }
}
