//
// Created by pogacha on 3/28/25.
//

#ifndef GRIM_GAME_STATE_H
#define GRIM_GAME_STATE_H

#include <sys/types.h>
#include "card.h"

/*
 * Define game state structures and enums here. These are all the structures
 * that hold data needed for the game to run properly.
 */
#define MAX_HAND_SIZE 8
#define DECK_SIZE 60
#define MAX_CREATURE_COUNT 4

/*
 * HP is stored in GameState structure, while the players hand is stored in Player
 * struct to make it more "private".
 */
typedef struct Player {
    Card hand[MAX_HAND_SIZE];
    u_int handSize;
} Player;

typedef enum PlayerKey {
    PLAYER,
    ENEMY
} PlayerKey;

/*
 * GameState struct holds all necessary information for the game.
 */
typedef struct GameState {
    Player player;
    Player computer;
    int playerHP;
    int computerHP;
    Card playerDeck[DECK_SIZE];
    Card playerGrave[DECK_SIZE];
    Card computerDeck[DECK_SIZE];
    Card computerGrave[DECK_SIZE];
    u_int curTurn;
    PlayerKey curPlayerTurn;
} GameState;

/* Initializes the GameState. */
void initializeGameState(GameState *state);

/* Initializes all players' attributes. */
void initializePlayers(GameState *state);

/* Fills the given Player's deck with cards. */
void initializeDecks(GameState *state);

/* Creates a card of a given name, mana cost and type and saves it in a Player's deck. */
void initializeCards(GameState *state, u_int i, char* name, u_int manaCost, CardType cardType);

/* Displays the current game state. */
void printGameState(GameState *state, int deck);

#endif //GRIM_GAME_STATE_H
