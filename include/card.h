//
// Created by pogacha on 3/28/25.
//

#ifndef GRIM_CARD_H
#define GRIM_CARD_H

typedef enum CardType {
    LAND,
    CREATURE,
    SORCERY
} CardType;

typedef struct Card {
    char* name;
    int mana_cost;
    CardType type;
    // ... other card attributes (effect, etc.)
} Card;

// Functions for card manipulation (e.g., create_card, display_card)

#endif //GRIM_CARD_H
