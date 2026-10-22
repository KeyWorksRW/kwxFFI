#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxMBConv* wxMBConvUTF8_Create(int options)
    {
        return new wxMBConvUTF8(options);
    }

    EXPORT void wxMBConv_Delete(wxMBConv* self)
    {
        delete self;
    }

    EXPORT int wxMBConv_GetMaxCharLen(wxMBConv* self)
    {
        return static_cast<int>(self->GetMaxCharLen());
    }

    EXPORT int wxMBConv_MB2WC(wxMBConv* self, void* output, char* input, int output_size)
    {
        return static_cast<int>(
            self->MB2WC(static_cast<wchar_t*>(output), input, static_cast<size_t>(output_size)));
    }

    EXPORT int wxMBConv_WC2MB(wxMBConv* self, char* output, void* input, int output_size)
    {
        return static_cast<int>(self->WC2MB(output, static_cast<const wchar_t*>(input),
                                            static_cast<size_t>(output_size)));
    }
}
