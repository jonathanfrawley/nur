#ifndef NXGAMEVIEW_H
#define NXGAMEVIEW_H

#include <nxCore/nxTypes.h>

typedef struct nxGameView
{
	nxInt (*init)(struct nxGameView* obj);
	void (*update)(struct nxGameView* obj);
	void (*draw)(struct nxGameView* obj);
	void (*shutdown)(struct nxGameView* obj);
} nxGameView;

#endif
