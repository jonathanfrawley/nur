#include "nxGameLogic.h"

#include <chipmunk.h> //XXX:prob shouldn't be here

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

	if(nxGameLogic_addPlatformEntity(obj,
               300.0f,
               100.0f,
               NX_SCREEN_WIDTH-600.0f,
               0.0f ))
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
    nxEntity* entity = &(obj->entities[id]);
	entity->type = NX_ENT_PLAYER;
	entity->id = id;
	entity->valid = 1;
	entity->reversed = 0;
	entity->pos.x = (NX_SCREEN_WIDTH / 2);
	entity->pos.y = (NX_SCREEN_HEIGHT / 2);
	entity->rot = 0.0f;
	entity->hasDoubleJumped = 0;
	nxPhysics_addEntity(obj->physics, &(obj->entities[id]));

	nxCreateEntityEventData createEvData = { obj->entities[id], 1 };
	nxEvent createEv = {NX_EVT_CREATEENT, &createEvData};
	//Fire event
	nxEventManager_triggerEvent(createEv);

	return 0;
}

nxInt nxGameLogic_addPlatformEntity(nxGameLogic* obj, 
        nxFloat x, 
        nxFloat y, 
        nxFloat w,
        nxFloat h)
{
	nxUInt id = obj->currentEntityId++;
    nxEntity* entity = &(obj->entities[id]);
	entity->type = NX_ENT_PLATFORM;
	entity->id = id;
	entity->valid = 1;
	entity->pos.x = x;
	entity->pos.y = y;
	entity->width = w;
	entity->height = h;
	entity->rot = 0.0f;

	nxPhysics_addEntity(obj->physics, entity);

	nxCreateEntityEventData createEvData = { obj->entities[id], 0 };
	nxEvent createEv = {NX_EVT_CREATEENT, &createEvData};
	nxEventManager_triggerEvent(createEv);

	return 0;
}

nxInt nxGameLogic_addBulletEntity(nxGameLogic* obj, 
        nxVector2 pos, 
        nxVector2 vel)
{
	nxUInt id = obj->currentEntityId++;
    nxEntity* entity = &(obj->entities[id]);
	entity->type = NX_ENT_BULLET;
	entity->id = id;
	entity->valid = 1;
	entity->pos.x = pos.x;
	entity->pos.y = pos.y;
	entity->width = NX_BULLET_HALFWIDTH * 2;
	entity->height = NX_BULLET_HALFHEIGHT * 2;
	entity->rot = 0.0f;

	nxPhysics_addEntity(obj->physics, entity);
	nxPhysics_applyImpulseToEntity(obj->physics, entity->id, &vel);

	nxCreateEntityEventData createEvData = { obj->entities[id], 0 };
	nxEvent createEv = { NX_EVT_CREATEENT, &createEvData };
	nxEventManager_triggerEvent( createEv );

	return 0;
}

void nxGameLogic_handleEvent(nxEvent evt, void* vobj)
{
	nxGameLogic* obj = (nxGameLogic*)vobj;

	//TODO : #define these somewhere
	nxFloat xSpeed = 150.0f;
	nxFloat ySpeed = 500.0f;
	nxFloat yDoubleJumpDelta = 100.0f;
	nxFloat bulletSpeed = 1.0f;

	if(evt.type == NX_EVT_ENDGAME)
	{
		finished = 1;
	}
    else if(evt.type == NX_EVT_FIRE)
    {
//        nxUInt entityId = *((nxUInt*)evt.data);
        nxFireEventData* evtData = (nxFireEventData*)evt.data;
        nxUInt entityId = evtData->entityId;
        nxVector2 vel = { 1.0f, 0.0f };
        if(obj->entities[entityId].reversed)
        {
            vel.x = -1.0f;
        }
        nxInt res = nxGameLogic_addBulletEntity(obj,
                obj->entities[entityId].pos, 
                vel);
        NX_ASSERT((res==0) && "Can't add bullet entity.");
    }
	else if(evt.type == NX_EVT_STARTMOVEUP)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        nxVector2 vel = { currentVel.x, ySpeed };
        if(currentVel.y > (0.0f + NX_FLOAT_DELTA) || 
            currentVel.y < (0.0f - NX_FLOAT_DELTA) )
        {
            if( ! obj->entities[obj->playerId].hasDoubleJumped)
            {
                vel.y += yDoubleJumpDelta;
                //Doing a double jump
                nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
                obj->entities[obj->playerId].hasDoubleJumped = 1;
            }
        }
        else
        {
            nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);
            obj->entities[obj->playerId].hasDoubleJumped = 0;
        }
        //obj->currentPlayerVel = vel;
        
        obj->entities[obj->playerId].yKeys = 1.0f;
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

        obj->entities[obj->playerId].xKeys = -1.0f;

        //Reverse if we were still or moving right
        if(currentVel.x >= 0.0f)
        {
            obj->entities[obj->playerId].reversed = 0;
        }

        obj->entities[obj->playerId].moving = 1;
//        obj->currentPlayerVel = vel;
	}
	else if(evt.type == NX_EVT_STARTMOVERIGHT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
        nxVector2 vel = { xSpeed, currentVel.y };
        nxPhysics_setLinearVel(obj->physics, obj->playerId, vel);

        obj->entities[obj->playerId].xKeys = 1.0f;

        if(currentVel.x <= 0.0f)
        {
            obj->entities[obj->playerId].reversed = 1;
        }
//        obj->currentPlayerVel = vel;
        obj->entities[obj->playerId].moving = 1;
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
        obj->entities[obj->playerId].yKeys = 0.0f;
	}
	else if(evt.type == NX_EVT_ENDMOVELEFT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
    //    if(currentVel.x < 0)
        if(obj->entities[obj->playerId].xKeys < 0)
        {
            currentVel.x = 0;
            nxPhysics_setLinearVel(obj->physics, obj->playerId, currentVel);

            obj->entities[obj->playerId].xKeys = 0.0f;
        }

        obj->entities[obj->playerId].moving = 0;
	}
	else if(evt.type == NX_EVT_ENDMOVERIGHT)
	{
        nxVector2 currentVel;
        nxPhysics_getLinearVel(obj->physics, obj->playerId, &currentVel);
//        if(currentVel.x > 0)
        if(obj->entities[obj->playerId].xKeys > 0)
        {
            currentVel.x = 0;
            nxPhysics_setLinearVel(obj->physics, obj->playerId, currentVel);

            obj->entities[obj->playerId].xKeys = 0.0f;
        }

        obj->entities[obj->playerId].moving = 0;
	}
}

void nxGameLogic_updateEntityState(nxGameLogic* obj, nxUInt entityId, nxVector2 pos, nxFloat rot)
{
   obj->entities[entityId].pos.x = pos.x; 
   obj->entities[entityId].pos.y = pos.y; 
   obj->entities[entityId].rot = rot; 
}
