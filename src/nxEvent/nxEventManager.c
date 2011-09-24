#include "nxEventManager.h"

#include <nxCore/nxLog.h>

static nxEventManager instance;
//instance = (nxEventManager*)nxMalloc(sizeof(nxEventManager));
//instance.currentEvtIdx = 0;
//instance.currentHandlerIdx = 0;

void nxEventManager_init()
{
	for(int i=0;i<NX_MAX_EVENTS;i++)
	{
		instance.events[i].type = -1;
	}

	for(int i=0;i<NX_MAX_HANDLERS;i++)
	{
		instance.handlers[i] = NX_NULL;
	}

	instance.currentEvtIdx = 0;
	instance.currentHandlerIdx = 0;
}

void nxEventManager_queueEvent(nxEvent event)
{
	instance.events[instance.currentEvtIdx++] = event;
}

void nxEventManager_addHandler(nxEventHandlerFunc handler)
{
	instance.handlers[instance.currentHandlerIdx++] = handler;
}

void nxEventManager_handleEvents()
{
	for(int i=0;i<NX_MAX_EVENTS;i++)
	{
		if(instance.events[i].type == -1)
		{
			continue;
		}

		NX_LOG("nxEventManager", "handling event");
		nxEventManager_handleEvent(instance.events[i]);

		instance.events[i].type = -1;
		instance.currentEvtIdx--;
	}
}

void nxEventManager_handleEvent(nxEvent event)
{
	for(int i=0;i<NX_MAX_HANDLERS;i++)
	{
		if(instance.handlers[i] == NX_NULL)
		{
			continue;
		}

		instance.handlers[i](event);
	}
}
