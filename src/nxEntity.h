#ifndef  NXENTITY_H
#define  NXENTITY_H

#include <nxAlgebra/nxVector2.h>
#include <nxCore/nxTypes.h>

typedef struct nxEntity
{
	nxUInt id;
	nxVector2 pos;
	nxVector2 accel;
} nxEntity;

nxEntity* nxEntity_new();
nxInt nxEntity_update(nxEntity* obj);
void nxEntity_delete(nxEntity* obj);

#endif   // NXENTITY_H
