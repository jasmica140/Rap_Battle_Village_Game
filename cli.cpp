#include "villagegame.h"

void mapcli(int playno){

    for(int v=0; v<(int)village.size(); v++){
        map[village[playno]->loc[0]][village[playno]->loc[1]].status = " CTY";
    }

    int acnt = (int)village[playno]->army.size();

    mvwprintw(win,10,120,"--MAP--");
    mvwprintw(win,10,148,"cities left: %d", village.size());
    wattron(win,COLOR_PAIR(2));

    int i,j,k,l;
    for(k=0; k<mapy; k++){
        for(i=0; i<mapx; i++){
            mvwprintw(win,11+(k*2),84+(i*6),"+-----");
        }
        mvwprintw(win,11+(k*2),84+(i*6),"+");

        for(i=0; i<mapy-2; i++){
            for(j=0; j<mapx; j++){
                mvwprintw(win,12+(k*2),84+(j*6), "|", map[j][k].status.c_str());

                wattron(win,COLOR_PAIR(3));

                //change color of current player's village
                if(j == village[playno]->loc[0] && k == village[playno]->loc[1]){
                    wattron(win, COLOR_PAIR(1));
                }

                //change color of current player's armies
                for(l=0; l<acnt; l++){
                    if(j == village[playno]->army[l]->loc[0] && k == village[playno]->army[l]->loc[1]) {
                        wattron(win, COLOR_PAIR(1));
                    }
                }

                mvwprintw(win,12+(k*2),85+(j*6), "%s", map[j][k].status.c_str());
                wattron(win,COLOR_PAIR(2));
            }
        }
        mvwprintw(win,12+(k*2),84+(j*6), "|");

    }

    for(i=0; i<mapx; i++){
        mvwprintw(win,11+(k*2),84+(i*6),"+-----");
    }
    mvwprintw(win,11+(k*2),84+(i*6),"+");
}

