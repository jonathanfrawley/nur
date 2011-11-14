#include "nxPhysics.h"

#include <stdio.h>

nxPhysics* nxPhysics_new(nxGameLogic* gameLogic)
{
	nxPhysics* res = (nxPhysics*) nxMalloc(sizeof(nxPhysics));

    res->_gameLogic = gameLogic;
    res->_nextEntityId = 0;
    res->_currentPlatformId = 0;

    for(int i=0;i<NX_MAX_ENTITIES;i++)
    {
        res->_physicsEntities[i].valid = 0;
    }

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
	//cpVect gravity = cpv(0, -400.0f);
	cpVect gravity = cpv(0, -NX_GRAVITY * 100.0f);
	obj->_space = cpSpaceNew();
    cpSpaceSetIterations(obj->_space, 20);
	cpSpaceSetGravity(obj->_space, gravity);
    obj->_space->enableContactGraph = cpTrue;

    cpShape* shape;

	//Ground init
	shape = cpSegmentShapeNew(obj->_space->staticBody, cpv(0, 0), cpv(NX_SCREEN_WIDTH, 0), 0);
	cpSpaceAddShape(obj->_space, shape);
    shape->e = 1.0f; shape->u = 0.0f;
    obj->_ground = shape;

	//Left wall init
	shape = cpSegmentShapeNew(obj->_space->staticBody, cpv(0, 0), cpv(0, NX_SCREEN_HEIGHT), 0);
	cpSpaceAddShape(obj->_space, shape);
    shape->e = 1.0f; shape->u = 1.0f;
    obj->_leftWall = shape;

	//Right wall init
	shape = cpSegmentShapeNew(obj->_space->staticBody, cpv(NX_SCREEN_WIDTH, 0), cpv(NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT), 0);
	cpSpaceAddShape(obj->_space, shape);
    shape->e = 1.0f; shape->u = 1.0f;
    obj->_rightWall = shape;

    /*
	// Add our one way segment
	shape = cpSpaceAddShape(obj->_space, cpSegmentShapeNew(obj->_space->staticBody, cpv(300,100), cpv(NX_SCREEN_WIDTH-300,100), 10.0f));
	cpShapeSetElasticity(shape, 1.0f);
	cpShapeSetFriction(shape, 0.0f);
	cpShapeSetCollisionType(shape, NX_PLATFORM_COLLISION_TYPE);
	
	obj->_oneWayPlatforms[0].valid = 1;
	obj->_oneWayPlatforms[0].n = cpv(0, 1); // let objects pass upwards
	cpShapeSetUserData(shape, &obj->_oneWayPlatforms[0]);

    cpSpaceAddCollisionHandler(obj->_space, NX_PLATFORM_COLLISION_TYPE, NX_PLAYER_COLLISION_TYPE, 
            NULL, platformPreSolve, NULL, NULL, NULL);
            */

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
            //nxGameLogic_updateEntityState(obj->_gameLogic, obj->_physicsEntities[i].entityId, vpos, rot);
            nxPhysicsUpdateEntityEventData evtData = { obj->_physicsEntities[i].entityId, vpos, rot };
			nxEvent evt = {NX_EVT_PHYSICSUPDATEENT, (void*)&evtData};
            nxEventManager_triggerEvent(evt);
        }
    }

    cpSpaceStep(obj->_space, timestep);
}

