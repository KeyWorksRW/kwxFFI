#include "wrapper.h"

extern "C"
{
    EXPORT wxDateTime* wxDateTime_Create()
    {
        return new wxDateTime();
    }

    EXPORT void wxDateTime_SetCountry(int country)
    {
        wxDateTime::SetCountry((wxDateTime::Country) country);
    }

    EXPORT int wxDateTime_GetCountry()
    {
        return (int) wxDateTime::GetCountry();
    }

    EXPORT bool wxDateTime_IsWestEuropeanCountry(int country)
    {
        return wxDateTime::IsWestEuropeanCountry((wxDateTime::Country) country);
    }

    EXPORT int wxDateTime_GetCurrentYear(int cal)
    {
        return wxDateTime::GetCurrentYear((wxDateTime::Calendar) cal);
    }

    EXPORT int wxDateTime_ConvertYearToBC(int year)
    {
        return wxDateTime::ConvertYearToBC(year);
    }

    EXPORT int wxDateTime_GetCurrentMonth(int cal)
    {
        return (int) wxDateTime::GetCurrentMonth((wxDateTime::Calendar) cal);
    }

    EXPORT bool wxDateTime_IsLeapYear(int year, int cal)
    {
        return wxDateTime::IsLeapYear(year, (wxDateTime::Calendar) cal);
    }

    EXPORT int wxDateTime_GetCentury(int year)
    {
        return wxDateTime::GetCentury(year);
    }

    EXPORT int wxDateTime_GetNumberOfDays(int year, int cal)
    {
        return (int) wxDateTime::GetNumberOfDays(year, (wxDateTime::Calendar) cal);
    }

    EXPORT int wxDateTime_GetNumberOfDaysMonth(int month, int year, int cal)
    {
        return wxDateTime::GetNumberOfDays((wxDateTime::Month) month, year,
                                           (wxDateTime::Calendar) cal);
    }

    EXPORT wxString* wxDateTime_GetMonthName(int month, int flags)
    {
        wxString* result = new wxString();
        *result =
            wxDateTime::GetMonthName((wxDateTime::Month) month, (wxDateTime::NameFlags) flags);
        return result;
    }

    EXPORT wxString* wxDateTime_GetWeekDayName(int weekday, int flags)
    {
        wxString* result = new wxString();
        *result = wxDateTime::GetWeekDayName((wxDateTime::WeekDay) weekday,
                                             (wxDateTime::NameFlags) flags);
        return result;
    }

    EXPORT wxString* wxDateTime_GetAmString()
    {
        wxString* result = new wxString();
        wxString pm;
        wxDateTime::GetAmPmStrings(result, &pm);
        return result;
    }

    EXPORT wxString* wxDateTime_GetPmString()
    {
        wxString* result = new wxString();
        wxString am;
        wxDateTime::GetAmPmStrings(&am, result);
        return result;
    }

    EXPORT bool wxDateTime_IsDSTApplicable(int year, int country)
    {
        return wxDateTime::IsDSTApplicable(year, (wxDateTime::Country) country);
    }

    EXPORT void wxDateTime_GetBeginDST(int year, int country, wxDateTime* dateTime)
    {
        *dateTime = wxDateTime::GetBeginDST(year, (wxDateTime::Country) country);
    }

    EXPORT void wxDateTime_GetEndDST(int year, int country, wxDateTime* dateTime)
    {
        *dateTime = wxDateTime::GetEndDST(year, (wxDateTime::Country) country);
    }

    EXPORT void wxDateTime_Now(wxDateTime* dateTime)
    {
        *dateTime = wxDateTime::Now();
    }

    EXPORT void wxDateTime_UNow(wxDateTime* dateTime)
    {
        *dateTime = wxDateTime::UNow();
    }

    EXPORT void wxDateTime_Today(wxDateTime* dateTime)
    {
        *dateTime = wxDateTime::Today();
    }

    EXPORT void wxDateTime_SetToCurrent(wxDateTime* self)
    {
        self->SetToCurrent();
    }

    EXPORT void wxDateTime_SetTime(wxDateTime* self, int hour, int minute, int second, int millisec)
    {
        self->Set((wxDateTime::wxDateTime_t) hour, (wxDateTime::wxDateTime_t) minute,
                  (wxDateTime::wxDateTime_t) second, (wxDateTime::wxDateTime_t) millisec);
    }

    EXPORT void wxDateTime_Set(wxDateTime* self, int day, int month, int year, int hour, int minute,
                               int second, int millisec)
    {
        self->Set((wxDateTime::wxDateTime_t) day, (wxDateTime::Month) month, year,
                  (wxDateTime::wxDateTime_t) hour, (wxDateTime::wxDateTime_t) minute,
                  (wxDateTime::wxDateTime_t) second, (wxDateTime::wxDateTime_t) millisec);
    }

    EXPORT void wxDateTime_ResetTime(wxDateTime* self)
    {
        self->ResetTime();
    }

    EXPORT void wxDateTime_SetYear(wxDateTime* self, int year)
    {
        self->SetYear(year);
    }

    EXPORT void wxDateTime_SetMonth(wxDateTime* self, int month)
    {
        self->SetMonth((wxDateTime::Month) month);
    }

    EXPORT void wxDateTime_SetDay(wxDateTime* self, int day)
    {
        self->SetDay((wxDateTime::wxDateTime_t) day);
    }

    EXPORT void wxDateTime_SetHour(wxDateTime* self, int hour)
    {
        self->SetHour((wxDateTime::wxDateTime_t) hour);
    }

    EXPORT void wxDateTime_SetMinute(wxDateTime* self, int minute)
    {
        self->SetMinute((wxDateTime::wxDateTime_t) minute);
    }

    EXPORT void wxDateTime_SetSecond(wxDateTime* self, int second)
    {
        self->SetSecond((wxDateTime::wxDateTime_t) second);
    }

    EXPORT void wxDateTime_SetMillisecond(wxDateTime* self, int millisecond)
    {
        self->SetMillisecond((wxDateTime::wxDateTime_t) millisecond);
    }

    EXPORT void wxDateTime_SetToWeekDayInSameWeek(wxDateTime* self, int weekday, int flags)
    {
        self->SetToWeekDayInSameWeek((wxDateTime::WeekDay) weekday, (wxDateTime::WeekFlags) flags);
    }

    EXPORT void wxDateTime_GetWeekDayInSameWeek(wxDateTime* self, int weekday, int flags,
                                                wxDateTime* ref)
    {
        *ref = self->GetWeekDayInSameWeek((wxDateTime::WeekDay) weekday,
                                          (wxDateTime::WeekFlags) flags);
    }

    EXPORT void wxDateTime_SetToNextWeekDay(wxDateTime* self, int weekday)
    {
        self->SetToNextWeekDay((wxDateTime::WeekDay) weekday);
    }

    EXPORT void wxDateTime_GetNextWeekDay(wxDateTime* self, int weekday, wxDateTime* ref)
    {
        *ref = self->GetNextWeekDay((wxDateTime::WeekDay) weekday);
    }

    EXPORT void wxDateTime_SetToPrevWeekDay(wxDateTime* self, int weekday)
    {
        self->SetToPrevWeekDay((wxDateTime::WeekDay) weekday);
    }

    EXPORT void wxDateTime_GetPrevWeekDay(wxDateTime* self, int weekday, wxDateTime* ref)
    {
        *ref = self->GetPrevWeekDay((wxDateTime::WeekDay) weekday);
    }

    EXPORT bool wxDateTime_SetToWeekDay(wxDateTime* self, int weekday, int nthWeek, int month,
                                        int year)
    {
        return self->SetToWeekDay((wxDateTime::WeekDay) weekday, nthWeek, (wxDateTime::Month) month,
                                  year);
    }

    EXPORT void wxDateTime_GetWeekDay(wxDateTime* self, int weekday, int nthWeek, int month,
                                      int year, wxDateTime* ref)
    {
        *ref = self->GetWeekDay((wxDateTime::WeekDay) weekday, nthWeek, (wxDateTime::Month) month,
                                year);
    }

    EXPORT bool wxDateTime_SetToLastWeekDay(wxDateTime* self, int weekday, int month, int year)
    {
        return self->SetToLastWeekDay((wxDateTime::WeekDay) weekday, (wxDateTime::Month) month,
                                      year);
    }

    EXPORT void wxDateTime_GetLastWeekDay(wxDateTime* self, int weekday, int month, int year,
                                          wxDateTime* ref)
    {
        *ref = self->GetLastWeekDay((wxDateTime::WeekDay) weekday, (wxDateTime::Month) month, year);
    }

    EXPORT void wxDateTime_SetToLastMonthDay(wxDateTime* self, int month, int year)
    {
        self->SetToLastMonthDay((wxDateTime::Month) month, year);
    }

    EXPORT void wxDateTime_GetLastMonthDay(wxDateTime* self, int month, int year, wxDateTime* ref)
    {
        *ref = self->GetLastMonthDay((wxDateTime::Month) month, year);
    }

    EXPORT void wxDateTime_ToTimezone(wxDateTime* self, int timeZone, bool noDST)
    {
        self->ToTimezone(wxDateTime::TimeZone((wxDateTime::TZ) timeZone), noDST);
    }

    EXPORT void wxDateTime_MakeTimezone(wxDateTime* self, int timeZone, bool noDST)
    {
        self->MakeTimezone(wxDateTime::TimeZone((wxDateTime::TZ) timeZone), noDST);
    }

    EXPORT void wxDateTime_ToGMT(wxDateTime* self, bool noDST)
    {
        self->ToGMT(noDST);
    }

    EXPORT void wxDateTime_MakeGMT(wxDateTime* self, bool noDST)
    {
        self->MakeGMT(noDST);
    }

    EXPORT int wxDateTime_IsDST(wxDateTime* self, int country)
    {
        return self->IsDST((wxDateTime::Country) country);
    }

    EXPORT bool wxDateTime_IsValid(wxDateTime* self)
    {
        return self->IsValid();
    }

    EXPORT time_t wxDateTime_GetTicks(wxDateTime* self)
    {
        return self->GetTicks();
    }

    EXPORT int wxDateTime_GetYear(wxDateTime* self, int timeZone)
    {
        return self->GetYear(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetMonth(wxDateTime* self, int timeZone)
    {
        return (int) self->GetMonth(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetDay(wxDateTime* self, int timeZone)
    {
        return (int) self->GetDay(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetWeekDayTZ(wxDateTime* self, int timeZone)
    {
        return (int) self->GetWeekDay(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetHour(wxDateTime* self, int timeZone)
    {
        return (int) self->GetHour(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetMinute(wxDateTime* self, int timeZone)
    {
        return (int) self->GetMinute(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetSecond(wxDateTime* self, int timeZone)
    {
        return (int) self->GetSecond(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetMillisecond(wxDateTime* self, int timeZone)
    {
        return (int) self->GetMillisecond(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetDayOfYear(wxDateTime* self, int timeZone)
    {
        return (int) self->GetDayOfYear(wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetWeekOfYear(wxDateTime* self, int flags, int timeZone)
    {
        return (int) self->GetWeekOfYear((wxDateTime::WeekFlags) flags,
                                         wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT int wxDateTime_GetWeekOfMonth(wxDateTime* self, int flags, int timeZone)
    {
        return (int) self->GetWeekOfMonth((wxDateTime::WeekFlags) flags,
                                          wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
    }

    EXPORT bool wxDateTime_IsWorkDay(wxDateTime* self, int country)
    {
        return self->IsWorkDay((wxDateTime::Country) country);
    }

    EXPORT bool wxDateTime_IsEqualTo(wxDateTime* self, wxDateTime* datetime)
    {
        return self->IsEqualTo(*datetime);
    }

    EXPORT bool wxDateTime_IsEarlierThan(wxDateTime* self, wxDateTime* datetime)
    {
        return self->IsEarlierThan(*datetime);
    }

    EXPORT bool wxDateTime_IsLaterThan(wxDateTime* self, wxDateTime* datetime)
    {
        return self->IsLaterThan(*datetime);
    }

    EXPORT bool wxDateTime_IsStrictlyBetween(wxDateTime* self, wxDateTime* t1, wxDateTime* t2)
    {
        return self->IsStrictlyBetween(*t1, *t2);
    }

    EXPORT bool wxDateTime_IsBetween(wxDateTime* self, wxDateTime* t1, wxDateTime* t2)
    {
        return self->IsBetween(*t1, *t2);
    }

    EXPORT bool wxDateTime_IsSameDate(wxDateTime* self, wxDateTime* dateTime)
    {
        return self->IsSameDate(*dateTime);
    }

    EXPORT bool wxDateTime_IsSameTime(wxDateTime* self, wxDateTime* dateTime)
    {
        return self->IsSameTime(*dateTime);
    }

    EXPORT bool wxDateTime_IsEqualUpTo(wxDateTime* self, wxDateTime* dateTime, wxTimeSpan* timeSpan)
    {
        return self->IsEqualUpTo(*dateTime, *timeSpan);
    }

    EXPORT void wxDateTime_AddTime(wxDateTime* self, wxTimeSpan* diff, wxDateTime* ref)
    {
        *ref = self->Add(*diff);
    }

    EXPORT void wxDateTime_SubtractTime(wxDateTime* self, wxTimeSpan* diff, wxDateTime* ref)
    {
        *ref = self->Subtract(*diff);
    }

    EXPORT void wxDateTime_AddDate(wxDateTime* self, wxDateSpan* diff, wxDateTime* ref)
    {
        *ref = self->Add(*diff);
    }

    EXPORT void wxDateTime_SubtractDate(wxDateTime* self, wxDateSpan* diff, wxDateTime* ref)
    {
        *ref = self->Subtract(*diff);
    }

    EXPORT void* wxDateTime_ParseRfc822Date(wxDateTime* self, void* date)
    {
        wxString dateStr((const char*) date);
        wxString::const_iterator parseOut;
        wxString remainStr;

        if (self->ParseRfc822Date(dateStr, &parseOut))
        {
            // The iterator points to the first character after the string
            // We should return a pointer to the remainder, but this is complicated
            // in Unicode by the fact that code points are not simple pointers...
            for (; parseOut != dateStr.end(); ++parseOut)
                remainStr += *parseOut;

            delete ((const char*) date);
            return (void*) strdup(remainStr.utf8_str().data());
        }
        else
            return nullptr;
    }

    EXPORT void* wxDateTime_ParseFormat(wxDateTime* self, void* date, void* format,
                                        wxDateTime* dateDef)
    {
        wxString dateStr((const char*) date);
        wxString parseFmt((const char*) format);
        wxString::const_iterator parseOut;
        wxString remainStr;

        if (self->ParseFormat(dateStr, parseFmt, *dateDef, &parseOut))
        {
            for (; parseOut != dateStr.end(); ++parseOut)
                remainStr += *parseOut;

            delete ((const char*) date);
            return (void*) strdup(remainStr.utf8_str().data());
        }
        else
            return nullptr;
    }

    EXPORT void* wxDateTime_ParseDateTime(wxDateTime* self, void* datetime)
    {
        wxString dateStr((const char*) datetime);
        wxString::const_iterator parseOut;
        wxString remainStr;

        if (self->ParseDateTime(dateStr, &parseOut))
        {
            for (; parseOut != dateStr.end(); ++parseOut)
                remainStr += *parseOut;

            delete ((const char*) datetime);
            return (void*) strdup(remainStr.utf8_str().data());
        }
        else
            return nullptr;
    }

    EXPORT void* wxDateTime_ParseDate(wxDateTime* self, void* date)
    {
        wxString dateStr((const char*) date);
        wxString::const_iterator parseOut;
        wxString remainStr;

        if (self->ParseDate(dateStr, &parseOut))
        {
            for (; parseOut != dateStr.end(); ++parseOut)
                remainStr += *parseOut;

            delete ((const char*) date);
            return (void*) strdup(remainStr.utf8_str().data());
        }
        else
            return nullptr;
    }

    EXPORT void* wxDateTime_ParseTime(wxDateTime* self, void* time)
    {
        wxString timeStr((const char*) time);
        wxString::const_iterator parseOut;
        wxString remainStr;

        if (self->ParseTime(timeStr, &parseOut))
        {
            for (; parseOut != timeStr.end(); ++parseOut)
                remainStr += *parseOut;

            delete ((const char*) time);
            return (void*) strdup(remainStr.utf8_str().data());
        }
        else
            return nullptr;
    }

    EXPORT wxString* wxDateTime_Format(wxDateTime* self, void* format, int timeZone)
    {
        wxString* result = new wxString();
        *result =
            self->Format((const char*) format, wxDateTime::TimeZone((wxDateTime::TZ) timeZone));
        return result;
    }

    EXPORT wxString* wxDateTime_FormatDate(wxDateTime* self)
    {
        wxString* result = new wxString();
        *result = self->FormatDate();
        return result;
    }

    EXPORT wxString* wxDateTime_FormatTime(wxDateTime* self)
    {
        wxString* result = new wxString();
        *result = self->FormatTime();
        return result;
    }

    EXPORT wxString* wxDateTime_FormatISODate(wxDateTime* self)
    {
        wxString* result = new wxString();
        *result = self->FormatISODate();
        return result;
    }

    EXPORT wxString* wxDateTime_FormatISOTime(wxDateTime* self)
    {
        wxString* result = new wxString();
        *result = self->FormatISOTime();
        return result;
    }

    EXPORT wxDateTime* wxDateTime_wxDateTime(long hi_long, unsigned long lo_long)
    {
        return new wxDateTime(wxLongLong(hi_long, lo_long));
    }

    EXPORT void wxDateTime_GetValue(wxDateTime* self, long* hi_long, unsigned long* lo_long)
    {
        wxLongLong val = self->GetValue();
        *hi_long = val.GetHi();
        *lo_long = val.GetLo();
    }

    EXPORT int wxDateTime_GetTimeNow()
    {
        return (int) wxDateTime::GetTimeNow();
    }

    EXPORT void wxDateTime_AddTimeValues(wxDateTime* self, int hours, int minVal, int seconds,
                                         int milliseconds)
    {
        self->Add(wxTimeSpan((long) hours, (long) minVal, (long) seconds, (long) milliseconds));
    }

    EXPORT void wxDateTime_AddDateValues(wxDateTime* self, int years, int month, int week, int day)
    {
        self->Add(wxDateSpan((long) years, (long) month, (long) week, (long) day));
    }
}
