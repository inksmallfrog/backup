#include "playerai.h"

PlayerAI::PlayerAI(const string &_name, short _id) :
    Player(_name, _id){

}

void PlayerAI::deal_card(Card *card){
    cards.add(card);
}

void PlayerAI::sort_card_on_choosing_special(CardSortType sorttype){
    cards.special_choosed(sorttype);
}

void PlayerAI::ask_special(CardColor color){
}

void PlayerAI::ask3special(){
}

void PlayerAI::ask5special(){
}

void PlayerAI::ask_give(){
}

void PlayerAI::ask_back(){
}

void PlayerAI::ask_holdup(){
}

void PlayerAI::ask_play(){
}

void PlayerAI::ask_follow(){
}
