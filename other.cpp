#include "villagegame.h"

void deleteplayer(int playno){

    //delete village
    map[village[playno]->loc[0]][village[playno]->loc[1]].status = "     ";

    for(int v=0; v<(int)village.size(); v++){ //search for villages destroyed player is attacking
        for(int j=0; j<village[playno]->army.size(); j++){
            if(village[v]->idx == village[playno]->army[j]->target){
                village[v]->attack=false;
            }
        }
    }

    //send attacking army home
    for(int i=0; i<(int)village.size(); i++){ //for each village
        for(int j=0; j<(int)village[i]->army.size(); j++){ //for each army
            if(village[i]->army[j]->target==village[playno]->idx){ //if village target is destroyed village
                village[i]->army[j]->comeHome = true;
                village[i]->army[j]->target = village[i]->idx; //send home
            }
        }
    }

    village.erase(village.begin() + playno);

    for(int v=0; v<(int)village.size(); v++){ //search for villages destroyed player is attacking
        for(int i=0; i<(int)village.size(); i++){
            for(int j=0; j<(int)village[i]->army.size(); j++){
                if(village[v]->idx == village[i]->army[j]->target && !village[i]->army[j]->comeHome){
                    village[v]->attack=true;
                }
            }
        }
    }
}



int options(int n, string choices[],int y, int x, bool sameline){

    int choice;
    int hl=0;
    int lim = 25;

    while(true) {

        int xspace=0;
        int yspace=0;

        for (int i = 0; i < n; i++, xspace++) {

            if(i%lim==0 && i!=0){ //for every 25th element
                yspace++; //new line
                xspace=0;
            }

            if (i == hl) {
                wattron(win, A_REVERSE);
            }
            if(sameline){

                if(choices[i].length() == 3){
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
