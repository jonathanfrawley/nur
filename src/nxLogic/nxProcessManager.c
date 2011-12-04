#include "nxProcessManager.h"

static nxProcessManager instance;

nxProcessManager* nxProcessManager_alloc()
{
    nxProcessManager* obj = (nxProcessManager*)nxMalloc(sizeof(nxProcessManager));
    nxProcessManager_init(obj);
    return obj;
}

void nxProcessManager_free(nxProcessManager* obj)
{
    nxList_free(obj->_processes);
    nxFree(obj);
}

void nxProcessManager_init(nxProcessManager* obj)
{
    obj->_processes = NX_NULL;
}

nxProcessManager* nxProcessManager_getInstance()
{
    return (&instance);
}

void nxProcessManager_attach(nxProcessManager* obj, nxProcess* process)
{
    obj->_processes = nxList_append(obj->_processes, process);
    process->dead = NX_FALSE;
}

void nxProcessManager_detach(nxProcessManager* obj, nxProcess* process)
{
    process->dead = NX_TRUE;
    obj->_processes = nxList_remove(obj->_processes, process);
}

void nxProcessManager_update(nxProcessManager* obj, nxUInt deltaMilli)
{
    nxList* pList;
    for(pList = obj->_processes; pList != NX_NULL ; pList = pList->next)
    {
        nxProcess* process = (nxProcess*)pList->data;
        nxProcess_update(process, deltaMilli);
        if(process->dead)
        {
            if(process->next != NX_NULL)
            {
                nxProcessManager_attach(obj, process->next);
            }
            nxProcessManager_detach(obj, process);
        }
    }
}
