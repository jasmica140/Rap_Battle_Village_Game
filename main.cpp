#include "villagegame.h"

Map map[mapx][mapy];
Village village[maxplay];
Resource resource[maxplay][3];
Troops troops[maxplay][maxtroops];
ResourceBuidlings rbuild[maxplay][maxrbuild];
TroopBuidlings tbuild[maxplay][maxtbuild];


void gameloop(){

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    int playno = 0;

    cli();
    cout << "Player 1's turn!" << endl;
    turnphase(playno,totplay);


    while(totplay > 1){ //win condition

        playno = endround(playno);
        startround(playno);

        cli();
        totplay = turnphase(playno,totplay);
    }
}

int main() {

    gameloop();

    return 0;
}

