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
	float timestep = 1.0f/60.0f;
    /*
    if(obj->playerHadMoved)
    {
        nxPhysics_setLinearVel(obj->physics, obj->playerId, obj->currentPlayerVel); //
    }
    */

	nxPhysics_update(obj->physics, timestep);

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
	obj->entities[id].rot = 0.0f;
    nxPhysics_addEntity(obj->physics, &(obj->entities[id]));

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
	nxFloat ySpeed = 300.0f;
	nxFloat xSpeed = 150.0f;

	if(evt.type == NX_EVT_ENDGAME)
	{
		finished = 1;
	}
	else if(evt.type == NX_EVT_STARTMOVEUP)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        nxVector2 vel = { currentVel.x, ySpeed };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
        //obj->currentPlayerVel = vel;
	}
	else if(evt.type == NX_EVT_STARTMOVEDOWN)
	{
        /*
        nxVector2 vel = { 0.0f, -ySpeed };
        nxPhysics_addLinearVel(obj->physics, obj->playerId, vel);
        */
	}
	else if(evt.type == NX_EVT_STARTMOVELEFT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        nxVector2 vel = { -xSpeed, currentVel.y };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
//        obj->currentPlayerVel = vel;
	}
	else if(evt.type == NX_EVT_STARTMOVERIGHT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        nxVector2 vel = { xSpeed, currentVel.y };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
//        obj->currentPlayerVel = vel;
	}
	else if(evt.type == NX_EVT_ENDMOVEUP)
	{
        //nxVector2 currentVel;
        //nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        //currentVel.y = 0;
        //nxPhysics_setLinearVel(obj->physics, obj->playerId, currentVel);
	}
	else if(evt.type == NX_EVT_ENDMOVEDOWN)
	{
	}
	else if(evt.type == NX_EVT_ENDMOVELEFT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        if(currentVel.x < 0)
        {
            currentVel.x = 0;
            nxPhysics_setLinearVel(obj->physics, obj->playerId, currentVel);
        }
	}
	else if(evt.type == NX_EVT_ENDMOVERIGHT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        if(currentVel.x > 0)
        {
            currentVel.x = 0;
            nxPhysics_setLinearVel(obj->physics, obj->playerId, currentVel);
        }
	}
}

void nxGameLogic_updateEntityState(nxGameLogic* obj, nxUInt entityId, nxVector2 pos, nxFloat rot)
{
   obj->entities[entityId].pos.x = pos.x; 
   obj->entities[entityId].pos.y = pos.y; 
   obj->entities[entityId].rot = rot; 
}
