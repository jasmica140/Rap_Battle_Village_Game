#include "villagegame.h"

int *gamesetup(){

    int rplay;      //real players
    int aiplay=0;     //AI players

    loop1:
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
    if(totplay > maxplay){
        clear();
        refresh();
        mvwprintw(win,erry,1,"Error: Max players exceeded!" );
        goto loop1;
    }

    for(int i=0; i<totplay; i++){
        int rndx = 1 + (rand() %mapx);
        int rndy = 1 + (rand() %mapy);
        int loc[2]={rndx,rndy};

        if(i<rplay){
            village[i] = Village(loc, maxhealth, 0, 0, maxtroops,0, true);
        }else{
            village[i] = Village(loc, maxhealth, 0, 0, maxtroops,0, false);
        }

        map[rndx][rndy].status = "  V  ";
    }

    //initialise resources for each player
    for(int i=0; i<totplay; i++){

        //assign 50 of each resource to each player
        resource[i][0] = Resource("tools",500);
        resource[i][1] = Resource("food",500);
        resource[i][2] = Resource("money",500);
    }


    //initialise troops for each player
    for(int i=0; i<totplay; i++) {
        for(int j=0; j<maxtroops; j++){

            int loc[2] = {village[i].loc[0],village[i].loc[1]};
            int res[3] = {0,0,0};

            troops[i][j] = Troops(15,0,0,0,0,"stationed","untrained",loc);
        }
    }

    //initialise

    int players[] = {rplay,aiplay};

    return players;
}

