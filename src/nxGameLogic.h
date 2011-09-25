#ifndef NXGAMELOGIC_H
#define NXGAMELOGIC_H

#include <nxEntity.h>
#include <nxCore/nxTypes.h>
#include <nxEvent/nxEvent.h>

#define MAX_ENTITIES 1024

typedef struct nxGameLogic
{
	nxEntity entities[MAX_ENTITIES];
	nxInt currentEntityId;
} nxGameLogic;

nxGameLogic* nxGameLogic_new();
nxInt nxGameLogic_init(nxGameLogic* obj);
nxInt nxGameLogic_update(nxGameLogic* obj);
void nxGameLogic_shutdown(nxGameLogic* obj);

nxInt nxGameLogic_addEntity(nxGameLogic* obj);

void nxGameLogic_handleEvent(nxEvent event);

#endif
