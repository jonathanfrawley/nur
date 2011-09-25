#ifndef  NXEVENT_H
#define  NXEVENT_H

#include <nxCore/nxTypes.h>

#define NX_EVT_CREATEENT 0
#define NX_EVT_ENDGAME 1

typedef struct nxEvent 
{
	nxUInt type;
	void* data;
} nxEvent;

#endif   // NXEVENT_H
