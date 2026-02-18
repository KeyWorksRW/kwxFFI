#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxClipboard* wxClipboard_Create()
    {
        return wxTheClipboard;
    }

    EXPORT void wxClipboard_Delete(wxClipboard* self)
    {
        // delete pObject;
    }

    EXPORT bool wxClipboard_Open(wxClipboard* self)
    {
        return self->Open();
    }

    EXPORT void wxClipboard_Close(wxClipboard* self)
    {
        self->Close();
    }

    EXPORT bool wxClipboard_IsOpened(wxClipboard* self)
    {
        return self->IsOpened();
    }

    EXPORT bool wxClipboard_SetData(wxClipboard* self, wxDataObject* data)
    {
        return self->SetData(data);
    }

    EXPORT bool wxClipboard_AddData(wxClipboard* self, wxDataObject* data)
    {
        return self->AddData(data);
    }

    EXPORT bool wxClipboard_IsSupported(wxClipboard* self, wxDataFormat* format)
    {
        return self->IsSupported(*format);
    }

    EXPORT bool wxClipboard_GetData(wxClipboard* self, wxDataObject* data)
    {
        return self->GetData(*data);
    }

    EXPORT void wxClipboard_Clear(wxClipboard* self)
    {
        self->Clear();
    }

    EXPORT bool wxClipboard_Flush(wxClipboard* self)
    {
        return self->Flush();
    }

    EXPORT void wxClipboard_UsePrimarySelection(wxClipboard* self, bool primary)
    {
        self->UsePrimarySelection(primary);
    }
}
