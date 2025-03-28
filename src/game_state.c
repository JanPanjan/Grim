//
// Created by pogacha on 3/28/25.
//
#include "../include/game_state.h"
#include <stdlib.h> // for rand() and srand()
#include <time.h>
#include <stdio.h>

/*
 * Each player has 20 HP available from the start and both start with empty hand.
 * Their decks are randomly populated with cards. Each deck has 60 cards - 20 lands,
 * 20 creatures and 20 sorceries.
 */
void
initializeGameState(GameState *state) {
    // Initialize player and computer
    initializePlayers(state);
    initializeDecks(state);
}

void
initializePlayers(GameState *state) {
    state->player.HP = 20;
    state->player.handSize = 0;
    state->computer.HP = 20;
    state->computer.handSize = 0;
}

void
initializeDecks(GameState *state) {
    srand(time(NULL));

    for (int i = 0; i < DECK_SIZE; i++){
        if (i < 20) { // land
            initializeCard(state, i, "land", 0, LAND);
        }
        if (i >= 20 && i < 40) { // creature
            initializeCard(state, i, "creature", rand() % 10, CREATURE);
        }
        if (i >= 40) { // sorcery
            initializeCard(state, i, "sorcery", rand() % 8, SORCERY);
        }
    }
}

void
initializeCard(GameState *state, int i, char* name, int manaCost, CardType cardType) {
    state->playerDeck[i].name = name;
    state->playerDeck[i].manaCost = manaCost;
    state->playerDeck[i].type = cardType;

    state->computerDeck[i].name = name;
    state->computerDeck[i].manaCost = manaCost;
    state->computerDeck[i].type = cardType;
}

/*
 * Prints the current game state. If `deck` is 0, the decks are not printed.
 */
void
printGameState(GameState *state, int deck) {
    printf("Player HP: %d\n", state->player.HP);
    printf("Computer HP: %d\n", state->computer.HP);

    if (deck == 0) {
        return;
    }

    printf("\nPlayer Deck:\n");
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("  Card %d: %s, Mana: %d, Type: %d\n", i, state->playerDeck[i].name, state->playerDeck[i].manaCost, state->playerDeck[i].type);
    }

    printf("\nComputer Deck:\n");
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("  Card %d: %s, Mana: %d, Type: %d\n", i, state->computerDeck[i].name, state->computerDeck[i].manaCost, state->computerDeck[i].type);
    }
    printf("\n");
}