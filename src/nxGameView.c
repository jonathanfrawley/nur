#include "nxGameView.h"

#include <nxCore/nxMM.h>

nxGameView* nxGameView_new()
{
    nxGameView* res = (nxGameView*)nxMalloc(sizeof(nxGameView));

    return res;
}

void nxGameView_init(nxGameView* obj)
{
}

void nxGameView_draw(nxGameView* obj)
{
}
