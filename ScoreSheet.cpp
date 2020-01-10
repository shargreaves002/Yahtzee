//
// Created by Student on 10/24/2019.
//

#include "ScoreSheet.h"
#include <algorithm>

using namespace std;

ScoreSheet::ScoreSheet() {
    choices->emplace_back("ones");
    choices->emplace_back("twos");
    choices->emplace_back("threes");
    choices->emplace_back("fours");
    choices->emplace_back("fives");
    choices->emplace_back("sixes");
    choices->emplace_back("3 of a kind");
    choices->emplace_back("4 of a kind");
    choices->emplace_back("full house");
    choices->emplace_back("low straight");
    choices->emplace_back("high straight");
    choices->emplace_back("yahtzee");
    choices->emplace_back("chance");
    choices->emplace_back("quit");
}

void ScoreSheet::score(const string &name, const int value) {
    scoreSheet[name] = value;
    choices->erase(find(choices->begin(), choices->end(), name));
}

map<const string, int> ScoreSheet::getScoreSheet() {
    return scoreSheet;
}

vector<string>* ScoreSheet::getChoices(){
    return choices;
}