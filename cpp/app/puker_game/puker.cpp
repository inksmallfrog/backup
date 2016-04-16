#include "puker.h"
#include "card.h"
#include <cstdlib>

const int Puker::cards_count = CARDS_NUMBER * PUKER_NUMBER;

Puker::Puker()
{
    for(int i = 0; i < cards_count; ++i){
        cards[i].draw_card(i % CARDS_NUMBER);
    }
}

void Puker::shuffle(){
    for(int i = 0; i < cards_count - 1; ++i){
        int pos = rand() % cards_count;
        Card tmp = cards[i];
        cards[i] = cards[pos];
        cards[pos] = tmp;
    }
}

void Puker::set_special(CardSortType sorttype){
    for(int i = 0; i < cards_count - 1; ++i){
        if(cards[i].get_color() == (CardColor)sorttype){
            cards[i].set_special();
        }
    }
}

short Puker::get_cards_count()const{
    return cards_count;
}

Card * Puker::get_card(int index){
    return cards + index;
}