void nxPhysics_addEntity(nxPhysics* obj, nxEntity* entity)
{
    switch(entity->type)
    {
        case NX_ENT_PLAYER: 
            {
            nxUInt id = obj->_nextEntityId++;
            obj->_physicsEntities[id].entityId = entity->id;
            obj->_physicsEntities[id].valid = 1;

            cpFloat moment = cpMomentForBox(NX_PLAYER_MASS, NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT);
            // The cpSpaceAdd*() functions return the thing that you are adding.
            // It's convenient to create and add an object in one line.
    //        cpBody* body = cpSpaceAddBody(obj->_space, cpBodyNew(NX_PLAYER_MASS, moment));
            cpBody* body = cpSpaceAddBody(obj->_space, cpBodyNew(NX_PLAYER_MASS, NX_INFINITY));
            cpBodySetPos(body, cpv(NX_SCREEN_WIDTH/2, NX_SCREEN_HEIGHT/2));
            //cpBodySetAngle(body, 0.0f);
            //cpBodySetTorque(body, 0.0f);
            body->velocity_func = playerUpdateVelocity;

            // Now we create the collision shape for the ball.
            // You can create multiple collision shapes that point to the same body.
            // They will all be attached to the body and move around to follow it.
            cpShape* shape = cpSpaceAddShape(obj->_space, cpBoxShapeNew(body, NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT));
            cpShapeSetCollisionType(shape, NX_PLAYER_COLLISION_TYPE);
            cpShapeSetFriction(shape, 0.7f);

            obj->_physicsEntities[id].shape = shape;
            obj->_physicsEntities[id].body = body;
            obj->_physicsEntities[id].entity = entity;

            //Back pointer to nxPhysicsEntity struct, to be used in vel func
            cpBodySetUserData(body, (const cpDataPointer)&(obj->_physicsEntities[id]));

            break;
            }
        case NX_ENT_PLATFORM:
            {
            nxUInt platformId = obj->_currentPlatformId++;
            // Add our one way segment
            cpShape* shape = cpSpaceAddShape(obj->_space, 
                    cpSegmentShapeNew(obj->_space->staticBody, cpv(entity->pos.x,entity->pos.y), cpv(entity->pos.x+entity->width, entity->pos.y+entity->height), 10.0f));
            cpShapeSetElasticity(shape, 1.0f);
            cpShapeSetFriction(shape, 0.0f);
            cpShapeSetCollisionType(shape, NX_PLATFORM_COLLISION_TYPE);

            obj->_oneWayPlatforms[platformId].valid = 1;
            obj->_oneWayPlatforms[platformId].n = cpv(0, 1); // let objects pass upwards
            cpShapeSetUserData(shape, &obj->_oneWayPlatforms[platformId]);

            cpSpaceAddCollisionHandler(obj->_space, NX_PLATFORM_COLLISION_TYPE, NX_PLAYER_COLLISION_TYPE, 
                    NULL, platformPreSolve, NULL, NULL, NULL);

            obj->_nextEntityId++; //Add it as an entity even though it isn't used, this is so there is a 1-1 mapping between physicsEntities and entities.
            break;
            }
        case NX_ENT_BULLET:
            {
            nxUInt id = obj->_nextEntityId++;
            obj->_physicsEntities[id].entityId = entity->id;
            obj->_physicsEntities[id].valid = 1;

            cpFloat moment = cpMomentForBox(NX_BULLET_MASS, entity->width * 0.5f, entity->height*0.5f);
            // The cpSpaceAdd*() functions return the thing that you are adding.
            // It's convenient to create and add an object in one line.
    //        cpBody* body = cpSpaceAddBody(obj->_space, cpBodyNew(NX_PLAYER_MASS, moment));
            cpBody* body = cpSpaceAddBody(obj->_space, cpBodyNew(NX_BULLET_MASS, moment));
//            cpBody* body = cpSpaceAddBody(obj->_space, cpBodyNew(NX_BULLET_MASS, NX_GRAVITY));
            cpBodySetPos(body, cpv(entity->pos.x, entity->pos.y));

            // Now we create the collision shape for the ball.
            // You can create multiple collision shapes that point to the same body.
            // They will all be attached to the body and move around to follow it.
            cpShape* shape = cpSpaceAddShape(obj->_space, cpBoxShapeNew(body, entity->width * 0.5f, entity->width * 0.5f));
            cpShapeSetCollisionType(shape, NX_BULLET_COLLISION_TYPE);
            //cpShapeSetFriction(shape, 0.1f);

            obj->_physicsEntities[id].shape = shape;
            obj->_physicsEntities[id].body = body;
            obj->_physicsEntities[id].entity = entity;

            cpSpaceAddCollisionHandler(obj->_space, NX_PLATFORM_COLLISION_TYPE, NX_BULLET_COLLISION_TYPE, 
                    NULL, bulletPreSolve, NULL, NULL, NULL);

            cpSpaceAddCollisionHandler(obj->_space, NX_PLAYER_COLLISION_TYPE, NX_BULLET_COLLISION_TYPE, 
                    NULL, bulletPreSolve, NULL, NULL, NULL);

            cpSpaceAddCollisionHandler(obj->_space, NX_BULLET_COLLISION_TYPE, NX_BULLET_COLLISION_TYPE, 
                    NULL, bulletPreSolve, NULL, NULL, NULL);

            //Back pointer to nxPhysicsEntity struct, to be used in vel func
            cpBodySetUserData(body, (const cpDataPointer)&(obj->_physicsEntities[id]));

            break;
            }
        default:
            {
                NX_ASSERT("Entity type not handled in physics.");
            }
    }
}

void nxPhysics_setLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2 vel)
{
    cpVect velDelta;
    velDelta.x = vel.x;
    velDelta.y = vel.y;
    cpBodySetVel(obj->_physicsEntities[entityId].body, velDelta);
//    cpBodySetForce(obj->_physicsEntities[entityId].body, velDelta); //XXX
}

void nxPhysics_addLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2 vel)
{
    cpVect velDelta;
    velDelta.x = vel.x;
    velDelta.y = vel.y;
    cpVect velBefore = cpBodyGetVel(obj->_physicsEntities[entityId].body);
    cpVect newVel = cpvadd(velDelta,velBefore);
    cpBodySetVel(obj->_physicsEntities[entityId].body, newVel);
}

void nxPhysics_getLinearVel(nxPhysics* obj, nxUInt entityId, nxVector2* res)
{
    cpVect vel = cpBodyGetVel(obj->_physicsEntities[entityId].body);
    nxVector2_fromCpVect(&vel, res);
}


void nxPhysics_applyImpulseToEntity(nxPhysics* obj, nxUInt entityId, const nxVector2* vel)
{
    //Fire the bullet
    cpVect j; //wtf is this!?!?
    cpVect r;
    //nxVector2_toCpVect(vel, &r);
    nxVector2_toCpVect(vel, &j);
    cpBodyApplyImpulse(obj->_physicsEntities[entityId].body, j, r);
}

