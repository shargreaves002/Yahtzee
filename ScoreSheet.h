//
// Created by Student on 10/24/2019.
//

#ifndef FIRST_PROJECT_SCORESHEET_H
#define FIRST_PROJECT_SCORESHEET_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class ScoreSheet {
private:
    map <const string, int> scoreSheet;
    vector<string> * choices = new vector<string>;

public:
    ScoreSheet();

    void score(const string &name, int value);
    map<const string, int> getScoreSheet();

    vector<string>* getChoices();
};
#endif
