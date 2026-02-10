#include "wrapper.h"
#include <wx/cmdproc.h>
#include <wx/docview.h>
extern "C"
{
    typedef int _cdecl (*TGetResp)(void* pObject, int canUndo);
}

class kwxCommand : public wxCommand
{
private:
    TGetResp func;
    void* EiffelObject;

public:
    kwxCommand(bool canUndo, const wxString& name, void* pObject, void* callback) : wxCommand(canUndo, name)
    {
        func = (TGetResp) callback;
        EiffelObject = pObject;
    }

    bool Do() { return func(EiffelObject, 0) != 0; }

    bool Undo() { return func(EiffelObject, 1) != 0; }
};

extern "C"
{
    EXPORT void* kwxCommand_Create(bool canUndo, wxString* name, void* pObject, void* callback)
    {
        return (void*) new kwxCommand(canUndo, *name, pObject, callback);
    }

    EXPORT void kwxCommand_Delete(kwxCommand* self)
    {
        delete self;
    }

    EXPORT wxString* kwxCommand_GetName(void* pObject)
    {
        return new wxString(((kwxCommand*) pObject)->GetName());
    }

    EXPORT bool kwxCommand_CanUndo(kwxCommand* self)
    {
        return self->CanUndo();
    }

    EXPORT void* wxCommandProcessor_wxCommandProcessor(int maxCommands)
    {
        return (void*) new wxCommandProcessor(maxCommands);
    }

    EXPORT void wxCommandProcessor_Delete(wxCommandProcessor* self)
    {
        delete self;
    }

    EXPORT bool wxCommandProcessor_Submit(wxCommandProcessor* self, wxCommand* command,
                                          bool storeIt)
    {
        return self->Submit(command, storeIt);
    }

    EXPORT bool wxCommandProcessor_Undo(wxCommandProcessor* self)
    {
        return self->Undo();
    }

    EXPORT bool wxCommandProcessor_Redo(wxCommandProcessor* self)
    {
        return self->Redo();
    }

    EXPORT bool wxCommandProcessor_CanUndo(wxCommandProcessor* self)
    {
        return self->CanUndo();
    }

    EXPORT bool wxCommandProcessor_CanRedo(wxCommandProcessor* self)
    {
        return self->CanRedo();
    }

    EXPORT void wxCommandProcessor_SetEditMenu(wxCommandProcessor* self, wxMenu* menu)
    {
        self->SetEditMenu(menu);
    }

    EXPORT void* wxCommandProcessor_GetEditMenu(wxCommandProcessor* self)
    {
        return (void*) self->GetEditMenu();
    }

    EXPORT void wxCommandProcessor_SetMenuStrings(wxCommandProcessor* self)
    {
        self->SetMenuStrings();
    }

    EXPORT void wxCommandProcessor_Initialize(wxCommandProcessor* self)
    {
        self->Initialize();
    }

    EXPORT int wxCommandProcessor_GetCommands(wxCommandProcessor* self, void* ref)
    {
        wxList lst = self->GetCommands();
        if (ref)
        {
            for (unsigned int i = 0; i < lst.GetCount(); i++)
                ((void**) ref)[i] = (void*) lst.Item(i);
        }

        return lst.GetCount();
    }

    EXPORT int wxCommandProcessor_GetMaxCommands(wxCommandProcessor* self)
    {
        return self->GetMaxCommands();
    }

    EXPORT void wxCommandProcessor_ClearCommands(wxCommandProcessor* self)
    {
        self->ClearCommands();
    }
}
