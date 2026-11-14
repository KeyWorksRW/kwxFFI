// Callback overrides for the three rich-text extension points a foreign language
// cannot derive from itself: wxRichTextCtrl, wxRichTextFieldTypeStandard and
// wxRichTextDrawingHandler.  The declarations live in
// include/kwx_richtext_hooks.h; this file holds the class definitions, the virtual
// overrides and the exported kwx* wrappers.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// ---------------------------------------------------------------------------
// Callback shapes.  Every callback returns void, receives the foreign object
// first and takes at most two further arguments.  A callback that must produce
// a value publishes it with the matching Set*Result function on the same object
// before it returns; a callback that returns without publishing keeps the
// base-class behaviour.  This is the include/kwx_propgrid_hooks.h ABI, and it
// is what lets a runtime whose native thunk is void (*)(void*, void*, void*)
// install every hook — an int-returning callback would answer from an undefined
// return register.
// ---------------------------------------------------------------------------

typedef void (*kwxRtcPrepareContentFunc)(void* pObject, void* container);
typedef void (*kwxRtcCanDeleteRangeFunc)(void* pObject, void* container, void* range);
typedef void (*kwxRtcCanInsertContentFunc)(void* pObject, void* container, long position);
typedef void (*kwxRtfCanEditPropertiesFunc)(void* pObject, void* field);
typedef void (*kwxRtfEditPropertiesFunc)(void* pObject, void* field, void* parent);
typedef void (*kwxRtfGetPropertiesMenuLabelFunc)(void* pObject, void* field);
typedef void (*kwxRtfUpdateFieldFunc)(void* pObject, void* buffer, void* field);
typedef void (*kwxRtfIsTopLevelFunc)(void* pObject, void* field);
typedef void (*kwxRdhHasVirtualAttributesFunc)(void* pObject, void* obj);
typedef void (*kwxRdhGetVirtualAttributesFunc)(void* pObject, void* attr, void* obj);
typedef void (*kwxRdhVirtualSubobjectCountFunc)(void* pObject, void* obj);
typedef void (*kwxRdhHasVirtualTextFunc)(void* pObject, void* obj);
typedef void (*kwxRdhGetVirtualTextFunc)(void* pObject, void* obj);

// ---------------------------------------------------------------------------
// kwxRichTextCtrl
//
// The guard callbacks answer the question the base class answers by sending an
// event, so a callback that is not installed keeps the base behaviour instead of
// silently allowing or rejecting every edit.
// ---------------------------------------------------------------------------

class kwxRichTextCtrl : public wxRichTextCtrl
{
private:
    void* m_object;
    kwxRtcPrepareContentFunc m_prepare_content_func;
    kwxRtcCanDeleteRangeFunc m_can_delete_range_func;
    kwxRtcCanInsertContentFunc m_can_insert_content_func;

    mutable bool m_result_bool;
    mutable bool m_has_result;

public:
    kwxRichTextCtrl(void* pObject, wxWindow* parent, wxWindowID id, const wxString& value,
                    const wxPoint& pos, const wxSize& size, long style);

    void SetOnPrepareContent(void* pFunction)
    {
        m_prepare_content_func = (kwxRtcPrepareContentFunc) pFunction;
    }
    void SetOnCanDeleteRange(void* pFunction)
    {
        m_can_delete_range_func = (kwxRtcCanDeleteRangeFunc) pFunction;
    }
    void SetOnCanInsertContent(void* pFunction)
    {
        m_can_insert_content_func = (kwxRtcCanInsertContentFunc) pFunction;
    }

    void SetCanDeleteRangeResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }
    void SetCanInsertContentResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }

    void PrepareContent(wxRichTextParagraphLayoutBox& container) override;
    bool CanDeleteRange(wxRichTextParagraphLayoutBox& container,
                        const wxRichTextRange& range) const override;
    bool CanInsertContent(wxRichTextParagraphLayoutBox& container, long pos) const override;
};

kwxRichTextCtrl::kwxRichTextCtrl(void* pObject, wxWindow* parent, wxWindowID id,
                                 const wxString& value, const wxPoint& pos, const wxSize& size,
                                 long style) :
    wxRichTextCtrl(parent, id, value, pos, size, style, wxDefaultValidator)
{
    m_object = pObject;
    m_prepare_content_func = nullptr;
    m_can_delete_range_func = nullptr;
    m_can_insert_content_func = nullptr;
    m_result_bool = false;
    m_has_result = false;
}

