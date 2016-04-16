#ifndef PLAYERHUMAN_H
#define PLAYERHUMAN_H

#include "player.h"

class PlayerHuman : public Player
{
public:
    PlayerHuman(const string &_name, short _id);
    virtual ~PlayerHuman(){}

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

    void choose_special(CardSortType sorttype);
    void choose3special();
    void choose5special();
    void back();
    void holdup();
    void play();
    void follow();
};

#endif // PLAYERHUMAN_H
