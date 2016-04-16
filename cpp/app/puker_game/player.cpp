#include "player.h"
#include "card.h"
#include "game.h"
#include <string>
#include <iostream>

Player::Player(const string &_name, short _id):
    name(_name),
    id(_id),
    score(0),
    team(Team_Normal),
    cards(this)
{
    cards.init();
}

void Player::new_start(Team _team){
    score = 0;
    team = _team;
    cards.init();
}

void Player::add_score(int _score){
    score += _score;
}

void Player::set_team(Team _team){
    team = _team;
}

const string& Player::get_name()const{
    return name;
}

short Player::get_id()const{
    return id;
}

short Player::get_score()const{
    return score;
}

Team Player::get_team()const{
    return team;
}

char Player::get_special()const{
    return cards.get_special();
}

short Player::get_cardscount()const{
    return cards.get_count();
}

void Player::printCards()const{
    cards.print();
}
