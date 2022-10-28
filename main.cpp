#include "villagegame.h"

int *gamesetup(){

    int rplay;      //real players
    int aiplay;     //AI players

    //ask user for player amounts
    loop1:
    cout << "Please provide the number of players:" << endl;
    cin >> rplay;

    if(rplay<1){
        cout << "At least one player required!" << endl;
        goto loop1;
    }

    loop2:
    cout << "How many AI players would you like?" << endl;
    cin >> aiplay;

    if(aiplay<0){
        cout << "Number must be zero or greater!" << endl;
        goto loop2;
    }

    int players[] = {rplay,aiplay};

    return players;
}

Player *playersetup(){

    int *players = gamesetup();
    int rplay = players[0];
    int aiplay = players[1];
    int totplay = rplay+aiplay;

    string username[totplay];
    Player player[totplay];

    for(int i=0; i<totplay; i++) {

        cout << "Player " << i+1 << " username: ";
        cin >> player[i].username;
        player[i].village = i;
    }

    return player;
}

Village *villagesetup(){

    int *players = gamesetup();
    int rplay = players[0];
    int aiplay = players[1];
    int totplay = rplay+aiplay;

    Village village[totplay];

    //village and resources for each player
    for(int i=0; i<totplay; i++) {

        loop:
        //not evenly spaced yet...fix later
        village[i].x = 1 + (rand() %100);
        village[i].y = 1 + (rand() %100);

        //different coordinates for each village
        for(int j=0; j<i; j++){
            if(village[i].x == village[j].x){
                if(village[i].y == village[j].y){
                    goto loop;
                }
            }
        }

        village[i].health = maxhealth;
        village[i].tbuildings = 0;
        village[i].rbuildings = 0;
        village[i].troops = 25;
        village[i].index = i;

        if(i<rplay){
            village[i].ptype = true;
        }else{
            village[i].ptype = false;
        }

        map[village[i].x][village[i].y] = "V";      //assign village location in map
    }

    return village;
}

Resource **resourcesetup(){

    int *players = gamesetup();
    int rplay = players[0];
    int aiplay = players[1];
    int totplay = rplay+aiplay;

    Resource **resource;

    Player *player = playersetup();

    //resources for each player
    for(int i=0; i<totplay; i++) {

        //assign 50 of each resource to each player
        resource[i][0].player = player[i].username;
        resource[i][0].type = "tools";
        resource[i][0].amount = 50;

        resource[i][1].player = player[i].username;
        resource[i][1].type = "spinach";
        resource[i][1].amount = 50;

        resource[i][2].player = player[i].username;
        resource[i][2].type = "tv";
        resource[i][2].amount = 50;
    }
    return resource;
}

void earnres(int playno){

    Village *village = villagesetup();
    Resource **resource = resourcesetup();

    int resbno = village[playno].rbuildings;
    ResourceBuidlings resbuild[resbno];

    for(int i=0; i<resbno; i++){
        if(resbuild[i].village==playno){
            if(resbuild[i].level==1){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+50;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+50;
                }else if(resbuild[i].type=="money"){
                    resource[playno][2].amount=+50;
                }
            }else if(resbuild[i].level==2){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+75;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+75;
                }else if(resbuild[i].type=="money"){
                    resource[playno][2].amount=+75;
                }
            }else if(resbuild[i].level==3){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+120;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+120;
                }else if(resbuild[i].type=="money"){
                    resource[playno][2].amount=+120;
                }
            }else if(resbuild[i].level==4){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+175;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+175;
                }else if(resbuild[i].type=="tv"){
                    resource[playno][2].amount=+175;
                }
            }else if(resbuild[i].level==5){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+250;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+250;
                }else if(resbuild[i].type=="money"){
                    resource[playno][2].amount=+250;
                }
            }
        }
    }
}

