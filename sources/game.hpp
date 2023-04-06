#ifndef header
#define header
#include "iostream"
#include "player.hpp"
#include "card.hpp"
#include "string.h"
#include <vector>
using namespace std;



class Game {
private:
    Player &p1;
    Player &p2;
    vector<Card> carr;
    vector<string> logs;
    string last_turn;
    double p1wins;
    double p2wins;
    double draws;
    double totalrounds;

public:
    Game(Player &pl1, Player &pl2);
    void playTurn();
    void printLastTurn();
    void playAll();
    void printWiner();
    void printLog();
    void printStats();
    void init_card_array();
    void printcarr();
    void shuffle_cards();
};
#endif
