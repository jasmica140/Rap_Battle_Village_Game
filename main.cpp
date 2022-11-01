#include "villagegame.h"

void gameloop(){

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    villagesetup();
    resourcesetup();
    troopsetup();

    int playno = 0;
    turnphase(playno,totplay);

    while(totplay > 1){ //win condition

        playno = endround(playno);
        startround(playno);

        totplay = turnphase(playno,totplay);
    }
}

int main() {

    gameloop();
    return 0;
}