void actions(int playno){

    Resource **resource = resourcesetup();
    Village *village = villagesetup();

    int resbno = village[playno].rbuildings;
    int troopbno = village[playno].tbuildings;
    int *players = gamesetup();
    int totplay = players[0]+players[1];

    ResourceBuidlings resbuild[totplay][resbno];
    TroopBuidlings tbuild[totplay][troopbno];

    int select=0;
    int cost;

    int funds = resource[playno][2].amount;
    int food = resource[playno][1].amount;

    int trooptot = village[playno].troops;
    Troops troops[totplay][trooptot];


    while(select!=6){

        loop:
        cout << "Please select one of the following options: \n"
                "1.Build new buildings\n"
                "2.Upgrade existing buildings\n"
                "3.Train troops\n"
                "4.Attack Villages\n"
                "5.Surrender\n"
                "6.End turn\n";
        cin >> select;

        if(select<1 || select>6){
            cout << "Option unavailable!" << endl;
            goto loop;
        }

        if(select==1){ //build buildings

            int bno;

            loop1:
            cout << "What type of building would you like to build?\n"
                    "1.Resource-generating\n"
                    "2.Troop-training" << endl;
            cin >> select;

            if(select!=1 && select!=2){
                cout << "Option unavailable!" << endl;
                goto loop1;
            }

            loop2:
            cout << "How many buildings would you like to build?" << endl;
            cin >> bno;

            if(bno<1){
                cout << "At least one building required!" << endl;
                goto loop2;
            }

            cost = bno*35;
            if(resource[playno][2].amount<cost){
                cout << "Insufficient funds!\nPlease select another option:"<<endl;
                goto loop;
            }

            if(select==1){ //resource
                village[playno].rbuildings+=bno;
            }else{ //training
                village[playno].tbuildings+=bno;
            }

            funds-=cost;

        }else if(select==2){ //upgrade buildings

            int totbuild = resbno+troopbno;

            if(totbuild==0){
                cout << "You have no buildins to upgrade yet!" << endl;
                goto loop;
            }

            cout << "Which building would you like to upgrade?" << endl;
            int count;
            int real[totbuild];
            int j=0;

            for(count=0; count<resbno; count++){
                real[count]=j;
                if(resbuild[playno][count].level<5){
                    cout << count+1 << ". Resource-generating - level " << resbuild[playno][count].level << " - type " << resbuild[playno][count].type << endl;
                }else{
                    count-=1;
                }
                j++;
            }
            for(int i=count; i<totbuild; i++){
                real[i]=j;
                if(resbuild[playno][i].level<5){
                    cout << i+1 << ". Troop-training - level " << tbuild[playno][i].level << " - type " << tbuild[playno][i].type << endl;
                }else{
                    i-=1;
                }
                j++;
            }
            cin >> select;

            if(select>totbuild || select<1){
                cout << "Option unavailable!" << endl;
            } else if(funds<15){
                cout << "Insufficient funds!\nPlease select another option:"<<endl;
                goto loop;
            }else{
                if(select<count+1){
                    resbuild[playno][real[select]].level++;
                }else{
                    tbuild[playno][real[select]].level++;
                }
            }

            funds-=cost;

        }else if(select==3){ //train troops

            loop3:
            cout << "Which troops would you like to train?\n";

            int real[trooptot];
            int j=0;
            int troopno;

            for(int i=0; i<trooptot; i++){
                real[i]=j;
                if(troops[playno][i].type!="master"){
                    cout << i+1 << ". " << troops[playno][i].type << endl;
                }
                if(troops[playno][i].type=="rookie"){

                }
                j++;
            }
            cin >> select;

            cout << "How many " << troops[playno][real[select]].type << "troops would you like to upgrade?" << endl;
            cin >> troopno;

            int k=0;
            for(int i=0; i<trooptot; i++){
                if(troops[playno][i].type==troops[playno][real[select]].type){
                    k++;
                }
            }
            if(troopno>k){
                cout << "Not enough troops!" << endl;
                goto loop3;
            } else if(food<15*troopno){
                cout << "Not enough resources!\nPlease select another option:" << endl;
                goto loop;
            }else{

            }




        }else if(select==4){ //attack village

        }else if(select==5){ //surrender

        }else if(select==6){ //done

        }









    }


}

void turnphase(int playno){

    //friendly troop arrival

    //enemy troop arrival

    //resource earning
    earnres(playno);

    //player actions

    //next player

}

void wincond(){}

void marching(){}

void endround(){}

void startround(){}


void gameloop(){

    int *players = gamesetup();
    int rplay = players[0];
    int aiplay = players[1];
    int totplay = rplay+aiplay;


    cout << rplay << endl;
    cout << aiplay << endl;

    int playno = 0;
    while(totplay > 1){

        turnphase(playno);

        playno++;
    }
}

int main() {

    gameloop();
    return 0;
}
