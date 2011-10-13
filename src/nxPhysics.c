#include "nxPhysics.h"

#include <stdio.h>
#include <nxGameLogic.h>

nxPhysics* nxPhysics_new(nxGameLogic* gameLogic)
{
	nxPhysics* res = (nxPhysics*) nxMalloc(sizeof(nxPhysics));

    res->_gameLogic = gameLogic;
    res->_nextEntityIdx = 0;

	return res;
}

void nxPhysics_shutdown(nxPhysics* obj)
{
    for(int i=0;i<NX_MAX_ENTITIES;i++)
    {
        if(obj->_physicsEntities[i].valid)
        {
            cpShapeFree(obj->_physicsEntities[i].shape);
            cpBodyFree(obj->_physicsEntities[i].body);
        }
    }
	cpShapeFree(obj->_ground);
	cpSpaceFree(obj->_space);
	nxFree(obj);
}

nxInt nxPhysics_init(nxPhysics* obj)
{
	//Space init
	cpVect gravity = cpv(0, -0.2);
	obj->_space = cpSpaceNew();
	cpSpaceSetGravity(obj->_space, gravity);

	//Ground init
	obj->_ground = cpSegmentShapeNew(obj->_space->staticBody, cpv(0, 0), cpv(NX_SCREEN_WIDTH, 0), 0);
	cpShapeSetFriction(obj->_ground, 0.1);
	cpSpaceAddShape(obj->_space, obj->_ground);

    /*
	//Create ball
	cpFloat radius = NX_BALL_HALFWIDTH;
	cpFloat mass = 0.1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	obj->ballBody = cpSpaceAddBody(obj->_space, cpBodyNew(mass, moment));
	cpBodySetPos(obj->ballBody, cpv(NX_SCREEN_WIDTH/2, NX_SCREEN_HEIGHT/2));
	cpBodySetAngle(obj->ballBody, 0.2f);
	cpBodySetTorque(obj->ballBody, 0.2f);

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	obj->ballShape = cpSpaceAddShape(obj->_space, cpCircleShapeNew(obj->ballBody, radius, cpvzero));
	cpShapeSetFriction(obj->ballShape, 0.7);
    */

    for(int i = 0 ; i < NX_MAX_ENTITIES ; i++)
    {
        obj->_physicsEntities[i].valid = 0;
    }

	return 0;
}

void nxPhysics_update(nxPhysics* obj, nxFloat timestep)
{
    /*
    cpVect pos = cpBodyGetPos(obj->ballBody);
    cpVect vel = cpBodyGetVel(obj->ballBody);
    printf(
      "ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
      pos.x, pos.y, vel.x, vel.y
    );
	//TODO: update event fired here?

    cpSpaceStep(obj->_space, timestep);
  */

    for(int i = 0 ; i < NX_MAX_ENTITIES ; i++)
    {
        if(obj->_physicsEntities[i].valid)
        {
            cpVect pos = cpBodyGetPos(obj->_physicsEntities[i].body);
            nxFloat rot = cpBodyGetAngle(obj->_physicsEntities[i].body);
//            cpVect vel = cpBodyGetVel(obj->_physicsEntities[i]);
            //Update entity
            nxVector2 vpos = {pos.x, pos.y};
            nxGameLogic_updateEntityState(obj->_gameLogic, obj->_physicsEntities[i].entityId, vpos, rot);
        }
    }

    cpSpaceStep(obj->_space, timestep);
}

void nxPhysics_addEntity(nxPhysics* obj, nxEntity* entity)
{
    int idx = obj->_nextEntityIdx;
    obj->_physicsEntities[idx].entityId = idx;
    switch(entity->type)
    {
        case NX_ENT_PLAYER: 
            {
            cpFloat moment = cpMomentForBox(NX_PLAYER_MASS, NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT);
            // The cpSpaceAdd*() functions return the thing that you are adding.
            // It's convenient to create and add an object in one line.
            cpBody* body = cpSpaceAddBody(obj->_space, cpBodyNew(NX_PLAYER_MASS, moment));
            cpBodySetPos(body, cpv(NX_SCREEN_WIDTH/2, NX_SCREEN_HEIGHT/2));
            cpBodySetAngle(body, 0.0f);
            cpBodySetTorque(body, 0.0f);

            // Now we create the collision shape for the ball.
            // You can create multiple collision shapes that point to the same body.
            // They will all be attached to the body and move around to follow it.
            cpShape* shape = cpSpaceAddShape(obj->_space, cpBoxShapeNew(body, NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT));
            cpShapeSetFriction(shape, 0.7f);
            obj->_physicsEntities[idx].shape = shape;
            obj->_physicsEntities[idx].body = body;
            break;
            }
    }

    obj->_physicsEntities[idx].valid = 1;
    obj->_nextEntityIdx++;
}

void nxPhysics_setLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2 vel)
{
    cpVect cpvel;
    cpvel.x = vel.x;
    cpvel.y = vel.y;
    cpBodySetVel(obj->_physicsEntities[entityId].body, cpvel);
}
