#include "villagegame.h"

int AIround1(int playno){

    //build
    village[playno]->addrbuild(Building("grub", 1, 15));
    village[playno]->rbuild[0]->refreshbuild();
    village[playno]->addrbuild(Building("dollaz", 1, 15));
    village[playno]->rbuild[1]->refreshbuild();
    village[playno]->addtbuild(Building("snoopdawgz",1,35));
    village[playno]->tbuild[0]->refreshbuild();
    village[playno]->addtbuild(Building("biggies",1,35));
    village[playno]->tbuild[1]->refreshbuild();

    //reduce money
    village[playno]->resource[2]->amount -= ((65 * 2) + (125*2));

    //upgrade buildings
    village[playno]->rbuild[0]->level++;
    village[playno]->rbuild[0]->cost+=15;
    village[playno]->rbuild[1]->level++;
    village[playno]->rbuild[1]->cost+=15;

    //reduce tools
    village[playno]->resource[2]->amount -= (15 * 2);

    //train troops
    int maxtroop = floor(village[playno]->resource[1]->amount / 5);   //max untrained troop training afforded
    int rnd;
    if(maxtroop==0){
        return 1;
    }else{

        rnd = 1 + (rand() % maxtroop);   //randomly select how many troops to train

        for (int i=0; i < rnd; i++) {
            //reduce food
            village[playno]->resource[1]->amount -= 5;
            village[playno]->addtroops(Troops(70,10,10,"snoopdawgz"));
        }
    }

    maxtroop = floor(village[playno]->resource[1]->amount / 35);   //max snoopdawgz troop training afforded
    if(maxtroop==0){
        return 1;
    }
    rnd = (rand() % maxtroop);   //randomly select how many troops to train

    for(int i=0; i<rnd; i++){
        village[playno]->resource[1]->amount-=15;
        village[playno]->addtroops(Troops(10,70,30,"biggies"));
    }

    return 0;
}



int AIbuild(int playno){

    //build troop building
    if(village[playno]->resource[2]->amount >= 125 && village[playno]->tbuild.size()<3){
        village[playno]->addtbuild(Building("tupacs",1,35));
        village[playno]->tbuild[2]->refreshbuild();
    }

    //if insufficient funds
    if (village[playno]->resource[2]->amount < 65) {
        return 1;
    }

    int type = (rand() %3);

    int maxbuild = floor(village[playno]->resource[2]->amount / 65);
    if(maxbuild==0){
        return 1;
    }
    int bno = (rand() %maxbuild);
    int cost = bno*65;

    //build resource building
    for(int i=0; i<bno; i++){
        village[playno]->addrbuild(Building(village[playno]->resource[type]->type, 1, 15));
        village[playno]->rbuild[village[playno]->rbuild.size()-1]->refreshbuild();
    }


    village[playno]->resource[2]->amount-=cost;
    return 0;
}

int AIupgrade(int playno){

    int select;
    int btype = rand() %2;

    if(btype==0){ //resource building

        if(village[playno]->rbuild.empty()){
            return 1;
        }

        int real[village[playno]->rbuild.size()];
        int count=0;

        for(int j=0; j<village[playno]->rbuild.size(); j++){
            if(village[playno]->rbuild[j]->level<5 && village[playno]->resource[0]->amount>=village[playno]->rbuild[j]->cost) {
                real[count]=j;
                count++;
            }
        }

        if(count==0){
            return 1;
        }
        select = (rand() % count);
        select = real[select];

        //decrease tools
        village[playno]->resource[0]->amount-=village[playno]->rbuild[select]->cost;

        //update building specs
        village[playno]->rbuild[select]->level++;
        village[playno]->rbuild[select]->cost+=15;
        village[playno]->rbuild[select]->refreshbuild();

    }else{ //troop building

        if(village[playno]->tbuild.empty()){
            return 1;
        }

        int real[village[playno]->tbuild.size()];
        int count=0;

        for(int j=0; j<village[playno]->tbuild.size(); j++){
            if(village[playno]->tbuild[j]->level<5 && village[playno]->resource[0]->amount>=village[playno]->tbuild[j]->cost) {
                real[count]=j;
                count++;
            }
        }

        if(count==0){
            return 1;
        }
        select = (rand() % count);
        select = real[select];

        //decrease tools
        village[playno]->resource[0]->amount-=village[playno]->tbuild[select]->cost;

        //update building specs
        village[playno]->tbuild[select]->level++;
        village[playno]->tbuild[select]->cost+=35;
        village[playno]->tbuild[select]->refreshbuild();
    }

    return 0;
}

