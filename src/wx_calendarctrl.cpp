#include "kwx_wrapper.h"

// wxCalendarCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxCalendarCtrl* wxCalendarCtrl_Create(wxWindow* parent, int id, wxDateTime* date, int x,
                                                 int y, int width, int height, int style)
    {
        return new wxCalendarCtrl(parent, id, *date, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxCalendarCtrl_SetDate(wxCalendarCtrl* self, wxDateTime* date)
    {
        self->SetDate(*date);
    }

    EXPORT void wxCalendarCtrl_GetDate(wxCalendarCtrl* self, wxDateTime* date)
    {
        *date = self->GetDate();
    }

    EXPORT void wxCalendarCtrl_EnableMonthChange(wxCalendarCtrl* self, bool enable)
    {
        self->EnableMonthChange(enable);
    }

    EXPORT void wxCalendarCtrl_EnableHolidayDisplay(wxCalendarCtrl* self, bool display)
    {
        self->EnableHolidayDisplay(display);
    }

    EXPORT void wxCalendarCtrl_SetHeaderColours(wxCalendarCtrl* self, wxColour* colFg,
                                                wxColour* colBg)
    {
        self->SetHeaderColours(*colFg, *colBg);
    }

    EXPORT void wxCalendarCtrl_GetHeaderColourFg(wxCalendarCtrl* self, wxColour* colour)
    {
        *colour = self->GetHeaderColourFg();
    }

    EXPORT void wxCalendarCtrl_GetHeaderColourBg(wxCalendarCtrl* self, wxColour* colour)
    {
        *colour = self->GetHeaderColourBg();
    }

    EXPORT void wxCalendarCtrl_SetHighlightColours(wxCalendarCtrl* self, wxColour* colFg,
                                                   wxColour* colBg)
    {
        self->SetHighlightColours(*colFg, *colBg);
    }

    EXPORT void wxCalendarCtrl_GetHighlightColourFg(wxCalendarCtrl* self, wxColour* colour)
    {
        *colour = self->GetHighlightColourFg();
    }

    EXPORT void wxCalendarCtrl_GetHighlightColourBg(wxCalendarCtrl* self, wxColour* colour)
    {
        *colour = self->GetHighlightColourBg();
    }

    EXPORT void wxCalendarCtrl_SetHolidayColours(wxCalendarCtrl* self, wxColour* colFg,
                                                 wxColour* colBg)
    {
        self->SetHolidayColours(*colFg, *colBg);
    }

    EXPORT void wxCalendarCtrl_GetHolidayColourFg(wxCalendarCtrl* self, wxColour* colour)
    {
        *colour = self->GetHolidayColourFg();
    }

    EXPORT void wxCalendarCtrl_GetHolidayColourBg(wxCalendarCtrl* self, wxColour* colour)
    {
        *colour = self->GetHolidayColourBg();
    }

    EXPORT wxCalendarDateAttr* wxCalendarCtrl_GetAttr(wxCalendarCtrl* self, size_t day)
    {
        return self->GetAttr(day);
    }

    EXPORT void wxCalendarCtrl_SetAttr(wxCalendarCtrl* self, size_t day, wxCalendarDateAttr* attr)
    {
        self->SetAttr(day, attr);
    }

    EXPORT void wxCalendarCtrl_SetHoliday(wxCalendarCtrl* self, size_t day)
    {
        self->SetHoliday(day);
    }

    EXPORT void wxCalendarCtrl_ResetAttr(wxCalendarCtrl* self, size_t day)
    {
        self->ResetAttr(day);
    }

    EXPORT int wxCalendarCtrl_HitTest(wxCalendarCtrl* self, int x, int y, wxDateTime* date,
                                      void* weekday)
    {
        return (int) self->HitTest(wxPoint(x, y), date, (wxDateTime::WeekDay*) weekday);
    }

    EXPORT wxCalendarDateAttr* wxCalendarDateAttr_Create(wxColour* textColour, wxColour* backColour,
                                                         wxColour* borderColour, wxFont* font, int border)
    {
        return new wxCalendarDateAttr(*textColour, *backColour, *borderColour, *font, (wxCalendarDateBorder) border);
    }

    EXPORT wxCalendarDateAttr* wxCalendarDateAttr_CreateDefault()
    {
        return new wxCalendarDateAttr();
    }

    EXPORT void wxCalendarDateAttr_Delete(wxCalendarDateAttr* self)
    {
        delete self;
    }

    EXPORT void wxCalendarDateAttr_SetTextColour(wxCalendarDateAttr* self, wxColour* col)
    {
        self->SetTextColour(*col);
    }

    EXPORT void wxCalendarDateAttr_SetBackgroundColour(wxCalendarDateAttr* self, wxColour* col)
    {
        self->SetBackgroundColour(*col);
    }

    EXPORT void wxCalendarDateAttr_SetBorderColour(wxCalendarDateAttr* self, wxColour* col)
    {
        self->SetBorderColour(*col);
    }

    EXPORT void wxCalendarDateAttr_SetFont(wxCalendarDateAttr* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxCalendarDateAttr_SetBorder(wxCalendarDateAttr* self, int border)
    {
        self->SetBorder((wxCalendarDateBorder) border);
    }

    EXPORT void wxCalendarDateAttr_SetHoliday(wxCalendarDateAttr* self, bool holiday)
    {
        self->SetHoliday(holiday);
    }

    EXPORT bool wxCalendarDateAttr_HasTextColour(wxCalendarDateAttr* self)
    {
        return self->HasTextColour();
    }

    EXPORT bool wxCalendarDateAttr_HasBackgroundColour(wxCalendarDateAttr* self)
    {
        return self->HasBackgroundColour();
    }

    EXPORT bool wxCalendarDateAttr_HasBorderColour(wxCalendarDateAttr* self)
    {
        return self->HasBorderColour();
    }

    EXPORT bool wxCalendarDateAttr_HasFont(wxCalendarDateAttr* self)
    {
        return self->HasFont();
    }

    EXPORT bool wxCalendarDateAttr_HasBorder(wxCalendarDateAttr* self)
    {
        return self->HasBorder();
    }

    EXPORT bool wxCalendarDateAttr_IsHoliday(wxCalendarDateAttr* self)
    {
        return self->IsHoliday();
    }

    EXPORT void wxCalendarDateAttr_GetTextColour(wxCalendarDateAttr* self, wxColour* ref)
    {
        *ref = self->GetTextColour();
    }

    EXPORT void wxCalendarDateAttr_GetBackgroundColour(wxCalendarDateAttr* self, wxColour* ref)
    {
        *ref = self->GetBackgroundColour();
    }

    EXPORT void wxCalendarDateAttr_GetBorderColour(wxCalendarDateAttr* self, wxColour* ref)
    {
        *ref = self->GetBorderColour();
    }

    EXPORT void wxCalendarDateAttr_GetFont(wxCalendarDateAttr* self, wxFont* ref)
    {
        *ref = self->GetFont();
    }

    EXPORT int wxCalendarDateAttr_GetBorder(wxCalendarDateAttr* self)
    {
        return (int) self->GetBorder();
    }
}
