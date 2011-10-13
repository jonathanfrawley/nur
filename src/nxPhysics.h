#ifndef  NXPHYSICS_H
#define  NXPHYSICS_H

#include <chipmunk.h>

#include <nxAlgebra/nxVector2.h>
#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
#include <nxCore/nxMM.h>

#define NX_PLAYER_MASS 1.0f

typedef struct nxGameLogic nxGameLogic;
typedef struct nxEntity nxEntity;

/**
 * Physical attributes of an entity.
 **/
typedef struct nxPhysicsEntity
{
    nxUInt entityId;
    nxUInt valid;
	cpShape* shape;
	cpBody* body;
} nxPhysicsEntity;

/**
 * Encapsulates the physics for the game.
 **/
typedef struct nxPhysics
{
    /*
	cpShape* ballShape;
	cpBody* ballBody;
    */
    nxGameLogic* _gameLogic;
	cpSpace* _space;
	cpShape* _ground;
    nxPhysicsEntity _physicsEntities[NX_MAX_ENTITIES];
    nxUInt _nextEntityIdx;
} nxPhysics;

nxPhysics* nxPhysics_new(nxGameLogic* gameLogic);
void nxPhysics_shutdown(nxPhysics* obj);
nxInt nxPhysics_init(nxPhysics* obj);
void nxPhysics_update(nxPhysics* obj, nxFloat timestep);
void nxPhysics_addEntity(nxPhysics* obj, nxEntity* entity);
void nxPhysics_setLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2 vel);

#endif   // NXPHYSICS_H
