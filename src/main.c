#include "../include/ncurses_utils.h"
#include "../include/game_state.h"
#include "../include/display.h"
#include "../include/input.h"

int main() {
    initNcurses();

    /*
     * Initialize display information (screen size) and display the start screen.
     * Wait for user input to proceed.
     */
    DisplayState displayState;
    initDisplayState(&displayState);
    displayStartScreen(&displayState);
    int ch;
    while ((ch = getch()) != '\n');

    /*
     * As the game starts, it needs to start storing information about the game state.
     */
    GameState gameState;
    initializeGameState(&gameState);

    /*
     * It draws the main view of the game - the game board, that contains the following
     * windows and is structured like this:
     *
     * --------------------------------------------------------------------------------
     * | enemy | | enemy |                 |  enemy |                         | enemy |
     * | deck  | | grave |                 |  hand  |                         | info  |
     * --------------------------------------------------------------------------------
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * --------------------------------------------------------------------------------
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * |                   |                   |                   |                  |
     * --------------------------------------------------------------------------------
     * | player | |               player               | prompts || | player | player |
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
    displayGameBoard(&gameBoard);

    getch();

    terminateGameBoardWindows(&gameBoard);
    cleanupNcurses();
    return 0;
}