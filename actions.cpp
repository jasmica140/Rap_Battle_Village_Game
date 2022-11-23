#include "villagegame.h"

int build(int playno){

    int bno;
    int select;
    int cost;

    mvwprintw(win,texty,1,"Select building type: ");
    string choices[]={"1.Resource-generating - cost: money x65","2.Troop-training - cost: money x125"};
    select = options(2,choices,texty+1, 1,false);

    refreshcli(playno);

    int type;

    if(select==1){ //resource

        mvwprintw(win,texty,1,"Select a resource to generate:");
        string types[]={"1.Tools","2.Food","3.Money"};
        type = options(3,types,texty+1, 1,false);

        refreshcli(playno);

        int maxbuild = floor(resource[playno][2].amount / 65);
        mvwprintw(win,texty,1,"How many buildings would you like to build? ");

        string nums[maxbuild+1];
        for(int i=0; i<maxbuild+1; i++){
            nums[i] = {to_string(i)};
        }
        bno = options(maxbuild+1,nums,texty+1,1,true)-1;
        cost = bno*65;

        village[playno]->rbuildings+=bno;        //increase village resource buildings count

        //update building specs
        for(int i=village[playno]->rbuildings-bno; i<village[playno]->rbuildings; i++){
            rbuild[playno][i] = ResourceBuildings(resource[playno][type-1].type, 1, 15);
        }

        resource[playno][2].amount-=cost;
        refreshcli(playno);
        mvwprintw(win,erry,1,"Update: Resource generating buildings built!");
        return 0;

    }else{ //troops

        //if sufficient funds
        if(resource[playno][2].amount>=125){

            //building type chosen successively
            if(village[playno]->tbuildings == 3){
                refreshcli(playno);
                mvwprintw(win,erry,1,"Error: All troop-training buildings built!");
                return 1;

            }else if(village[playno]->tbuildings == 2){
                refreshcli(playno);
                tbuild[playno][2].type = "expert";
                mvwprintw(win,erry,1,"Update: Expert troop-training building built!");

            }else if(village[playno]->tbuildings == 1){
                refreshcli(playno);
                tbuild[playno][1].type = "rookie";
                mvwprintw(win,erry,1,"Update: Rookie troop-training building built!");

            }else if(village[playno]->tbuildings == 0){
                refreshcli(playno);
                tbuild[playno][0].type = "untrained";
                mvwprintw(win,erry,1,"Update: Untrained troop-training building built!");
            }

            village[playno]->tbuildings++;    //increase village training buildings count
            cost = 125;

            resource[playno][2].amount-=cost;
            return 0;

        }else{
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Insufficient funds!");
            return 1;
        }
    }

    return 0;
}

