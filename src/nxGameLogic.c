#include "nxGameLogic.h"

#include <nxCore/nxMM.h>

nxGameLogic* nxGameLogic_new()
{
	nxGameLogic* res = (nxGameLogic*)nxMalloc(sizeof(nxGameLogic));

	return res;
}

nxInt nxGameLogic_init(nxGameLogic* obj)
{
	return 0;
}

nxInt nxGameLogic_update(nxGameLogic* obj)
{
	return 0;
}

void nxGameLogic_shutdown(nxGameLogic* obj)
{
	nxFree(obj);
}
