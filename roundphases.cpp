#include "villagegame.h"


int turnphase(int playno, int roundno){

    if(village[playno]->attack && village[playno]->preal){
        alertcli(playno,"attack");
    }

    //friendly troop arrival
    friendtroop(playno);

    //enemy troop arrival
    playno = enemytroop(playno);

    //resource earning
    earnres(playno);

    //player actions
    playno = actions(playno, roundno);

    return playno;
}

void marching(int playno, int armyno, int target, int mspeed){

    int i=0;

    for(int v=0; v<village.size(); v++){
        if(village[v]->idx == village[playno]->army[armyno]->target){
            target = v;
            break;
        }
    }

    int villx = village[target]->loc[0];
    int villy = village[target]->loc[1];

    //clear old position
    map[village[playno]->army[armyno]->loc[0]][village[playno]->army[armyno]->loc[1]].status = "     ";

    // while army is not in same row or column as target and army's steps per round not exceeded
    while ((village[playno]->army[armyno]->loc[0] != villx || village[playno]->army[armyno]->loc[1] != villy) && i<mspeed){

        //go up
        if (village[playno]->army[armyno]->loc[0] < villx) {
            village[playno]->army[armyno]->loc[0]++;       //update army location
        }

        //go down
        if (village[playno]->army[armyno]->loc[0] > villx) {
            village[playno]->army[armyno]->loc[0]--;      //update army location
        }

        //go left
        if (village[playno]->army[armyno]->loc[1] > villy) {
            village[playno]->army[armyno]->loc[1]--;      //update army location
        }

        //go right
        if (village[playno]->army[armyno]->loc[1] < villy) {
            village[playno]->army[armyno]->loc[1]++;      //update army location
        }
        i++;
    }

    map[village[playno]->army[armyno]->loc[0]][village[playno]->army[armyno]->loc[1]].status = "  A  ";
    refreshcli(playno);
}

int endround(int round){

    round++;

    return round;
}

void startround(int roundno){

    for(auto & i : village){
        if(i->preal){
            alertcli(roundno,"round");
            break;
        }
    }
}
