
#include <stdio.h>

#include <nxLogic/nxGameLogic.h>
#include <nxView/nxHumanGameView.h>
#include <nxEvent/nxEventManager.h>
#include <nxCore/nxMM.h>
#include <nxLogic/nxProcessManager.h>

#define FRAMES_PER_SECOND 60

static int FRAME_TIME = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
    fflush(stdout);

	nxEventManager_init0();

    nxProcessManager_init(nxProcessManager_getInstance());

    nxGameView* gameView = nxHumanGameView_alloc();
    gameView->init(gameView);

    nxGameLogic* gameLogic = nxGameLogic_alloc();
	nxGameLogic_init0(gameLogic);

	nxInt finished = 0;
	nxUInt startTime = SDL_GetTicks();
	nxUInt lastFrameTime = 0;
	while( ! finished) {
        nxProcessManager_update(nxProcessManager_getInstance(), lastFrameTime);

		nxEventManager_handleEvents();
		finished = nxGameLogic_update(gameLogic, lastFrameTime);

		gameView->update(gameView, lastFrameTime);
		gameView->draw(gameView);

        nxUInt now = SDL_GetTicks();
        nxUInt timeDelta = now - startTime;

		//limit frame rate
		if( timeDelta < FRAME_TIME )
		{
            printf("Going down for SDL_Delay , timeDelta is : %d, FRAME_TIME is : %d \n", timeDelta, FRAME_TIME);

			SDL_Delay( FRAME_TIME - timeDelta );
		}

        lastFrameTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();

        printf("YO! lastFrameTime is : %d \n", lastFrameTime);
	}

	nxGameLogic_shutdown(gameLogic);
	gameView->shutdown(gameView);

    return 0;
}

/*
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

size_t sx=600, sy=600, bpp=0;

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();                                       // set location in front of camera
    glTranslated(0, 0, -10);

    glBegin(GL_QUADS);                                      // draw a square
        glColor3d(1, 0, 0);
        glVertex3d(-2,  2,  0);
        glVertex3d( 2,  2,  0);
        glVertex3d( 2, -2,  0);
        glVertex3d(-2, -2,  0);
    glEnd();

    glFlush();
    SDL_GL_SwapBuffers();
}

int input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
        if (event.type == SDL_QUIT || (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    SDL_Surface *surf;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
    if (!(surf = SDL_SetVideoMode(sx, sy, bpp, SDL_OPENGL))) return 0;

    glViewport(0, 0, sx, sy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)sx / (float)sy, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(1, 1, 1, 1);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    for (;;) {
        if (!input()) break;
        render();
        SDL_Delay(10);
    }

    SDL_FreeSurface(surf);
    SDL_Quit();
    return 0;
}
*/
