#ifndef NXGAMELOGIC_H
#define NXGAMELOGIC_H

#include <nxEntity.h>
#include <nxCore/nxTypes.h>
#include <nxEvent/nxEvent.h>

#define NX_MAX_ENTITIES 1024

typedef struct nxGameLogic
{
	nxEntity entities[NX_MAX_ENTITIES];
	nxInt currentEntityId;
	nxInt playerId;
} nxGameLogic;

nxGameLogic* nxGameLogic_new();
nxInt nxGameLogic_init(nxGameLogic* obj);
nxInt nxGameLogic_update(nxGameLogic* obj);
void nxGameLogic_shutdown(nxGameLogic* obj);

nxInt nxGameLogic_addNonPlayerEntity(nxGameLogic* obj);
nxInt nxGameLogic_addPlayerEntity(nxGameLogic* obj);

void nxGameLogic_handleEvent(nxEvent evt, void* vobj);

#endif
