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




void actions(int playno, int totplay){

    int resbno = village[playno].rbuildings;
    int troopbno = village[playno].tbuildings;

    int select=0;
    int cost;

    int funds = resource[playno][2].amount;
    int food = resource[playno][1].amount;

    int trooptot = village[playno].troops;

    while(select!=6){

        villagecli(playno);

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
                cout << "You have no buildings to upgrade yet!" << endl;
                goto loop;
            }

            cout << "Which building would you like to upgrade?" << endl;
            int count;
            int real[totbuild];
            int j=0;

            for(count=0; count<resbno; count++){
                real[count]=j;
                if(rbuild[playno][count].level<5){
                    cout << count+1 << ". Resource-generating - level " << rbuild[playno][count].level << " - type " << rbuild[playno][count].type << endl;
                }else{
                    count-=1;
                }
                j++;
            }
            for(int i=count; i<totbuild; i++){
                real[i]=j;
                if(rbuild[playno][i].level<5){
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
                    rbuild[playno][real[select]].level++;
                }else{
                    tbuild[playno][real[select]].level++;
                }
            }

            funds-=cost;

        }else if(select==3){ //train troops

            loop3:
            cout << "Which troops would you like to train?\n";

            int troopno;

            int k=0,l=0,m=0;
            for(int i=0; i<trooptot; i++){
                if(troops[playno][i].type=="untrained"){
                    k++;
                }else if(troops[playno][i].type=="rookie"){
                    l++;
                }else if(troops[playno][i].type=="expert"){
                    m++;
                }
            }

            cout << "1. Untrained troops x" << k << " available" << endl;
            cout << "2. Rookie troops x" << l << " available" << endl;
            cout << "3. Expert troops x" << m << " available" << endl;

            cin >> select;

            cout << "How many " << troops[playno][select-1].type << "troops would you like to upgrade?" << endl;
            cin >> troopno;

            int j=0;
            if(food<15*troopno){
                cout << "Not enough resources!\nPlease select another option:" << endl;
                goto loop;
            }else if(select==1){
                if(troopno>k){
                    cout << "Not enough troops!" << endl;
                    goto loop3;
                }else{
                    for(int i=0; i<trooptot; i++){
                        if(troops[playno][i].type==troops[playno][select-1].type){
                            troops[playno][i].type = "rookie";
                            j++;
                            if(j==troopno){
                                break;
                            }
                        }
                    }
                }
            }else if(select==2){
                if(troopno>l){
                    cout << "Not enough troops!" << endl;
                    goto loop3;
                }else{
                    for(int i=0; i<trooptot; i++){
                        if(troops[playno][i].type==troops[playno][select-1].type){
                            troops[playno][i].type = "expert";
                            j++;
                            if(j==troopno){
                                break;
                            }
                        }
                    }
                }
            }else if(select==3){
                if(troopno>m){
                    cout << "Not enough troops!" << endl;
                    goto loop3;
                }else{
                    for(int i=0; i<trooptot; i++){
                        if(troops[playno][i].type==troops[playno][select-1].type){
                            troops[playno][i].type = "master";
                            j++;
                            if(j==troopno){
                                break;
                            }
                        }
                    }
                }
            }

            food-=15*troopno;

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

        }else if(select==6){ //done

            break;
        }
    }
}