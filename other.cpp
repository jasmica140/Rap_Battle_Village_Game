#include "villagegame.h"

void deleteplayer(int playno){

    //delete village
    map[village[playno]->loc[0]][village[playno]->loc[1]].status = "     ";

    for(int v=0; v<(int)village.size(); v++){ //search for villages destroyed player is attacking
        for(int j=0; j<(int)village[playno]->army.size(); j++){
            if(village[v]->id == village[playno]->army[j]->target){
                village[v]->attack=false;
            }
        }
    }

    //send attacking army home
    for(int i=0; i<(int)village.size(); i++){ //for each village
        for(int j=0; j<(int)village[i]->army.size(); j++){ //for each army
            if(village[i]->army[j]->target==village[playno]->id){ //if village target is destroyed village
                village[i]->army[j]->comeHome = true;
                village[i]->army[j]->target = village[i]->id; //send home
            }
        }
    }

    village.erase(village.begin() + playno);

    for(int v=0; v<(int)village.size(); v++){ //search for villages destroyed player is attacking
        for(int i=0; i<(int)village.size(); i++){
            for(int j=0; j<(int)village[i]->army.size(); j++){
                if(village[v]->id == village[i]->army[j]->target && !village[i]->army[j]->comeHome){
                    village[v]->attack=true;
                }
            }
        }
    }
}



int options(int n, string choices[],int y, int x, bool sameline){

    int choice, lim, hl=0;
    bool multi = false;

    for(int i = 0; i < n; i++){
        if(choices[i].length() == 3){
            multi=true;
            break;
        }
    }

    while(true) {
        int xspace=0, yspace=0;
        for (int i = 0; i < n; i++, xspace++) {

            if(x==textx && ((x+(xspace*3)>=55 && multi) || x+(xspace*3)>=70)){
                yspace++; //new line
                xspace=0;
            }

            if (i == hl) {
                wattron(win, A_REVERSE);
            }

            if(sameline){
                if(multi){
                    mvwprintw(win, y+yspace, x+(xspace*4), choices[i].c_str());
                }else{
                    mvwprintw(win, y+yspace, x+(xspace*3), choices[i].c_str());
                }
                wattroff(win, A_REVERSE);
            }else{
                mvwprintw(win, y+i, x, choices[i].c_str());
                wattroff(win, A_REVERSE);
            }
        }

        choice = wgetch(win);

        if(sameline){
            if(!multi){
                lim=23;
            }else{
                lim=18;
            }
            switch(choice) {

                case KEY_LEFT:
                    hl--;
                    if (hl == -1) {
                        hl = 0;
                    }
                    break;

                case KEY_RIGHT:
                    hl++;
                    if (hl == n) {
                        hl = n - 1;
                    }
                    break;

                case KEY_UP:
                    hl-=lim;
                    if (hl < 0) {
                        hl+=lim;
                    }
                    break;

                case KEY_DOWN:
                    hl+=lim;
                    if (hl >= n) {
                        hl-= lim;
                    }
                    break;
            }
        }else{
            switch(choice) {

                case KEY_UP:
                    hl--;
                    if (hl == -1) {
                        hl = 0;
                    }
                    break;

                case KEY_DOWN:
                    hl++;
                    if (hl == n) {
                        hl = n - 1;
                    }
                    break;
            }
        }

        if (choice == 10) {
            break;
        }
    }
    return hl+1;
}
