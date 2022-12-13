#include "villagegame.h"

void mapcli(int playno){

    for(int v=0; v<village.size(); v++){
        map[village[playno]->loc[0]][village[playno]->loc[1]].status = "  V  ";
    }

    int acnt = (int)village[playno]->army.size();

    mvwprintw(win,10,120,"--MAP--");
    mvwprintw(win,10,147,"villages left: %d", village.size());
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

    int y=2;
    int x=2;

    wattron(win,COLOR_PAIR(4));

    if(vill==0){

        mvwprintw(win,y+1,x,"                   _                                       |\n");
        mvwprintw(win,y+2,x,"    ____________ .' '.                                    / \\\n");
        mvwprintw(win,y+3,x,"   //// ////// /V_.-._\\                                  /___\\\n");
        mvwprintw(win,y+4,x,"  // /// // ///==\\ u |.                                 .| u |_ _ _ _ _ _\n");

    }else if(vill==1){

        mvwprintw(win,y+1,x,"                   _                                       |\n");
        mvwprintw(win,y+2,x,"    ____________ .' '.                       /========\\   / \\\n");
        mvwprintw(win,y+3,x,"   //// ////// /V_.-._\\                      | u    u |  /___\\\n");
        mvwprintw(win,y+4,x,"  // /// // ///==\\ u |.                      |   ||   | .| u |_ _ _ _ _ _\n");

    }else if(vill==2){

        mvwprintw(win,y+1,x,"                   _                      _                |\n");
        mvwprintw(win,y+2,x,"    ____________ .' '.                  .' './========\\   / \\\n");
        mvwprintw(win,y+3,x,"   //// ////// /V_.-._\\                |-----| u    u |  /___\\\n");
        mvwprintw(win,y+4,x,"  // /// // ///==\\ u |.                | |T| |   ||   | .| u |_ _ _ _ _ _\n");

    }else if(vill==3){

        mvwprintw(win,y+1,x,"                   _                      _                |\n");
        mvwprintw(win,y+2,x,"    ____________ .' '.              /-\\ .' './========\\   / \\\n");
        mvwprintw(win,y+3,x,"   //// ////// /V_.-._\\            | _ |-----| u    u |  /___\\\n");
        mvwprintw(win,y+4,x,"  // /// // ///==\\ u |.            ||||| |T| |   ||   | .| u |_ _ _ _ _ _\n");

    } else if(vill==4){

        mvwprintw(win,y+1,x,"                   _                      _                |\n");
        mvwprintw(win,y+2,x,"    ____________ .' '.         /----/-\\ .' './========\\   / \\\n");
        mvwprintw(win,y+3,x,"   //// ////// /V_.-._\\        |===| _ |-----| u    u |  /___\\\n");
        mvwprintw(win,y+4,x,"  // /// // ///==\\ u |.        |===||||| |T| |   ||   | .| u |_ _ _ _ _ _\n");

    } else if(vill>=5){

        mvwprintw(win,y+1,x,"                   _                      _                |\n");
        mvwprintw(win,y+2,x,"    ____________ .' '.    _____/----/-\\ .' './========\\   / \\\n");
        mvwprintw(win,y+3,x,"   //// ////// /V_.-._\\  |.-.-.|===| _ |-----| u    u |  /___\\\n");
        mvwprintw(win,y+4,x,"  // /// // ///==\\ u |.  || | ||===||||| |T| |   ||   | .| u |_ _ _ _ _ _\n");
    }


    mvwprintw(win,y,x,"                                                           |>>>\n");
    mvwprintw(win,y+5,x," ///////-\\////====\\==|:::::::::::::::::::::::::::::::::::|u u| U U U U U\n");
    mvwprintw(win,y+6,x," |----/\\u |--|++++|..|'''''''''''::::::::::::::''''''''''|+++|+-+-+-+-+-+\n");
    mvwprintw(win,y+7,x," |u u|u | |u ||||||..|              '::::::::'           |===|>=== _ _ ==\n");
    mvwprintw(win,y+8,x," |===|  |u|==|++++|==|              .::::::::.           | T |....| V |..\n");
    mvwprintw(win,y+9,x," |u u|u | |u ||HH||         \\|/    .::::::::::.\n");
    mvwprintw(win,y+10,x," |===|_.|u|_.|+HH+|_              .::::::::::::.              _\n");
    mvwprintw(win,y+11,x,"                __(_)___         .::::::::::::::.         ___(_)__\n");
    mvwprintw(win,y+12,x,"---------------/  / \\  /|       .:::::;;;:::;;:::.       |\\  / \\  \\-------\n");
    mvwprintw(win,y+13,x,"______________/_______/ |      .::::::;;:::::;;:::.      | \\_______\\________\n");
    mvwprintw(win,y+14,x,"|       |     [===  =] /|     .:::::;;;::::::;;;:::.     |\\ [==  = ]   |\n");
    mvwprintw(win,y+15,x,"|_______|_____[ = == ]/ |    .:::::;;;:::::::;;;::::.    | \\[ ===  ]___|____\n");
    mvwprintw(win,y+16,x,"     |       |[  === ] /|   .:::::;;;::::::::;;;:::::.   |\\ [=  ===] |\n");
    mvwprintw(win,y+17,x,"_____|_______|[== = =]/ |  .:::::;;;::::::::::;;;:::::.  | \\[ ==  =]_|______\n");
    mvwprintw(win,y+18,x," |       |    [ == = ] /| .::::::;;:::::::::::;;;::::::. |\\ [== == ]      |\n");
    mvwprintw(win,y+19,x,"_|_______|____[=  == ]/ |.::::::;;:::::::::::::;;;::::::.| \\[  === ]______|_\n");
    mvwprintw(win,y+20,x,"   |       |  [ === =] /.::::::;;::::::::::::::;;;:::::::.\\ [===  =]   |\n");
    mvwprintw(win,y+21,x,"___|_______|__[ == ==]/.::::::;;;:::::::::::::::;;;:::::::.\\[=  == ]___|_____");


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

    wattron(win,COLOR_PAIR(3));
    mvwprintw(win,y,86,"Player %d's Village:",village[playno]->idx+1);
    mvwprintw(win,y+1,86,"Village health: %d",village[playno]->health);
    mvwprintw(win,y+2,86,"Troops: %d",village[playno]->troops.size());
    mvwprintw(win,y+3,86,"Armies: %d",village[playno]->army.size());
    mvwprintw(win,y+4,86,"Resource-generating buildings: %d",village[playno]->rbuild.size());
    mvwprintw(win,y+5,86,"Troop-training buildings: %d",village[playno]->tbuild.size());


    mvwprintw(win,y,121,"Resources: ");
    mvwprintw(win,y+1,121,"Tools: %d ",village[playno]->resource[0]->amount);
    mvwprintw(win,y+2,121,"Food: %d ",village[playno]->resource[1]->amount);
    mvwprintw(win,y+3,121,"Money: %d ",village[playno]->resource[2]->amount);


    mvwprintw(win,y,136,"Stationed Troops: ");
    mvwprintw(win,y+1,136,"Snoopdawgz: %d ",k);
    mvwprintw(win,y+2,136,"Biggies: %d ",l);
    mvwprintw(win,y+3,136,"Tupacs: %d ",m);
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
    mvwprintw(win,y,x,"  ,   |           ");
    mvwprintw(win,y+1,x," / \\, | ,        .--.");
    mvwprintw(win,y+2,x,"|    =|= >      /.--.\\");
    mvwprintw(win,y+3,x," \\ /` | `       |====|");
    mvwprintw(win,y+4,x,"  `   |         |`::`|");
    mvwprintw(win,y+5,x,"      |     .-;`\\..../`;_.-^-._");
    mvwprintw(win,y+6,x,"     /\\/  /  |...::..|`   :   `|");
    mvwprintw(win,y+7,x,"     |:'\\ |   /'''::''|   .:.   |");
    mvwprintw(win,y+8,x,"      \\ /\\;-,/\\   ::  |..:::::..|");
    mvwprintw(win,y+9,x,"      |\\ <` >  >._::_.| ':::::' |");
    mvwprintw(win,y+10,x,"      | `\"\"`  /   ^^  |   ':'   |");
    mvwprintw(win,y+11,x,"      |       |       \\    :    /");
    mvwprintw(win,y+12,x,"      |       |        \\   :   /");
    mvwprintw(win,y+13,x,"      |       |___/\\___|`-.:.-`");
    mvwprintw(win,y+14,x,"      |        \\_ || _/    `");
    mvwprintw(win,y+15,x,"      |        <_ >< _>");
    mvwprintw(win,y+16,x,"      |        |  ||  |");
    mvwprintw(win,y+17,x,"      |        |  ||  |");
    mvwprintw(win,y+18,x,"      |       _\\.:||:./_");
    mvwprintw(win,y+19,x,"      |      /____/\\____\\");

    x = 110;
    mvwprintw(win,y,x,"  ,   |           ");
    mvwprintw(win,y+1,x," / \\, | ,        .--.");
    mvwprintw(win,y+2,x,"|    =|= >      /.--.\\");
    mvwprintw(win,y+3,x," \\ /` | `       |====|");
    mvwprintw(win,y+4,x,"  `   |         |`::`|");
    mvwprintw(win,y+5,x,"      |     .-;`\\..../`;_.-^-._");
    mvwprintw(win,y+6,x,"     /\\/  /  |...::..|`   :   `|");
    mvwprintw(win,y+7,x,"     |:'\\ |   /'''::''|   .:.   |");
    mvwprintw(win,y+8,x,"      \\ /\\;-,/\\   ::  |..:::::..|");
    mvwprintw(win,y+9,x,"      |\\ <` >  >._::_.| ':::::' |");
    mvwprintw(win,y+10,x,"      | `\"\"`  /   ^^  |   ':'   |");
    mvwprintw(win,y+11,x,"      |       |       \\    :    /");
    mvwprintw(win,y+12,x,"      |       |        \\   :   /");
    mvwprintw(win,y+13,x,"      |       |___/\\___|`-.:.-`");
    mvwprintw(win,y+14,x,"      |        \\_ || _/    `");
    mvwprintw(win,y+15,x,"      |        <_ >< _>");
    mvwprintw(win,y+16,x,"      |        |  ||  |");
    mvwprintw(win,y+17,x,"      |        |  ||  |");
    mvwprintw(win,y+18,x,"      |       _\\.:||:./_");
    mvwprintw(win,y+19,x,"      |      /____/\\____\\");


    if(type=="attack"){
        mvwprintw(win,15,75,"VILLAGE UNDER ATTACK!");

    }else if(type == "success"){
        mvwprintw(win,15,77,"ATTACK SUCCESSFUL!");

    }else if(type == "fail"){
        mvwprintw(win,15,78,"ATTACK FAILED!");

    }else if(type == "destroy"){
        mvwprintw(win,15,71,"PLAYER %d'S VILLAGE DESTROYED!",village[playno]->idx+1);

    }else if(type == "round"){
        mvwprintw(win,15,82,"ROUND %d",playno);
        int choice = wgetch(win);
        if (choice == 10) {
            return 1;
        }
    }else if(type == "winner"){
        mvwprintw(win,15,76,"WINNER IS PLAYER %d!", village[playno]->idx+1);
    }else if(type == "test1") {
        mvwprintw(win, 15, 78, "TEST TWO!!!!!!!!");
    }else if(type == "test2") {
        mvwprintw(win, 15, 78, "******** TEST ONE");
    }

    int choice = wgetch(win);
    if (choice == 10) {
        refreshcli(playno);
        return 1;
    }

    return 0;
}

void refreshcli(int playno){
    wclear(win);
    wrefresh(win);
    villagecli(playno);
    mvwprintw(win,2,2,"Player %d's turn!",village[playno]->idx+1);
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
