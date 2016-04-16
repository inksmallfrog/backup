#ifndef GAME_H
#define GAME_H

#ifndef GIVE_NUMBER
#define GIVE_NUMBER 1
#endif

#ifndef HOLDUP_NUMBER
#define HOLDUP_NUMBER 6
#endif

#ifndef MAX_PLAY_NUMBER
#define MAX_PLAY_NUMBER 12
#endif

#ifndef PLAYER_NUMBER
#define PLAYER_NUMBER 4
#endif

#include "card.h"
#include "player.h"
#include "puker.h"
#include "gamewindow.h"
#include <QThread>

enum Rule{
    RULE_SPECIAL,
    RULE_NO_SCORE,
    RULE_JUST_AVAILABLE
};

enum GiveState{
    GiveState_Null,
    GiveState_SingleGive,
    GiveState_DoubleGive
};

enum GameState{
    GameState_Start,
    GameState_Deal,
    GameState_WaitingForSpecial,
    GameState_Give,
    GameState_Back,
    GameState_GetBottom,
    GameState_HoldUp,
    GameState_Play,
    GameState_Follow,
    GameState_CircleFinished,
    GameState_NewTurn,
    GameState_End,
    GameState_Wait
};

enum CardsType{
    CardsType_Error = -1,
    CardsType_Single,
    CardsType_Multiple,
    CardsType_Falsebig,
    CardsType_Realbig,
};

struct Circle{
    short score;
    short cards_count;
    CardSortType sorttype;
    CardsType cardstype;
    Player *biggest_player;
    Card **biggest_cards;

    Circle();
};

class Game : public QThread{
public:
    ~Game();
    static Game * getInstance(){
        return instance;
   }
    static void sleep(unsigned long time){QThread::sleep(time);}
    static bool check_rule(Card ** cards_array, short count, Rule rule, short need_count, const CardsOnHand &cards);
    static bool check_rule(Card ** cards_array, short count, const CardsOnHand &cards);
    static CardsType check_cardstype(Card ** cards_array, short count);

    void onGame();
    void on_start();
    void on_deal(bool clear = false);
    void on_waiting_for_special();
    void on_give();
    void on_back();
    void on_getbottom(bool clear = false);
    void on_holdup();
    void on_play();
    void on_follow(bool clear = false);
    void on_circlefinished();
    void on_newturn();

    void choose_special(CardSortType sorttype, Player *player);
    void set_mainwindow(GameWindow *window){gamewindow = window;}
    void give(Card **cards_array, short count, Player *player, bool clear = false);
    void back(Card **cards_array, short count, Player *player, bool clear = false);
    void holdup(Card **cards_array, short count, Player *player);
    void play(Card **cards_array, short count, Player *player);
    void follow(Card **cards_array, short count, Player *player);

    void wait();

    Circle current_circle;

protected:
    Game();
    virtual void run();

private:
    void nextplayer();
    Player *get_nextplayer(Player *player);
    Player *get_beforeplayer(Player *player);

    static Game *instance;

    GameWindow *gamewindow;

    Puker puker;
    Player *players[PLAYER_NUMBER];
    Player *banker;
    Player *current_player;

    CardSortType special_sorttype;
    short holdup_score;

    GiveState give_state;
    GameState state_before_wait;
    GameState state;
};
#ifndef GAME
#define GAME (Game::getInstance())
#endif
#endif // GAME_H
