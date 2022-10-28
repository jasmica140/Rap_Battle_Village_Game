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
        village[i].troopbuildings = 0;
        village[i].resbuildings = 0;
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

    int resbno = village[playno].resbuildings;
    ResourceBuidlings resbuild[resbno];

    for(int i=0; i<resbno; i++){
        if(resbuild[i].village==playno){
            if(resbuild[i].level==1){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+50;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+50;
                }else if(resbuild[i].type=="tv"){
                    resource[playno][2].amount=+50;
                }
            }else if(resbuild[i].level==2){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+75;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+75;
                }else if(resbuild[i].type=="tv"){
                    resource[playno][2].amount=+75;
                }
            }else if(resbuild[i].level==3){
                if(resbuild[i].type=="tools"){
                    resource[playno][0].amount=+120;
                }else if(resbuild[i].type=="spinach"){
                    resource[playno][1].amount=+120;
                }else if(resbuild[i].type=="tv"){
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
                }else if(resbuild[i].type=="tv"){
                    resource[playno][2].amount=+250;
                }
            }
        }
    }
}

void actions(int playno){

    //build buildings

    //upgrade buildings

    //train troops

    //attack village

    //surrender

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
