#include "nxHumanGameView.h"

#include <nxCore/nxMM.h>

nxGameView* nxHumanGameView_new()
{
	nxGameView* res = (nxGameView*)nxMalloc(sizeof(nxGameView));

	res->init = nxHumanGameView_init;
	res->update = nxHumanGameView_update;
	res->draw = nxHumanGameView_draw;

	return res;
}

void nxHumanGameView_init(nxGameView* obj)
{
}

void nxHumanGameView_update(nxGameView* obj)
{
}

void nxHumanGameView_draw(nxGameView* obj)
{
}
