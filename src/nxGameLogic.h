#ifndef NXGAMELOGIC_H
#define NXGAMELOGIC_H

#include <nxCore/nxTypes.h>

typedef struct nxGameLogic
{
} nxGameLogic;

nxGameLogic* nxGameLogic_new();

nxInt nxGameLogic_init(nxGameLogic* obj);

nxInt nxGameLogic_update(nxGameLogic* obj);

#endif
