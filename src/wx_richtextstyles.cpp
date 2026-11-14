// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// Rich text style list box and buffer data object.
// Declarations: include/kwx_richtext.h

extern "C"
{
    // ------------------------------------------------------------------
    // wxRichTextStyleListBox
    // ------------------------------------------------------------------

    EXPORT wxRichTextStyleListBox* wxRichTextStyleListBox_Create(wxWindow* parent, int windowId,
                                                                 int x, int y, int width,
                                                                 int height, long style)
    {
        return new wxRichTextStyleListBox(parent, windowId, wxPoint(x, y), wxSize(width, height),
                                          style);
    }

    EXPORT void wxRichTextStyleListBox_Delete(wxRichTextStyleListBox* self)
    {
        delete self;
    }

    EXPORT void wxRichTextStyleListBox_SetStyleSheet(wxRichTextStyleListBox* self,
                                                     wxRichTextStyleSheet* styleSheet)
    {
        self->SetStyleSheet(styleSheet);
    }

    EXPORT wxRichTextStyleSheet* wxRichTextStyleListBox_GetStyleSheet(wxRichTextStyleListBox* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT void wxRichTextStyleListBox_SetRichTextCtrl(wxRichTextStyleListBox* self,
                                                       wxRichTextCtrl* ctrl)
    {
        self->SetRichTextCtrl(ctrl);
    }

    EXPORT wxRichTextCtrl* wxRichTextStyleListBox_GetRichTextCtrl(wxRichTextStyleListBox* self)
    {
        return self->GetRichTextCtrl();
    }

    EXPORT wxRichTextStyleDefinition* wxRichTextStyleListBox_GetStyle(wxRichTextStyleListBox* self,
                                                                      size_t index)
    {
        return self->GetStyle(index);
    }

    EXPORT int wxRichTextStyleListBox_GetIndexForStyle(wxRichTextStyleListBox* self, wxString* name)
    {
        return self->GetIndexForStyle(*name);
    }

    EXPORT int wxRichTextStyleListBox_SetStyleSelection(wxRichTextStyleListBox* self,
                                                        wxString* name)
    {
        return self->SetStyleSelection(*name);
    }

    EXPORT void wxRichTextStyleListBox_UpdateStyles(wxRichTextStyleListBox* self)
    {
        self->UpdateStyles();
    }

    EXPORT void wxRichTextStyleListBox_ApplyStyle(wxRichTextStyleListBox* self, int index)
    {
        self->ApplyStyle(index);
    }

    EXPORT void wxRichTextStyleListBox_SetApplyOnSelection(wxRichTextStyleListBox* self,
                                                           bool applyOnSelection)
    {
        self->SetApplyOnSelection(applyOnSelection);
    }

    EXPORT int wxRichTextStyleListBox_GetApplyOnSelection(wxRichTextStyleListBox* self)
    {
        return self->GetApplyOnSelection();
    }

    EXPORT void wxRichTextStyleListBox_SetStyleType(wxRichTextStyleListBox* self, int styleType)
    {
        self->SetStyleType(static_cast<wxRichTextStyleListBox::wxRichTextStyleType>(styleType));
    }

    EXPORT int wxRichTextStyleListBox_GetStyleType(wxRichTextStyleListBox* self)
    {
        return static_cast<int>(self->GetStyleType());
    }

    EXPORT void wxRichTextStyleListBox_SetAutoSetSelection(wxRichTextStyleListBox* self,
                                                           bool autoSet)
    {
        self->SetAutoSetSelection(autoSet);
    }

    EXPORT int wxRichTextStyleListBox_CanAutoSetSelection(wxRichTextStyleListBox* self)
    {
        return self->CanAutoSetSelection();
    }

    // ------------------------------------------------------------------
    // wxRichTextBufferDataObject
    // ------------------------------------------------------------------

    EXPORT wxRichTextBufferDataObject*
        wxRichTextBufferDataObject_Create(wxRichTextBuffer* richTextBuffer)
    {
        return new wxRichTextBufferDataObject(richTextBuffer);
    }

    EXPORT void wxRichTextBufferDataObject_Delete(wxRichTextBufferDataObject* self)
    {
        delete self;
    }

    EXPORT wxRichTextBuffer*
        wxRichTextBufferDataObject_GetRichTextBuffer(wxRichTextBufferDataObject* self)
    {
        return self->GetRichTextBuffer();
    }

    EXPORT wxString* wxRichTextBufferDataObject_GetRichTextBufferFormatId(
        [[maybe_unused]] wxRichTextBufferDataObject* self)
    {
        wxString* result = new wxString();
        *result = wxString(wxRichTextBufferDataObject::GetRichTextBufferFormatId());
        return result;
    }

    EXPORT size_t wxRichTextBufferDataObject_GetDataSize(wxRichTextBufferDataObject* self)
    {
        return self->GetDataSize();
    }

    // ------------------------------------------------------------------
    // wxRichTextStyleDefinition
    // ------------------------------------------------------------------

    EXPORT void wxRichTextStyleDefinition_Copy(wxRichTextStyleDefinition* self,
                                               wxRichTextStyleDefinition* def)
    {
        self->Copy(*def);
    }

    EXPORT int wxRichTextStyleDefinition_Eq(wxRichTextStyleDefinition* self,
                                            wxRichTextStyleDefinition* def)
    {
        return self->Eq(*def);
    }

    EXPORT void wxRichTextStyleDefinition_SetName(wxRichTextStyleDefinition* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxRichTextStyleDefinition_GetName(wxRichTextStyleDefinition* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxRichTextStyleDefinition_SetDescription(wxRichTextStyleDefinition* self,
                                                         wxString* descr)
    {
        self->SetDescription(*descr);
    }

    EXPORT wxString* wxRichTextStyleDefinition_GetDescription(wxRichTextStyleDefinition* self)
    {
        wxString* result = new wxString();
        *result = self->GetDescription();
        return result;
    }

    EXPORT void wxRichTextStyleDefinition_SetBaseStyle(wxRichTextStyleDefinition* self,
                                                       wxString* name)
    {
        self->SetBaseStyle(*name);
    }

    EXPORT wxString* wxRichTextStyleDefinition_GetBaseStyle(wxRichTextStyleDefinition* self)
    {
        wxString* result = new wxString();
        *result = self->GetBaseStyle();
        return result;
    }

    EXPORT void wxRichTextStyleDefinition_SetStyle(wxRichTextStyleDefinition* self,
                                                   wxRichTextAttr* style)
    {
        self->SetStyle(*style);
    }

    // Borrowed subobject of the definition -- never delete the returned pointer.
    EXPORT wxRichTextAttr* wxRichTextStyleDefinition_GetStyle(wxRichTextStyleDefinition* self)
    {
        return &self->GetStyle();
    }

    // Borrowed subobject of the definition -- never delete the returned pointer.
    EXPORT wxRichTextProperties*
        wxRichTextStyleDefinition_GetProperties(wxRichTextStyleDefinition* self)
    {
        return &self->GetProperties();
    }

    EXPORT void wxRichTextStyleDefinition_SetProperties(wxRichTextStyleDefinition* self,
                                                        wxRichTextProperties* props)
    {
        self->SetProperties(*props);
    }

    // ------------------------------------------------------------------
    // wxRichTextCharacterStyleDefinition
    // ------------------------------------------------------------------

    EXPORT wxRichTextCharacterStyleDefinition*
        wxRichTextCharacterStyleDefinition_Create(wxString* name)
    {
        return new wxRichTextCharacterStyleDefinition(*name);
    }

    EXPORT void wxRichTextCharacterStyleDefinition_Delete(wxRichTextCharacterStyleDefinition* self)
    {
        delete self;
    }

    // ------------------------------------------------------------------
    // wxRichTextParagraphStyleDefinition
    // ------------------------------------------------------------------

    EXPORT wxRichTextParagraphStyleDefinition*
        wxRichTextParagraphStyleDefinition_Create(wxString* name)
    {
        return new wxRichTextParagraphStyleDefinition(*name);
    }

    EXPORT void wxRichTextParagraphStyleDefinition_Delete(wxRichTextParagraphStyleDefinition* self)
    {
        delete self;
    }

    EXPORT void
        wxRichTextParagraphStyleDefinition_SetNextStyle(wxRichTextParagraphStyleDefinition* self,
                                                        wxString* name)
    {
        self->SetNextStyle(*name);
    }

    EXPORT wxString*
        wxRichTextParagraphStyleDefinition_GetNextStyle(wxRichTextParagraphStyleDefinition* self)
    {
        wxString* result = new wxString();
        *result = self->GetNextStyle();
        return result;
    }

    EXPORT void wxRichTextParagraphStyleDefinition_Copy(wxRichTextParagraphStyleDefinition* self,
                                                        wxRichTextParagraphStyleDefinition* def)
    {
        self->Copy(*def);
    }

    // ------------------------------------------------------------------
    // wxRichTextListStyleDefinition
    // ------------------------------------------------------------------

    EXPORT wxRichTextListStyleDefinition* wxRichTextListStyleDefinition_Create(wxString* name)
    {
        return new wxRichTextListStyleDefinition(*name);
    }

    EXPORT void wxRichTextListStyleDefinition_Delete(wxRichTextListStyleDefinition* self)
    {
        delete self;
    }

    EXPORT void wxRichTextListStyleDefinition_Copy(wxRichTextListStyleDefinition* self,
                                                   wxRichTextListStyleDefinition* def)
    {
        self->Copy(*def);
    }

    EXPORT void
        wxRichTextListStyleDefinition_SetLevelAttributes(wxRichTextListStyleDefinition* self,
                                                         int level, wxRichTextAttr* attr)
    {
        self->SetLevelAttributes(level, *attr);
    }

    // Borrowed level style owned by the definition -- never delete the returned pointer.
    EXPORT wxRichTextAttr*
        wxRichTextListStyleDefinition_GetLevelAttributes(wxRichTextListStyleDefinition* self,
                                                         int level)
    {
        return self->GetLevelAttributes(level);
    }

    EXPORT void wxRichTextListStyleDefinition_SetAttributes(wxRichTextListStyleDefinition* self,
                                                            int level, int leftIndent,
                                                            int leftSubIndent, int bulletStyle,
                                                            wxString* bulletSymbol)
    {
        self->SetAttributes(level, leftIndent, leftSubIndent, bulletStyle, *bulletSymbol);
    }

    EXPORT int wxRichTextListStyleDefinition_FindLevelForIndent(wxRichTextListStyleDefinition* self,
                                                                int indent)
    {
        return self->FindLevelForIndent(indent);
    }

    EXPORT wxRichTextAttr* wxRichTextListStyleDefinition_CombineWithParagraphStyle(
        wxRichTextListStyleDefinition* self, int indent, wxRichTextAttr* paraStyle,
        wxRichTextStyleSheet* styleSheet)
    {
        return new wxRichTextAttr(self->CombineWithParagraphStyle(indent, *paraStyle, styleSheet));
    }

    EXPORT wxRichTextAttr*
        wxRichTextListStyleDefinition_GetCombinedStyle(wxRichTextListStyleDefinition* self,
                                                       int indent, wxRichTextStyleSheet* styleSheet)
    {
        return new wxRichTextAttr(self->GetCombinedStyle(indent, styleSheet));
    }

    EXPORT wxRichTextAttr* wxRichTextListStyleDefinition_GetCombinedStyleForLevel(
        wxRichTextListStyleDefinition* self, int level, wxRichTextStyleSheet* styleSheet)
    {
        return new wxRichTextAttr(self->GetCombinedStyleForLevel(level, styleSheet));
    }

    EXPORT int wxRichTextListStyleDefinition_GetLevelCount(wxRichTextListStyleDefinition* self)
    {
        return self->GetLevelCount();
    }

    EXPORT int wxRichTextListStyleDefinition_IsNumbered(wxRichTextListStyleDefinition* self,
                                                        int level)
    {
        return self->IsNumbered(level);
    }

    // ------------------------------------------------------------------
    // wxRichTextBoxStyleDefinition
    // ------------------------------------------------------------------

    EXPORT wxRichTextBoxStyleDefinition* wxRichTextBoxStyleDefinition_Create(wxString* name)
    {
        return new wxRichTextBoxStyleDefinition(*name);
    }

    EXPORT void wxRichTextBoxStyleDefinition_Delete(wxRichTextBoxStyleDefinition* self)
    {
        delete self;
    }

    EXPORT void wxRichTextBoxStyleDefinition_Copy(wxRichTextBoxStyleDefinition* self,
                                                  wxRichTextBoxStyleDefinition* def)
    {
        self->Copy(*def);
    }

    // ------------------------------------------------------------------
    // wxRichTextStyleSheet
    // ------------------------------------------------------------------

    EXPORT wxRichTextStyleSheet* wxRichTextStyleSheet_Create()
    {
        return new wxRichTextStyleSheet();
    }

    EXPORT wxRichTextStyleSheet* wxRichTextStyleSheet_CreateCopy(wxRichTextStyleSheet* sheet)
    {
        return new wxRichTextStyleSheet(*sheet);
    }

    EXPORT void wxRichTextStyleSheet_Delete(wxRichTextStyleSheet* self)
    {
        delete self;
    }

    EXPORT void wxRichTextStyleSheet_Init(wxRichTextStyleSheet* self)
    {
        self->Init();
    }

    EXPORT void wxRichTextStyleSheet_Copy(wxRichTextStyleSheet* self, wxRichTextStyleSheet* sheet)
    {
        self->Copy(*sheet);
    }

    // The style sheet takes ownership of def; do not Delete() it afterwards.
    EXPORT int wxRichTextStyleSheet_AddCharacterStyle(wxRichTextStyleSheet* self,
                                                      wxRichTextCharacterStyleDefinition* def)
    {
        return self->AddCharacterStyle(def);
    }

    // The style sheet takes ownership of def; do not Delete() it afterwards.
    EXPORT int wxRichTextStyleSheet_AddParagraphStyle(wxRichTextStyleSheet* self,
                                                      wxRichTextParagraphStyleDefinition* def)
    {
        return self->AddParagraphStyle(def);
    }

    // The style sheet takes ownership of def; do not Delete() it afterwards.
    EXPORT int wxRichTextStyleSheet_AddListStyle(wxRichTextStyleSheet* self,
                                                 wxRichTextListStyleDefinition* def)
    {
        return self->AddListStyle(def);
    }

    // The style sheet takes ownership of def; do not Delete() it afterwards.
    EXPORT int wxRichTextStyleSheet_AddBoxStyle(wxRichTextStyleSheet* self,
                                                wxRichTextBoxStyleDefinition* def)
    {
        return self->AddBoxStyle(def);
    }

    // The style sheet takes ownership of def; do not Delete() it afterwards.
    EXPORT int wxRichTextStyleSheet_AddStyle(wxRichTextStyleSheet* self,
                                             wxRichTextStyleDefinition* def)
    {
        return self->AddStyle(def);
    }

    EXPORT int wxRichTextStyleSheet_RemoveCharacterStyle(wxRichTextStyleSheet* self,
                                                         wxRichTextStyleDefinition* def,
                                                         bool deleteStyle)
    {
        return self->RemoveCharacterStyle(def, deleteStyle);
    }

    EXPORT int wxRichTextStyleSheet_RemoveParagraphStyle(wxRichTextStyleSheet* self,
                                                         wxRichTextStyleDefinition* def,
                                                         bool deleteStyle)
    {
        return self->RemoveParagraphStyle(def, deleteStyle);
    }

    EXPORT int wxRichTextStyleSheet_RemoveListStyle(wxRichTextStyleSheet* self,
                                                    wxRichTextStyleDefinition* def,
                                                    bool deleteStyle)
    {
        return self->RemoveListStyle(def, deleteStyle);
    }

    EXPORT int wxRichTextStyleSheet_RemoveBoxStyle(wxRichTextStyleSheet* self,
                                                   wxRichTextStyleDefinition* def, bool deleteStyle)
    {
        return self->RemoveBoxStyle(def, deleteStyle);
    }

    EXPORT int wxRichTextStyleSheet_RemoveStyle(wxRichTextStyleSheet* self,
                                                wxRichTextStyleDefinition* def, bool deleteStyle)
    {
        return self->RemoveStyle(def, deleteStyle);
    }

    EXPORT wxRichTextCharacterStyleDefinition*
        wxRichTextStyleSheet_FindCharacterStyle(wxRichTextStyleSheet* self, wxString* name,
                                                bool recurse)
    {
        return self->FindCharacterStyle(*name, recurse);
    }

    EXPORT wxRichTextParagraphStyleDefinition*
        wxRichTextStyleSheet_FindParagraphStyle(wxRichTextStyleSheet* self, wxString* name,
                                                bool recurse)
    {
        return self->FindParagraphStyle(*name, recurse);
    }

    EXPORT wxRichTextListStyleDefinition*
        wxRichTextStyleSheet_FindListStyle(wxRichTextStyleSheet* self, wxString* name, bool recurse)
    {
        return self->FindListStyle(*name, recurse);
    }

    EXPORT wxRichTextBoxStyleDefinition*
        wxRichTextStyleSheet_FindBoxStyle(wxRichTextStyleSheet* self, wxString* name, bool recurse)
    {
        return self->FindBoxStyle(*name, recurse);
    }

    EXPORT wxRichTextStyleDefinition* wxRichTextStyleSheet_FindStyle(wxRichTextStyleSheet* self,
                                                                     wxString* name, bool recurse)
    {
        return self->FindStyle(*name, recurse);
    }

    EXPORT size_t wxRichTextStyleSheet_GetCharacterStyleCount(wxRichTextStyleSheet* self)
    {
        return self->GetCharacterStyleCount();
    }

    EXPORT size_t wxRichTextStyleSheet_GetParagraphStyleCount(wxRichTextStyleSheet* self)
    {
        return self->GetParagraphStyleCount();
    }

    EXPORT size_t wxRichTextStyleSheet_GetListStyleCount(wxRichTextStyleSheet* self)
    {
        return self->GetListStyleCount();
    }

    EXPORT size_t wxRichTextStyleSheet_GetBoxStyleCount(wxRichTextStyleSheet* self)
    {
        return self->GetBoxStyleCount();
    }

    EXPORT wxRichTextCharacterStyleDefinition*
        wxRichTextStyleSheet_GetCharacterStyle(wxRichTextStyleSheet* self, size_t index)
    {
        return self->GetCharacterStyle(index);
    }

    EXPORT wxRichTextParagraphStyleDefinition*
        wxRichTextStyleSheet_GetParagraphStyle(wxRichTextStyleSheet* self, size_t index)
    {
        return self->GetParagraphStyle(index);
    }

    EXPORT wxRichTextListStyleDefinition*
        wxRichTextStyleSheet_GetListStyle(wxRichTextStyleSheet* self, size_t index)
    {
        return self->GetListStyle(index);
    }

    EXPORT wxRichTextBoxStyleDefinition*
        wxRichTextStyleSheet_GetBoxStyle(wxRichTextStyleSheet* self, size_t index)
    {
        return self->GetBoxStyle(index);
    }

    EXPORT void wxRichTextStyleSheet_DeleteStyles(wxRichTextStyleSheet* self)
    {
        self->DeleteStyles();
    }

    EXPORT int wxRichTextStyleSheet_InsertSheet(wxRichTextStyleSheet* self,
                                                wxRichTextStyleSheet* before)
    {
        return self->InsertSheet(before);
    }

    EXPORT int wxRichTextStyleSheet_AppendSheet(wxRichTextStyleSheet* self,
                                                wxRichTextStyleSheet* after)
    {
        return self->AppendSheet(after);
    }

    EXPORT void wxRichTextStyleSheet_Unlink(wxRichTextStyleSheet* self)
    {
        self->Unlink();
    }

    EXPORT wxRichTextStyleSheet* wxRichTextStyleSheet_GetNextSheet(wxRichTextStyleSheet* self)
    {
        return self->GetNextSheet();
    }

    EXPORT void wxRichTextStyleSheet_SetNextSheet(wxRichTextStyleSheet* self,
                                                  wxRichTextStyleSheet* sheet)
    {
        self->SetNextSheet(sheet);
    }

    EXPORT wxRichTextStyleSheet* wxRichTextStyleSheet_GetPreviousSheet(wxRichTextStyleSheet* self)
    {
        return self->GetPreviousSheet();
    }

    EXPORT void wxRichTextStyleSheet_SetPreviousSheet(wxRichTextStyleSheet* self,
                                                      wxRichTextStyleSheet* sheet)
    {
        self->SetPreviousSheet(sheet);
    }

    EXPORT void wxRichTextStyleSheet_SetName(wxRichTextStyleSheet* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxRichTextStyleSheet_GetName(wxRichTextStyleSheet* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxRichTextStyleSheet_SetDescription(wxRichTextStyleSheet* self, wxString* descr)
    {
        self->SetDescription(*descr);
    }

    EXPORT wxString* wxRichTextStyleSheet_GetDescription(wxRichTextStyleSheet* self)
    {
        wxString* result = new wxString();
        *result = self->GetDescription();
        return result;
    }

    // Borrowed subobject of the style sheet -- never delete the returned pointer.
    EXPORT wxRichTextProperties* wxRichTextStyleSheet_GetProperties(wxRichTextStyleSheet* self)
    {
        return &self->GetProperties();
    }

    EXPORT void wxRichTextStyleSheet_SetProperties(wxRichTextStyleSheet* self,
                                                   wxRichTextProperties* props)
    {
        self->SetProperties(*props);
    }

    // ------------------------------------------------------------------
    // wxRichTextStyleListCtrl
    // ------------------------------------------------------------------

    EXPORT wxRichTextStyleListCtrl* wxRichTextStyleListCtrl_Create(wxWindow* parent, int windowId,
                                                                   int x, int y, int width,
                                                                   int height, long style)
    {
        return new wxRichTextStyleListCtrl(parent, windowId, wxPoint(x, y), wxSize(width, height),
                                           style);
    }

    EXPORT void wxRichTextStyleListCtrl_Delete(wxRichTextStyleListCtrl* self)
    {
        delete self;
    }

    EXPORT void wxRichTextStyleListCtrl_UpdateStyles(wxRichTextStyleListCtrl* self)
    {
        self->UpdateStyles();
    }

    EXPORT void wxRichTextStyleListCtrl_SetStyleSheet(wxRichTextStyleListCtrl* self,
                                                      wxRichTextStyleSheet* styleSheet)
    {
        self->SetStyleSheet(styleSheet);
    }

    EXPORT wxRichTextStyleSheet*
        wxRichTextStyleListCtrl_GetStyleSheet(wxRichTextStyleListCtrl* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT void wxRichTextStyleListCtrl_SetRichTextCtrl(wxRichTextStyleListCtrl* self,
                                                        wxRichTextCtrl* ctrl)
    {
        self->SetRichTextCtrl(ctrl);
    }

    EXPORT wxRichTextCtrl* wxRichTextStyleListCtrl_GetRichTextCtrl(wxRichTextStyleListCtrl* self)
    {
        return self->GetRichTextCtrl();
    }

    EXPORT void wxRichTextStyleListCtrl_SetStyleType(wxRichTextStyleListCtrl* self, int styleType)
    {
        self->SetStyleType(static_cast<wxRichTextStyleListBox::wxRichTextStyleType>(styleType));
    }

    EXPORT int wxRichTextStyleListCtrl_GetStyleType(wxRichTextStyleListCtrl* self)
    {
        return static_cast<int>(self->GetStyleType());
    }

    EXPORT wxRichTextStyleListBox*
        wxRichTextStyleListCtrl_GetStyleListBox(wxRichTextStyleListCtrl* self)
    {
        return self->GetStyleListBox();
    }

    EXPORT wxChoice* wxRichTextStyleListCtrl_GetStyleChoice(wxRichTextStyleListCtrl* self)
    {
        return self->GetStyleChoice();
    }

    // ------------------------------------------------------------------
    // wxRichTextStyleComboCtrl
    // ------------------------------------------------------------------

    EXPORT wxRichTextStyleComboCtrl* wxRichTextStyleComboCtrl_Create(wxWindow* parent, int windowId,
                                                                     int x, int y, int width,
                                                                     int height, long style)
    {
        return new wxRichTextStyleComboCtrl(parent, windowId, wxPoint(x, y), wxSize(width, height),
                                            style);
    }

    EXPORT void wxRichTextStyleComboCtrl_Delete(wxRichTextStyleComboCtrl* self)
    {
        delete self;
    }

    EXPORT void wxRichTextStyleComboCtrl_UpdateStyles(wxRichTextStyleComboCtrl* self)
    {
        self->UpdateStyles();
    }

    EXPORT void wxRichTextStyleComboCtrl_SetStyleSheet(wxRichTextStyleComboCtrl* self,
                                                       wxRichTextStyleSheet* styleSheet)
    {
        self->SetStyleSheet(styleSheet);
    }

    EXPORT wxRichTextStyleSheet*
        wxRichTextStyleComboCtrl_GetStyleSheet(wxRichTextStyleComboCtrl* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT void wxRichTextStyleComboCtrl_SetRichTextCtrl(wxRichTextStyleComboCtrl* self,
                                                         wxRichTextCtrl* ctrl)
    {
        self->SetRichTextCtrl(ctrl);
    }

    EXPORT wxRichTextCtrl* wxRichTextStyleComboCtrl_GetRichTextCtrl(wxRichTextStyleComboCtrl* self)
    {
        return self->GetRichTextCtrl();
    }
}
