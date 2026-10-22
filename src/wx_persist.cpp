#include "kwx_wrapper.h"

extern "C"
{
    // Returns the global manager; the caller must not delete it.
    EXPORT wxPersistenceManager* wxPersistenceManager_Get()
    {
        return &wxPersistenceManager::Get();
    }

    EXPORT void wxPersistenceManager_Set([[maybe_unused]] wxPersistenceManager* self,
                                         wxPersistenceManager* manager)
    {
        wxPersistenceManager::Set(*manager);
    }

    EXPORT wxPersistentObject* wxPersistenceManager_Register(wxPersistenceManager* self,
                                                             void* object,
                                                             wxPersistentObject* persistent_object)
    {
        return self->Register(object, persistent_object);
    }

    EXPORT wxPersistentObject* wxPersistenceManager_Find(wxPersistenceManager* self, void* object)
    {
        return self->Find(object);
    }

    EXPORT void wxPersistenceManager_Unregister(wxPersistenceManager* self, void* object)
    {
        self->Unregister(object);
    }

    EXPORT void wxPersistenceManager_Save(wxPersistenceManager* self, void* object)
    {
        self->Save(object);
    }

    EXPORT bool wxPersistenceManager_Restore(wxPersistenceManager* self, void* object)
    {
        return self->Restore(object);
    }

    EXPORT void wxPersistenceManager_SaveAndUnregister(wxPersistenceManager* self, void* object)
    {
        self->SaveAndUnregister(object);
    }

    EXPORT bool wxPersistenceManager_RegisterAndRestore(wxPersistenceManager* self, void* object,
                                                        wxPersistentObject* persistent_object)
    {
        return self->RegisterAndRestore(object, persistent_object);
    }

    EXPORT void wxPersistenceManager_DisableSaving(wxPersistenceManager* self)
    {
        self->DisableSaving();
    }

    EXPORT void wxPersistenceManager_DisableRestoring(wxPersistenceManager* self)
    {
        self->DisableRestoring();
    }

    EXPORT wxString* wxPersistentObject_GetName(wxPersistentObject* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT wxString* wxPersistentObject_GetKind(wxPersistentObject* self)
    {
        return new wxString(self->GetKind());
    }

    EXPORT void* wxPersistentObject_GetObject(wxPersistentObject* self)
    {
        return self->GetObject();
    }

    EXPORT void wxPersistentObject_Save(wxPersistentObject* self)
    {
        self->Save();
    }

    EXPORT bool wxPersistentObject_Restore(wxPersistentObject* self)
    {
        return self->Restore();
    }
}
