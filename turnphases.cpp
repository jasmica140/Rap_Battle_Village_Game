#include "villagegame.h"

void friendtroop(int playno, int totplay){

    //for each troop that made it back home
    for(int i=0; i<maxtroops; i++){

        if(troops[playno][i].army && troops[playno][i].status != "dead"){

            troops[playno][i].status = "stationed";                 //set status to stationed
            troops[playno][i].army = false;                 //reset army status

            //transfer resources obtain to player and reset troop resources
            resource[playno][0].amount += troops[playno][i].resource[0];
            troops[playno][i].resource[0]=0;
            resource[playno][1].amount += troops[playno][i].resource[1];
            troops[playno][i].resource[1]=0;
            resource[playno][2].amount += troops[playno][i].resource[2];
            troops[playno][i].resource[2]=0;
        }
    }
}

int enemytroop(int playno, int totplay){

    if(village[playno].health==0){
        village[playno].loc[0]=0;
        village[playno].loc[1]=0;
        totplay--;
    }

    return totplay;
}


void earnres(int playno){

    int resbno = village[playno].rbuildings;

    for(int i=0; i<resbno; i++){

        if(rbuild[playno][i].level==1){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+50;
            }else if(rbuild[playno][i].type=="spinach"){
                resource[playno][1].amount=+50;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+50;
            }
        }else if(rbuild[playno][i].level==2){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+75;
            }else if(rbuild[playno][i].type=="spinach"){
                resource[playno][1].amount=+75;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+75;
            }
        }else if(rbuild[playno][i].level==3){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+120;
            }else if(rbuild[playno][i].type=="spinach"){
                resource[playno][1].amount=+120;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+120;
            }
        }else if(rbuild[playno][i].level==4){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+175;
            }else if(rbuild[playno][i].type=="spinach"){
                resource[playno][1].amount=+175;
            }else if(rbuild[playno][i].type=="tv"){
                resource[playno][2].amount=+175;
            }
        }else if(rbuild[playno][i].level==5){
            if(rbuild[playno][i].type=="tools"){
                resource[playno][0].amount=+250;
            }else if(rbuild[playno][i].type=="spinach"){
                resource[playno][1].amount=+250;
            }else if(rbuild[playno][i].type=="money"){
                resource[playno][2].amount=+250;
            }
        }
    }
}

void actions(int playno, int totplay){

    int select=0;

    while(select!=7){

        refreshcli(playno);

        loop:
        printw("Select an action: \n\n");

        string choices[] = {
                "1.Build new buildings","2.Upgrade existing buildings","3.Train troops",
                "4.Attack Villages","5.Surrender", "6.View map", "7.End turn"
        };

        select = options(7, choices);

        refreshcli(playno);

        if(select==1){ //build buildings

            build(playno);

        }else if(select==2){ //upgrade buildings

           if(upgrade(playno)==1){
               goto loop;
           }

        }else if(select==3){ //train troops

            if(train(playno)==1){
                goto loop;
            }

        }else if(select==4){ //attack village

            int villno;

            cout << "Which village would you like to attack? " << endl;
            cin >> villno;

            int vattack=0;
            int phealth=0;

            for(int i=0; i<maxtroops; i++){
                if(troops[playno][i].status=="army"){
                    phealth += troops[playno][i].health; //sum of player troops health
                }
            }

            for(int i=0; i<maxtroops; i++){
                if(troops[villno][i].status=="stationed"){
                    vattack += troops[villno][i].attack; //sum of villager troops attack
                }
            }

            if(villno>totplay || villno<1){
                cout << "Invalid option!" << endl;
                goto loop;
            }else if(phealth<=vattack){
                cout << "Not enough health to attack village!" << endl;
                goto loop;
            }else{
                attack(playno,villno,totplay);
            }

        }else if(select==5){ //surrender

            string ans;
            cout << "Are you sure you want to surrender? [y/n]" << endl;
            cin >> ans;

            if(ans == "y"){
                village[playno].health = 0;
                cout << "VILLAGE DESTROYED!" << endl;
                totplay--;
                break;
            }else{
                goto loop;
            }

        }else if(select==6){ //show map

            mapcli();

        }else if(select==7){ //done
            break;
        }

    }
}