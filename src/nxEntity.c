#include "nxEntity.h"

#include <nxCore/nxMM.h>

nxEntity* nxEntity_new()
{
	nxEntity* res = (nxEntity*)nxMalloc(sizeof(nxEntity));

	res->pos.x = 0.0f;
	res->pos.y = 0.0f;

	res->accel.x = 0.0f;
	res->accel.y = 0.0f;

	res->rot = 0.0f;

	return res;
}

nxInt nxEntity_update(nxEntity* obj)
{
	return 0;
}

void nxEntity_delete(nxEntity* obj)
{
	nxFree(obj);
}
