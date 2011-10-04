#ifndef  NXPHYSICS_H
#define  NXPHYSICS_H

#include <chipmunk.h>

#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
#include <nxCore/nxMM.h>

typedef struct nxPhysics
{
	cpSpace* space;
	cpShape* ground;
	cpShape* ballShape;
	cpBody* ballBody;
} nxPhysics;

nxPhysics* nxPhysics_new();
void nxPhysics_shutdown(nxPhysics* obj);
nxInt nxPhysics_init(nxPhysics* obj);
void nxPhysics_update(nxPhysics* obj, nxFloat timestep);

#endif   // NXPHYSICS_H