void kwxRichTextCtrl::PrepareContent(wxRichTextParagraphLayoutBox& container)
{
    if (!m_prepare_content_func)
    {
        wxRichTextCtrl::PrepareContent(container);
        return;
    }
    m_prepare_content_func(m_object, &container);
}

bool kwxRichTextCtrl::CanDeleteRange(wxRichTextParagraphLayoutBox& container,
                                     const wxRichTextRange& range) const
{
    if (!m_can_delete_range_func)
    {
        return wxRichTextCtrl::CanDeleteRange(container, range);
    }

    m_result_bool = false;
    m_has_result = false;
    m_can_delete_range_func(m_object, &container, const_cast<wxRichTextRange*>(&range));
    if (!m_has_result)
    {
        return wxRichTextCtrl::CanDeleteRange(container, range);
    }
    return m_result_bool;
}

bool kwxRichTextCtrl::CanInsertContent(wxRichTextParagraphLayoutBox& container, long pos) const
{
    if (!m_can_insert_content_func)
    {
        return wxRichTextCtrl::CanInsertContent(container, pos);
    }

    m_result_bool = false;
    m_has_result = false;
    m_can_insert_content_func(m_object, &container, pos);
    if (!m_has_result)
    {
        return wxRichTextCtrl::CanInsertContent(container, pos);
    }
    return m_result_bool;
}

// ---------------------------------------------------------------------------
// kwxRichTextFieldTypeStandard
//
// GetPropertiesMenuLabel() is const, so the string a callback publishes lives in
// mutable members that are cleared before every callback invocation.
// ---------------------------------------------------------------------------

class kwxRichTextFieldTypeStandard : public wxRichTextFieldTypeStandard
{
private:
    void* m_object;
    kwxRtfCanEditPropertiesFunc m_can_edit_properties_func;
    kwxRtfEditPropertiesFunc m_edit_properties_func;
    kwxRtfGetPropertiesMenuLabelFunc m_get_properties_menu_label_func;
    kwxRtfUpdateFieldFunc m_update_field_func;
    kwxRtfIsTopLevelFunc m_is_top_level_func;

    mutable wxString m_result_string;
    mutable bool m_result_bool;
    mutable bool m_has_result;

public:
    kwxRichTextFieldTypeStandard(void* pObject, const wxString& name, const wxString& label,
                                 int displayStyle);

    void SetOnCanEditProperties(void* pFunction)
    {
        m_can_edit_properties_func = (kwxRtfCanEditPropertiesFunc) pFunction;
    }
    void SetOnEditProperties(void* pFunction)
    {
        m_edit_properties_func = (kwxRtfEditPropertiesFunc) pFunction;
    }
    void SetOnGetPropertiesMenuLabel(void* pFunction)
    {
        m_get_properties_menu_label_func = (kwxRtfGetPropertiesMenuLabelFunc) pFunction;
    }
    void SetOnUpdateField(void* pFunction)
    {
        m_update_field_func = (kwxRtfUpdateFieldFunc) pFunction;
    }
    void SetOnIsTopLevel(void* pFunction)
    {
        m_is_top_level_func = (kwxRtfIsTopLevelFunc) pFunction;
    }

    void SetPropertiesMenuLabelResult(wxString* label)
    {
        m_result_string = label ? *label : wxString();
        m_has_result = true;
    }
    void SetCanEditPropertiesResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }
    void SetEditPropertiesResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }
    void SetUpdateFieldResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }
    void SetIsTopLevelResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }

    bool CanEditProperties(wxRichTextField* obj) const override;
    bool EditProperties(wxRichTextField* obj, wxWindow* parent, wxRichTextBuffer* buffer) override;
    wxString GetPropertiesMenuLabel(wxRichTextField* obj) const override;
    bool UpdateField(wxRichTextBuffer* buffer, wxRichTextField* obj) override;
    bool IsTopLevel(wxRichTextField* obj) const override;
};

