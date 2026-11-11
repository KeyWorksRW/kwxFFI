// Callback overrides for the three PropertyGrid extension points a foreign
// language cannot derive from itself: wxPGProperty, wxPGTextCtrlEditor and
// wxPropertyGridPage.  The declarations live in include/kwx_propgrid_hooks.h;
// this file holds the class definitions, the virtual overrides and the exported
// kwx* wrappers.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <utility>

// ---------------------------------------------------------------------------
// Callback shapes.  Every one receives the foreign object first; a callback
// that must produce a value publishes it with the matching Set*Result function
// on the same object before it returns.
// ---------------------------------------------------------------------------

typedef void (*kwxPropHookVoidFunc)(void* pObject);
typedef void (*kwxPropHookCreateControlsFunc)(void* pObject, void* propGrid, void* property, int x,
                                              int y, int width, int height, void* primary);
typedef void (*kwxPropHookEventFunc)(void* pObject, void* propGrid, void* property, void* ctrl,
                                     void* event);
typedef void (*kwxPropHookValueToStringFunc)(void* pObject, void* value, int flags);
typedef void (*kwxPropHookStringToValueFunc)(void* pObject, void* variant, void* text, int flags);
typedef void (*kwxPropHookChildChangedFunc)(void* pObject, void* thisValue, int childIndex,
                                            void* childValue);
typedef void (*kwxPropHookValidateValueFunc)(void* pObject, void* value, void* validationInfo);

// ---------------------------------------------------------------------------
// kwxPGProperty
//
// wxPGProperty's constructors are protected, so the derived class owns the only
// public constructor and assigns m_value (protected in the base) itself.
// ---------------------------------------------------------------------------

class kwxPGProperty : public wxPGProperty
{
private:
    void* m_object;
    kwxPropHookChildChangedFunc m_child_changed_func;
    kwxPropHookVoidFunc m_refresh_children_func;
    kwxPropHookVoidFunc m_set_value_func;
    kwxPropHookVoidFunc m_do_get_value_func;
    kwxPropHookValueToStringFunc m_value_to_string_func;
    kwxPropHookStringToValueFunc m_string_to_value_func;
    kwxPropHookValidateValueFunc m_validate_value_func;

    // Scratch results the callbacks fill in; cleared before each callback runs.
    mutable wxVariant m_result_variant;
    mutable wxString m_result_string;
    mutable bool m_result_bool;
    mutable bool m_has_result;

public:
    kwxPGProperty(void* pObject, const wxString& label, const wxString& name,
                  const wxVariant& value);

    void SetOnChildChanged(void* pFunction)
    {
        m_child_changed_func = (kwxPropHookChildChangedFunc) pFunction;
    }
    void SetOnRefreshChildren(void* pFunction)
    {
        m_refresh_children_func = (kwxPropHookVoidFunc) pFunction;
    }
    void SetOnOnSetValue(void* pFunction) { m_set_value_func = (kwxPropHookVoidFunc) pFunction; }
    void SetOnDoGetValue(void* pFunction) { m_do_get_value_func = (kwxPropHookVoidFunc) pFunction; }
    void SetOnValueToString(void* pFunction)
    {
        m_value_to_string_func = (kwxPropHookValueToStringFunc) pFunction;
    }
    void SetOnStringToValue(void* pFunction)
    {
        m_string_to_value_func = (kwxPropHookStringToValueFunc) pFunction;
    }
    void SetOnValidateValue(void* pFunction)
    {
        m_validate_value_func = (kwxPropHookValidateValueFunc) pFunction;
    }

    // Store the value a callback wants the running override to return.  Only the
    // callback whose override is executing should call these.
    void SetChildChangedResult(wxVariant* value);
    void SetDoGetValueResult(wxVariant* value);
    void SetValueToStringResult(wxString* value);
    void SetStringToValueResult(bool result);
    void SetValidateValueResult(bool result);

    wxVariant DoGetValue() const override;
    void OnSetValue() override;
    wxString ValueToString(wxVariant& value, wxPGPropValFormatFlags flags) const override;
    bool StringToValue(wxVariant& variant, const wxString& text,
                       wxPGPropValFormatFlags flags) const override;
    wxVariant ChildChanged(wxVariant& this_value, int child_index,
                           wxVariant& child_value) const override;
    void RefreshChildren() override;
    bool ValidateValue(wxVariant& value, wxPGValidationInfo& validation_info) const override;
};

