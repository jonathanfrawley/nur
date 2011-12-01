#ifndef NXGAMELOGIC_H
#define NXGAMELOGIC_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxLogic/nxEntity.h>
#include <nxEvent/nxEvent.h>
#include <nxEvent/nxEventData.h>
#include <nxEvent/nxEventManager.h>
#include <nxLogic/nxPhysics.h>

#define NX_DOUBLETAP_TIME 1000

typedef struct nxGameLogic
{
	nxEntity entities[NX_MAX_ENTITIES];
	nxInt currentEntityId;
	nxInt playerId;
	nxPhysics* physics;
} nxGameLogic;

nxGameLogic* nxGameLogic_alloc();
void nxGameLogic_shutdown(nxGameLogic* obj);
nxInt nxGameLogic_init0(nxGameLogic* obj);
nxInt nxGameLogic_aiUpdate(nxGameLogic* obj, nxUInt timestep);
nxInt nxGameLogic_update(nxGameLogic* obj, nxUInt timestep);
nxInt nxGameLogic_addPlayerEntity(nxGameLogic* obj);
nxInt nxGameLogic_addPlatformEntity(nxGameLogic* obj, 
        nxFloat x, 
        nxFloat y, 
        nxFloat w,
        nxFloat h);
nxInt nxGameLogic_addEnemyEntity(nxGameLogic* obj, 
        nxUInt type,
        nxFloat x,
        nxFloat y, 
        nxFloat w,
        nxFloat h);
nxInt nxGameLogic_addBulletEntity(nxGameLogic* obj, 
        nxVector2 pos, 
        nxVector2 vel);
void nxGameLogic_handleEvent(nxEvent evt, void* vobj);
//Utils
void nxGameLogic_updateEntityState(nxGameLogic* obj, nxUInt entityId, nxVector2 pos, nxFloat rot);
nxEntity* nxGameLogic_getEntity(nxGameLogic* obj, nxUInt entityId);

#endif
