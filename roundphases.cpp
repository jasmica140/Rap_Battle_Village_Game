#include "villagegame.h"


int turnphase(int playno, int totplay){

    //friendly troop arrival
    friendtroop(playno,totplay);

    //enemy troop arrival
    totplay = enemytroop(playno,totplay);

    //resource earning
    earnres(playno);

    //player actions
    actions(playno, totplay);

    return totplay;
}

bool marching(int playno, int villno, int mspeed){

    //shortest path to get to target
    int i=0;
    int villx = village[villno].loc[0];
    int villy = village[villno].loc[1];

    int k;
    for(k=0; k<maxtroops; k++) {
        if (troops[playno][k].status == "army") {
            break;
        }
    }

    //min steps required to get to target
    int minstep = max(abs(troops[playno][k].loc[0] - villx), abs(troops[playno][k].loc[1] - villy));

    // while army is not in same row or column as target and army's steps per round not exceeded
    while (((troops[playno][k].loc[0] != villx) || (troops[playno][k].loc[1] != villy)) && i<mspeed){

        //go up
        if (troops[playno][k].loc[0] < villx) {
            for(int j=0; i<maxtroops; i++){
                if(troops[playno][j].status=="army"){
                    troops[playno][j].loc[0]++;      //update army location
                }
            }
        }

        //go down
        if (troops[playno][k].loc[0] > villx) {
            for(int j=0; i<maxtroops; i++){
                if(troops[playno][j].status=="army"){
                    troops[playno][j].loc[0]--;      //update army location
                }
            }
        }

        //go left
        if (troops[playno][k].loc[1] > villy) {
            for(int j=0; i<maxtroops; i++){
                if(troops[playno][j].status=="army"){
                    troops[playno][j].loc[1]--;      //update army location
                }
            }
        }

        //go right
        if (troops[playno][k].loc[1] < villy) {
            for(int j=0; i<maxtroops; i++){
                if(troops[playno][j].status=="army"){
                    troops[playno][j].loc[1]++;      //update army location
                }
            }
        }

        i++;
    }

    bool success;

    if(mspeed<=minstep){
        success=true;
    }else{
        success=false;
    }

    return success;
}

int endround(int playno){
    cout << "Player " << playno+1 << "'s turn complete!" << endl;
    playno++;
    return playno;
}

void startround(int playno){
    cout << "Player " << playno+1 << "'s turn!" << endl;
}
