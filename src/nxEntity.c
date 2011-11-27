#include "nxEntity.h"

#include <nxCore/nxMM.h>

nxEntity* nxEntity_new()
{
	nxEntity* res = (nxEntity*)nxMalloc(sizeof(nxEntity));
    nxEntity_init(res);
	return res;
}

void nxEntity_init(nxEntity* obj)
{
	obj->id = 0;
	obj->type = 0;
	obj->valid = 0;
	nxVector2_init(&(obj->pos));
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
}

nxInt nxEntity_update(nxEntity* obj)
{
	return 0;
}

void nxEntity_delete(nxEntity* obj)
{
	nxFree(obj);
}

nxBool nxEntity_isDoubleTap(nxEntity* obj, nxFloat xVel)
{
    if(xVel > NX_FLOAT_DELTA)
    {
        return NX_TRUE;
    }
    else if(xVel < -NX_FLOAT_DELTA)
    {
        return NX_TRUE;
    }
    else
    {
        return NX_FALSE;
    }
}
