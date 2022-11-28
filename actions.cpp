#include "villagegame.h"

int build(int playno){

    int select;

    mvwprintw(win,texty,1,"Select building type: ");
    string choices[]={"1.Resource-generating - cost: money x65","2.Troop-training - cost: money x125"};
    select = options(2,choices,texty+1, 1,false);

    refreshcli(playno);

    if(select==1) { //resource

        if(village[playno]->resource[2]->amount<65){
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Insufficient funds!");
            return 1;
        }

        int cost;
        int bno;

        mvwprintw(win, texty, 1, "Select a type of resource to generate:");
        string types[] = {"1.Tools", "2.Food", "3.Money"};

        int type = options(3, types, texty + 1, 1, false);
        refreshcli(playno);

        int maxbuild = floor(village[playno]->resource[2]->amount / 65);
        mvwprintw(win,texty,1,"How many buildings would you like to build? ");

        string nums[maxbuild+1];
        for(int i=0; i<maxbuild+1; i++){
            nums[i] = {to_string(i)};
        }
        bno = options(maxbuild+1,nums,texty+1,1,true)-1;
        cost = bno*65;

        //create buildings
        for (int i = 0; i < bno; i++) {
            village[playno]->addrbuild(Building(village[playno]->resource[type-1]->type, 1, 15));
        }

        village[playno]->resource[2]->amount-=cost;

    }else { //troop

        if(village[playno]->resource[2]->amount<125){
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Insufficient funds!");
            return 1;
        }

        if(village[playno]->tbuild.size()==3){
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: All troop training buildings built!");
            return 1;
        }

        string types[3-village[playno]->tbuild.size()];

        if(village[playno]->tbuild.empty()){
            types[0] = "snoopdawgz";
            types[1] = "biggies";
            types[2] = "tupacs";

        }else{
            bool s=true;
            bool b=true;
            bool t=true;

            for(auto & i : village[playno]->tbuild){
                if(i->type=="snoopdawgz"){
                    s=false;
                }else if(i->type=="biggies"){
                    b=false;
                }else if(i->type=="tupacs"){
                    t=false;
                }
            }

            if(village[playno]->tbuild.size()==1){
                if(!s){
                    types[0] = "biggies";
                    types[1] = "tupacs";
                }else if(!b){
                    types[0] = "snoopdawgz";
                    types[1] = "tupacs";
                }else if(!t){
                    types[0] = "snoopdawgz";
                    types[1] = "biggies";
                }
            }

            if(village[playno]->tbuild.size()==2){
                if(!s && !b){
                    types[0] = "tupacs";
                }else if(!s && !t){
                    types[0] = "biggies";
                }else if(!b && !t){
                    types[0] = "snoopdawgz";
                }
            }
        }

        mvwprintw(win, texty, 1, "Select a type of troop to train:");
        int type = options(3-(int)village[playno]->tbuild.size(), types, texty + 1, 1, false);
        refreshcli(playno);

        //create building
        village[playno]->addtbuild(Building(types[type-1], 0, 0));
        village[playno]->resource[2]->amount-=125;
    }

    refreshcli(playno);
    return 0;
}

int upgrade(int playno){

    int select;

    if(village[playno]->rbuild.empty()){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: You have no resource buildings to upgrade yet!");
        return 1;
    }

    int real[village[playno]->rbuild.size()];
    int count=0;

    string choices[village[playno]->rbuild.size()];

    for(int j=0; j<village[playno]->rbuild.size(); j++){
        if(village[playno]->rbuild[j]->level<5 && village[playno]->resource[0]->amount>=village[playno]->rbuild[j]->cost){
            choices[count] = {to_string(count+1) + ". level " + to_string(village[playno]->rbuild[j]->level) + " - generates " + village[playno]->rbuild[j]->type + "- cost: tools x" + to_string(village[playno]->rbuild[j]->cost)};
            real[count]=j;
            count++;
        }
    }

    if(count==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No resource buildings available for upgrade!");
        return 1;
    }

    mvwprintw(win,texty,1,"Select a resource building to upgrade:");
    select = options(count,choices,texty+1, 1,false)-1;
    select = real[select];

    //decrease tools
    village[playno]->resource[0]->amount -= village[playno]->rbuild[select]->cost;

    //update building specs
    village[playno]->rbuild[select]->level++;
    village[playno]->rbuild[select]->cost += 15;
    refreshcli(playno);

    return 0;
}

