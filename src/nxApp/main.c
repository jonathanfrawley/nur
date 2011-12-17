
#include <stdio.h>

#include <nxLogic/nxGameLogic.h>
#include <nxView/nxHumanGameView.h>
#include <nxEvent/nxEventManager.h>
#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxLogic/nxProcessManager.h>

#define FRAMES_PER_SECOND 60

static int FRAME_TIME = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
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

	nxUInt frameTimeCounter = 0;
	nxUInt frameDrawCounter = 0;
	nxUInt frameUpdateCounter = 0;

	while( ! finished) {
        nxProcessManager_update(nxProcessManager_getInstance(), lastFrameTime);

		nxEventManager_handleEvents();
		finished = nxGameLogic_update(gameLogic, lastFrameTime);
        frameUpdateCounter++;

		gameView->update(gameView, lastFrameTime);
		gameView->draw(gameView);
        frameDrawCounter++;

        nxUInt now = SDL_GetTicks();
        nxUInt timeDelta = now - startTime;

		//limit frame rate
		while( timeDelta < FRAME_TIME )
		{
            //printf("Going down for SDL_Delay , timeDelta is : %d, FRAME_TIME is : %d \n", timeDelta, FRAME_TIME);

            gameView->draw(gameView);
            frameDrawCounter++;

            now = SDL_GetTicks();
            timeDelta = now - startTime;

			//SDL_Delay( FRAME_TIME - timeDelta );
		}

        lastFrameTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();

#ifdef DEBUG
        //Useful logging every second.
        frameTimeCounter += lastFrameTime;
        if(frameTimeCounter >= 1000)
        {
           char buf[255];
           sprintf(buf, "nupdates <%d>, ndraws <%d>", frameUpdateCounter, frameDrawCounter);
           nxLog(NX_LOG_INFO, buf);
           fflush(stdout);

           frameTimeCounter = 0;
           frameDrawCounter = 0;
           frameUpdateCounter = 0;
        }
#endif //DEBUG
	}

	nxGameLogic_shutdown(gameLogic);
	gameView->shutdown(gameView);

    return 0;
}
