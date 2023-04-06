#include "card.hpp"
#include "iostream"
#include "string.h"
using namespace std;
namespace ariel{

}

Card::Card(int num, string type)
{
    this->card_num = num;
    this->card_type = type;
}

int Card::get_card_num()
{
    return this->card_num;
}

string Card::get_card_type()
{
    return this->card_type;
}