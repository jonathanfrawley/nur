#ifndef  NXEVENT_H
#define  NXEVENT_H

#include <nxCore/nxTypes.h>

#define NX_EVT_CREATEENT 0
#define NX_EVT_ENDGAME 1

#define NX_EVT_STARTMOVEUP 2
#define NX_EVT_STARTMOVEDOWN 3
#define NX_EVT_STARTMOVELEFT 4
#define NX_EVT_STARTMOVERIGHT 5

#define NX_EVT_ENDMOVEUP 6
#define NX_EVT_ENDMOVEDOWN 7
#define NX_EVT_ENDMOVELEFT 8
#define NX_EVT_ENDMOVERIGHT 9

#define NX_EVT_UPDATEENT 10

#define NX_EVT_FIRE 11

typedef struct nxEvent 
{
	nxUInt type;
	void* data;
} nxEvent;

#endif   // NXEVENT_H
