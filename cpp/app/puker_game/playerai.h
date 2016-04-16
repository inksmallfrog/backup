#ifndef PLAYERAI_H
#define PLAYERAI_H

#include "player.h"

class PlayerAI : public Player
{
public:
    PlayerAI(const string &_name, short _id);
    virtual ~PlayerAI(){}

    virtual void deal_card(Card *card);
    virtual void sort_card_on_choosing_special(CardSortType sorttype);

    virtual void ask_special(CardColor color);
    virtual void ask3special();
    virtual void ask5special();
    virtual void ask_give();
    virtual void ask_back();
    virtual void ask_holdup();
    virtual void ask_play();
    virtual void ask_follow();
};

#endif // PLAYERAI_H
