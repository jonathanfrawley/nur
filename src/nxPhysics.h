#ifndef  NXPHYSICS_H
#define  NXPHYSICS_H

#include <chipmunk.h>

#include <nxAlgebra/nxVector2.h>
#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
#include <nxCore/nxMM.h>

#define NX_INFINITY __builtin_inf()

#define NX_PLAYER_MASS 1.0f
#define NX_BULLET_MASS 1.0f

#define NX_GRAVITY 2000.0f

#define NX_PLATFORM_COLLISION_TYPE 1
#define NX_PLAYER_COLLISION_TYPE 2
#define NX_BULLET_COLLISION_TYPE 3

//#define NX_PLAYER_MASS NX_INFINITY
#define NX_JUMP_HEIGHT 2050.0
#define NX_JUMP_BOOST_HEIGHT 155.0
#define NX_FALL_VELOCITY 300.0

#define NX_PLAYER_VELOCITY 200.0

#define NX_PLAYER_GROUND_ACCEL_TIME 0.2
#define NX_PLAYER_GROUND_ACCEL (NX_PLAYER_VELOCITY/NX_PLAYER_GROUND_ACCEL_TIME)

#define NX_PLAYER_AIR_ACCEL_TIME 0.25
#define NX_PLAYER_AIR_ACCEL (NX_PLAYER_VELOCITY/NX_PLAYER_AIR_ACCEL_TIME)

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
    nxEntity* entity;
} nxPhysicsEntity;

typedef struct nxOneWayPlatform 
{
    cpVect n; // direction objects may pass through
    nxUInt valid;
} nxOneWayPlatform;

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
	cpShape* _leftWall;
	cpShape* _rightWall;

    nxUInt _nextEntityId;
    nxUInt _currentPlatformId;

    nxPhysicsEntity _physicsEntities[NX_MAX_ENTITIES];
    nxOneWayPlatform _oneWayPlatforms[NX_MAX_ONEWAYPLATFORMS];
} nxPhysics;

nxPhysics* nxPhysics_new(nxGameLogic* gameLogic);
void nxPhysics_shutdown(nxPhysics* obj);
nxInt nxPhysics_init(nxPhysics* obj);
void nxPhysics_update(nxPhysics* obj, nxFloat timestep);
void nxPhysics_addEntity(nxPhysics* obj, nxEntity* entity);
void nxPhysics_setLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2 vel);
void nxPhysics_addLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2 vel);
void nxPhysics_getLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2* res);
void nxPhysics_applyImpulseToEntity(nxPhysics* obj, nxUInt entityId, const nxVector2* vel);

void playerUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt);
cpBool platformPreSolve(cpArbiter *arb, cpSpace *space, void *ignore);
cpBool bulletPreSolve(cpArbiter *arb, cpSpace *space, void *ignore);

#endif   // NXPHYSICS_H
