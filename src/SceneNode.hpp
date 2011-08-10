#ifndef SCENENODE_HPP
#define SCENENODE_HPP

/**
 * Scenenodes are graphical representations of objects in the game.
 */

#include "Point2.hpp"

typedef enum SceneNodeType
{
	NODE_MAN
} ScenenodeType;

class SceneNode 
{
	public:

		SceneNode()
			: m_Type(NODE_MAN)
		{
		}

		SceneNode(SceneNodeType type)
			: m_Type(type)
		{
		}

		void setType(const SceneNodeType& type)
		{
			m_Type = type;
		}

		SceneNodeType getType() const
		{
			return m_Type;
		}

		Point2 getPos() const
		{
			return m_Pos;
		}
		float getX()const{return m_Pos.getX();}
		float getY()const{return m_Pos.getY();}
		void setX(float x){m_Pos.setX(x);}
		void setY(float y){m_Pos.setY(y);}

	protected:
		SceneNodeType m_Type;
		Point2 m_Pos;
};
#endif   // SCENENODE_HPP
