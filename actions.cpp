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

        int maxbuild = round(resource[playno][2].amount / 65);
        mvwprintw(win,texty,1,"How many buildings would you like to build? ");

        string nums[maxbuild];
        for(int i=0; i<maxbuild; i++){
            nums[i] = {to_string(i)};
        }
        bno = options(maxbuild,nums,texty+1,1,true)-1;
        cost = bno*65;

        village[playno].rbuildings+=bno;        //increase village resource buildings count

        //update building specs
        for(int i=village[playno].rbuildings-bno; i<village[playno].rbuildings; i++){
            rbuild[playno][i] = ResourceBuildings(resource[playno][type-1].type, 1, 15);
        }

    }else{ //troops

        //if sufficient funds
        if(resource[playno][2].amount>=125){

            //building type chosen successively
            if(village[playno].tbuildings == 3){
                refreshcli(playno);
                mvwprintw(win,erry,1,"Error: All troop-training buildings built!");
                return 1;

            }else if(village[playno].tbuildings == 2){
                refreshcli(playno);
                tbuild[playno][2].type = "expert";
                mvwprintw(win,erry,1,"Update: Expert troop-training building finished!");

            }else if(village[playno].tbuildings == 1){
                refreshcli(playno);
                tbuild[playno][1].type = "rookie";
                mvwprintw(win,erry,1,"Update: Expert troop-training building finished!");

            }else if(village[playno].tbuildings == 0){
                refreshcli(playno);
                tbuild[playno][0].type = "untrained";
                mvwprintw(win,erry,1,"Update: Expert troop-training building finished!");
            }

            village[playno].tbuildings++;    //increase village training buildings count
            cost = 125;

        }else{
            refreshcli(playno);
            mvwprintw(win,erry,1,"Error: Insufficient funds!");
            return 1;
        }
    }

    refreshcli(playno);

    resource[playno][2].amount-=cost;
    return 0;
}

int upgrade(int playno){

    int select;

    if(village[playno].rbuildings==0){
        mvwprintw(win,erry,1,"Error: You have no resource buildings to upgrade yet!");
        return 1;
    }else if(resource[playno][0].amount){

    }

    mvwprintw(win,texty,1,"Select a resource building to upgrade:");

    int count;
    int real[village[playno].rbuildings];
    int j=0;

    string choices[village[playno].rbuildings];

    for(count=0; count<village[playno].rbuildings; count++){
        real[count]=j;
        if(rbuild[playno][count].level<5){
            choices[count] = {to_string(count+1) + ". Resource-generating - level " + to_string(rbuild[playno][count].level) + " - generates " + rbuild[playno][count].type + "- cost: tools x" + to_string(rbuild[playno][count].cost)};
        }else{
            count-=1;
        }
    }
    select = options(count,choices,texty+1, 1,false);

    //update building specs
    rbuild[playno][real[select-1]] = ResourceBuildings(rbuild[playno][real[select-1]].type, rbuild[playno][real[select-1]].level+1, rbuild[playno][real[select-1]].cost+15);

    refreshcli(playno);

    //decrease tools
    resource[playno][0].amount-=rbuild[playno][real[select-1]].cost;

    return 0;
}

