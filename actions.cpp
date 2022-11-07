#include "villagegame.h"

void build(int playno){

    int bno;
    int select;

    refreshcli(playno);

    loop:
    mvwprintw(win,texty,1,"Select building type: \n");
    string choices[]={"1.Resource-generating","2.Troop-training"};
    select = options(2,choices);

    refreshcli(playno);

    int type;

    if(select==1){
        mvwprintw(win,texty,1,"Select a resource to generate:\n");
        string types[]={"1.Tools","2.Food","3.Money"};
        type = options(3,types);

    }else if(select==2){
        mvwprintw(win,texty,1,"Select the type of troops to train:\n");
        string types[]={"1.Untrained","2.Rookies","3.Experts"};
        type = options(3,types);
    }

    refreshcli(playno);

    loop2:
    mvwprintw(win,texty,1,"How many buildings would you like to build? ");
    bno = wgetch(win)-48;

    refreshcli(playno);

    if(bno<1){
        mvwprintw(win,texty+1,1,"At least one building required!");
        refreshcli(playno);
        goto loop2;
    }

    int cost = bno*35;
    if(resource[playno][2].amount<cost){
        mvwprintw(win,texty,1,"Insufficient funds!\nPlease select another option:");
        goto loop;
    }

    if(select==1){ //resource
        village[playno].rbuildings+=bno;

        for(int i=village[playno].rbuildings-bno; i<village[playno].rbuildings; i++){
            rbuild[playno][i].level = 1;
            rbuild[playno][i].type = resource[playno][type-1].type;
        }

    }else{ //training
        village[playno].tbuildings+=bno;

        for(int i=village[playno].tbuildings-1; i<village[playno].tbuildings+bno-1; i++){
            rbuild[playno][i].level = 1;
            if(type==1){
                tbuild[playno][i].type = "untrained";
            }else if(type==2){
                tbuild[playno][i].type = "rookie";
            }else if(type==3){
                tbuild[playno][i].type = "expert";
            }
        }
    }

    resource[playno][2].amount-=cost;
}

int upgrade(int playno){

    int select;

    int totbuild = village[playno].rbuildings+village[playno].tbuildings;

    if(totbuild==0){
        mvwprintw(win,texty,1,"You have no buildings to upgrade yet!");
        return 1;
    }

    mvwprintw(win,texty,1,"Select a building to upgrade:");

    int count;
    int real[totbuild];
    int j=0;
    int i=0;

    string choices[totbuild];

    for(count=0; count<village[playno].rbuildings; count++){
        real[count]=j;
        if(rbuild[playno][count].level<5){
            choices[count] = {to_string(count+1) + ". Resource-generating - level " + to_string(rbuild[playno][count].level) + " - generates " + rbuild[playno][count].type};
        }else{
            count-=1;
        }
        j++;
    }
    for(i=count; i<totbuild; i++){
        real[i]=j;
        if(rbuild[playno][i].level<5){
            choices[i] = {to_string(i+1) + ". Troop-training - level "  + to_string(tbuild[playno][i].level+1) + " - trains " + tbuild[playno][i].type};
        }else{
            if(i!=totbuild-1){
                i-=1;
            }
        }
        j++;
    }
    select = options(i,choices);

    refreshcli(playno);

    if(resource[playno][0].amount<15){
        mvwprintw(win,texty,1,"Insufficient funds!\n Please select another option:");
        return 1;
    }else{
        if(select<count+1){
            rbuild[playno][real[select-1]].level++;
        }else{
            tbuild[playno][real[select-1]].level++;
        }
    }

    resource[playno][2].amount-=15;
    return 0;
}

