#include "wrapper.h"

#if !defined(__WXGTK__)
    #include <wx/dcprint.h>
#endif

#if defined(wxUSE_POSTSCRIPT) && (wxUSE_POSTSCRIPT == 0)
    #undef wxUSE_POSTSCRIPT
#endif

#ifdef wxUSE_POSTSCRIPT
    #include <wx/dcps.h>
    #include <wx/generic/prntdlgg.h>
#endif

#ifndef wxUSE_POSTSCRIPT
    #define wxPostScriptDC void
#endif

extern "C"
{
    EXPORT void* wxPrinter_Create(void* data)
    {
        return (void*) new wxPrinter((wxPrintDialogData*) data);
    }

    EXPORT void wxPrinter_Delete(wxPrinter* self)
    {
        delete self;
    }

    EXPORT void* wxPrinter_CreateAbortWindow(wxPrinter* self, wxWindow* parent,
                                             wxPrintout* printout)
    {
        return (void*) self->CreateAbortWindow(parent, printout);
    }

    EXPORT void wxPrinter_ReportError(wxPrinter* self, wxWindow* parent, wxPrintout* printout,
                                      wxString* message)
    {
        self->ReportError(parent, printout, *message);
    }

    EXPORT void wxPrinter_GetPrintDialogData(wxPrinter* self, wxPrintDialogData* _ref)
    {
        *_ref = self->GetPrintDialogData();
    }

    EXPORT bool wxPrinter_GetAbort(wxPrinter* self)
    {
        return self->GetAbort();
    }

    EXPORT int wxPrinter_GetLastError(wxPrinter* self)
    {
        return self->GetLastError();
    }

    EXPORT bool wxPrinter_Setup(wxPrinter* self, wxWindow* parent)
    {
        return self->Setup(parent);
    }

    EXPORT bool wxPrinter_Print(wxPrinter* self, wxWindow* parent, wxPrintout* printout,
                                bool prompt)
    {
        return self->Print(parent, printout, prompt);
    }

    EXPORT void* wxPrinter_PrintDialog(wxPrinter* self, wxWindow* parent)
    {
        return (void*) self->PrintDialog(parent);
    }

    EXPORT void* ELJPrintout_Create(void* title, void* self, void* _DoOnBeginDocument,
                                    void* _DoOnEndDocument, void* _DoOnBeginPrinting,
                                    void* _DoOnEndPrinting, void* _DoOnPreparePrinting,
                                    void* _DoOnPrintPage, void* _DoOnHasPage, void* DoOnPageInfo)
    {
        return (void*) new ELJPrintout(title, self, _DoOnBeginDocument, _DoOnEndDocument,
                                       _DoOnBeginPrinting, _DoOnEndPrinting, _DoOnPreparePrinting,
                                       _DoOnPrintPage, _DoOnHasPage, DoOnPageInfo);
    }
    EXPORT void ELJPrintout_Delete(ELJPrintout* self)
    {
        delete self;
    }

    EXPORT wxString* ELJPrintout_GetTitle(ELJPrintout* self)
    {
        return new wxString(self->GetTitle());
    }

    EXPORT void* ELJPrintout_GetDC(ELJPrintout* self)
    {
        return (void*) self->GetDC();
    }

    EXPORT void ELJPrintout_SetDC(ELJPrintout* self, wxDC* dc)
    {
        self->SetDC(dc);
    }

    EXPORT void ELJPrintout_SetPageSizePixels(void* _obj, int w, int h)
    {
        ((ELJPrintout*) _obj)->SetPageSizePixels(w, h);
    }

    EXPORT void ELJPrintout_GetPageSizePixels(void* _obj, int* w, int* h)
    {
        ((ELJPrintout*) _obj)->GetPageSizePixels(w, h);
    }

    EXPORT void ELJPrintout_SetPageSizeMM(void* _obj, int w, int h)
    {
        ((ELJPrintout*) _obj)->SetPageSizeMM(w, h);
    }

    EXPORT void ELJPrintout_GetPageSizeMM(void* _obj, int* w, int* h)
    {
        ((ELJPrintout*) _obj)->GetPageSizeMM(w, h);
    }

    EXPORT void ELJPrintout_SetPPIScreen(void* _obj, int x, int y)
    {
        ((ELJPrintout*) _obj)->SetPPIScreen(x, y);
    }

    EXPORT void ELJPrintout_GetPPIScreen(void* _obj, int* x, int* y)
    {
        ((ELJPrintout*) _obj)->GetPPIScreen(x, y);
    }

    EXPORT void ELJPrintout_SetPPIPrinter(void* _obj, int x, int y)
    {
        ((ELJPrintout*) _obj)->SetPPIPrinter(x, y);
    }

    EXPORT void ELJPrintout_GetPPIPrinter(void* _obj, int* x, int* y)
    {
        ((ELJPrintout*) _obj)->GetPPIPrinter(x, y);
    }

    EXPORT bool ELJPrintout_IsPreview(ELJPrintout* self)
    {
        return self->IsPreview();
    }

    EXPORT void* wxPreviewCanvas_Create(void* preview, wxWindow* parent, int x, int y, int w, int h,
                                        int style)
    {
        return (void*) new wxPreviewCanvas((wxPrintPreviewBase*) preview, parent, wxPoint(x, y),
                                           wxSize(w, h), (long) style);
    }

    EXPORT void* ELJPreviewFrame_Create(void* _obj, void* _init, void* _create_canvas,
                                        void* _create_toolbar, void* preview, void* parent,
                                        void* title, int x, int y, int w, int h, int style)
    {
        return (void*) new ELJPreviewFrame(_obj, _init, _create_canvas, _create_toolbar, preview,
                                           parent, title, x, y, w, h, style);
    }

    EXPORT void ELJPreviewFrame_Initialize(ELJPreviewFrame* self)
    {
        self->Initialize();
    }

    EXPORT void ELJPreviewFrame_SetPreviewCanvas(ELJPreviewFrame* self, void* obj)
    {
        self->SetPreviewCanvas(obj);
    }

    EXPORT void ELJPreviewFrame_SetControlBar(ELJPreviewFrame* self, void* obj)
    {
        self->SetControlBar(obj);
    }

    EXPORT void ELJPreviewFrame_SetPrintPreview(ELJPreviewFrame* self, void* obj)
    {
        self->SetPrintPreview(obj);
    }

    EXPORT void* ELJPreviewFrame_GetPreviewCanvas(ELJPreviewFrame* self)
    {
        return (void*) self->GetPreviewCanvas();
    }

    EXPORT void* ELJPreviewFrame_GetControlBar(ELJPreviewFrame* self)
    {
        return (void*) self->GetControlBar();
    }

    EXPORT void* ELJPreviewFrame_GetPrintPreview(ELJPreviewFrame* self)
    {
        return (void*) self->GetPrintPreview();
    }

    EXPORT void* ELJPreviewControlBar_Create(void* preview, int buttons, wxWindow* parent,
                                             void* title, int x, int y, int w, int h, int style)
    {
        return (void*) new wxPreviewControlBar((wxPrintPreviewBase*) preview, (long) buttons,
                                               parent, wxPoint(x, y), wxSize(w, h), (long) style);
    }

    EXPORT void* wxPrintPreview_CreateFromDialogData(void* printout, void* printoutForPrinting,
                                                     void* data)
    {
        return (void*) new wxPrintPreview((wxPrintout*) printout, (wxPrintout*) printoutForPrinting,
                                          (wxPrintDialogData*) data);
    }

    EXPORT void* wxPrintPreview_CreateFromData(void* printout, void* printoutForPrinting,
                                               void* data)
    {
        return (void*) new wxPrintPreview((wxPrintout*) printout, (wxPrintout*) printoutForPrinting,
                                          (wxPrintData*) data);
    }

    EXPORT void wxPrintPreview_Delete(wxPrintPreview* self)
    {
        delete self;
    }

    EXPORT void wxPrintPreview_SetCurrentPage(wxPrintPreview* self, int pageNum)
    {
        self->SetCurrentPage(pageNum);
    }

    EXPORT int wxPrintPreview_GetCurrentPage(wxPrintPreview* self)
    {
        return self->GetCurrentPage();
    }

    EXPORT void wxPrintPreview_SetPrintout(wxPrintPreview* self, wxPrintout* printout)
    {
        self->SetPrintout(printout);
    }

    EXPORT void* wxPrintPreview_GetPrintout(wxPrintPreview* self)
    {
        return (void*) self->GetPrintout();
    }

    EXPORT void* wxPrintPreview_GetPrintoutForPrinting(wxPrintPreview* self)
    {
        return (void*) self->GetPrintoutForPrinting();
    }

    EXPORT void wxPrintPreview_SetFrame(wxPrintPreview* self, wxFrame* frame)
    {
        self->SetFrame(frame);
    }

    EXPORT void wxPrintPreview_SetCanvas(wxPrintPreview* self, wxPreviewCanvas* canvas)
    {
        self->SetCanvas(canvas);
    }

    EXPORT void* wxPrintPreview_GetFrame(wxPrintPreview* self)
    {
        return (void*) self->GetFrame();
    }

    EXPORT void* wxPrintPreview_GetCanvas(wxPrintPreview* self)
    {
        return (void*) self->GetCanvas();
    }

    EXPORT bool wxPrintPreview_PaintPage(wxPrintPreview* self, wxPreviewCanvas* canvas, wxDC* dc)
    {
        return self->PaintPage(canvas, *dc);
    }

    EXPORT bool wxPrintPreview_DrawBlankPage(wxPrintPreview* self, wxPreviewCanvas* canvas,
                                             wxDC* dc)
    {
        return self->DrawBlankPage(canvas, *dc);
    }

    EXPORT bool wxPrintPreview_RenderPage(wxPrintPreview* self, int pageNum)
    {
        return self->RenderPage(pageNum);
    }

    EXPORT void wxPrintPreview_GetPrintDialogData(wxPrintPreview* self, wxPrintDialogData* _ref)
    {
        *_ref = self->GetPrintDialogData();
    }

    EXPORT void wxPrintPreview_SetZoom(wxPrintPreview* self, int percent)
    {
        self->SetZoom(percent);
    }

    EXPORT int wxPrintPreview_GetZoom(wxPrintPreview* self)
    {
        return self->GetZoom();
    }

    EXPORT int wxPrintPreview_GetMaxPage(wxPrintPreview* self)
    {
        return self->GetMaxPage();
    }

    EXPORT int wxPrintPreview_GetMinPage(wxPrintPreview* self)
    {
        return self->GetMinPage();
    }

    EXPORT bool wxPrintPreview_IsOk(wxPrintPreview* self)
    {
        return self->IsOk();
    }

    EXPORT void wxPrintPreview_SetOk(wxPrintPreview* self, bool ok)
    {
        self->SetOk(ok);
    }

    EXPORT bool wxPrintPreview_Print(wxPrintPreview* self, bool interactive)
    {
        return self->Print(interactive);
    }

    EXPORT void wxPrintPreview_DetermineScaling(wxPrintPreview* self)
    {
        self->DetermineScaling();
    }

    EXPORT void* wxPrintData_Create()
    {
        return (void*) new wxPrintData();
    }

    EXPORT void wxPrintData_Delete(wxPrintData* self)
    {
        delete self;
    }

    EXPORT void* wxPostScriptPrintNativeData_Create()
    {
#ifdef wxUSE_POSTSCRIPT
        return (void*) new wxPostScriptPrintNativeData();
#else
        return nullptr;
#endif
    }

    EXPORT void wxPostScriptPrintNativeData_Delete(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        delete (wxPostScriptPrintNativeData*) self;
#endif
    }

    EXPORT int wxPrintData_GetNoCopies(wxPrintData* self)
    {
        return self->GetNoCopies();
    }

    EXPORT bool wxPrintData_GetCollate(wxPrintData* self)
    {
        return self->GetCollate();
    }

    EXPORT int wxPrintData_GetOrientation(wxPrintData* self)
    {
        return self->GetOrientation();
    }

    EXPORT wxString* wxPrintData_GetPrinterName(wxPrintData* self)
    {
        return new wxString(self->GetPrinterName());
    }

    EXPORT bool wxPrintData_GetColour(wxPrintData* self)
    {
        return self->GetColour();
    }

    EXPORT int wxPrintData_GetDuplex(wxPrintData* self)
    {
        return (int) self->GetDuplex();
    }

    EXPORT int wxPrintData_GetPaperId(wxPrintData* self)
    {
        return (int) self->GetPaperId();
    }

    EXPORT wxSize* wxPrintData_GetPaperSize(wxPrintData* self)
    {
        wxSize* s = new wxSize();
        *s = self->GetPaperSize();
        return s;
    }

    EXPORT int wxPrintData_GetQuality(wxPrintData* self)
    {
        return (int) self->GetQuality();
    }

    EXPORT void wxPrintData_SetNoCopies(wxPrintData* self, int v)
    {
        self->SetNoCopies(v);
    }

    EXPORT void wxPrintData_SetCollate(wxPrintData* self, bool flag)
    {
        self->SetCollate(flag);
    }

    EXPORT void wxPrintData_SetOrientation(wxPrintData* self, int orient)
    {
        self->SetOrientation((wxPrintOrientation) orient);
    }

    EXPORT void wxPrintData_SetPrinterName(wxPrintData* self, wxString* name)
    {
        self->SetPrinterName(*name);
    }

    EXPORT void wxPrintData_SetColour(wxPrintData* self, bool colour)
    {
        self->SetColour(colour);
    }

    EXPORT void wxPrintData_SetDuplex(wxPrintData* self, int duplex)
    {
        self->SetDuplex((wxDuplexMode) duplex);
    }

    EXPORT void wxPrintData_SetPaperId(wxPrintData* self, int sizeId)
    {
        self->SetPaperId((wxPaperSize) sizeId);
    }

    EXPORT void wxPrintData_SetPaperSize(wxPrintData* self, int w, int h)
    {
        self->SetPaperSize(wxSize(w, h));
    }

    EXPORT void wxPrintData_SetQuality(wxPrintData* self, int quality)
    {
        self->SetQuality((wxPrintQuality) quality);
    }

    EXPORT wxString* wxPrintData_GetPrinterCommand(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        wxString tmp = ((wxPostScriptPrintNativeData*) self)->GetPrinterCommand();
        return new wxString(tmp);
#else
        return nullptr;
#endif
    }

    EXPORT wxString* wxPrintData_GetPrinterOptions(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        wxString tmp = ((wxPostScriptPrintNativeData*) self)->GetPrinterOptions();
        return new wxString(tmp);
#else
        return nullptr;
#endif
    }

    EXPORT wxString* wxPrintData_GetPreviewCommand(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        wxString tmp = ((wxPostScriptPrintNativeData*) self)->GetPreviewCommand();
        return new wxString(tmp);
#else
        return nullptr;
#endif
    }

    EXPORT wxString* wxPrintData_GetFilename(wxPrintData* self)
    {
        wxString tmp = self->GetFilename();
        return new wxString(tmp);
    }

    EXPORT wxString* wxPrintData_GetFontMetricPath(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        wxString tmp = ((wxPostScriptPrintNativeData*) self)->GetFontMetricPath();
        return new wxString(tmp);
#else
        return nullptr;
#endif
    }

    EXPORT double wxPrintData_GetPrinterScaleX(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        return ((wxPostScriptPrintNativeData*) self)->GetPrinterScaleX();
#else
        return 0.0;
#endif
    }

    EXPORT double wxPrintData_GetPrinterScaleY(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        return ((wxPostScriptPrintNativeData*) self)->GetPrinterScaleY();
#else
        return 0.0;
#endif
    }

    EXPORT int wxPrintData_GetPrinterTranslateX(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        return ((wxPostScriptPrintNativeData*) self)->GetPrinterTranslateX();
#else
        return 0;
#endif
    }

    EXPORT int wxPrintData_GetPrinterTranslateY(void* self)
    {
#ifdef wxUSE_POSTSCRIPT
        return ((wxPostScriptPrintNativeData*) self)->GetPrinterTranslateY();
#else
        return 0;
#endif
    }

    EXPORT int wxPrintData_GetPrintMode(wxPrintData* self)
    {
        return (int) self->GetPrintMode();
    }

    EXPORT void wxPrintData_SetPrinterCommand(void* self, wxString* command)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterCommand(*command);
#endif
    }

    EXPORT void wxPrintData_SetPrinterOptions(void* self, wxString* options)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterOptions(*options);
