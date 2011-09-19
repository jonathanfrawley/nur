#include "nxMM.h"

void *nxMalloc(unsigned size)
{
    return malloc(size);
}

void nxFree(void* ptr)
{
    free(ptr);
}
