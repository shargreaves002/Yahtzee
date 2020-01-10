#include "Player.h"
#include "Yahtzee.h"

using namespace std;

int main()
{
    auto * player = new Player("Sarah");
    auto * player2 = new Player("Christian");
    Yahtzee yahtzee;
    list<Player*> players;
    players.push_back(player);
    players.push_back(player2);
    yahtzee.play(players);
    delete(player);

    return 0;
}