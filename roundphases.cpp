#include "villagegame.h"


void turnphase(int playno){

    //friendly troop arrival

    //enemy troop arrival

    //resource earning
    earnres(playno);

    //player actions
    actions(playno);
}

void marching(int playno, int villno, int mspeed){

    //min steps required to get to target
    int minstep = max(abs(village[playno].loc[0] - village[villno].loc[0]), abs(village[playno].loc[1] - village[villno].loc[1]));

    //shortest path to get to target
    int i=0;
    int playx = village[playno].loc[0];
    int playy = village[playno].loc[1];
    int villx = village[villno].loc[0];
    int villy = village[villno].loc[1];

    // while army is not in same row or column as target and army's steps per round not exceeded
    while (((playx != villx) || (playy != villy)) && i<mspeed){

        //go up
        if (playx < villx) {
            army[playno].loc[0]++;      //update army location
            playx++;
        }

        //go down
        if (playx > villx) {
            army[playno].loc[0]--;      //update army location
            playx--;
        }

        //go left
        if (playy > villy) {
            army[playno].loc[1]++;      //update army location
            playy--;
        }

        //go right
        if (playy < villy) {
            army[playno].loc[1]--;      //update army location
            playy++;
        }
        i++;
    }
}

int endround(int playno){
    cout << "Player " << playno << "'s turn complete!" << endl;
    playno++;
    return playno;
}

void startround(int playno){
    cout << "Player " << playno << "'s turn!" << endl;
}
