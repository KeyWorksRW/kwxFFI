#pragma once

// Date/time, locale, config, command-line and variant gap wrappers.
//
// Only the methods that are missing from the existing blocks in `include/kwx_classes.h`,
// `include/kwx_classes_sync.h` and `include/kwx_spec_residual.h` are declared here. kwxgen
// merges repeated `TClassDef`/`TClassDefExtend` blocks by class name, so each block below adds
// methods to the class instead of redefining it.
//
// Profile classification (`.private/coverage_expansion_inventory.md`):
//   * `base-utility` — wxDateTime, wxTimeSpan, wxDateSpan, wxCmdLineParser and the
//     kwxCmdLineDesc helper are in `GuiExcludedClasses()` (`kwxgen/src/profile.cpp`), so the
//     `gui` profile used by Go and Julia does not emit them. The reference closure still keeps
//     a class that a retained class names in a signature — wxDateTime is re-added this way by
//     wxDatePickerCtrl, wxCalendarCtrl, wxFileName, wxFSFile, wxDateEvent and wxDateProperty,
//     which is why `gui` output contains a wxDateTime binding even though the class is listed
//     as excluded.
//   * `gui` — wxLocale, wxUILocale, wxTranslations, wxNumberFormatter, wxConfigBase and
//     wxFileConfig are deliberately kept in the `gui` surface; do not add them to the
//     exclusion list.
//
// Strings are returned as `TClass(wxString)` (a `wxString*` the caller owns) with two
// exceptions that follow the block they extend: wxNumberFormatter keeps its `TString` returns
// in `include/kwx_classes.h`, and the new wxNumberFormatter functions return `wxString*`.
// Methods that expose `TInt64`, `wxUIntPtr` or a wxWidgets struct/enumeration that has no
// stable FFI spelling are skipped; see `.private/deferred_i64.md`.

// ---------------------------------------------------------------------------
// wxDateTime
// ---------------------------------------------------------------------------

// wxDateTime is a value type: the out-parameters marked `ref` receive a copy of the produced
// value, and the instance is never modified by them. `CreateFromTimeT`/`CreateFromJDN` use the
// corresponding wxDateTime constructors. SetFromDOS/GetAsDOS use the packed 32-bit DOS
// date/time format. The MSW SYSTEMTIME helpers are not wrapped.
TClassDef(wxDateTime) void wxDateTime_SetFromTimeT(TSelf(wxDateTime) pObject, time_t ticks);
void wxDateTime_SetFromJDN(TSelf(wxDateTime) pObject, double julian_day);
TClass(wxDateTime) wxDateTime_CreateFromTimeT(time_t ticks);
TClass(wxDateTime) wxDateTime_CreateFromJDN(double julian_day);
TBool wxDateTime_GetFirstWeekDay(int* first_week_day);
TClass(wxString) wxDateTime_GetEnglishMonthName(int month, int flags);
TClass(wxString) wxDateTime_GetEnglishWeekDayName(int weekday, int flags);
void wxDateTime_GetDateOnly(TSelf(wxDateTime) pObject, TClassRef(wxDateTime) ref);
void wxDateTime_SetToYearDay(TSelf(wxDateTime) pObject, int year_day);
void wxDateTime_GetYearDay(TSelf(wxDateTime) pObject, int year_day, TClassRef(wxDateTime) ref);
double wxDateTime_GetJulianDayNumber(TSelf(wxDateTime) pObject);
double wxDateTime_GetModifiedJulianDayNumber(TSelf(wxDateTime) pObject);
double wxDateTime_GetRataDie(TSelf(wxDateTime) pObject);
void wxDateTime_FromTimezone(TSelf(wxDateTime) pObject, int time_zone, int no_dst,
                             TClassRef(wxDateTime) ref);
