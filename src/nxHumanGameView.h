#ifndef  NXHUMANGAMEVIEW_H
#define  NXHUMANGAMEVIEW_H

#include <nxGameView.h>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

nxGameView* nxHumanGameView_new();
nxInt nxHumanGameView_init(nxGameView* obj);
void nxHumanGameView_update(nxGameView* obj);
void nxHumanGameView_draw(nxGameView* obj);
void nxHumanGameView_shutdown(nxGameView* obj);

nxInt init_GL();

#endif   // NXHUMANGAMEVIEW_H
