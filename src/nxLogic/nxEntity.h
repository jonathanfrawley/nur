#ifndef  NXENTITY_H
#define  NXENTITY_H

#include <nxAlgebra/nxVector2.h>
#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>

#define NX_ENT_PLAYER 0
#define NX_ENT_PLATFORM 1
#define NX_ENT_BULLET 2
#define NX_ENT_FIKE 3

#define NX_DOUBLETAPTIME 100

typedef struct nxEntity
{
	nxUInt id;
	nxUInt type;
	nxUInt valid;
	nxVector2 pos;
	nxFloat rot;
    nxUInt reversed;
    nxUInt moving;
	nxUInt crouching;
    nxInt xVel;
    nxInt yVel;
    nxFloat width;
    nxFloat height;
//    nxUInt nJumps;
	nxUInt hasDoubleJumped;
    //Show keyboard movement on x and y axes.
    nxFloat xKeys;
    nxFloat yKeys;
    nxBool movingRight;
//    nxUInt timeSpentTapping;

    nxBool runningLeft;
    nxBool allowedRunLeft;
    nxBool runningRight;
    nxBool allowedRunRight;
} nxEntity;

nxEntity* nxEntity_alloc();
void nxEntity_free(nxEntity* obj);
void nxEntity_init0(nxEntity* obj);

#endif   // NXENTITY_H
