#ifndef  NXPROCESS_H
#define  NXPROCESS_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxEvent/nxEvent.h>
#include <nxEvent/nxEventManager.h>

typedef enum nxProcessType 
{
    NX_PROCESS_WAIT,
    NX_PROCESS_TRIGGEREVENT
} nxProcessType;

typedef struct nxProcess 
{
    nxProcessType type;
    nxBool dead;
    struct nxProcess* next;

    //WAIT
    nxUInt waitTime;
    nxUInt time;

    //FIREEVENT
    nxEvent* event;
} nxProcess;

nxProcess* nxProcess_alloc(nxProcessType type);

void nxProcess_free(nxProcess* obj);

void nxProcess_init(nxProcess* obj);

void nxProcess_update(nxProcess* obj, nxUInt deltaMilli);

#endif   // NXPROCESS_H
