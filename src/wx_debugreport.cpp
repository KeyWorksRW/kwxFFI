// wxDebugReport family (wx/debugrpt.h): the report generator, its compressing and uploading
// variants, and the standard preview window.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/debugrpt.h>

extern "C"
{
    // -----------------------------------------------------------------------
    // wxDebugReport
    // -----------------------------------------------------------------------

    EXPORT wxDebugReport* wxDebugReport_Create()
    {
        return new wxDebugReport();
    }

    EXPORT void wxDebugReport_Delete(wxDebugReport* self)
    {
        delete self;
    }

    EXPORT wxString* wxDebugReport_GetDirectory(wxDebugReport* self)
    {
        // Borrowed pointer to the object's own directory string: valid only while the
        // report lives, never pass it to wxString_Delete.
        return const_cast<wxString*>(&self->GetDirectory());
    }

    EXPORT int wxDebugReport_IsOk(wxDebugReport* self)
    {
        return self->IsOk() ? 1 : 0;
    }

    EXPORT void wxDebugReport_Reset(wxDebugReport* self)
    {
        self->Reset();
    }

    EXPORT void wxDebugReport_AddFile(wxDebugReport* self, wxString* filename,
                                      wxString* description)
    {
        self->AddFile(*filename, *description);
    }

    EXPORT int wxDebugReport_AddText(wxDebugReport* self, wxString* filename, wxString* text,
                                     wxString* description)
    {
        return self->AddText(*filename, *text, *description) ? 1 : 0;
    }

    EXPORT int wxDebugReport_AddContext(wxDebugReport* self, int ctx)
    {
        return self->AddContext(static_cast<wxDebugReport::Context>(ctx)) ? 1 : 0;
    }

    EXPORT int wxDebugReport_AddCurrentContext(wxDebugReport* self)
    {
        return self->AddCurrentContext() ? 1 : 0;
    }

    EXPORT int wxDebugReport_AddExceptionContext(wxDebugReport* self)
    {
        return self->AddExceptionContext() ? 1 : 0;
    }

    EXPORT int wxDebugReport_AddDump(wxDebugReport* self, int ctx)
    {
        // wxWidgets turns wxUSE_CRASHREPORT off on a toolchain without SEH support
        // (wx/msw/chkconf.h), so the crash-dump hooks exist only in an MSVC build.  The
        // export itself must exist on every build, so it reports the failure value there.
#if wxUSE_CRASHREPORT
        return self->AddDump(static_cast<wxDebugReport::Context>(ctx)) ? 1 : 0;
#else
        wxUnusedVar(self);
        wxUnusedVar(ctx);
        return 0;
#endif
    }

    EXPORT int wxDebugReport_AddCurrentDump(wxDebugReport* self)
    {
#if wxUSE_CRASHREPORT
        return self->AddCurrentDump() ? 1 : 0;
#else
        wxUnusedVar(self);
        return 0;
#endif
    }

    EXPORT int wxDebugReport_AddExceptionDump(wxDebugReport* self)
    {
#if wxUSE_CRASHREPORT
        return self->AddExceptionDump() ? 1 : 0;
#else
        wxUnusedVar(self);
        return 0;
#endif
    }

    EXPORT void wxDebugReport_AddAll(wxDebugReport* self, int context)
    {
        // The C++ default argument (Context_Exception) cannot be expressed across the
        // boundary, so the caller always passes the context explicitly.
        self->AddAll(static_cast<wxDebugReport::Context>(context));
    }

    EXPORT int wxDebugReport_Process(wxDebugReport* self)
    {
        return self->Process() ? 1 : 0;
    }

    EXPORT wxString* wxDebugReport_GetReportName(wxDebugReport* self)
    {
        return new wxString(self->GetReportName());
    }

    EXPORT size_t wxDebugReport_GetFilesCount(wxDebugReport* self)
    {
        return self->GetFilesCount();
    }

    EXPORT wxString* wxDebugReport_GetFileName(wxDebugReport* self, size_t index)
    {
        wxString name;
        wxString description;
        if (!self->GetFile(index, &name, &description))
        {
            return nullptr;
        }
        return new wxString(name);
    }

    EXPORT wxString* wxDebugReport_GetFileDescription(wxDebugReport* self, size_t index)
    {
        wxString name;
        wxString description;
        if (!self->GetFile(index, &name, &description))
        {
            return nullptr;
        }
        return new wxString(description);
    }

    EXPORT void wxDebugReport_RemoveFile(wxDebugReport* self, wxString* name)
    {
        self->RemoveFile(*name);
    }

    // -----------------------------------------------------------------------
    // wxDebugReportCompress
    // -----------------------------------------------------------------------

    EXPORT wxDebugReportCompress* wxDebugReportCompress_Create()
    {
        return new wxDebugReportCompress();
    }

    EXPORT void wxDebugReportCompress_Delete(wxDebugReportCompress* self)
    {
        delete self;
    }

    EXPORT void wxDebugReportCompress_SetCompressedFileDirectory(wxDebugReportCompress* self,
                                                                 wxString* dir)
    {
        self->SetCompressedFileDirectory(*dir);
    }

    EXPORT void wxDebugReportCompress_SetCompressedFileBaseName(wxDebugReportCompress* self,
                                                                wxString* name)
    {
        self->SetCompressedFileBaseName(*name);
    }

    EXPORT wxString* wxDebugReportCompress_GetCompressedFileName(wxDebugReportCompress* self)
    {
        // Borrowed member pointer, same rule as wxDebugReport_GetDirectory.
        return const_cast<wxString*>(&self->GetCompressedFileName());
    }

    // -----------------------------------------------------------------------
    // wxDebugReportUpload
    // -----------------------------------------------------------------------

    EXPORT wxDebugReportUpload* wxDebugReportUpload_Create(wxString* url, wxString* input,
                                                           wxString* action, wxString* curl)
    {
        return new wxDebugReportUpload(*url, *input, *action, *curl);
    }

    EXPORT wxDebugReportUpload* wxDebugReportUpload_CreateDefault(wxString* url, wxString* input,
                                                                  wxString* action)
    {
        return new wxDebugReportUpload(*url, *input, *action);
    }

    EXPORT void wxDebugReportUpload_Delete(wxDebugReportUpload* self)
    {
        delete self;
    }

    // -----------------------------------------------------------------------
    // wxDebugReportPreviewStd
    // -----------------------------------------------------------------------

    EXPORT wxDebugReportPreviewStd* wxDebugReportPreviewStd_Create()
    {
        return new wxDebugReportPreviewStd();
    }

    EXPORT void wxDebugReportPreviewStd_Delete(wxDebugReportPreviewStd* self)
    {
        delete self;
    }

    EXPORT int wxDebugReportPreviewStd_Show(wxDebugReportPreviewStd* self, wxDebugReport* report)
    {
        // Show() is const in wxWidgets; calling it on the pointer the caller owns is fine.
        return self->Show(*report) ? 1 : 0;
    }
}