void wxDateTime_MakeFromTimezone(TSelf(wxDateTime) pObject, int time_zone, int no_dst);
void wxDateTime_ToUTC(TSelf(wxDateTime) pObject, int no_dst, TClassRef(wxDateTime) ref);
void wxDateTime_MakeUTC(TSelf(wxDateTime) pObject, int no_dst);
void wxDateTime_FromUTC(TSelf(wxDateTime) pObject, int no_dst, TClassRef(wxDateTime) ref);
void wxDateTime_MakeFromUTC(TSelf(wxDateTime) pObject, int no_dst);
int wxDateTime_GetCenturyTZ(TSelf(wxDateTime) pObject, int time_zone);
int wxDateTime_GetWeekBasedYear(TSelf(wxDateTime) pObject, int time_zone);
TClass(wxString) wxDateTime_FormatISOCombined(TSelf(wxDateTime) pObject, TChar separator);
TBool wxDateTime_ParseISODate(TSelf(wxDateTime) pObject, TClass(wxString) text);
TBool wxDateTime_ParseISOTime(TSelf(wxDateTime) pObject, TClass(wxString) text);
TBool wxDateTime_ParseISOCombined(TSelf(wxDateTime) pObject, TClass(wxString) text,
                                  TChar separator);
void wxDateTime_DiffAsDateSpan(TSelf(wxDateTime) pObject, TClass(wxDateTime) datetime,
                               TClassRef(wxDateSpan) ref);
void wxDateTime_SetFromDOS(TSelf(wxDateTime) pObject, TUInt32 dos_date_time);
TUInt32 wxDateTime_GetAsDOS(TSelf(wxDateTime) pObject);

// ---------------------------------------------------------------------------
// wxTimeSpan
// ---------------------------------------------------------------------------

// The existing block in `include/kwx_classes.h` is empty, so this block supplies the whole
// surface. Add()/Subtract()/Multiply()/Negate()/Abs() return a new value through `ref`; the
// *InPlace variants mutate the object. The current value does not fit in 32 bits on every
// platform: GetSeconds/GetMilliseconds/GetValue return `int` and truncate — see
// `.private/deferred_i64.md`.
TClassDef(wxTimeSpan) TClass(wxTimeSpan) wxTimeSpan_Create(int hours, int minutes);
TClass(wxTimeSpan) wxTimeSpan_CreateFromHours(int hours);
TClass(wxTimeSpan) wxTimeSpan_CreateFromMinutes(int minutes);
TClass(wxTimeSpan) wxTimeSpan_CreateFromSeconds(int seconds);
TClass(wxTimeSpan) wxTimeSpan_CreateFromMilliseconds(int milliseconds);
TClass(wxTimeSpan) wxTimeSpan_CreateFromDays(int days);
TClass(wxTimeSpan) wxTimeSpan_CreateFromWeeks(int weeks);
void wxTimeSpan_Delete(TSelf(wxTimeSpan) pObject);
void wxTimeSpan_Add(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) diff, TClassRef(wxTimeSpan) ref);
void wxTimeSpan_AddInPlace(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) diff);
void wxTimeSpan_Subtract(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) diff,
                         TClassRef(wxTimeSpan) ref);
void wxTimeSpan_SubtractInPlace(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) diff);
void wxTimeSpan_Multiply(TSelf(wxTimeSpan) pObject, int factor, TClassRef(wxTimeSpan) ref);
void wxTimeSpan_MultiplyInPlace(TSelf(wxTimeSpan) pObject, int factor);
void wxTimeSpan_Negate(TSelf(wxTimeSpan) pObject, TClassRef(wxTimeSpan) ref);
void wxTimeSpan_NegateInPlace(TSelf(wxTimeSpan) pObject);
void wxTimeSpan_Abs(TSelf(wxTimeSpan) pObject, TClassRef(wxTimeSpan) ref);
TBool wxTimeSpan_IsNull(TSelf(wxTimeSpan) pObject);
TBool wxTimeSpan_IsPositive(TSelf(wxTimeSpan) pObject);
TBool wxTimeSpan_IsNegative(TSelf(wxTimeSpan) pObject);
TBool wxTimeSpan_IsEqualTo(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) other);
TBool wxTimeSpan_IsLongerThan(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) other);
TBool wxTimeSpan_IsShorterThan(TSelf(wxTimeSpan) pObject, TClass(wxTimeSpan) other);
int wxTimeSpan_GetWeeks(TSelf(wxTimeSpan) pObject);
int wxTimeSpan_GetDays(TSelf(wxTimeSpan) pObject);
int wxTimeSpan_GetHours(TSelf(wxTimeSpan) pObject);
int wxTimeSpan_GetMinutes(TSelf(wxTimeSpan) pObject);
int wxTimeSpan_GetSeconds(TSelf(wxTimeSpan) pObject);
int wxTimeSpan_GetMilliseconds(TSelf(wxTimeSpan) pObject);
int wxTimeSpan_GetValue(TSelf(wxTimeSpan) pObject);
TClass(wxString) wxTimeSpan_Format(TSelf(wxTimeSpan) pObject, TClass(wxString) format);

