#include "villagegame.h"


void friendtroop(int playno){

    int trooptot = village[playno].troops;      //update village troop number
    int idx = village[playno].index;

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    //for each troop that made it back home
    for(int i=0; i<trooptot; i++){

        //set status to stationed
        troops[idx][i].status = "stationed";

        //transfer resources obtain to player and reset troop resources
        resource[playno][0].amount += troops[idx][i].resource[0];
        troops[idx][i].resource[0]=0;
        resource[playno][1].amount += troops[idx][i].resource[1];
        troops[idx][i].resource[1]=0;
        resource[playno][2].amount += troops[idx][i].resource[2];
        troops[idx][i].resource[2]=0;
    }
}

void enemytroop(int playno, int attackno){

    int ptroop = village[playno].troops;      //update village troop number
    int atroop = village[attackno].troops;

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    Troops troops[totplay][50];

    //winning probabilities
    int pwinprob=0;
    int awinprob=0;

    if(village[playno].troops>village[attackno].troops){
        pwinprob+=15;
    }else{awinprob+=15;}


    for(int i=0; i<ptroop; i++){
        if(troops[playno][i].type=="rookie"){
            pwinprob+=5;
        }else if(troops[playno][i].type=="expert"){
            pwinprob+=25;
        }else if(troops[playno][i].type=="master"){
            pwinprob+=75;
        }
    }

    for(int i=0; i<atroop; i++){
        if(troops[attackno][i].type=="rookie"){
            awinprob+=5;
        }else if(troops[attackno][i].type=="expert"){
            awinprob+=25;
        }else if(troops[attackno][i].type=="master"){
            awinprob+=75;
        }
    }

    if(pwinprob>=5*awinprob){

        //village losses
        village[attackno].health = 0;
        village[attackno].troops = round(village[attackno].troops*0.4);
        village[attackno].rbuildings = round(village[attackno].rbuildings*0.5);
        village[attackno].tbuildings = round(village[attackno].tbuildings*0.5);

    }else if(pwinprob>=3*awinprob){

        //village losses
        village[attackno].health = village[attackno].health*0.25;
        village[attackno].troops = round(village[attackno].troops*0.6);
        village[attackno].rbuildings = round(village[attackno].rbuildings*0.65);
        village[attackno].tbuildings = round(village[attackno].tbuildings*0.65);

        //attacker losses
        village[playno].troops = round(village[playno].troops*0.8);

    }else if(pwinprob>=1.5*awinprob){

        //village losses
        village[attackno].health = village[attackno].health*0.75;
        village[attackno].troops = round(village[attackno].troops*0.8);
        village[attackno].rbuildings = round(village[attackno].rbuildings*0.85);
        village[attackno].tbuildings = round(village[attackno].tbuildings*0.85);

        //attacker losses
        village[playno].troops = round(village[playno].troops*0.6);

    }else if(pwinprob<awinprob){

        //attacker losses
        village[playno].troops = round(village[playno].troops*0.4);
    }

    //update village troops
    for(int i=0; i<village[attackno].troops; i++){
        loop0:
        int rdm = rand() % 50;
        if(troops[playno][rdm].status != "dead"){
            troops[playno][rdm].status = "dead";
        }else{
            goto loop0;
        }
    }

    //update attacker troops
    for(int i=0; i<village[playno].troops; i++){
        loop:
        int rdm = rand() % 50;
        if(troops[playno][rdm].status != "dead"){
            troops[playno][rdm].status = "dead";
        }else{
            goto loop;
        }
    }

    //update carrying capacity
    int carrycap=0;      //total carrying capacity
    for(int i=0; i<50; i++){
        if(troops[playno][i].status != "dead"){
            carrycap += troops[playno][i].carrycap;
        }
    }

    cout<<"Your carrying capacity is %d!\nHow many of the following resources would you like to take:"<< carrycap << endl;

    int tools;
    int spinach;
    int money;

    loop1:
    cout<<"Tools [%d available]:"<<resource[attackno][0].amount;
    cin>>tools;
    if(tools>resource[attackno][0].amount){
        cout<<"Not enough resources available!"<<endl;
        goto loop1;
    }

    loop2:
    cout<<"Spinach [%d available]:"<<resource[attackno][1].amount;
    cin>>spinach;
    if(spinach>resource[attackno][1].amount){
        cout<<"Not enough resources available!"<<endl;
        goto loop2;
    }

    loop3:
    cout<<"Money [%d available]:"<<resource[attackno][2].amount;
    cin>>money;
    if(money>resource[attackno][2].amount){
        cout<<"Not enough resources available!"<<endl;
        goto loop3;
    }

    if(tools+spinach+money>carrycap){
        cout<<"Max carrying capacity exceeded!\n Pick again."<<endl;
        goto loop1;
    }

    resource[attackno][0].amount -= tools;
    resource[attackno][1].amount -= spinach;
    resource[attackno][2].amount -= money;
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


void attack(int playno, int villno){

    int ptroop = village[playno].troops;      //update village troop number
    int atroop = village[villno].troops;

    int *players = gamesetup();
    int totplay = players[0]+players[1];


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

    int rookie, expert, master;

    loop1:
    cout<<"How many rookie troops are you taking?"<<endl;
    cin>>rookie;
    if(rookie>k){
        cout<<"Not enough rookie troops available!"<<endl;
        goto loop1;
    }

    loop2:
    cout<<"How many expert troops are you taking?"<<endl;
    cin>>expert;
    if(expert>l){
        cout<<"Not enough expert troops available!"<<endl;
        goto loop2;
    }

    loop3:
    cout<<"How many master troops are you taking?"<<endl;
    cin>>master;
    if(master>m){
        cout<<"Not enough master troops available!"<<endl;
        goto loop3;
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
}


void actions(int playno){

    int resbno = village[playno].rbuildings;
    int troopbno = village[playno].tbuildings;

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    int select=0;
    int cost;

    int funds = resource[playno][2].amount;
    int food = resource[playno][1].amount;

    int trooptot = village[playno].troops;

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
                            troops[playno][i].type = "Rookie";
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
                            troops[playno][i].type = "Expert";
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
                            troops[playno][i].type = "Master";
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

            if(villno>totplay || villno<1){
                cout << "Invalid option!" << endl;
                goto loop;
            }else{
                enemytroop(playno,villno);
                friendtroop(playno);
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