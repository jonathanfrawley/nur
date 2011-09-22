#ifndef  NXHUMANGAMEVIEW_H
#define  NXHUMANGAMEVIEW_H

#include <nxGameView.h>

nxGameView* nxHumanGameView_new();

void nxHumanGameView_init(nxGameView* obj);

void nxHumanGameView_update(nxGameView* obj);

void nxHumanGameView_draw(nxGameView* obj);

#endif   // NXHUMANGAMEVIEW_H
