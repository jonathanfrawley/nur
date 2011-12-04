#include "nxEntity.h"

#include <nxCore/nxMM.h>

nxEntity* nxEntity_alloc()
{
	nxEntity* res = (nxEntity*)nxMalloc(sizeof(nxEntity));
    nxEntity_init0(res);
	return res;
}

void nxEntity_free(nxEntity* obj)
{
	nxFree(obj);
}

void nxEntity_init0(nxEntity* obj)
{
	obj->id = 0;
	obj->type = 0;
	obj->valid = 0;
	nxVector2_init0(&(obj->pos));
    obj->rot = 0.0f;
    obj->reversed = 0;
    obj->moving = 0;
	obj->crouching = 0;
    obj->xVel = 0.0f;
    obj->yVel = 0.0f;
    obj->width = 0.0f;
    obj->height = 0.0f;
	obj->hasDoubleJumped = 0;
    obj->xKeys = 0.0f;
    obj->yKeys = 0.0f;
//    obj->timeSpentTapping = 0.0f;
    obj->runningLeft = NX_FALSE;
    obj->allowedRunLeft = NX_FALSE;
    obj->runningRight = NX_FALSE;
    obj->allowedRunRight = NX_FALSE;
}
