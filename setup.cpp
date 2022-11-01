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

    int players[] = {rplay,aiplay};

    return players;
}


void villagesetup(){

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    //village and resources for each player
    for(int i=0; i<totplay; i++) {

        loop:
        //not evenly spaced yet...fix later
        village[i].loc[0] = 1 + (rand() %100);
        village[i].loc[1] = 1 + (rand() %100);

        //different coordinates for each village
        for(int j=0; j<i; j++){
            if(village[i].loc[0] == village[j].loc[0]){
                if(village[i].loc[1] == village[j].loc[1]){
                    goto loop;
                }
            }
        }

        village[i].health = maxhealth;
        village[i].tbuildings = 0;
        village[i].rbuildings = 0;
        village[i].troops = 50;

        if(i<players[0]){
            village[i].ptype = true;
        }else{
            village[i].ptype = false;
        }

        map[village[i].loc[0]][village[i].loc[1]].status = "V";      //assign village location in map
    }
}

void resourcesetup(){

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    //resources for each player
    for(int i=0; i<totplay; i++) {

        //assign 50 of each resource to each player
        resource[i][0].type = "tools";
        resource[i][0].amount = 50;

        resource[i][1].type = "spinach";
        resource[i][1].amount = 50;

        resource[i][2].type = "tv";
        resource[i][2].amount = 50;
    }
}

void troopsetup(){

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    //initialise troops for each player
    for(int i=0; i<totplay; i++) {
        for(int j=0; j<maxtroops; j++){

            troops[i][j].cost = 15;
            troops[i][j].health = 0;
            troops[i][j].attack = 0;
            troops[i][j].carrycap = 0;
            troops[i][j].speed = 0;
            troops[i][j].status = "stationed";
            troops[i][j].type = "untrained";
            troops[i][j].army = false;
            troops[i][j].loc[0] = village[i].loc[0];
            troops[i][j].loc[1] = village[i].loc[1];
            troops[i][j].resource[0] = 0;
            troops[i][j].resource[1] = 0;
            troops[i][j].resource[2] = 0;
        }
    }
}
