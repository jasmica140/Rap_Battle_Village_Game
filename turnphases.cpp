#include "villagegame.h"

void friendtroop(int playno){

    for(int i=0; i<village[playno]->army.size(); i++){

        //if army made it home
        if(village[playno]->army[i]->loc[0] == village[playno]->loc[0] && village[playno]->army[i]->loc[1] == village[playno]->loc[1]){
            //transfer resources obtained to player
            village[playno]->resource[0]->amount += village[playno]->army[i]->resource[0];
            village[playno]->resource[1]->amount += village[playno]->army[i]->resource[1];
            village[playno]->resource[2]->amount += village[playno]->army[i]->resource[2];

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

int enemytroop(int playno){

    int villno;

    for(int cnt=0; cnt<village[playno]->army.size(); cnt++){

        for(int v=0; v<village.size(); v++){
            if(village[v]->idx == village[playno]->army[cnt]->target){
                villno = v;
                break;
            }
        }

        //if army successfully arrived to target
        if(village[playno]->army[cnt]->loc[0] == village[villno]->loc[0] && village[playno]->army[cnt]->loc[1] == village[villno]->loc[1]) {

            int phealth = village[playno]->army[cnt]->health;        //sum of player troops health
            int pattack = village[playno]->army[cnt]->attack;

            int vattack = 0;
            for (auto &troop: village[villno]->troops) {
                vattack += troop->attack;        //sum of target village troops attack
            }

            int rnd;
            bool success = true;

            if (phealth <= vattack) {
                village[villno]->attack = false;
                if (village[playno]->preal) {
                    alertcli(playno, "fail");
                }
                village[playno]->army[cnt]->target = village[playno]->idx;

            } else {

                //until player troop health = villager troops health
                while (phealth > vattack) {

                    //kill player troop
                    if (!village[playno]->army[cnt]->troops.empty()) {
                        rnd = (rand() % (int) village[playno]->army[cnt]->troops.size());
                        village[playno]->army[cnt]->troops.erase(village[playno]->army[cnt]->troops.begin() + rnd);

                        if(village[playno]->army[cnt]->troops.empty()){
                            //no troops left => attack failed
                            success = false;
                            break;
                        }

                        //recalculate health
                        village[playno]->army[cnt]->refresharmy(*village[playno]->army[cnt]);
                        phealth = village[playno]->army[cnt]->health;        //sum of player troops health

                    }

                    //kill villager troop
                    if (!village[villno]->troops.empty()) {
                        rnd = (rand() % (int) village[villno]->troops.size());
                        village[villno]->troops.erase(village[villno]->troops.begin() + rnd);

                        if (village[villno]->troops.empty()){
                            break;
                        }

                        //recalculate attack
                        vattack = 0;
                        for (auto &troop: village[villno]->troops) {
                            vattack += troop->attack;    //sum of villager troops attack
                        }
                    }
                }

                //update village to not under attack
                village[villno]->attack = false;

                if (success) {

                    //sum of surviving player troops attack
                    pattack = village[playno]->army[cnt]->attack;

                    //reduce village health
                    village[villno]->health -= pattack;

                    //army carrying capacity
                    int carrycap = village[playno]->army[cnt]->carrycap;

                    if (village[playno]->preal) {  //real player

                        alertcli(playno, "success");

                        loop6:
                        //steal resources
                        for (int res = 0; res < 3; res++) {

                            mvwprintw(win, texty - 2, textx + 30, "ATTACK SUCCESSFUL!");
                            mvwprintw(win, texty - 1, textx, "Carrying Capacity: %d", carrycap);
                            mvwprintw(win, texty, textx, "Player %d's resources: tools x%d   food x%d    money x%d",
                                      village[villno]->idx, village[villno]->resource[0]->amount,
                                      village[villno]->resource[1]->amount, village[villno]->resource[2]->amount);

                            mvwprintw(win, texty + 2, textx, "How many %s are you taking:",
                                      village[villno]->resource[res]->type.c_str());

                            int maxres;
                            if (carrycap < village[villno]->resource[res]->amount) {
                                maxres = carrycap;
                            } else {
                                maxres = village[villno]->resource[res]->amount;
                            }

                            string r[maxres / 5];
                            for (int i = 0; i < maxres / 5; i++) {
                                r[i] = {to_string(i * 5)};
                            }

                            village[playno]->army[cnt]->resource[res] =
                                    (options(maxres / 5, r, texty + 3, textx, true) - 1) * 5;
                            carrycap -= village[playno]->army[cnt]->resource[res];
                            refreshcli(playno);
                        }

                        mvwprintw(win, texty, textx, "You are taking:");
                        mvwprintw(win, texty + 1, textx, "tools x%d   food x%d    money x%d",
                                  village[playno]->army[cnt]->resource[0], village[playno]->army[cnt]->resource[1],
                                  village[playno]->army[cnt]->resource[2]);
                        mvwprintw(win, texty + 3, textx, "Choose resources again?");
                        string choices[] = {"Nah cuz, i'm good", "Yeah man, this looks wack"};
                        int choice = (options(2, choices, texty + 4, textx, false));
                        if (choice == 2) {
                            carrycap = village[playno]->army[cnt]->carrycap;
                            goto loop6;
                        }

                    } else {  //AI player

                        int maxcarrycap = carrycap; //max carrying capacity

                        //steal resources in multiples of 5
                        for (int res = 0; res < 3; res++) {
                            if (village[villno]->resource[res]->amount > 5 && maxcarrycap > 5) {
                                if (maxcarrycap > village[villno]->resource[res]->amount) {
                                    maxcarrycap = village[villno]->resource[res]->amount;
                                }
                                village[playno]->army[cnt]->resource[res] = (rand() % (maxcarrycap / 5));
                                village[playno]->army[cnt]->resource[res] *= 5;
                                maxcarrycap -= village[playno]->army[cnt]->resource[res];
                            }
                        }
                    }

                    village[villno]->resource[0]->amount -= village[playno]->army[cnt]->resource[0];
                    village[villno]->resource[1]->amount -= village[playno]->army[cnt]->resource[1];
                    village[villno]->resource[2]->amount -= village[playno]->army[cnt]->resource[2];

                    //surviving troops march back home
                    village[playno]->army[cnt]->target = village[playno]->idx;

                    if (village[villno]->health <= 0) {

                        if (village[villno]->idx < village[playno]->idx) {
                            playno--;
                        }

                        alertcli(villno, "destroy");
                        //delete player
                        deleteplayer(villno);
                    }

                } else {
                    //delete army
                    village[playno]->army.erase(village[playno]->army.begin() + cnt);
                    if (village[playno]->preal) {
                        alertcli(playno, "fail");
                    }
                    cnt--;
                }
            }
        }
    }

    return playno;
}


void earnres(int playno){

    for(int i=0; i<village[playno]->rbuild.size(); i++) {

        if (village[playno]->rbuild[i]->type == "tools") {
            village[playno]->resource[0]->amount += village[playno]->rbuild[i]->output;
        } else if (village[playno]->rbuild[i]->type == "food") {
            village[playno]->resource[1]->amount += village[playno]->rbuild[i]->output;
        } else if (village[playno]->rbuild[i]->type == "money") {
            village[playno]->resource[2]->amount += village[playno]->rbuild[i]->output;
        }
    }
}

int actions(int playno, int roundno) {

    int select;

    if (village[playno]->preal) {
        while(true) {

            refreshcli(playno);

            loop:
            mvwprintw(win, texty, textx, "Select an action: ");

            string choices[] = {
                    "1.Build new buildings", "2.Upgrade existing buildings", "3.Train troops",
                    "4.Attack Villages",  "5.Surrender", "6.End turn"
            };

            select = options(6, choices, texty + 2, textx, false);

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

                int trpcnt=(int)village[playno]->troops.size();
                for(auto & cnt : village[playno]->army){
                    trpcnt+=cnt->troops.size();
                }

                if(trpcnt<=maxtroops){
                    if (train(playno) == 1) {
                        goto loop;
                    }
                }else{
                    refreshcli(playno);
                    mvwprintw(win, erry, textx, "Error: Maximum troop limit reached!");
                    goto loop;
                }

            } else if (select == 4) { //attack village

                if (village[playno]->army.size() < 4) {
                    if (attack(playno) == 1) {
                        goto loop;
                    }
                } else {
                    refreshcli(playno);
                    mvwprintw(win, erry, textx, "Error: Maximum army limit reached!");
                    goto loop;
                }

            } else if (select == 5) { //surrender

                mvwprintw(win, texty, textx, "Are you sure you want to surrender?");
                string yn[] = {"YES", "NO"};
                int ans = options(2, yn, texty + 1, textx, false);

                if (ans == 1) {

                    alertcli(playno,"destroy");

                    //delete player
                    deleteplayer(playno);
                    playno--;
                    break;

                } else {
                    refreshcli(playno);
                    goto loop;
                }

            } else if (select == 6) { //done

                break;
            }

        }
    } else {

        //if first round
        if (roundno == 1) {
            AIround1(playno);               //build+upgrade+train
            AIattack(playno);               //attack

        } else{

            int trpcnt=(int)village[playno]->troops.size();
            for(auto & cnt : village[playno]->army){
                trpcnt+=cnt->troops.size();
            }

            //build buildings
            AIbuild(playno);
            //upgrade buildings
            AIupgrade(playno);
            //train troops
            if(trpcnt<=maxtroops){
                AItrain(playno);
            }
            //attack
            if (village[playno]->army.size() < 4) {
                AIattack(playno);
            }
        }
        //end turn
    }

    return playno;
}