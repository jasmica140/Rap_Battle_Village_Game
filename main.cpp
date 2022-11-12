#include "villagegame.h"

Map map[mapx][mapy];
Village village[maxplay];
Resource resource[maxplay][4];
Troops troops[maxplay][maxtroops];
Army army[maxplay][maxarmy];
ResourceBuildings rbuild[maxplay][maxrbuild];
TroopBuildings tbuild[maxplay][maxtbuild];

WINDOW *win;

void gameloop(){

    int totplay = gamesetup();

    int playno = 0;
    int roundno = 1;

    refreshcli(playno);

    while(totplay > 1){ //win condition

        for(int i=0; i<totplay; i++){

            totplay = turnphase(playno,totplay,roundno);

            if(totplay==1){
                break;
            }

            for(int j=0; j<village[playno].army; j++){
                marching(playno, i, army[playno][i].target, army[playno][i].speed);
            }

            playno = endround(playno, totplay);
            startround(playno);
        }
        roundno++;
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
                mvwprintw(win, y+yspace, x+(xspace*3), choices[i].c_str());
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

int main() {

    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int ymax, xmax;
    getmaxyx(stdscr,ymax,xmax);

    win = newwin(39, xmax-8, ymax-39, 5);

    refresh();
    wrefresh(win);
    //enable arrow keys
    keypad(win,true);

    gameloop();

    getch();
    endwin();

    return 0;
}
