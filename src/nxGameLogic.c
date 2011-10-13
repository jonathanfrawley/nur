#include "nxGameLogic.h"

#include <chipmunk.h> //XXX:prob shouldn't be here
#include <nxCore/nxConstants.h> //XXX:prob shouldn't be here

static int finished = 0;

nxGameLogic* nxGameLogic_new()
{
	nxGameLogic* res = (nxGameLogic*)nxMalloc(sizeof(nxGameLogic));

	int i = 0;
	for(i=0;i<NX_MAX_ENTITIES;i++)
	{
		res->entities[i].valid = 0;
	}

	res->currentEntityId = 0;

	res->physics = nxPhysics_new(res);

	nxEventManager_addHandler(nxGameLogic_handleEvent, (void*)res);

	return res;
}

void nxGameLogic_shutdown(nxGameLogic* obj)
{
	nxPhysics_shutdown(obj->physics);
	nxFree(obj);
}

nxInt nxGameLogic_init(nxGameLogic* obj)
{
	nxPhysics_init(obj->physics); //Important to do this first.

	if(nxGameLogic_addPlayerEntity(obj))
	{
		return 1;
	}

    /*
	if(nxGameLogic_addBallEntity(obj))
	{
		return 1;
	}
    */

	return 0;
}

nxInt nxGameLogic_update(nxGameLogic* obj)
{
	float timestep = 0.02f;

	nxPhysics_update(obj->physics, timestep);

    /*
	//XXX:Do Test physics
    cpVect pos = cpBodyGetPos(obj->physics->ballBody);
    nxFloat rot = cpBodyGetAngle(obj->physics->ballBody);
	obj->entities[1].pos.x = pos.x;
	obj->entities[1].pos.y = NX_SCREEN_HEIGHT - pos.y; //TODO:Put into translation func
	obj->entities[1].rot = rot; //TODO:Put into translation func
	printf("rot is : %f", rot); 
	//XXX:End Test physics
    */

	if(finished)
	{
		return 1;
	}
	for(int i = 0 ; i < NX_MAX_ENTITIES ; i++)
	{
		if(! obj->entities[i].valid)
		{
			continue;
		}
		else
		{
			//Do physics
	//		obj->entities[i].pos.x += (obj->entities[i].accel.x * timestep);
	//		obj->entities[i].pos.y += (obj->entities[i].accel.y * timestep);
			//End physics

			//TODO:Only update info if something has changed.
			nxUpdateEntityEventData evtData = { obj->entities[i] };

			nxEvent evt = {NX_EVT_UPDATEENT, (void*)&evtData};

			//Fire event
			nxEventManager_triggerEvent(evt);
		}
	}

	return 0;
}

nxInt nxGameLogic_addPlayerEntity(nxGameLogic* obj)
{
	nxUInt id = obj->currentEntityId++;
	obj->playerId = id;
	obj->entities[id].type = NX_ENT_PLAYER;
	obj->entities[id].id = id;
	obj->entities[id].valid = 1;
	obj->entities[id].pos.x = (NX_SCREEN_WIDTH / 2);
	obj->entities[id].pos.y = (NX_SCREEN_HEIGHT / 2);
//	obj->entities[id].accel.x = 0.0f;
//	obj->entities[id].accel.y = -1.0f;
	obj->entities[id].rot = 0.0f;
    nxPhysics_addEntity(obj->physics, &(obj->entities[id]));
//	obj->entities[id].accel.x = 0.0f;
//	obj->entities[id].accel.y = 0.0f;

	nxCreateEntityEventData createEvData = { obj->entities[id], 1 };

	nxEvent createEv = {NX_EVT_CREATEENT, &createEvData};

	//Fire event
	nxEventManager_triggerEvent(createEv);

	return 0;
}

nxInt nxGameLogic_addBallEntity(nxGameLogic* obj)
{
	nxUInt id = obj->currentEntityId++;
	obj->entities[id].type = NX_ENT_BALL;
	obj->entities[id].id = id;
	obj->entities[id].valid = 1;
	obj->entities[id].pos.x = (NX_SCREEN_WIDTH / 2);
	obj->entities[id].pos.y = (NX_SCREEN_HEIGHT / 2);
//	obj->entities[id].accel.x = 0.0f;
//	obj->entities[id].accel.y = -1.0f;
	obj->entities[id].rot = 0.0f;

	nxCreateEntityEventData createEvData = { obj->entities[id], 0 };

	nxEvent createEv = {NX_EVT_CREATEENT, &createEvData};

	//Fire event
	nxEventManager_triggerEvent(createEv);

	return 0;
}

void nxGameLogic_handleEvent(nxEvent evt, void* vobj)
{
	nxGameLogic* obj = (nxGameLogic*)vobj;

	//TODO : #define these somewhere
	nxFloat ySpeed = 150.0f;
	nxFloat xSpeed = 150.0f;

	if(evt.type == NX_EVT_ENDGAME)
	{
		finished = 1;
	}
	else if(evt.type == NX_EVT_STARTMOVEUP)
	{
        nxVector2 vel = { 0.0f, -ySpeed };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
//		obj->entities[obj->playerId].accel.y = - ySpeed;
//		obj->entities[obj->playerId].accel.y = - ySpeed;
	}
	else if(evt.type == NX_EVT_STARTMOVEDOWN)
	{
        nxVector2 vel = { 0.0f, ySpeed };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
//		obj->entities[obj->playerId].accel.y = ySpeed;
	}
	else if(evt.type == NX_EVT_STARTMOVELEFT)
	{
        nxVector2 vel = { -xSpeed, 0 };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
//		obj->entities[obj->playerId].accel.x = - xSpeed;
	}
	else if(evt.type == NX_EVT_STARTMOVERIGHT)
	{
        nxVector2 vel = { xSpeed, 0 };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
//		obj->entities[obj->playerId].accel.x = xSpeed;
	}
	else if(evt.type == NX_EVT_ENDMOVEUP)
	{
//		obj->entities[obj->playerId].accel.y = 0.0f;
	}
	else if(evt.type == NX_EVT_ENDMOVEDOWN)
	{
//		obj->entities[obj->playerId].accel.y = 0.0f;
	}
	else if(evt.type == NX_EVT_ENDMOVELEFT)
	{
//		obj->entities[obj->playerId].accel.x = 0.0f;
	}
	else if(evt.type == NX_EVT_ENDMOVERIGHT)
	{
//		obj->entities[obj->playerId].accel.x = 0.0f;
	}
}

void nxGameLogic_updateEntityState(nxGameLogic* obj, nxUInt entityId, nxVector2 pos, nxFloat rot)
{
   obj->entities[entityId].pos.x = pos.x; 
   obj->entities[entityId].pos.y = pos.y; 
   obj->entities[entityId].rot = rot; 
}
