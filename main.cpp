#include "villagegame.h"

Map map[mapx][mapy];
Village village[maxplay];
Resource resource[maxplay][3];
Troops troops[maxplay][maxtroops];
ResourceBuidlings rbuild[maxplay][maxrbuild];
TroopBuidlings tbuild[maxplay][maxtbuild];

WINDOW *win;

void gameloop(){

    int *players = gamesetup();
    int totplay = players[0]+players[1];

    int playno = 0;

    refreshcli(playno);
    turnphase(playno,totplay);

    while(totplay > 1){ //win condition

        playno = endround(playno);
        startround(playno);

        totplay = turnphase(playno,totplay);
    }
}

int options(int n, string choices[n]){

    int choice;
    int hl=0;

    while(true) {
        for (int i = 0; i < n; i++) {
            if (i == hl) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, i + 1 + 25, 1, choices[i].c_str());
            wattroff(win, A_REVERSE);

        }
        choice = wgetch(win);

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

        if (choice == 10) {
            break;
        }
    }
    return hl+1;
}


int main() {

    initscr();
    echo();
    cbreak();

    int ymax, xmax;
    getmaxyx(stdscr,ymax,xmax);

    win = newwin(39, xmax-8, ymax-39, 5);
    box(win,0,0);
    hline(2,xmax-8);
    refresh();
    wrefresh(win);
    //enable arrow keys
    keypad(win,true);

    gameloop();

    getch();
    endwin();

    return 0;
}

