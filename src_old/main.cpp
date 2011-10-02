#include <SDL/SDL.h>
#include <stdio.h>

#include "Boost.hpp"
#include "SceneNode.hpp"
#include "View.hpp"
#include "EvtMan.hpp"
#include "ThrustEvt.hpp"

bool handle_events()
{
    SDL_Event event;
    bool done = false;
    while ( SDL_PollEvent(&event) ) 
	{
		switch(event.type)
		{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						done = true;
						break;
					case SDLK_LEFT:
						EvtMan::get().push(sptr<Evt>(new ThrustEvt(-1.0f,0.0f)));
						break;
					case SDLK_RIGHT:
						EvtMan::get().push(sptr<Evt>(new ThrustEvt(1.0f,0.0f)));
						break;
				}
				break;
		}
    }
    return done;
}

int main(int argc, char *argv[]) 
{    
    /* Initialize SDL for video output */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Set the title bar in environments that support it */
    SDL_WM_SetCaption("pmuj", NULL);

	sptr<View> view = sptr<View>(new View());
	view->init();
	view->setNodeType(0, NODE_MAN);
	view->incNNodes();
	EvtMan::get().pushHnd(view);

    bool done = false;
    while ( ! done ) 
    {
        done = handle_events();
		EvtMan::get().handle();
		view->draw();
	}

    SDL_Quit();
    return 1;
}