// ---------------------------------------------------------------------------
// wxDateSpan
// ---------------------------------------------------------------------------

// A logical date span: weeks and days are separate components, so Create() takes years and
// months only and the remaining components come from the CreateFrom* factories.
// IsEqualTo() exposes wxDateSpan::operator==.
TClassDef(wxDateSpan) TClass(wxDateSpan) wxDateSpan_Create(int years, int months);
TClass(wxDateSpan) wxDateSpan_CreateFromYears(int years);
TClass(wxDateSpan) wxDateSpan_CreateFromMonths(int months);
TClass(wxDateSpan) wxDateSpan_CreateFromWeeks(int weeks);
TClass(wxDateSpan) wxDateSpan_CreateFromDays(int days);
void wxDateSpan_Delete(TSelf(wxDateSpan) pObject);
void wxDateSpan_SetYears(TSelf(wxDateSpan) pObject, int years);
void wxDateSpan_SetMonths(TSelf(wxDateSpan) pObject, int months);
void wxDateSpan_SetWeeks(TSelf(wxDateSpan) pObject, int weeks);
void wxDateSpan_SetDays(TSelf(wxDateSpan) pObject, int days);
int wxDateSpan_GetYears(TSelf(wxDateSpan) pObject);
int wxDateSpan_GetMonths(TSelf(wxDateSpan) pObject);
int wxDateSpan_GetTotalMonths(TSelf(wxDateSpan) pObject);
int wxDateSpan_GetWeeks(TSelf(wxDateSpan) pObject);
int wxDateSpan_GetDays(TSelf(wxDateSpan) pObject);
int wxDateSpan_GetTotalDays(TSelf(wxDateSpan) pObject);
void wxDateSpan_Add(TSelf(wxDateSpan) pObject, TClass(wxDateSpan) other, TClassRef(wxDateSpan) ref);
void wxDateSpan_AddInPlace(TSelf(wxDateSpan) pObject, TClass(wxDateSpan) other);
void wxDateSpan_Subtract(TSelf(wxDateSpan) pObject, TClass(wxDateSpan) other,
                         TClassRef(wxDateSpan) ref);
void wxDateSpan_SubtractInPlace(TSelf(wxDateSpan) pObject, TClass(wxDateSpan) other);
void wxDateSpan_Negate(TSelf(wxDateSpan) pObject, TClassRef(wxDateSpan) ref);
void wxDateSpan_NegateInPlace(TSelf(wxDateSpan) pObject);
void wxDateSpan_Multiply(TSelf(wxDateSpan) pObject, int factor, TClassRef(wxDateSpan) ref);
void wxDateSpan_MultiplyInPlace(TSelf(wxDateSpan) pObject, int factor);
TBool wxDateSpan_IsEqualTo(TSelf(wxDateSpan) pObject, TClass(wxDateSpan) other);

// ---------------------------------------------------------------------------
// wxLocale
// ---------------------------------------------------------------------------

// wxLocale is deprecated in wxWidgets 3.3 but is still the only type that owns a catalog set
// through AddCatalog(); the wrappers keep it available for the bindings that already use it.
// The getters in this block are the ones missing from the existing block; GetSystemLanguage
// and GetInfo also exist as wxUILocale statics below.
TClassDef(wxLocale) TBool wxLocale_Init(TSelf(wxLocale) pObject, int language, int flags);
TBool wxLocale_InitFromName(TSelf(wxLocale) pObject, TClass(wxString) name,
                            TClass(wxString) short_name, TClass(wxString) locale,
                            TBool load_default);
