#include "villagegame.h"

int *gamesetup(){

    int rplay;      //real players
    int aiplay;     //AI players

    wrefresh(win);
    keypad(win,true);

    //ask user for player amounts
    loop1:
    mvwprintw(win,texty,1,"Please provide the number of players:");
    rplay = wgetch(win)-48;

    if(rplay<1){
        mvwprintw(win,texty+1,1,"At least one player required!" );
        goto loop1;
    }

    loop2:
    mvwprintw(win,texty+2,1,"Please provide the number of AI players:");
    aiplay= wgetch(win)-48;

    if(aiplay<0){
        mvwprintw(win,texty+3,1,"Number must be zero or greater!" );
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
        resource[i][0] = Resource("tools",500);
        resource[i][1] = Resource("food",500);
        resource[i][2] = Resource("money",500);
    }


    //initialise troops for each player
    for(int i=0; i<totplay; i++) {
        for(int j=0; j<maxtroops; j++){

            int loc[2] = {village[i].loc[0],village[i].loc[1]};
            int res[3] = {0,0,0};

            troops[i][j] = Troops(15,0,0,0,0,"stationed","untrained",false,loc,res);
        }
    }

    //initialise

    int players[] = {rplay,aiplay};

    return players;
}

