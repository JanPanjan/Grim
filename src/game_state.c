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
initialize_game_state(GameState *state) {
    // Initialize player and computer
    initialize_players(state);
    initialize_decks(state);
}

void
initialize_players(GameState *state) {
    state->player.HP = 20;
    state->player.hand_size = 0;
    state->computer.HP = 20;
    state->computer.hand_size = 0;
}

void
initialize_decks(GameState *state) {
    srand(time(NULL));

    for (int i = 0; i < DECK_SIZE; i++){
        if (i < 20) { // land
            initialize_card(state, i, "land", 0, LAND);
        }
        if (i >= 20 && i < 40) { // creature
            initialize_card(state, i, "creature", rand() % 10, CREATURE);
        }
        if (i >= 40) { // sorcery
            initialize_card(state, i, "sorcery", rand() % 8,  SORCERY);
        }
    }
}

void
initialize_card(GameState *state, const int i, char* name, const int mana_cost, const CardType card_type) {
    state->player_deck[i].name = name;
    state->player_deck[i].mana_cost = mana_cost;
    state->player_deck[i].type = card_type;

    state->computer_deck[i].name = name;
    state->computer_deck[i].mana_cost = mana_cost;
    state->computer_deck[i].type = card_type;
}

/*
 * Prints the current game state. If `deck` is 0, the decks are not printed.
 */
void
print_game_state(GameState *state, int deck) {
    printf("Player HP: %d\n", state->player.HP);
    printf("Computer HP: %d\n", state->computer.HP);

    if (deck == 0) {
        return;
    }

    printf("\nPlayer Deck:\n");
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("  Card %d: %s, Mana: %d, Type: %d\n", i, state->player_deck[i].name, state->player_deck[i].mana_cost, state->player_deck[i].type);
    }

    printf("\nComputer Deck:\n");
    for (int i = 0; i < DECK_SIZE; i++) {
        printf("  Card %d: %s, Mana: %d, Type: %d\n", i, state->computer_deck[i].name, state->computer_deck[i].mana_cost, state->computer_deck[i].type);
    }
    printf("\n");
}