#include "game.h"
#include "player.h"
#include "playerhuman.h"
#include "playerai.h"
#include <stdlib.h>
#include <assert.h>

Circle::Circle() :
    score(0),
    cards_count(0),
    sorttype(CardSortType_Heart),
    cardstype(CardsType_Single),
    biggest_player(NULL),
    biggest_cards(NULL){

}

Game* Game::instance = new Game;

Game::Game() :
    banker(NULL),
    current_player(NULL),
    special_sorttype(CardSortType_Number),
    give_state(GiveState_Null),
    holdup_score(0),
    state_before_wait(GameState_Start),
    state(GameState_Start){
    players[0] = new PlayerHuman("human", 0);
    players[1] = new PlayerAI("ai0", 1);
    players[2] = new PlayerAI("ai1", 2);
    players[3] = new PlayerAI("ai2", 3);
}

Game::~Game(){
    delete players[3];
    delete players[2];
    delete players[1];
    delete players[0];
}

bool Game::check_rule(Card **cards_array, short count, Rule rule, short need_count, const CardsOnHand &cards){
    if(need_count != -1 && count != need_count){
        return false;
    }
    switch(rule){
    case RULE_SPECIAL:{
        short same_sorttype_count = 0;
        for(int i = 0; i < count; ++i){
            if(cards_array[i]->get_sorttype() == CardSortType_Special){
                ++same_sorttype_count;
            }
        }
        if(same_sorttype_count < count && (cards.get_sorttype_count(CardSortType_Special))){
            return false;
        }
        break;
    }
    case RULE_NO_SCORE:{
        short noscore_count = 0;
        for(int i = 0; i < count; ++i){
            if(cards_array[i]->get_number() != 5 && cards_array[i]->get_number() != 10 && cards_array[i]->get_number() != 13){
                ++noscore_count;
            }
        }
        if(noscore_count < count
                && cards.get_count() - cards.get_score_count() > noscore_count){
            return false;
        }
        break;
    }
    case RULE_JUST_AVAILABLE:{
        if(check_cardstype(cards_array, count) == CardsType_Error){
            return false;
        }
        break;
    }
    }
    return true;
}

bool Game::check_rule(Card **cards_array, short count, const CardsOnHand &cards){
    if(count != (instance->current_circle).cards_count){
        return false;
    }
    CardSortType sorttype = (instance->current_circle).sorttype;
    switch((instance->current_circle).cardstype){
    case CardsType_Single:{
        if(cards_array[0]->get_sorttype() != (instance->current_circle).sorttype && cards.get_sorttype_count(sorttype) > 0){
            return false;
        }
        break;
    }

    case CardsType_Multiple:{
        int same_sorttype_count = 0;
        for(int i = 0; i < count; ++i){
            if(cards_array[i]->get_sorttype() == sorttype){
                ++same_sorttype_count;
            }
        }
        if(same_sorttype_count < count && cards.get_sorttype_count(sorttype) > same_sorttype_count){
            return false;
        }
        break;
    }

    case CardsType_Falsebig:{
        break;
    }

    case CardsType_Realbig:{
        int same_sorttype_count = 0;
        CardsType cardstype = check_cardstype(cards_array, count);
        if(cardstype == CardsType_Falsebig || cardstype == CardsType_Realbig){
            return true;
        }
        for(int i = 0; i < count; ++i){
            if(cards_array[i]->get_sorttype() == CardSortType_Special){
                ++same_sorttype_count;
            }
        }
        if(same_sorttype_count < count
                && (cards.get_sorttype_count(CardSortType_Special) > same_sorttype_count)){
            return false;
        }
        break;
    }
    case CardsType_Error:{
        break;
    }
    }
    return true;
}

