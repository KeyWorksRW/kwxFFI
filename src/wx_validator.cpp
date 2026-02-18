#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxValidator_Create()
    {
        return (void*) new wxValidator();
    }

    EXPORT void wxValidator_Delete(wxValidator* self)
    {
        delete self;
    }

    EXPORT bool wxValidator_Validate(wxValidator* self, wxWindow* parent)
    {
        return self->Validate(parent);
    }

    EXPORT bool wxValidator_TransferToWindow(wxValidator* self)
    {
        return self->TransferToWindow();
    }

    EXPORT bool wxValidator_TransferFromWindow(wxValidator* self)
    {
        return self->TransferFromWindow();
    }

    EXPORT void* wxValidator_GetWindow(wxValidator* self)
    {
        return (void*) self->GetWindow();
    }

    EXPORT void wxValidator_SetWindow(wxValidator* self, wxWindow* win)
    {
        self->SetWindow(win);
    }

    // EWXWEXPORT(void,wxValidator_SetBellOnError)(bool doIt)
    EXPORT void wxValidator_SuppressBellOnError(bool doIt)
    {
        //	wxValidator::SetBellOnError(doIt);
        wxValidator::SuppressBellOnError(doIt);
    }

    EXPORT void* wxTextValidator_Create(int style, void* val)
    {
        return (void*) new wxTextValidator((long) style, new wxString);
    }

    EXPORT int wxTextValidator_GetStyle(wxTextValidator* self)
    {
        return (int) self->GetStyle();
    }

    EXPORT void wxTextValidator_SetStyle(wxTextValidator* self, int style)
    {
        self->SetStyle((long) style);
    }

    EXPORT void wxTextValidator_SetIncludes(wxTextValidator* self, void* list, int count)
    {
        wxArrayString str;

        for (int i = 0; i < count; i++)
            str.Add(((char**) list)[i]);

        self->SetIncludes(str);
    }

    EXPORT void* wxTextValidator_GetIncludes(wxTextValidator* self, int* count)
    {
        void* retval = nullptr;

        if (count != nullptr)
        {
            wxArrayString items = self->GetIncludes();
            char** items_copy = (char**) malloc(sizeof(char*) * items.GetCount());
            if (!items_copy)
            {
                *count = 0;
                return nullptr;
            }

            for (unsigned int i = 0; i < items.GetCount(); i++)
            {
                items_copy[i] = strdup(items.Item(i).utf8_str().data());
            }
            retval = (void*) items_copy;
            *count = items.GetCount();
        }
        return retval;
    }

    EXPORT void wxTextValidator_SetExcludes(wxTextValidator* self, void* list, int count)
    {
        wxArrayString str;

        for (int i = 0; i < count; i++)
            str.Add(((char**) list)[i]);

        self->SetExcludes(str);
    }

    EXPORT void* wxTextValidator_GetExcludes(wxTextValidator* self, int* count)
    {
        void* retval = nullptr;

        if (count != nullptr)
        {
            wxArrayString items = self->GetExcludes();
            char** items_copy = (char**) malloc(sizeof(char*) * items.GetCount());
            if (!items_copy)
            {
                *count = 0;
                return nullptr;
            }

            for (unsigned int i = 0; i < items.GetCount(); i++)
            {
                items_copy[i] = strdup(items.Item(i).utf8_str().data());
            }
            retval = (void*) items_copy;
            *count = items.GetCount();
        }
        return retval;
    }

    EXPORT void* wxTextValidator_Clone(wxTextValidator* self)
    {
        return (void*) self->Clone();
    }

    EXPORT bool wxTextValidator_TransferToWindow(wxTextValidator* self)
    {
        return self->TransferToWindow();
    }

    EXPORT bool wxTextValidator_TransferFromWindow(wxTextValidator* self)
    {
        return self->TransferFromWindow();
    }

    EXPORT void wxTextValidator_OnChar(wxTextValidator* self, wxKeyEvent* event)
    {
        self->OnChar(*event);
    }

    EXPORT void* kwxTextValidator_Create(void* self, void* func, void* text, long style)
    {
        return new kwxTextValidator(self, func, text, style);
    }
}

bool kwxTextValidator::Validate(wxWindow* parent)
{
    if (obj && fnc)
        return fnc(obj) != 0;
    else
        return wxTextValidator::Validate(parent);
}
