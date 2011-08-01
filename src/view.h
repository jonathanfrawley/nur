#ifndef  VIEW_H
#define  VIEW_H

#include <SDL.h>

#include <stdio.h>

#include "scenenode.h"

#define MAX_SCENENODES 255

typedef struct View
{
	SceneNode nodes[MAX_SCENENODES];
	int nNodes;
} View;

View* view_new();
void view_free(View* view);
void view_init();
void view_draw(View* view);

#endif   // VIEW_H
