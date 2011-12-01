#include "nxList.h"

nxList* nxList_alloc(void)
{
    nxList* obj = nxMalloc(sizeof(nxList));
    obj->data = NX_NULL;
    obj->next = NX_NULL;
    return obj;
}

void nxList_free(nxList* obj)
{
    if(obj == NX_NULL)
    {
        return;
    }
    else if(obj->next == NX_NULL)
    {
        nxFree(obj->data);
        nxFree(obj);
    }
    else 
    {
        nxList_free(obj->next);
        nxFree(obj->data);
        nxFree(obj);
    }
}

nxList* nxList_append(nxList* list, nxPointer data)
{
    if(list == NX_NULL)
    {
        //1st
        list = nxList_alloc();
        list->data = data;
        return list;
    }
    else if(list->next == NX_NULL)
    {
        //not 1st
        list->next = nxList_alloc();
        list->next->data = data;
        return list->next;
    }
    else
    {
        //recurse
        nxList* lastElem = nxList_append(list->next, data);
        if(list != lastElem)
        {
            return list;
        }
    }
}

nxList* nxList_remove(nxList* list, nxPointer data)
{
    return 0;
}

void nxList_empty(nxList* list)
{
}

nxUInt nxList_getLength(nxList* list)
{
    if(list == NX_NULL)
    {
        return 0;
    }
    else
    {
        return 1+nxList_getLength(list->next);
    }
}
