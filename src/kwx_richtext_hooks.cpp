// Callback overrides for the three rich-text extension points a foreign language
// cannot derive from itself: wxRichTextCtrl, wxRichTextFieldTypeStandard and
// wxRichTextDrawingHandler.  The declarations live in
// include/kwx_richtext_hooks.h; this file holds the class definitions, the virtual
// overrides and the exported kwx* wrappers.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <cstdint>

// ---------------------------------------------------------------------------
// Callback shapes.  The plain per-hook typedefs below return void, receive the
// object-level callback token first and take at most two further arguments.  A
// callback that must produce a value publishes it with the matching Set*Result
// function on the same object before it returns; a callback that returns
// without publishing keeps the base-class behaviour.
//
// Because that first argument identifies the object rather than the hook, a
// runtime that can form only one C function pointer cannot install these
// directly; kwxHookFunc below is the uniform single-thunk form that can.
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

// Uniform single-thunk hook ABI — see include/kwx_richtext_hooks.h.  The
// first argument is the per-hook token, the next two are the hook
// arguments; unused positions are null.
typedef void (*kwxHookFunc)(void* data, void* arg1, void* arg2);

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

    kwxHookFunc m_prepare_content_hook;
    void* m_prepare_content_hook_data;
    kwxHookFunc m_can_delete_range_hook;
    void* m_can_delete_range_hook_data;
    kwxHookFunc m_can_insert_content_hook;
    void* m_can_insert_content_hook_data;

    long m_lock_id;
    bool m_locked;

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

    void SetOnPrepareContentWithData(void* pFunction, void* data)
    {
        m_prepare_content_hook = (kwxHookFunc) pFunction;
        m_prepare_content_hook_data = data;
    }
    void SetOnCanDeleteRangeWithData(void* pFunction, void* data)
    {
        m_can_delete_range_hook = (kwxHookFunc) pFunction;
        m_can_delete_range_hook_data = data;
    }
    void SetOnCanInsertContentWithData(void* pFunction, void* data)
    {
        m_can_insert_content_hook = (kwxHookFunc) pFunction;
        m_can_insert_content_hook_data = data;
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

    void SetCallbackObject(void* object) { m_object = object; }
    void* GetCallbackObject() const { return m_object; }
    void SetLockId(long id) { m_lock_id = id; }
    long GetLockId() const { return m_lock_id; }
    void BeginLock()
    {
        ++m_lock_id;
        m_locked = true;
    }
    void EndLock() { m_locked = false; }
    bool IsLocked() const { return m_locked; }

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
    m_prepare_content_hook = nullptr;
    m_prepare_content_hook_data = nullptr;
    m_can_delete_range_hook = nullptr;
    m_can_delete_range_hook_data = nullptr;
    m_can_insert_content_hook = nullptr;
    m_can_insert_content_hook_data = nullptr;
    m_result_bool = false;
    m_has_result = false;
    m_lock_id = 0;
    m_locked = false;
}