kwxRichTextFieldTypeStandard::kwxRichTextFieldTypeStandard(void* pObject, const wxString& name,
                                                           const wxString& label,
                                                           int displayStyle) :
    wxRichTextFieldTypeStandard(name, label, displayStyle)
{
    m_object = pObject;
    m_can_edit_properties_func = nullptr;
    m_edit_properties_func = nullptr;
    m_get_properties_menu_label_func = nullptr;
    m_update_field_func = nullptr;
    m_is_top_level_func = nullptr;
    m_result_bool = false;
    m_has_result = false;
}

bool kwxRichTextFieldTypeStandard::CanEditProperties(wxRichTextField* obj) const
{
    if (!m_can_edit_properties_func)
    {
        return wxRichTextFieldTypeStandard::CanEditProperties(obj);
    }

    m_result_bool = false;
    m_has_result = false;
    m_can_edit_properties_func(m_object, obj);
    if (!m_has_result)
    {
        return wxRichTextFieldTypeStandard::CanEditProperties(obj);
    }
    return m_result_bool;
}

bool kwxRichTextFieldTypeStandard::EditProperties(wxRichTextField* obj, wxWindow* parent,
                                                  wxRichTextBuffer* buffer)
{
    if (!m_edit_properties_func)
    {
        return wxRichTextFieldTypeStandard::EditProperties(obj, parent, buffer);
    }

    m_result_bool = false;
    m_has_result = false;
    m_edit_properties_func(m_object, obj, parent);
    if (!m_has_result)
    {
        return wxRichTextFieldTypeStandard::EditProperties(obj, parent, buffer);
    }
    return m_result_bool;
}

wxString kwxRichTextFieldTypeStandard::GetPropertiesMenuLabel(wxRichTextField* obj) const
{
    if (!m_get_properties_menu_label_func)
    {
        return wxRichTextFieldTypeStandard::GetPropertiesMenuLabel(obj);
    }

    m_result_string.clear();
    m_has_result = false;
    m_get_properties_menu_label_func(m_object, obj);
    if (!m_has_result)
    {
        return wxRichTextFieldTypeStandard::GetPropertiesMenuLabel(obj);
    }
    return m_result_string;
}

bool kwxRichTextFieldTypeStandard::UpdateField(wxRichTextBuffer* buffer, wxRichTextField* obj)
{
    if (!m_update_field_func)
    {
        return wxRichTextFieldTypeStandard::UpdateField(buffer, obj);
    }

    m_result_bool = false;
    m_has_result = false;
    m_update_field_func(m_object, buffer, obj);
    if (!m_has_result)
    {
        return wxRichTextFieldTypeStandard::UpdateField(buffer, obj);
    }
    return m_result_bool;
}

bool kwxRichTextFieldTypeStandard::IsTopLevel(wxRichTextField* obj) const
{
    if (!m_is_top_level_func)
    {
        return wxRichTextFieldTypeStandard::IsTopLevel(obj);
    }

    m_result_bool = false;
    m_has_result = false;
    m_is_top_level_func(m_object, obj);
    if (!m_has_result)
    {
        return wxRichTextFieldTypeStandard::IsTopLevel(obj);
    }
    return m_result_bool;
}

// ---------------------------------------------------------------------------
// kwxRichTextDrawingHandler
//
// GetVirtualSubobjectAttributes() hands the caller two wxArray containers that a
// foreign runtime cannot build, so it always reports zero mixed attributes.  The
// reference sample returns zero as well; GetVirtualAttributes() covers per-object
// virtual styling.
// ---------------------------------------------------------------------------

class kwxRichTextDrawingHandler : public wxRichTextDrawingHandler
{
private:
    void* m_object;
    kwxRdhHasVirtualAttributesFunc m_has_virtual_attributes_func;
    kwxRdhGetVirtualAttributesFunc m_get_virtual_attributes_func;
    kwxRdhVirtualSubobjectCountFunc m_subobject_count_func;
    kwxRdhHasVirtualTextFunc m_has_virtual_text_func;
    kwxRdhGetVirtualTextFunc m_get_virtual_text_func;

    mutable wxString m_result_string;
    mutable bool m_result_bool;
    mutable int m_result_int;
    mutable bool m_has_result;

public:
    kwxRichTextDrawingHandler(void* pObject, const wxString& name);

