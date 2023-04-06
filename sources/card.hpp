#ifndef X2
#define X2
#include "iostream"
#include "string.h"
using namespace std;
namespace ariel{

}
class Card {
    private:
        int card_num;
        string card_type;
    public:
        Card(int num, string type);
        int get_card_num();
        string get_card_type();
};

#endif