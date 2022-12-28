#include "villagegame.h"

int gamesetup(){

    startcli();

    int rplay;      //real players
    int aiplay=0;     //AI players

    wrefresh(win);
    keypad(win,true);

    //boarder
    wattron(win,COLOR_PAIR(1));
    mvwhline(win, 13, 57, '*', 50);
    mvwhline(win, 18, 57, '*', 51);
    mvwvline(win, 13, 57, '*', 5);
    mvwvline(win, 13, 107,'*', 5);

    //ask user for player amounts
    wattron(win,COLOR_PAIR(2));
    mvwprintw(win,14,59,"Number of real players:");
    string choices[maxplay];
    for(int i=0; i<maxplay; i++){
        choices[i] = {to_string(i+1)};
    }
    wattron(win,COLOR_PAIR(3));
    rplay = options(maxplay,choices,15,59,true);

    //ask user for number of AI players
    if(rplay!=15){
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win,16,59,"Number of AI players:");
        string ch[maxplay-rplay+1];
        for(int i=0; i<maxplay-rplay+1; i++){
            ch[i] = {to_string(i)};
        }
        wattron(win,COLOR_PAIR(3));
        aiplay = options(maxplay-rplay+1,ch,17,59,true)-1;
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
        village[i]->addres(Resource("grub", 500));
        village[i]->addres(Resource("dollaz", 500));
    }

    int players = totplay;

    return players;
}


void gameloop(){

    gamesetup();

    int roundno = 1;
    bool real=false;

    while(village.size() > 1){ //win condition

        for(int playno=0; playno<village.size(); playno++){
            playno = turnphase(playno,roundno);

            for(auto & i : village){
                if(i->preal){
                    real=true;
                }
            }

            if(!real){

                while(village.size()>1){
                    int healthidx = 0;
                    int minhealth = village[0]->health;
                    for(int idx=1; idx<village.size(); idx++){
                        if(village[idx]->health<minhealth) {
                            minhealth = village[idx]->health;
                            healthidx = idx;
                        }
                    }
                    deleteplayer(healthidx);
                }
                goto label;

            }else{
                real=false;
            }

            if(village.size()==1){
                goto label;
            }
        }

        for(int i=0; i<village.size(); i++){
            for(int j=0; j<village[i]->army.size(); j++){
                marching(i, j, village[i]->army[j]->target, village[i]->army[j]->speed);
            }
        }

        roundno = endround(roundno);
        startround(roundno);
    }

    label:
    alertcli(0,"winner");
}


