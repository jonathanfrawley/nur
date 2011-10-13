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

    nxGameLogic* gameLogic = nxGameLogic_new();
    nxGameView* gameView = nxHumanGameView_new();

	nxGameLogic_init(gameLogic);
    gameView->init(gameView);

	nxInt finished = 0;
	nxUInt startTime = SDL_GetTicks();
	while( ! finished) {
		nxEventManager_handleEvents();
		finished = nxGameLogic_update(gameLogic);

		gameView->update(gameView);
		gameView->draw(gameView);

        nxUInt now = SDL_GetTicks();
        nxUInt timeDelta = now - startTime;
		//limit frame rate
		if( timeDelta < FRAME_TIME )
		{ 
			SDL_Delay( FRAME_TIME - timeDelta ); 
            startTime = SDL_GetTicks();
		}
	}

	nxGameLogic_shutdown(gameLogic);
	gameView->shutdown(gameView);

    return 0;
}
