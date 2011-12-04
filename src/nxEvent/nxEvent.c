#include "nxEvent.h"

nxEvent* nxEvent_alloc(nxEventType type)
{
    nxEvent* obj = (nxEvent*)nxMalloc(sizeof(nxEvent));
    obj->type = type;
    return obj;
}

void nxEvent_free(nxEvent* obj)
{
    nxFree(obj->data);
    nxFree(obj);
}
