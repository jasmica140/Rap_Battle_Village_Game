#include "villagegame.h"

void friendtroop(int playno){

    for(int i=0; i<village[playno]->army.size(); i++){

        //if army made it home
        if(village[playno]->army[i]->loc[0] == village[playno]->loc[0] && village[playno]->army[i]->loc[1] == village[playno]->loc[1]){
            //transfer resources obtained to player
            resource[playno][0].amount += village[playno]->army[i]->resource[0];
            resource[playno][1].amount += village[playno]->army[i]->resource[1];
            resource[playno][2].amount += village[playno]->army[i]->resource[2];

            //bring troops home
            while(!village[playno]->army[i]->troops.empty()){
                village[playno]->addtroops(*village[playno]->army[i]->troops[0]);
                village[playno]->army[i]->troops.erase(village[playno]->army[i]->troops.begin());
            }

            //remove army
            village[playno]->army.erase(village[playno]->army.begin()+i);
            i--;
        }
    }
}

void enemytroop(int playno){

    int villno;

    for(int cnt=0; cnt<village[playno]->army.size(); cnt++){

        for(int v=0; v<village.size(); v++){
            if(village[v]->idx == village[playno]->army[cnt]->target){
                villno = v;
                break;
            }
        }

        //if army successfully arrived to target
        if(village[playno]->army[cnt]->loc[0] == village[villno]->loc[0] && village[playno]->army[cnt]->loc[1] == village[villno]->loc[1]){

            int res[] = {0,0,0};        //current resources carried

            int phealth = village[playno]->army[cnt]->health;        //sum of player troops health
            int pattack = village[playno]->army[cnt]->attack;

            int vattack=0;
            for(auto & troop : village[villno]->troops){
                vattack += troop->attack;        //sum of target village troops attack
            }

            int rnd;
            //until player troop health = villager troops health
            while(phealth>vattack) {

                //kill player troop
                if(!village[playno]->army[cnt]->troops.empty()){
                    rnd = (rand() %(int)village[playno]->army[cnt]->troops.size());
                    village[playno]->army[cnt]->troops.erase(village[playno]->army[cnt]->troops.begin()+rnd);
                }

                //kill villager troop
                if(!village[villno]->troops.empty()){
                    rnd = (rand() %(int)village[villno]->troops.size());
                    village[villno]->troops.erase(village[villno]->troops.begin() + rnd);
                }

                //recalculate health and attack
                village[playno]->army[cnt]->refresharmy(*village[playno]->army[cnt],res, village[villno]->idx);
                phealth = village[playno]->army[cnt]->health;        //sum of player troops health

                vattack = 0;
                for(auto & troop : village[villno]->troops){
                    vattack += troop->attack;    //sum of villager troops attack
                }
            }

            //if at least one troop in player's army survives = success
            bool success;
            if(!village[playno]->army[cnt]->troops.empty()){
                success=true;
            }else{
                success=false;
            }

            //update village to not under attack
            village[villno]->attack = false;

            if(success){

                //sum of surviving player troops attack
                pattack = village[playno]->army[cnt]->attack;

                //reduce village health
                village[villno]->health-= pattack;

                //army carrying capacity
                int carrycap = village[playno]->army[cnt]->carrycap;

                int tools;
                int food;
                int money;

                if(village[playno]->preal){  //real player

                    alertcli(playno,"success");

                    loop6:
                    mvwprintw(win,texty-1,30,"ATTACK SUCCESSFUL!");
                    mvwhline(win, texty, 1, '=', 79);

                    //steal resources
                    mvwprintw(win,texty+2,1,"Your carrying capacity is %d!", carrycap);
                    mvwprintw(win,texty+3,1,"How many of the following resources would you like to take:");

                    mvwprintw(win,texty+4,1,"Tools:");
                    string tls[resource[villno][0].amount/5];
                    for(int i=0; i<resource[villno][0].amount/5; i++){
                        tls[i] = {to_string(i*5)};
                    }
                    tools = (options(resource[villno][0].amount/5,tls,texty+5,1,true)-1)*5;

                    refreshcli(playno);
                    mvwprintw(win,texty+2,1,"Your carrying capacity is %d!", carrycap);
                    mvwprintw(win,texty+3,1,"How many of the following resources would you like to take:");

                    mvwprintw(win,texty+4,1,"Food: ");
                    string fd[resource[villno][1].amount/5];
                    for(int i=0; i<resource[villno][1].amount/5; i++){
                        fd[i] = {to_string(i*5)};
                    }
                    food = (options(resource[villno][1].amount/5,fd,texty+5,1,true)-1)*5;

                    refreshcli(playno);
                    mvwprintw(win,texty+2,1,"Your carrying capacity is %d!", carrycap);
                    mvwprintw(win,texty+3,1,"How many of the following resources would you like to take:");

                    mvwprintw(win,texty+4,1,"Money:");
                    string mny[resource[villno][2].amount/5];
                    for(int i=0; i<resource[villno][2].amount/5; i++){
                        mny[i] = {to_string(i*5)};
                    }
                    money = (options(resource[villno][2].amount/5,mny,texty+5,1,true)-1)*5;

                    if(tools+food+money>carrycap){
                        refreshcli(playno);
                        mvwprintw(win,erry,1,"Error: Max carrying capacity exceeded! Pick resources again.");
                        goto loop6;
                    }
                }else{  //AI player

                    //steal resources
                    loop1:
                    tools=0;
                    if(resource[villno][0].amount>5){
                        tools = (rand()% (int)floor(resource[villno][0].amount/5));
                        tools *= 5;
                    }
                    food=0;
                    if(resource[villno][1].amount>5){
                        food = (rand()% (int)floor(resource[villno][1].amount/5));
                        food *= 5;
                    }
                    money=0;
                    if(resource[villno][2].amount>5){
                        money = (rand()% (int)floor(resource[villno][2].amount/5));
                        money *= 5;
                    }

                    //max carrying capacity exceeded
                    if(tools+food+money>carrycap){
                        refreshcli(playno);
                        goto loop1;
                    }
                }

                resource[villno][0].amount -= tools;
                resource[villno][1].amount -= food;
                resource[villno][2].amount -= money;

                village[playno]->army[cnt]->resource[0] = tools;
                village[playno]->army[cnt]->resource[1] = food;
                village[playno]->army[cnt]->resource[2] = money;

                //surviving troops march back home
                village[playno]->army[cnt]->target = village[playno]->idx;

                if(village[villno]->health<=0){

                    refreshcli(playno);
                    mvwprintw(win,erry,1,"PLAYER %d's VILLAGE DESTROYED!");

                    //delete player
                    deleteplayer(villno);
                }

            }else{
                //delete army
                village[playno]->army.erase(village[playno]->army.begin()+cnt);
                alertcli(playno,"fail");
                cnt--;
            }
        }
    }
}


