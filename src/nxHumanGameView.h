#ifndef  NXHUMANGAMEVIEW_H
#define  NXHUMANGAMEVIEW_H

#include <nxGameView.h>
#include <nxSceneNode.h>
#include <nxEvent/nxEvent.h>
#include <nxCore/nxConstants.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxCore/nxMath.h>
#include <nxEvent/nxEventManager.h>
#include <nxEvent/nxEventData.h>

#include <nxTextureLoader.h>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include <stdlib.h>
#include <AL/alut.h>

#define NX_MAX_SCENENODES 1024

nxGameView* nxHumanGameView_new();
nxInt nxHumanGameView_init(nxGameView* obj);
void nxHumanGameView_update(nxGameView* obj, nxUInt deltaMilliseconds);
void nxHumanGameView_draw(nxGameView* obj);
void nxHumanGameView_shutdown(nxGameView* obj);

nxInt init_GL();

nxInt nxHumanGameView_initAudio(nxGameView* obj);

nxInt nxHumanGameView_loadBackgrounds(void* vobj);

void nxHumanGameView_handleEvent(nxEvent evt, void* vobj);

void nxHumanGameView_toggleFullscreen();

//Rendering
void nxHumanGameView_drawSceneNode(nxSceneNode* node);

void nxHumanGameView_drawRectangle(nxFloat x, nxFloat y, nxFloat width, nxFloat height, nxFloat rot);

//Util
nxUInt nxHumanGameView_getSceneNodeIdxWithEntityId(nxUInt entityId);

#endif   // NXHUMANGAMEVIEW_H
