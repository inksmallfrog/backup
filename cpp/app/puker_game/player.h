#ifndef PLAYER_H
#define PLAYER_H

#ifndef MAX_CARDS_ONE_PLAYER
#define MAX_CARDS_ONE_PLAYER 18
#endif

#ifndef HOLDUP_NUMBER
#define HOLDUP_NUMBER 6
#endif

#include <iostream>
#include "cardsonhand.h"
using namespace std;
class Player;
class Card;
struct Circle;

enum Team{
    Team_Banker,
    Team_Normal
};

class Player
{
public:
    Player(const string &_name, short _id);
    virtual ~Player(){}

    void new_start(Team team);

    void add_score(int _score);

    virtual void deal_card(Card *card)=0;
    virtual void sort_card_on_choosing_special(CardSortType type)=0;

    virtual void ask_special(CardColor color)=0;
    virtual void ask3special()=0;
    virtual void ask5special()=0;
    virtual void ask_give()=0;
    virtual void ask_back()=0;
    virtual void ask_holdup()=0;
    virtual void ask_play()=0;
    virtual void ask_follow()=0;

    void set_team(Team _team);

    const string& get_name()const;
    short get_id()const;
    char get_special()const;
    short get_score()const;
    Team get_team()const;
    short get_cardscount()const;

    void printCards()const;

protected:
    string name;
    short id;
    short score;
    Team team;
    CardsOnHand cards;
};

#endif // PLAYER_H
