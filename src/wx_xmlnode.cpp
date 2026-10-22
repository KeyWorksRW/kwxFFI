#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxXmlAttribute* wxXmlAttribute_Create(wxString* name, wxString* value)
    {
        return new wxXmlAttribute(*name, *value);
    }

    EXPORT void wxXmlAttribute_Delete(wxXmlAttribute* self)
    {
        delete self;
    }

    EXPORT wxString* wxXmlAttribute_GetName(wxXmlAttribute* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT wxString* wxXmlAttribute_GetValue(wxXmlAttribute* self)
    {
        return new wxString(self->GetValue());
    }

    EXPORT wxXmlAttribute* wxXmlAttribute_GetNext(wxXmlAttribute* self)
    {
        return self->GetNext();
    }

    EXPORT void wxXmlAttribute_SetName(wxXmlAttribute* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT void wxXmlAttribute_SetValue(wxXmlAttribute* self, wxString* value)
    {
        self->SetValue(*value);
    }

    EXPORT void wxXmlAttribute_SetNext(wxXmlAttribute* self, wxXmlAttribute* next_attribute)
    {
        self->SetNext(next_attribute);
    }

    EXPORT wxXmlNode* wxXmlNode_Create(int node_type, wxString* name, wxString* content,
                                       int line_number)
    {
        return new wxXmlNode(static_cast<wxXmlNodeType>(node_type), *name, *content, line_number);
    }

    EXPORT void wxXmlNode_Delete(wxXmlNode* self)
    {
        delete self;
    }

    EXPORT int wxXmlNode_GetType(wxXmlNode* self)
    {
        return static_cast<int>(self->GetType());
    }

    EXPORT void wxXmlNode_SetType(wxXmlNode* self, int node_type)
    {
        self->SetType(static_cast<wxXmlNodeType>(node_type));
    }

    EXPORT wxString* wxXmlNode_GetName(wxXmlNode* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT void wxXmlNode_SetName(wxXmlNode* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxXmlNode_GetContent(wxXmlNode* self)
    {
        return new wxString(self->GetContent());
    }

    EXPORT wxString* wxXmlNode_GetNodeContent(wxXmlNode* self)
    {
        return new wxString(self->GetNodeContent());
    }

    EXPORT void wxXmlNode_SetContent(wxXmlNode* self, wxString* content)
    {
        self->SetContent(*content);
    }

    EXPORT bool wxXmlNode_GetAttribute(wxXmlNode* self, wxString* attribute_name, wxString* value)
    {
        return self->GetAttribute(*attribute_name, value);
    }

    EXPORT wxString* wxXmlNode_GetAttributeWithDefault(wxXmlNode* self, wxString* attribute_name,
                                                       wxString* default_value)
    {
        return new wxString(self->GetAttribute(*attribute_name, *default_value));
    }

    EXPORT bool wxXmlNode_HasAttribute(wxXmlNode* self, wxString* attribute_name)
    {
        return self->HasAttribute(*attribute_name);
    }

    EXPORT void wxXmlNode_AddAttribute(wxXmlNode* self, wxString* name, wxString* value)
    {
        self->AddAttribute(*name, *value);
    }

    EXPORT void wxXmlNode_AddAttributeObject(wxXmlNode* self, wxXmlAttribute* attribute)
    {
        self->AddAttribute(attribute);
    }

    EXPORT bool wxXmlNode_DeleteAttribute(wxXmlNode* self, wxString* attribute_name)
    {
        return self->DeleteAttribute(*attribute_name);
    }

    EXPORT wxXmlAttribute* wxXmlNode_GetAttributes(wxXmlNode* self)
    {
        return self->GetAttributes();
    }

    EXPORT wxXmlNode* wxXmlNode_GetChildren(wxXmlNode* self)
    {
        return self->GetChildren();
    }

    EXPORT void wxXmlNode_AddChild(wxXmlNode* self, wxXmlNode* child)
    {
        self->AddChild(child);
    }

    EXPORT bool wxXmlNode_InsertChild(wxXmlNode* self, wxXmlNode* child, wxXmlNode* following_node)
    {
        return self->InsertChild(child, following_node);
    }

    EXPORT bool wxXmlNode_InsertChildAfter(wxXmlNode* self, wxXmlNode* child,
                                           wxXmlNode* preceding_node)
    {
        return self->InsertChildAfter(child, preceding_node);
    }

    EXPORT bool wxXmlNode_RemoveChild(wxXmlNode* self, wxXmlNode* child)
    {
        return self->RemoveChild(child);
    }

    EXPORT wxXmlNode* wxXmlNode_GetNext(wxXmlNode* self)
    {
        return self->GetNext();
    }

    EXPORT void wxXmlNode_SetNext(wxXmlNode* self, wxXmlNode* next_node)
    {
        self->SetNext(next_node);
    }

    EXPORT wxXmlNode* wxXmlNode_GetParent(wxXmlNode* self)
    {
        return self->GetParent();
    }

    EXPORT void wxXmlNode_SetParent(wxXmlNode* self, wxXmlNode* parent)
    {
        self->SetParent(parent);
    }

    EXPORT int wxXmlNode_GetLineNumber(wxXmlNode* self)
    {
        return self->GetLineNumber();
    }

    EXPORT bool wxXmlNode_GetNoConversion(wxXmlNode* self)
    {
        return self->GetNoConversion();
    }

    EXPORT void wxXmlNode_SetNoConversion(wxXmlNode* self, bool no_conversion)
    {
        self->SetNoConversion(no_conversion);
    }
}
