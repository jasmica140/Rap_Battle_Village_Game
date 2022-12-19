#include "villagegame.h"

void deleteplayer(int playno){

    //delete village
    map[village[playno]->loc[0]][village[playno]->loc[1]].status = "     ";

    //send attacking army home
    if(village[playno]->attack){
        for(int i=0; i<village.size(); i++){
            for(int j=0; j<village[i]->army.size(); j++){
                if(village[i]->army[j]->target==village[playno]->idx && i!=playno){
                    village[i]->army[j]->target = village[i]->idx;
                    goto label;
                }
            }
        }
    }

    label:
    village.erase(village.begin() + playno);
}



int options(int n, string choices[n],int y, int x, bool sameline){

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