kwxPGProperty::kwxPGProperty(void* pObject, const wxString& label, const wxString& name,
                             const wxVariant& value) : wxPGProperty(label, name)
{
    m_object = pObject;
    m_child_changed_func = nullptr;
    m_refresh_children_func = nullptr;
    m_set_value_func = nullptr;
    m_do_get_value_func = nullptr;
    m_value_to_string_func = nullptr;
    m_string_to_value_func = nullptr;
    m_validate_value_func = nullptr;
    m_result_bool = false;
    m_has_result = false;
    m_value = value;
}

void kwxPGProperty::SetChildChangedResult(wxVariant* value)
{
    m_result_variant = value ? *value : wxVariant();
    m_has_result = true;
}

void kwxPGProperty::SetDoGetValueResult(wxVariant* value)
{
    m_result_variant = value ? *value : wxVariant();
    m_has_result = true;
}

void kwxPGProperty::SetValueToStringResult(wxString* value)
{
    m_result_string = value ? *value : wxString();
    m_has_result = true;
}

void kwxPGProperty::SetStringToValueResult(bool result)
{
    m_result_bool = result;
    m_has_result = true;
}

void kwxPGProperty::SetValidateValueResult(bool result)
{
    m_result_bool = result;
    m_has_result = true;
}

wxVariant kwxPGProperty::DoGetValue() const
{
    if (!m_do_get_value_func)
    {
        return wxPGProperty::DoGetValue();
    }

    m_result_variant = wxVariant();
    m_has_result = false;
    m_do_get_value_func(m_object);
    if (!m_has_result)
    {
        return wxPGProperty::DoGetValue();
    }
    return m_result_variant;
}

void kwxPGProperty::OnSetValue()
{
    if (!m_set_value_func)
    {
        wxPGProperty::OnSetValue();
        return;
    }
    m_set_value_func(m_object);
}

wxString kwxPGProperty::ValueToString(wxVariant& value, wxPGPropValFormatFlags flags) const
{
    if (!m_value_to_string_func)
    {
        return wxPGProperty::ValueToString(value, flags);
    }

    m_result_string.clear();
    m_has_result = false;
    m_value_to_string_func(m_object, &value, std::to_underlying(flags));
    if (!m_has_result)
    {
        return wxPGProperty::ValueToString(value, flags);
    }
    return m_result_string;
}

bool kwxPGProperty::StringToValue(wxVariant& variant, const wxString& text,
                                  wxPGPropValFormatFlags flags) const
{
    if (!m_string_to_value_func)
    {
        return wxPGProperty::StringToValue(variant, text, flags);
    }

    m_result_bool = false;
    m_has_result = false;
    m_string_to_value_func(m_object, &variant, const_cast<wxString*>(&text),
                           std::to_underlying(flags));
    if (!m_has_result)
    {
        return wxPGProperty::StringToValue(variant, text, flags);
    }
    return m_result_bool;
}

wxVariant kwxPGProperty::ChildChanged(wxVariant& this_value, int child_index,
                                      wxVariant& child_value) const
{
    if (!m_child_changed_func)
    {
        return wxPGProperty::ChildChanged(this_value, child_index, child_value);
    }

    m_result_variant = wxVariant();
    m_has_result = false;
    m_child_changed_func(m_object, &this_value, child_index, &child_value);
    if (!m_has_result)
    {
        return wxPGProperty::ChildChanged(this_value, child_index, child_value);
    }
    return m_result_variant;
}

void kwxPGProperty::RefreshChildren()
{
    if (!m_refresh_children_func)
    {
        wxPGProperty::RefreshChildren();
        return;
    }
    m_refresh_children_func(m_object);
}

bool kwxPGProperty::ValidateValue(wxVariant& value, wxPGValidationInfo& validation_info) const
{
    if (!m_validate_value_func)
    {
        return wxPGProperty::ValidateValue(value, validation_info);
    }

    // wxPGProperty::ValidateValue() accepts every value, so a callback that
    // publishes nothing must keep that answer instead of rejecting the value.
    m_result_bool = true;
    m_has_result = false;
    m_validate_value_func(m_object, &value, &validation_info);
    if (!m_has_result)
    {
        return true;
    }
    return m_result_bool;
}

// ---------------------------------------------------------------------------
// kwxPGTextCtrlEditor
//
// CreateControls() must keep the primary control the base class built and only
// add the secondary window (normally a wxPGMultiButton) the callback published.
// ---------------------------------------------------------------------------

class kwxPGTextCtrlEditor : public wxPGTextCtrlEditor
{
private:
    void* m_object;
    kwxPropHookCreateControlsFunc m_create_controls_func;
    kwxPropHookEventFunc m_on_event_func;

    mutable wxWindow* m_result_secondary;
    mutable bool m_result_handled;

public:
    explicit kwxPGTextCtrlEditor(void* pObject);

