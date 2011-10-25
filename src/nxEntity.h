#ifndef  NXENTITY_H
#define  NXENTITY_H

#include <nxAlgebra/nxVector2.h>
#include <nxCore/nxTypes.h>

#define NX_ENT_PLAYER 0
#define NX_ENT_PLATFORM 1

typedef struct nxEntity
{
	nxUInt id;
	nxUInt type;
	nxUInt valid;
	nxVector2 pos;
	nxFloat rot;
    nxUInt reversed;

    nxInt xVel;
    nxInt yVel;

    nxFloat width;
    nxFloat height;

    //Show keyboard movement on x and y axes.
    nxInt xKeys;
    nxInt yKeys;
} nxEntity;

nxEntity* nxEntity_new();
nxInt nxEntity_update(nxEntity* obj);
void nxEntity_delete(nxEntity* obj);

#endif   // NXENTITY_H
