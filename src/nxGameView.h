#ifndef NXGAMEVIEW_H
#define NXGAMEVIEW_H

typedef struct nxGameView
{
} nxGameView;

nxGameView* nxGameView_new();
void nxGameView_init(nxGameView* obj);
void nxGameView_draw(nxGameView* obj);

#endif
