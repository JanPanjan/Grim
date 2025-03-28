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
    int manaCost;
    CardType type;
} Card;

#endif //GRIM_CARD_H