    void SetOnCreateControls(void* pFunction)
    {
        m_create_controls_func = (kwxPropHookCreateControlsFunc) pFunction;
    }
    void SetOnOnEvent(void* pFunction) { m_on_event_func = (kwxPropHookEventFunc) pFunction; }

    void SetCreateControlsResult(wxWindow* secondary) { m_result_secondary = secondary; }
    void SetOnEventResult(bool result) { m_result_handled = result; }

    wxPGWindowList CreateControls(wxPropertyGrid* prop_grid, wxPGProperty* property,
                                  const wxPoint& position, const wxSize& size) const override;
    bool OnEvent(wxPropertyGrid* prop_grid, wxPGProperty* property, wxWindow* ctrl,
                 wxEvent& event) const override;
    wxString GetName() const override;
};

kwxPGTextCtrlEditor::kwxPGTextCtrlEditor(void* pObject) : wxPGTextCtrlEditor()
{
    m_object = pObject;
    m_create_controls_func = nullptr;
    m_on_event_func = nullptr;
    m_result_secondary = nullptr;
    m_result_handled = false;
}

wxPGWindowList kwxPGTextCtrlEditor::CreateControls(wxPropertyGrid* prop_grid,
                                                   wxPGProperty* property, const wxPoint& position,
                                                   const wxSize& size) const
{
    wxPGWindowList window_list =
        wxPGTextCtrlEditor::CreateControls(prop_grid, property, position, size);
    if (!m_create_controls_func)
    {
        return window_list;
    }

    m_result_secondary = nullptr;
    m_create_controls_func(m_object, prop_grid, property, position.x, position.y, size.x, size.y,
                           window_list.GetPrimary());
    if (m_result_secondary)
    {
        window_list.SetSecondary(m_result_secondary);
    }
    return window_list;
}

bool kwxPGTextCtrlEditor::OnEvent(wxPropertyGrid* prop_grid, wxPGProperty* property, wxWindow* ctrl,
                                  wxEvent& event) const
{
    if (!m_on_event_func)
    {
        return wxPGTextCtrlEditor::OnEvent(prop_grid, property, ctrl, event);
    }

    m_result_handled = false;
    m_on_event_func(m_object, prop_grid, property, ctrl, &event);
    return m_result_handled;
}

// A registered editor is looked up by name, so the name must not collide with a
// built-in one (wxPGTextCtrlEditor reports "TextCtrlEditor").
wxString kwxPGTextCtrlEditor::GetName() const
{
    return wxS("kwxCustomEditor");
}

// ---------------------------------------------------------------------------
// kwxPropertyGridPage
// ---------------------------------------------------------------------------

class kwxPropertyGridPage : public wxPropertyGridPage
{
private:
    void* m_object;
    kwxPropHookVoidFunc m_is_handling_all_events_func;
    kwxPropHookVoidFunc m_init_func;
    kwxPropHookVoidFunc m_on_show_func;

    mutable bool m_result_handled;

public:
    explicit kwxPropertyGridPage(void* pObject);

    void SetOnIsHandlingAllEvents(void* pFunction)
    {
        m_is_handling_all_events_func = (kwxPropHookVoidFunc) pFunction;
    }
    void SetOnInit(void* pFunction) { m_init_func = (kwxPropHookVoidFunc) pFunction; }
    void SetOnOnShow(void* pFunction) { m_on_show_func = (kwxPropHookVoidFunc) pFunction; }

    void SetIsHandlingAllEventsResult(bool result) { m_result_handled = result; }

    bool IsHandlingAllEvents() const override;
    void Init() override;
    void OnShow() override;
};

kwxPropertyGridPage::kwxPropertyGridPage(void* pObject) : wxPropertyGridPage()
{
    m_object = pObject;
    m_is_handling_all_events_func = nullptr;
    m_init_func = nullptr;
    m_on_show_func = nullptr;
    m_result_handled = true;
}

bool kwxPropertyGridPage::IsHandlingAllEvents() const
{
    if (!m_is_handling_all_events_func)
    {
        return wxPropertyGridPage::IsHandlingAllEvents();
    }

    // The base answers true; a callback that publishes nothing keeps that answer.
    m_result_handled = true;
    m_is_handling_all_events_func(m_object);
    return m_result_handled;
}

void kwxPropertyGridPage::Init()
{
    if (!m_init_func)
    {
        wxPropertyGridPage::Init();
        return;
    }
    m_init_func(m_object);
}

void kwxPropertyGridPage::OnShow()
{
    if (!m_on_show_func)
    {
        wxPropertyGridPage::OnShow();
        return;
    }
    m_on_show_func(m_object);
}

// ---------------------------------------------------------------------------
// Exported wrappers
// ---------------------------------------------------------------------------

