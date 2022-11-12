#include "villagegame.h"

void friendtroop(int playno){

    int acnt = village[playno].army;
    int i;

    for(i=0; i<acnt; i++){
        //if army made it home
        if(army[playno][i].loc[0] == village[playno].loc[0] && army[playno][i].loc[1] == village[playno].loc[1]){
            //transfer resources obtained to player
            resource[playno][0].amount += army[playno][i].resource[0];
            resource[playno][1].amount += army[playno][i].resource[1];
            resource[playno][2].amount += army[playno][i].resource[2];

            //set status to stationed
            for(int j=0; j<army[playno][i].troops; j++){
                troops[playno][j+village[playno].troops] = army[playno][i].trps[j];
            }

            //decrease village army count
            village[playno].army--;
        }
    }
}

int enemytroop(int playno, int totplay){

    int acnt = village[playno].army;
    int villno;

    for(int cnt=0; cnt<acnt; cnt++){
        villno = army[playno][cnt].target;

        //if army successfully arrived to target
        if(army[playno][cnt].loc[0] == village[villno].loc[0] && army[playno][cnt].loc[1] == village[villno].loc[1]){

            int res[] = {0,0,0};        //current resources carried

            int mspeed = army[playno][acnt].speed;          //army marching speed
            int phealth = army[playno][acnt].health;        //sum of player troops health
            int trooptot = army[playno][acnt].troops;       //no. of troops in army

            int vattack=0;
            for(int i=0; i<village[villno].troops; i++){
                vattack += troops[villno][i].attack;        //sum of target village troops attack
            }

            int pattack = army[playno][acnt].attack;

            int rnd;
            //until player troop health = villager troops health
            while(phealth>vattack) {

                //kill player troop
                if(trooptot>0){
                    rnd = (rand() %trooptot);
                    for(int j=rnd; j<trooptot; j++){
                        army[playno][acnt].trps[j] = army[playno][acnt].trps[j+1];
                    }
                    trooptot--;
                    village[playno].troops--;
                }

                //kill villager troop
                if(village[villno].troops>0){
                    rnd = (rand() %village[villno].troops);
                    for(int j=rnd; j<village[villno].troops; j++){
                        troops[villno][j] = troops[playno][j+1];
                    }
                    village[villno].troops--;
                }

                //recalculate health and attack
                army[playno][acnt] = Army(trooptot, army[playno][acnt].trps, res, villno);

                phealth = army[playno][acnt].health;        //sum of player troops health

                vattack = 0;
                for(int i=0; i<village[villno].troops; i++){
                    vattack += troops[villno][i].attack;    //sum of villager troops attack
                }
            }

            //if at least one troop in player's army survives = success
            bool success;
            for(int i=0; i<trooptot; i++){
                if(army[playno][acnt].troops != 0){
                    success=true;
                    break;
                }else{
                    success=false;
                }
            }

            //update village to not under attack
            village[villno].attack = false;

            if(success){

                refreshcli(playno);

                //update army
                army[playno][acnt] = Army(trooptot, army[playno][acnt].trps, res, villno);

                //sum of surviving player troops attack
                pattack = army[playno][acnt].attack;

                //reduce village health
                village[villno].health-= pattack;

                //army carrying capacity
                int carrycap = army[playno][acnt].carrycap;

                int tools;
                int food;
                int money;

                if(village[playno].preal){  //real player

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
                    tools = options(resource[villno][0].amount/5,tls,texty+5,1,true)-1;

                    mvwprintw(win,texty+2,1,"Your carrying capacity is %d!", carrycap);
                    mvwprintw(win,texty+3,1,"How many of the following resources would you like to take:");
                    refreshcli(playno);

                    mvwprintw(win,texty+4,1,"Food: ");
                    string fd[resource[villno][1].amount/5];
                    for(int i=0; i<resource[villno][1].amount/5; i++){
                        fd[i] = {to_string(i*5)};
                    }
                    food = options(resource[villno][1].amount/5,fd,texty+5,1,true)-1;

                    mvwprintw(win,texty+2,1,"Your carrying capacity is %d!", carrycap);
                    mvwprintw(win,texty+3,1,"How many of the following resources would you like to take:");
                    refreshcli(playno);

                    mvwprintw(win,texty+4,1,"Money:");
                    string mny[resource[villno][2].amount/5];
                    for(int i=0; i<resource[villno][2].amount/5; i++){
                        mny[i] = {to_string(i*5)};
                    }
                    money = options(resource[villno][2].amount/5,mny,texty+5,1,true)-1;

                    if(tools+food+money>carrycap){
                        refreshcli(playno);
                        mvwprintw(win,erry,1,"Error: Max carrying capacity exceeded! Pick resources again.");
                        goto loop6;
                    }
                }else{  //AI player

                    //steal resources
                    loop1:
                    tools=0;
                    if(resource[villno][0].amount>0){
                        tools = 1+ (rand()% resource[villno][0].amount+1);
                    }
                    food=0;
                    if(resource[villno][1].amount>0){
                        food = 1+ (rand()% resource[villno][1].amount+1);
                    }
                    money=0;
                    if(resource[villno][2].amount>0){
                        money = 1+ (rand()% resource[villno][2].amount+1);
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

                res[0] = tools;
                res[1] = food;
                res[2] = money;

                //update army marching speed
                mspeed=army[playno][acnt].speed;

                //surviving troops march back home
                army[playno][acnt] = Army(trooptot, army[playno][acnt].trps, res, playno);

                if(village[villno].health<=0){

                    refreshcli(playno);
                    mvwprintw(win,erry,1,"PLAYER %d's VILLAGE DESTROYED!");

                    //delete player
                    deleteplayer(villno,totplay);
                    totplay--;
                }

            }else{
                village[playno].army--;
            }
        }
    }

    return totplay;
}


void earnres(int playno){

    int resbno = village[playno].rbuildings;

    for(int i=0; i<resbno; i++){

        if(rbuild[playno][i].level==1){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+50;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount=+50;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+50;
            }
        }else if(rbuild[playno][i].level==2){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+75;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount=+75;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+75;
            }
        }else if(rbuild[playno][i].level==3){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+120;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount=+120;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+120;
            }
        }else if(rbuild[playno][i].level==4){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+175;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount=+175;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+175;
            }
        }else if(rbuild[playno][i].level==5){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+250;
            }else if(rbuild[playno][i].type=="food"){
                resource[playno][1].amount=+250;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+250;
            }
        }
    }
}

