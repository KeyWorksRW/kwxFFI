// Date/time, locale, config, command-line and variant gap wrappers: wxDateTime, wxTimeSpan,
// wxDateSpan, wxLocale, wxUILocale, wxTranslations, wxNumberFormatter, wxConfigBase,
// wxFileConfig, wxCmdLineParser and wxVariant.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include "kwx_helper_cmdline.h"

#include <wx/cmdline.h>
#include <wx/confbase.h>
#include <wx/datetime.h>
#include <wx/fileconf.h>
#include <wx/intl.h>
#include <wx/numformatter.h>
#include <wx/translation.h>
#include <wx/uilocale.h>
#include <wx/variant.h>

// The wxWidgets time-zone enumeration is a plain int in the FFI.
static wxDateTime::TimeZone ToTimeZone(int time_zone)
{
    return wxDateTime::TimeZone(static_cast<wxDateTime::TZ>(time_zone));
}

// ---------------------------------------------------------------------------
// kwxCmdLineDesc
// ---------------------------------------------------------------------------

kwxCmdLineDesc::kwxCmdLineDesc()
{
    m_entries.push_back(
        wxCmdLineEntryDesc { wxCMD_LINE_NONE, nullptr, nullptr, nullptr, wxCMD_LINE_VAL_NONE, 0 });
}

const char* kwxCmdLineDesc::StoreText(const wxString& text)
{
    m_text.push_back(std::string(text.utf8_string().data()));
    return m_text.back().c_str();
}

void kwxCmdLineDesc::AppendEntry(wxCmdLineEntryType kind, const wxString& short_name,
                                 const wxString& long_name, const wxString& description,
                                 wxCmdLineParamType type, int flags)
{
    wxCmdLineEntryDesc entry {};
    entry.kind = kind;
    entry.shortName = short_name.empty() ? nullptr : StoreText(short_name);
    entry.longName = long_name.empty() ? nullptr : StoreText(long_name);
    entry.description = description.empty() ? nullptr : StoreText(description);
    entry.type = type;
    entry.flags = flags;

    // The table always ends with its wxCMD_LINE_NONE terminator: replace it, then re-append it.
    if (m_entries.back().kind == wxCMD_LINE_NONE)
    {
        m_entries.back() = entry;
    }
    else
    {
        m_entries.push_back(entry);
    }

    m_entries.push_back(
        wxCmdLineEntryDesc { wxCMD_LINE_NONE, nullptr, nullptr, nullptr, wxCMD_LINE_VAL_NONE, 0 });
}

void kwxCmdLineDesc::AddSwitch(const wxString& short_name, const wxString& long_name,
                               const wxString& description, int flags)
{
    AppendEntry(wxCMD_LINE_SWITCH, short_name, long_name, description, wxCMD_LINE_VAL_NONE, flags);
}

void kwxCmdLineDesc::AddOption(const wxString& short_name, const wxString& long_name,
                               const wxString& description, int type, int flags)
{
    AppendEntry(wxCMD_LINE_OPTION, short_name, long_name, description,
                static_cast<wxCmdLineParamType>(type), flags);
}

void kwxCmdLineDesc::AddParam(const wxString& description, int type, int flags)
{
    AppendEntry(wxCMD_LINE_PARAM, wxString(), wxString(), description,
                static_cast<wxCmdLineParamType>(type), flags);
}

const wxCmdLineEntryDesc* kwxCmdLineDesc::GetDesc() const
{
    return m_entries.data();
}