int train(int playno){

    int select;

    mvwprintw(win,texty,1,"Select which type of troops to train:");

    int troopno;

    int k=0,l=0,m=0;
    for(int i=0; i<village[playno].troops; i++){
        if(troops[playno][i].type=="untrained"){
            k++;
        }else if(troops[playno][i].type=="rookie"){
            l++;
        }else if(troops[playno][i].type=="expert"){
            m++;
        }
    }

    string choices[] = {"1. Untrained troops x"+to_string(k)+" available - cost: food x15",
                       "2. Rookie troops x"+ to_string(l) +" available - cost: food x35",
                       "3. Expert troops x" + to_string(m) + " available - cost: food x80"};
    select = options(3,choices,texty+1,1,false);

    refreshcli(playno);

    int maxtroop = round(resource[playno][1].amount / troops[playno][select-1].cost);

    //max is either max available or max afforded
    //error if building not purchased
    if(select==1){

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

    string nums[maxtroops];
    for(int i=0; i<maxtroop; i++){
        nums[i] = {to_string(i)};
    }

    mvwprintw(win,texty,1,"How many %s troops would you like to upgrade? ",troops[playno][select-1].type.c_str());
    troopno = options(maxtroop,nums,texty+1,1,true)-1;
    refreshcli(playno);

    int j=0;
    if(select==1){ //rookies

        for(int i=0; i<village[playno].troops; i++){
            if(troops[playno][i].type=="untrained"){

                if(j==troopno){
                    break;
                }
                resource[playno][1].amount-=troops[playno][i].cost;

                //update troop specs
                int loc[2] = {village[playno].loc[0],village[playno].loc[1]};
                troops[playno][i] = Troops(35,50,50,30,10,"stationed","rookie",loc);

                j++;
            }
        }
    }else if(select==2){ //expert

        for(int i=0; i<village[playno].troops; i++){
            if(troops[playno][i].type=="rookie"){

                if(j==troopno){
                    break;
                }
                resource[playno][1].amount-=troops[playno][i].cost;

                //update troop specs
                int loc[2] = {village[playno].loc[0],village[playno].loc[1]};
                troops[playno][i] = Troops(80,175,175,50,15,"stationed","expert",loc);

                j++;
            }
        }

    }else if(select==3){ //master

        for(int i=0; i<village[playno].troops; i++){
            if(troops[playno][i].type=="expert"){

                if(j==troopno){
                    break;
                }
                resource[playno][1].amount-=troops[playno][i].cost;

                //update troop specs
                int loc[2] = {village[playno].loc[0],village[playno].loc[1]};
                troops[playno][i] = Troops(0,350,350,90,25,"stationed","master",loc);

                j++;
            }
        }
    }
    return 0;
}


int attack(int playno, int totplay){

    refreshcli(playno);

    mvwprintw(win,texty,1,"Select a village to attack :");

    string vills[totplay-1-village[playno].army];

    int cnt=0;

    for(int j=0; j<totplay; j++){

        bool ok = true;

        //rounds required
        int minstep = max(abs(village[playno].loc[0] - village[j].loc[0]), abs(village[playno].loc[1] - village[j].loc[1]));

        //village troops total attack
        int vattack=0;
        for(int i=0; i<maxtroops; i++){
            if (troops[j][i].status == "stationed") {
                vattack += troops[j][i].attack; //sum of villager troops attack
            }
        }

        if(j!=playno-1){ //can't attack their own village
            for(int i=0; i<village[playno].army; i++){
                if(army[playno][i].target == j){ //can't attack villages player is already attacking
                    ok = false;
                    break;
                }
            }
        }

        if(ok){
            vills[cnt] = {"Player "+to_string(cnt+1)+"'s Village - health "+to_string(village[cnt].health)+" - total attack "+to_string(vattack)+" - tools x"+to_string(resource[cnt][0].amount)+" - food x"+to_string(resource[cnt][1].amount)+" - money x"+to_string(resource[cnt][2].amount)+" - "+to_string(minstep)+" rounds to reach target "};
            cnt++;
        }
    }

    int villno = options(totplay-1,vills,texty+1, 1,false);
    refreshcli(playno);

    //create new army

    int ptroop = village[playno].troops;      //update village troop number

    //count troops by status
    int k=0,l=0,m=0;
    for(int i=0; i<ptroop; i++){
        if(troops[playno][i].type=="rookie"){
            k++;
        }else if(troops[playno][i].type=="expert"){
            l++;
        }else if(troops[playno][i].type=="master"){
            m++;
        }
    }

    int trooptot = k+l+m;
    if(trooptot==0){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: No troops available for battle!");
        return 1;
    }

    int rookie=0, expert=0, master=0;

    if(k>0){
        //ask for troops to send for battle
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

    Troops trps[trooptot];

    int tcnt=0;
    for(int i=0; i<maxtroops; i++){
        if(tcnt==rookie){
            break;
        }
        if(troops[playno][i].type=="rookie"){
            trps[tcnt] = troops[playno][i];
            tcnt++;
        }
    }

    for(int i=0; i<maxtroops; i++){
        if(tcnt==expert+rookie){
            break;
        }
        if(troops[playno][i].type=="expert"){
            trps[tcnt] = troops[playno][i];
            tcnt++;
        }
    }

    for(int i=0; i<maxtroops; i++){
        if(tcnt==master+expert+rookie){
            break;
        }
        if(troops[playno][i].type=="master"){
            trps[tcnt] = troops[playno][i];
            tcnt++;
        }
    }

    //segmentation fault: 11
    village[playno].army++;

    int acnt = village[playno].army-1;


    int res[] = {0,0,0};
    army[playno][acnt] = Army(trooptot, trps, res, villno);

    int vattack=0;
    int phealth = army[playno][acnt].health;        //sum of player troops health

    for(int i=0; i<maxtroops; i++){
        if(troops[villno][i].status=="stationed"){
            vattack += troops[villno][i].attack;    //sum of villager troops attack
        }
    }

    if(phealth<=vattack){
        refreshcli(playno);
        mvwprintw(win,erry,1,"Error: Not enough health to attack selected village! Try another army combo homedawg ¯\\_(ツ)_/¯.");
        return 1;
    }

    //army marching speed
    int mspeed = army[playno][acnt].speed;

    //if army successfully arrived
    if(marching(playno, acnt, villno, mspeed)){

        int pattack = army[playno][acnt].attack;

        //until player troop health = villager troops health
        while(phealth>vattack) {

            //kill player troop
            loop4:
            int rnd = (rand() %trooptot);
            if (army[playno][acnt].trps[rnd].status != "dead") {
                army[playno][acnt].trps[rnd].cost = 0;
                army[playno][acnt].trps[rnd].health = 0;
                army[playno][acnt].trps[rnd].attack = 0;
                army[playno][acnt].trps[rnd].carrycap = 0;
                army[playno][acnt].trps[rnd].speed = 0;
                army[playno][acnt].trps[rnd].status = "dead";
                army[playno][acnt].trps[rnd].type = "dead";
                village[playno].troops--;
            }else{
                goto loop4;
            }

            //kill villager troop
            loop5:
            rnd = (rand() %maxtroops);
            if (troops[villno][rnd].status == "stationed") {
                troops[villno][rnd].cost = 0;
                troops[villno][rnd].health = 0;
                troops[villno][rnd].attack = 0;
                troops[villno][rnd].carrycap = 0;
                troops[villno][rnd].speed = 0;
                troops[villno][rnd].status = "dead";
                troops[villno][rnd].type = "dead";
                village[villno].troops--;
            }else{
                goto loop5;
            }

            //recalculate health and attack
            army[playno][acnt] = Army(trooptot, trps, res, villno);

            phealth = army[playno][acnt].health;        //sum of player troops health
            vattack = 0;

            for(int i=0; i<maxtroops; i++){
                if (troops[villno][i].status == "stationed") {
                    vattack += troops[villno][i].attack; //sum of villager troops attack
                }
            }
        }

        //if at least one troop in player's army survives = success
        bool success;
        for(int i=0; i<trooptot; i++){
            if(army[playno][acnt].trps[i].status != "dead"){
                success=true;
                break;
            }else{
                success=false;
            }
        }

        if(success){

            refreshcli(playno);

            loop6:
            mvwprintw(win,texty,20,"ATTACK SUCCESSFUL!");
            mvwhline(win, texty+1, 1, '_', 80);

            //update army
            army[playno][acnt] = Army(trooptot, trps, res, villno);

            //sum of surviving player troops attack
            pattack = army[playno][acnt].attack;

            //reduce village health
            village[villno].health-= pattack;

            //army carrying capacity
            int carrycap = army[playno][acnt].carrycap;

            //steal resources
            mvwprintw(win,texty+2,1,"Your carrying capacity is %d!", carrycap);
            mvwprintw(win,texty+3,1,"How many of the following resources would you like to take:");

            int tools;
            int food;
            int money;

            mvwprintw(win,texty+4,1,"Tools");
            string tls[resource[villno][0].amount];
            for(int i=0; i<resource[villno][0].amount; i++){
                tls[i] = {to_string(i)};
            }
            tools = options(resource[villno][0].amount,tls,texty+5,1,true)-1;

            mvwprintw(win,texty+6,1,"Food");
            string fd[resource[villno][1].amount];
            for(int i=0; i<resource[villno][1].amount; i++){
                fd[i] = {to_string(i)};
            }
            food = options(resource[villno][1].amount,fd,texty+7,1,true)-1;

            mvwprintw(win,texty+8,1,"Money");
            string mny[resource[villno][2].amount];
            for(int i=0; i<resource[villno][2].amount; i++){
                mny[i] = {to_string(i)};
            }
            money = options(resource[villno][2].amount,mny,texty+9,1,true)-1;

            if(tools+food+money>carrycap){
                refreshcli(playno);
                mvwprintw(win,erry,1,"Error: Max carrying capacity exceeded! Pick resources again.");
                goto loop6;
            }

            resource[villno][0].amount -= tools;
            resource[villno][1].amount -= food;
            resource[villno][2].amount -= money;

            //update army marching speed
            mspeed=army[playno][acnt].speed;

            //surviving troops march back home
            marching(playno, acnt, playno, mspeed);
        }else{
            village[playno].army--;
        }
    }
    return 0;
}

int resurrect(int playno){

    //count dead troops
    int dead = 50-village[playno].troops;

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


    int loc[] = {village[playno].loc[0],village[playno].loc[1]};


    int cnt=0;
    for(int i=0; i<maxtroops; i++){

        if(cnt==elixir){
            break;
        }

        if(troops[playno][i].status == "dead"){
            troops[playno][i] = Troops(15,0,0,0,0,"stationed","untrained",loc);
            cnt++;
        }
    }

    refreshcli(playno);

    return 0;
}