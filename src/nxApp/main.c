#include <stdio.h>

#include <nxLogic/nxGameLogic.h>
#include <nxView/nxHumanGameView.h>
#include <nxEvent/nxEventManager.h>
#include <nxCore/nxMM.h>
#include <nxLogic/nxProcessManager.h>

#define FRAMES_PER_SECOND 60

static int FRAME_TIME = 1000 / FRAMES_PER_SECOND;

int main(void)
{
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
