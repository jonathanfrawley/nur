#include "nxSceneNode.h"

void nxSceneNode_init(nxSceneNode* obj)
{
	obj->id = 0;
	obj->valid = 0;
	obj->hasTex = 0;
	obj->type = 0;
	nxVector2_init(&obj->pos);
	obj->rot = 0;
	obj->isAnimated = NX_FALSE;
	obj->moving = 0;
	obj->animTime = 0;
	obj->animFrameTime = 0;
	obj->maxAnimTime = 0;
	obj->texId = 0;
	obj->mainTexId = 0;
	obj->crouchingTexId = 0;
    for(int i=0;i<NX_MAX_ANIMTEXS;i++)
    {
        obj->animTexIds[i] = 0;
    }
	obj->reversed = 0;
	obj->width = 0;
	obj->height = 0;
}
