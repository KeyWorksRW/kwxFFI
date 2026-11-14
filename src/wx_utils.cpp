#include "kwx_wrapper.h"

#include <wx/busyinfo.h>
#include <wx/cursor.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/generic/choicdgg.h>
#include <wx/math.h>
#include <wx/power.h>
#include <wx/process.h>
#include <wx/stockitem.h>
#include <wx/tipdlg.h>
#include <wx/utils.h>
#include <wx/valnum.h>
#include <wx/versioninfo.h>
#include <wx/wxcrt.h>

#include <cstdio>
#include <vector>

// The wrapper definitions live inside a namespace so that the exported C symbols are allowed to
// reuse the wxWidgets free-function names (wxNow, wxSleep, ...). C language linkage ignores
// namespaces, so the exported symbols are the unqualified names that the bindings look up.
//
// Every call into wxWidgets is qualified with :: because an unqualified call would find the
// wrapper being defined instead of the wxWidgets function.
namespace kwx
{
    extern "C"
    {
        // -------------------------------------------------------------------
        // System information
        // -------------------------------------------------------------------

        EXPORT wxString* wxGetOsDescription()
        {
            return new wxString(::wxGetOsDescription());
        }

        EXPORT int wxGetOsVersion(int* major, int* minor, int* micro)
        {
            return static_cast<int>(::wxGetOsVersion(major, minor, micro));
        }

        EXPORT int wxCheckOsVersion(int major, int minor, int micro)
        {
            return ::wxCheckOsVersion(major, minor, micro);
        }

        EXPORT int wxIsPlatformLittleEndian()
        {
            return ::wxIsPlatformLittleEndian();
        }

        EXPORT int wxIsPlatform64Bit()
        {
            return ::wxIsPlatform64Bit();
        }

        EXPORT wxString* wxGetCpuArchitectureName()
        {
            return new wxString(::wxGetCpuArchitectureName());
        }

        EXPORT wxString* wxGetNativeCpuArchitectureName()
        {
            return new wxString(::wxGetNativeCpuArchitectureName());
        }

        EXPORT wxString* wxNow()
        {
            return new wxString(::wxNow());
        }

        EXPORT wxString* wxGetInstallPrefix()
        {
            return new wxString(::wxGetInstallPrefix());
        }

        EXPORT wxString* wxGetDataDir()
        {
            return new wxString(::wxGetDataDir());
        }

        EXPORT int64_t wxGetFreeMemory()
        {
            return ::wxGetFreeMemory().GetValue();
        }

        EXPORT int wxHandleFatalExceptions([[maybe_unused]] int doit)
        {
#if wxUSE_ON_FATAL_EXCEPTION
            return ::wxHandleFatalExceptions(doit != 0);
#else
            // wxWidgets disables this API for compilers without SEH support, see wx/msw/chkconf.h.
            return false;
#endif
        }

        // -------------------------------------------------------------------
        // GUI and system helpers
        // -------------------------------------------------------------------

        EXPORT int wxGetKeyState(int key)
        {
            return ::wxGetKeyState(static_cast<wxKeyCode>(key));
        }

        EXPORT int wxSetDetectableAutoRepeat(int flag)
        {
            return ::wxSetDetectableAutoRepeat(flag != 0);
        }

        EXPORT void wxGetMousePosition(int* x, int* y)
        {
            ::wxGetMousePosition(x, y);
        }

        EXPORT void wxInfoMessageBox(wxWindow* parent)
        {
            ::wxInfoMessageBox(parent);
        }

        EXPORT void wxRegisterId(int id)
        {
            ::wxRegisterId(id);
        }

        EXPORT int wxGetCurrentId()
        {
            return ::wxGetCurrentId();
        }

        EXPORT int wxNewId()
        {
            return ::wxNewId();
        }

        EXPORT int wxHexToDec(const wxString* buf)
        {
            return ::wxHexToDec(*buf);
        }

        EXPORT wxString* wxDecToHex(int dec)
        {
            return new wxString(::wxDecToHex(static_cast<unsigned char>(dec)));
        }

        EXPORT void wxSecureZeroMemory(void* data, unsigned count)
        {
            ::wxSecureZeroMemory(data, static_cast<size_t>(count));
        }

        // -------------------------------------------------------------------
        // Environment variables
        // -------------------------------------------------------------------

        EXPORT int wxGetEnv(const wxString* var, wxString* value)
        {
            return ::wxGetEnv(*var, value);
        }

        EXPORT int wxSetEnv(const wxString* var, const wxString* value)
        {
            return ::wxSetEnv(*var, *value);
        }

        EXPORT int wxUnsetEnv(const wxString* var)
        {
            return ::wxUnsetEnv(*var);
        }

        EXPORT int wxGetEnvMap(wxArrayString* env_map)
        {
            wxEnvVariableHashMap env_variables;
            if (!::wxGetEnvMap(&env_variables))
            {
                return false;
            }

            for (const auto& [name, value]: env_variables)
            {
                env_map->Add(name + "=" + value);
            }
            return true;
        }

        // -------------------------------------------------------------------
        // User, network and disk information
        // -------------------------------------------------------------------

        EXPORT wxString* wxGetEmailAddress()
        {
            return new wxString(::wxGetEmailAddress());
        }

        EXPORT wxString* wxGetHostName()
        {
            return new wxString(::wxGetHostName());
        }

        EXPORT wxString* wxGetFullHostName()
        {
            return new wxString(::wxGetFullHostName());
        }

        EXPORT wxString* wxGetUserId()
        {
            return new wxString(::wxGetUserId());
        }

        EXPORT wxString* wxGetUserName()
        {
            return new wxString(::wxGetUserName());
        }

        EXPORT wxString* wxGetHomeDir()
        {
            return new wxString(::wxGetHomeDir());
        }

        EXPORT wxString* wxGetUserHome(const wxString* user)
        {
            return new wxString(::wxGetUserHome(*user));
        }

        EXPORT int wxGetDiskSpace(const wxString* path, int64_t* total_bytes, int64_t* free_bytes)
        {
            wxDiskspaceSize_t total_space;
            wxDiskspaceSize_t free_space;
            const bool result = ::wxGetDiskSpace(*path, &total_space, &free_space);
            *total_bytes = total_space.GetValue();
            *free_bytes = free_space.GetValue();
            return result;
        }

        // -------------------------------------------------------------------
        // Process management
        // -------------------------------------------------------------------

        EXPORT long wxExecute(const wxString* command, int flags, wxProcess* process,
                              const wxExecuteEnv* execute_env)
        {
            return ::wxExecute(*command, flags, process, execute_env);
        }

        EXPORT long wxExecuteWithOutput(const wxString* command, wxArrayString* output, int flags,
                                        const wxExecuteEnv* execute_env)
        {
            return ::wxExecute(*command, *output, flags, execute_env);
        }

        EXPORT long wxExecuteWithOutputAndError(const wxString* command, wxArrayString* output,
                                                wxArrayString* errors, int flags,
                                                const wxExecuteEnv* execute_env)
        {
            return ::wxExecute(*command, *output, *errors, flags, execute_env);
        }

        EXPORT long wxExecuteArgv(int count, char** argv, int flags, wxProcess* process,
                                  const wxExecuteEnv* execute_env)
        {
            // wxExecute() expects a nullptr-terminated array, the FFI passes a counted one.
            std::vector<const char*> arguments(argv, argv + count);
            arguments.push_back(nullptr);
            return ::wxExecute(arguments.data(), flags, process, execute_env);
        }

        EXPORT int wxExecuteDDE(const wxString* server, const wxString* topic,
                                const wxString* command)
        {
#if defined(__WINDOWS__) && wxUSE_IPC
            return ::wxExecuteDDE(*server, *topic, *command);
#else
            wxUnusedVar(server);
            wxUnusedVar(topic);
            wxUnusedVar(command);
            return false;
#endif
        }

        EXPORT int wxShutdown(int flags)
        {
            return ::wxShutdown(flags);
        }

        EXPORT int wxKill(long pid, int sig, int* rc, int flags)
        {
            wxKillError kill_error = wxKILL_OK;
            const int result =
                ::wxKill(pid, static_cast<wxSignal>(sig), rc ? &kill_error : nullptr, flags);
            if (rc)
            {
                *rc = static_cast<int>(kill_error);
            }
            return result;
        }

        EXPORT int wxShell(const wxString* command)
        {
            return ::wxShell(*command);
        }

        EXPORT int wxShellWithOutput(const wxString* command, wxArrayString* output)
        {
#if defined(__WINDOWS__)
            // wxWidgets defines the output-capturing wxShell() overload only for the Unix
            // ports (src/unix/utilsunx.cpp); the MSW port has the interactive overload only.
            // Reproduce the Unix behaviour: run the command through the command processor
            // and capture its output.
            //
            // Returns true on success, matching the MSW one-arg wxShell(), which returns
            // wxExecute(...) == 0. The Unix two-arg overload instead returns the raw exit
            // code cast to bool, so this is deliberately not bug-for-bug parity with it.
            wxString shell;
            if (!::wxGetEnv("COMSPEC", &shell))
            {
                shell = "\\COMMAND.COM";
            }
            const wxString full_command = shell + " /c " + *command;
            return ::wxExecute(full_command, *output) == 0;
#else
            return ::wxShell(*command, *output);
#endif
        }

        EXPORT void wxSleep(int seconds)
        {
            ::wxSleep(seconds);
        }

        EXPORT void wxMilliSleep(unsigned long milliseconds)
        {
            ::wxMilliSleep(milliseconds);
        }

        EXPORT void wxMicroSleep(unsigned long microseconds)
        {
            ::wxMicroSleep(microseconds);
        }

        EXPORT unsigned long wxGetProcessId()
        {
            return ::wxGetProcessId();
        }

        // -------------------------------------------------------------------
        // GUI helpers
        // -------------------------------------------------------------------

        EXPORT int wxLaunchDefaultBrowser(const wxString* url, int flags)
        {
            return ::wxLaunchDefaultBrowser(*url, flags);
        }

        EXPORT int wxLaunchDefaultApplication(const wxString* path, int flags)
        {
            return ::wxLaunchDefaultApplication(*path, flags);
        }

        EXPORT wxString* wxStripMenuCodes(const wxString* text, int flags)
        {
            return new wxString(::wxStripMenuCodes(*text, flags));
        }

        EXPORT int wxFindMenuItemId(wxFrame* frame, const wxString* menu_string,
                                    const wxString* item_string)
        {
            return ::wxFindMenuItemId(frame, *menu_string, *item_string);
        }

        EXPORT wxWindow* wxGenericFindWindowAtPoint(int x, int y)
        {
            return ::wxGenericFindWindowAtPoint(wxPoint(x, y));
        }

        EXPORT wxWindow* wxFindWindowAtPoint(int x, int y)
        {
            return ::wxFindWindowAtPoint(wxPoint(x, y));
        }

        EXPORT wxWindow* wxFindWindowByLabel(const wxString* title, wxWindow* parent)
        {
            return ::wxFindWindowByLabel(*title, parent);
        }

        EXPORT wxWindow* wxFindWindowByName(const wxString* name, wxWindow* parent)
        {
            return ::wxFindWindowByName(*name, parent);
        }

        EXPORT int wxSafeYield(wxWindow* window, int only_if_needed)
        {
            return ::wxSafeYield(window, only_if_needed != 0);
        }

        EXPORT void wxEnableTopLevelWindows(int enable)
        {
            ::wxEnableTopLevelWindows(enable != 0);
        }

        EXPORT int wxCheckForInterrupt(wxWindow* window)
        {
            return ::wxCheckForInterrupt(window);
        }

        EXPORT void wxFlushEvents()
        {
#if defined(__WXX11__)
            ::wxFlushEvents();
#else
            // wxWidgets implements wxFlushEvents() only in the wxX11 port (src/x11/utils.cpp);
            // the MSW, GTK and macOS ports declare it without providing a definition.
            // Consume pending events through the active event loop instead.
            while (wxTheApp && wxTheApp->Pending())
            {
                if (!wxTheApp->Dispatch())
                {
                    break;
                }
            }
#endif
        }

        EXPORT int wxYield()
        {
            return ::wxYield();
        }

        EXPORT int wxYieldIfNeeded()
        {
            return ::wxYieldIfNeeded();
        }

        EXPORT int wxMSWIsOnSecureScreen()
        {
#ifdef __WINDOWS__
            return ::wxMSWIsOnSecureScreen();
#else
            return false;
#endif
        }

        // -------------------------------------------------------------------
        // File selectors and stock items (wxFunctions surface)
        // -------------------------------------------------------------------

        EXPORT wxString* wxFileSelector(const wxString* message, const wxString* default_path,
                                        const wxString* default_filename,
                                        const wxString* default_extension, const wxString* wildcard,
                                        int flags, wxWindow* parent, int x, int y)
        {
            return new wxString(::wxFileSelector(*message, *default_path, *default_filename,
                                                 *default_extension, *wildcard, flags, parent, x,
                                                 y));
        }

        EXPORT wxString* wxFileSelectorEx(const wxString* message, const wxString* default_path,
                                          const wxString* default_filename,
                                          int* index_default_extension, const wxString* wildcard,
                                          int flags, wxWindow* parent, int x, int y)
        {
            return new wxString(::wxFileSelectorEx(*message, *default_path, *default_filename,
                                                   index_default_extension, *wildcard, flags,
                                                   parent, x, y));
        }

        EXPORT wxString* wxLoadFileSelector(const wxString* what, const wxString* extension,
                                            const wxString* default_name, wxWindow* parent)
        {
            return new wxString(::wxLoadFileSelector(*what, *extension, *default_name, parent));
        }

        EXPORT wxString* wxSaveFileSelector(const wxString* what, const wxString* extension,
                                            const wxString* default_name, wxWindow* parent)
        {
            return new wxString(::wxSaveFileSelector(*what, *extension, *default_name, parent));
        }

        EXPORT int wxIsStockID(int id)
        {
            return ::wxIsStockID(static_cast<wxWindowID>(id));
        }

        EXPORT int wxIsStockLabel(int id, const wxString* label)
        {
            return ::wxIsStockLabel(static_cast<wxWindowID>(id), *label);
        }

        EXPORT wxString* wxGetStockLabel(int id, long flags)
        {
            return new wxString(::wxGetStockLabel(static_cast<wxWindowID>(id), flags));
        }

        EXPORT wxAcceleratorEntry* wxGetStockAccelerator(int id)
        {
            return new wxAcceleratorEntry(::wxGetStockAccelerator(static_cast<wxWindowID>(id)));
        }

        EXPORT wxString* wxGetStockHelpString(int id, int client)
        {
            return new wxString(::wxGetStockHelpString(
                static_cast<wxWindowID>(id), static_cast<wxStockHelpStringClient>(client)));
        }

        // -------------------------------------------------------------------
        // Leaf free functions (Phase 2: .private/port/fix_worklist.json)
        // -------------------------------------------------------------------

        EXPORT void* wxCheckDynamicCast(wxObject* obj, wxClassInfo* class_info)
        {
            return ::wxCheckDynamicCast(obj, class_info);
        }

        // wxCheckCast() is a template, so no instance can be named here. The ABI contract of
        // the sample-facing function is the identity cast wxStaticCast() performs after its
        // debug-only assertion.
        EXPORT void* wxCheckCast(wxObject* obj, [[maybe_unused]] wxClassInfo* class_info)
        {
            return obj;
        }

        EXPORT void* wxGetApp()
        {
            // wxGetApp() is a macro over wxApp::GetInstance() and is therefore not a
            // symbol; the instance getter is the ABI-stable spelling of the same value.
            return wxApp::GetInstance();
        }

        EXPORT void wxInitAllImageHandlers()
        {
            ::wxInitAllImageHandlers();
        }

        EXPORT void wxUnusedVar([[maybe_unused]] void* value)
        {
            // Intentionally empty: wxUnusedVar() exists only to silence unused-variable
            // warnings, so there is no value for the binding to observe.
        }

        EXPORT int wxGetSingleChoiceIndex(const wxString* message, const wxString* caption,
                                          const wxString* choices, int count, wxWindow* parent)
        {
            return ::wxGetSingleChoiceIndex(*message, *caption, count, choices, parent);
        }

        EXPORT int wxGetSingleChoiceIndexEx(const wxString* message, const wxString* caption, int n,
                                            const wxArrayString* choices, wxWindow* parent, int x,
                                            int y, int centre, int width, int height,
                                            int initialSelection)
        {
            std::vector<wxString> items;
            const size_t item_count = choices->GetCount();
            items.reserve(item_count);
            for (size_t index = 0; index < item_count; ++index)
            {
                items.push_back((*choices)[index]);
            }
            const wxString* strings = items.empty() ? nullptr : items.data();
            return ::wxGetSingleChoiceIndex(*message, *caption, n, strings, parent, x, y,
                                            centre != 0, width, height, initialSelection);
        }

        EXPORT void wxBeginBusyCursor()
        {
            ::wxBeginBusyCursor();
        }

        EXPORT void wxEndBusyCursor()
        {
            ::wxEndBusyCursor();
        }

        EXPORT wxString* wxJoin(const wxArrayString* array, int separator)
        {
            return new wxString(::wxJoin(*array, static_cast<wxChar>(separator)));
        }

        EXPORT int wxAtoi(const wxString* str)
        {
            return ::wxAtoi(*str);
        }

        EXPORT wxSize* wxGetDisplaySize()
        {
            return new wxSize(::wxGetDisplaySize());
        }

        EXPORT wxWindow* wxGetTopLevelParent(wxWindow* window)
        {
            return ::wxGetTopLevelParent(window);
        }

        EXPORT int wxIsprint(int character)
        {
            return ::wxIsprint(wxUniChar(static_cast<wxUint32>(character)));
        }

        EXPORT int wxRound(double value)
        {
            return ::wxRound(value);
        }

        EXPORT void wxWakeUpIdle()
        {
            ::wxWakeUpIdle();
        }

        EXPORT void wxBell()
        {
            ::wxBell();
        }

        EXPORT double wxDegToRad(double degrees)
        {
            return ::wxDegToRad(degrees);
        }

        EXPORT char* wxFgets(char* buffer, int size, void* stream)
        {
            return ::wxFgets(buffer, size, static_cast<FILE*>(stream));
        }

        EXPORT wxString* wxGetCwd()
        {
            return new wxString(::wxGetCwd());
        }

        EXPORT int wxIsMainThread()
        {
            return ::wxIsMainThread();
        }

        EXPORT int wxNewEventType()
        {
            return static_cast<int>(::wxNewEventType());
        }

        EXPORT void wxQueueEvent(wxEvtHandler* dest, wxEvent* event)
        {
            ::wxQueueEvent(dest, event);
        }

        EXPORT void wxSetCursor(const wxCursor* cursors)
        {
            if (!cursors)
            {
                return;
            }
            // wxSetCursor() takes a wxCursorBundle, which has no single-cursor constructor,
            // so the phone call is made through the owner that stores the bundle.
            ::wxSetCursor(wxCursorBundle(*cursors));
        }

        EXPORT wxArrayString* wxSplit(const wxString* str, int separator)
        {
            return new wxArrayString(::wxSplit(*str, static_cast<wxChar>(separator)));
        }

        EXPORT int wxStrcmp(const wxString* first, const wxString* second)
        {
            return ::wxStrcmp(*first, *second);
        }

        EXPORT void wxSwap(void* first, void* second, size_t size)
        {
            // Byte-wise swap: the binding has no type information, only the element size.
            unsigned char* first_bytes = static_cast<unsigned char*>(first);
            unsigned char* second_bytes = static_cast<unsigned char*>(second);
            for (size_t i = 0; i < size; ++i)
            {
                const unsigned char temporary = first_bytes[i];
                first_bytes[i] = second_bytes[i];
                second_bytes[i] = temporary;
            }
        }

        EXPORT void* wxUIntToPtr(size_t value)
        {
            return ::wxUIntToPtr(static_cast<wxUIntPtr>(value));
        }

        EXPORT void* wxCreateFileTipProvider(const wxString* filename, int current_tip)
        {
            return ::wxCreateFileTipProvider(*filename, static_cast<size_t>(current_tip));
        }

        EXPORT wxString* wxDirSelector(const wxString* message, const wxString* default_path,
                                       long style, int x, int y, wxWindow* parent)
        {
            return new wxString(
                ::wxDirSelector(*message, *default_path, style, wxPoint(x, y), parent));
        }

        EXPORT int wxFileExists(const wxString* filename)
        {
            return ::wxFileExists(*filename);
        }

        EXPORT wxWindow* wxFindFocusDescendant(wxWindow* ancestor)
        {
            return ::wxFindFocusDescendant(ancestor);
        }

        EXPORT int wxGetBatteryState()
        {
            return static_cast<int>(::wxGetBatteryState());
        }

        EXPORT wxRect* wxGetClientDisplayRect()
        {
            return new wxRect(::wxGetClientDisplayRect());
        }

        EXPORT long wxGetLocalTime()
        {
            return ::wxGetLocalTime();
        }

        EXPORT int wxGetPowerType()
        {
            return static_cast<int>(::wxGetPowerType());
        }

        EXPORT int wxGetSelectedChoices(void* selections, const wxString* choices, int count,
                                        const wxString* message, const wxString* caption,
                                        wxWindow* parent)
        {
            return ::wxGetSelectedChoices(*static_cast<wxArrayInt*>(selections), *message, *caption,
                                          count, choices, parent);
        }

        EXPORT int wxGetSelectedChoicesEx(void* selections, const wxString* message,
                                          const wxString* caption, int n,
                                          const wxArrayString* choices, wxWindow* parent, int x,
                                          int y, int centre, int width, int height)
        {
            std::vector<wxString> items;
            const size_t item_count = choices->GetCount();
            items.reserve(item_count);
            for (size_t index = 0; index < item_count; ++index)
            {
                items.push_back((*choices)[index]);
            }
            const wxString* strings = items.empty() ? nullptr : items.data();
            return ::wxGetSelectedChoices(*static_cast<wxArrayInt*>(selections), *message, *caption,
                                          n, strings, parent, x, y, centre != 0, width, height);
        }

        EXPORT wxString* wxGetSingleChoice(const wxString* message, const wxString* caption,
                                           const wxString* choices, int count, wxWindow* parent)
        {
            return new wxString(::wxGetSingleChoice(*message, *caption, count, choices, parent));
        }

        EXPORT void* wxGetSingleChoiceData(const wxString* message, const wxString* caption,
                                           const wxString* choices, int count, void* client_data,
                                           wxWindow* parent)
        {
            return ::wxGetSingleChoiceData(*message, *caption, count, choices, &client_data,
                                           parent);
        }

        EXPORT void* wxGetSingleChoiceDataEx(const wxString* message, const wxString* caption,
                                             int n, const wxArrayString* choices, void* client_data,
                                             wxWindow* parent, int x, int y, int centre, int width,
                                             int height, int initialSelection)
        {
            std::vector<wxString> items;
            const size_t item_count = choices->GetCount();
            items.reserve(item_count);
            for (size_t index = 0; index < item_count; ++index)
            {
                items.push_back((*choices)[index]);
            }
            const wxString* strings = items.empty() ? nullptr : items.data();
            return ::wxGetSingleChoiceData(*message, *caption, n, strings, &client_data, parent, x,
                                           y, centre != 0, width, height, initialSelection);
        }

        EXPORT wxString* wxGetTranslation(const wxString* str)
        {
            return new wxString(::wxGetTranslation(*str));
        }

        EXPORT wxString* wxGetZlibVersionInfo()
        {
            return new wxString(::wxGetZlibVersionInfo().ToString());
        }

        EXPORT void* wxGet_wxConvLibc()
        {
            return &::wxGet_wxConvLibc();
        }

        EXPORT void* wxGet_wxConvLocal()
        {
            return &::wxGet_wxConvLocal();
        }

        EXPORT void* wxGet_wxConvUTF8()
        {
            return &::wxGet_wxConvUTF8();
        }

        EXPORT int wxIsalnum(int character)
        {
            return ::wxIsalnum(wxUniChar(static_cast<wxUint32>(character)));
        }

        EXPORT int wxIsdigit(int character)
        {
            return ::wxIsdigit(wxUniChar(static_cast<wxUint32>(character)));
        }

        EXPORT int wxIslower(int character)
        {
            return ::wxIslower(wxUniChar(static_cast<wxUint32>(character)));
        }

        EXPORT void* wxMakeFloatingPointValidator(double* value, int style)
        {
            return new wxFloatingPointValidator<double>(value, style);
        }

        EXPORT void wxMutexGuiEnter()
        {
            ::wxMutexGuiEnter();
        }

        EXPORT void wxMutexGuiLeave()
        {
            ::wxMutexGuiLeave();
        }

        EXPORT int wxPlatformIs(int platform)
        {
            return ::wxPlatformIs(platform);
        }

        EXPORT void* wxPointRefFromVariant(wxVariant* variant)
        {
            return &::wxPointRefFromVariant(*variant);
        }

        EXPORT void wxPostEvent(wxEvtHandler* dest, wxEvent* event)
        {
            ::wxPostEvent(dest, *event);
        }

        EXPORT size_t wxPtrToUInt(void* pointer)
        {
            return static_cast<size_t>(::wxPtrToUInt(pointer));
        }

        EXPORT int wxPuts(const wxString* str)
        {
            return ::wxPuts(*str);
        }

        EXPORT int wxRemoveFile(const wxString* file)
        {
            return ::wxRemoveFile(*file);
        }

        EXPORT int wxRenameFile(const wxString* old_path, const wxString* new_path, int overwrite)
        {
            return ::wxRenameFile(*old_path, *new_path, overwrite != 0);
        }

        EXPORT int wxShowTip(wxWindow* parent, void* tip_provider)
        {
            return ::wxShowTip(parent, static_cast<wxTipProvider*>(tip_provider));
        }

        EXPORT void* wxSizeRefFromVariant(wxVariant* variant)
        {
            return &::wxSizeRefFromVariant(*variant);
        }

        EXPORT char* wxStrdup(const wxString* str)
        {
            return ::wxStrdup(str->utf8_str());
        }

        EXPORT double wxStrtod(const wxString* nptr)
        {
            return ::wxStrtod(nptr->c_str(), nullptr);
        }

        EXPORT long wxStrtol(const wxString* nptr, int base)
        {
            return ::wxStrtol(nptr->c_str(), nullptr, base);
        }

        // -------------------------------------------------------------------
        // wxArrayString
        //
        // The block is declared in include/kwx_classes.h against the existing
        // TClassDefExtend(wxArrayString, wxArray). Elements are handed over as wxString*
        // because that is what the wxArrayString storage already holds.
        // -------------------------------------------------------------------

        EXPORT wxArrayString* wxArrayString_Create()
        {
            return new wxArrayString();
        }

        EXPORT void wxArrayString_Add(wxArrayString* self, const wxString* str)
        {
            self->Add(*str);
        }

        EXPORT int wxArrayString_GetCount(wxArrayString* self)
        {
            return static_cast<int>(self->GetCount());
        }

        EXPORT int wxArrayString_Count(wxArrayString* self)
        {
            return static_cast<int>(self->Count());
        }

        EXPORT void wxArrayString_Insert(wxArrayString* self, const wxString* str, int index)
        {
            self->Insert(*str, static_cast<size_t>(index));
        }

        EXPORT void wxArrayString_RemoveAt(wxArrayString* self, int index, int count)
        {
            self->RemoveAt(static_cast<size_t>(index), static_cast<size_t>(count));
        }

        EXPORT int wxArrayString_IsEmpty(wxArrayString* self)
        {
            return self->IsEmpty();
        }

        EXPORT wxString* wxArrayString_Item(wxArrayString* self, int index)
        {
            // The binding owns the returned copy; the element itself stays in the array.
            return new wxString(self->Item(static_cast<size_t>(index)));
        }

        EXPORT void wxArrayString_Sort(wxArrayString* self, int reverse)
        {
            self->Sort(reverse != 0);
        }

        EXPORT void wxArrayString_Alloc(wxArrayString* self, int count)
        {
            self->Alloc(static_cast<size_t>(count));
        }

        EXPORT void wxArrayString_Clear(wxArrayString* self)
        {
            self->Clear();
        }

        EXPORT void wxArrayString_Delete(wxArrayString* self)
        {
            delete self;
        }

        // -------------------------------------------------------------------
        // wxArrayInt
        //
        // The int analogue of wxArrayString. Declared as its own TClassDef in
        // include/kwx_classes.h; elements are plain ints.
        // -------------------------------------------------------------------

        EXPORT wxArrayInt* wxArrayInt_Create()
        {
            return new wxArrayInt();
        }

        EXPORT void wxArrayInt_Delete(wxArrayInt* self)
        {
            delete self;
        }

        EXPORT void wxArrayInt_Add(wxArrayInt* self, int item)
        {
            self->Add(item);
        }

        EXPORT int wxArrayInt_GetCount(wxArrayInt* self)
        {
            return static_cast<int>(self->GetCount());
        }

        EXPORT int wxArrayInt_Item(wxArrayInt* self, int index)
        {
            return self->Item(static_cast<size_t>(index));
        }

        EXPORT void wxArrayInt_Clear(wxArrayInt* self)
        {
            self->Clear();
        }

        EXPORT int wxArrayInt_IsEmpty(wxArrayInt* self)
        {
            return self->IsEmpty() ? 1 : 0;
        }
    }
}  // namespace kwx
