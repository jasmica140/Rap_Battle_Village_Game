#include "villagegame.h"


int turnphase(int playno, int totplay, int roundno){

    if(village[playno].attack){
        alertcli(playno,totplay,"attack");
    }

    //friendly troop arrival
    friendtroop(playno);

    //enemy troop arrival
    totplay = enemytroop(playno,totplay);

    //resource earning
    earnres(playno);

    //player actions
    totplay = actions(playno, totplay, roundno);

    return totplay;
}

void marching(int playno, int armyno, int target, int mspeed, int totplay){

    //shortest path to get to target
    int i=0;
    int villx = village[target].loc[0];
    int villy = village[target].loc[1];

    //clear old position
    map[army[playno][armyno].loc[0]][army[playno][armyno].loc[1]].status = "     ";

    // while army is not in same row or column as target and army's steps per round not exceeded
    while (((army[playno][armyno].loc[0] != villx) || (army[playno][armyno].loc[1] != villy)) && i<mspeed){

        //go up
        if (army[playno][armyno].loc[0] < villx) {
            army[playno][armyno].loc[0]++;       //update army location
        }

        //go down
        if (army[playno][armyno].loc[0] > villx) {
            army[playno][armyno].loc[0]--;      //update army location
        }

        //go left
        if (army[playno][armyno].loc[1] > villy) {
            army[playno][armyno].loc[1]--;      //update army location
        }

        //go right
        if (army[playno][armyno].loc[1] < villy) {
            army[playno][armyno].loc[1]++;      //update army location
        }
        i++;
    }

    map[army[playno][armyno].loc[0]][army[playno][armyno].loc[1]].status = "  A  ";
    refreshcli(playno,totplay);
}

int endround(int playno, int round){

    round++;

    return round;
}

int startround(int playno, int totplay){

    alertcli(playno, totplay, "round");
    playno = village[0].idx;
    return playno;
}
