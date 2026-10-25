#include "kwx_wrapper.h"

#include <wx/filedlg.h>
#include <wx/process.h>
#include <wx/stockitem.h>
#include <wx/utils.h>

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

        EXPORT bool wxCheckOsVersion(int major, int minor, int micro)
        {
            return ::wxCheckOsVersion(major, minor, micro);
        }

        EXPORT bool wxIsPlatformLittleEndian()
        {
            return ::wxIsPlatformLittleEndian();
        }

        EXPORT bool wxIsPlatform64Bit()
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

        EXPORT bool wxHandleFatalExceptions([[maybe_unused]] int doit)
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

        EXPORT bool wxGetKeyState(int key)
        {
            return ::wxGetKeyState(static_cast<wxKeyCode>(key));
        }

        EXPORT bool wxSetDetectableAutoRepeat(int flag)
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

        EXPORT bool wxGetEnv(const wxString* var, wxString* value)
        {
            return ::wxGetEnv(*var, value);
        }

        EXPORT bool wxSetEnv(const wxString* var, const wxString* value)
        {
            return ::wxSetEnv(*var, *value);
        }

        EXPORT bool wxUnsetEnv(const wxString* var)
        {
            return ::wxUnsetEnv(*var);
        }

        EXPORT bool wxGetEnvMap(wxArrayString* env_map)
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

        EXPORT bool wxGetDiskSpace(const wxString* path, int64_t* total_bytes, int64_t* free_bytes)
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

        EXPORT bool wxExecuteDDE(const wxString* server, const wxString* topic,
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

        EXPORT bool wxShutdown(int flags)
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

        EXPORT bool wxShell(const wxString* command)
        {
            return ::wxShell(*command);
        }

        EXPORT bool wxShellWithOutput(const wxString* command, wxArrayString* output)
        {
            return ::wxShell(*command, *output);
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

        EXPORT bool wxLaunchDefaultBrowser(const wxString* url, int flags)
        {
            return ::wxLaunchDefaultBrowser(*url, flags);
        }

        EXPORT bool wxLaunchDefaultApplication(const wxString* path, int flags)
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

        EXPORT bool wxSafeYield(wxWindow* window, int only_if_needed)
        {
            return ::wxSafeYield(window, only_if_needed != 0);
        }

        EXPORT void wxEnableTopLevelWindows(int enable)
        {
            ::wxEnableTopLevelWindows(enable != 0);
        }

        EXPORT bool wxCheckForInterrupt(wxWindow* window)
        {
            return ::wxCheckForInterrupt(window);
        }

        EXPORT void wxFlushEvents()
        {
            ::wxFlushEvents();
        }

        EXPORT bool wxYield()
        {
            return ::wxYield();
        }

        EXPORT bool wxYieldIfNeeded()
        {
            return ::wxYieldIfNeeded();
        }

        EXPORT bool wxMSWIsOnSecureScreen()
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

        EXPORT bool wxIsStockID(int id)
        {
            return ::wxIsStockID(static_cast<wxWindowID>(id));
        }

        EXPORT bool wxIsStockLabel(int id, const wxString* label)
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
    }
}  // namespace kwx
