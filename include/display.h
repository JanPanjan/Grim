//
// Created by pogacha on 3/28/25.
//

#ifndef GRIM_DISPLAY_H
#define GRIM_DISPLAY_H

#include <ncurses.h>
#include "game_state.h"

/* Structure to hold information about the current window */
typedef struct {
    int maxY;
    int maxX;
    WINDOW* win;
} DisplayState;

typedef struct PlayerWin {
    WINDOW *grave;
    WINDOW *deck;
    WINDOW *hand;
    WINDOW *prompts;
    WINDOW *stats;
} PlayerWin;

typedef struct EnemyWin {
    WINDOW *grave;
    WINDOW *deck;
    WINDOW *hand;
    WINDOW *stats;
} EnemyWin;

/*
 * Each player has multiple card slots in his battlefield. Each card is its own
 * window.
 */
typedef struct BattleField {
    WINDOW *player[MAX_CREATURE_COUNT];
    WINDOW *enemy[MAX_CREATURE_COUNT];
} BattleField;

typedef struct GameBoard {
    PlayerWin *playerWin;
    EnemyWin *enemyWin;
    BattleField *battleField;
} GameBoard;

/* Initializes the display state with details of the given window */
void saveDisplayState(DisplayState *displayState, WINDOW *win);

/* Functions to create the game windows and populate the GameBoard struct */
void createGameBoardWindows(DisplayState *displayState, GameBoard *gameBoard);
void createPlayerWindows(DisplayState *displayState, PlayerWin *playerWin);
void createEnemyWindows(DisplayState *displayState, EnemyWin *enemyWin);
void createBattleFieldWindows(DisplayState *displayState, BattleField *battleField);

/* Displays and refreshes the gameboard */
void displayGameBoard(GameBoard *gameBoard);

/* Cleans up the game board's windows */
void terminateGameBoardWindows(GameBoard *gameBoard);

/* Displays the start screen */
void displayStartScreen(DisplayState *displayState);

#endif //GRIM_DISPLAY_H