extern "C"
{
    // kwxPGProperty ----------------------------------------------------------

    EXPORT void* kwxPGProperty_Create(void* pObject, wxString* label, wxString* name,
                                      wxVariant* value)
    {
        return new kwxPGProperty(pObject, label ? *label : wxString(), name ? *name : wxString(),
                                 value ? *value : wxVariant());
    }

    EXPORT void kwxPGProperty_Delete(kwxPGProperty* self)
    {
        delete self;
    }

    EXPORT void kwxPGProperty_SetOnChildChanged(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnChildChanged(pFunction);
    }

    EXPORT void kwxPGProperty_SetOnRefreshChildren(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnRefreshChildren(pFunction);
    }

    EXPORT void kwxPGProperty_SetOnOnSetValue(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnOnSetValue(pFunction);
    }

    EXPORT void kwxPGProperty_SetOnDoGetValue(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnDoGetValue(pFunction);
    }

    EXPORT void kwxPGProperty_SetOnValueToString(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnValueToString(pFunction);
    }

    EXPORT void kwxPGProperty_SetOnStringToValue(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnStringToValue(pFunction);
    }

    EXPORT void kwxPGProperty_SetOnValidateValue(kwxPGProperty* self, void* pFunction)
    {
        self->SetOnValidateValue(pFunction);
    }

    EXPORT void kwxPGProperty_SetChildChangedResult(kwxPGProperty* self, wxVariant* value)
    {
        if (self)
        {
            self->SetChildChangedResult(value);
        }
    }

    EXPORT void kwxPGProperty_SetDoGetValueResult(kwxPGProperty* self, wxVariant* value)
    {
        if (self)
        {
            self->SetDoGetValueResult(value);
        }
    }

    EXPORT void kwxPGProperty_SetValueToStringResult(kwxPGProperty* self, wxString* value)
    {
        if (self)
        {
            self->SetValueToStringResult(value);
        }
    }

    EXPORT void kwxPGProperty_SetStringToValueResult(kwxPGProperty* self, int result)
    {
        if (self)
        {
            self->SetStringToValueResult(result != 0);
        }
    }

    EXPORT void kwxPGProperty_SetValidateValueResult(kwxPGProperty* self, int result)
    {
        if (self)
        {
            self->SetValidateValueResult(result != 0);
        }
    }

    // kwxPGTextCtrlEditor ----------------------------------------------------

    EXPORT void* kwxPGTextCtrlEditor_Create(void* pObject)
    {
        return new kwxPGTextCtrlEditor(pObject);
    }

    EXPORT void kwxPGTextCtrlEditor_Delete(kwxPGTextCtrlEditor* self)
    {
        delete self;
    }

    EXPORT void kwxPGTextCtrlEditor_SetOnCreateControls(kwxPGTextCtrlEditor* self, void* pFunction)
    {
        self->SetOnCreateControls(pFunction);
    }

    EXPORT void kwxPGTextCtrlEditor_SetOnOnEvent(kwxPGTextCtrlEditor* self, void* pFunction)
    {
        self->SetOnOnEvent(pFunction);
    }

    EXPORT void kwxPGTextCtrlEditor_SetCreateControlsResult(kwxPGTextCtrlEditor* self,
                                                            wxWindow* secondary)
    {
        if (self)
        {
            self->SetCreateControlsResult(secondary);
        }
    }

    EXPORT void kwxPGTextCtrlEditor_SetOnEventResult(kwxPGTextCtrlEditor* self, int result)
    {
        if (self)
        {
            self->SetOnEventResult(result != 0);
        }
    }

    // kwxPropertyGridPage ----------------------------------------------------

    EXPORT void* kwxPropertyGridPage_Create(void* pObject)
    {
        return new kwxPropertyGridPage(pObject);
    }

    EXPORT void kwxPropertyGridPage_Delete(kwxPropertyGridPage* self)
    {
        delete self;
    }

    EXPORT void kwxPropertyGridPage_SetOnIsHandlingAllEvents(kwxPropertyGridPage* self,
                                                             void* pFunction)
    {
        self->SetOnIsHandlingAllEvents(pFunction);
    }

    EXPORT void kwxPropertyGridPage_SetIsHandlingAllEventsResult(kwxPropertyGridPage* self,
                                                                 int result)
    {
        if (self)
        {
            self->SetIsHandlingAllEventsResult(result != 0);
        }
    }

    EXPORT void kwxPropertyGridPage_SetOnInit(kwxPropertyGridPage* self, void* pFunction)
    {
        self->SetOnInit(pFunction);
    }

    EXPORT void kwxPropertyGridPage_SetOnOnShow(kwxPropertyGridPage* self, void* pFunction)
    {
        self->SetOnOnShow(pFunction);
    }
}
