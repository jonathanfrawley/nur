#ifndef  NXEVENTDATA_H
#define  NXEVENTDATA_H

#include <nxCore/nxTypes.h>
#include <nxAlgebra/nxVector2.h>

typedef struct nxCreateEntityEventData
{
	nxUInt entityId;
	nxVector2 pos;
} nxCreateEntityEventData;

#endif   // NXEVENTDATA_H
