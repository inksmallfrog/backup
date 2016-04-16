#ifndef CARD_H
#define CARD_H

#ifndef CARDS_NUMBER
#define CARDS_NUMBER 54
#endif

#ifndef GHOST_CARDS_NUMBER
#define GHOST_CARDS_NUMBER 2
#endif

#ifndef CARDS_NUMBER_IN_COLOR
#define CARDS_NUMBER_IN_COLOR  ((CARDS_NUMBER - GHOST_CARDS_NUMBER)/4)
#endif

enum CardColor{
    CardColor_Heart = 0,
    CardColor_Spade,
    CardColor_Diamond,
    CardColor_Club,
    CardColor_Ghost,
    CardColor_Number
};

/*enum CardType{
    CardType_Normal,
    CardType_Special
};*/

enum CardSortType{
    CardSortType_Heart = 0,
    CardSortType_Spade,
    CardSortType_Diamond,
    CardSortType_Club,
    CardSortType_Special,
    CardSortType_Number,
};

class Card
{
public:
    Card();
    void draw_card(short id);
    Card(short id);

    void set_special();
    void set3special();
    void set5special();

    short get_id()const;
    short  get_number()const;
    short get_authority()const;
    CardColor get_color()const;
    //CardType get_type()const;
    CardSortType get_sorttype()const;

private:
    static short authority_id[CARDS_NUMBER];

    short id;
    //CardType type;
    CardSortType sorttype;
};

#endif // CARD_H