    void SetOnHasVirtualAttributes(void* pFunction)
    {
        m_has_virtual_attributes_func = (kwxRdhHasVirtualAttributesFunc) pFunction;
    }
    void SetOnGetVirtualAttributes(void* pFunction)
    {
        m_get_virtual_attributes_func = (kwxRdhGetVirtualAttributesFunc) pFunction;
    }
    void SetOnGetVirtualSubobjectAttributesCount(void* pFunction)
    {
        m_subobject_count_func = (kwxRdhVirtualSubobjectCountFunc) pFunction;
    }
    void SetOnHasVirtualText(void* pFunction)
    {
        m_has_virtual_text_func = (kwxRdhHasVirtualTextFunc) pFunction;
    }
    void SetOnGetVirtualText(void* pFunction)
    {
        m_get_virtual_text_func = (kwxRdhGetVirtualTextFunc) pFunction;
    }

    void SetVirtualTextResult(wxString* text)
    {
        m_result_string = text ? *text : wxString();
        m_has_result = true;
    }
    void SetHasVirtualAttributesResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }
    void SetGetVirtualAttributesResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }
    void SetGetVirtualSubobjectAttributesCountResult(int result)
    {
        m_result_int = result;
        m_has_result = true;
    }
    void SetHasVirtualTextResult(bool result)
    {
        m_result_bool = result;
        m_has_result = true;
    }

    bool HasVirtualAttributes(wxRichTextObject* obj) const override;
    bool GetVirtualAttributes(wxRichTextAttr& attr, wxRichTextObject* obj) const override;
    int GetVirtualSubobjectAttributesCount(wxRichTextObject* obj) const override;
    int GetVirtualSubobjectAttributes(wxRichTextObject* obj, wxArrayInt& positions,
                                      wxRichTextAttrArray& attributes) const override;
    bool HasVirtualText(const wxRichTextPlainText* obj) const override;
    bool GetVirtualText(const wxRichTextPlainText* obj, wxString& text) const override;
};

kwxRichTextDrawingHandler::kwxRichTextDrawingHandler(void* pObject, const wxString& name) :
    wxRichTextDrawingHandler(name)
{
    m_object = pObject;
    m_has_virtual_attributes_func = nullptr;
    m_get_virtual_attributes_func = nullptr;
    m_subobject_count_func = nullptr;
    m_has_virtual_text_func = nullptr;
    m_get_virtual_text_func = nullptr;
    m_result_bool = false;
    m_result_int = 0;
    m_has_result = false;
}

bool kwxRichTextDrawingHandler::HasVirtualAttributes(wxRichTextObject* obj) const
{
    if (!m_has_virtual_attributes_func)
    {
        return false;
    }

    m_result_bool = false;
    m_has_result = false;
    m_has_virtual_attributes_func(m_object, obj);
    if (!m_has_result)
    {
        return false;
    }
    return m_result_bool;
}

bool kwxRichTextDrawingHandler::GetVirtualAttributes(wxRichTextAttr& attr,
                                                     wxRichTextObject* obj) const
{
    if (!m_get_virtual_attributes_func)
    {
        return false;
    }

    m_result_bool = false;
    m_has_result = false;
    m_get_virtual_attributes_func(m_object, &attr, obj);
    if (!m_has_result)
    {
        return false;
    }
    return m_result_bool;
}

int kwxRichTextDrawingHandler::GetVirtualSubobjectAttributesCount(wxRichTextObject* obj) const
{
    if (!m_subobject_count_func)
    {
        return 0;
    }

    m_result_int = 0;
    m_has_result = false;
    m_subobject_count_func(m_object, obj);
    if (!m_has_result)
    {
        return 0;
    }
    return m_result_int;
}

int kwxRichTextDrawingHandler::GetVirtualSubobjectAttributes(
    [[maybe_unused]] wxRichTextObject* obj, [[maybe_unused]] wxArrayInt& positions,
    [[maybe_unused]] wxRichTextAttrArray& attributes) const
{
    return 0;
}

bool kwxRichTextDrawingHandler::HasVirtualText(const wxRichTextPlainText* obj) const
{
    if (!m_has_virtual_text_func)
    {
        return false;
    }

    m_result_bool = false;
    m_has_result = false;
    m_has_virtual_text_func(m_object, const_cast<wxRichTextPlainText*>(obj));
    if (!m_has_result)
    {
        return false;
    }
    return m_result_bool;
}

