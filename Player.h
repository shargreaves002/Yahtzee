//
// Created by Student on 10/20/2019.
//
#include "ScoreSheet.h"
#include <string>

#ifndef FIRST_PROJECT_PLAYER_H
#define FIRST_PROJECT_PLAYER_H

class Player
{
private:
    string name;
    ScoreSheet * scoreSheet = new ScoreSheet();
    bool isPlaying;

public:
    string getName();
    explicit Player(string name);
    ScoreSheet* getScoreSheet();

    bool getPlaying() const;

    void setIsPlaying(bool isPlaying);
};
#endif
