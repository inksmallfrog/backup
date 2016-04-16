#include "cardsonhand.h"
#include "player.h"
#include <assert.h>

CardsOnHand::CardsOnHand(Player *_player):
    player(_player),
    head(sorttypeNodes),
    specialType(SpecialType_Null)
{
    for (int i = 0; i < CardSortType_Number; ++i){
        sorttypeNodes[i].count = 0;
        sorttypeNodes[i].head = NULL;
        if(i < CardSortType_Number - 1){
            sorttypeNodes[i].next  = sorttypeNodes + i + 1;
        }
        else{
            sorttypeNodes[i].next = NULL;
        }
    }
    for(int i = 0; i < MAX_CARDS_ONE_PLAYER; ++i){
        cards[i].card = NULL;
        cards[i].next = NULL;
    }
}

void CardsOnHand::init(){
    add(NULL, true);
    head = sorttypeNodes;
    specialType = SpecialType_Null;
    for (int i = 0; i < CardSortType_Number; ++i){
        sorttypeNodes[i].count = 0;
        sorttypeNodes[i].head = NULL;
        if(i < CardSortType_Number - 1){
            sorttypeNodes[i].next  = sorttypeNodes + i + 1;
        }
        else{
            sorttypeNodes[i].next = NULL;
        }
    }
    for(int i = 0; i < MAX_CARDS_ONE_PLAYER; ++i){
        cards[i].card = NULL;
        cards[i].next = NULL;
    }
}

void CardsOnHand::add(Card *card, bool clear){
    static short count3 = 0;
    static short count5 = 0;
    if(clear){
        count3 = 0;
        count5 = 0;
        return;
    }
    short count = get_count();
    assert(count < MAX_CARDS_ONE_PLAYER);
    cards[count].card = card;

    short authority = card->get_authority();
    CardColor color = card->get_color();
    CardSortType sorttype = card->get_sorttype();
    CardNode *lastcnode = NULL;
    CardNode *cnode = NULL;
    for(cnode = sorttypeNodes[sorttype].head; cnode != NULL; cnode = cnode->next){
        short cnode_authority = cnode->card->get_authority();
        if(authority < cnode_authority
                || (authority == cnode_authority && color < cnode->card->get_color())){
            break;
        }
        else{
            lastcnode = cnode;
        }
    }
    cards[count].next = cnode;
    if(lastcnode != NULL){
        lastcnode->next = cards + count;
    }
    else{
        sorttypeNodes[sorttype].head = cards + count;
    }
    ++(sorttypeNodes[sorttype].count);
    switch(card->get_number()){
    case 2:
        specialType |= SpecialType_2;
        player->ask_special(card->get_color());
        break;

    case 3:
        ++count3 ;
        if(count3 > 2){
            specialType |= SpecialType_3;
            player->ask3special();
        }
        break;

    case 5:
        ++count5 ;
        if(count3 > 2){
            specialType |= SpecialType_5;
            player->ask5special();
        }
        break;

    default:
        break;
    }
}

void CardsOnHand::remove(Card *card){
    CardSortType sorttype = card->get_sorttype();
    CardNode *lastcnode = NULL;
    CardNode *cnode = NULL;
    for(cnode = sorttypeNodes[sorttype].head; cnode != NULL; cnode = cnode->next){
        if(cnode->card == card){
            break;
        }
    }
    assert(cnode == NULL);
    if(lastcnode == NULL){
        sorttypeNodes[sorttype].head = cnode->next;
    }
    else{
        lastcnode->next = cnode->next;
    }
    --(sorttypeNodes[sorttype].count);
}

void CardsOnHand::special_choosed(CardSortType sorttype){
    CardNode *lastcnode = NULL;
    CardNode *cnode = NULL;
    for(cnode = sorttypeNodes[CardSortType_Special].head; cnode != NULL; cnode = cnode->next){
        if(cnode->card->get_authority() > cnode->next->card->get_authority()){
            lastcnode->next = cnode->next;
            cnode->next = cnode->next->next;
            lastcnode->next->next = cnode;
        }
        lastcnode = cnode->next;
    }
    for(cnode = sorttypeNodes[sorttype].head; cnode != NULL; cnode = cnode->next){
        add(cnode->card);
    }
    sorttypeNodes[sorttype].count = 0;
    sorttypeNodes[sorttype].head = NULL;
    /*switch(type){
    case CardSortType_Heart:
        head = head->next;
        sorttypeNodes[CardSortType_Club].next = sorttypeNodes + CardSortType_Heart;
        sorttypeNodes[CardSortType_Heart].next = sorttypeNodes + CardSortType_Special;
        break;
    case CardSortType_Spade:
        sorttypeNodes[CardSortType_Heart].next = sorttypeNodes + CardSortType_Diamond;
        sorttypeNodes[CardSortType_Club].next = sorttypeNodes + CardSortType_Spade;
        sorttypeNodes[CardSortType_Spade].next = sorttypeNodes + CardSortType_Special;
        break;
    case CardSortType_Diamond:
        sorttypeNodes[CardSortType_Spade].next = sorttypeNodes + CardSortType_Club;
        sorttypeNodes[CardSortType_Club].next = sorttypeNodes + CardSortType_Diamond;
        sorttypeNodes[CardSortType_Diamond].next = sorttypeNodes + CardSortType_Special;
        break;
    case CardSortType_Club:
        break;
    default:
        break;
    }
    CardNode *lastcnode = NULL;
    CardNode *cnode = NULL;*/
}

void CardsOnHand::print()const{
    for(ColorNode *node = head; node != NULL; node = node->next){
        for(CardNode *cnode = node->head; cnode != NULL; cnode = cnode->next){
            std::cout << cnode->card->get_number() << " " << cnode->card->get_color() << " " << cnode->card->get_authority() << "\n";
        }
    }
}

short CardsOnHand::get_score_count()const{
    short count = 0;
    for(ColorNode *node = head; node != NULL; node = node->next){
        for(CardNode *cnode = head->head; cnode != NULL; cnode = cnode->next){
            if(cnode->card->get_number() == 5 || cnode->card->get_number() == 10 || cnode->card->get_number() == 13){
                ++count;
            }
        }
    }
    return count;
}

Card * CardsOnHand::get_card(short index){
    int count = 0;
    for(ColorNode *node = head; node != NULL; node = node->next){
        if(node->count + count < index){
            CardNode *cnode = node->head;
            for(int i = count; i < index; ++i){
                cnode = cnode->next;
            }
            return cnode->card;
        }
        else{
            count += node->count;
        }
    }
    return NULL;
}

Card * CardsOnHand::get_maxCard(){
    ColorNode *node = NULL;
    CardNode *cnode = NULL;
    for(node = head; node != NULL; node = node->next){
        for(cnode = node->head; cnode->next != NULL; cnode = cnode->next){
            ;
        }
    }
    return cnode->card;
}

/*const short CardsOnHand::get_type_count(CardType type) const{
    short count = 0;
    for(ColorNode *node = head; node != NULL; node = node->next){
        for(CardNode *cnode = head->head; cnode != NULL; cnode = cnode->next){
            if(cnode->card->get_type() == type){
                ++count;
            }
        }
    }
    return count;
}*/

short CardsOnHand::get_sorttype_count(CardSortType sorttype)const{
    return sorttypeNodes[sorttype].count;
}

short CardsOnHand::get_count()const{
    short count = 0;
    for(ColorNode *node = head; node != NULL; node = node->next){
        count += node->count;
    }
    return count;
}

char CardsOnHand::get_special()const{
    return specialType;
}
