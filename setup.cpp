#include "villagegame.h"

int gamesetup(){

    int rplay;      //real players
    int aiplay=0;     //AI players

    wrefresh(win);
    keypad(win,true);

    //boarder
    wattron(win,COLOR_PAIR(1));
    mvwhline(win, 13, 65, '*', 50);
    mvwhline(win, 18, 65, '*', 51);
    mvwvline(win, 13, 65, '*', 5);
    mvwvline(win, 13, 115,'*', 5);

    //ask user for player amounts
    wattron(win,COLOR_PAIR(2));
    mvwprintw(win,14,67,"Number of real players:");
    string choices[maxplay];
    for(int i=0; i<maxplay; i++){
        choices[i] = {to_string(i+1)};
    }
    wattron(win,COLOR_PAIR(3));
    rplay = options(maxplay,choices,15,67,true);

    //ask user for number of AI players
    if(rplay!=15){
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win,16,67,"Number of AI players:");
        string ch[maxplay-rplay+1];
        for(int i=0; i<maxplay-rplay+1; i++){
            ch[i] = {to_string(i)};
        }
        wattron(win,COLOR_PAIR(3));
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
            if(abs(rndx - village[j]->loc[0]) <= space){
                if(abs(rndy - village[j]->loc[1]) <= space){
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

                auto v = make_unique<Village>(i,loc, maxhealth, false, true);
                village.push_back(std::move(v));
                r++;

            }else{

                auto v = make_unique<Village>(i,loc, maxhealth, false, false);
                village.push_back(std::move(v));
                ai++;
            }
        }else{
            //if AI player limit is not reached
            if(ai!=aiplay){

                auto v = make_unique<Village>(i,loc, maxhealth, false, false);
                village.push_back(std::move(v));
                ai++;
            }else{

                auto v = make_unique<Village>(i,loc, maxhealth, false, true);
                village.push_back(std::move(v));
                r++;
            }
        }
        map[rndx][rndy].status = "  V  ";

        //initialise resources for each player
        village[i]->addres(Resource("tools", 500));
        village[i]->addres(Resource("food", 500));
        village[i]->addres(Resource("money", 500));
    }

    int players = totplay;

    return players;
}

void gameloop(){

    int totplay = gamesetup();

    int playno = 0;
    int roundno = 1;

    while(village.size() > 1){ //win condition

        for(int i=0; i<village.size(); i++, playno++){
            turnphase(playno,roundno);

            if(village.size()<totplay){
                playno -= (totplay - village.size());
                totplay = village.size();
                i--;
            }

            if(village.size()==1){
                break;
            }
        }

        for(int i=0; i<village.size(); i++){
            for(int j=0; j<village[i]->army.size(); j++){
                marching(i, j, village[i]->army[j]->target, village[i]->army[j]->speed);
            }
        }

        roundno = endround(roundno);
        playno = 0; //start from first surviving player
        startround(playno);
    }
}


