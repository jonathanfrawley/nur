#ifndef  NXPROCESSMANAGER_H
#define  NXPROCESSMANAGER_H

#include <nxCore/nxList.h>
#include <nxCore/nxMM.h>
#include <nxLogic/nxProcess.h>

typedef struct nxProcessManager 
{
    nxList* _processes;
} nxProcessManager;

nxProcessManager* nxProcessManager_alloc();

void nxProcessManager_free(nxProcessManager* manager);

void nxProcessManager_init(nxProcessManager* obj);

nxProcessManager* nxProcessManager_getInstance();

void nxProcessManager_attach(nxProcessManager* manager, nxProcess* process);

void nxProcessManager_detach(nxProcessManager* manager, nxProcess* process);

void nxProcessManager_update(nxProcessManager* manager, nxUInt deltaMilli);


#endif   // NXPROCESSMANAGER_H
