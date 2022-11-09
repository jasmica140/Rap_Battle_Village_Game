#include "villagegame.h"

void friendtroop(int playno, int totplay){

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
            for(int j=0; j<army[playno][acnt].troops; j++){
                if(army[playno][acnt].trps[j]->status != "dead"){
                    army[playno][acnt].trps[j]->status = "stationed";
                }
            }

            //decrease village army count
            village[playno].army--;
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

    int select;

    while(true){

        refreshcli(playno);

        loop:
        mvwprintw(win,texty,1,"Select an action: ");

        string choices[] = {
                "1.Build new buildings","2.Upgrade existing buildings","3.Train troops",
                "4.Attack Villages","5.Surrender", "6.End turn"
        };

        select = options(6, choices,texty+1, 1,false);

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

            if(village[playno].army<6){
                if(attack(playno,totplay)==1){
                    goto loop;
                }
            }else{
                refreshcli(playno);
                mvwprintw(win,erry,1,"Error: Maximum army limit reached!");
                goto loop;
            }

        }else if(select==5){ //surrender

            mvwprintw(win,texty,1,"Are you sure you want to surrender?");
            string yn[]={"YES","NO"};
            int ans = options(2,yn,texty+1, 1,false);

            if(ans == 1){
                village[playno].health = 0;
                refreshcli(playno);
                mvwprintw(win,texty,1,"VILLAGE DESTROYED!");
                totplay--;
                break;
            }else{
                goto loop;
            }

        }else if(select==6){ //done
            break;
        }

    }
}