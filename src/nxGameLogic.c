#include "nxGameLogic.h"

#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxEvent/nxEvent.h>
#include <nxEvent/nxEventData.h>
#include <nxEvent/nxEventManager.h>

static int finished = 0;

nxGameLogic* nxGameLogic_new()
{
	nxGameLogic* res = (nxGameLogic*)nxMalloc(sizeof(nxGameLogic));

	int i = 0;
	for(i=0;i<NX_MAX_ENTITIES;i++)
	{
		res->entities[i].id = -1;
	}

	res->currentEntityId = 0;

	nxEventManager_addHandler(nxGameLogic_handleEvent);

	return res;
}

nxInt nxGameLogic_init(nxGameLogic* obj)
{
	if(nxGameLogic_addPlayerEntity(obj))
	{
		return 1;
	}

	NX_LOG("nxGameLogic", "added entity correctly");
	return 0;
}

nxInt nxGameLogic_update(nxGameLogic* obj)
{
	if(finished)
	{
		return 1;
	}
	for(int i = 0 ; i < NX_MAX_ENTITIES ; i++)
	{
		if(obj->entities[i].id = -1)
		{
			continue;
		}
		else
		{
			//TODO:Only update info if something has changed.
			nxUpdateEntityEventData* evtData = (nxUpdateEntityEventData*)nxMalloc(sizeof(nxUpdateEntityEventData));
			evtData->entity = obj->entities[i];

			nxEvent evt = {NX_EVT_UPDATEENT, (void*)evtData};

			//Fire event
			nxEventManager_queueEvent(evt);
		}
	}

	return 0;
}

void nxGameLogic_shutdown(nxGameLogic* obj)
{
	nxFree(obj);
}

nxInt nxGameLogic_addNonPlayerEntity(nxGameLogic* obj)
{
	nxUInt id = obj->currentEntityId++;
	obj->entities[id].id = id;
	obj->entities[id].pos.x = 10.0f;
	obj->entities[id].pos.y = 0.0f;

	nxCreateEntityEventData* createEvData = (nxCreateEntityEventData*)nxMalloc(sizeof(nxCreateEntityEventData));
	createEvData->entity = obj->entities[id];
	createEvData->isPlayer = 0;

	nxEvent createEv = {NX_EVT_CREATEENT, (void*)createEvData};

	//Fire event
	nxEventManager_queueEvent(createEv);

	return 0;
}

nxInt nxGameLogic_addPlayerEntity(nxGameLogic* obj)
{
	nxUInt id = obj->currentEntityId++;
	obj->entities[id].id = id;
	obj->entities[id].pos.x = 10.0f;
	obj->entities[id].pos.y = 0.0f;

	nxCreateEntityEventData* createEvData = (nxCreateEntityEventData*)nxMalloc(sizeof(nxCreateEntityEventData));
	createEvData->entity = obj->entities[id];
	createEvData->isPlayer = 1;

	nxEvent createEv = {NX_EVT_CREATEENT, (void*)createEvData};

	//Fire event
	nxEventManager_queueEvent(createEv);

	return 0;
}

void nxGameLogic_handleEvent(nxEvent evt)
{
	if(evt.type == NX_EVT_ENDGAME)
	{
		finished = 1;
	}
	else if(evt.type == NX_EVT_STARTMOVEUP)
	{
	}
	else if(evt.type == NX_EVT_STARTMOVEDOWN)
	{
	}
	else if(evt.type == NX_EVT_STARTMOVELEFT)
	{
	}
	else if(evt.type == NX_EVT_STARTMOVERIGHT)
	{
	}
	else if(evt.type == NX_EVT_ENDMOVEUP)
	{
	}
	else if(evt.type == NX_EVT_ENDMOVEDOWN)
	{
	}
	else if(evt.type == NX_EVT_ENDMOVELEFT)
	{
	}
	else if(evt.type == NX_EVT_ENDMOVERIGHT)
	{
	}
}
