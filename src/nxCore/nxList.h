#ifndef  NXLIST_H
#define  NXLIST_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxMM.h>

typedef struct nxList 
{
    nxPointer data;
    struct nxList *next; 
} nxList;

nxList* nxList_alloc(void);
void nxList_free(nxList* obj);

nxList* nxList_append(nxList* list, nxPointer data);
nxList* nxList_remove(nxList* list, nxPointer data);
void nxList_empty(nxList* list);
nxUInt nxList_getLength(nxList* list);

#endif   // NXLIST_H