int train(int playno){

    int select;

    mvwprintw(win,texty,1,"Select a type of troop to train:");

    int troopno;

    string choices[] = {"1. Snoopdawgz - cost: food x5",
                       "2. Biggies - cost: food x15",
                       "3. Tupacs - cost: food x10"};
    select = options(3,choices,texty+1,1,false);

    refreshcli(playno);

    int maxtroop=0;
    int cost=0;
    bool purchased = false;
    string type;

    //max is either max available or max afforded
    //error if building not purchased
    if(select==1){

        cost=5;
        type = "snoopdawgz";

    }else if(select==2){

        cost=15;
        type = "biggies";

    }else if(select==3){

        cost=10;
        type = "tupacs";
    }

    if(village[playno]->resource[1]->amount<cost){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: Insufficient funds!");
        return 1;
    }

    maxtroop = floor(village[playno]->resource[1]->amount / cost);

    if(maxtroop==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No %s to train!",type.c_str());
        return 1;
    }

    for(auto & i : village[playno]->tbuild){
        if(i->type==type){
            purchased = true;
            break;
        }
    }

    if(!purchased){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: %s training building not purchased!", type.c_str());
        return 1;
    }

    string nums[maxtroop+1];
    for(int i=0; i<maxtroop+1; i++){
        nums[i] = {to_string(i)};
    }

    mvwprintw(win,texty,1,"How many %s would you like to train? ",type.c_str());
    troopno = options(maxtroop+1,nums,texty+1,1,true)-1;
    refreshcli(playno);


    if(select==1){ //snoopdawgz

        for(int i=0; i<troopno; i++){
            village[playno]->addtroops(Troops(5,350,50,30,type));
        }

    }else if(select==2){ //biggies

        for(int i=0; i<troopno; i++){
            village[playno]->addtroops(Troops(15,50,350,90,type));
        }

    }else if(select==3){ //tupacs

        for(int i=0; i<troopno; i++){
            village[playno]->addtroops(Troops(10,175,175,50,type));
        }
    }

    village[playno]->resource[1]->amount -= cost*troopno;

    return 0;
}


