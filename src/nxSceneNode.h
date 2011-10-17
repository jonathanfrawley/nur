#ifndef  NXSCENENODE_H
#define  NXSCENENODE_H

#include <nxCore/nxTypes.h>
#include <nxAlgebra/nxVector2.h>

#define NX_SN_PADDLE 0
#define NX_SN_BALL 1
#define NX_SN_PLAYER 2

typedef struct nxSceneNode
{
	nxUInt id;
	nxUInt type;
	nxVector2 pos;
	nxFloat rot;
	nxUInt texIdx;
} nxSceneNode;

#endif   // NXSCENENODE_H
