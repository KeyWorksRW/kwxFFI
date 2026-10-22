#include "kwx_wrapper.h"

// wxGenericAboutDialog::AddControl() is protected. The local subclass makes the
// overload public so the FFI wrapper can add custom controls to a dialog that
// was created by wxGenericAboutDialog_Create().
class kwxGenericAboutDialog : public wxGenericAboutDialog
{
public:
    kwxGenericAboutDialog(const wxAboutDialogInfo& info, wxWindow* parent) :
        wxGenericAboutDialog(info, parent)
    {
    }

    using wxGenericAboutDialog::AddControl;
};

extern "C"
{
    EXPORT void* wxGenericAboutDialog_Create(wxAboutDialogInfo* info, wxWindow* parent)
    {
        return static_cast<void*>(new kwxGenericAboutDialog(*info, parent));
    }

    EXPORT bool wxGenericAboutDialog_AddControl(wxGenericAboutDialog* self, wxWindow* window)
    {
        kwxGenericAboutDialog* dialog = dynamic_cast<kwxGenericAboutDialog*>(self);
        if (!dialog)
        {
            return false;
        }
        dialog->AddControl(window);
        return true;
    }

    EXPORT int wxGenericAboutDialog_ShowModal(wxGenericAboutDialog* self)
    {
        return self->ShowModal();
    }

    EXPORT void wxGenericAboutDialog_Delete(wxGenericAboutDialog* self)
    {
        delete self;
    }
}
