#ifndef  NXSCENENODE_H
#define  NXSCENENODE_H

#include <nxCore/nxTypes.h>
#include <nxCore/nxConstants.h>
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

	nxUInt moving;
	nxUInt animTime;
	nxUInt animFrameTime;
	nxUInt maxAnimTime;

	nxUInt texId;
	nxUInt animTexIds[NX_MAX_ANIMTEXS];

	nxUInt reversed;
	nxFloat width;
	nxFloat height;
} nxSceneNode;

#endif   // NXSCENENODE_H
