#include "villagegame.h"

void deleteplayer(int playno){

    int idx;
    for(idx=0; idx<playno; idx++){}

    //delete village
    map[village[playno]->loc[0]][village[playno]->loc[1]].status = "     ";
    village.erase(village.begin() + idx);


    for(int i=playno; i<village.size(); i++){

        //delete resources
        for(int j=0; j<4; j++){
            resource[i][j] = resource[i+1][j];
        }

        //delete resource buildings
        for(int j=0; j<maxrbuild; j++){
            rbuild[i][j] = rbuild[i+1][j];
        }

        //delete training buildings
        for(int j=0; j<maxtbuild; j++){
            tbuild[i][j] = tbuild[i+1][j];
        }
    }
}



int options(int n, string choices[n],int y, int x, bool sameline){

    int choice;
    int hl=0;

    while(true) {

        int xspace=0;
        int yspace=0;

        for (int i = 0; i < n; i++, xspace++) {

            if(i%20==0 && i!=0){
                yspace++;
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
                    hl=-20;
                    if (hl < 0) {
                        hl+=20;
                    }
                    break;

                case KEY_DOWN:
                    hl=+20;
                    if (hl >= n) {
                        hl-= 20;
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
