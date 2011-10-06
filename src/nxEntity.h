#ifndef  NXENTITY_H
#define  NXENTITY_H

#include <nxAlgebra/nxVector2.h>
#include <nxCore/nxTypes.h>

#define NX_ENT_PLAYER 0
#define NX_ENT_BALL 1

typedef struct nxEntity
{
	nxUInt id;
	nxUInt type;
	nxVector2 pos;
	nxVector2 accel;
	nxFloat rot;
} nxEntity;

nxEntity* nxEntity_new();
nxInt nxEntity_update(nxEntity* obj);
void nxEntity_delete(nxEntity* obj);

#endif   // NXENTITY_H
