//
// Created by pogacha on 3/28/25.
//

#ifndef GRIM_GAME_STATE_H
#define GRIM_GAME_STATE_H

#include "card.h"

/*
 * Define game state structures and enums here. These are all the structures
 * that hold data needed for the game to run properly.
 */
#define MAX_HAND_SIZE 8
#define DECK_SIZE 60
#define MAX_CREATURE_COUNT 4

/*
 * Players have mutable HP and a hand with MAX_HAND_SIZE cards. It also stores current
 * "hand-fulness".
 */
typedef struct Player {
    int HP;
    Card hand[MAX_HAND_SIZE];
    unsigned int handSize;
} Player;

/*
 * GameState struct holds all necessary information for the game - player information and
 * their decks.
 */
typedef struct GameState {
    Player player;
    Player computer;
    Card playerDeck[DECK_SIZE];
    Card computerDeck[DECK_SIZE];
} GameState;

/* Initializes the GameState. */
void initializeGameState(GameState *state);

/* Initializes all players' attributes. */
void initializePlayers(GameState *state);

/* Fills the given Player's deck with cards. */
void initializeDecks(GameState *state);

/* Creates a card of a given name, mana cost and type and saves it in a Player's deck. */
void initializeCard(GameState *state, int i, char* name, int manaCost, CardType cardType);

/* Displays the current game state. */
void printGameState(GameState *state, int deck);

#endif //GRIM_GAME_STATE_H
