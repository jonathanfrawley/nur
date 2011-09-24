#ifndef  NXEVENT_H
#define  NXEVENT_H

#include <nxCore/nxTypes.h>

#define NX_EVT_CREATEEVT 0

typedef struct nxEvent {
	nxUInt type;
	void* data;
} nxEvent;				

#endif   // NXEVENT_H
