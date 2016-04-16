#include "gamewindow.h"
#include <QApplication>
#include <iostream>
using namespace std;
#include "card.h"
#include "puker.h"
#include "player.h"
#include "game.h"

void TestCard();
void TestPuker();
void TestPlayer();
void TestGame();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();

    //TestCard();
    //TestPuker();
    //TestPlayer();
    //TestGame();
}

void TestGame(){
    GAME->onGame();
}


/*void TestPlayer(){
    Player player0("name1", 0);
    Player player1("name2", 1);
    Player player2("name3", 2);
    Player player3("name4", 3);
    Puker puker;
    puker.shuffle();
    for(int i = 0; i < puker.get_cards_count() - 6; i+=4){
         player0.deal_card(puker.get_card(i));
         player1.deal_card(puker.get_card(i + 1));
         player2.deal_card(puker.get_card(i + 2));
         player3.deal_card(puker.get_card(i + 3));
    }
    player2.printCards();
}*/

void TestPuker(){
    Puker puker;
    puker.shuffle();
    Card *card;
    for(int i = 0; i < puker.get_cards_count(); ++i){
        card = puker.get_card(i);
        cout << card->get_number() << " " << card->get_color() << " " << card->get_authority() << "\n";
    }
}

void TestCard(){
    for(int i = 0; i < 54; ++i){
        Card card_test(i);
        cout << "number:  " << card_test.get_number() << "\n";
        cout << "authority: " << card_test.get_authority() << "\n";
        cout << "color: ";
        switch(card_test.get_color()){
        case CardColor_Heart:
            cout << "Heart\n";
            break;
        case CardColor_Spade:
            cout << "Spade\n";
            break;
        case CardColor_Diamond:
            cout << "Diamond\n";
            break;
        case CardColor_Club:
            cout << "Club\n";
            break;
        case CardColor_Ghost:
            cout << "Ghost\n";
            break;
        }

        cout << "\n";
    }
}
