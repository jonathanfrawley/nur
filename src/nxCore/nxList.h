#ifndef  NXLIST_H
#define  NXLIST_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxMM.h>

typedef struct nxList 
{
    nxPointer data;
    struct nxList *next; 
} nxList;

nxList* nxList_alloc(nxPointer data);
void nxList_free(nxList* obj);

//----------------------------------------------------------------------
//  Adds data to this list. List will handle freeing data.
//  Returns: New beginning of list.
//----------------------------------------------------------------------
nxList* nxList_append(nxList* list, nxPointer data);

//----------------------------------------------------------------------
//  Removes elem w/ data == data in this list.
//  Returns: New beginning of list.
//----------------------------------------------------------------------
nxList* nxList_remove(nxList* list, nxPointer data);

//----------------------------------------------------------------------
//  Empties list and frees data.
//----------------------------------------------------------------------
nxList* nxList_empty(nxList* list);

//----------------------------------------------------------------------
//  Returns: Length of list.
//----------------------------------------------------------------------
nxUInt nxList_getLength(nxList* list);

#endif   // NXLIST_H