//--------------------------------------------------------------------------------------------
//Non ADT functions below
//--------------------------------------------------------------------------------------------

static void selectPlayerGroundNormal(cpBody *body, cpArbiter *arb, cpVect *groundNormal)
{
    cpVect n = cpvneg(cpArbiterGetNormal(arb, 0));
        
    if(n.y > groundNormal->y)
    {
        (*groundNormal) = n;
    }   
}

void playerUpdateVelocity(cpBody *body, cpVect gravity, cpFloat damping, cpFloat dt)
{
    static int lastJumpState = 0;
    static int nJumps = 0;
    const int maxNJumps = 2;

	nxFloat remainingBoost;
    nxPhysicsEntity *physicsEntity = (nxPhysicsEntity *)cpBodyGetUserData(body);
    nxEntity *entity = physicsEntity->entity;
	int jumpState = (entity->yKeys > (0.0f + NX_FLOAT_DELTA));

    //
    //	int jumpState = (ChipmunkDemoKeyboard.y > 0.0f);
	//int jumpState = (entity->yKeys > (0.0f + NX_FLOAT_DELTA));
	
	// Grab the grounding normal from last frame
	cpVect groundNormal = cpvzero;
	cpBodyEachArbiter(body, (cpBodyArbiterIteratorFunc)selectPlayerGroundNormal, &groundNormal);

	nxUInt grounded = (groundNormal.y > (0.0f + NX_FLOAT_DELTA));

    //BEGINPRE
    if(grounded)
    {
        nJumps = 0;
    }

    // If the jump key was just pressed this frame, jump!
    //if(jumpState && (!lastJumpState) && grounded)
    if(jumpState && (!lastJumpState) && (nJumps < maxNJumps))
    {
        cpFloat jumpVel = nxMath_sqrt(2.0*NX_JUMP_HEIGHT*NX_GRAVITY);
        body->v = cpvadd(body->v, cpv(0.0f, jumpVel));

        remainingBoost = NX_JUMP_BOOST_HEIGHT/jumpVel;

    //    entity->yKeys = 0.0f; //XXX:Nasty hack
        nJumps++;
        //lastJumpState = jumpState;
    }

    entity->yKeys = 0.0f; //XXX:Nasty hack

	if((!grounded) && (!jumpState))
    {
//        body->v.y = -NX_FALL_SPEED;

//        body->v = cpvadd(body->v, cpv(0.0, -NX_FALL_SPEED));
    }
    //ENDPRE

	if(groundNormal.y < 0.0f) 
    {
        remainingBoost = 0.0f;
    }

    //VERTICAL movement
	// Do a normal-ish update
	cpBool boost = (jumpState && (remainingBoost > 0.0f));
    //printf("boost is %d \n", boost);
    //cpVect jumpVel = {0.0f, NX_PLAYER_JUMP_SPEED};
	//cpVect g = (boost ? cpvzero : jumpVel);

    cpVect g = (boost ? cpvzero : gravity);
	cpBodyUpdateVelocity(body, g, damping, dt);

	//body->v.y = cpfclamp(body->v.y, -NX_FALL_VELOCITY, NX_INFINITY);
	//body->v.y = cpfclamp(body->v.y, -NX_FALL_SPEED, NX_INFINITY);
	body->v.y = cpfclamp(body->v.y, -NX_FALL_SPEED, NX_PLAYER_JUMP_SPEED);
	
    //HORIZONTAL movement
	// Target horizontal speed for air/ground control
	cpFloat target_vx = NX_PLAYER_SPEED*entity->xKeys;
	
	// Update the surface velocity and friction
	cpVect surface_v = cpv(target_vx, 0.0);
	physicsEntity->shape->surface_v = surface_v;
	physicsEntity->shape->u = (grounded ? NX_PLAYER_GROUND_ACCEL/NX_GRAVITY : 0.0);
	
	// Apply air control if not grounded
	if(!grounded)
    {
		// Smoothly accelerate the velocity
		body->v.x = cpflerpconst(body->v.x, target_vx, NX_PLAYER_AIR_ACCEL*dt);

        if(!jumpState)
        {
            //XXX
            //body->v.y = -NX_FALL_VELOCITY;
        }
	}

    lastJumpState = jumpState;
}

cpBool platformPreSolve(cpArbiter *arb, cpSpace *space, void *ignore)
{
    CP_ARBITER_GET_SHAPES(arb, a, b); 
    nxOneWayPlatform *platform = (nxOneWayPlatform *)cpShapeGetUserData(a);
     
    if(cpvdot(cpArbiterGetNormal(arb, 0), platform->n) < 0){ 
        cpArbiterIgnore(arb);
        return cpFalse;
    }   
    
    return cpTrue;
}

cpBool bulletPreSolve(cpArbiter *arb, cpSpace *space, void *ignore)
{
    CP_ARBITER_GET_SHAPES(arb, a, b); 
     
    //TODO : Enemy collisions and stuff.
    cpArbiterIgnore(arb);
    return cpFalse;
}
