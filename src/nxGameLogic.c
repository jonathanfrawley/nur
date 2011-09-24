#include "nxGameLogic.h"

#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxEvent/nxEvent.h>
#include <nxEvent/nxEventData.h>
#include <nxEvent/nxEventManager.h>

nxGameLogic* nxGameLogic_new()
{
	nxGameLogic* res = (nxGameLogic*)nxMalloc(sizeof(nxGameLogic));

	int i = 0;
	for(i=0;i<MAX_ENTITIES;i++)
	{
		res->entities[i].id = -1;
	}

	res->currentEntityId = 0;

	return res;
}

nxInt nxGameLogic_init(nxGameLogic* obj)
{
	if(nxGameLogic_addEntity(obj))
	{
		return 1;
	}

	NX_LOG("nxGameLogic", "added entity correctly");
	return 0;
}

nxInt nxGameLogic_update(nxGameLogic* obj)
{
	return 0;
}

void nxGameLogic_shutdown(nxGameLogic* obj)
{
	nxFree(obj);
}

nxInt nxGameLogic_addEntity(nxGameLogic* obj)
{
	nxUInt id = obj->currentEntityId++;
	obj->entities[id].id = id;
	obj->entities[id].pos.x = 0.0f;
	obj->entities[id].pos.y = 0.0f;

	nxEvent createEv;
	nxCreateEntityEventData* createEvData = (nxCreateEntityEventData*)nxMalloc(sizeof(nxCreateEntityEventData));
	createEvData->entityId = obj->entities[id].id;
	createEvData->pos = obj->entities[id].pos;

	createEv.type = NX_EVT_CREATEEVT;
	createEv.data = (void*)createEvData;

	//Fire event
	nxEventManager_queueEvent(createEv);

	return 0;
}
