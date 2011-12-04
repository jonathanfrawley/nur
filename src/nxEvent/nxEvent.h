#ifndef  NXEVENT_H
#define  NXEVENT_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxMM.h>

typedef enum nxEventType 
{
    NX_EVT_CREATEENT,
    NX_EVT_ENDGAME,
    NX_EVT_STARTMOVEUP,
    NX_EVT_STARTMOVEDOWN,
    NX_EVT_STARTMOVELEFT,
    NX_EVT_STARTMOVERIGHT,
    NX_EVT_ENDMOVEUP,
    NX_EVT_ENDMOVEDOWN,
    NX_EVT_ENDMOVELEFT,
    NX_EVT_ENDMOVERIGHT,
    NX_EVT_UPDATEENT ,
    NX_EVT_FIRE,
    NX_EVT_PHYSICSUPDATEENT,
    NX_EVT_CROUCH,
    NX_EVT_UNCROUCH,
    NX_EVT_STOPALLOWEDRUNLEFT,
    NX_EVT_STOPALLOWEDRUNRIGHT
} nxEventType;

typedef struct nxEvent 
{
	nxEventType type;
	nxPointer data;
} nxEvent;

nxEvent* nxEvent_alloc(nxEventType type);
void nxEvent_free(nxEvent* obj);

#endif   // NXEVENT_H
