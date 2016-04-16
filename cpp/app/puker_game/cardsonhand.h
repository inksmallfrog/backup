#ifndef CARDSONHAND_H
#define CARDSONHAND_H

#include "card.h"
class Player;

#ifndef MAX_CARDS_ONE_PLAYER
#define MAX_CARDS_ONE_PLAYER 18
#endif

enum SpecialType{
    SpecialType_Null = 0,
    SpecialType_3 = 1,
    SpecialType_5 = 1 << 1,
    SpecialType_2 = 1 << 2
};

struct CardNode{
    Card *card;
    CardNode *next;
};

struct ColorNode{
    int count;
    CardNode *head;
    ColorNode *next;
};

class CardsOnHand
{
public:
    CardsOnHand(Player *_player);
    void init();
    void add(Card *card, bool clear = false);
    void remove(Card *card);
    void special_choosed(CardSortType color);

    void print()const;

    Card * get_card(short index);
    Card * get_maxCard();
    short get_score_count()const;
    short get_sorttype_count(CardSortType sorttype)const;
    short get_count()const;
    char get_special()const;

private:
    Player *player;

    ColorNode *head;
    ColorNode sorttypeNodes[CardSortType_Number];
    CardNode cards[MAX_CARDS_ONE_PLAYER];

    char specialType;
};

#endif // CARDSONHAND_H