int AItrain(int playno){

    int select = (rand() %3)+1;

    int tt;
    int health;
    int attack;
    int carrycap;
    string type;

    if(select==1){

        type = "snoopdawgz";
        health = 70;
        attack = 10;
        carrycap = 10;

    }else if(select==2){

        type = "biggies";
        health = 10;
        attack = 70;
        carrycap = 30;

    }else if(select==3){

        if(village[playno]->tbuild.size()<3){
            return 1;
        }

        type = "tupacs";
        health = 35;
        attack = 35;
        carrycap = 20;
    }

    for(tt=0; tt<village[playno]->tbuild.size(); tt++){
        if(village[playno]->tbuild[tt]->type==type){
            break;
        }
    }

    int maxtroop = floor(village[playno]->resource[1]->amount / village[playno]->tbuild[tt]->output);

    if(maxtroop==0){
        return 1;
    }

    int troopno = rand() %maxtroop;

    for(int i=0; i<troopno; i++){
        village[playno]->resource[1]->amount -= village[playno]->tbuild[tt]->output;
        village[playno]->addtroops(Troops(health,attack,carrycap,type));
    }

    return 0;
}

int AIattack(int playno){

    int optattack;  //keep track of points
    int opt[2];       //{points,player}
    int track=0;

    for(int j=0; j<village.size(); j++){

        //can't attack their own village
        //can't attack villages player is already attacking
        if (!village[j]->attack && j != playno) {

            optattack=0;

            //rounds required
            optattack += max(abs(village[playno]->loc[0] - village[j]->loc[0]),abs(village[playno]->loc[1] - village[j]->loc[1]));

            //target village troops total attack and health
            for (auto & troop : village[j]->troops) {
                optattack += troop->attack; //sum of villager troops attack
                optattack += troop->health; //sum of villager troops health
            }
            track++;

           if (track==1 || optattack < opt[0]){  //if current player has fewer points
               opt[0] = optattack;
               opt[1] = j;
           }
        }
    }

    //if all villages are already under attack
    if(track==0){
       return 1;        //don't attack
    }

    int villno = opt[1];

    //count troops
    int l=0,m=0,n=0;
    for(auto & troop : village[playno]->troops){
        if(troop->type=="snoopdawgz"){
            l++;
        }else if(troop->type=="biggies"){
            m++;
        }else if(troop->type=="tupacs"){
            n++;
        }
    }

    int snoopdawgz=0, biggies=0, tupacs=0;
    if(l>0){
        snoopdawgz = (int)floor(l/2)+rand() %(l-(int)floor(l/2));
    }
    if(m>0){
        biggies = (int)floor(m/2)+rand() %(m-(int)floor(m/2));
    }
    if(n>0){
        tupacs = (int)floor(n/2)+rand() %(n-(int)floor(n/2));
    }


    village[playno]->addarmy(Army());
    int acnt = (int)village[playno]->army.size()-1;

    int tcnt=0;
    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==snoopdawgz){
            break;
        }
        if(village[playno]->troops[i]->type=="snoopdawgz"){
            //copy troop to army
            village[playno]->army[acnt]->addtroops(*village[playno]->troops[i]);
            //remove troop from village
            village[playno]->troops.erase(village[playno]->troops.begin()+i);
            i--;
            tcnt++;
        }
    }

    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==biggies+snoopdawgz){
            break;
        }
        if(village[playno]->troops[i]->type=="biggies"){
            //copy troop to army
            village[playno]->army[acnt]->addtroops(*village[playno]->troops[i]);
            //remove troop from village
            village[playno]->troops.erase(village[playno]->troops.begin()+i);
            i--;
            tcnt++;
        }
    }

    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==tupacs+biggies+snoopdawgz){
            break;
        }
        if(village[playno]->troops[i]->type=="tupacs"){
            //copy troop to army
            village[playno]->army[acnt]->addtroops(*village[playno]->troops[i]);
            //remove troop from village
            village[playno]->troops.erase(village[playno]->troops.begin()+i);
            i--;
            tcnt++;
        }
    }

    village[playno]->army[acnt]->refresharmy(*village[playno]->army[acnt]);

    int vattack=0;
    int phealth = village[playno]->army[acnt]->health;        //sum of player troops health

    for(auto & troop : village[villno]->troops){
        vattack += troop->attack;    //sum of villager troops attack
    }

    if(phealth<=vattack){ //don't attack

        int lim = (int)village[playno]->army[acnt]->troops.size();

        for(int k=0; k<lim; k++){
            village[playno]->addtroops(*village[playno]->army[acnt]->troops[0]);
            village[playno]->army[acnt]->troops.erase(village[playno]->army[acnt]->troops.begin());
        }
        //remove army
        village[playno]->army.erase(village[playno]->army.begin()+acnt);
        return 1;
    }

    //set army location
    village[playno]->army[acnt]->loc[0] = village[playno]->loc[0];
    village[playno]->army[acnt]->loc[1] = village[playno]->loc[1];

    //set army target
    village[playno]->army[acnt]->target = village[villno]->idx;

    //update village to under attack
    village[villno]->attack = true;

    return 0;
}
