#include "scenenode.h"

SceneNode* scenenode_new(SceneNodeType type)
{
	SceneNode* node = (SceneNode*) malloc(sizeof(SceneNode));
	node->type = type;
	return node;
}

