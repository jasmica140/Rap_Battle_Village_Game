#include "villagegame.h"

int *gamesetup(){

    int rplay;      //real players
    int aiplay;     //AI players

    //ask user for player amounts
    loop1:
    cout << "Please provide the number of players:" << endl;
    cin >> rplay;

    if(rplay<1){
        cout << "At least one player required!" << endl;
        goto loop1;
    }

    loop2:
    cout << "How many AI players would you like?" << endl;
    cin >> aiplay;

    if(aiplay<0){
        cout << "Number must be zero or greater!" << endl;
        goto loop2;
    }

    int totplay = rplay+aiplay;

    for(int i=0; i<totplay; i++){
        int rndx = 1 + (rand() %mapx);
        int rndy = 1 + (rand() %mapy);
        int loc[2]={rndx,rndy};

        if(i<rplay){
            village[i] = Village(loc, maxhealth, 0, 0, maxtroops, true);
        }else{
            village[i] = Village(loc, maxhealth, 0, 0, maxtroops, false);
        }

        map[rndx][rndy].status = "  V  ";
    }

    //initialise resources for each player
    for(int i=0; i<totplay; i++){

        //assign 50 of each resource to each player
        resource[i][0] = Resource("tools",50);
        resource[i][1] = Resource("spinach",50);
        resource[i][2] = Resource("tv",50);
    }


    //initialise troops for each player
    for(int i=0; i<totplay; i++) {
        for(int j=0; j<maxtroops; j++){

            int loc[2] = {village[i].loc[0],village[i].loc[1]};
            int res[3] = {0,0,0};

            troops[i][j] = Troops(15,0,0,0,0,"stationed","untrained",false,loc,res);
        }
    }

    int players[] = {rplay,aiplay};

    return players;
}

