#include "player.hpp"
#include "iostream"
using namespace std;

Player::Player(){
    
}
Player::Player(string player_Name)
{
    this->player_Name = player_Name;
    this->cards_taken = 0;
}

int Player::cardesTaken()
{
    return this->cards_taken;
}

int Player::stacksize()
{
    return this->cards.size();
}

Card Player::topcard()
{
    return this->cards.top();
}

void Player::popcard()
{
    this->cards.pop();
}

void Player::updatecardstaken(int n)
{
    this->cards_taken+= n;
}

void Player::givecard(Card c)
{
    this->cards.push(c);
}

string Player::getname()
{
    return this->player_Name;
}