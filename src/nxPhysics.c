#include "nxPhysics.h"
#include <stdio.h>

nxPhysics* nxPhysics_new()
{
	nxPhysics* res = (nxPhysics*) nxMalloc(sizeof(nxPhysics));

	return res;
}

void nxPhysics_shutdown(nxPhysics* obj)
{
	cpShapeFree(obj->ballShape);
	cpBodyFree(obj->ballBody);
	cpShapeFree(obj->ground);
	cpSpaceFree(obj->space);
	nxFree(obj);
}

nxInt nxPhysics_init(nxPhysics* obj)
{
	//Space init
	cpVect gravity = cpv(0, -0.2);
	obj->space = cpSpaceNew();
	cpSpaceSetGravity(obj->space, gravity);

	//Ground init
	obj->ground = cpSegmentShapeNew(obj->space->staticBody, cpv(0, 0), cpv(NX_SCREEN_WIDTH, 0), 0);
	cpShapeSetFriction(obj->ground, 0.1);
	cpSpaceAddShape(obj->space, obj->ground);

	//Create ball
	cpFloat radius = NX_BALL_HALFWIDTH;
	cpFloat mass = 0.1;

	// The moment of inertia is like mass for rotation
	// Use the cpMomentFor*() functions to help you approximate it.
	cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

	// The cpSpaceAdd*() functions return the thing that you are adding.
	// It's convenient to create and add an object in one line.
	obj->ballBody = cpSpaceAddBody(obj->space, cpBodyNew(mass, moment));
	cpBodySetPos(obj->ballBody, cpv(NX_SCREEN_WIDTH/2, NX_SCREEN_HEIGHT/2));
	cpBodySetAngle(obj->ballBody, 0.2f);
	cpBodySetTorque(obj->ballBody, 0.2f);

	// Now we create the collision shape for the ball.
	// You can create multiple collision shapes that point to the same body.
	// They will all be attached to the body and move around to follow it.
	obj->ballShape = cpSpaceAddShape(obj->space, cpCircleShapeNew(obj->ballBody, radius, cpvzero));
	cpShapeSetFriction(obj->ballShape, 0.7);

	return 0;
}

void nxPhysics_update(nxPhysics* obj, nxFloat timestep)
{
    cpVect pos = cpBodyGetPos(obj->ballBody);
    cpVect vel = cpBodyGetVel(obj->ballBody);
    printf(
      "ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
      pos.x, pos.y, vel.x, vel.y
    );
	//TODO: update event fired here?

    cpSpaceStep(obj->space, timestep);
}
