//
// Created by pogacha on 3/28/25.
//

#include "../include/display.h"
#include <string.h> // For strlen

void
init_display_state(DisplayState *display_state) {
    getmaxyx(stdscr, display_state->max_y, display_state->max_x);
}

WINDOW
*create_battlefield_window(DisplayState *display_state) {
    int battlefield_height = display_state->max_y - 4;
    int battlefield_width = display_state->max_x - 4;
    int battlefield_y = 2;
    int battlefield_x = 2;

    WINDOW *battlefield_win = newwin(battlefield_height, battlefield_width, battlefield_y, battlefield_x);
    box(battlefield_win, 0, 0);
    return battlefield_win;
}

void
display_battlefield(WINDOW *battlefield_win, DisplayState *display_state) {
    mvwprintw(battlefield_win, 1, 2, "BATTLEFIELD");
    mvwprintw(battlefield_win, 3, 2, "[H]AND");
    mvwprintw(battlefield_win, 4, 2, "[D]ECK");
    mvwprintw(battlefield_win, 5, 2, "[E]ND TURN");

    wrefresh(battlefield_win);
}

void
display_start_screen(DisplayState *display_state) {
    char greeting[] = "Welcome to Grim!";
    char instruction[] = "Press ";
    char enter_text[] = "Enter";
    char instruction_end[] = " to start..";

    int greeting_y = display_state->max_y / 2 - 1;
    int greeting_x = (int) (display_state->max_x - strlen(greeting)) / 2;
    mvprintw(greeting_y, greeting_x, "%s", greeting);

    int instruction_y = display_state->max_y / 2 + 1;
    int instruction_x = (int) (display_state->max_x - (strlen(instruction) + strlen(enter_text) + strlen(instruction_end))) / 2;
    mvprintw(instruction_y, instruction_x, "%s", instruction);

    instruction_x += (int) strlen(instruction);
    attron(A_BOLD);
    mvprintw(instruction_y, instruction_x, "%s", enter_text);
    attroff(A_BOLD);

    instruction_x += (int) strlen(enter_text);
    mvprintw(instruction_y, instruction_x, "%s", instruction_end);

    refresh();
}