#include "villagegame.h"


int turnphase(int playno, int totplay, int round){

    //friendly troop arrival
    friendtroop(playno,totplay);

    //enemy troop arrival
    totplay = enemytroop(playno,totplay);

    //resource earning
    earnres(playno);

    //player actions
    totplay = actions(playno, totplay, round);

    return totplay;
}

bool marching(int playno, int armyno, int target, int mspeed){

    //shortest path to get to target
    int i=0;
    int villx = village[target].loc[0];
    int villy = village[target].loc[1];


    //min steps required to get to target
    int minstep = max(abs(army[playno][armyno].loc[0] - villx), abs(army[playno][armyno].loc[1] - villy));

    // while army is not in same row or column as target and army's steps per round not exceeded
    while (((army[playno][armyno].loc[0] != villx) || (army[playno][armyno].loc[1] != villy)) && i<mspeed){

        //go up
        if (army[playno][armyno].loc[0] < villx) {
            army[playno][armyno].loc[0]++;          //update army location
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

    bool success;

    if(mspeed<=minstep){
        success=true;
    }else{
        success=false;
    }

    return success;
}

int endround(int playno){
    refreshcli(playno);
    mvwprintw(win,erry,1,"Player %d's turn complete!", playno+1);
    playno++;
    return playno;
}

void startround(int playno){
    mvwprintw(win,1,1,"Player %d's turn!",playno+1);
}