int upgrade(int playno){

    int select;

    if(village[playno]->rbuildings==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: You have no resource buildings to upgrade yet!");
        return 1;
    }

    int real[village[playno]->rbuildings];
    int count=0;

    string choices[village[playno]->rbuildings];

    for(int j=0; j<village[playno]->rbuildings; j++){
        real[count]=j;
        if(rbuild[playno][j].level<5 && resource[playno][0].amount>=rbuild[playno][j].cost){
            choices[count] = {to_string(count+1) + ". Resource-generating - level " + to_string(rbuild[playno][j].level) + " - generates " + rbuild[playno][j].type + "- cost: tools x" + to_string(rbuild[playno][j].cost)};
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

    //decrease tools
    resource[playno][0].amount-=rbuild[playno][real[select]].cost;

    //update building specs
    rbuild[playno][real[select]] = ResourceBuildings(rbuild[playno][real[select]].type, rbuild[playno][real[select]].level+1, rbuild[playno][real[select]].cost+15);

    refreshcli(playno);

    return 0;
}

int train(int playno){

    int select;

    mvwprintw(win,texty,1,"Select which type of troops to train:");

    int troopno;

    int k=0,l=0,m=0;
    for(auto & troop : village[playno]->troops){
        if(troop->type=="untrained"){
            k++;
        }else if(troop->type=="rookie"){
            l++;
        }else if(troop->type=="expert"){
            m++;
        }
    }

    string choices[] = {"1. Untrained troops x"+to_string(k)+" available - cost: food x15",
                       "2. Rookie troops x"+ to_string(l) +" available - cost: food x35",
                       "3. Expert troops x" + to_string(m) + " available - cost: food x80"};
    select = options(3,choices,texty+1,1,false);

    refreshcli(playno);

    int maxtroop=0;

    //max is either max available or max afforded
    //error if building not purchased
    if(select==1){

        maxtroop = floor(resource[playno][1].amount / 15);

        if(tbuild[playno][0].type=="undefined"){
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Untrained troop-training building not purchased!");
            return 1;
        }else{
            if(maxtroop>k){
                maxtroop = k;
            }
        }
    }else if(select==2){

        maxtroop = floor(resource[playno][1].amount / 35);

        if(tbuild[playno][1].type=="undefined"){
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Rookie troop-training building not purchased!");
            return 1;
        }else{
            if(maxtroop>l){
                maxtroop = l;
            }
        }
    } else if(select==3){

        maxtroop = floor(resource[playno][1].amount / 80);

        if(tbuild[playno][2].type=="undefined"){
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Expert troop-training building not purchased!");
            return 1;
        }else{
            if(maxtroop>m){
                maxtroop = m;
            }
        }
    }

    if(maxtroop==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No %s troops to train!",village[playno]->troops[select]->type.c_str());
        return 1;
    }

    string nums[maxtroop+1];
    for(int i=0; i<maxtroop+1; i++){
        nums[i] = {to_string(i)};
    }

    mvwprintw(win,texty,1,"How many %s troops would you like to upgrade? ",village[playno]->troops[select]->type.c_str());
    troopno = options(maxtroop+1,nums,texty+1,1,true)-1;
    refreshcli(playno);

    int j=0;
    if(select==1){ //rookies

        for(int i=0; i<village[playno]->troops.size(); i++){
            if(village[playno]->troops[i]->type=="untrained"){

                if(j==troopno){
                    break;
                }
                resource[playno][1].amount-=village[playno]->troops[i]->cost;

                //update troop specs
                int loc[2] = {village[playno]->loc[0],village[playno]->loc[1]};
                village[playno]->troops.erase(village[playno]->troops.begin() + i);
                village[playno]->addtroops(Troops(35,50,50,30,1,"rookie",loc));

                j++;
            }
        }
    }else if(select==2){ //expert

        for(int i=0; i<village[playno]->troops.size(); i++){
            if(village[playno]->troops[i]->type=="rookie"){

                if(j==troopno){
                    break;
                }
                resource[playno][1].amount-=village[playno]->troops[i]->cost;

                //update troop specs
                int loc[2] = {village[playno]->loc[0],village[playno]->loc[1]};
                village[playno]->troops.erase(village[playno]->troops.begin() + i);
                village[playno]->addtroops(Troops(80,175,175,50,2,"expert",loc));

                j++;
            }
        }

    }else if(select==3){ //master

        for(int i=0; i<village[playno]->troops.size(); i++){
            if(village[playno]->troops[i]->type=="expert"){

                if(j==troopno){
                    break;
                }
                resource[playno][1].amount-=village[playno]->troops[i]->cost;

                //update troop specs
                int loc[2] = {village[playno]->loc[0],village[playno]->loc[1]};
                village[playno]->troops.erase(village[playno]->troops.begin() + i);
                village[playno]->addtroops(Troops(0,350,350,90,3,"master",loc));

                j++;
            }
        }
    }
    return 0;
}


int attack(int playno){

    refreshcli(playno);

    //count troops by type
    int k=0,l=0,m=0;
    for(auto & troop : village[playno]->troops){
        if(troop->type=="rookie"){
            k++;
        }else if(troop->type=="expert"){
            l++;
        }else if(troop->type=="master"){
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
    int realno=0;
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

            vills[cnt] = {"Player "+to_string(village[j]->idx+1)+"'s Village - health "+to_string(village[j]->health)+" - total attack "+to_string(vattack)+" - tools x"+to_string(resource[j][0].amount)+" - food x"+to_string(resource[j][1].amount)+" - money x"+to_string(resource[j][2].amount)+" - "+to_string(minstep)+" rounds to reach target "};
            cnt++;
        }else{
            realno++;
        }
    }

    if(cnt==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No villages available to attack!");
        return 1;
    }

    int villno = options(cnt,vills,texty+1, 1,false);
    refreshcli(playno);

    //ask for troops to send for battle
    int rookie=0, expert=0, master=0;

    if(k>0){
        mvwprintw(win,texty,1,"Troops available for battle:");
        mvwprintw(win,texty+1,1,"1.Rookie troops x%d",k);
        mvwprintw(win,texty+2,1,"2.Expert troops x%d",l);
        mvwprintw(win,texty+3,1,"3.Master troops x%d",m);

        mvwprintw(win,texty+5,1,"How many rookie troops are you taking?");
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
        mvwprintw(win,texty+1,1,"1.Rookie troops x%d",k);
        mvwprintw(win,texty+2,1,"2.Expert troops x%d",l);
        mvwprintw(win,texty+3,1,"3.Master troops x%d",m);

        mvwprintw(win,texty+5,1,"How many expert troops are you taking?");
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
        mvwprintw(win,texty+1,1,"1.Rookie troops x%d",k);
        mvwprintw(win,texty+2,1,"2.Expert troops x%d",l);
        mvwprintw(win,texty+3,1,"3.Master troops x%d",m);

        mvwprintw(win,texty+5,1,"How many master troops are you taking?");
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

    //update village to under attack
    village[villno]->attack = true;

    return 0;
}

int resurrect(int playno){

    //count army troops
    int armytrps=0;
    for(auto & i : village[playno]->army){
        armytrps+=i->troops.size();
    }

    //count dead troops
    int dead = 50-village[playno]->troops.size()-armytrps;

    //if no dead troops exit
    if(dead==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No dead to troops to resurrect!");
        return 1;

    }else if(resource[playno][3].amount<45){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: Insufficient funds!");
        return 1;
    }

    refreshcli(playno);

    //max afforded
    int maxdead= resource[playno][3].amount/45;

    if(dead<maxdead){
        maxdead = dead;
    }

    mvwprintw(win,texty+1,1,"How many troops do you want to resurrect?");
    string d[maxdead+1];
    for(int i=0; i<maxdead+1; i++){
        d[i] = {to_string(i)};
    }
    int elixir = options(dead,d,texty+6,1,true)-1;

    int loc[] = {village[playno]->loc[0],village[playno]->loc[1]};

    for(int i=village[playno]->troops.size(); i<village[playno]->troops.size()+elixir; i++){

        village[playno]->addtroops(Troops(15,0,20,0,0,"untrained",loc));
    }

    refreshcli(playno);

    return 0;
}