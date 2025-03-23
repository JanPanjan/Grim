#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

int main() {
    int ch;
    int x = 92;
    int y = 23;

    initscr();            /* Start curses mode 		*/
    raw();                /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */

    /* ko klikam karkoli se menja napis iz non-bold v bold */
    char* title = "G R I M\n";
    int bold = 0; // false

    mvprintw(y, x, title);

    while ((ch = getch()) != KEY_BACKSPACE) {
        if (bold == 0) {
            attron(A_BOLD);
            mvprintw(y, x, title);
            bold = 1;
        } else {
            attroff(A_BOLD);
            mvprintw(y, x, title);
            bold = 0;
        }
        refresh();  /* Print it on to the real screen */
    }
    endwin();   /* End curses mode		  */

    return 0;
}