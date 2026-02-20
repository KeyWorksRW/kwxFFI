#include "kwx_wrapper.h"

#include <wx/filename.h>
#include <wx/stdpaths.h>

#ifdef __WXMAC__
    #include <dlfcn.h>   // dlsym
    #include <limits.h>  // PATH_MAX
    #include <mach-o/dyld.h>
typedef int (*NSGetExecutablePathProcPtr)(char* buf, size_t* bufsize);
#endif

wxString GetApplicationPath()
{
    static bool found = false;
    static wxString path;

    if (!found)
    {
#ifdef __WXMSW__
        path = wxStandardPaths::Get().GetExecutablePath();

#else
        wxString argv0;

    #ifdef __WXMAC__
        // _NSGetExecutablePath returns UTF-8 on APFS/HFS+
        void* addrOf_NSGetExecutablePath = dlsym(RTLD_DEFAULT, "_NSGetExecutablePath");
        if (addrOf_NSGetExecutablePath != nullptr)
        {
            char buf[PATH_MAX + 1];
            size_t bufLen = PATH_MAX;
            buf[0] = 0;
            ((NSGetExecutablePathProcPtr) addrOf_NSGetExecutablePath)(buf, &bufLen);
            if (buf[0] != 0)
            {
                path = wxString(buf);
                found = true;
                return path;
            }
        }
    #endif

        argv0 = wxTheApp->argv[0];

        // check absolute path
        if (wxIsAbsolutePath(argv0))
        {
            path = argv0;
        }
        else
        {
            // check relative path
            wxString fname = wxGetCwd() + wxFILE_SEP_PATH + argv0;
            if (wxFileExists(fname))
            {
                path = fname;
            }
            else
            {
                // find on PATH
                wxPathList pathlist;
                pathlist.AddEnvList("PATH");
                path = pathlist.FindAbsoluteValidPath(argv0);
            }
        }

        wxFileName filename(path);
        filename.Normalize();
        path = filename.GetFullPath();
#endif

        found = true;
    }
    return path;
}

wxString GetApplicationDir()
{
    wxString path;

    // check APPDIR on unix's
#ifndef __WXMSW__
    #ifndef __WXMAC__
    wxGetEnv("APPDIR", &path);
    if (!path.IsEmpty())
        return path;
    #endif
#endif

    path = GetApplicationPath();
    if (path.IsEmpty())
        return wxGetCwd();
    else
    {
        wxFileName fname(path);
        return fname.GetPath(wxPATH_GET_VOLUME);
    }
}

extern "C"
{
    EXPORT wxString* wxGetApplicationDir()
    {
        wxString* result = new wxString();
        *result = GetApplicationDir();
        return result;
    }

    EXPORT wxString* wxGetApplicationPath()
    {
        wxString* result = new wxString();
        *result = GetApplicationPath();
        return result;
    }
}
