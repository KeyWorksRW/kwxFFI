#include "wrapper.h"
#include <wx/cmdproc.h>
#include <wx/docview.h>
extern "C"
{
    typedef int _cdecl (*TGetResp)(void* _obj, int _und);
}

class kwxCommand : public wxCommand
{
private:
    TGetResp func;
    void* EiffelObject;

public:
    kwxCommand(bool _und, const wxString& _nme, void* _obj, void* _clb) : wxCommand(_und, _nme)
    {
        func = (TGetResp) _clb;
        EiffelObject = _obj;
    }

    bool Do() { return func(EiffelObject, 0) != 0; }

    bool Undo() { return func(EiffelObject, 1) != 0; }
};

extern "C"
{
    EXPORT void* kwxCommand_Create(bool _und, wxString* _nme, void* _obj, void* _clb)
    {
        return (void*) new kwxCommand(_und, *_nme, _obj, _clb);
    }

    EXPORT void kwxCommand_Delete(kwxCommand* self)
    {
        delete self;
    }

    EXPORT wxString* kwxCommand_GetName(void* _obj)
    {
        return new wxString(((kwxCommand*) _obj)->GetName());
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

    EXPORT int wxCommandProcessor_GetCommands(wxCommandProcessor* self, void* _ref)
    {
        wxList lst = self->GetCommands();
        if (_ref)
        {
            for (unsigned int i = 0; i < lst.GetCount(); i++)
                ((void**) _ref)[i] = (void*) lst.Item(i);
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