int wxLocale_GetLanguage(TSelf(wxLocale) pObject);
TClass(wxString) wxLocale_GetSysName(TSelf(wxLocale) pObject);
TClass(wxString) wxLocale_GetCanonicalName(TSelf(wxLocale) pObject);
TClass(wxString) wxLocale_GetHeaderValue(TSelf(wxLocale) pObject, TClass(wxString) header,
                                         TClass(wxString) domain);
TClass(wxString)
    wxLocale_GetPluralString(TSelf(wxLocale) pObject, TClass(wxString) orig_string,
                             TClass(wxString) plural_string, int count, TClass(wxString) domain);
int wxLocale_GetSystemLanguage();
int wxLocale_GetSystemEncoding();
TClass(wxString) wxLocale_GetSystemEncodingName();
TClass(wxString) wxLocale_GetInfo(int index, int category);
TClass(wxString) wxLocale_GetOSInfo(int index, int category);
TBool wxLocale_IsAvailable(int language);
TClass(wxString) wxLocale_GetLanguageName(int language);
TClass(wxString) wxLocale_GetLanguageCanonicalName(int language);

// ---------------------------------------------------------------------------
// wxUILocale
// ---------------------------------------------------------------------------

// wxUILocale is a value type. CreateFromTag() and GetCurrent() return a new object the caller
// deletes; the reference returned by wxUILocale::GetCurrent() is copied, never aliased.
// Enumeration-valued results are returned as `int` using the wxWidgets enum values
// (wxLayoutDirection, wxMeasurementSystem, wxCurrencySymbolPosition).
TClassDef(wxUILocale) TClass(wxUILocale) wxUILocale_CreateFromTag(TClass(wxString) tag);
TClass(wxUILocale) wxUILocale_GetCurrent();
void wxUILocale_Delete(TSelf(wxUILocale) pObject);
TBool wxUILocale_UseLocaleName(TClass(wxString) locale_name);
TBool wxUILocale_IsSupported(TSelf(wxUILocale) pObject);
TBool wxUILocale_IsDefault(TSelf(wxUILocale) pObject);
TClass(wxString) wxUILocale_GetName(TSelf(wxUILocale) pObject);
TClass(wxString) wxUILocale_GetLocaleTag(TSelf(wxUILocale) pObject);
TClass(wxString) wxUILocale_GetLocalizedName(TSelf(wxUILocale) pObject, int name, int form);
TClass(wxString) wxUILocale_GetMonthName(TSelf(wxUILocale) pObject, int month, int form);
TClass(wxString) wxUILocale_GetWeekDayName(TSelf(wxUILocale) pObject, int weekday, int form);
int wxUILocale_GetLayoutDirection(TSelf(wxUILocale) pObject);
TClass(wxString) wxUILocale_GetCurrencySymbol(TSelf(wxUILocale) pObject);
TClass(wxString) wxUILocale_GetCurrencyCode(TSelf(wxUILocale) pObject);
int wxUILocale_GetCurrencySymbolPosition(TSelf(wxUILocale) pObject);
int wxUILocale_UsesMetricSystem(TSelf(wxUILocale) pObject);
int wxUILocale_CompareStrings(TSelf(wxUILocale) pObject, TClass(wxString) lhs, TClass(wxString) rhs,
                              int flags);
TClass(wxString) wxUILocale_GetSystemLocaleTag();
int wxUILocale_GetSystemLanguage();
int wxUILocale_GetSystemLocale();
TClass(wxString) wxUILocale_GetLanguageName(int language);
TClass(wxString) wxUILocale_GetLanguageCanonicalName(int language);

// ---------------------------------------------------------------------------
// wxTranslations
// ---------------------------------------------------------------------------

