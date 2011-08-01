/**
 * Scenenodes are representations of objects in the game.
 */
#ifndef SCENENODE_H
#define SCENENODE_H

#include "mmgt.h"

typedef enum SceneNodeType
{
	NODE_MAN
} SceneNodeType;

typedef struct SceneNode
{
	SceneNodeType type;
} SceneNode;

SceneNode* scenenode_new(SceneNodeType type);

#endif   // SCENENODE_H
