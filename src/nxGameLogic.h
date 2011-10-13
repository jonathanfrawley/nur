#ifndef NXGAMELOGIC_H
#define NXGAMELOGIC_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxEntity.h>
#include <nxEvent/nxEvent.h>
#include <nxEvent/nxEventData.h>
#include <nxEvent/nxEventManager.h>
#include <nxPhysics.h>

typedef struct nxGameLogic
{
	nxEntity entities[NX_MAX_ENTITIES];
	nxInt currentEntityId;
	nxInt playerId;
	nxPhysics* physics;
} nxGameLogic;

nxGameLogic* nxGameLogic_new();
void nxGameLogic_shutdown(nxGameLogic* obj);
nxInt nxGameLogic_init(nxGameLogic* obj);
nxInt nxGameLogic_update(nxGameLogic* obj);

nxInt nxGameLogic_addPlayerEntity(nxGameLogic* obj);
nxInt nxGameLogic_addBallEntity(nxGameLogic* obj);

void nxGameLogic_handleEvent(nxEvent evt, void* vobj);

void nxGameLogic_updateEntityState(nxGameLogic* obj, nxUInt entityId, nxVector2 pos, nxFloat rot);

#endif
