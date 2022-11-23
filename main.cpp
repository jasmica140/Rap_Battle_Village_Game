#include "villagegame.h"

Map map[mapx][mapy];
Resource resource[maxplay][4];
ResourceBuildings rbuild[maxplay][maxrbuild];
TroopBuildings tbuild[maxplay][maxtbuild];
vector<unique_ptr<Village>> village;


WINDOW *win;

int main() {

    setlocale(LC_ALL, "");

    srand(time(nullptr));  // Initialize random number generator.

    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int xmax = getmaxx(stdscr);

    win = newwin(40, xmax-12, 3, 10);

    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    refresh();
    wrefresh(win);
    //enable arrow keys
    keypad(win,true);

    gameloop();

    getch();
    endwin();

    return 0;
}
