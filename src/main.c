#include <SDL.h>

#include "scenenode.h"
#include "view.h"

int handle_events()
{
    SDL_Event event;
    int done = 0;
    while ( SDL_PollEvent(&event) ) {
        if ( event.type == SDL_QUIT ) {
            done = 1;
        }
        if ( event.type == SDL_KEYDOWN ) {
            if ( event.key.keysym.sym == SDLK_SPACE ) {
            }
            if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                done = 1;
            }
        }
    }
    return done;
}

int main(int argc, char *argv[]) 
{    
    int done;

    /* Initialize SDL for video output */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Set the title bar in environments that support it */
    SDL_WM_SetCaption("pmuj", NULL);

	View* view = view_new();
	view->nodes[0].type=NODE_MAN;
	view->nNodes=1;

	view_init();

    done = 0;
    while ( ! done ) 
    {
        done = handle_events();
		view_draw(view);
    }

	view_free(view);

    SDL_Quit();
    return 1;
}
