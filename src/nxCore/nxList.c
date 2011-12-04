#include "nxList.h"

nxList* nxList_alloc(nxPointer data)
{
    nxList* obj = nxMalloc(sizeof(nxList));
    obj->data = data;
    obj->next = NX_NULL;
    return obj;
}

void nxList_free(nxList* obj)
{
    /*
    if(obj == NX_NULL)
    {
        return;
    }
    else if(obj->next == NX_NULL)
    {
        if(obj->data != NX_NULL)
        {
            nxFree(obj->data);
        }
        nxFree(obj);
    }
    else 
    {
        nxList_free(obj->next);
        nxFree(obj->data);
        nxFree(obj);
    }
    */
    if(obj == NX_NULL)
    {
        return;
    }

    nxList* curr;
    nxList* next;
    for(curr=obj, next=curr->next ; next != NX_NULL ; curr=next, next=next->next)
    {
        nxFree(curr->data);
        curr->next = NX_NULL;
        curr->data = NX_NULL;
        curr = NX_NULL;
    }
}

nxList* nxList_append(nxList* list, nxPointer data)
{
    /*
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
    */

    nxList* curr;
    nxList* prev;
    for(prev=NX_NULL, curr=list ; curr != NX_NULL ; prev=curr, curr=curr->next)
    {
        ;
    }
    if(prev==NX_NULL)
    {
        list = nxList_alloc(data);
        return list;
    }
    else
    {
        prev->next = nxList_alloc(data);
        return list;
    }
}

nxList* nxList_remove(nxList* list, nxPointer data)
{
    nxList* prev;
    nxList* curr;
    for(prev=NX_NULL, curr=list ; curr != NX_NULL ; prev=curr, curr=curr->next)
    {
        if(curr->data == data)
        {
            if(prev == NX_NULL)
            {
                list = curr->next;
                curr->next = NX_NULL;
                nxFree(curr);
            }
            else
            {
                prev = curr->next;
                curr->next = NX_NULL;
                nxFree(curr);
            }
            return list;
        }
    }
    return list;
}

nxList* nxList_empty(nxList* list)
{
    nxList_free(list);
    return NX_NULL;
}

nxUInt nxList_getLength(nxList* list)
{
    nxUInt cnt = 0;
    nxList* curr;
    for(curr=list ; curr != NX_NULL ; curr=curr->next)
    {
        if(curr->data != NX_NULL)
        {
            cnt++;
        }
    }
    return cnt;
}