#endif
    }

    EXPORT void wxPrintData_SetPreviewCommand(void* self, wxString* command)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPreviewCommand(*command);
#endif
    }

    EXPORT void wxPrintData_SetFilename(wxPrintData* self, wxString* filename)
    {
        self->SetFilename(*filename);
    }

    EXPORT void wxPrintData_SetFontMetricPath(void* self, wxString* path)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetFontMetricPath(*path);
#endif
    }

    EXPORT void wxPrintData_SetPrinterScaleX(void* self, double x)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterScaleX(x);
#endif
    }

    EXPORT void wxPrintData_SetPrinterScaleY(void* self, double y)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterScaleY(y);
#endif
    }

    EXPORT void wxPrintData_SetPrinterScaling(void* self, double x, double y)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterScaling(x, y);
#endif
    }

    EXPORT void wxPrintData_SetPrinterTranslateX(void* self, int x)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterTranslateX((int) x);
#endif
    }

    EXPORT void wxPrintData_SetPrinterTranslateY(void* self, int y)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterTranslateY((int) y);
#endif
    }

    EXPORT void wxPrintData_SetPrinterTranslation(void* self, int x, int y)
    {
#ifdef wxUSE_POSTSCRIPT
        ((wxPostScriptPrintNativeData*) self)->SetPrinterTranslation((long) x, (long) y);
#endif
    }

    EXPORT void wxPrintData_SetPrintMode(void* self, int printMode)
    {
        ((wxPrintData*) self)->SetPrintMode((wxPrintMode) printMode);
    }

    EXPORT void wxPrintData_Assign(void* self, void* data)
    {
        *((wxPrintData*) self) = *((wxPrintData*) data);
    }

    EXPORT void* wxPrintDialogData_CreateDefault()
    {
        return (void*) new wxPrintDialogData();
    }

    EXPORT void* wxPrintDialogData_CreateFromData(void* printData)
    {
        return (void*) new wxPrintDialogData(*((wxPrintData*) printData));
    }

    EXPORT void wxPrintDialogData_Delete(void* self)
    {
        delete (wxPrintDialogData*) self;
    }

    EXPORT int wxPrintDialogData_GetFromPage(void* self)
    {
        return ((wxPrintDialogData*) self)->GetFromPage();
    }

    EXPORT int wxPrintDialogData_GetToPage(void* self)
    {
        return ((wxPrintDialogData*) self)->GetToPage();
    }

    EXPORT int wxPrintDialogData_GetMinPage(void* self)
    {
        return ((wxPrintDialogData*) self)->GetMinPage();
    }

    EXPORT int wxPrintDialogData_GetMaxPage(void* self)
    {
        return ((wxPrintDialogData*) self)->GetMaxPage();
    }

    EXPORT int wxPrintDialogData_GetNoCopies(void* self)
    {
        return ((wxPrintDialogData*) self)->GetNoCopies();
    }

    EXPORT bool wxPrintDialogData_GetAllPages(wxPrintDialogData* self)
    {
        return self->GetAllPages();
    }

    EXPORT bool wxPrintDialogData_GetSelection(wxPrintDialogData* self)
    {
        return self->GetSelection();
    }

    EXPORT bool wxPrintDialogData_GetCollate(wxPrintDialogData* self)
    {
        return self->GetCollate();
    }

    EXPORT bool wxPrintDialogData_GetPrintToFile(wxPrintDialogData* self)
    {
        return self->GetPrintToFile();
    }

    EXPORT void wxPrintDialogData_SetFromPage(wxPrintDialogData* self, int v)
    {
        self->SetFromPage(v);
    }

    EXPORT void wxPrintDialogData_SetToPage(wxPrintDialogData* self, int v)
    {
        self->SetToPage(v);
    }

    EXPORT void wxPrintDialogData_SetMinPage(wxPrintDialogData* self, int v)
    {
        self->SetMinPage(v);
    }

    EXPORT void wxPrintDialogData_SetMaxPage(wxPrintDialogData* self, int v)
    {
        self->SetMaxPage(v);
    }

    EXPORT void wxPrintDialogData_SetNoCopies(wxPrintDialogData* self, int v)
    {
        self->SetNoCopies(v);
    }

    EXPORT void wxPrintDialogData_SetAllPages(wxPrintDialogData* self, bool flag)
    {
        self->SetAllPages(flag);
    }

    EXPORT void wxPrintDialogData_SetSelection(wxPrintDialogData* self, bool flag)
    {
        self->SetSelection(flag);
    }

    EXPORT void wxPrintDialogData_SetCollate(wxPrintDialogData* self, bool flag)
    {
        self->SetCollate(flag);
    }

    EXPORT void wxPrintDialogData_SetPrintToFile(wxPrintDialogData* self, bool flag)
    {
        self->SetPrintToFile(flag);
    }

    EXPORT void wxPrintDialogData_EnablePrintToFile(wxPrintDialogData* self, bool flag)
    {
        self->EnablePrintToFile(flag);
    }

    EXPORT void wxPrintDialogData_EnableSelection(wxPrintDialogData* self, bool flag)
    {
        self->EnableSelection(flag);
    }

    EXPORT void wxPrintDialogData_EnablePageNumbers(wxPrintDialogData* self, bool flag)
    {
        self->EnablePageNumbers(flag);
    }

    EXPORT void wxPrintDialogData_EnableHelp(wxPrintDialogData* self, bool flag)
    {
        self->EnableHelp(flag);
    }

    EXPORT bool wxPrintDialogData_GetEnablePrintToFile(wxPrintDialogData* self)
    {
        return self->GetEnablePrintToFile();
    }

    EXPORT bool wxPrintDialogData_GetEnableSelection(wxPrintDialogData* self)
    {
        return self->GetEnableSelection();
    }

    EXPORT bool wxPrintDialogData_GetEnablePageNumbers(wxPrintDialogData* self)
    {
        return self->GetEnablePageNumbers();
    }

    EXPORT bool wxPrintDialogData_GetEnableHelp(wxPrintDialogData* self)
    {
        return self->GetEnableHelp();
    }

    EXPORT void wxPrintDialogData_GetPrintData(wxPrintDialogData* self, wxPrintData* _ref)
    {
        *_ref = self->GetPrintData();
    }

    EXPORT void wxPrintDialogData_SetPrintData(wxPrintDialogData* self, wxPrintData* printData)
    {
        self->SetPrintData(*printData);
    }

    EXPORT void wxPrintDialogData_Assign(wxPrintDialogData* self, wxPrintDialogData* data)
    {
        *self = *data;
    }

    EXPORT void wxPrintDialogData_AssignData(wxPrintDialogData* self, wxPrintData* data)
    {
        *self = *data;
    }

    EXPORT wxPostScriptDC* wxPostScriptDC_Create(wxPrintData* printData)
    {
#ifdef wxUSE_POSTSCRIPT
        return new wxPostScriptDC(*printData);
#else
        return nullptr;
#endif
    }

    EXPORT void wxPostScriptDC_Delete(wxPostScriptDC* self)
    {
#ifdef wxUSE_POSTSCRIPT
        if (self)
            delete self;
#endif
    }

    EXPORT void wxPostScriptDC_SetResolution(wxPostScriptDC* self, int ppi)
    {
        // SetResolution was removed in wxWidgets 2.9+
    }

    EXPORT int wxPostScriptDC_GetResolution(wxPostScriptDC* self, int ppi)
    {
#ifdef wxUSE_POSTSCRIPT
        return self->GetResolution();
#else
        return 0;
#endif
    }

    EXPORT void* wxPrinterDC_Create(wxPrintData* printData)
    {
#if defined(__WXGTK__)
        return nullptr;
#else
        return new wxPrinterDC(*printData);
#endif
    }

    EXPORT void wxPrinterDC_Delete(void* self)
    {
#if !defined(__WXGTK__)
        delete (wxPrinterDC*) self;
#endif
    }

    EXPORT wxRect* wxPrinterDC_GetPaperRect(void* self)
    {
#if !defined(__WXGTK__)
        wxRect* rct = new wxRect();
        *rct = ((wxPrinterDC*) self)->GetPaperRect();
        return rct;
#else
        return 0;
#endif
    }
}
