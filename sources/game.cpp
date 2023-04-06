#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <chrono>
#include <random>
#include <algorithm>
#include "iostream"
#include "string.h"

using namespace std;


Game::Game(Player &pl1, Player &pl2)
    : p1(pl1), p2(pl2)
{
    init_card_array();
    shuffle_cards();
    for (std::vector<Card>::size_type i = 0; i < this->carr.size(); i++)
    {
        if (i % 2 == 0)
        {
            p1.givecard(carr[i]);
        }
        else
        {
            p2.givecard(carr[i]);
        }
    }
}

void Game::playTurn()
{
    if (p1.stacksize() == 0)
    {
        throw invalid_argument("failed to play turn");
    }
    if (&p1 == &p2)
    {
        throw invalid_argument("same player");
    }
    if (p1.stacksize() != 0)
    {
        last_turn = "";
        this->totalrounds += 1;
        int cardstobetaken = 2;
        Card c1 = p1.topcard();
        p1.popcard();
        Card c2 = p2.topcard();
        p2.popcard();
        while (c1.get_card_num() == c2.get_card_num())
        {
            int t1 = c1.get_card_num();
            if (t1 == 10)
            {
                this->last_turn += (p1.getname() + " played prince of " + c1.get_card_type() + " " + p2.getname() + " played prince of " + c2.get_card_type() + ". Draw. ");
            }
            if (t1 == 11)
            {
                this->last_turn += (p1.getname() + " played queen of " + c1.get_card_type() + " " + p2.getname() + " played queen of " + c2.get_card_type() + ". Draw. ");
            }
            if (t1 == 12)
            {
                this->last_turn += (p1.getname() + " played king of " + c1.get_card_type() + " " + p2.getname() + " played king of " + c2.get_card_type() + ". Draw. ");
            }
            if (t1 == 13)
            {
                this->last_turn += (p1.getname() + " played ace of " + c1.get_card_type() + " " + p2.getname() + " played ace of " + c2.get_card_type() + ". Draw. ");
            }
            if (t1 < 10)
            {
                this->last_turn += (p1.getname() + " played " + to_string(c1.get_card_num() + 1) + " of " + c1.get_card_type() + " " + p2.getname() + " played " + to_string(c1.get_card_num() + 1) + " of " + c2.get_card_type() + ". Draw. ");
            }
            this->draws += 1;
            if (p1.stacksize() == 0 && p2.stacksize() == 0)
            {
                p1.updatecardstaken(cardstobetaken / 2);
                p2.updatecardstaken(cardstobetaken / 2);
                return;
            }
            p1.popcard();
            p2.popcard();
            if (p1.stacksize() == 0)
            {
                this->draws -= 1;
                cardstobetaken += 2;
                continue;
            }
            c1 = p1.topcard();
            p1.popcard();
            c2 = p2.topcard();
            p2.popcard();
            cardstobetaken += 4;
        }
        if (c1.get_card_num() > c2.get_card_num())
        {
            int t1 = c1.get_card_num();
            if (t1 == 10)
            {
                this->last_turn += (p1.getname() + " played prince of " + c1.get_card_type() + " ");
            }
            if (t1 == 11)
            {
                this->last_turn += (p1.getname() + " played queen of " + c1.get_card_type() + " ");
            }
            if (t1 == 12)
            {
                this->last_turn += (p1.getname() + " played king of " + c1.get_card_type() + " ");
            }
            if (t1 == 13)
            {
                this->last_turn += (p1.getname() + " played ace of " + c1.get_card_type() + " ");
            }
            if (t1 < 10)
            {
                this->last_turn += (p1.getname() + " played " + to_string(c1.get_card_num() + 1) + " of " + c1.get_card_type() + " ");
            }
            int t2 = c2.get_card_num();
            if (t2 == 10)
            {
                this->last_turn += (p2.getname() + " played prince of " + c2.get_card_type() + ". " + p1.getname() + " wins.\n");
            }
            if (t2 == 11)
            {
                this->last_turn += (p2.getname() + " played queen of " + c2.get_card_type() + ". " + p1.getname() + " wins.\n");
            }
            if (t2 == 12)
            {
                this->last_turn += (p2.getname() + " played king of " + c2.get_card_type() + ". " + p1.getname() + " wins.\n");
            }
            if (t2 == 13)
            {
                this->last_turn += (p2.getname() + " played ace of " + c2.get_card_type() + ". " + p1.getname() + " wins.\n");
            }
            if (t2 < 10)
            {
                this->last_turn += (p2.getname() + " played " + to_string(c2.get_card_num() + 1) + " of " + c2.get_card_type() + ". " + p1.getname() + " wins.\n");
            }
            if (!(c1.get_card_num() == 13 && c2.get_card_num() == 2))
            { // 2 beats ace
                p1.updatecardstaken(cardstobetaken);
                this->p1wins += 1;
            }
            else
            {
                p2.updatecardstaken(cardstobetaken);
                this->p2wins += 1;
            }
        }
        if (c1.get_card_num() < c2.get_card_num())
        {
            int t1 = c1.get_card_num();
            if (t1 == 10)
            {
                this->last_turn += (p1.getname() + " played prince of " + c1.get_card_type() + " ");
            }
            if (t1 == 11)
            {
                this->last_turn += (p1.getname() + " played queen of " + c1.get_card_type() + " ");
            }
            if (t1 == 12)
            {
                this->last_turn += (p1.getname() + " played king of " + c1.get_card_type() + " ");
            }
            if (t1 == 13)
            {
                this->last_turn += (p1.getname() + " played ace of " + c1.get_card_type() + " ");
            }
            if (t1 < 10)
            {
                this->last_turn += (p1.getname() + " played " + to_string(c1.get_card_num() + 1) + " of " + c1.get_card_type() + " ");
            }
            int t2 = c2.get_card_num();
            if (t2 == 10)
            {
                this->last_turn += (p2.getname() + " played prince of " + c2.get_card_type() + ". " + p2.getname() + " wins.\n");
            }
            if (t2 == 11)
            {
                this->last_turn += (p2.getname() + " played queen of " + c2.get_card_type() + ". " + p2.getname() + " wins.\n");
            }
            if (t2 == 12)
            {
                this->last_turn += (p2.getname() + " played king of " + c2.get_card_type() + ". " + p2.getname() + " wins.\n");
            }
            if (t2 == 13)
            {
                this->last_turn += (p2.getname() + " played ace of " + c2.get_card_type() + ". " + p2.getname() + " wins.\n");
            }
            if (t2 < 10)
            {
                this->last_turn += (p2.getname() + " played " + to_string(c2.get_card_num() + 1) + " of " + c2.get_card_type() + ". " + p2.getname() + " wins.\n");
            }
            if (!(c2.get_card_num() == 13 && c1.get_card_num() == 2))
            { // 2 beats ace
                p2.updatecardstaken(cardstobetaken);
                this->p2wins += 1;
            }
            else
            {
                p1.updatecardstaken(cardstobetaken);
                this->p1wins += 1;
            }
        }
        this->logs.push_back(this->last_turn);
    }
}

