#ifndef PUKER_H
#define PUKER_H

#ifndef PUKER_NUMBER
#define PUKER_NUMBER 1
#endif

#include"card.h"

class Puker
{
public:
    Puker();
    void shuffle();
    void set_special(CardSortType sorttype);
    short get_cards_count()const;
    Card * get_card(int index);
private:
    static const int cards_count;
    Card cards[CARDS_NUMBER * PUKER_NUMBER];
};

#endif // PUKER_H
