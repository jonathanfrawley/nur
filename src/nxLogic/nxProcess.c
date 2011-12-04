#include "nxProcess.h"

nxProcess* nxProcess_alloc(nxProcessType type)
{
    nxProcess* obj = (nxProcess*)nxMalloc(sizeof(nxProcess));
    obj->type = type;
    nxProcess_init(obj);
    return obj;
}

void nxProcess_free(nxProcess* obj)
{
    nxEvent_free(obj->event);
    nxFree(obj);
}

void nxProcess_init(nxProcess* obj)
{
    obj->waitTime = 0;
    obj->time = 0;
    obj->dead = NX_FALSE;
    obj->next = NX_NULL;
    obj->event = NX_NULL;
}

void nxProcess_update(nxProcess* obj, nxUInt deltaMilli)
{
    switch(obj->type)
    {
        case NX_PROCESS_WAIT:
            obj->time += deltaMilli;
            if(obj->time >= obj->waitTime)
            {
                obj->dead = NX_TRUE;
            }
            break;
        case NX_PROCESS_TRIGGEREVENT:
            nxEventManager_triggerEvent((*obj->event));
            obj->dead = NX_TRUE;
            break;
        default:
            nxAssertFail("Unkown process type.");
            break;
    }
}
