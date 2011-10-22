#ifndef  NXSCENENODE_H
#define  NXSCENENODE_H

#include <nxCore/nxTypes.h>
#include <nxAlgebra/nxVector2.h>

#define NX_SN_PLAYER 0
#define NX_SN_PLATFORM 1

typedef struct nxSceneNode
{
	nxUInt id;
	nxInt valid;
	nxInt hasTex;
	nxUInt type;
	nxVector2 pos;
	nxFloat rot;
	nxUInt texId;
	nxUInt reversed;
	nxFloat width;
	nxFloat height;
} nxSceneNode;

#endif   // NXSCENENODE_H
