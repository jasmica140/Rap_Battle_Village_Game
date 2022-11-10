#include "villagegame.h"

int *gamesetup(){

    int rplay;      //real players
    int aiplay=0;     //AI players

    wrefresh(win);
    keypad(win,true);

    mvwhline(win, 13, 65, '*', 50);
    mvwhline(win, 18, 65, '*', 51);
    mvwvline(win, 13, 65, '*', 5);
    mvwvline(win, 13, 115,'*', 5);

    //ask user for player amounts
    mvwprintw(win,14,67,"Number of real players:");
    string choices[maxplay];
    for(int i=0; i<maxplay; i++){
        choices[i] = {to_string(i+1)};
    }
    rplay = options(maxplay,choices,15,67,true);

    //ask user for number of AI players
    if(rplay!=15){
        mvwprintw(win,16,67,"Number of AI players:");
        string ch[maxplay-rplay+1];
        for(int i=0; i<maxplay-rplay+1; i++){
            ch[i] = {to_string(i)};
        }
        aiplay = options(maxplay-rplay,ch,17,67,true)-1;
    }

    int totplay = rplay+aiplay;


    for(int i=0; i<totplay; i++){

        //initialise villages for each player

        int rndx = 1 + (rand() %mapx);
        int rndy = 1 + (rand() %mapy);
        int loc[2]={rndx,rndy};

        if(i<rplay){
            village[i] = Village(loc, maxhealth, 0, 0, maxtroops,0, true);
        }else{
            village[i] = Village(loc, maxhealth, 0, 0, maxtroops,0, false);
        }
        map[rndx][rndy].status = "  V  ";


        //initialise resources for each player
        resource[i][0] = Resource("tools", 500);
        resource[i][1] = Resource("food", 500);
        resource[i][2] = Resource("money", 500);
        resource[i][3] = Resource("elixir", 0);


        //initialise troops for each player
        for(int j=0; j<maxtroops; j++){
            troops[i][j] = Troops(15,0,0,0,0,"stationed","untrained",loc);
        }

        //initialise resource buildings
        for(int j=0; j<maxrbuild; j++){
            rbuild[i][j] = ResourceBuildings("undefined",0,0);
        }

        //initialise training buildings
        for(int j=0; j<maxtbuild; j++){
            tbuild[i][j] = TroopBuildings("undefined");
        }
    }

    int players[] = {rplay,aiplay};

    return players;
}

