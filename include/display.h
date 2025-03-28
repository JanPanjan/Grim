//
// Created by pogacha on 3/28/25.
//

#ifndef GRIM_DISPLAY_H
#define GRIM_DISPLAY_H

#include <ncurses.h>
#include "game_state.h"

/* Structure to hold display state */
typedef struct {
    int maxY;
    int maxX;
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

/* Each player has multiple card slots in his battlefield. Each card is its own window. */
typedef struct BattleField {
    WINDOW *player[MAX_CREATURE_COUNT];
    WINDOW *enemy[MAX_CREATURE_COUNT];
} BattleField;

typedef struct GameBoard {
    PlayerWin *playerWin;
    EnemyWin *enemyWin;
    BattleField *battleField;
} GameBoard;

/* Initializes the display state with details of the current window */
void initDisplayState(DisplayState *displayState);

/* Functions to create the game windows and populate the GameBoard struct */
void createGameBoardWindows(DisplayState *displayState, GameBoard *gameBoard);
void createPlayerWindows(DisplayState *displayState, PlayerWin *playerWin);
void createEnemyWindows(DisplayState *displayState, EnemyWin *enemyWin);
void createBattleFieldWindows(DisplayState *displayState, BattleField *battleField);

// Cleans up game board windows
void terminateGameBoardWindows(GameBoard *gameBoard);

// Function to display the game board
void displayGameBoard(GameBoard *gameBoard);

/* Displays the start screen */
void displayStartScreen(DisplayState *displayState);

#endif //GRIM_DISPLAY_H
