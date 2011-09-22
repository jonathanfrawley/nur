#include <stdio.h>

#include <nxGameLogic.h>
#include <nxHumanGameView.h>
#include <nxCore/nxMM.h>

int main(void)
{
    nxGameLogic* gameLogic = nxGameLogic_new();
    nxGameView* gameView = nxHumanGameView_new();

	nxGameLogic_init(gameLogic);
    gameView->init(gameView);

	int finished = 0;
	while( ! finished) {
		finished = nxGameLogic_update(gameLogic);

		gameView->update(gameView);
		gameView->draw(gameView);
	}

	nxGameLogic_shutdown(gameLogic);
	gameView->shutdown(gameView);

    return 0;
}
