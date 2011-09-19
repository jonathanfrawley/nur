#include <stdio.h>

#include "nxGameView.h"
#include <nxCore/nxMM.h>

int main(void)
{
    nxGameView* gameView = nxGameView_new();

    nxGameView_init(gameView);

    nxGameView_draw(gameView);

    nxFree(gameView);
    return 0;
}