int train(int playno){

    int select;

    loop3:
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

    string choices[] = {"1. Untrained troops x"+to_string(k)+" available",
                       "2. Rookie troops x"+ to_string(l) +" available",
                       "3. Expert troops x" + to_string(m) + " available"};
    select = options(3,choices);

    mvwprintw(win,texty,1,"How many %s troops would you like to upgrade? ",troops[playno][select-1].type.c_str());
    troopno = wgetch(win);

    int j=0;
    if(select==1){ //rookies

        if(resource[playno][1].amount<15*troopno){
            mvwprintw(win,texty,1,"Not enough resources!");
            return 1;
        }else{
            if(troopno>k){
                mvwprintw(win,texty,1,"Not enough troops!");
                goto loop3;
            }else{
                for(int i=0; i<village[playno].troops; i++){
                    if(troops[playno][i].type==troops[playno][select-1].type){
                        troops[playno][i].type = "rookie";
                        resource[playno][1].amount-=troops[playno][j].cost;
                        j++;
                        if(j==troopno){
                            break;
                        }
                    }
                }
            }
        }

    }else if(select==2){ //expert

        if(resource[playno][1].amount<15*troopno){
            mvwprintw(win,texty,1,"Not enough resources!");
            return 1;
        }else{
            if(troopno>l){
                mvwprintw(win,texty,1,"Not enough troops!");
                goto loop3;
            }else{
                for(int i=0; i<village[playno].troops; i++){
                    if(troops[playno][i].type==troops[playno][select-1].type){
                        troops[playno][i].type = "expert";
                        resource[playno][1].amount-=troops[playno][j].cost;
                        j++;
                        if(j==troopno){
                            break;
                        }
                    }
                }
            }
        }

    }else if(select==3){ //master

        if(resource[playno][1].amount<15*troopno){
            mvwprintw(win,texty,1,"Not enough resources!");
            return 1;
        }else{
            if(troopno>m){
                mvwprintw(win,texty,1,"Not enough troops!");
                goto loop3;
            }else{
                for(int i=0; i<village[playno].troops; i++){
                    if(troops[playno][i].type==troops[playno][select-1].type){
                        troops[playno][i].type = "master";
                        resource[playno][1].amount-=troops[playno][j].cost;
                        j++;
                        if(j==troopno){
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}


void attack(int playno, int villno, int totplay){

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

    //ask for troops to send for battle
    cout<<"Troops available for battle:"<<endl;
    cout<<"1.Rookie troops x"<<k<<endl;
    cout<<"2.Expert troops x"<<l<<endl;
    cout<<"3.Master troops x"<<m<<endl;

    int rookie=0, expert=0, master=0;

    loop1:
    cout<<"How many rookie troops are you taking?"<<endl;
    cin>>rookie;
    if(rookie>k){
        cout<<"Not enough rookie troops available!"<<endl;
        goto loop1;
    }else{
        for(int i=0; i<rookie; i++){
            if(troops[playno][i].type=="rookie"){
                troops[playno][i].status="army";
                troops[playno][i].army = true;
            }
        }
    }

    loop2:
    cout<<"How many expert troops are you taking?"<<endl;
    cin>>expert;
    if(expert>l){
        cout<<"Not enough expert troops available!"<<endl;
        goto loop2;
    }else{
        for(int i=0; i<expert; i++){
            if(troops[playno][i].type=="expert"){
                troops[playno][i].status="army";
                troops[playno][i].army = true;
            }
        }
    }

    loop3:
    cout<<"How many master troops are you taking?"<<endl;
    cin>>master;
    if(master>m){
        cout<<"Not enough master troops available!"<<endl;
        goto loop3;
    }else{
        for(int i=0; i<master; i++){
            if(troops[playno][i].type=="master"){
                troops[playno][i].status="army";
                troops[playno][i].army = true;
            }
        }
    }

    //army marching speed
    int mspeed;
    if(rookie>0){
        mspeed = 10;
    }else if(expert>0){
        mspeed=15;
    }else{
        mspeed = 25;
    }

    //if army successfully arrived
    if(marching(playno, villno, mspeed)){

        int pattack=0;
        int vattack=0;
        int phealth=0;

        for(int i=0; i<maxtroops; i++){
            if(troops[playno][i].status=="army"){
                pattack += troops[playno][i].attack; //sum of player troops attack
                phealth += troops[playno][i].health; //sum of player troops health
            }
        }

        for(int i=0; i<maxtroops; i++){
            if(troops[villno][i].status=="stationed"){
                vattack += troops[villno][i].attack; //sum of villager troops attack
            }
        }

        //until player troop health = villager troops health
        while(phealth>vattack) {

            //kill player troop
            loop4:
            int rnd = (rand() %maxtroops);
            if (troops[playno][rnd].status == "army") {
                troops[playno][rnd].cost = 0;
                troops[playno][rnd].health = 0;
                troops[playno][rnd].attack = 0;
                troops[playno][rnd].carrycap = 0;
                troops[playno][rnd].speed = 0;
                troops[playno][rnd].status = "dead";
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
            }else{
                goto loop5;
            }

            //recalculate health and attack
            vattack=0;
            phealth=0;
            for(int i=0; i<maxtroops; i++){
                if(troops[playno][i].status=="army"){
                    phealth += troops[playno][i].health; //sum of player troops health
                }
                if (troops[villno][rnd].status == "stationed") {
                    vattack += troops[villno][i].attack; //sum of villager troops attack
                }
            }
        }

        bool success;
        for(int i=0; i<maxtroops; i++){
            if(troops[playno][i].army && troops[playno][i].status != "dead"){
                success=true;
                break;
            }else{
                success=false;
            }
        }

        if(success){

            //sum of surviving player troops attack
            for(int i=0; i<maxtroops; i++){
                if(troops[playno][i].army && troops[playno][i].status != "dead"){
                    pattack += troops[playno][i].attack;
                }
            }

            //reduce village health
            village[villno].health-= pattack;


            //calculate carrying capacity
            int carrycap=0;
            for(int i=0; i<50; i++){
                if(troops[playno][i].army && troops[playno][i].status != "dead"){
                    carrycap += troops[playno][i].carrycap;
                }
            }

            //steal resources
            cout<<"Your carrying capacity is "<< carrycap <<"!\nHow many of the following resources would you like to take:"<< endl;

            int tools;
            int spinach;
            int money;

            loop6:
            cout<<"Tools [" <<resource[villno][0].amount<<" available]:";
            cin>>tools;
            if(tools>resource[villno][0].amount){
                cout<<"Not enough resources available!"<<endl;
                goto loop6;
            }

            loop7:
            cout<<"Spinach ["<<resource[villno][1].amount<<" available]:";
            cin>>spinach;
            if(spinach>resource[villno][1].amount){
                cout<<"Not enough resources available!"<<endl;
                goto loop7;
            }

            loop8:
            cout<<"Money ["<<resource[villno][2].amount<<" available]:";
            cin>>money;
            if(money>resource[villno][2].amount){
                cout<<"Not enough resources available!"<<endl;
                goto loop8;
            }

            if(tools+spinach+money>carrycap){
                cout<<"Max carrying capacity exceeded!\n Pick resources again."<<endl;
                goto loop6;
            }

            resource[villno][0].amount -= tools;
            resource[villno][1].amount -= spinach;
            resource[villno][2].amount -= money;

            //update army marching speed
            mspeed=0;
            for(int i=0; i<maxtroops; i++){
                if(troops[playno][i].army && troops[playno][i].status == "rookie"){
                    mspeed = 10;
                }
            }

            if(mspeed==0){
                for(int i=0; i<maxtroops; i++){
                    if(troops[playno][i].army && troops[playno][i].status == "expert"){
                        mspeed = 15;
                    }
                }
            }

            if(mspeed==0){
                mspeed=25;
            }

            //surviving troops march back home
            marching(playno, playno, mspeed);
        }
    }
}