void Game::init_card_array()
{
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 13; j++)
        {
            if (i == 1)
            {
                this->carr.push_back(Card(j, "Diamonds"));
            }
            if (i == 2)
            {
                this->carr.push_back(Card(j, "Spades"));
            }
            if (i == 3)
            {
                this->carr.push_back(Card(j, "Hearts"));
            }
            if (i == 4)
            {
                this->carr.push_back(Card(j, "Clubs"));
            }
        }
    }
}

void Game::shuffle_cards()
{
    unsigned num = chrono::system_clock::now().time_since_epoch().count();
    shuffle(this->carr.begin(), this->carr.end(), default_random_engine(num));
}

void Game::printcarr()
{
    for (std::vector<Card>::size_type i = 0; i < this->carr.size(); i++)
    {
        std::cout << this->carr[i].get_card_num() << ", ";
    }
}
void Game::printLastTurn()
{
    std::cout << this->last_turn;
}
void Game::playAll()
{
    while (p1.stacksize() != 0)
        playTurn();
}
void Game::printWiner()
{
    if (p1.cardesTaken() + p2.cardesTaken() != 52)
    {
        std::cout << "still no winner" << endl;
        return;
    }
    if (p1.cardesTaken() > p2.cardesTaken())
    {
        std::cout << p1.getname() << endl;
        return;
    }
    if (p1.cardesTaken() < p2.cardesTaken())
    {
        std::cout << p2.getname() << endl;
        return;
    }
    std::cout << "draw";
}
void Game::printLog()
{
    for (std::vector<string>::size_type i = 0; i < this->logs.size(); i++)
    {
        std::cout << this->logs[i];
    }
}
void Game::printStats()
{
    std::cout << p1.getname() << " stats: win rate: " << this->p1wins / this->totalrounds * 100 << " percent  cards won: " << p1.cardesTaken() << endl;
    std::cout << p2.getname() << " stats: win rate: " << this->p2wins / this->totalrounds * 100 << " percent  cards won: " << p2.cardesTaken() << endl;
    std::cout << "Draw rate: " << this->draws / this->totalrounds * 100 << " percent  amount of draws: " << this->draws << endl;
}