CardsType Game::check_cardstype(Card **cards_array, short count){
    assert(count > 0);
    CardsType ret = CardsType_Error;
    if(count == 1){
        return CardsType_Single;
    }
    else{
        CardSortType sorttype = cards_array[0]->get_sorttype();
        short number = cards_array[0]->get_number();
        for(int i = 1; i < count; ++i){
            if(cards_array[i]->get_sorttype() == sorttype){
                ret = CardsType_Multiple;
                continue;
            }
            if(cards_array[i]->get_number() == number){
                if(ret == CardsType_Falsebig){
                    continue;
                }
                else{
                    ret = CardsType_Realbig;
                    continue;
                }
            }
            else if(ret == CardsType_Realbig && cards_array[i]->get_number() == 12){
                ret = CardsType_Falsebig;
                continue;
            }
            else if(number == 12){
                ret = CardsType_Falsebig;
                number = cards_array[i]->get_number();
            }
            else{
                ret = CardsType_Error;
                break;
            }
        }
    }
    return ret;
}

void Game::onGame(){
    while(true){
        switch (state) {
        case GameState_Start:
            on_start();
            break;

        case GameState_Deal:
           on_deal();
            break;

        case GameState_WaitingForSpecial:
            on_waiting_for_special();
            break;

        case GameState_Give:
            on_give();
            break;

        case GameState_Back:
            on_back();
            break;

        case GameState_GetBottom:
            on_getbottom();
            break;

        case GameState_HoldUp:
            on_holdup();
            break;

        case GameState_Play:
            on_play();
            break;

        case GameState_Follow:
            on_follow();
            break;

        case GameState_CircleFinished:
            on_circlefinished();
            break;

        case GameState_NewTurn:
            on_newturn();
            break;

        case GameState_Wait:
            break;

        default:
            break;
        }
        Game::msleep(33);
    }
}

void Game::on_start(){
    for(int i = 0; i < PLAYER_NUMBER; ++i){
        players[i]->new_start(Team_Normal);
    }
    on_deal(true);
    puker.shuffle();
    current_player = *(players + rand() % 4);
    state = GameState_Deal;

    gamewindow->game_start();
}

void Game::on_deal(bool clear){
    static short deal_pos = 0;
    if(clear){
        deal_pos = 0;
        return;
    }
    current_player->deal_card(puker.get_card(deal_pos));
    ++deal_pos;
    nextplayer();
    if(deal_pos == puker.get_cards_count() - HOLDUP_NUMBER - 1){
        state = GameState_WaitingForSpecial;
    }
    Game::msleep(100);

    gamewindow->game_deal(current_player->get_id());
}

void Game::on_waiting_for_special(){
    //wait for 10s
    if(special_sorttype == CardSortType_Number){
        if(banker == NULL){
            state = GameState_Start;
            return;
        }
        int random;
        CardColor color;
        do{
            random = puker.get_cards_count() - (rand() % 6 + 1);
            color = puker.get_card(random)->get_color();
        }while(color != CardColor_Ghost);
        //Show card 3s
        special_sorttype = (CardSortType)color;
        give_state = GiveState_Null;
    }
    if(give_state != GiveState_Null){
        state = GameState_Give;
    }
    else{
        state = GameState_GetBottom;
    }
}

void Game::on_give(){
    get_beforeplayer(banker)->ask_give();
    if(give_state == GiveState_DoubleGive){
        get_nextplayer(banker)->ask_give();
    }
    wait();
}

void Game::on_back(){
    banker->ask_back();
    if(give_state == GiveState_DoubleGive){
       get_nextplayer(get_nextplayer(banker))->ask_back();
    }
    wait();
}

void Game::on_getbottom(bool clear){
    static short deal_pos = puker.get_cards_count() - HOLDUP_NUMBER;
    if(clear){
        deal_pos = puker.get_cards_count() - HOLDUP_NUMBER;
        return;
    }
    banker->deal_card(puker.get_card(deal_pos));
    ++deal_pos;
    if(deal_pos == puker.get_cards_count() - 1){
        state = GameState_HoldUp;
    }
}

void Game::on_holdup(){
    banker->ask_holdup();
    wait();
}

void Game::on_play(){
    if(current_player->get_cardscount() == 0){
        state = GameState_NewTurn;
        return;
    }
    current_player->ask_play();
    wait();
}

