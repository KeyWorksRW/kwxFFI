// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// Rich text dialogs: symbol picker, formatting dialog and style organiser.
// Declarations: include/kwx_richtext.h

extern "C"
{
    // ------------------------------------------------------------------
    // wxSymbolPickerDialog
    // ------------------------------------------------------------------

    EXPORT wxSymbolPickerDialog* wxSymbolPickerDialog_Create(wxString* symbol, wxString* fontName,
                                                             wxString* normalTextFont,
                                                             wxWindow* parent, int windowId,
                                                             wxString* caption, int x, int y,
                                                             int width, int height, long style)
    {
        return new wxSymbolPickerDialog(*symbol, *fontName, *normalTextFont, parent, windowId,
                                        *caption, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxSymbolPickerDialog_Delete(wxSymbolPickerDialog* self)
    {
        delete self;
    }

    EXPORT int wxSymbolPickerDialog_GetSymbolChar(wxSymbolPickerDialog* self)
    {
        return self->GetSymbolChar();
    }

    EXPORT bool wxSymbolPickerDialog_HasSelection(wxSymbolPickerDialog* self)
    {
        return self->HasSelection();
    }

    EXPORT bool wxSymbolPickerDialog_UseNormalFont(wxSymbolPickerDialog* self)
    {
        return self->UseNormalFont();
    }

    EXPORT void wxSymbolPickerDialog_SetUnicodeMode(wxSymbolPickerDialog* self, bool unicodeMode)
    {
        self->SetUnicodeMode(unicodeMode);
    }

    EXPORT void wxSymbolPickerDialog_ShowAtSubset(wxSymbolPickerDialog* self)
    {
        self->ShowAtSubset();
    }

    EXPORT wxString* wxSymbolPickerDialog_GetSymbol(wxSymbolPickerDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetSymbol();
        return result;
    }

    EXPORT void wxSymbolPickerDialog_SetSymbol(wxSymbolPickerDialog* self, wxString* symbol)
    {
        self->SetSymbol(*symbol);
    }

    EXPORT wxString* wxSymbolPickerDialog_GetFontName(wxSymbolPickerDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetFontName();
        return result;
    }

    EXPORT void wxSymbolPickerDialog_SetFontName(wxSymbolPickerDialog* self, wxString* fontName)
    {
        self->SetFontName(*fontName);
    }

    EXPORT bool wxSymbolPickerDialog_GetFromUnicode(wxSymbolPickerDialog* self)
    {
        return self->GetFromUnicode();
    }

    EXPORT void wxSymbolPickerDialog_SetFromUnicode(wxSymbolPickerDialog* self, bool fromUnicode)
    {
        self->SetFromUnicode(fromUnicode);
    }

    EXPORT wxString* wxSymbolPickerDialog_GetNormalTextFontName(wxSymbolPickerDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetNormalTextFontName();
        return result;
    }

    EXPORT void wxSymbolPickerDialog_SetNormalTextFontName(wxSymbolPickerDialog* self,
                                                           wxString* fontName)
    {
        self->SetNormalTextFontName(*fontName);
    }

    // ------------------------------------------------------------------
    // wxRichTextFormattingDialog
    // ------------------------------------------------------------------

    EXPORT wxRichTextFormattingDialog*
        wxRichTextFormattingDialog_Create(long flags, wxWindow* parent, wxString* title,
                                          int windowId, int x, int y, int width, int height,
                                          long style)
    {
        return new wxRichTextFormattingDialog(flags, parent, *title, windowId, wxPoint(x, y),
                                              wxSize(width, height), style);
    }

    EXPORT void wxRichTextFormattingDialog_Delete(wxRichTextFormattingDialog* self)
    {
        delete self;
    }

    EXPORT bool wxRichTextFormattingDialog_GetStyle(wxRichTextFormattingDialog* self,
                                                    wxRichTextCtrl* ctrl, long startPos,
                                                    long endPos)
    {
        return self->GetStyle(ctrl, wxRichTextRange(startPos, endPos));
    }

    EXPORT bool wxRichTextFormattingDialog_SetStyle(wxRichTextFormattingDialog* self,
                                                    wxRichTextAttr* style, bool update)
    {
        return self->SetStyle(*style, update);
    }

    EXPORT bool wxRichTextFormattingDialog_SetStyleDefinition(wxRichTextFormattingDialog* self,
                                                              wxRichTextStyleDefinition* styleDef,
                                                              wxRichTextStyleSheet* sheet,
                                                              bool update)
    {
        return self->SetStyleDefinition(*styleDef, sheet, update);
    }

    EXPORT wxRichTextStyleDefinition*
        wxRichTextFormattingDialog_GetStyleDefinition(wxRichTextFormattingDialog* self)
    {
        return self->GetStyleDefinition();
    }

    EXPORT wxRichTextStyleSheet*
        wxRichTextFormattingDialog_GetStyleSheet(wxRichTextFormattingDialog* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT bool wxRichTextFormattingDialog_UpdateDisplay(wxRichTextFormattingDialog* self)
    {
        return self->UpdateDisplay();
    }

    EXPORT bool wxRichTextFormattingDialog_ApplyStyle(wxRichTextFormattingDialog* self,
                                                      wxRichTextCtrl* ctrl, long startPos,
                                                      long endPos, int flags)
    {
        return self->ApplyStyle(ctrl, wxRichTextRange(startPos, endPos), flags);
    }

    EXPORT void wxRichTextFormattingDialog_GetAttributes(wxRichTextFormattingDialog* self,
                                                         wxRichTextAttr* attr)
    {
        *attr = self->GetAttributes();
    }

    EXPORT void wxRichTextFormattingDialog_SetAttributes(wxRichTextFormattingDialog* self,
                                                         wxRichTextAttr* attr)
    {
        self->SetAttributes(*attr);
    }

    EXPORT void wxRichTextFormattingDialog_SetOptions(wxRichTextFormattingDialog* self, int options)
    {
        self->SetOptions(options);
    }

    EXPORT int wxRichTextFormattingDialog_GetOptions(wxRichTextFormattingDialog* self)
    {
        return self->GetOptions();
    }

    EXPORT bool wxRichTextFormattingDialog_HasOption(wxRichTextFormattingDialog* self, int option)
    {
        return self->HasOption(option);
    }

    EXPORT wxRichTextObject* wxRichTextFormattingDialog_GetObject(wxRichTextFormattingDialog* self)
    {
        return self->GetObject();
    }

    EXPORT void wxRichTextFormattingDialog_SetObject(wxRichTextFormattingDialog* self,
                                                     wxRichTextObject* obj)
    {
        self->SetObject(obj);
    }

    EXPORT bool wxRichTextFormattingDialog_TransferDataToWindow(wxRichTextFormattingDialog* self)
    {
        return self->TransferDataToWindow();
    }

    EXPORT bool wxRichTextFormattingDialog_TransferDataFromWindow(wxRichTextFormattingDialog* self)
    {
        return self->TransferDataFromWindow();
    }

    // ------------------------------------------------------------------
    // wxRichTextStyleOrganiserDialog
    // ------------------------------------------------------------------

    EXPORT wxRichTextStyleOrganiserDialog* wxRichTextStyleOrganiserDialog_Create(
        int flags, wxRichTextStyleSheet* sheet, wxRichTextCtrl* ctrl, wxWindow* parent,
        int windowId, wxString* caption, int x, int y, int width, int height, long style)
    {
        return new wxRichTextStyleOrganiserDialog(flags, sheet, ctrl, parent, windowId, *caption,
                                                  wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxRichTextStyleOrganiserDialog_Delete(wxRichTextStyleOrganiserDialog* self)
    {
        delete self;
    }

    EXPORT void wxRichTextStyleOrganiserDialog_SetStyleSheet(wxRichTextStyleOrganiserDialog* self,
                                                             wxRichTextStyleSheet* sheet)
    {
        self->SetStyleSheet(sheet);
    }

    EXPORT wxRichTextStyleSheet*
        wxRichTextStyleOrganiserDialog_GetStyleSheet(wxRichTextStyleOrganiserDialog* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT void wxRichTextStyleOrganiserDialog_SetRichTextCtrl(wxRichTextStyleOrganiserDialog* self,
                                                               wxRichTextCtrl* ctrl)
    {
        self->SetRichTextCtrl(ctrl);
    }

    EXPORT wxRichTextCtrl*
        wxRichTextStyleOrganiserDialog_GetRichTextCtrl(wxRichTextStyleOrganiserDialog* self)
    {
        return self->GetRichTextCtrl();
    }

    EXPORT void wxRichTextStyleOrganiserDialog_SetFlags(wxRichTextStyleOrganiserDialog* self,
                                                        int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT int wxRichTextStyleOrganiserDialog_GetFlags(wxRichTextStyleOrganiserDialog* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxRichTextStyleOrganiserDialog_ShowPreview(wxRichTextStyleOrganiserDialog* self,
                                                           int sel)
    {
        self->ShowPreview(sel);
    }

    EXPORT void wxRichTextStyleOrganiserDialog_ClearPreview(wxRichTextStyleOrganiserDialog* self)
    {
        self->ClearPreview();
    }

    EXPORT bool
        wxRichTextStyleOrganiserDialog_GetRestartNumbering(wxRichTextStyleOrganiserDialog* self)
    {
        return self->GetRestartNumbering();
    }

    EXPORT void
        wxRichTextStyleOrganiserDialog_SetRestartNumbering(wxRichTextStyleOrganiserDialog* self,
                                                           bool restartNumbering)
    {
        self->SetRestartNumbering(restartNumbering);
    }

    EXPORT wxString*
        wxRichTextStyleOrganiserDialog_GetSelectedStyle(wxRichTextStyleOrganiserDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetSelectedStyle();
        return result;
    }

    EXPORT wxRichTextStyleDefinition* wxRichTextStyleOrganiserDialog_GetSelectedStyleDefinition(
        wxRichTextStyleOrganiserDialog* self)
    {
        return self->GetSelectedStyleDefinition();
    }

    EXPORT bool wxRichTextStyleOrganiserDialog_ApplyStyle(wxRichTextStyleOrganiserDialog* self,
                                                          wxRichTextCtrl* ctrl)
    {
        return self->ApplyStyle(ctrl);
    }
}
