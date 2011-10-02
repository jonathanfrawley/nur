#ifndef  VIEW_HPP
#define  VIEW_HPP

#include <SDL/SDL.h>

#include <stdio.h>

#include "SceneNode.hpp"
#include "Evt.hpp"
#include "EvtHnd.hpp"

#define MAX_SCENENODES 255

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;
static SDL_Surface* screen_surface;
static SDL_Surface* man_surface;

/**
 * Helpers for SDL
 **/
static SDL_Surface* load_surface(const char* filename)
{
	SDL_Surface* surface = SDL_LoadBMP(filename);
    if ( ! surface ) 
	{
        fprintf(stderr, "Unable to load image %s : %s\n", filename, SDL_GetError());
        SDL_Quit();
		return NULL;
    }
	SDL_Surface* optimizedSurface = SDL_DisplayFormat(surface); 
	SDL_FreeSurface( surface );
	return optimizedSurface;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) 
{
	SDL_Rect offset; 
	offset.x = x; 
	offset.y = y;
	SDL_BlitSurface( source, NULL, destination, &offset ); 
}


class View : public EvtHnd
{
	public:
		View()
			: m_NNodes(0)
		{
		}

		virtual ~View()
		{
			SDL_FreeSurface( man_surface );
		}

		void init()
		{
			screen_surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
			man_surface = load_surface("man.bmp");
		}

		void draw()
		{
			int i;
			for(i=0;i<m_NNodes;i++)
			{
				drawSceneNode(m_Nodes[i]);
			}
			SDL_Flip(screen_surface);
		}

		void setNodeType(int idx, SceneNodeType type)
		{
			m_Nodes[idx].setType(type);
		}

		void incNNodes(){m_NNodes++;}

		void handle(sptr<Evt> ev)
		{
			if(ev->getType()==ET_Thrust)
			{
				m_Nodes[0].setX(m_Nodes[0].getX()+1);
			}
		}

	protected:
		void drawSceneNode(const SceneNode& node)
		{
			switch(node.getType())
			{
				case(NODE_MAN):
				{
					//TODO:Coords
					apply_surface(node.getX(), node.getY(), man_surface, screen_surface);
					break;
				}
			}
		}

		SceneNode m_Nodes[MAX_SCENENODES];
		int m_NNodes;
};

#endif   // VIEW_HPP
