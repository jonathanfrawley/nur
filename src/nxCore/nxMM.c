#include "nxMM.h"

void *nxMalloc(nxUInt size)
{
    return malloc(size);
}

void nxFree(void* ptr)
{
    free(ptr);
}
