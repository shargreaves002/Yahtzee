//
// Created by Student on 10/20/2019.
//

#include "Player.h"
#include <utility>

Player::Player(string name)
{
    this->name = move(name);
    this->isPlaying = true;
}

string Player::getName() { return this->name; }

ScoreSheet* Player::getScoreSheet() {
    return scoreSheet;
}

bool Player::getPlaying() const {
    return isPlaying;
}

void Player::setIsPlaying(bool isPlaying) {
    Player::isPlaying = isPlaying;
}