// The exported signatures are fixed by include/kwx_date_locale_extra.h: an object handle, an
// input handle and an out-handle all cross the C ABI as the same pointer type, so several
// exports necessarily take adjacent parameters of the same type. Suppress the check for the
// whole file instead of annotating every export.
// NOLINTBEGIN(bugprone-identical-type-multi-param)
extern "C"
{
    // -----------------------------------------------------------------------
    // wxDateTime
    // -----------------------------------------------------------------------

    EXPORT wxDateTime* wxDateTime_CreateFromTimeT(time_t ticks)
    {
        return new wxDateTime(ticks);
    }

    EXPORT wxDateTime* wxDateTime_CreateFromJDN(double julian_day)
    {
        return new wxDateTime(julian_day);
    }

    EXPORT void wxDateTime_SetFromTimeT(wxDateTime* self, time_t ticks)
    {
        self->Set(ticks);
    }

    EXPORT void wxDateTime_SetFromJDN(wxDateTime* self, double julian_day)
    {
        self->Set(julian_day);
    }

    EXPORT bool wxDateTime_GetFirstWeekDay(int* first_week_day)
    {
        wxDateTime::WeekDay weekday = wxDateTime::Mon;
        const bool found = wxDateTime::GetFirstWeekDay(&weekday);
        *first_week_day = static_cast<int>(weekday);
        return found;
    }

    EXPORT wxString* wxDateTime_GetEnglishMonthName(int month, int flags)
    {
        return new wxString(wxDateTime::GetEnglishMonthName(
            static_cast<wxDateTime::Month>(month), static_cast<wxDateTime::NameFlags>(flags)));
    }

    EXPORT wxString* wxDateTime_GetEnglishWeekDayName(int weekday, int flags)
    {
        return new wxString(wxDateTime::GetEnglishWeekDayName(
            static_cast<wxDateTime::WeekDay>(weekday), static_cast<wxDateTime::NameFlags>(flags)));
    }

    EXPORT void wxDateTime_GetDateOnly(wxDateTime* self, wxDateTime* ref)
    {
        *ref = self->GetDateOnly();
    }

    EXPORT void wxDateTime_SetToYearDay(wxDateTime* self, int year_day)
    {
        self->SetToYearDay(static_cast<wxDateTime::wxDateTime_t>(year_day));
    }

    EXPORT void wxDateTime_GetYearDay(wxDateTime* self, int year_day, wxDateTime* ref)
    {
        *ref = self->GetYearDay(static_cast<wxDateTime::wxDateTime_t>(year_day));
    }

    EXPORT double wxDateTime_GetJulianDayNumber(wxDateTime* self)
    {
        return self->GetJulianDayNumber();
    }

    EXPORT double wxDateTime_GetModifiedJulianDayNumber(wxDateTime* self)
    {
        return self->GetModifiedJulianDayNumber();
    }

    EXPORT double wxDateTime_GetRataDie(wxDateTime* self)
    {
        return self->GetRataDie();
    }

    EXPORT void wxDateTime_FromTimezone(wxDateTime* self, int time_zone, int no_dst,
                                        wxDateTime* ref)
    {
        *ref = self->FromTimezone(ToTimeZone(time_zone), no_dst != 0);
    }

    EXPORT void wxDateTime_MakeFromTimezone(wxDateTime* self, int time_zone, int no_dst)
    {
        self->MakeFromTimezone(ToTimeZone(time_zone), no_dst != 0);
    }

    EXPORT void wxDateTime_ToUTC(wxDateTime* self, int no_dst, wxDateTime* ref)
    {
        *ref = self->ToUTC(no_dst != 0);
    }

    EXPORT void wxDateTime_MakeUTC(wxDateTime* self, int no_dst)
    {
        self->MakeUTC(no_dst != 0);
    }

    EXPORT void wxDateTime_FromUTC(wxDateTime* self, int no_dst, wxDateTime* ref)
    {
        *ref = self->FromUTC(no_dst != 0);
    }

    EXPORT void wxDateTime_MakeFromUTC(wxDateTime* self, int no_dst)
    {
        self->MakeFromUTC(no_dst != 0);
    }

    EXPORT int wxDateTime_GetCenturyTZ(wxDateTime* self, int time_zone)
    {
        return self->GetCentury(ToTimeZone(time_zone));
    }

    EXPORT int wxDateTime_GetWeekBasedYear(wxDateTime* self, int time_zone)
    {
        return self->GetWeekBasedYear(ToTimeZone(time_zone));
    }

    EXPORT wxString* wxDateTime_FormatISOCombined(wxDateTime* self, char separator)
    {
        return new wxString(self->FormatISOCombined(separator));
    }

    EXPORT bool wxDateTime_ParseISODate(wxDateTime* self, wxString* text)
    {
        return self->ParseISODate(*text);
    }

    EXPORT bool wxDateTime_ParseISOTime(wxDateTime* self, wxString* text)
    {
        return self->ParseISOTime(*text);
    }

    EXPORT bool wxDateTime_ParseISOCombined(wxDateTime* self, wxString* text, char separator)
    {
        return self->ParseISOCombined(*text, separator);
    }

    EXPORT void wxDateTime_DiffAsDateSpan(wxDateTime* self, wxDateTime* datetime, wxDateSpan* ref)
    {
        *ref = self->DiffAsDateSpan(*datetime);
    }

    EXPORT void wxDateTime_SetFromDOS(wxDateTime* self, uint32_t dos_date_time)
    {
        self->SetFromDOS(static_cast<unsigned long>(dos_date_time));
    }

    EXPORT uint32_t wxDateTime_GetAsDOS(wxDateTime* self)
    {
        return static_cast<uint32_t>(self->GetAsDOS());
    }

    // -----------------------------------------------------------------------
    // wxTimeSpan
    // -----------------------------------------------------------------------

    EXPORT wxTimeSpan* wxTimeSpan_Create(int hours, int minutes)
    {
        return new wxTimeSpan(hours, minutes);
    }

    EXPORT wxTimeSpan* wxTimeSpan_CreateFromHours(int hours)
    {
        return new wxTimeSpan(hours);
    }

    EXPORT wxTimeSpan* wxTimeSpan_CreateFromMinutes(int minutes)
    {
        return new wxTimeSpan(0, minutes);
    }

    EXPORT wxTimeSpan* wxTimeSpan_CreateFromSeconds(int seconds)
    {
        return new wxTimeSpan(0, 0, seconds);
    }

    EXPORT wxTimeSpan* wxTimeSpan_CreateFromMilliseconds(int milliseconds)
    {
        return new wxTimeSpan(0, 0, 0, milliseconds);
    }

    EXPORT wxTimeSpan* wxTimeSpan_CreateFromDays(int days)
    {
        return new wxTimeSpan(wxTimeSpan::Days(days));
    }

    EXPORT wxTimeSpan* wxTimeSpan_CreateFromWeeks(int weeks)
    {
        return new wxTimeSpan(wxTimeSpan::Weeks(weeks));
    }

    EXPORT void wxTimeSpan_Delete(wxTimeSpan* self)
    {
        delete self;
    }

    EXPORT void wxTimeSpan_Add(wxTimeSpan* self, wxTimeSpan* diff, wxTimeSpan* ref)
    {
        *ref = self->Add(*diff);
    }

    EXPORT void wxTimeSpan_AddInPlace(wxTimeSpan* self, wxTimeSpan* diff)
    {
        self->Add(*diff);
    }

    EXPORT void wxTimeSpan_Subtract(wxTimeSpan* self, wxTimeSpan* diff, wxTimeSpan* ref)
    {
        *ref = self->Subtract(*diff);
    }

    EXPORT void wxTimeSpan_SubtractInPlace(wxTimeSpan* self, wxTimeSpan* diff)
    {
        self->Subtract(*diff);
    }

    EXPORT void wxTimeSpan_Multiply(wxTimeSpan* self, int factor, wxTimeSpan* ref)
    {
        *ref = self->Multiply(factor);
    }

    EXPORT void wxTimeSpan_MultiplyInPlace(wxTimeSpan* self, int factor)
    {
        self->Multiply(factor);
    }

    EXPORT void wxTimeSpan_Negate(wxTimeSpan* self, wxTimeSpan* ref)
    {
        *ref = self->Negate();
    }

    EXPORT void wxTimeSpan_NegateInPlace(wxTimeSpan* self)
    {
        self->Neg();
    }

    EXPORT void wxTimeSpan_Abs(wxTimeSpan* self, wxTimeSpan* ref)
    {
        *ref = self->Abs();
    }

    EXPORT bool wxTimeSpan_IsNull(wxTimeSpan* self)
    {
        return self->IsNull();
    }

    EXPORT bool wxTimeSpan_IsPositive(wxTimeSpan* self)
    {
        return self->IsPositive();
    }

    EXPORT bool wxTimeSpan_IsNegative(wxTimeSpan* self)
    {
        return self->IsNegative();
    }

    EXPORT bool wxTimeSpan_IsEqualTo(wxTimeSpan* self, wxTimeSpan* other)
    {
        return self->IsEqualTo(*other);
    }

    EXPORT bool wxTimeSpan_IsLongerThan(wxTimeSpan* self, wxTimeSpan* other)
    {
        return self->IsLongerThan(*other);
    }

    EXPORT bool wxTimeSpan_IsShorterThan(wxTimeSpan* self, wxTimeSpan* other)
    {
        return self->IsShorterThan(*other);
    }

    EXPORT int wxTimeSpan_GetWeeks(wxTimeSpan* self)
    {
        return self->GetWeeks();
    }

    EXPORT int wxTimeSpan_GetDays(wxTimeSpan* self)
    {
        return self->GetDays();
    }

    EXPORT int wxTimeSpan_GetHours(wxTimeSpan* self)
    {
        return self->GetHours();
    }

    EXPORT int wxTimeSpan_GetMinutes(wxTimeSpan* self)
    {
        return self->GetMinutes();
    }

    EXPORT int wxTimeSpan_GetSeconds(wxTimeSpan* self)
    {
        return static_cast<int>(self->GetSeconds().GetValue());
    }

    EXPORT int wxTimeSpan_GetMilliseconds(wxTimeSpan* self)
    {
        return static_cast<int>(self->GetMilliseconds().GetValue());
    }

    EXPORT int wxTimeSpan_GetValue(wxTimeSpan* self)
    {
        return static_cast<int>(self->GetValue().GetValue());
    }

    EXPORT wxString* wxTimeSpan_Format(wxTimeSpan* self, wxString* format)
    {
        return new wxString(self->Format(*format));
    }

    // -----------------------------------------------------------------------
    // wxDateSpan
    // -----------------------------------------------------------------------

    EXPORT wxDateSpan* wxDateSpan_Create(int years, int months)
    {
        return new wxDateSpan(years, months);
    }

    EXPORT wxDateSpan* wxDateSpan_CreateFromYears(int years)
    {
        return new wxDateSpan(wxDateSpan::Years(years));
    }

    EXPORT wxDateSpan* wxDateSpan_CreateFromMonths(int months)
    {
        return new wxDateSpan(wxDateSpan::Months(months));
    }

    EXPORT wxDateSpan* wxDateSpan_CreateFromWeeks(int weeks)
    {
        return new wxDateSpan(wxDateSpan::Weeks(weeks));
    }

    EXPORT wxDateSpan* wxDateSpan_CreateFromDays(int days)
    {
        return new wxDateSpan(wxDateSpan::Days(days));
    }

    EXPORT void wxDateSpan_Delete(wxDateSpan* self)
    {
        delete self;
    }

    EXPORT void wxDateSpan_SetYears(wxDateSpan* self, int years)
    {
        self->SetYears(years);
    }

    EXPORT void wxDateSpan_SetMonths(wxDateSpan* self, int months)
    {
        self->SetMonths(months);
    }

    EXPORT void wxDateSpan_SetWeeks(wxDateSpan* self, int weeks)
    {
        self->SetWeeks(weeks);
    }

    EXPORT void wxDateSpan_SetDays(wxDateSpan* self, int days)
    {
        self->SetDays(days);
    }

    EXPORT int wxDateSpan_GetYears(wxDateSpan* self)
    {
        return self->GetYears();
    }

    EXPORT int wxDateSpan_GetMonths(wxDateSpan* self)
    {
        return self->GetMonths();
    }

    EXPORT int wxDateSpan_GetTotalMonths(wxDateSpan* self)
    {
        return self->GetTotalMonths();
    }

    EXPORT int wxDateSpan_GetWeeks(wxDateSpan* self)
    {
        return self->GetWeeks();
    }

    EXPORT int wxDateSpan_GetDays(wxDateSpan* self)
    {
        return self->GetDays();
    }

    EXPORT int wxDateSpan_GetTotalDays(wxDateSpan* self)
    {
        return self->GetTotalDays();
    }

    EXPORT void wxDateSpan_Add(wxDateSpan* self, wxDateSpan* other, wxDateSpan* ref)
    {
        *ref = self->Add(*other);
    }

    EXPORT void wxDateSpan_AddInPlace(wxDateSpan* self, wxDateSpan* other)
    {
        self->Add(*other);
    }

    EXPORT void wxDateSpan_Subtract(wxDateSpan* self, wxDateSpan* other, wxDateSpan* ref)
    {
        *ref = self->Subtract(*other);
    }

    EXPORT void wxDateSpan_SubtractInPlace(wxDateSpan* self, wxDateSpan* other)
    {
        self->Subtract(*other);
    }

    EXPORT void wxDateSpan_Negate(wxDateSpan* self, wxDateSpan* ref)
    {
        *ref = self->Negate();
    }

    EXPORT void wxDateSpan_NegateInPlace(wxDateSpan* self)
    {
        self->Neg();
    }

    EXPORT void wxDateSpan_Multiply(wxDateSpan* self, int factor, wxDateSpan* ref)
    {
        *ref = self->Multiply(factor);
    }

    EXPORT void wxDateSpan_MultiplyInPlace(wxDateSpan* self, int factor)
    {
        self->Multiply(factor);
    }

    EXPORT bool wxDateSpan_IsEqualTo(wxDateSpan* self, wxDateSpan* other)
    {
        return *self == *other;
    }

    // -----------------------------------------------------------------------
    // wxLocale
    // -----------------------------------------------------------------------

    EXPORT bool wxLocale_Init(wxLocale* self, int language, int flags)
    {
        return self->Init(language, flags);
    }

    EXPORT bool wxLocale_InitFromName(wxLocale* self, wxString* name, wxString* short_name,
                                      wxString* locale, bool load_default)
    {
        return self->Init(*name, *short_name, *locale, load_default);
    }

    EXPORT int wxLocale_GetLanguage(wxLocale* self)
    {
        return self->GetLanguage();
    }

    EXPORT wxString* wxLocale_GetSysName(wxLocale* self)
    {
        return new wxString(self->GetSysName());
    }

    EXPORT wxString* wxLocale_GetCanonicalName(wxLocale* self)
    {
        return new wxString(self->GetCanonicalName());
    }

    EXPORT wxString* wxLocale_GetHeaderValue(wxLocale* self, wxString* header, wxString* domain)
    {
        return new wxString(self->GetHeaderValue(*header, *domain));
    }

    EXPORT wxString* wxLocale_GetPluralString(wxLocale* self, wxString* orig_string,
                                              wxString* plural_string, int count, wxString* domain)
    {
        return new wxString(
            self->GetString(*orig_string, *plural_string, static_cast<unsigned>(count), *domain));
    }

    EXPORT int wxLocale_GetSystemLanguage()
    {
        return wxLocale::GetSystemLanguage();
    }

    EXPORT int wxLocale_GetSystemEncoding()
    {
        return static_cast<int>(wxLocale::GetSystemEncoding());
    }

    EXPORT wxString* wxLocale_GetSystemEncodingName()
    {
        return new wxString(wxLocale::GetSystemEncodingName());
    }

    EXPORT wxString* wxLocale_GetInfo(int index, int category)
    {
        return new wxString(wxLocale::GetInfo(static_cast<wxLocaleInfo>(index),
                                              static_cast<wxLocaleCategory>(category)));
    }

    EXPORT wxString* wxLocale_GetOSInfo(int index, int category)
    {
        return new wxString(wxLocale::GetOSInfo(static_cast<wxLocaleInfo>(index),
                                                static_cast<wxLocaleCategory>(category)));
    }

    EXPORT bool wxLocale_IsAvailable(int language)
    {
        return wxLocale::IsAvailable(language);
    }

    EXPORT wxString* wxLocale_GetLanguageName(int language)
    {
        return new wxString(wxLocale::GetLanguageName(language));
    }

    EXPORT wxString* wxLocale_GetLanguageCanonicalName(int language)
    {
        return new wxString(wxLocale::GetLanguageCanonicalName(language));
    }

    // -----------------------------------------------------------------------
    // wxUILocale
    // -----------------------------------------------------------------------

    EXPORT wxUILocale* wxUILocale_CreateFromTag(wxString* tag)
    {
        return new wxUILocale(wxUILocale::FromTag(*tag));
    }

    EXPORT wxUILocale* wxUILocale_GetCurrent()
    {
        return new wxUILocale(wxUILocale::GetCurrent());
    }

    EXPORT void wxUILocale_Delete(wxUILocale* self)
    {
        delete self;
    }

    EXPORT bool wxUILocale_UseLocaleName(wxString* locale_name)
    {
        return wxUILocale::UseLocaleName(*locale_name);
    }

    EXPORT bool wxUILocale_IsSupported(wxUILocale* self)
    {
        return self->IsSupported();
    }

    EXPORT bool wxUILocale_IsDefault(wxUILocale* self)
    {
        return self->IsDefault();
    }

    EXPORT wxString* wxUILocale_GetName(wxUILocale* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT wxString* wxUILocale_GetLocaleTag(wxUILocale* self)
    {
        return new wxString(self->GetLocaleId().GetTag());
    }

    EXPORT wxString* wxUILocale_GetLocalizedName(wxUILocale* self, int name, int form)
    {
        return new wxString(self->GetLocalizedName(static_cast<wxLocaleName>(name),
                                                   static_cast<wxLocaleForm>(form)));
    }

    EXPORT wxString* wxUILocale_GetMonthName(wxUILocale* self, int month, int form)
    {
        return new wxString(
            self->GetMonthName(static_cast<wxDateTime::Month>(month),
                               wxDateTime::NameForm(static_cast<wxDateTime::NameFlags>(form))));
    }

    EXPORT wxString* wxUILocale_GetWeekDayName(wxUILocale* self, int weekday, int form)
    {
        return new wxString(
            self->GetWeekDayName(static_cast<wxDateTime::WeekDay>(weekday),
                                 wxDateTime::NameForm(static_cast<wxDateTime::NameFlags>(form))));
    }

    EXPORT int wxUILocale_GetLayoutDirection(wxUILocale* self)
    {
        return static_cast<int>(self->GetLayoutDirection());
    }

    EXPORT wxString* wxUILocale_GetCurrencySymbol(wxUILocale* self)
    {
        return new wxString(self->GetCurrencySymbol());
    }

    EXPORT wxString* wxUILocale_GetCurrencyCode(wxUILocale* self)
    {
        return new wxString(self->GetCurrencyCode());
    }

    EXPORT int wxUILocale_GetCurrencySymbolPosition(wxUILocale* self)
    {
        return static_cast<int>(self->GetCurrencySymbolPosition());
    }

    EXPORT int wxUILocale_UsesMetricSystem(wxUILocale* self)
    {
        return static_cast<int>(self->UsesMetricSystem());
    }

    EXPORT int wxUILocale_CompareStrings(wxUILocale* self, wxString* lhs, wxString* rhs, int flags)
    {
        return self->CompareStrings(*lhs, *rhs, flags);
    }

    EXPORT wxString* wxUILocale_GetSystemLocaleTag()
    {
        return new wxString(wxUILocale::GetSystemLocaleId().GetTag());
    }

    EXPORT int wxUILocale_GetSystemLanguage()
    {
        return wxUILocale::GetSystemLanguage();
    }

    EXPORT int wxUILocale_GetSystemLocale()
    {
        return wxUILocale::GetSystemLocale();
    }

    EXPORT wxString* wxUILocale_GetLanguageName(int language)
    {
        return new wxString(wxUILocale::GetLanguageName(language));
    }

    EXPORT wxString* wxUILocale_GetLanguageCanonicalName(int language)
    {
        return new wxString(wxUILocale::GetLanguageCanonicalName(language));
    }

    // -----------------------------------------------------------------------
    // wxTranslations
    // -----------------------------------------------------------------------

    EXPORT wxTranslations* wxTranslations_Create()
    {
        return new wxTranslations();
    }

    EXPORT void wxTranslations_Delete(wxTranslations* self)
    {
        delete self;
    }

    EXPORT wxTranslations* wxTranslations_Get()
    {
        return wxTranslations::Get();
    }

    EXPORT void wxTranslations_Set(wxTranslations* translations)
    {
        wxTranslations::Set(translations);
    }

    EXPORT void wxTranslations_SetLanguage(wxTranslations* self, int language)
    {
        self->SetLanguage(static_cast<wxLanguage>(language));
    }

    EXPORT void wxTranslations_SetLanguageName(wxTranslations* self, wxString* language)
    {
        self->SetLanguage(*language);
    }

    EXPORT wxArrayString* wxTranslations_GetAvailableTranslations(wxTranslations* self,
                                                                  wxString* domain)
    {
        return new wxArrayString(self->GetAvailableTranslations(*domain));
    }

    EXPORT wxString* wxTranslations_GetBestAvailableTranslation(wxTranslations* self,
                                                                wxString* domain)
    {
        return new wxString(self->GetBestAvailableTranslation(*domain));
    }

    EXPORT wxString* wxTranslations_GetBestTranslation(wxTranslations* self, wxString* domain,
                                                       int msg_id_language)
    {
        return new wxString(
            self->GetBestTranslation(*domain, static_cast<wxLanguage>(msg_id_language)));
    }

    EXPORT wxString* wxTranslations_GetBestTranslationForName(wxTranslations* self,
                                                              wxString* domain,
                                                              wxString* msg_id_language)
    {
        return new wxString(self->GetBestTranslation(*domain, *msg_id_language));
    }

    EXPORT bool wxTranslations_AddAvailableCatalog(wxTranslations* self, wxString* domain,
                                                   int msg_id_language)
    {
        return self->AddAvailableCatalog(*domain, static_cast<wxLanguage>(msg_id_language));
    }

    EXPORT bool wxTranslations_AddStdCatalog(wxTranslations* self)
    {
        return self->AddStdCatalog();
    }

    EXPORT bool wxTranslations_AddCatalog(wxTranslations* self, wxString* domain,
                                          int msg_id_language)
    {
        return self->AddCatalog(*domain, static_cast<wxLanguage>(msg_id_language));
    }

    EXPORT bool wxTranslations_IsLoaded(wxTranslations* self, wxString* domain)
    {
        return self->IsLoaded(*domain);
    }

    EXPORT wxString* wxTranslations_GetTranslatedString(wxTranslations* self, wxString* text,
                                                        wxString* domain, wxString* context)
    {
        const wxString* translated = self->GetTranslatedString(*text, *domain, *context);
        if (translated == nullptr)
        {
            return nullptr;
        }
        return new wxString(*translated);
    }

    EXPORT wxString* wxTranslations_GetHeaderValue(wxTranslations* self, wxString* header,
                                                   wxString* domain)
    {
        return new wxString(self->GetHeaderValue(*header, *domain));
    }

    EXPORT wxString* wxTranslations_GetUntranslatedString(wxString* text)
    {
        return new wxString(wxTranslations::GetUntranslatedString(*text));
    }

    // -----------------------------------------------------------------------
    // wxNumberFormatter
    // -----------------------------------------------------------------------

    EXPORT wxString* wxNumberFormatter_ToStringLong(long value, int style)
    {
        return new wxString(wxNumberFormatter::ToString(value, style));
    }

    EXPORT wxString* wxNumberFormatter_Format(wxString* format, double value)
    {
        return new wxString(wxNumberFormatter::Format(*format, value));
    }

    EXPORT bool wxNumberFormatter_FromStringLong(wxString* text, long* value)
    {
        return wxNumberFormatter::FromString(*text, value);
    }

    EXPORT bool wxNumberFormatter_FromStringDouble(wxString* text, double* value)
    {
        return wxNumberFormatter::FromString(*text, value);
    }

    EXPORT void wxNumberFormatter_RemoveTrailingZeroes(wxString* text)
    {
        wxNumberFormatter::RemoveTrailingZeroes(*text);
    }

    EXPORT wxString* wxNumberFormatter_RemoveCurrencySymbolOrCode(wxString* text, int style)
    {
        return new wxString(wxNumberFormatter::RemoveCurrencySymbolOrCode(*text, style));
    }

    // -----------------------------------------------------------------------
    // wxConfigBase
    // -----------------------------------------------------------------------

    EXPORT void wxConfigBase_DontCreateOnDemand()
    {
        wxConfigBase::DontCreateOnDemand();
    }

    EXPORT long wxConfigBase_ReadLong(wxConfigBase* self, wxString* key, long def_val)
    {
        return self->ReadLong(*key, def_val);
    }

    // -----------------------------------------------------------------------
    // wxFileConfig
    // -----------------------------------------------------------------------

    EXPORT wxFileConfig* wxFileConfig_CreateFor(wxString* app_name, wxString* vendor_name,
                                                wxString* local_filename, wxString* global_filename,
                                                long style)
    {
        return new wxFileConfig(*app_name, *vendor_name, *local_filename, *global_filename, style);
    }

    EXPORT wxString* wxFileConfig_GetGlobalFileName(wxString* file_name)
    {
        return new wxString(wxFileConfig::GetGlobalFileName(*file_name));
    }

    EXPORT wxString* wxFileConfig_GetLocalFileName(wxString* file_name, int style)
    {
        return new wxString(wxFileConfig::GetLocalFileName(*file_name, style));
    }

    EXPORT void wxFileConfig_SetUmask(wxFileConfig* self, int mode)
    {
        self->SetUmask(mode);
    }

    EXPORT bool wxFileConfig_Save(wxFileConfig* self, wxOutputStream* stream)
    {
#if wxUSE_STREAMS
        return self->Save(*stream);
#else
        wxUnusedVar(self);
        wxUnusedVar(stream);
        return false;
#endif
    }

    EXPORT void wxFileConfig_EnableAutoSave(wxFileConfig* self)
    {
        self->EnableAutoSave();
    }

    EXPORT void wxFileConfig_DisableAutoSave(wxFileConfig* self)
    {
        self->DisableAutoSave();
    }

    // -----------------------------------------------------------------------
    // wxCmdLineParser
    // -----------------------------------------------------------------------

    EXPORT wxCmdLineParser* wxCmdLineParser_Create()
    {
        return new wxCmdLineParser();
    }

    EXPORT void wxCmdLineParser_Delete(wxCmdLineParser* self)
    {
        delete self;
    }

    EXPORT void wxCmdLineParser_SetDesc(wxCmdLineParser* self, kwxCmdLineDesc* desc)
    {
        if (desc == nullptr)
        {
            return;
        }
        self->SetDesc(desc->GetDesc());
    }

    EXPORT void wxCmdLineParser_AddSwitch(wxCmdLineParser* self, wxString* name,
                                          wxString* long_name, wxString* description, int flags)
    {
        self->AddSwitch(*name, *long_name, *description, flags);
    }

    EXPORT void wxCmdLineParser_AddOption(wxCmdLineParser* self, wxString* name,
                                          wxString* long_name, wxString* description, int type,
                                          int flags)
    {
        self->AddOption(*name, *long_name, *description, static_cast<wxCmdLineParamType>(type),
                        flags);
    }

    EXPORT void wxCmdLineParser_AddParam(wxCmdLineParser* self, wxString* description, int type,
                                         int flags)
    {
        self->AddParam(*description, static_cast<wxCmdLineParamType>(type), flags);
    }

    EXPORT int wxCmdLineParser_Parse(wxCmdLineParser* self, int argc, void* argv)
    {
        if (argc > 0 && argv != nullptr)
        {
            self->SetCmdLine(argc, static_cast<char**>(argv));
        }
        return self->Parse(false);
    }

    EXPORT int wxCmdLineParser_ParseString(wxCmdLineParser* self, wxString* command_line)
    {
        self->SetCmdLine(*command_line);
        return self->Parse(false);
    }

    EXPORT bool wxCmdLineParser_Found(wxCmdLineParser* self, wxString* name)
    {
        return self->Found(*name);
    }

    EXPORT int wxCmdLineParser_GetParamCount(wxCmdLineParser* self)
    {
        return static_cast<int>(self->GetParamCount());
    }

    EXPORT wxString* wxCmdLineParser_GetParam(wxCmdLineParser* self, int index)
    {
        const size_t param_count = self->GetParamCount();
        if (index < 0 || static_cast<size_t>(index) >= param_count)
        {
            return new wxString();
        }
        return new wxString(self->GetParam(static_cast<size_t>(index)));
    }

    EXPORT wxString* wxCmdLineParser_GetOptionValue(wxCmdLineParser* self, wxString* name)
    {
        wxString value;
        if (!self->Found(*name, &value))
        {
            return nullptr;
        }
        return new wxString(value);
    }

    EXPORT long wxCmdLineParser_GetOptionLong(wxCmdLineParser* self, wxString* name,
                                              long default_value)
    {
        long value = default_value;
        if (!self->Found(*name, &value))
        {
            return default_value;
        }
        return value;
    }

    EXPORT kwxCmdLineDesc* kwxCmdLineDesc_Create()
    {
        return new kwxCmdLineDesc();
    }

    EXPORT void kwxCmdLineDesc_Delete(kwxCmdLineDesc* self)
    {
        delete self;
    }

    EXPORT void kwxCmdLineDesc_AddSwitch(kwxCmdLineDesc* self, wxString* name, wxString* long_name,
                                         wxString* description, int flags)
    {
        self->AddSwitch(*name, *long_name, *description, flags);
    }

    EXPORT void kwxCmdLineDesc_AddOption(kwxCmdLineDesc* self, wxString* name, wxString* long_name,
                                         wxString* description, int type, int flags)
    {
        self->AddOption(*name, *long_name, *description, type, flags);
    }

    EXPORT void kwxCmdLineDesc_AddParam(kwxCmdLineDesc* self, wxString* description, int type,
                                        int flags)
    {
        self->AddParam(*description, type, flags);
    }

    // -----------------------------------------------------------------------
    // wxVariant
    // -----------------------------------------------------------------------

    EXPORT wxVariant* wxVariant_CreateFromBool(bool value, wxString* name)
    {
        return new wxVariant(value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromLong(long value, wxString* name)
    {
        return new wxVariant(value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromDouble(double value, wxString* name)
    {
        return new wxVariant(value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromString(wxString* value, wxString* name)
    {
        return new wxVariant(*value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromDateTime(wxDateTime* value, wxString* name)
    {
        return new wxVariant(*value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromChar(char value, wxString* name)
    {
        return new wxVariant(value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromVoidPtr(void* value, wxString* name)
    {
        return new wxVariant(value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromObject(wxObject* value, wxString* name)
    {
        return new wxVariant(value, *name);
    }

    EXPORT wxVariant* wxVariant_CreateFromArrayString(wxArrayString* value, wxString* name)
    {
        return new wxVariant(*value, *name);
    }

    EXPORT void wxVariant_SetName(wxVariant* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxVariant_GetName(wxVariant* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT bool wxVariant_IsNull(wxVariant* self)
    {
        return self->IsNull();
    }

    EXPORT bool wxVariant_IsType(wxVariant* self, wxString* type)
    {
        return self->IsType(*type);
    }

    EXPORT void wxVariant_MakeNull(wxVariant* self)
    {
        self->MakeNull();
    }

    EXPORT void wxVariant_Clear(wxVariant* self)
    {
        self->Clear();
    }

    EXPORT void wxVariant_SetBool(wxVariant* self, bool value)
    {
        *self = value;
    }

    EXPORT void wxVariant_SetLong(wxVariant* self, long value)
    {
        *self = value;
    }

    EXPORT void wxVariant_SetDouble(wxVariant* self, double value)
    {
        *self = value;
    }

    EXPORT void wxVariant_SetString(wxVariant* self, wxString* value)
    {
        *self = *value;
    }

    EXPORT void wxVariant_SetDateTime(wxVariant* self, wxDateTime* value)
    {
        *self = *value;
    }

    EXPORT void wxVariant_SetVoidPtr(wxVariant* self, void* value)
    {
        *self = value;
    }

    EXPORT void wxVariant_SetObject(wxVariant* self, wxObject* value)
    {
        *self = value;
    }

    EXPORT void wxVariant_SetArrayString(wxVariant* self, wxArrayString* value)
    {
        *self = *value;
    }

    EXPORT char wxVariant_GetChar(wxVariant* self)
    {
        return static_cast<char>(self->GetChar().GetValue());
    }

    EXPORT void* wxVariant_GetVoidPtr(wxVariant* self)
    {
        return self->GetVoidPtr();
    }

    EXPORT wxObject* wxVariant_GetWxObjectPtr(wxVariant* self)
    {
        return self->GetWxObjectPtr();
    }

    EXPORT wxArrayString* wxVariant_GetArrayString(wxVariant* self)
    {
        return new wxArrayString(self->GetArrayString());
    }

    EXPORT int wxVariant_GetCount(wxVariant* self)
    {
        return static_cast<int>(self->GetCount());
    }

    EXPORT void wxVariant_NullList(wxVariant* self)
    {
        self->NullList();
    }

    EXPORT void wxVariant_Append(wxVariant* self, wxVariant* value)
    {
        self->Append(*value);
    }

    EXPORT void wxVariant_Insert(wxVariant* self, wxVariant* value)
    {
        self->Insert(*value);
    }

    EXPORT bool wxVariant_Member(wxVariant* self, wxVariant* value)
    {
        return self->Member(*value);
    }

    EXPORT void wxVariant_ClearList(wxVariant* self)
    {
        self->ClearList();
    }

    EXPORT bool wxVariant_ConvertToLong(wxVariant* self, long* value)
    {
        long converted = 0;
        if (!self->Convert(&converted))
        {
            return false;
        }
        *value = converted;
        return true;
    }

    EXPORT bool wxVariant_ConvertToDouble(wxVariant* self, double* value)
    {
        double converted = 0.0;
        if (!self->Convert(&converted))
        {
            return false;
        }
        *value = converted;
        return true;
    }

    EXPORT bool wxVariant_ConvertToBool(wxVariant* self, int* value)
    {
        bool converted = false;
        if (!self->Convert(&converted))
        {
            return false;
        }
        *value = converted ? 1 : 0;
        return true;
    }
}

// NOLINTEND(bugprone-identical-type-multi-param)
