#ifndef X
#define X
#include <iostream>
#include <stack>
#include "card.hpp"

using namespace std;

class Player {
private:
    string player_Name;
    stack<Card> cards;
    int cards_taken;
public:
    Player();
    Player(string player_Name);
    int cardesTaken();
    int stacksize();
    Card topcard();
    void popcard();
    void givecard(Card crd);
    void updatecardstaken(int n);
    string getname();

};
#endif


