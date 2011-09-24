#include "nxEntity.h"

#include <nxCore/nxMM.h>

nxEntity* nxEntity_new()
{
	nxEntity* res = (nxEntity*)nxMalloc(sizeof(nxEntity));

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
