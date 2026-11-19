#pragma once

/* wxDebugReport family (wx/debugrpt.h): the report generator, its compressing
 * and uploading variants, and the standard preview window.
 *
 * The report "context" argument is one of the two constants exported from
 * src/kwx_defs.cpp: DebugReport_Context_Current (0) and
 * DebugReport_Context_Exception (1).
 */

TClassDef(wxDebugReport) TClass(wxDebugReport) wxDebugReport_Create();
void wxDebugReport_Delete(TSelf(wxDebugReport) pObject);
// Borrowed pointer to the object's own directory string: valid only while the
// report lives, never pass it to wxString_Delete.
TClass(wxString) wxDebugReport_GetDirectory(TSelf(wxDebugReport) pObject);
TBool wxDebugReport_IsOk(TSelf(wxDebugReport) pObject);
void wxDebugReport_Reset(TSelf(wxDebugReport) pObject);
void wxDebugReport_AddFile(TSelf(wxDebugReport) pObject, TClass(wxString) filename,
                           TClass(wxString) description);
TBool wxDebugReport_AddText(TSelf(wxDebugReport) pObject, TClass(wxString) filename,
                            TClass(wxString) text, TClass(wxString) description);
TBool wxDebugReport_AddContext(TSelf(wxDebugReport) pObject, int ctx);
TBool wxDebugReport_AddCurrentContext(TSelf(wxDebugReport) pObject);
TBool wxDebugReport_AddExceptionContext(TSelf(wxDebugReport) pObject);
TBool wxDebugReport_AddDump(TSelf(wxDebugReport) pObject, int ctx);
TBool wxDebugReport_AddCurrentDump(TSelf(wxDebugReport) pObject);
TBool wxDebugReport_AddExceptionDump(TSelf(wxDebugReport) pObject);
void wxDebugReport_AddAll(TSelf(wxDebugReport) pObject, int context);
TBool wxDebugReport_Process(TSelf(wxDebugReport) pObject);
TClassOwned(wxString) wxDebugReport_GetReportName(TSelf(wxDebugReport) pObject);
size_t wxDebugReport_GetFilesCount(TSelf(wxDebugReport) pObject);
// wxDebugReport::GetFile() publishes two strings through out-pointers; these
// two getters return a copy of each and null when index is out of range.
TClassOwned(wxString) wxDebugReport_GetFileName(TSelf(wxDebugReport) pObject, size_t index);
TClassOwned(wxString) wxDebugReport_GetFileDescription(TSelf(wxDebugReport) pObject, size_t index);
void wxDebugReport_RemoveFile(TSelf(wxDebugReport) pObject, TClass(wxString) name);

TClassDefExtend(wxDebugReportCompress, wxDebugReport) TClass(wxDebugReportCompress)
    wxDebugReportCompress_Create();
void wxDebugReportCompress_Delete(TSelf(wxDebugReportCompress) pObject);
void wxDebugReportCompress_SetCompressedFileDirectory(TSelf(wxDebugReportCompress) pObject,
                                                      TClass(wxString) dir);
void wxDebugReportCompress_SetCompressedFileBaseName(TSelf(wxDebugReportCompress) pObject,
                                                     TClass(wxString) name);
// Borrowed member pointer, same rule as GetDirectory.
TClass(wxString) wxDebugReportCompress_GetCompressedFileName(TSelf(wxDebugReportCompress) pObject);

TClassDefExtend(wxDebugReportUpload, wxDebugReportCompress)
    // `curl` is the curl command name; _CreateDefault passes wxWidgets' own default.
    TClass(wxDebugReportUpload)
        wxDebugReportUpload_Create(TClass(wxString) url, TClass(wxString) input,
                                   TClass(wxString) action, TClass(wxString) curl);
TClass(wxDebugReportUpload)
    wxDebugReportUpload_CreateDefault(TClass(wxString) url, TClass(wxString) input,
                                      TClass(wxString) action);
void wxDebugReportUpload_Delete(TSelf(wxDebugReportUpload) pObject);

TClassDef(wxDebugReportPreviewStd) TClass(wxDebugReportPreviewStd) wxDebugReportPreviewStd_Create();
void wxDebugReportPreviewStd_Delete(TSelf(wxDebugReportPreviewStd) pObject);
TBool wxDebugReportPreviewStd_Show(TSelf(wxDebugReportPreviewStd) pObject,
                                   TClass(wxDebugReport) report);
