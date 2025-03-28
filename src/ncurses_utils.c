//
// Created by pogacha on 3/28/25.
//

#include "../include/ncurses_utils.h"

void initNcurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void cleanupNcurses() {
    endwin();
}