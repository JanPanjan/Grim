#include "../include/ncurses_utils.h"
#include "../include/game_state.h"
#include "../include/display.h"
#include "../include/input.h"
#include "../include/log.h"

int main() {
    log_msg(__FILE_NAME__, __LINE__, "------- start session -------\n");

    initNcurses();
    log_msg(__FILE_NAME__, __LINE__, "ncurses initialized\n");

    /*
     * Initialize display information (screen size) for stdscr, display the start screen,
     * wait for user input to proceed.
     */
    DisplayState displayState;

    saveDisplayState(&displayState, stdscr);
    log_msg(__FILE_NAME__, __LINE__, "display state saved\n");

    displayStartScreen(&displayState);
    log_msg(__FILE_NAME__, __LINE__, "start screen displayed\n");

    int ch;
    while ((ch = getch()) != '\n') {
        if (ch == 'q') {
            cleanupNcurses();
            log_msg(__FILE_NAME__, __LINE__, "------- end session -------\n");
            return 0;
        } else {
            continue;
        }
    }

    /*
     * As the game starts, it needs to start storing information about the game state.
     */
    GameState gameState;

    initializeGameState(&gameState);
    log_msg(__FILE_NAME__, __LINE__, "game state initialized\n");

    /*
     * It draws the main view of the game - the game board, that contains the following
     * windows and is structured like this:
     *
     * --------------------------------------------------------------------------------
     * | enemy | | enemy |                 |  enemy |                         | enemy | <-- enemy window
     * | deck  | | grave |                 |  hand  |                         | info  |
     * --------------------------------------------------------------------------------
     * |                   |                   |                   |                  | <-- battlefield
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * --------------------------------------------------------------------------------
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * --------------------------------------------------------------------------------
     * | player | |               player               | prompts || | player | player | <-- player window
     * | info   | |                hand                |         || | grave  | deck   |
     * --------------------------------------------------------------------------------
     *
     * To switch to a different view, prompts are displayed on the screen.
     */
    GameBoard gameBoard;
    PlayerWin playerWin;
    EnemyWin enemyWin;
    BattleField battleField;

    createGameBoardWindows(&displayState, &gameBoard);
    log_msg(__FILE_NAME__, __LINE__, "game board windows created\n");

    displayGameBoard(&gameBoard);
    log_msg(__FILE_NAME__, __LINE__, "game board displayed\n");

    getch();

    terminateGameBoardWindows(&gameBoard);
    log_msg(__FILE_NAME__, __LINE__, "game board windows terminated\n");

    cleanupNcurses();
    log_msg(__FILE_NAME__, __LINE__, "ncurses cleaned\n");

    log_msg(__FILE_NAME__, __LINE__, "------- end session -------\n");
    return 0;
}