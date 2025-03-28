#include "../include/ncurses_utils.h"
#include "../include/game_state.h"
#include "../include/display.h"
#include "../include/input.h"

int main() {
    init_ncurses();

    DisplayState display_state;
    init_display_state(&display_state);

    display_start_screen(&display_state);

    int ch;
    while ((ch = getch()) != '\n');

    GameState game_state;
    initialize_game_state(&game_state);

    WINDOW *battlefield_win = create_battlefield_window(&display_state);
    display_battlefield(battlefield_win, &display_state);

    getch();

    delwin(battlefield_win);
    cleanup_ncurses();
    return 0;
}