void Game::on_follow(bool clear){
    static int time = 0;
    if(clear){
        time = 0;
    }
    nextplayer();
    ++time;
    if(time == 4){
       time = 0;
       state = GameState_CircleFinished;
       return;
    }
    current_player->ask_follow();
    wait();
}

void Game::on_circlefinished(){
    if(current_circle.biggest_player == get_nextplayer(banker) || current_circle.biggest_player == get_beforeplayer(banker)){
        get_nextplayer(banker)->add_score(current_circle.score);
    }
    current_player = current_circle.biggest_player;
    current_circle.score = 0;
    state = GameState_Play;
}

void Game::on_newturn(){
    if(current_player->get_team() == Team_Normal){
        get_nextplayer(banker)->add_score(holdup_score * 2);
    }
    Player *next = get_nextplayer(banker);
    if(next->get_score() >= 45){
        banker = next;
        if(next->get_score() >= 60){
            give_state = GiveState_SingleGive;
            if(next->get_score() >= 80){
                give_state = GiveState_DoubleGive;
            }
        }
    }
    else if(next->get_score() == 0){
        give_state = GiveState_DoubleGive;
    }
    on_deal(true);
    on_getbottom(true);
    on_follow(true);
    holdup_score = 0;
    banker->new_start(Team_Banker);
    get_nextplayer(banker)->new_start(Team_Normal);
    get_nextplayer(get_nextplayer(banker))->new_start(Team_Banker);
    get_beforeplayer(banker)->new_start(Team_Normal);
    puker.shuffle();
    current_player = banker;
    state = GameState_Deal;
}

void Game::choose_special(CardSortType sorttype, Player *player){
    puker.set_special(sorttype);
    for(int i = 0; i < PLAYER_NUMBER; ++i){
        players[i]->sort_card_on_choosing_special(sorttype);
    }
    if(banker == NULL){
        banker = player;
        player->set_team(Team_Banker);
        get_nextplayer(get_nextplayer(player))->set_team(Team_Banker);
    }
    //Gui
}

void Game::wait(){
    state_before_wait = state;
    state = GameState_Wait;
}

void Game::give(Card **cards_array, short count, Player *player, bool clear){
    static short time = 0;
    if(clear){
        time = 0;
        return;
    }
    for(int i = 0; i < count; ++i){
        get_nextplayer(player)->deal_card(cards_array[i]);
    }
    ++time;
    if(give_state == GiveState_SingleGive && time == 1){
        state = GameState_Back;
    }
    else if(time == 2){
        state = GameState_Back;
    }
}

void Game::back(Card **cards_array, short count, Player *player, bool clear){
    static short time = 0;
    if(clear){
        time = 0;
        return;
    }
    for(int i = 0; i < count; ++i){
        get_beforeplayer(player)->deal_card(cards_array[i]);
    }
    ++time;
    if(give_state == GiveState_SingleGive && time == 1){
        state = GameState_GetBottom;
    }
    else if(time == 2){
        state = GameState_GetBottom;
    }
}

void Game::holdup(Card **cards_array, short count, Player *player){
   for(int i = 0; i < count; ++i) {
       short number = cards_array[i]->get_number();
       switch(number){
       case 5:
           holdup_score += 5;
           break;
       case 10:
       case 13:
           holdup_score += 10;
           break;
       default:
           break;
       }
   }
   state = GameState_Play;
}

void Game::play(Card **cards_array, short count, Player *player){
    current_circle.cardstype = check_cardstype(cards_array, count);
    switch(current_circle.cardstype){
    case CardsType_Single:
    case CardsType_Multiple:
        current_circle.sorttype = cards_array[0]->get_sorttype();
        break;
    case CardsType_Falsebig:
        current_circle.sorttype = CardSortType_Number;
        break;
    case CardsType_Realbig:
        current_circle.sorttype = CardSortType_Special;
        break;
    default:
        assert(1 == 0);
        break;
    }
    current_circle.cards_count = count;
    current_circle.biggest_player = player;
    current_circle.biggest_cards = cards_array;
    for(int i = 0; i < count; ++i) {
       short number = cards_array[i]->get_number();
       switch(number){
       case 5:
           current_circle.score += 5;
           break;
       case 10:
       case 13:
           current_circle.score += 10;
           break;
       default:
           break;
       }
   }
   state = GameState_Follow;
}

