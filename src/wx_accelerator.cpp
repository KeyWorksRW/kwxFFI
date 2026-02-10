#include "wrapper.h"

extern "C"
{
    EXPORT void* wxAcceleratorEntry_Create(int flags, int keyCode, int cmd)
    {
        return (void*) new wxAcceleratorEntry(flags, keyCode, cmd);
    }

    EXPORT void wxAcceleratorEntry_Delete(void* _obj)
    {
        delete (wxAcceleratorEntry*) _obj;
    }

    EXPORT void wxAcceleratorEntry_Set(void* _obj, int flags, int keyCode, int cmd, void* item)
    {
        ((wxAcceleratorEntry*) _obj)->Set(flags, keyCode, cmd, (wxMenuItem*) item);
    }

    EXPORT int wxAcceleratorEntry_GetFlags(void* _obj)
    {
        return ((wxAcceleratorEntry*) _obj)->GetFlags();
    }

    EXPORT int wxAcceleratorEntry_GetKeyCode(void* _obj)
    {
        return ((wxAcceleratorEntry*) _obj)->GetKeyCode();
    }

    EXPORT int wxAcceleratorEntry_GetCommand(void* _obj)
    {
        return ((wxAcceleratorEntry*) _obj)->GetCommand();
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

    EXPORT void wxAcceleratorTable_Delete(void* _obj)
    {
        delete (wxAcceleratorEntry*) _obj;
    }
}
