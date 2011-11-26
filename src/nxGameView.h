#ifndef NXGAMEVIEW_H
#define NXGAMEVIEW_H

#include <AL/alut.h>

#include <nxCore/nxTypes.h>

#define NX_MAX_SOUNDS 255

typedef struct nxGameView
{
	nxInt (*init)(struct nxGameView* obj);
	void (*update)(struct nxGameView* obj, nxUInt deltaMilliseconds);
	void (*draw)(struct nxGameView* obj);
	void (*shutdown)(struct nxGameView* obj);

    ALuint soundSources[NX_MAX_SOUNDS];
} nxGameView;

#endif
