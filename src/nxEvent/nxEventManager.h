#ifndef  NXEVENTMANAGER_H
#define  NXEVENTMANAGER_H

#include <nxCore/nxTypes.h>
#include <nxEvent/nxEvent.h>

#define NX_MAX_HANDLERS 32
#define NX_MAX_EVENTS 1024

//typedef void (*handlers)(nxEvent ev) = nxEventHandlerFunc;
//typedef nxEventHandlerFunc = void (*handlers)(nxEvent ev);
typedef void (*nxEventHandlerFunc)(nxEvent ev);

typedef struct nxEventManager
{
	nxEventHandlerFunc handlers[NX_MAX_HANDLERS];
	nxEvent events[NX_MAX_EVENTS];
	nxUInt currentEvtIdx;
	nxUInt currentHandlerIdx;
} nxEventManager;

void nxEventManager_queueEvent(nxEvent event);

void nxEventManager_addHandler(nxEventHandlerFunc);

void nxEventManager_handleEvents();

void nxEventManager_handleEvent(nxEvent event);

void nxEventManager_init();

#endif   // NXEVENTMANAGER_H