int attack(int playno){

    refreshcli(playno);

    //count troops by type
    int k=0,l=0,m=0;
    for(auto & troop : village[playno]->troops){
        if(troop->type=="snoopdawgz"){
            k++;
        }else if(troop->type=="biggies"){
            l++;
        }else if(troop->type=="tupacs"){
            m++;
        }
    }

    int trooptot = k+l+m;
    if(trooptot==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No troops available for battle!");
        return 1;
    }

    mvwprintw(win,texty,1,"Select a village to attack :");

    string vills[village.size()-1-village[playno]->army.size()];

    int cnt=0;
    int real[village.size()];
    for(int j=0; j<village.size(); j++){

        //can't attack villages player is already under attack
        //can't attack their own village
        if(!village[j]->attack && j != playno){

            //rounds required
            int minstep = max(abs(village[playno]->loc[0] - village[j]->loc[0]), abs(village[playno]->loc[1] - village[j]->loc[1]));

            //target village troops total attack
            int vattack=0;
            for(auto & troop : village[j]->troops){
                vattack += troop->attack; //sum of villager troops attack
            }

            vills[cnt] = {"Player "+to_string(village[j]->idx+1)+"'s Village - health "+to_string(village[j]->health)+" - total attack "+to_string(vattack)+" - tools x"+to_string(village[j]->resource[0]->amount)+" - food x"+to_string(village[j]->resource[1]->amount)+" - money x"+to_string(village[j]->resource[2]->amount)+" - "+to_string(minstep)+" rounds to reach target "};
            real[cnt] = j;
            cnt++;
        }
    }

    if(cnt==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No villages available to attack!");
        return 1;
    }

    int villno = options(cnt,vills,texty+1, 1,false)-1;
    villno = real[villno];
    refreshcli(playno);

    //ask for troops to send for battle
    int rookie=0, expert=0, master=0;

    if(k>0){
        mvwprintw(win,texty,1,"Troops available for battle:");
        mvwprintw(win,texty+1,1,"1.Snoopdawgz x%d",k);
        mvwprintw(win,texty+2,1,"2.Biggies x%d",l);
        mvwprintw(win,texty+3,1,"3.Tupacs x%d",m);

        mvwprintw(win,texty+5,1,"How many snoopdawgz are you taking?");
        string rook[k+1];
        for(int i=0; i<k+1; i++){
            rook[i] = {to_string(i)};
        }
        rookie = options(k+1,rook,texty+6,1,true)-1;
        refreshcli(playno);
    }

    if(l>0){
        //ask for troops to send for battle
        mvwprintw(win,texty,1,"Troops available for battle:");
        mvwprintw(win,texty+1,1,"1.Snoopdawgz troops x%d",k);
        mvwprintw(win,texty+2,1,"2.Biggies troops x%d",l);
        mvwprintw(win,texty+3,1,"3.Tupacs troops x%d",m);

        mvwprintw(win,texty+5,1,"How many biggies are you taking?");
        string exp[l+1];
        for(int i=0; i<l+1; i++){
            exp[i] = {to_string(i)};
        }
        expert = options(l+1,exp,texty+6,1,true)-1;
        refreshcli(playno);
    }


    if(m>0){
        //ask for troops to send for battle
        mvwprintw(win,texty,1,"Troops available for battle:");
        mvwprintw(win,texty+1,1,"1.Snoopdawgz x%d",k);
        mvwprintw(win,texty+2,1,"2.Biggies x%d",l);
        mvwprintw(win,texty+3,1,"3.Tupacs x%d",m);

        mvwprintw(win,texty+5,1,"How many tupacs are you taking?");
        string mst[m+1];
        for(int i=0; i<m+1; i++){
            mst[i] = {to_string(i)};
        }
        master = options(m+1,mst,texty+6,1,true)-1;
        refreshcli(playno);
    }

    trooptot = rookie+expert+master;

    //create new army
    village[playno]->addarmy(Army());

    int acnt = village[playno]->army.size()-1;
    int tcnt=0;

    for(int i=0; i<village[playno]->troops.size(); i++){
        if(tcnt==rookie){
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
        if(tcnt==expert+rookie){
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
        if(tcnt==master+expert+rookie){
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

    int res[] = {0,0,0};
    village[playno]->army[acnt]->refresharmy(*village[playno]->army[acnt],res, village[villno]->idx);

    int vattack=0;
    int phealth = village[playno]->army[acnt]->health;        //sum of player troops health

    for(auto & troop : village[villno]->troops){
        vattack += troop->attack;    //sum of villager troops attack
    }

    if(phealth<=vattack){

        int lim = village[playno]->army[acnt]->troops.size();

        for(int j=0; j<lim; j++){
            village[playno]->addtroops(*village[playno]->army[acnt]->troops[0]);
            village[playno]->army[acnt]->troops.erase(village[playno]->army[acnt]->troops.begin());
        }

        //remove army
        village[playno]->army.erase(village[playno]->army.begin()+acnt);

        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: Increase army health to attack selected village!");
        return 1;
    }

    //set army location
    village[playno]->army[acnt]->loc[0] = village[playno]->loc[0];
    village[playno]->army[acnt]->loc[1] = village[playno]->loc[1];

    //update village to under attack
    village[villno]->attack = true;

    return 0;
}