// wxTranslations owns the loaded message catalogs. wxTranslations_Get() returns the global
// object (owned by wxWidgets — never delete it); wxTranslations_Set() takes ownership of its
// argument, so the caller must not delete that object either. Only objects returned by
// wxTranslations_Create() may be deleted. GetTranslatedString() returns nullptr when the
// translation is missing, so the caller can fall back to the original text.
TClassDef(wxTranslations) TClass(wxTranslations) wxTranslations_Create();
void wxTranslations_Delete(TSelf(wxTranslations) pObject);
TClass(wxTranslations) wxTranslations_Get();
void wxTranslations_Set(TClass(wxTranslations) translations);
void wxTranslations_SetLanguage(TSelf(wxTranslations) pObject, int language);
void wxTranslations_SetLanguageName(TSelf(wxTranslations) pObject, TClass(wxString) language);
TClass(wxArrayString)
    wxTranslations_GetAvailableTranslations(TSelf(wxTranslations) pObject, TClass(wxString) domain);
TClass(wxString) wxTranslations_GetBestAvailableTranslation(TSelf(wxTranslations) pObject,
                                                            TClass(wxString) domain);
TClass(wxString) wxTranslations_GetBestTranslation(TSelf(wxTranslations) pObject,
                                                   TClass(wxString) domain, int msg_id_language);
TClass(wxString)
    wxTranslations_GetBestTranslationForName(TSelf(wxTranslations) pObject, TClass(wxString) domain,
                                             TClass(wxString) msg_id_language);
TBool wxTranslations_AddAvailableCatalog(TSelf(wxTranslations) pObject, TClass(wxString) domain,
                                         int msg_id_language);
TBool wxTranslations_AddStdCatalog(TSelf(wxTranslations) pObject);
TBool wxTranslations_AddCatalog(TSelf(wxTranslations) pObject, TClass(wxString) domain,
                                int msg_id_language);
TBool wxTranslations_IsLoaded(TSelf(wxTranslations) pObject, TClass(wxString) domain);
TClass(wxString)
    wxTranslations_GetTranslatedString(TSelf(wxTranslations) pObject, TClass(wxString) text,
                                       TClass(wxString) domain, TClass(wxString) context);
TClass(wxString) wxTranslations_GetHeaderValue(TSelf(wxTranslations) pObject,
                                               TClass(wxString) header, TClass(wxString) domain);
TClass(wxString) wxTranslations_GetUntranslatedString(TClass(wxString) text);

// ---------------------------------------------------------------------------
// wxNumberFormatter
// ---------------------------------------------------------------------------

// wxNumberFormatter is entirely static. These fill the gaps in the existing block; note that
// the pre-existing GetDecimalSeparator/GetThousandsSeparator return a `TString` (a malloc'd
// buffer) while the functions here return an owned `wxString*`. FromStringLong() and
// FromStringDouble() accept the separators produced by ToString. RemoveTrailingZeroes()
// rewrites the caller's `wxString` in place.
TClassDef(wxNumberFormatter) TClass(wxString) wxNumberFormatter_ToStringLong(long value, int style);
TClass(wxString) wxNumberFormatter_Format(TClass(wxString) format, double value);
TBool wxNumberFormatter_FromStringLong(TClass(wxString) text, long* value);
TBool wxNumberFormatter_FromStringDouble(TClass(wxString) text, double* value);
void wxNumberFormatter_RemoveTrailingZeroes(TClass(wxString) text);
TClass(wxString) wxNumberFormatter_RemoveCurrencySymbolOrCode(TClass(wxString) text, int style);

// ---------------------------------------------------------------------------
// wxConfigBase
// ---------------------------------------------------------------------------

// Additional methods for the existing wxConfigBase block; the block gains its wxObject parent
// here so the generated bindings can walk the hierarchy. The binary Read/Write overloads are
// not wrapped: they require wxMemoryBuffer, a base-utility class that would then be pulled
// back into the `gui` profile through the reference closure.
TClassDefExtend(wxConfigBase, wxObject) void wxConfigBase_DontCreateOnDemand();
long wxConfigBase_ReadLong(TSelf(wxConfigBase) pObject, TClass(wxString) key, long def_val);

// ---------------------------------------------------------------------------
// wxFileConfig
// ---------------------------------------------------------------------------