void villagecli(int playno){

    int vill = (int)village[playno]->rbuild.size() + (int)village[playno]->tbuild.size();

    int y=1;
    int x=2;

    wattron(win,COLOR_PAIR(4));

    if(vill==0){

        mvwprintw(win,y+1,x," \n");
        mvwprintw(win,y+2,x," \n");
        mvwprintw(win,y+3,x,"                                           .~.\n");
        mvwprintw(win,y+4,x,"                                     .~.   |\"|\n");
        mvwprintw(win,y+5,x,"                                     |\"|l_l|\"|\n");
        mvwprintw(win,y+6,x,"                                     |\"||_||\"|\n");
        mvwprintw(win,y+7,x,"                                     |\"!/|\\!\"|\n");
        mvwprintw(win,y+8,x,"                                     !//_:_\\\\!\n");

    }else if(vill==1){

        mvwprintw(win,y+1,x," \n");
        mvwprintw(win,y+2,x," \n");
        mvwprintw(win,y+3,x,"                                           .~.\n");
        mvwprintw(win,y+4,x,"                             .=======.~.   |\"|\n");
        mvwprintw(win,y+5,x,"                             |: :: ::|\"|l_l|\"|\n");
        mvwprintw(win,y+6,x,"                             ::: :: :|\"||_||\"|\n");
        mvwprintw(win,y+7,x,"                             |:===F=:|\"!/|\\!\"|\n");
        mvwprintw(win,y+8,x,"                             ![_][I_]!//_:_\\\\!\n");


    }else if(vill==2){

        mvwprintw(win,y+1,x," \n");
        mvwprintw(win,y+2,x," \n");
        mvwprintw(win,y+3,x,"                                           .~.===:\n");
        mvwprintw(win,y+4,x,"                             .=======.~.   |\"|: :|\n");
        mvwprintw(win,y+5,x,"                             |: :: ::|\"|l_l|\"|:: |\n");
        mvwprintw(win,y+6,x,"                             ::: :: :|\"||_||\"| : |\n");
        mvwprintw(win,y+7,x,"                             |:===F=:|\"!/|\\!\"|::F|\n");
        mvwprintw(win,y+8,x,"                             ![_][I_]!//_:_\\\\![]I!\n");

    }else if(vill==3){

        mvwprintw(win,y+1,x," \n");
        mvwprintw(win,y+2,x," \n");
        mvwprintw(win,y+3,x,"                                           .~.===:\n");
        mvwprintw(win,y+4,x,"                             .=======.~.   |\"|: :|\n");
        mvwprintw(win,y+5,x,"                             |: :: ::|\"|l_l|\"|:: |\n");
        mvwprintw(win,y+6,x,"                         |===::: :: :|\"||_||\"| : |\n");
        mvwprintw(win,y+7,x,"                         |:::|:===F=:|\"!/|\\!\"|::F|\n");
        mvwprintw(win,y+8,x,"                         ![_]![_][I_]!//_:_\\\\![]I!\n");

    } else if(vill==4){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|\n");
        mvwprintw(win,y+4,x,"                             .=======.~.   |\"|: :|::::::|\n");
        mvwprintw(win,y+5,x,"                             |: :: ::|\"|l_l|\"|:: |:;;:::|\n");
        mvwprintw(win,y+6,x,"                         |===::: :: :|\"||_||\"| : |: :: :|\n");
        mvwprintw(win,y+7,x,"                         |:::|:===F=:|\"!/|\\!\"|::F|:====:|\n");
        mvwprintw(win,y+8,x,"                         ![_]![_][I_]!//_:_\\\\![]I![_][_]!\n");

    } else if(vill==5){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|\n");
        mvwprintw(win,y+4,x,"                             .=======.~.   |\"|: :|::::::|\n");
        mvwprintw(win,y+5,x,"                       !_    |: :: ::|\"|l_l|\"|:: |:;;:::|\n");
        mvwprintw(win,y+6,x,"                      |: |===::: :: :|\"||_||\"| : |: :: :|\n");
        mvwprintw(win,y+7,x,"                      |::|:::|:===F=:|\"!/|\\!\"|::F|:====:|\n");
        mvwprintw(win,y+8,x,"                      ![]![_]![_][I_]!//_:_\\\\![]I![_][_]!\n");

    } else if(vill==6){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|\n");
        mvwprintw(win,y+4,x,"                             .=======.~.   |\"|: :|::::::|\n");
        mvwprintw(win,y+5,x,"                       !_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!\n");
        mvwprintw(win,y+6,x,"                      |: |===::: :: :|\"||_||\"| : |: :: :|: : |\n");
        mvwprintw(win,y+7,x,"                      |::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|\n");
        mvwprintw(win,y+8,x,"                      ![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]!\n");

    } else if(vill==7){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|\n");
        mvwprintw(win,y+4,x,"                .=====.      .=======.~.   |\"|: :|::::::|\n");
        mvwprintw(win,y+5,x,"                |:::::|!_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!\n");
        mvwprintw(win,y+6,x,"                |; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |\n");
        mvwprintw(win,y+7,x,"                |:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|\n");
        mvwprintw(win,y+8,x,"                !_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]!\n");

    } else if(vill==8){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|   ..===.\n");
        mvwprintw(win,y+4,x,"                .=====.      .=======.~.   |\"|: :|::::::|   ||:::|\n");
        mvwprintw(win,y+5,x,"                |:::::|!_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|\n");
        mvwprintw(win,y+6,x,"                |; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |\n");
        mvwprintw(win,y+7,x,"                |:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|\n");
        mvwprintw(win,y+8,x,"                !_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!\n");

    } else if(vill==9){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|   ..===.\n");
        mvwprintw(win,y+4,x,"                 .=====.      .=======.~.   |\"|: :|::::::|   ||:::|\n");
        mvwprintw(win,y+5,x,"              ,  |:::::|!_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|\n");
        mvwprintw(win,y+6,x,"              !__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |\n");
        mvwprintw(win,y+7,x,"             |:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|\n");
        mvwprintw(win,y+8,x,"             ![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!\n");

    } else if(vill==10){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|   ..===.\n");
        mvwprintw(win,y+4,x,"                 .=====.      .=======.~.   |\"|: :|::::::|   ||:::|=====|\n");
        mvwprintw(win,y+5,x,"              ,  |:::::|!_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|: : :|\n");
        mvwprintw(win,y+6,x,"              !__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |:::::|\n");
        mvwprintw(win,y+7,x,"             |:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|::__:|\n");
        mvwprintw(win,y+8,x,"             ![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!_[__]!\n");

    } else if(vill==11){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"                                           .~.===: : : :|   ..===.\n");
        mvwprintw(win,y+4,x,"                 .=====.      .=======.~.   |\"|: :|::::::|   ||:::|=====|\n");
        mvwprintw(win,y+5,x,"         !__.,  |:::::|!_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|: : :|\n");
        mvwprintw(win,y+6,x,"        |:: |!__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |:::::|\n");
        mvwprintw(win,y+7,x,"        |: :|:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|::__:|\n");
        mvwprintw(win,y+8,x,"        !_[]![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!_[__]!\n");

    } else if(vill==12){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"   .====.                                  .~.===: : : :|   ..===.\n");
        mvwprintw(win,y+4,x,"   |.::'|        .=====.      .=======.~.   |\"|: :|::::::|   ||:::|=====|\n");
        mvwprintw(win,y+5,x,"   | :::|!__.,  |:::::|!_    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|: : :|\n");
        mvwprintw(win,y+6,x,"   |::: |:: |!__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |:::::|\n");
        mvwprintw(win,y+7,x,"   | _::|: :|:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|::__:|\n");
        mvwprintw(win,y+8,x,"   ![_]_!_[]![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!_[__]!\n");

    } else if(vill>=13){
        mvwprintw(win,y+1,x,"                                                ..======..          \n");
        mvwprintw(win,y+2,x,"                                                ||::: : | .          \n");
        mvwprintw(win,y+3,x,"   .====.                                  .~.===: : : :|   ..===.\n");
        mvwprintw(win,y+4,x,"   |.::'||      .=====.,    ..=======.~,   |\"|: :|::::::|   ||:::|=====|\n");
        mvwprintw(win,y+5,x," __| :::|!__.,  |:::::|!_,   |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|: : :|\n");
        mvwprintw(win,y+6,x,"  :|::: |:: |!__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |:::::|\n");
        mvwprintw(win,y+7,x," ::| _::|: :|:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|::__:|\n");
        mvwprintw(win,y+8,x," []![_]_!_[]![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!_[__]!\n");
    }

    mvwprintw(win,y+9,x,"___________________________________|___________|________________________\n");
    mvwprintw(win,y+10,x," _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |= _ _:_ _ =| _ _ _ _ _ _ _ _ _ _ _ _\n");
    mvwprintw(win,y+11,x,"___________________________________|___________|________________________\n");
    mvwprintw(win,y+12,x,"                   _              .:::::::::::::.              _\n");
    mvwprintw(win,y+13,x,"                __(_)___         .:::::::::::::::.         ___(_)__\n");
    mvwprintw(win,y+14,x,"---------------/  / \\  /|       .:::::;;;:::;;::::.       |\\  / \\  \\------\n");
    mvwprintw(win,y+15,x,"______________/_______/ |      .::::::;;:::::;;::::.      | \\_______\\_______\n");
    mvwprintw(win,y+16,x,"|       |     [===  =] /|     .:::::;;;::::::;;;::::.     |\\ [==  = ]   |\n");
    mvwprintw(win,y+17,x,"|_______|_____[ = == ]/ |    .:::::;;;:::::::;;;:::::.    | \\[ ===  ]___|___\n");
    mvwprintw(win,y+18,x,"     |       |[  === ] /|   .:::::;;;::::::::;;;::::::.   |\\ [=  ===] |\n");
    mvwprintw(win,y+19,x,"_____|_______|[== = =]/ |  .:::::;;;::::::::::;;;::::::.  | \\[ ==  =]_|_____\n");
    mvwprintw(win,y+20,x," |       |    [ == = ] /| .::::::;;:::::::::::;;;:::::::. |\\ [== == ]      |\n");
    mvwprintw(win,y+21,x,"_|_______|____[=  == ]/ |.::::::;;:::::::::::::;;;:::::::.| \\[  === ]______|_\n");
    mvwprintw(win,y+22,x,"   |       |  [ === =] /.::::::;;::::::::::::::;;;::::::::.\\ [===  =]   |\n");

    wattron(win,COLOR_PAIR(1));

    y=2;

    mvwvline(win, 0, 117, '|', 9);
    mvwvline(win, 0, 140, '|', 9);
    mvwhline(win, y, 80, '-', 100);


    //count troops
    int k=0,l=0,m=0;
    for(auto & troop : village[playno]->troops){
        if(troop->type=="snoopdawgz"){
            k++;
        }else if(troop->type=="biggies"){
            l++;
        }else if(troop->type=="tupacs") {
            m++;
        }
    }

    int tt=0;
    for(const auto & i : village[playno]->army){
        tt+=i->troops.size();
    }

    wattron(win,COLOR_PAIR(3));
    mvwprintw(win,1,91,"Player %d's City",village[playno]->id+1);
    mvwprintw(win,y+1,82,"City health: %d",village[playno]->health);
    mvwprintw(win,y+2,82,"Gangstaz: %d",tt+village[playno]->troops.size());
    mvwprintw(win,y+3,82,"Crews: %d",village[playno]->army.size());
    mvwprintw(win,y+4,82,"Resource-generating buildings: %d",village[playno]->rbuild.size());
    mvwprintw(win,y+5,82,"Studios: %d",village[playno]->tbuild.size());


    mvwprintw(win,1,125,"Resources ");
    mvwprintw(win,y+1,119,"Connections: %d ",village[playno]->resource[0]->amount);
    mvwprintw(win,y+2,119,"Grub: %d ",village[playno]->resource[1]->amount);
    mvwprintw(win,y+3,119,"Dollaz: %d ",village[playno]->resource[2]->amount);


    mvwprintw(win,1,145,"Stationed Gangstaz ");
    mvwprintw(win,y+1,142,"Snoopdawgz: %d ",k);
    mvwprintw(win,y+2,142,"Biggies: %d ",l);
    mvwprintw(win,y+3,142,"Tupacs: %d ",m);
}

