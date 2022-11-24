#include "villagegame.h"

int AIround1(int playno){

    //build one of each building type
    rbuild[playno][0] = ResourceBuildings("food", 1, 15);
    rbuild[playno][1] = ResourceBuildings("money", 1, 15);
    tbuild[playno][0] = TroopBuildings("untrained");
    tbuild[playno][0] = TroopBuildings("rookie");

    //increase building counts
    village[playno]->rbuildings += 2;
    village[playno]->tbuildings += 2;

    //reduce money
    resource[playno][2].amount -= ((65 * 2) + 125);

    //upgrade buildings
    rbuild[playno][0] = ResourceBuildings("food", 2, 30);
    rbuild[playno][1] = ResourceBuildings("money", 2, 30);

    //reduce tools
    resource[playno][2].amount -= (15 * 2);

    //train troops
    int maxtroop = floor(resource[playno][1].amount / 15);   //max untrained troop training afforded
    if(maxtroop==0){
        return 1;
    }
    int rnd = 1 + (rand() % maxtroop);   //randomly select how many troops to train

    int loc[] = {village[playno]->loc[0], village[playno]->loc[1]};

    for (int i = 0; i < rnd; i++) {
        //reduce food
        resource[playno][1].amount -= village[playno]->troops[0]->cost;

        //update troop specs
        village[playno]->troops.erase(village[playno]->troops.begin());
        village[playno]->addtroops(Troops(35, 50, 50, 30, 10, "rookie", loc));
    }

    maxtroop = floor(resource[playno][1].amount / 35);   //max rookie troop training afforded
    if(maxtroop==0){
        return 1;

    }else if(maxtroop>rnd){ //if more than untrained troops available
        maxtroop = rnd;
    }
    rnd = (rand() % maxtroop);   //randomly select how many troops to train

    int j=0;
    for(int i=0; i<village[playno]->troops.size(); i++){

        if(j==rnd){
            break;
        }
        if(village[playno]->troops[i]->type=="rookie"){
            resource[playno][1].amount-=village[playno]->troops[i]->cost;

            //update troop specs
            village[playno]->troops.erase(village[playno]->troops.begin() + i);
            village[playno]->addtroops(Troops(80, 175, 175, 50, 15, "expert", loc));
            i--;
            j++;
        }
    }

    return 0;
}



int AIbuild(int playno){

    //if insufficient funds
    if (resource[playno][2].amount < 65) {
        return 1;
    }

    int type = (rand() %4);

    int maxbuild = floor(resource[playno][2].amount / 65);
    if(maxbuild==0){
        return 1;
    }
    int bno = (rand() %maxbuild);

    int cost = bno*65;

    //increase village resource buildings count
    village[playno]->rbuildings+=bno;

    //update building specs
    for(int i=village[playno]->rbuildings-bno; i<village[playno]->rbuildings; i++){
        rbuild[playno][i] = ResourceBuildings(resource[playno][type].type, 1, 15);
    }

    resource[playno][2].amount-=cost;
    return 0;
}

int AIupgrade(int playno){

    int select;

    if(village[playno]->rbuildings==0){
        return 1;
    }

    int real[village[playno]->rbuildings];
    int count=0;

    for(int j=0; j<village[playno]->rbuildings; count++, j++){
        real[count]=j;
        if(rbuild[playno][j].level==5 || resource[playno][0].amount<rbuild[playno][j].cost) {
            count--;
        }
    }
    if(count==0){
        return 1;
    }
    select = (rand() % count);

    //decrease tools
    resource[playno][0].amount-=rbuild[playno][real[select]].cost;

    //update building specs
    rbuild[playno][real[select]] = ResourceBuildings(rbuild[playno][real[select]].type, rbuild[playno][real[select]].level+1, rbuild[playno][real[select]].cost+15);

    return 0;
}

