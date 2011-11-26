#include <stdio.h>

#include <nxGameLogic.h>
#include <nxHumanGameView.h>
#include <nxEvent/nxEventManager.h>
#include <nxCore/nxMM.h>

#define FRAMES_PER_SECOND 60

static int FRAME_TIME = 1000 / FRAMES_PER_SECOND;

int main(void)
{
	nxEventManager_init();

    nxGameView* gameView = nxHumanGameView_new();
    gameView->init(gameView);

    nxGameLogic* gameLogic = nxGameLogic_new();
	nxGameLogic_init(gameLogic);

	nxInt finished = 0;
	nxUInt startTime = SDL_GetTicks();
	nxUInt lastFrameTime = 0;
	while( ! finished) {
		nxEventManager_handleEvents();
		finished = nxGameLogic_update(gameLogic, lastFrameTime);

		gameView->update(gameView, lastFrameTime);
		gameView->draw(gameView);

        nxUInt now = SDL_GetTicks();
        nxUInt timeDelta = now - startTime;

        printf("now is %d, timeDelta is %d, startTime is %d \n", now, timeDelta, startTime);

		//limit frame rate
		if( timeDelta < FRAME_TIME )
		{ 
			SDL_Delay( FRAME_TIME - timeDelta ); 
		}

        lastFrameTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();
	}

	nxGameLogic_shutdown(gameLogic);
	gameView->shutdown(gameView);

    return 0;
}
