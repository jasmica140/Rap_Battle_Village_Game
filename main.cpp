#include "villagegame.h"

Map map[mapx][mapy];
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
    int ymax = getmaxy(stdscr);

    win = newwin(40, 168, (ymax-40)/2, (xmax-168)/2);
    box(win,0,0);

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
