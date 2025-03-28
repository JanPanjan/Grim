//
// Created by pogacha on 3/28/25.
//
#include "../include/display.h"
#include <string.h>
#include <assert.h>

void
initDisplayState(DisplayState *displayState) {
    getmaxyx(stdscr, displayState->maxY, displayState->maxX);
}

void
createGameBoardWindows(DisplayState *displayState, GameBoard *gameBoard) {
    createPlayerWindows(displayState, gameBoard->playerWin);
    createEnemyWindows(displayState, gameBoard->enemyWin);
    createBattleFieldWindows(displayState, gameBoard->battleField);
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

    int enemyHeight = 3;
    int enemyStatsWidth = maxX / 3;
    int enemyHandCountWidth = maxX / 3;
    int enemyGraveyardDeckWidth = maxX / 3;


    enemyWin->grave = newwin(enemyHeight, enemyGraveyardDeckWidth, 0, 0);
    assert(enemyWin->grave != NULL);
    box(enemyWin->grave, 0, 0);

    enemyWin->deck = newwin(enemyHeight, enemyGraveyardDeckWidth, 0, 0);
    assert(enemyWin->deck != NULL);
    box(enemyWin->deck, 0, 0);

    enemyWin->hand = newwin(enemyHeight, enemyHandCountWidth, 0, enemyGraveyardDeckWidth);
    assert(enemyWin->hand != NULL);
    box(enemyWin->hand, 0, 0);

    enemyWin->stats = newwin(enemyHeight, enemyStatsWidth, 0, maxX - enemyStatsWidth);
    assert(enemyWin->stats != NULL);
    box(enemyWin->stats, 0, 0);
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
    char greeting[] = "Welcome to Grim!";
    char instruction[] = "Press ";
    char enterText[] = "Enter";
    char instructionEnd[] = " to start...";

    int greetingY = displayState->maxY / 2 - 1;
    int greetingX = (int)(displayState->maxX - strlen(greeting)) / 2;
    int instructionY = displayState->maxY / 2 + 1;
    int instructionX = (int)(displayState->maxX - (strlen(instruction) + strlen(enterText) + strlen(instructionEnd))) / 2;

    mvprintw(greetingY, greetingX, "%s", greeting);

    instructionX += (int)strlen(instruction);
    attron(A_BOLD);
    mvprintw(instructionY, instructionX, "%s", enterText);
    attroff(A_BOLD);

    instructionX += (int)strlen(enterText);
    mvprintw(instructionY, instructionX, "%s", instructionEnd);

    refresh();
}