int alertcli(int playno, const string& type){

    wclear(win);
    wrefresh(win);

    wattron(win,COLOR_PAIR(1));
    mvwhline(win, 13, 65, '*', 40);
    mvwhline(win, 17, 65, '*', 40);
    mvwvline(win, 13, 65, '*', 4);
    mvwvline(win, 13, 105,'*', 5);
    box(win,0,0);

    int x = 25;
    int y = 8;

    wattron(win,COLOR_PAIR(2));

    mvwprintw(win,y,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⠶⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+1,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡞⠉⢹⡀⣾⠁⠀⠀⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+2,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀⣸⣇⣿⠀⠀⢸⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+3,x,"⣠⡤⣤⡀⠀⠀⠀⠀⠀⣠⣿⣷⣴⣿⣿⣿⡓⢲⡾⠀⠀⠀⠀⢀⣴⠛⠛⣷⠀⠀");
    mvwprintw(win,y+4,x,"⢿⡀⠀⠙⢶⣄⠀⢀⣾⡿⣿⣿⣿⣿⣿⣿⣿⣿⠇⣠⣴⣶⣿⣿⠁⢀⣷⠋⠀⠀");
    mvwprintw(win,y+5,x,"⠀⠙⢶⣦⡤⠉⠻⢿⣿⣧⡙⢛⠛⢻⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⡿⠟⠁⠀⠀⠀");
    mvwprintw(win,y+6,x,"⠀⠀⠀⠙⢿⣿⣆⣀⠉⠉⠙⠉⠀⠀⠉⣟⠁⠈⠠⣴⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+7,x,"⠀⠀⠀⠀⠀⢿⣧⣀⣀⣀⣤⣾⣿⣿⣿⣿⣧⣤⣠⣼⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+8,x,"⠀⠀⠀⠀⠀⠀⠙⠻⠿⢿⣿⣿⣿⡟⠻⣿⡿⠛⠋⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+9,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣷⡀⠀⠀⠀⠀⢻⡇⠀⣠⣤⡶⠖⠒⠲⣆⠀");
    mvwprintw(win,y+10,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⢶⣤⣀⣀⣼⡿⠋⠁⠀⢧⠀⠀⠀⢸⡆");
    mvwprintw(win,y+11,x,"⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣠⣤⡤⠴⠖⠛⠋⠉⠀⣀⡀⡄⠀⠀⢾⠀⠀⠀⢠⡧");
    mvwprintw(win,y+12,x,"⢀⣠⣤⣤⡶⠾⠿⠛⠛⠉⣉⣀⣀⣤⡴⠶⠾⠟⢛⣛⣫⣉⣄⣀⣠⣶⣶⡾⠟⠃");
    mvwprintw(win,y+13,x,"⢿⡟⠛⢁⣤⣤⣴⠶⢞⣛⣻⣭⣭⣵⡶⠷⠛⠚⠛⢿⣍⡉⠉⠉⣯⠉⠁⠀⠀⠀");
    mvwprintw(win,y+14,x,"⠸⣿⣿⣿⣿⡿⠿⠟⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠶⠶⠋⠀⠀⠀⠀⠀");
    mvwprintw(win,y+15,x,"⠀⠈⠉⣀⣀⣀⣀⡀⠀⢀⣀⣀⡀⠀⢀⣀⣀⣀⠀⣀⣀⠀⢀⣀⣀⣀⣀⣀⠀⠀");
    mvwprintw(win,y+16,x,"⠀⠀⠀⡇⠀⡦⡀⢹⡶⠃⡤⣄⠙⣦⠋⣤⣤⠈⢳⡄⠀⠳⡎⠀⢸⢸⠀⡟⠀⠀");
    mvwprintw(win,y+17,x,"⠀⠀⠀⡇⢀⣉⡀⢾⡇⠀⡇⢐⠀⣿⠀⣻⣺⠀⢸⠇⢰⠦⣼⠀⢘⢸⣀⡇⠀⠀");
    mvwprintw(win,y+18,x,"⠀⠀⠀⣇⠈⠷⠇⣠⢻⡀⠳⠾⣠⠿⣄⠘⠞⢀⡼⡆⢸⠀⢸⠀⢸⢼⢛⣧⠀⠀");
    mvwprintw(win,y+19,x,"⠀⠀⠀⠉⠉⠉⠉⠁⠀⠉⠉⠉⠉⠀⠈⠉⠉⠉⠀⠉⠉⠀⠈⠉⠉⠈⠉⠁⠀⠀");

    x = 115;
    mvwprintw(win,y,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡶⠶⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+1,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡞⠉⢹⡀⣾⠁⠀⠀⡷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+2,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀⣸⣇⣿⠀⠀⢸⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+3,x,"⣠⡤⣤⡀⠀⠀⠀⠀⠀⣠⣿⣷⣴⣿⣿⣿⡓⢲⡾⠀⠀⠀⠀⢀⣴⠛⠛⣷⠀⠀");
    mvwprintw(win,y+4,x,"⢿⡀⠀⠙⢶⣄⠀⢀⣾⡿⣿⣿⣿⣿⣿⣿⣿⣿⠇⣠⣴⣶⣿⣿⠁⢀⣷⠋⠀⠀");
    mvwprintw(win,y+5,x,"⠀⠙⢶⣦⡤⠉⠻⢿⣿⣧⡙⢛⠛⢻⣿⣿⣿⣿⣿⡿⢿⣿⣿⣿⡿⠟⠁⠀⠀⠀");
    mvwprintw(win,y+6,x,"⠀⠀⠀⠙⢿⣿⣆⣀⠉⠉⠙⠉⠀⠀⠉⣟⠁⠈⠠⣴⣿⣿⠟⠋⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+7,x,"⠀⠀⠀⠀⠀⢿⣧⣀⣀⣀⣤⣾⣿⣿⣿⣿⣧⣤⣠⣼⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+8,x,"⠀⠀⠀⠀⠀⠀⠙⠻⠿⢿⣿⣿⣿⡟⠻⣿⡿⠛⠋⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    mvwprintw(win,y+9,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣷⡀⠀⠀⠀⠀⢻⡇⠀⣠⣤⡶⠖⠒⠲⣆⠀");
    mvwprintw(win,y+10,x,"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⢶⣤⣀⣀⣼⡿⠋⠁⠀⢧⠀⠀⠀⢸⡆");
    mvwprintw(win,y+11,x,"⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣠⣤⡤⠴⠖⠛⠋⠉⠀⣀⡀⡄⠀⠀⢾⠀⠀⠀⢠⡧");
    mvwprintw(win,y+12,x,"⢀⣠⣤⣤⡶⠾⠿⠛⠛⠉⣉⣀⣀⣤⡴⠶⠾⠟⢛⣛⣫⣉⣄⣀⣠⣶⣶⡾⠟⠃");
    mvwprintw(win,y+13,x,"⢿⡟⠛⢁⣤⣤⣴⠶⢞⣛⣻⣭⣭⣵⡶⠷⠛⠚⠛⢿⣍⡉⠉⠉⣯⠉⠁⠀⠀⠀");
    mvwprintw(win,y+14,x,"⠸⣿⣿⣿⣿⡿⠿⠟⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠶⠶⠋⠀⠀⠀⠀⠀");
    mvwprintw(win,y+15,x,"⠀⠈⠉⣀⣀⣀⣀⡀⠀⢀⣀⣀⡀⠀⢀⣀⣀⣀⠀⣀⣀⠀⢀⣀⣀⣀⣀⣀⠀⠀");
    mvwprintw(win,y+16,x,"⠀⠀⠀⡇⠀⡦⡀⢹⡶⠃⡤⣄⠙⣦⠋⣤⣤⠈⢳⡄⠀⠳⡎⠀⢸⢸⠀⡟⠀⠀");
    mvwprintw(win,y+17,x,"⠀⠀⠀⡇⢀⣉⡀⢾⡇⠀⡇⢐⠀⣿⠀⣻⣺⠀⢸⠇⢰⠦⣼⠀⢘⢸⣀⡇⠀⠀");
    mvwprintw(win,y+18,x,"⠀⠀⠀⣇⠈⠷⠇⣠⢻⡀⠳⠾⣠⠿⣄⠘⠞⢀⡼⡆⢸⠀⢸⠀⢸⢼⢛⣧⠀⠀");
    mvwprintw(win,y+19,x,"⠀⠀⠀⠉⠉⠉⠉⠁⠀⠉⠉⠉⠉⠀⠈⠉⠉⠉⠀⠉⠉⠀⠈⠉⠉⠈⠉⠁⠀⠀");

    if(type=="attack"){
        mvwprintw(win,15,77,"CITY UNDER ATTACK!");

    }else if(type == "success"){
        mvwprintw(win,15,79,"BATTLE WON!");

    }else if(type == "fail"){
        mvwprintw(win,15,78,"ATTACK FAILED!");

    }else if(type == "destroy"){
        mvwprintw(win,15,71,"PLAYER %d'S CITY DESTROYED!",village[playno]->id+1);

    }else if(type == "round"){
        mvwprintw(win,15,82,"ROUND %d",playno);
        int choice = wgetch(win);
        if (choice == 10) {
            return 1;
        }
    }else if(type == "winner"){
        mvwprintw(win,15,76,"WINNER IS PLAYER %d!", village[playno]->id+1);
    }

    int choice = wgetch(win);
    if (choice == 10) {
        refreshcli(playno);
        return 1;
    }

    return 0;
}

int startcli(){

    wclear(win);
    wrefresh(win);

    wattron(win,COLOR_PAIR(1));
    mvwhline(win, 12, 45, '*', 90);
    mvwhline(win, 17, 45, '*', 90);
    mvwvline(win, 12, 45, '*', 5);
    mvwvline(win, 12, 135,'*', 6);
    box(win,0,0);

    wattron(win,COLOR_PAIR(2));

    mvwprintw(win,14,50,"In a world...");
    wgetch(win);
    mvwprintw(win,15,50,"Where Snoopdawgz, Biggies and Tupacs must rap together to defend their city...");
    wgetch(win);

    wclear(win);
    wrefresh(win);

    wattron(win,COLOR_PAIR(1));
    box(win,0,0);

    mvwhline(win, 10, 50, '*', 70);
    mvwhline(win, 14, 50, '*', 70);
    mvwvline(win, 10, 50, '*', 5);
    mvwvline(win, 10, 120,'*', 5);

    mvwhline(win, 20, 10, '*', 45);
    mvwhline(win, 30, 10, '*', 45);
    mvwvline(win, 20, 10, '*', 10);
    mvwvline(win, 20, 55,'*', 11);

    mvwhline(win, 20, 60, '*', 45);
    mvwhline(win, 30, 60, '*', 45);
    mvwvline(win, 20, 60, '*', 10);
    mvwvline(win, 20, 105,'*', 11);

    mvwhline(win, 20, 110, '*', 45);
    mvwhline(win, 30, 110, '*', 45);
    mvwvline(win, 20, 110, '*', 10);
    mvwvline(win, 20, 155,'*', 11);

    wattron(win,COLOR_PAIR(2));

    mvwprintw(win,12,55,"Win the game by building your city and going on rap battles!");

    mvwprintw(win,22,15,"Snoopdawgz have the most health");
    mvwprintw(win,23,15,"because they carry around");
    mvwprintw(win,24,15,"a bag of herbs that allows them");
    mvwprintw(win,25,15,"to replenish any lost health.");

    mvwprintw(win,22,65,"Biggies are a little chubby so ");
    mvwprintw(win,23,65,"they're the slowest but they have ");
    mvwprintw(win,24,65,"the most carrying capacity, making");
    mvwprintw(win,25,65,"it easier to steal resources from");
    mvwprintw(win,26,65,"surrounding cities.");

    mvwprintw(win,22,115,"Tupacs are peaceful gangstaz, but");
    mvwprintw(win,23,115,"don't mess with them because you ");
    mvwprintw(win,24,115,"best believe they will mess with ");
    mvwprintw(win,25,115,"you. Tupacs have the most attack.");

    wgetch(win);

    wclear(win);
    wrefresh(win);

    return 0;
}


void refreshcli(int playno){
    wclear(win);
    wrefresh(win);
    villagecli(playno);
    mvwprintw(win,2,2,"Player %d's turn!",village[playno]->id+1);
    mapcli(playno);

    wattron(win,COLOR_PAIR(1));

    //dividers
    mvwhline(win, 24, 1, '_', 80);
    mvwhline(win, 8, 80, '_', 100);
    mvwvline(win, 1, 80, '|', 38);
    mvwhline(win, 37, 1, '-', 79);


    //boarder
    box(win,0,0);

    wattron(win,COLOR_PAIR(3));

}
