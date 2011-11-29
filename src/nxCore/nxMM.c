#include "nxMM.h"

#include <nxCore/nxLog.h>

void *nxMalloc(nxUInt size)
{
    void* dataPtr = (void*)malloc(size);
    if(dataPtr == NX_NULL) 
    {
        assert(0 && "dynamic memory allocation failed");
        return NX_NULL;
    }
    return dataPtr;
}

void nxFree(void* ptr)
{
    free(ptr);
}
