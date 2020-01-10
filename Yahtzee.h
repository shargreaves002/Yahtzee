//
// Created by Student on 10/20/2019.
//

#ifndef FIRST_PROJECT_YAHTZEE_H
#define FIRST_PROJECT_YAHTZEE_H

#include <array>
#include <list>
#include <vector>
#include "Die.h"
#include "Player.h"

class Yahtzee
{
private:
    Die d1, d2, d3, d4, d5;
    Die *savedDice[5] { nullptr };
    int count[6]{ 0 };
    bool stillPlaying;
    enum Choices {
        error,
        ones,
        twos,
        threes,
        fours,
        fives,
        sixes,
        three_of_a_kind,
        four_of_a_kind,
        full_house,
        low_straight,
        high_straight,
        yahtzee,
        yahtzee_bonus,
        chance,
        quit
    };
    void rollDice();
    static void clearArray(Die **arr, int length);
    static string makeChoice(Player* player);
    void score(Player * player, const string &choice);
    static int mapChoice(const string &choice);
    static void printScores(const list<Player *>& list);


public:
    Yahtzee();
    void play(const list<Player*>& players);
};
#endif
