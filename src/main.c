//
// Created by pogacha on 3/23/25.
//
#include <ncurses.h>

int main() {
    initscr();
    printw("hello world");
    refresh();
    getch();
    endwin();
    return 0;
}