#include "card.h"
#include <assert.h>

short Card::authority_id[CARDS_NUMBER] = {
    10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 13, 8, 9,
    10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 13, 15, 9,
    10, 11, 0, 1, 20, 3, 4, 5, 6, 7, 13, 8, 9,
    10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 13, 8, 9,
    16, 17
};

Card::Card()
{

}

void Card::draw_card(short _id){
    assert(_id < CARDS_NUMBER);
    id = _id;
    if(authority_id[id] > 10){
        sorttype = CardSortType_Special;
    }
    else{
        sorttype = (CardSortType)get_color();
    }
}

Card::Card(short _id)
{
    draw_card(_id);
}

void Card::set_special(){
    sorttype = CardSortType_Special;
    if(get_number() == 2 || get_number() == 11){
       ++authority_id[id];
    }
}

void Card::set3special(){
    assert(get_number() == 3);
    authority_id[id] += 18;
    sorttype = CardSortType_Special;
}

void Card::set5special(){
    assert(get_number() == 5);
    if(authority_id[id] < 10){
        authority_id[id] += 17;
    }
    sorttype = CardSortType_Special;
}

short Card::get_id()const{
    return id;
}
short Card::get_number()const{
    return (id % CARDS_NUMBER_IN_COLOR) + 1;
}
short Card::get_authority()const{
    return authority_id[id];
}
CardColor Card::get_color()const{
    return (CardColor)(id / CARDS_NUMBER_IN_COLOR);
}
CardSortType Card::get_sorttype()const{
    return sorttype;
}
