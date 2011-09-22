#ifndef NXGAMEVIEW_H
#define NXGAMEVIEW_H

typedef struct nxGameView
{
	void (*init)(struct nxGameView* obj);
	void (*update)(struct nxGameView* obj);
	void (*draw)(struct nxGameView* obj);
} nxGameView;

#endif