void earnres(int playno){

    int resbno = village[playno]->rbuildings;

    for(int i=0; i<resbno; i++){

        if(rbuild[playno][i].level==1){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount+=50;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount+=50;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount+=50;
            }
        }else if(rbuild[playno][i].level==2){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount+=75;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount+=75;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount+=75;
            }
        }else if(rbuild[playno][i].level==3){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount+=120;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount+=120;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount+=120;
            }
        }else if(rbuild[playno][i].level==4){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount+=175;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount+=175;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount+=175;
            }
        }else if(rbuild[playno][i].level==5){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount+=250;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount+=250;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount+=250;
            }
        }
    }
}

void actions(int playno, int roundno) {

    int select;

    while (true) {

        if (village[playno]->preal) {

            refreshcli(playno);

            loop:
            mvwprintw(win, texty, 1, "Select an action: ");

            string choices[] = {
                    "1.Build new buildings", "2.Upgrade existing buildings", "3.Train troops",
                    "4.Attack Villages", "5.Resurrect troops", "6.Surrender", "7.End turn"
            };

            select = options(7, choices, texty + 2, 1, false);

            refreshcli(playno);

            if (select == 1) { //build buildings

                if (build(playno) == 1) {
                    goto loop;
                }

            } else if (select == 2) { //upgrade buildings

                if (upgrade(playno) == 1) {
                    goto loop;
                }

            } else if (select == 3) { //train troops

                if (train(playno) == 1) {
                    goto loop;
                }

            } else if (select == 4) { //attack village

                if (village[playno]->army.size() < 6) {
                    if (attack(playno) == 1) {
                        goto loop;
                    }
                } else {
                    refreshcli(playno);
                    mvwprintw(win, erry, 1, "Error: Maximum army limit reached!");
                    goto loop;
                }

            } else if (select == 5) { //resurrect

                if (resurrect(playno) == 1) {
                    goto loop;
                }

            } else if (select == 6) { //surrender

                mvwprintw(win, texty, 1, "Are you sure you want to surrender?");
                string yn[] = {"YES", "NO"};
                int ans = options(2, yn, texty + 1, 1, false);

                if (ans == 1) {

                    //delete player
                    deleteplayer(playno);

                    refreshcli(playno);
                    alertcli(playno,"destroy");
                    break;

                } else {
                    refreshcli(playno);
                    goto loop;
                }

            } else if (select == 7) { //done

                break;
            }

        } else {

            //if first round
            if (roundno == 1) {
                AIround1(playno);               //build+upgrade+train
                AIattack(playno);               //attack
                break;                          //end turn
            } else {

                //count army troops
                int armytrps=0;
                for(auto & i : village[playno]->army){
                    armytrps+=i->troops.size();
                }

                //build buildings
                AIbuild(playno);
                //upgrade buildings
                AIupgrade(playno);
                //train troops
                AItrain(playno);
                //attack
                AIattack(playno);
                //ressurect troops
                int dead = 50-village[playno]->troops.size()-armytrps;
                //if dead troops and sufficient funds
                if(dead!=0 && resource[playno][3].amount>=45){
                    AIresurrect(playno, dead);
                }
            }
            //end turn
            break;
        }
    }
}