bool kwxRichTextDrawingHandler::GetVirtualText(const wxRichTextPlainText* obj, wxString& text) const
{
    if (!m_get_virtual_text_func)
    {
        return false;
    }

    m_result_string.clear();
    m_has_result = false;
    m_get_virtual_text_func(m_object, const_cast<wxRichTextPlainText*>(obj));
    if (!m_has_result)
    {
        return false;
    }
    text = m_result_string;
    return true;
}

// ---------------------------------------------------------------------------
// Exported wrappers
// ---------------------------------------------------------------------------

extern "C"
{
    // kwxRichTextCtrl ---------------------------------------------------------

    EXPORT void* kwxRichTextCtrl_Create(wxWindow* parent, int id, int x, int y, int width,
                                        int height, int style)
    {
        return new kwxRichTextCtrl(nullptr, parent, id, wxEmptyString, wxPoint(x, y),
                                   wxSize(width, height), style);
    }

    EXPORT void kwxRichTextCtrl_Delete(kwxRichTextCtrl* self)
    {
        delete self;
    }

    EXPORT void kwxRichTextCtrl_SetOnPrepareContent(kwxRichTextCtrl* self, void* pFunction)
    {
        if (self)
        {
            self->SetOnPrepareContent(pFunction);
        }
    }

    EXPORT void kwxRichTextCtrl_SetOnCanDeleteRange(kwxRichTextCtrl* self, void* pFunction)
    {
        if (self)
        {
            self->SetOnCanDeleteRange(pFunction);
        }
    }

    EXPORT void kwxRichTextCtrl_SetOnCanInsertContent(kwxRichTextCtrl* self, void* pFunction)
    {
        if (self)
        {
            self->SetOnCanInsertContent(pFunction);
        }
    }

    EXPORT void kwxRichTextCtrl_SetCanDeleteRangeResult(kwxRichTextCtrl* self, int result)
    {
        if (self)
        {
            self->SetCanDeleteRangeResult(result != 0);
        }
    }

    EXPORT void kwxRichTextCtrl_SetCanInsertContentResult(kwxRichTextCtrl* self, int result)
    {
        if (self)
        {
            self->SetCanInsertContentResult(result != 0);
        }
    }

    // kwxRichTextFieldTypeStandard --------------------------------------------

    EXPORT void* kwxRichTextFieldTypeStandard_Create(void* pObject, wxString* name, wxString* label,
                                                     int displayStyle)
    {
        return new kwxRichTextFieldTypeStandard(pObject, name ? *name : wxString(),
                                                label ? *label : wxString(), displayStyle);
    }

    EXPORT void kwxRichTextFieldTypeStandard_Delete(kwxRichTextFieldTypeStandard* self)
    {
        delete self;
    }

    EXPORT void
        kwxRichTextFieldTypeStandard_SetOnCanEditProperties(kwxRichTextFieldTypeStandard* self,
                                                            void* pFunction)
    {
        if (self)
        {
            self->SetOnCanEditProperties(pFunction);
        }
    }

    EXPORT void kwxRichTextFieldTypeStandard_SetOnEditProperties(kwxRichTextFieldTypeStandard* self,
                                                                 void* pFunction)
    {
        if (self)
        {
            self->SetOnEditProperties(pFunction);
        }
    }

    EXPORT void
        kwxRichTextFieldTypeStandard_SetOnGetPropertiesMenuLabel(kwxRichTextFieldTypeStandard* self,
                                                                 void* pFunction)
    {
        if (self)
        {
            self->SetOnGetPropertiesMenuLabel(pFunction);
        }
    }

    EXPORT void kwxRichTextFieldTypeStandard_SetPropertiesMenuLabelResult(
        kwxRichTextFieldTypeStandard* self, wxString* label)
    {
        if (self)
        {
            self->SetPropertiesMenuLabelResult(label);
        }
    }

    EXPORT void
        kwxRichTextFieldTypeStandard_SetCanEditPropertiesResult(kwxRichTextFieldTypeStandard* self,
                                                                int result)
    {
        if (self)
        {
            self->SetCanEditPropertiesResult(result != 0);
        }
    }

    EXPORT void
        kwxRichTextFieldTypeStandard_SetEditPropertiesResult(kwxRichTextFieldTypeStandard* self,
                                                             int result)
    {
        if (self)
        {
            self->SetEditPropertiesResult(result != 0);
        }
    }

    EXPORT void
        kwxRichTextFieldTypeStandard_SetUpdateFieldResult(kwxRichTextFieldTypeStandard* self,
                                                          int result)
    {
        if (self)
        {
            self->SetUpdateFieldResult(result != 0);
        }
    }

    EXPORT void kwxRichTextFieldTypeStandard_SetIsTopLevelResult(kwxRichTextFieldTypeStandard* self,
                                                                 int result)
    {
        if (self)
        {
            self->SetIsTopLevelResult(result != 0);
        }
    }

    EXPORT void kwxRichTextFieldTypeStandard_SetOnUpdateField(kwxRichTextFieldTypeStandard* self,
                                                              void* pFunction)
    {
        if (self)
        {
            self->SetOnUpdateField(pFunction);
        }
    }

    EXPORT void kwxRichTextFieldTypeStandard_SetOnIsTopLevel(kwxRichTextFieldTypeStandard* self,
                                                             void* pFunction)
    {
        if (self)
        {
            self->SetOnIsTopLevel(pFunction);
        }
    }

    // kwxRichTextDrawingHandler -----------------------------------------------

    EXPORT void* kwxRichTextDrawingHandler_Create(void* pObject, wxString* name)
    {
        return new kwxRichTextDrawingHandler(pObject, name ? *name : wxString());
    }

    EXPORT void kwxRichTextDrawingHandler_Delete(kwxRichTextDrawingHandler* self)
    {
        delete self;
    }

    EXPORT void kwxRichTextDrawingHandler_SetOnHasVirtualAttributes(kwxRichTextDrawingHandler* self,
                                                                    void* pFunction)
    {
        if (self)
        {
            self->SetOnHasVirtualAttributes(pFunction);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetOnGetVirtualAttributes(kwxRichTextDrawingHandler* self,
                                                                    void* pFunction)
    {
        if (self)
        {
            self->SetOnGetVirtualAttributes(pFunction);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetOnGetVirtualSubobjectAttributesCount(
        kwxRichTextDrawingHandler* self, void* pFunction)
    {
        if (self)
        {
            self->SetOnGetVirtualSubobjectAttributesCount(pFunction);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetOnHasVirtualText(kwxRichTextDrawingHandler* self,
                                                              void* pFunction)
    {
        if (self)
        {
            self->SetOnHasVirtualText(pFunction);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetOnGetVirtualText(kwxRichTextDrawingHandler* self,
                                                              void* pFunction)
    {
        if (self)
        {
            self->SetOnGetVirtualText(pFunction);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetVirtualTextResult(kwxRichTextDrawingHandler* self,
                                                               wxString* text)
    {
        if (self)
        {
            self->SetVirtualTextResult(text);
        }
    }

    EXPORT void
        kwxRichTextDrawingHandler_SetHasVirtualAttributesResult(kwxRichTextDrawingHandler* self,
                                                                int result)
    {
        if (self)
        {
            self->SetHasVirtualAttributesResult(result != 0);
        }
    }

    EXPORT void
        kwxRichTextDrawingHandler_SetGetVirtualAttributesResult(kwxRichTextDrawingHandler* self,
                                                                int result)
    {
        if (self)
        {
            self->SetGetVirtualAttributesResult(result != 0);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetGetVirtualSubobjectAttributesCountResult(
        kwxRichTextDrawingHandler* self, int result)
    {
        if (self)
        {
            self->SetGetVirtualSubobjectAttributesCountResult(result);
        }
    }

    EXPORT void kwxRichTextDrawingHandler_SetHasVirtualTextResult(kwxRichTextDrawingHandler* self,
                                                                  int result)
    {
        if (self)
        {
            self->SetHasVirtualTextResult(result != 0);
        }
    }

    // wxRichTextRange accessors for the range a CanDeleteRange callback receives.
    // The pointer is borrowed for the duration of the call.

    EXPORT long wxRichTextRange_GetStart(wxRichTextRange* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetStart();
    }

    EXPORT long wxRichTextRange_GetEnd(wxRichTextRange* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetEnd();
    }

    EXPORT long wxRichTextRange_GetLength(wxRichTextRange* self)
    {
        if (!self)
        {
            return 0;
        }
        return self->GetLength();
    }
}
