#include "kwx_wrapper.h"

extern "C"
{
    EXPORT int boolToInt(bool val)
    {
        return val ? 1 : 0;
    }

    EXPORT bool intToBool(int val)
    {
        return val != 0 ? true : false;
    }
}
