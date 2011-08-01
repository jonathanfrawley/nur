#include "view.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int SCREEN_BPP = 32;
static SDL_Surface* screen_surface;
static SDL_Surface* man_surface;

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

static void draw_scenenode(SceneNode* node) 
{
	switch(node->type)
	{
		case(NODE_MAN):
		{
			//TODO:Coords
			apply_surface(0, 0, man_surface, screen_surface);
			break;
		}
	}
}

//-------------------------------------------

View* view_new()
{
	View* view = (View*) malloc(sizeof(View));
	view->nNodes = 0;
	return view;
}

void view_free(View* view)
{
	SDL_FreeSurface( man_surface );
}

void view_init()
{
	screen_surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    man_surface = load_surface("man.bmp");
}

void view_draw(View* view)
{
	int i;
	for(i=0;i<view->nNodes;i++)
	{
		draw_scenenode(&(view->nodes[i]));
	}
	SDL_Flip(screen_surface);
}
