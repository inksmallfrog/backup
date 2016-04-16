#include "playerhuman.h"
#include "game.h"

PlayerHuman::PlayerHuman(const string &_name, short _id):
    Player(_name, _id)
{

}

void PlayerHuman::deal_card(Card *card){
    cards.add(card);
    //Gui
}

void PlayerHuman::sort_card_on_choosing_special(CardSortType sorttype){
    cards.special_choosed(sorttype);
    //Gui
}

void PlayerHuman::ask_special(CardColor color){
    //Gui
}

void PlayerHuman::ask3special(){
    //Gui
}

void PlayerHuman::ask5special(){
    //Gui
}

void PlayerHuman::ask_give(){
    //Gui
    Card *cards_array[GIVE_NUMBER];
    for(int i = 0; i < GIVE_NUMBER; ++i){
        Card *card = cards.get_maxCard();
        cards_array[i] = card;
        cards.remove(card);
    }
    GAME->give(cards_array, GIVE_NUMBER, this);
    //Gui
}

void PlayerHuman::ask_back(){
    //Gui
}

void PlayerHuman::ask_holdup(){
    //Gui
}

void PlayerHuman::ask_play(){
    //Gui
}

void PlayerHuman::ask_follow(){
    //Gui
}

void PlayerHuman::choose_special(CardSortType sorttype){
    GAME->choose_special(sorttype, this);
    //Gui
}

void PlayerHuman::choose3special(){
    short cards_index[3];
    //get cards_index from Gui
    Card *cards_array[3];
    for(int i = 0; i < 3; ++i){
        cards_array[i] = cards.get_card(cards_index[i]);
        if(cards_array[i]->get_number() == 3){
            cards_array[i]->set3special();
            //Gui
        }
        else{
            //Gui show error
            break;
        }
    }
}

void PlayerHuman::choose5special(){
    short cards_index[3];
    //get cards_index from Gui
    Card *cards_array[3];
    for(int i = 0; i < 3; ++i){
        cards_array[i] = cards.get_card(cards_index[i]);
        if(cards_array[i]->get_number() == 5){
            cards_array[i]->set5special();
            //Gui
        }
        else{
            //Gui show error
            break;
        }
    }
}

void PlayerHuman::back(){
    short cards_index[GIVE_NUMBER];
    //get cards_index from Gui
    Card *cards_array[GIVE_NUMBER];
    for(int i = 0; i < GIVE_NUMBER; ++i){
        cards_array[i] = cards.get_card(cards_index[i]);
    }
    if(Game::check_rule(cards_array, GIVE_NUMBER, RULE_SPECIAL, GIVE_NUMBER, cards)){
        GAME->back(cards_array, GIVE_NUMBER, this);
        for(int i = 0; i < GIVE_NUMBER; ++i){
            cards.remove(cards_array[i]);
        }
    }
    else{
        //Gui show error
    }
}

void PlayerHuman::holdup(){
    short cards_index[HOLDUP_NUMBER];
    //get cards_index from Gui
    Card *cards_array[HOLDUP_NUMBER];
    for(int i = 0; i < HOLDUP_NUMBER; ++i){
        cards_array[i] = cards.get_card(cards_index[i]);
    }

    if(Game::check_rule(cards_array, HOLDUP_NUMBER, RULE_NO_SCORE, HOLDUP_NUMBER, cards)){
        GAME->holdup(cards_array, HOLDUP_NUMBER,  this);
        for(int i = 0; i < HOLDUP_NUMBER; ++i){
            cards.remove(cards_array[i]);
        }
    }
    else{
        //Gui show error
    }
}

void PlayerHuman::play(){
    int play_count = 0;
    short cards_index[MAX_PLAY_NUMBER];
    //get cards_index from Gui
    Card *cards_array[MAX_PLAY_NUMBER];
    for(int i = 0; i < play_count; ++i){
        cards_array[i] = cards.get_card(cards_index[i]);
    }

    if(Game::check_rule(cards_array, play_count, RULE_JUST_AVAILABLE, -1, cards)){
        GAME->play(cards_array, play_count, this);
        for(int i = 0; i < play_count; ++i){
            cards.remove(cards_array[i]);
        }
    }
    else{
        //Gui show error
    }
}

void PlayerHuman::follow(){
    int play_count = 0;
    short cards_index[MAX_PLAY_NUMBER];
    //get cards_index from Gui
    Card *cards_array[MAX_PLAY_NUMBER];
    for(int i = 0; i < play_count; ++i){
        cards_array[i] = cards.get_card(cards_index[i]);
    }

    if(Game::check_rule(cards_array, play_count, cards)){
        GAME->follow(cards_array, play_count, this);
        for(int i = 0; i < play_count; ++i){
            cards.remove(cards_array[i]);
        }
    }
    else{
        //Gui show error
    }
}