void Game::follow(Card **cards_array, short count, Player *player){
    switch(current_circle.cardstype) {
    case CardsType_Single:{
        if((cards_array[0]->get_sorttype() == CardSortType_Special)
             && (current_circle.sorttype != CardSortType_Special
                    || (cards_array[0]->get_authority() > current_circle.biggest_cards[0]->get_authority()))){
            current_circle.biggest_cards = cards_array;
            current_circle.biggest_player = player;
        }
        else if(cards_array[0]->get_sorttype() == current_circle.sorttype
                  && cards_array[0]->get_authority() > current_circle.biggest_cards[0]->get_authority()){
            current_circle.biggest_cards = cards_array;
            current_circle.biggest_player = player;
        }
        break;
    }
    case CardsType_Multiple:{
        bool same_sorttype = true;
        int max_authority = cards_array[0]->get_authority();
        CardSortType sorttype = cards_array[0]->get_sorttype();
        for(int i = 1; i < count; ++i){
            if(cards_array[i]->get_sorttype() != sorttype){
                same_sorttype = false;
                break;
            }
            if(cards_array[i]->get_authority() > max_authority){
                max_authority = cards_array[i]->get_authority();
            }
        }
        if(same_sorttype){
            if(sorttype == current_circle.sorttype){
                bool is_biggest = true;
                for(int i = 0; i < count; ++i){
                    if(max_authority <= current_circle.biggest_cards[i]->get_authority()){
                        is_biggest = false;
                        break;
                    }
                }
                if(is_biggest){
                    current_circle.biggest_cards = cards_array;
                    current_circle.biggest_player = player;
                }
            }
            else  if(sorttype == CardSortType_Special){
                    current_circle.biggest_cards = cards_array;
                    current_circle.biggest_player = player;
            }
        }
        break;
    }
    case CardsType_Falsebig:{
        if(check_cardstype(cards_array, count) == CardsType_Realbig){
            if(check_cardstype(current_circle.biggest_cards, count) != CardsType_Realbig){
                current_circle.biggest_cards = cards_array;
                current_circle.biggest_player = player;
            }
            else{
                if(current_circle.biggest_cards[0]->get_number() == 1){
                    ;
                }
                else if(cards_array[0]->get_number() == 1 || cards_array[0]->get_number() > current_circle.biggest_cards[0]->get_number()){
                    current_circle.biggest_cards = cards_array;
                    current_circle.biggest_player = player;
                }
            }
        }
        break;
    }
    case CardsType_Realbig:{
        if(current_circle.biggest_cards[0]->get_number() == 1){
            break;
        }
        if(check_cardstype(cards_array, count) == CardsType_Realbig){
             if(cards_array[0]->get_number() == 1 || cards_array[0]->get_number() > current_circle.biggest_cards[0]->get_number()){
                 current_circle.biggest_cards = cards_array;
                 current_circle.biggest_player = player;
             }
        }
        break;
    }
    }
    for(int i = 0; i < count; ++i) {
       short number = cards_array[i]->get_number();
       switch(number){
       case 5:
           current_circle.score += 5;
           break;
       case 10:
       case 13:
           current_circle.score += 10;
           break;
       default:
           break;
       }
   }
   state = GameState_Follow;
}

void Game::nextplayer(){
    current_player = get_nextplayer(current_player);
}

Player * Game::get_nextplayer(Player *player){
    return players[(player->get_id() + 1) % 4];
}

Player * Game::get_beforeplayer(Player *player){
    return players[(player->get_id() - 1) % 4];
}

void Game::run(){
    onGame();
}
