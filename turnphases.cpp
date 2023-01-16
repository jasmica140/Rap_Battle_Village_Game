#include "villagegame.h"

void friendtroop(int playno){

    for(int i=0; i<(int)village[playno]->army.size(); i++){

        //if army made it home
        if(village[playno]->army[i]->loc[0] == village[playno]->loc[0]
        && village[playno]->army[i]->loc[1] == village[playno]->loc[1]
        && village[playno]->army[i]->comeHome){
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

    for(int cnt=0; cnt<(int)village[playno]->army.size(); cnt++){

        for(int v=0; v<(int)village.size(); v++){
            if(village[v]->id == village[playno]->army[cnt]->target){
                villno = v;
                break;
            }
        }

        //if army successfully arrived to target
        if(village[playno]->army[cnt]->loc[0] == village[villno]->loc[0]
        && village[playno]->army[cnt]->loc[1] == village[villno]->loc[1]
        && !village[playno]->army[cnt]->comeHome) {

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
                if (village[playno]->real) {
                    alertcli(playno, "fail");
                }
                village[playno]->army[cnt]->target = village[playno]->id;

            }else {

                if(village[villno]->troops.empty()){
                    success = true;
                }else{

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
                            village[playno]->army[cnt]->refresharmy();
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
                }

                //update village to not under attack
                village[villno]->attack = false;

                if (success) {

                    //sum of surviving player troops attack
                    pattack = village[playno]->army[cnt]->attack;

                    //reduce village health
                    village[villno]->health -= pattack;

                    //army carrying capacity
                    int carryCap = village[playno]->army[cnt]->carryCap;

                    if (village[playno]->real) {  //real player

                        alertcli(playno, "success");

                        loop6:
                        refreshcli(playno);
                        //steal resources
                        for (int res = 0; res < 3; res++) {

                            mvwprintw(win, texty - 2, textx + 30, "BATTLE SUCCESSFUL!");
                            mvwprintw(win, texty - 1, textx, "Carrying Capacity: %d", carryCap);
                            mvwprintw(win, texty, textx, "Player %d's resources: connections x%d   grub x%d    dollaz x%d",
                                      village[villno]->id+1, village[villno]->resource[0]->amount,
                                      village[villno]->resource[1]->amount, village[villno]->resource[2]->amount);

                            mvwprintw(win, texty + 2, textx, "How many %s are you taking:",
                                      village[villno]->resource[res]->type.c_str());

                            int maxres;
                            if (carryCap < village[villno]->resource[res]->amount) {
                                maxres = carryCap;
                            } else {
                                maxres = village[villno]->resource[res]->amount;
                            }

                            string r[(maxres+5) / 5];
                            for (int i = 0; i < (maxres+5) / 5; i++) {
                                r[i] = {to_string(i * 5)};
                            }

                            village[playno]->army[cnt]->resource[res] =
                                    (options((maxres+5) / 5, r, texty + 3, textx, true) - 1) * 5;
                            carryCap -= village[playno]->army[cnt]->resource[res];
                            refreshcli(playno);
                        }

                        mvwprintw(win, texty, textx, "You are taking:");
                        mvwprintw(win, texty + 1, textx, "connections x%d   grub x%d    dollaz x%d",
                                  village[playno]->army[cnt]->resource[0], village[playno]->army[cnt]->resource[1],
                                  village[playno]->army[cnt]->resource[2]);
                        mvwprintw(win, texty + 3, textx, "Choose resources again?");
                        string choices[] = {"Nah cuz, i'm good.", "Yeah fool, this looks wack."};
                        int choice = (options(2, choices, texty + 4, textx, false));
                        if (choice == 2) {
                            carryCap = village[playno]->army[cnt]->carryCap;
                            goto loop6;
                        }

                    } else {  //AI player

                        int maxCarryCap = carryCap; //max carrying capacity

                        //steal resources in multiples of 5
                        for (int res = 0; res < 3; res++) {
                            if (village[villno]->resource[res]->amount > 5 && maxCarryCap > 5) {
                                if (carryCap > village[villno]->resource[res]->amount) {
                                    maxCarryCap = village[villno]->resource[res]->amount;
                                }else{
                                    maxCarryCap = carryCap;
                                }
                                int take = (rand() % (maxCarryCap / 5));
                                village[playno]->army[cnt]->resource[res] = take*5;
                                carryCap -= village[playno]->army[cnt]->resource[res];
                            }
                        }
                    }

                    village[villno]->resource[0]->amount -= village[playno]->army[cnt]->resource[0];
                    village[villno]->resource[1]->amount -= village[playno]->army[cnt]->resource[1];
                    village[villno]->resource[2]->amount -= village[playno]->army[cnt]->resource[2];

                    //surviving troops march back home
                    village[playno]->army[cnt]->target = village[playno]->id;
                    village[playno]->army[cnt]->comeHome = true;

                    if (village[villno]->health <= 0) {

                        if (villno<playno) {
                            playno--;
                        }

                        alertcli(villno, "destroy");
                        //delete player
                        deleteplayer(villno);
                    }

                } else {
                    //delete army
                    village[playno]->army.erase(village[playno]->army.begin() + cnt);
                    if (village[playno]->real) {
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

    for(int i=0; i<(int)village[playno]->rbuild.size(); i++) {

        if (village[playno]->rbuild[i]->type == "connections") {
            village[playno]->resource[0]->amount += village[playno]->rbuild[i]->resOutput;
        } else if (village[playno]->rbuild[i]->type == "grub") {
            village[playno]->resource[1]->amount += village[playno]->rbuild[i]->resOutput;
        } else if (village[playno]->rbuild[i]->type == "dollaz") {
            village[playno]->resource[2]->amount += village[playno]->rbuild[i]->resOutput;
        }
    }
}

int actions(int playno, int roundno) {

    int select;

    if (village[playno]->real) {
        while(true) {

            refreshcli(playno);

            loop:
            mvwprintw(win, texty, textx, "Select an action: ");

            string choices[] = {
                    "1.Build new buildings", "2.Upgrade existing buildings", "3.Train gangstaz",
                    "4.Battle Cities",  "5.Surrender", "6.End turn"
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

                if(trpcnt<maxtroops){
                    if (train(playno) == 1) {
                        goto loop;
                    }
                }else{
                    refreshcli(playno);
                    mvwprintw(win, erry, textx, "Error: Maximum gangsta limit reached!");
                    goto loop;
                }

            } else if (select == 4) { //attack village

                if ((int)village[playno]->army.size() < 3) {
                    if (attack(playno) == 1) {
                        goto loop;
                    }
                } else {
                    refreshcli(playno);
                    mvwprintw(win, erry, textx, "Error: Maximum crew limit reached!");
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
            if(trpcnt<maxtroops){
                AItrain(playno);
            }
            //attack
            if ((int)village[playno]->army.size() < 3) {
                AIattack(playno);
            }

        }
        //end turn
    }

    return playno;
}