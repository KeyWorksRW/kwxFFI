#pragma once

// Callback helper for wxFileDialogCustomizeHook.
//
// The hook is passed to wxFileDialog::SetCustomizeHook(); wxWidgets calls the three
// virtual methods below while the dialog is being created, updated, and accepted.
// The callbacks are declared with their exact function-pointer types so no cast from
// a void* is required.

typedef void (*FileDialogCustomControlsFunc)(void* pObject, wxFileDialogCustomize* customizer);
typedef void (*FileDialogCustomControlsUpdateFunc)(void* pObject);

class kwxFileDialogCustomizeHook : public wxFileDialogCustomizeHook
{
public:
    kwxFileDialogCustomizeHook(void* pObject, FileDialogCustomControlsFunc add_func,
                               FileDialogCustomControlsUpdateFunc update_func,
                               FileDialogCustomControlsUpdateFunc transfer_func) :
        m_kwx_object(pObject), m_add_func(add_func), m_update_func(update_func),
        m_transfer_func(transfer_func)
    {
    }

    void AddCustomControls(wxFileDialogCustomize& customizer) override
    {
        if (m_add_func)
        {
            m_add_func(m_kwx_object, &customizer);
        }
    }

    void UpdateCustomControls() override
    {
        if (m_update_func)
        {
            m_update_func(m_kwx_object);
        }
    }

    void TransferDataFromCustomControls() override
    {
        if (m_transfer_func)
        {
            m_transfer_func(m_kwx_object);
        }
    }

private:
    void* m_kwx_object;
    FileDialogCustomControlsFunc m_add_func;
    FileDialogCustomControlsUpdateFunc m_update_func;
    FileDialogCustomControlsUpdateFunc m_transfer_func;
};
