//
// Created by pogacha on 3/28/25.
//
#include "../include/display.h"
#include <string.h>
#include <assert.h>

#define ENEMY_WIN_HEIGHT 10

#define GRAVE_WIDTH 5
#define DECK_WIDTH 5
#define HAND_WIDTH 50
#define STATS_WIDTH 20

void
saveDisplayState(DisplayState *displayState, WINDOW *win) {
    getmaxyx(stdscr, displayState->maxY, displayState->maxX);
    displayState->win = win;
}

void
createGameBoardWindows(DisplayState *displayState, GameBoard *gameBoard) {
//    createPlayerWindows(displayState, gameBoard->playerWin);
    createEnemyWindows(displayState, gameBoard->enemyWin);
//    createBattleFieldWindows(displayState, gameBoard->battleField);
}

void createPlayerWindows(DisplayState *displayState, PlayerWin *playerWin) {
    int maxY = displayState->maxY;
    int maxX = displayState->maxX;

    int playerHeight = 3;
    int playerStatsWidth = maxX / 10;
    int playerGraveyardDeckWidth = maxX / 3;
    int playerPromptsWidth = maxX - playerStatsWidth - playerGraveyardDeckWidth;

    playerWin->deck = newwin(playerHeight, playerGraveyardDeckWidth, maxY - playerHeight, playerStatsWidth);
    assert(playerWin->deck != NULL);
    box(playerWin->deck, 0, 0);

    playerWin->grave = newwin(playerHeight, playerGraveyardDeckWidth, maxY - playerHeight, playerStatsWidth);
    assert(playerWin->grave != NULL);
    box(playerWin->grave, 0, 0);

    playerWin->hand = newwin(playerHeight, playerGraveyardDeckWidth, maxY - playerHeight, playerStatsWidth);
    assert(playerWin->hand != NULL);
    box(playerWin->hand, 0, 0);

    playerWin->prompts = newwin(playerHeight, playerPromptsWidth, maxY - playerHeight, playerStatsWidth + playerGraveyardDeckWidth);
    assert(playerWin->prompts != NULL);
    box(playerWin->prompts, 0, 0);

    playerWin->stats = newwin(playerHeight, playerStatsWidth, maxY - playerHeight, 0);
    assert(playerWin->stats != NULL);
    box(playerWin->stats, 0, 0);
}

void
createEnemyWindows(DisplayState *displayState, EnemyWin *enemyWin) {
    int maxY = displayState->maxY;
    int maxX = displayState->maxX;

    enemyWin->grave = newwin(ENEMY_WIN_HEIGHT, GRAVE_WIDTH, 0, 0);
    assert(enemyWin->grave != NULL);
    box(enemyWin->grave, 0, 0);

    /*
    enemyWin->deck = newwin(height, graveDeckWidth, 0, 0);
    assert(enemyWin->deck != NULL);
    box(enemyWin->deck, 0, 0);

    enemyWin->hand = newwin(height, handWidth, 0, graveDeckWidth);
    assert(enemyWin->hand != NULL);
    box(enemyWin->hand, 0, 0);

    enemyWin->stats = newwin(height, statsWidth, 0, maxX - statsWidth);
    assert(enemyWin->stats != NULL);
    box(enemyWin->stats, 0, 0);
    */
}

void
createBattleFieldWindows(DisplayState *displayState, BattleField *battleField) {
    int maxY = displayState->maxY;
    int maxX = displayState->maxX;

    int battlefieldHeight = maxY - 8;
    int battlefieldWidth = maxX - 4;
    int battlefieldY = 4;
    int battlefieldX = 2;

    for (int i = 0; i < MAX_CREATURE_COUNT; ++i) {
        battleField->player[i] = newwin(battlefieldHeight, battlefieldWidth, battlefieldY, battlefieldX);
        assert(battleField->player[i] != NULL);
        box(battleField->player[i], 0, 0);

        battleField->enemy[i] = newwin(battlefieldHeight, battlefieldWidth, battlefieldY, battlefieldX);
        assert(battleField->enemy[i] != NULL);
        box(battleField->enemy[i], 0, 0);
    }
}

void
terminateGameBoardWindows(GameBoard *gameBoard) {
    delwin((WINDOW *) gameBoard->battleField->player);
    delwin((WINDOW *) gameBoard->battleField->enemy);

    delwin((WINDOW *) gameBoard->enemyWin->deck);
    delwin((WINDOW *) gameBoard->enemyWin->grave);
    delwin((WINDOW *) gameBoard->enemyWin->hand);
    delwin((WINDOW *) gameBoard->enemyWin->stats);

    delwin((WINDOW *) gameBoard->playerWin->deck);
    delwin((WINDOW *) gameBoard->playerWin->grave);
    delwin((WINDOW *) gameBoard->playerWin->hand);
    delwin((WINDOW *) gameBoard->playerWin->stats);
    delwin((WINDOW *) gameBoard->playerWin->prompts);
}

void
displayGameBoard(GameBoard *gameBoard) {
    for (int i = 0; i < MAX_CREATURE_COUNT; ++i) {
        wrefresh(gameBoard->battleField->player[i]);
        wrefresh(gameBoard->battleField->enemy[i]);
    }
    wrefresh(gameBoard->playerWin->stats);
    wrefresh(gameBoard->playerWin->grave);
    wrefresh(gameBoard->playerWin->prompts);

    wrefresh(gameBoard->enemyWin->stats);
    wrefresh(gameBoard->enemyWin->hand);
    wrefresh(gameBoard->enemyWin->grave);
}

void
displayStartScreen(DisplayState *displayState) {
    int maxX = displayState->maxX;
    int maxY = displayState->maxY;

    char greeting[] = "Welcome to Grim.";
    char enterStart[] = "Press ";
    char enterKey[] = "Enter";
    char enterEnd[] = " to start..";

    char quitStart[] = "Press ";
    char quitKey[] = "Q";
    char quitEnd[] = " to quit..";

    int greetingY = maxY / 2 - 1;
    int greetingX = (int)(maxX - strlen(greeting)) / 2;
    mvprintw(greetingY, greetingX, "%s", greeting);

    /*
     * Start by printing "Press ", then increment x by length of this string.
     * Write out "enter" in bold and increment. Lastly write out " to start..".
     */
    int enterY = maxY / 2 + 1;
    int wholeEnterX = (int) (maxX - (strlen(enterStart) + strlen(enterKey) + strlen(enterEnd)));
    int enterX = wholeEnterX / 2;

    mvprintw(enterY, enterX, "%s", enterStart);
    enterX += (int)strlen(enterStart);
    attron(A_BOLD);
    mvprintw(enterY, enterX, "%s", enterKey);
    attroff(A_BOLD);
    enterX += (int)strlen(enterKey);
    mvprintw(enterY, enterX, "%s", enterEnd);

    int quitY = maxY / 2 + 3;
    int wholeQuitX = (int) (maxX - (strlen(quitStart) + strlen(quitKey) + strlen(quitEnd)));
    int quitX = wholeQuitX / 2;

    mvprintw(quitY, quitX, "%s", quitStart);
    quitX += (int)strlen(quitStart);
    attron(A_BOLD);
    mvprintw(quitY, quitX, "%s", quitKey);
    attroff(A_BOLD);
    quitX += (int)strlen(quitKey);
    mvprintw(quitY, quitX, "%s", quitEnd);

    refresh();
}