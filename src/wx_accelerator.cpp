#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxAcceleratorEntry_Create(int flags, int keyCode, int cmd)
    {
        return (void*) new wxAcceleratorEntry(flags, keyCode, cmd);
    }

    EXPORT void wxAcceleratorEntry_Delete(void* pObject)
    {
        delete (wxAcceleratorEntry*) pObject;
    }

    EXPORT void wxAcceleratorEntry_Set(void* pObject, int flags, int keyCode, int cmd, void* item)
    {
        ((wxAcceleratorEntry*) pObject)->Set(flags, keyCode, cmd, (wxMenuItem*) item);
    }

    EXPORT int wxAcceleratorEntry_GetFlags(void* pObject)
    {
        return ((wxAcceleratorEntry*) pObject)->GetFlags();
    }

    EXPORT int wxAcceleratorEntry_GetKeyCode(void* pObject)
    {
        return ((wxAcceleratorEntry*) pObject)->GetKeyCode();
    }

    EXPORT int wxAcceleratorEntry_GetCommand(void* pObject)
    {
        return ((wxAcceleratorEntry*) pObject)->GetCommand();
    }

    EXPORT void* wxAcceleratorTable_Create(int count, void* entries)
    {
        wxAcceleratorEntry* list = new wxAcceleratorEntry[count];

        for (int i = 0; i < count; i++)
            list[i] = *(((wxAcceleratorEntry**) entries)[i]);

        wxAcceleratorTable* result = new wxAcceleratorTable(count, list);

        delete[] list;

        return (void*) result;
    }

    EXPORT void wxAcceleratorTable_Delete(void* pObject)
    {
        delete (wxAcceleratorEntry*) pObject;
    }
}