int actions(int playno, int totplay, int roundno) {

    int select;

    while (true) {

        if (village[playno].preal) {

            refreshcli(playno);

            loop:
            mvwprintw(win, texty, 1, "Select an action: ");

            string choices[] = {
                    "1.Build new buildings", "2.Upgrade existing buildings", "3.Train troops",
                    "4.Attack Villages", "5.Resurrect troops", "6.Surrender", "7.End turn"
            };

            select = options(7, choices, texty + 1, 1, false);

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

                if (village[playno].army < 6) {
                    if (attack(playno, totplay) == 1) {
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
                    deleteplayer(playno, totplay);
                    totplay--;

                    refreshcli(playno);
                    mvwprintw(win, erry, 1, "Update: VILLAGE DESTROYED!");
                    break;

                } else {
                    goto loop;
                }

            } else if (select == 7) { //done
                break;
            }

        } else {

            //if first round
            if (roundno == 1) {
                AIround1(playno);               //build+upgrade+train
                AIattack(playno, totplay);      //attack
                break;                          //end turn
            } else {

                //count army troops
                int armytrps=0;
                for(int i=0; i<village[playno].army; i++){
                    armytrps+=army[playno][i].troops;
                }

                //build buildings
                AIbuild(playno);
                //upgrade buildings
                AIupgrade(playno);
                //train troops
                AItrain(playno);
                //attack
                AIattack(playno, totplay);
                //ressurect troops
                int dead = 50-village[playno].troops-armytrps;
                //if dead troops and sufficient funds
                if(dead!=0 && resource[playno][3].amount>=45){
                    AIresurrect(playno, dead);
                }
            }
            //end turn
            break;
        }
    }
    return totplay;
}