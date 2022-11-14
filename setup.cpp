#include "villagegame.h"

int gamesetup(){

    int rplay;      //real players
    int aiplay=0;     //AI players

    wrefresh(win);
    keypad(win,true);

    //boarder
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
        aiplay = options(maxplay-rplay+1,ch,17,67,true)-1;
    }

    int totplay = rplay+aiplay;

    int r=0;
    int ai=0;
    int space=3;
    //no combinations possible for more than 9 players
    if(totplay>9){
        space=2;
    }

    for(int i=0; i<totplay; i++){


        //initialise villages for each player
        loop:
        int rndx = rand() %mapx;
        int rndy = rand() %mapy;

        //different coordinates for each village
        for(int j=0; j<i; j++){
            if(abs(rndx - village[j].loc[0]) <= space){
                if(abs(rndy - village[j].loc[1]) <= space){
                    goto loop;
                }
            }
        }

        int loc[2]={rndx,rndy};

        //random AI/real player order
        int rnd = (rand() %2);

        if(rnd==0){
            //if real player limit is not reached
            if(r!=rplay){
                village[i] = Village(i,loc, maxhealth, 0, 0, maxtroops,0, false,true);
                r++;
            }else{
                village[i] = Village(i,loc, maxhealth, 0, 0, maxtroops,0, false,false);
                ai++;
            }
        }else{
            //if AI player limit is not reached
            if(ai!=aiplay){
                village[i] = Village(i,loc, maxhealth, 0, 0, maxtroops,0, false,false);
                ai++;
            }else{
                village[i] = Village(i,loc, maxhealth, 0, 0, maxtroops,0, false, true);
                r++;
            }
        }
        map[rndx][rndy].status = "  V  ";


        //initialise resources for each player
        resource[i][0] = Resource("tools", 500);
        resource[i][1] = Resource("food", 500);
        resource[i][2] = Resource("money", 500);
        resource[i][3] = Resource("elixir", 0);


        //initialise troops for each player
        for(int j=0; j<maxtroops; j++){
            troops[i][j] = Troops(15,0,20,0,0,"untrained",loc);
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

    int players = totplay;

    return players;
}

void deleteplayer(int playno, int totplay){

    for(int i=playno; i<(totplay-1); i++){

        //delete village
        village[i] = village[i+1];

        //delete troops
        for(int j=0; j<maxtroops; j++){
            troops[i][j] = troops[i+1][j];
        }

        //delete resources
        for(int j=0; j<4; j++){
            resource[i][j] = resource[i+1][j];
        }

        //delete resource buildings
        for(int j=0; j<maxrbuild; j++){
            rbuild[i][j] = rbuild[i+1][j];
        }

        //delete training buildings
        for(int j=0; j<maxtbuild; j++){
            tbuild[i][j] = tbuild[i+1][j];
        }

        //delete armies
        for(int j=0; j<maxarmy; j++){
            army[i][j] = army[i+1][j];
        }
    }
}