void kwxRichTextCtrl::PrepareContent(wxRichTextParagraphLayoutBox& container)
{
    // Tag every leaf object of every paragraph with the current lock id, mirroring
    // MyRichTextCtrl::PrepareContent in wxSamples/src/richtext/richtext.cpp:2152-2175.
    if (m_locked)
    {
        wxRichTextObjectList::compatibility_iterator node = container.GetChildren().GetFirst();
        while (node)
        {
            wxRichTextParagraph* para = wxDynamicCast(node->GetData(), wxRichTextParagraph);
            if (para)
            {
                wxRichTextObjectList::compatibility_iterator childNode =
                    para->GetChildren().GetFirst();
                while (childNode)
                {
                    wxRichTextObject* obj = childNode->GetData();
                    obj->GetProperties().SetProperty("Lock", m_lock_id);
                    childNode = childNode->GetNext();
                }
            }
            node = node->GetNext();
        }
    }

    if (m_prepare_content_hook)
    {
        m_prepare_content_hook(m_prepare_content_hook_data, &container, nullptr);
        return;
    }

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
    if (m_can_delete_range_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_can_delete_range_hook(m_can_delete_range_hook_data, &container,
                                const_cast<wxRichTextRange*>(&range));
        if (!m_has_result)
        {
            return wxRichTextCtrl::CanDeleteRange(container, range);
        }
        return m_result_bool;
    }

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
    if (m_can_insert_content_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_can_insert_content_hook(m_can_insert_content_hook_data, &container,
                                  (void*) (intptr_t) pos);
        if (!m_has_result)
        {
            return wxRichTextCtrl::CanInsertContent(container, pos);
        }
        return m_result_bool;
    }

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

    kwxHookFunc m_can_edit_properties_hook;
    void* m_can_edit_properties_hook_data;
    kwxHookFunc m_edit_properties_hook;
    void* m_edit_properties_hook_data;
    kwxHookFunc m_get_properties_menu_label_hook;
    void* m_get_properties_menu_label_hook_data;
    kwxHookFunc m_update_field_hook;
    void* m_update_field_hook_data;
    kwxHookFunc m_is_top_level_hook;
    void* m_is_top_level_hook_data;

    mutable wxString m_result_string;
    mutable bool m_result_bool;
    mutable bool m_has_result;

    void Init(void* pObject);

public:
    kwxRichTextFieldTypeStandard(void* pObject, const wxString& name, const wxString& label,
                                 int displayStyle);
    kwxRichTextFieldTypeStandard(void* pObject, const wxString& name, const wxBitmap& bitmap,
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

    void SetOnCanEditPropertiesWithData(void* pFunction, void* data)
    {
        m_can_edit_properties_hook = (kwxHookFunc) pFunction;
        m_can_edit_properties_hook_data = data;
    }
    void SetOnEditPropertiesWithData(void* pFunction, void* data)
    {
        m_edit_properties_hook = (kwxHookFunc) pFunction;
        m_edit_properties_hook_data = data;
    }
    void SetOnGetPropertiesMenuLabelWithData(void* pFunction, void* data)
    {
        m_get_properties_menu_label_hook = (kwxHookFunc) pFunction;
        m_get_properties_menu_label_hook_data = data;
    }
    void SetOnUpdateFieldWithData(void* pFunction, void* data)
    {
        m_update_field_hook = (kwxHookFunc) pFunction;
        m_update_field_hook_data = data;
    }
    void SetOnIsTopLevelWithData(void* pFunction, void* data)
    {
        m_is_top_level_hook = (kwxHookFunc) pFunction;
        m_is_top_level_hook_data = data;
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
    Init(pObject);
}

kwxRichTextFieldTypeStandard::kwxRichTextFieldTypeStandard(void* pObject, const wxString& name,
                                                           const wxBitmap& bitmap,
                                                           int displayStyle) :
    wxRichTextFieldTypeStandard(name, bitmap, displayStyle)
{
    Init(pObject);
}

void kwxRichTextFieldTypeStandard::Init(void* pObject)
{
    m_object = pObject;
    m_can_edit_properties_func = nullptr;
    m_edit_properties_func = nullptr;
    m_get_properties_menu_label_func = nullptr;
    m_update_field_func = nullptr;
    m_is_top_level_func = nullptr;
    m_can_edit_properties_hook = nullptr;
    m_can_edit_properties_hook_data = nullptr;
    m_edit_properties_hook = nullptr;
    m_edit_properties_hook_data = nullptr;
    m_get_properties_menu_label_hook = nullptr;
    m_get_properties_menu_label_hook_data = nullptr;
    m_update_field_hook = nullptr;
    m_update_field_hook_data = nullptr;
    m_is_top_level_hook = nullptr;
    m_is_top_level_hook_data = nullptr;
    m_result_bool = false;
    m_has_result = false;
}

bool kwxRichTextFieldTypeStandard::CanEditProperties(wxRichTextField* obj) const
{
    if (m_can_edit_properties_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_can_edit_properties_hook(m_can_edit_properties_hook_data, obj, nullptr);
        if (!m_has_result)
        {
            return wxRichTextFieldTypeStandard::CanEditProperties(obj);
        }
        return m_result_bool;
    }

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
    if (m_edit_properties_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_edit_properties_hook(m_edit_properties_hook_data, obj, parent);
        if (!m_has_result)
        {
            return wxRichTextFieldTypeStandard::EditProperties(obj, parent, buffer);
        }
        return m_result_bool;
    }

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
    if (m_get_properties_menu_label_hook)
    {
        m_result_string.clear();
        m_has_result = false;
        m_get_properties_menu_label_hook(m_get_properties_menu_label_hook_data, obj, nullptr);
        if (!m_has_result)
        {
            return wxRichTextFieldTypeStandard::GetPropertiesMenuLabel(obj);
        }
        return m_result_string;
    }

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
    if (m_update_field_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_update_field_hook(m_update_field_hook_data, buffer, obj);
        if (!m_has_result)
        {
            return wxRichTextFieldTypeStandard::UpdateField(buffer, obj);
        }
        return m_result_bool;
    }

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
    if (m_is_top_level_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_is_top_level_hook(m_is_top_level_hook_data, obj, nullptr);
        if (!m_has_result)
        {
            return wxRichTextFieldTypeStandard::IsTopLevel(obj);
        }
        return m_result_bool;
    }

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

    kwxHookFunc m_has_virtual_attributes_hook;
    void* m_has_virtual_attributes_hook_data;
    kwxHookFunc m_get_virtual_attributes_hook;
    void* m_get_virtual_attributes_hook_data;
    kwxHookFunc m_subobject_count_hook;
    void* m_subobject_count_hook_data;
    kwxHookFunc m_has_virtual_text_hook;
    void* m_has_virtual_text_hook_data;
    kwxHookFunc m_get_virtual_text_hook;
    void* m_get_virtual_text_hook_data;

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

    void SetOnHasVirtualAttributesWithData(void* pFunction, void* data)
    {
        m_has_virtual_attributes_hook = (kwxHookFunc) pFunction;
        m_has_virtual_attributes_hook_data = data;
    }
    void SetOnGetVirtualAttributesWithData(void* pFunction, void* data)
    {
        m_get_virtual_attributes_hook = (kwxHookFunc) pFunction;
        m_get_virtual_attributes_hook_data = data;
    }
    void SetOnGetVirtualSubobjectAttributesCountWithData(void* pFunction, void* data)
    {
        m_subobject_count_hook = (kwxHookFunc) pFunction;
        m_subobject_count_hook_data = data;
    }
    void SetOnHasVirtualTextWithData(void* pFunction, void* data)
    {
        m_has_virtual_text_hook = (kwxHookFunc) pFunction;
        m_has_virtual_text_hook_data = data;
    }
    void SetOnGetVirtualTextWithData(void* pFunction, void* data)
    {
        m_get_virtual_text_hook = (kwxHookFunc) pFunction;
        m_get_virtual_text_hook_data = data;
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
    m_has_virtual_attributes_hook = nullptr;
    m_has_virtual_attributes_hook_data = nullptr;
    m_get_virtual_attributes_hook = nullptr;
    m_get_virtual_attributes_hook_data = nullptr;
    m_subobject_count_hook = nullptr;
    m_subobject_count_hook_data = nullptr;
    m_has_virtual_text_hook = nullptr;
    m_has_virtual_text_hook_data = nullptr;
    m_get_virtual_text_hook = nullptr;
    m_get_virtual_text_hook_data = nullptr;
    m_result_bool = false;
    m_result_int = 0;
    m_has_result = false;
}

bool kwxRichTextDrawingHandler::HasVirtualAttributes(wxRichTextObject* obj) const
{
    if (m_has_virtual_attributes_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_has_virtual_attributes_hook(m_has_virtual_attributes_hook_data, obj, nullptr);
        if (!m_has_result)
        {
            return false;
        }
        return m_result_bool;
    }

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
    if (m_get_virtual_attributes_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_get_virtual_attributes_hook(m_get_virtual_attributes_hook_data, &attr, obj);
        if (!m_has_result)
        {
            return false;
        }
        return m_result_bool;
    }

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
    if (m_subobject_count_hook)
    {
        m_result_int = 0;
        m_has_result = false;
        m_subobject_count_hook(m_subobject_count_hook_data, obj, nullptr);
        if (!m_has_result)
        {
            return 0;
        }
        return m_result_int;
    }

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
    if (m_has_virtual_text_hook)
    {
        m_result_bool = false;
        m_has_result = false;
        m_has_virtual_text_hook(m_has_virtual_text_hook_data, const_cast<wxRichTextPlainText*>(obj),
                                nullptr);
        if (!m_has_result)
        {
            return false;
        }
        return m_result_bool;
    }

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
    if (m_get_virtual_text_hook)
    {
        m_result_string.clear();
        m_has_result = false;
        m_get_virtual_text_hook(m_get_virtual_text_hook_data, const_cast<wxRichTextPlainText*>(obj),
                                nullptr);
        if (!m_has_result)
        {
            return false;
        }
        text = m_result_string;
        return true;
    }

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

    EXPORT void kwxRichTextCtrl_SetOnPrepareContentWithData(kwxRichTextCtrl* self, void* pFunction,
                                                            void* data)
    {
        if (self)
        {
            self->SetOnPrepareContentWithData(pFunction, data);
        }
    }

    EXPORT void kwxRichTextCtrl_SetOnCanDeleteRange(kwxRichTextCtrl* self, void* pFunction)
    {
        if (self)
        {
            self->SetOnCanDeleteRange(pFunction);
        }
    }

    EXPORT void kwxRichTextCtrl_SetOnCanDeleteRangeWithData(kwxRichTextCtrl* self, void* pFunction,
                                                            void* data)
    {
        if (self)
        {
            self->SetOnCanDeleteRangeWithData(pFunction, data);
        }
    }

    EXPORT void kwxRichTextCtrl_SetOnCanInsertContent(kwxRichTextCtrl* self, void* pFunction)
    {
        if (self)
        {
            self->SetOnCanInsertContent(pFunction);
        }
    }

    EXPORT void kwxRichTextCtrl_SetOnCanInsertContentWithData(kwxRichTextCtrl* self,
                                                              void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnCanInsertContentWithData(pFunction, data);
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

    EXPORT void kwxRichTextCtrl_SetCallbackObject(kwxRichTextCtrl* self, void* object)
    {
        if (self)
        {
            self->SetCallbackObject(object);
        }
    }

    EXPORT void* kwxRichTextCtrl_GetCallbackObject(kwxRichTextCtrl* self)
    {
        return self ? self->GetCallbackObject() : nullptr;
    }

    EXPORT void kwxRichTextCtrl_SetLockId(kwxRichTextCtrl* self, long id)
    {
        if (self)
        {
            self->SetLockId(id);
        }
    }

    EXPORT long kwxRichTextCtrl_GetLockId(kwxRichTextCtrl* self)
    {
        return self ? self->GetLockId() : 0;
    }

    EXPORT void kwxRichTextCtrl_BeginLock(kwxRichTextCtrl* self)
    {
        if (self)
        {
            self->BeginLock();
        }
    }

    EXPORT void kwxRichTextCtrl_EndLock(kwxRichTextCtrl* self)
    {
        if (self)
        {
            self->EndLock();
        }
    }

    EXPORT int kwxRichTextCtrl_IsLocked(kwxRichTextCtrl* self)
    {
        return self && self->IsLocked();
    }

    // kwxRichTextFieldTypeStandard --------------------------------------------

    EXPORT void* kwxRichTextFieldTypeStandard_Create(void* pObject, wxString* name, wxString* label,
                                                     int displayStyle)
    {
        return new kwxRichTextFieldTypeStandard(pObject, name ? *name : wxString(),
                                                label ? *label : wxString(), displayStyle);
    }

    EXPORT void* kwxRichTextFieldTypeStandard_CreateWithBitmap(void* pObject, wxString* name,
                                                               wxBitmap* bitmap, int displayStyle)
    {
        return new kwxRichTextFieldTypeStandard(pObject, name ? *name : wxString(),
                                                bitmap ? *bitmap : wxNullBitmap, displayStyle);
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

    EXPORT void kwxRichTextFieldTypeStandard_SetOnCanEditPropertiesWithData(
        kwxRichTextFieldTypeStandard* self, void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnCanEditPropertiesWithData(pFunction, data);
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
        kwxRichTextFieldTypeStandard_SetOnEditPropertiesWithData(kwxRichTextFieldTypeStandard* self,
                                                                 void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnEditPropertiesWithData(pFunction, data);
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

    EXPORT void kwxRichTextFieldTypeStandard_SetOnGetPropertiesMenuLabelWithData(
        kwxRichTextFieldTypeStandard* self, void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnGetPropertiesMenuLabelWithData(pFunction, data);
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

    EXPORT void
        kwxRichTextFieldTypeStandard_SetOnUpdateFieldWithData(kwxRichTextFieldTypeStandard* self,
                                                              void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnUpdateFieldWithData(pFunction, data);
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

    EXPORT void
        kwxRichTextFieldTypeStandard_SetOnIsTopLevelWithData(kwxRichTextFieldTypeStandard* self,
                                                             void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnIsTopLevelWithData(pFunction, data);
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

    EXPORT void
        kwxRichTextDrawingHandler_SetOnHasVirtualAttributesWithData(kwxRichTextDrawingHandler* self,
                                                                    void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnHasVirtualAttributesWithData(pFunction, data);
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

    EXPORT void
        kwxRichTextDrawingHandler_SetOnGetVirtualAttributesWithData(kwxRichTextDrawingHandler* self,
                                                                    void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnGetVirtualAttributesWithData(pFunction, data);
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

    EXPORT void kwxRichTextDrawingHandler_SetOnGetVirtualSubobjectAttributesCountWithData(
        kwxRichTextDrawingHandler* self, void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnGetVirtualSubobjectAttributesCountWithData(pFunction, data);
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

    EXPORT void
        kwxRichTextDrawingHandler_SetOnHasVirtualTextWithData(kwxRichTextDrawingHandler* self,
                                                              void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnHasVirtualTextWithData(pFunction, data);
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

    EXPORT void
        kwxRichTextDrawingHandler_SetOnGetVirtualTextWithData(kwxRichTextDrawingHandler* self,
                                                              void* pFunction, void* data)
    {
        if (self)
        {
            self->SetOnGetVirtualTextWithData(pFunction, data);
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