// The existing block only declares the stream constructor. The block gains the wxConfigBase
// parent here, so the inherited read/write surface is available on a wxFileConfig handle.
// CreateFor() mirrors the five-argument constructor; style is a combination of the
// wxCONFIG_USE_* values.
TClassDefExtend(wxFileConfig, wxConfigBase) TClass(wxFileConfig)
    wxFileConfig_CreateFor(TClass(wxString) app_name, TClass(wxString) vendor_name,
                           TClass(wxString) local_filename, TClass(wxString) global_filename,
                           long style);
TClass(wxString) wxFileConfig_GetGlobalFileName(TClass(wxString) file_name);
TClass(wxString) wxFileConfig_GetLocalFileName(TClass(wxString) file_name, int style);
void wxFileConfig_SetUmask(TSelf(wxFileConfig) pObject, int mode);
TBool wxFileConfig_Save(TSelf(wxFileConfig) pObject, TClass(wxOutputStream) stream);
void wxFileConfig_EnableAutoSave(TSelf(wxFileConfig) pObject);
void wxFileConfig_DisableAutoSave(TSelf(wxFileConfig) pObject);

// ---------------------------------------------------------------------------
// wxCmdLineParser
// ---------------------------------------------------------------------------

// wxCmdLineParser copies the switch/option/parameter descriptions it is given, so the parser
// owns its own description once AddSwitch/AddOption/AddParam/SetDesc has returned. The
// kwxCmdLineDesc helper (`include/kwx_helper_cmdline.h`) owns the wxCmdLineEntryDesc table for
// SetDesc(); see that header for the lifetime rules.
//
// Parse() takes the raw argc/argv pair a process received; the wrapper casts argv to char**
// and passes it to wxCmdLineParser::SetCmdLine() before parsing. It returns 0 on success, -1
// when a help option was found and the usage message was shown, and a positive value on a
// syntax error. ParseString() does the same for a single command-line string.
//
// Value types are the wxCmdLineParamType values, flags are combinations of the
// wxCmdLineEntryFlags values, and GetOptionLong() returns `default_value` when the option was
// not found or did not hold a number.
TClassDef(wxCmdLineParser) TClass(wxCmdLineParser) wxCmdLineParser_Create();
void wxCmdLineParser_Delete(TSelf(wxCmdLineParser) pObject);
void wxCmdLineParser_SetDesc(TSelf(wxCmdLineParser) pObject, TClass(kwxCmdLineDesc) desc);
void wxCmdLineParser_AddSwitch(TSelf(wxCmdLineParser) pObject, TClass(wxString) name,
                               TClass(wxString) long_name, TClass(wxString) description, int flags);
void wxCmdLineParser_AddOption(TSelf(wxCmdLineParser) pObject, TClass(wxString) name,
                               TClass(wxString) long_name, TClass(wxString) description, int type,
                               int flags);
void wxCmdLineParser_AddParam(TSelf(wxCmdLineParser) pObject, TClass(wxString) description,
                              int type, int flags);
int wxCmdLineParser_Parse(TSelf(wxCmdLineParser) pObject, int argc, void* argv);
int wxCmdLineParser_ParseString(TSelf(wxCmdLineParser) pObject, TClass(wxString) command_line);
TBool wxCmdLineParser_Found(TSelf(wxCmdLineParser) pObject, TClass(wxString) name);
int wxCmdLineParser_GetParamCount(TSelf(wxCmdLineParser) pObject);
TClass(wxString) wxCmdLineParser_GetParam(TSelf(wxCmdLineParser) pObject, int index);
TClass(wxString)
    wxCmdLineParser_GetOptionValue(TSelf(wxCmdLineParser) pObject, TClass(wxString) name);
long wxCmdLineParser_GetOptionLong(TSelf(wxCmdLineParser) pObject, TClass(wxString) name,
                                   long default_value);

