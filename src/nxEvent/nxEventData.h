#ifndef  NXEVENTDATA_H
#define  NXEVENTDATA_H

#include <nxEntity.h>

typedef struct nxCreateEntityEventData
{
	nxEntity entity;
	nxUInt isPlayer;
} nxCreateEntityEventData;

typedef struct nxMovementEventData
{
	nxUInt entityId;
} nxMovementEventData;

typedef struct nxUpdateEntityEventData
{
	nxEntity entity;
} nxUpdateEntityEventData;

#endif   // NXEVENTDATA_H
