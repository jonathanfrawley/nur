#include <stdio.h>

#include <nxGameLogic.h>
#include <nxHumanGameView.h>
#include <nxEvent/nxEventManager.h>
#include <nxCore/nxMM.h>

#define FRAMES_PER_SECOND 40

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

		//limit frame rate
		if( (SDL_GetTicks() - startTime) < 1000 / FRAMES_PER_SECOND )
		{ 
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - (SDL_GetTicks() - startTime) ); 
		}
	}

	nxGameLogic_shutdown(gameLogic);
	gameView->shutdown(gameView);

    return 0;
}