// The kwxCmdLineDesc handle owns a wxCmdLineEntryDesc table for wxCmdLineParser_SetDesc().
// Add every entry first, then pass the handle to SetDesc(). This is a base-utility helper for
// a base-utility class, so it is listed in `GuiExcludedClasses()` with wxCmdLineParser.
TClassDef(kwxCmdLineDesc) TClass(kwxCmdLineDesc) kwxCmdLineDesc_Create();
void kwxCmdLineDesc_Delete(TSelf(kwxCmdLineDesc) pObject);
void kwxCmdLineDesc_AddSwitch(TSelf(kwxCmdLineDesc) pObject, TClass(wxString) name,
                              TClass(wxString) long_name, TClass(wxString) description, int flags);
void kwxCmdLineDesc_AddOption(TSelf(kwxCmdLineDesc) pObject, TClass(wxString) name,
                              TClass(wxString) long_name, TClass(wxString) description, int type,
                              int flags);
void kwxCmdLineDesc_AddParam(TSelf(kwxCmdLineDesc) pObject, TClass(wxString) description, int type,
                             int flags);

// ---------------------------------------------------------------------------
// wxVariant
// ---------------------------------------------------------------------------

// Additional methods for the existing wxVariant block. wxVariant is `base-utility` and is
// excluded from the `gui` profile, but the closure adds it back whenever a retained class
// names it in a signature. The wxVariant long-long accessors and wxVariantData-level methods
// are not wrapped; see `.private/deferred_i64.md`.
TClassDefExtend(wxVariant, wxObject) TClass(wxVariant)
    wxVariant_CreateFromBool(TBool value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromLong(long value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromDouble(double value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromString(TClass(wxString) value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromDateTime(TClass(wxDateTime) value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromChar(TChar value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromVoidPtr(void* value, TClass(wxString) name);
TClass(wxVariant) wxVariant_CreateFromObject(TClass(wxObject) value, TClass(wxString) name);
TClass(wxVariant)
    wxVariant_CreateFromArrayString(TClass(wxArrayString) value, TClass(wxString) name);
void wxVariant_SetName(TSelf(wxVariant) pObject, TClass(wxString) name);
TClass(wxString) wxVariant_GetName(TSelf(wxVariant) pObject);
TBool wxVariant_IsNull(TSelf(wxVariant) pObject);
TBool wxVariant_IsType(TSelf(wxVariant) pObject, TClass(wxString) type);
void wxVariant_MakeNull(TSelf(wxVariant) pObject);
void wxVariant_Clear(TSelf(wxVariant) pObject);
void wxVariant_SetBool(TSelf(wxVariant) pObject, TBool value);
void wxVariant_SetLong(TSelf(wxVariant) pObject, long value);
void wxVariant_SetDouble(TSelf(wxVariant) pObject, double value);
void wxVariant_SetString(TSelf(wxVariant) pObject, TClass(wxString) value);
void wxVariant_SetDateTime(TSelf(wxVariant) pObject, TClass(wxDateTime) value);
void wxVariant_SetVoidPtr(TSelf(wxVariant) pObject, void* value);
void wxVariant_SetObject(TSelf(wxVariant) pObject, TClass(wxObject) value);
void wxVariant_SetArrayString(TSelf(wxVariant) pObject, TClass(wxArrayString) value);
TChar wxVariant_GetChar(TSelf(wxVariant) pObject);
void* wxVariant_GetVoidPtr(TSelf(wxVariant) pObject);
TClass(wxObject) wxVariant_GetWxObjectPtr(TSelf(wxVariant) pObject);
TClass(wxArrayString) wxVariant_GetArrayString(TSelf(wxVariant) pObject);
int wxVariant_GetCount(TSelf(wxVariant) pObject);
void wxVariant_NullList(TSelf(wxVariant) pObject);
void wxVariant_Append(TSelf(wxVariant) pObject, TClass(wxVariant) value);
void wxVariant_Insert(TSelf(wxVariant) pObject, TClass(wxVariant) value);
TBool wxVariant_Member(TSelf(wxVariant) pObject, TClass(wxVariant) value);
void wxVariant_ClearList(TSelf(wxVariant) pObject);
TBool wxVariant_ConvertToLong(TSelf(wxVariant) pObject, long* value);
TBool wxVariant_ConvertToDouble(TSelf(wxVariant) pObject, double* value);
TBool wxVariant_ConvertToBool(TSelf(wxVariant) pObject, int* value);
