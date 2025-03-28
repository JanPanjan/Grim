//
// Created by pogacha on 3/28/25.
//

#ifndef GRIM_DISPLAY_H
#define GRIM_DISPLAY_H

#include <ncurses.h>
#include "game_state.h"

/* Structure to hold display state */
typedef struct {
    int max_y;
    int max_x;
} DisplayState;

/* Initializes the display state with details of the current window */
void init_display_state(DisplayState *display_state);

/* Creates the battlefield window */
WINDOW *create_battlefield_window(DisplayState *display_state);

/* Displays the GameBoard's battlefield - the main view */
void display_battlefield(WINDOW *battlefield_win, DisplayState *display_state);

/* Displays the start screen */
void display_start_screen(DisplayState *display_state);

#endif //GRIM_DISPLAY_H