int AItrain(int playno){

    int select;
    int troopno;
    int loc[] = {village[playno]->loc[0],village[playno]->loc[1]};

    int n=1, j=0, k=0,l=0,m=0;

    for(auto & troop : village[playno]->troops){
        if(troop->type=="untrained"){
            k++;
        }else if(troop->type=="rookie"){
            l++;
            n=2;
        }else if(troop->type=="expert"){
            m++;
            n=3;
            break;
        }
    }

    select = (rand() %n)+1;

    int maxtroop;

    if(select==1){

        maxtroop = floor(resource[playno][1].amount / 15);

        if(tbuild[playno][0].type=="undefined"){
            if(resource[playno][2].amount>=125){
                tbuild[playno][0].type = "untrained";
                village[playno]->tbuildings++;    //increase village training buildings count
                resource[playno][2].amount-=125;
            }else{
                return 1;       //error if building not purchased
            }
        }else{
            if(maxtroop>k){     //max is either max available or max afforded
                maxtroop = k;
            }

            if(maxtroop==0){
                return 1;
            }

            troopno = rand() %maxtroop;

            for(int i=0; i<village[playno]->troops.size(); i++){

                if(j==troopno){
                    break;
                }
                if(village[playno]->troops[i]->type=="untrained"){

                    resource[playno][1].amount-=village[playno]->troops[i]->cost;

                    //update troop specs
                    village[playno]->troops.erase(village[playno]->troops.begin() + i);
                    village[playno]->addtroops(Troops(35,50,50,30,1,"rookie",loc));
                    i--;
                    j++;
                }
            }
        }
    }else if(select==2){

        maxtroop = floor(resource[playno][1].amount / 35);

        if(tbuild[playno][1].type=="undefined"){
            if(resource[playno][2].amount>=125){
                tbuild[playno][1].type = "rookie";
                village[playno]->tbuildings++;    //increase village training buildings count
                resource[playno][2].amount-=125;
            }else{
                return 1;           //error if building not purchased
            }
        }else{
            if(maxtroop>l){     //max is either max available or max afforded
                maxtroop = l;
            }
            if(maxtroop==0){
                return 1;
            }

            troopno = rand() %maxtroop;

            for(int i=0; i<village[playno]->troops.size(); i++){

                if(j==troopno){
                    break;
                }

                if(village[playno]->troops[i]->type=="rookie"){
                    resource[playno][1].amount-=village[playno]->troops[i]->cost;

                    //update troop specs
                    village[playno]->troops.erase(village[playno]->troops.begin() + i);
                    village[playno]->addtroops(Troops(80,175,175,50,2,"expert",loc));
                    i--;
                    j++;
                }
            }
        }
    }else if(select==3){

        maxtroop = floor(resource[playno][1].amount / 80);

        if(tbuild[playno][2].type=="undefined"){
            if(resource[playno][2].amount>=125){
                tbuild[playno][2].type = "expert";
                village[playno]->tbuildings++;    //increase village training buildings count
                resource[playno][2].amount-=125;
            }else{
                return 1;           //error if building not purchased
            }
        }else{
            if(maxtroop>m){     //max is either max available or max afforded
                maxtroop = m;
            }
            if(maxtroop==0){
                return 1;
            }

            troopno = (rand() %maxtroop);

            for(int i=0; i<village[playno]->troops.size(); i++){

                if(j==troopno){
                    break;
                }

                if(village[playno]->troops[i]->type=="expert"){

                    resource[playno][1].amount-=village[playno]->troops[i]->cost;

                    //update troop specs
                    village[playno]->troops.erase(village[playno]->troops.begin() + i);
                    village[playno]->addtroops(Troops(0,350,350,90,3,"master",loc));
                    i--;
                    j++;
                }
            }
        }
    }
    return 0;
}

int AIattack(int playno){

    int optattack;  //keep track of points
    int opt[2];       //{points,player}
    int j;
    int track=0;

    for(j=0; j<village.size(); j++){

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

            if(track==1){
                opt[0] = optattack;
                opt[1] = j;
            }else if (optattack < opt[0]) {  //if current player has fewer points
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
        if(troop->type=="rookie"){
            l++;
        }else if(troop->type=="expert"){
            m++;
        }else if(troop->type=="master"){
            n++;
        }
    }

    int rookie=0, expert=0, master=0;
    if(l>0){
        rookie = floor(l/2)+(rand() %l)+1;
    }
    if(m>0){
        expert = floor(m/2)+(rand() %m)+1;
    }
    if(n>0){
        master = floor(n/2)+(rand() %n)+1;
    }

    village[playno]->addarmy(Army());
    int acnt = village[playno]->army.size()-1;

    int tcnt=0;
    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==rookie){
            break;
        }
        if(village[playno]->troops[i]->type=="rookie"){
            //copy troop to army
            village[playno]->army[acnt]->addtroops(*village[playno]->troops[i]);
            //remove troop from village
            village[playno]->troops.erase(village[playno]->troops.begin()+i);
            i--;
            tcnt++;
        }
    }

    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==expert+rookie){
            break;
        }
        if(village[playno]->troops[i]->type=="expert"){
            //copy troop to army
            village[playno]->army[acnt]->addtroops(*village[playno]->troops[i]);
            //remove troop from village
            village[playno]->troops.erase(village[playno]->troops.begin()+i);
            i--;
            tcnt++;
        }
    }

    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==master+expert+rookie){
            break;
        }
        if(village[playno]->troops[i]->type=="master"){
            //copy troop to army
            village[playno]->army[acnt]->addtroops(*village[playno]->troops[i]);
            //remove troop from village
            village[playno]->troops.erase(village[playno]->troops.begin()+i);
            i--;
            tcnt++;
        }
    }

    int res[] = {0,0,0};
    village[playno]->army[acnt]->refresharmy(*village[playno]->army[acnt],res, village[villno]->idx);

    int vattack=0;
    int phealth = village[playno]->army[acnt]->health;        //sum of player troops health

    for(auto & troop : village[villno]->troops){
        vattack += troop->attack;    //sum of villager troops attack
    }

    if(phealth<=vattack){ //don't attack

        int lim = village[playno]->army[acnt]->troops.size();

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

    //update village to under attack
    village[villno]->attack = true;

    return 0;
}

void AIresurrect(int playno, int dead){

    //max afforded
    int maxdead= floor(resource[playno][3].amount/45);

    if(dead<maxdead){
        maxdead = dead;
    }

    if(maxdead>0){
        int elixir = (rand() %maxdead+1);

        int loc[] = {village[playno]->loc[0],village[playno]->loc[1]};

        for(int i=village[playno]->troops.size(); i<village[playno]->troops.size()+elixir; i++){

            village[playno]->addtroops(Troops(15,0,20,0,0,"untrained",loc));
        }
    }
}