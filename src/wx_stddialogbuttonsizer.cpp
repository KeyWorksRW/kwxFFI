// wxStdDialogButtonSizer - Standard dialog button sizer
#include "wrapper.h"

extern "C"
{
    // Constructor
    EXPORT wxStdDialogButtonSizer* wxStdDialogButtonSizer_Create()
    {
        return new wxStdDialogButtonSizer();
    }

    // Add button
    EXPORT void wxStdDialogButtonSizer_AddButton(wxStdDialogButtonSizer* self, wxButton* button)
    {
        self->AddButton(button);
    }

    // Set affirmative button
    EXPORT void wxStdDialogButtonSizer_SetAffirmativeButton(wxStdDialogButtonSizer* self,
                                                            wxButton* button)
    {
        self->SetAffirmativeButton(button);
    }

    // Set negative button
    EXPORT void wxStdDialogButtonSizer_SetNegativeButton(wxStdDialogButtonSizer* self,
                                                         wxButton* button)
    {
        self->SetNegativeButton(button);
    }

    // Set cancel button
    EXPORT void wxStdDialogButtonSizer_SetCancelButton(wxStdDialogButtonSizer* self,
                                                       wxButton* button)
    {
        self->SetCancelButton(button);
    }

    // Realize (finalize layout)
    EXPORT void wxStdDialogButtonSizer_Realize(wxStdDialogButtonSizer* self)
    {
        self->Realize();
    }

    // Get affirmative button
    EXPORT wxButton* wxStdDialogButtonSizer_GetAffirmativeButton(wxStdDialogButtonSizer* self)
    {
        return self->GetAffirmativeButton();
    }

    // Get apply button
    EXPORT wxButton* wxStdDialogButtonSizer_GetApplyButton(wxStdDialogButtonSizer* self)
    {
        return self->GetApplyButton();
    }

    // Get negative button
    EXPORT wxButton* wxStdDialogButtonSizer_GetNegativeButton(wxStdDialogButtonSizer* self)
    {
        return self->GetNegativeButton();
    }

    // Get cancel button
    EXPORT wxButton* wxStdDialogButtonSizer_GetCancelButton(wxStdDialogButtonSizer* self)
    {
        return self->GetCancelButton();
    }

    // Get help button
    EXPORT wxButton* wxStdDialogButtonSizer_GetHelpButton(wxStdDialogButtonSizer* self)
    {
        return self->GetHelpButton();
    }
}
