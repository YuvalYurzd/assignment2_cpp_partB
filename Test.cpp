#include "doctest.h"
#include "sources/card.hpp"
#include "sources/game.hpp"
#include "sources/player.hpp"

using namespace std;

TEST_CASE("check_intial_players")
{
    CHECK_NOTHROW(Player p2("Yuval"));
    Player p1("Yuval1");
    CHECK_NOTHROW(p1.cardesTaken());
    CHECK_NOTHROW(p1.stacksize());
    CHECK(p1.stacksize() == 0);
    CHECK(p1.cardesTaken() == 0);
}

TEST_CASE("test_game_functions")
{
    Player p1("Yuval1");
    Player p2("Yuval2");
    Game game(p1,p2);
    CHECK_NOTHROW(game.playTurn());
    game.playTurn();
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.playAll());
    game.playAll();
    CHECK_NOTHROW(game.printWiner());
}

TEST_CASE("testing_Game_constructor_and_card_shuffle")
{
    Player p1("Yuval1");
    Player p2("Yuval2");
    CHECK_NOTHROW(Game game(p1,p2));
    Player p3("Yuval3");
    Game game(p1,p2);
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    CHECK_THROWS_AS(Game game2(p1,p3), invalid_argument); // p1 can be only part of one game at a time
    game.playAll();
    CHECK_NOTHROW(Game game2(p1,p3));
    Game game2(p1,p3);
    //check that p1's stats reset
    CHECK(p1.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
}

TEST_CASE("test_turn")
{
    Player p1("Yuval1");
    Player p2("Yuval2");
    Game game(p1,p2);
    game.playTurn();
    CHECK(p1.stacksize() == 25);
    CHECK(p2.stacksize() == 25);
}

TEST_CASE("test_cards_taken")
{
    Player p1("Yuval1");
    Player p2("Yuval2");
    Game game(p1,p2);
    for(int i = 0; i < 14; i++)
    {
        game.playTurn();
    }
    if(p1.stacksize() > 0 && p2.stacksize() > 0) // case in which not all the 14 turns were draws
    {
        bool cards_taken = false;
        if(p1.cardesTaken() > 0 || p2.cardesTaken() > 0) // making sure cards were taken
            cards_taken = true;
        CHECK(cards_taken == true);
    }
    else // case in which all the 14 turns were draws
    {
        CHECK(p1.cardesTaken() == 0);
        CHECK(p2.cardesTaken() == 0);
    }
}

TEST_CASE("test_game_end")
{
    Player p1("Yuval1");
    Player p2("Yuval2");
    Game game(p1,p2);
    game.playAll();
    CHECK(p1.cardesTaken() + p2.cardesTaken() == 52);
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
    CHECK_THROWS(game.playAll());
    CHECK_THROWS(game.playTurn());
}

// This test should be tested only when we implement the game
// TEST_CASE("test_draw_situations")
// {
//     Player p1("Yuval1");
//     Player p2("Yuval2");
//     Game game(p1,p2);
//     while(p1.cardesTaken() + p2.cardesTaken() != 52)
//     {
//         if(p1.stacksize() == 0 && p2.stacksize() == 0) //check reshuffle in case of both players ran out of cards in a draw
//         {
//             game.playTurn();
//             CHECK(p1.stacksize() > 0);
//             CHECK(p2.stacksize() > 0);
//         }
//         game.playTurn();
//     }

// }

