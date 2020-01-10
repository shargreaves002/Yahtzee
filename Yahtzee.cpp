//
// Created by Student on 10/20/2019.
//

#include "Yahtzee.h"
#include <algorithm>
#include <random>
#include <iostream>

Yahtzee::Yahtzee() {
    stillPlaying = true;
}

void Yahtzee::play(const list<Player*>& players)
{
    while (stillPlaying)
    {
        for (Player *j : players)
        {
            if (j->getPlaying())
            {
                //first, we roll dice:
                rollDice();

                //Then show their choices:
                cout << "Your choices:" << endl;
                for (auto &i : *j->getScoreSheet()->getChoices()) std::cout << i << endl;
                cout << endl;

                //make the decision:
                cin.ignore();
                string answer = makeChoice(j);

                //mark their score on their score sheet
                score(j, answer);

                //make them stop playing if they have no more choices
                if (j->getScoreSheet()->getChoices()->size() == 1)
                {
                    j->setIsPlaying(false);
                }
            }
        }

        //exit while loop if no more players are playing

        stillPlaying = false;
        for (Player *i : players)
        {
            stillPlaying |= i->getPlaying();
        }
    }

    printScores(players);
}

void Yahtzee::rollDice()
{
    //start by clearing all saved dice
    clearArray(savedDice, size(savedDice));
    //you get three rolls per turn
    for (int x = 0; x < 3; x++)
    {
        //Start by rolling the dice that aren't saved from the previous roll
        random_device rnd;
        mt19937 randomNumber(rnd());
        if (savedDice[0] == nullptr)
            d1.setValue((int) ((randomNumber.operator()() % 6) + 1));
        if (savedDice[1] == nullptr)
            d2.setValue((int) ((randomNumber.operator()() % 6) + 1));
        if (savedDice[2] == nullptr)
            d3.setValue((int) ((randomNumber.operator()() % 6) + 1));
        if (savedDice[3] == nullptr)
            d4.setValue((int) ((randomNumber.operator()() % 6) + 1));
        if (savedDice[4] == nullptr)
            d5.setValue((int) ((randomNumber.operator()() % 6) + 1));
        //if this isn't their last roll
        if (x < 2)
        {
            //display dice rolls
            cout << "Your dice rolls are: " +
                    to_string(d1.getValue()) +
                    ", " + to_string(d2.getValue()) +
                    ", " + to_string(d3.getValue()) +
                    ", " + to_string(d4.getValue()) +
                    ", " + to_string(d5.getValue()) +
                    "." << endl;

            //then save some dice
            //this takes a string that we'll iterate through one character at a time
            // ex: "123" saves dice 1, 2, and 3.
            cout << "Which dice would you like to save?" << endl;
            string answer;
            cin >> answer;
            //We clear the saved dice so we don't accidentally save some from the previous roll
            //we don't need to do this if it's the first roll, it's already cleared
            if (x > 0) clearArray(savedDice, size(savedDice));
            for (char i : answer)
            {
                switch (i)
                {
                    case '1':
                        if (savedDice[0] != &d1)
                            savedDice[0] = &d1;
                        break;
                    case '2':
                        if (savedDice[1] != &d2)
                            savedDice[1] = &d2;
                        break;
                    case '3':
                        if (savedDice[2] != &d3)
                            savedDice[2] = &d3;
                        break;
                    case '4':
                        if (savedDice[3] != &d4)
                            savedDice[3] = &d4;
                        break;
                    case '5':
                        if (savedDice[4] != &d5)
                            savedDice[4] = &d5;
                        break;
                    default:
                        break;
                }
            }

            //This just gives an easy way to save all dice, instead of typing "12345"
            if (answer == "all")
            {
                savedDice[0] = &d1;
                savedDice[1] = &d2;
                savedDice[2] = &d3;
                savedDice[3] = &d4;
                savedDice[4] = &d5;
            }

            //if they saved all dice, don't reroll because obviously they like the current numbers.
            if (savedDice[0] == &d1 &&
                savedDice[1] == &d2 &&
                savedDice[2] == &d3 &&
                savedDice[3] == &d4 &&
                savedDice[4] == &d5)
                break;
        }
        else
        {
            //on the last roll, save all the dice.
            if (savedDice[0] != &d1) savedDice[0] = &d1;
            if (savedDice[1] != &d2) savedDice[1] = &d2;
            if (savedDice[2] != &d3) savedDice[2] = &d3;
            if (savedDice[3] != &d4) savedDice[3] = &d4;
            if (savedDice[4] != &d5) savedDice[4] = &d5;
        }
    }

    //finally, print their total result.
    cout << "Your dice rolls are: " +
            to_string(savedDice[0]->getValue()) +
            ", " + to_string(savedDice[1]->getValue()) +
            ", " + to_string(savedDice[2]->getValue()) +
            ", " + to_string(savedDice[3]->getValue()) +
            ", " + to_string(savedDice[4]->getValue()) +
            "." << endl;
}

//This is used for resetting the savedDice array
void Yahtzee::clearArray(Die **arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        arr[i] = nullptr;
    }
}

string Yahtzee::makeChoice(Player* player)
{
    vector<string> * choices = player->getScoreSheet()->getChoices();

    //Get their choice
    cout << player->getName() << ", please enter a choice:" << endl;
    string answer;
    getline(cin, answer);


    //If their choice is not valid, try again
    if (find(choices->begin(), choices->end(), answer) == choices->end())
    {
        cout << "Invalid choice, please try again." << endl;
        return makeChoice(player);
    }

    //return a valid choice
    return answer;
}

void Yahtzee::score(Player * player, const string &choice)
{
    // this next bit counts how many dice of each value we have
    // used for determining scoring later
    int j = 0;
    ScoreSheet * scoreSheet = player->getScoreSheet();
    for (int &i : count){
        i = 0;
    }
    for (Die *die : savedDice) {
        count[die->getValue() - 1] += 1;
    }

    //check to see if we have 2 dice of the same value
    bool check2 = false;
    // 3 of the same value
    bool check3 = false;
    // 4 of the same value
    bool check4 = false;
    // 5 of the same value
    bool check5 = false;
    for (int i : count) {
        check2 |= (i == 2);
        check3 |= (i == 3);
        check4 |= (i == 4);
        check5 |= (i == 5);
    }

    switch (mapChoice(choice))
    {
        case ones:
            j = count[0];
            scoreSheet->score("ones", j);
            cout << "Added " << j << " points to ones." << endl;
            break;
        case twos:
            j = count[1] * 2;
            scoreSheet->score("twos", j);
            cout << "Added " << j << " points to twos." << endl;
            break;
        case threes:
            j = count[2] * 3;
            scoreSheet->score("threes", j);
            cout << "Added " << j << " points to threes." << endl;
            break;
        case fours:
            j = count[3] * 4;
            scoreSheet->score("fours", j);
            cout << "Added " << j << " points to fours." << endl;
            break;
        case fives:
            j = count[4] * 5;
            scoreSheet->score("fives", j);
            cout << "Added " << j << " points to fives." << endl;
            break;
        case sixes:
            j = count[5] * 6;
            scoreSheet->score("sixes", j);
            cout << "Added " << j << " points to sixes" << endl;
            break;
        case three_of_a_kind:
            if (check3) {
                for (Die *die : savedDice) {
                    j += die->getValue();
                }
                scoreSheet->score("3 of a kind", j);
                cout << "Added " << j << " points to 3 of a kind." << endl;
            } else {
                scoreSheet->score("3 of a kind", 0);
                cout << "Added 0 points to 3 of a kind." << endl;
            }
            break;
        case four_of_a_kind:
            if (check4) {
                for (Die *die : savedDice) {
                    j += die->getValue();
                }
                scoreSheet->score("4 of a kind", j);
                cout << "Added " << j << " points to 4 of a kind." << endl;
            } else {
                scoreSheet->score("4 of a kind", 0);
                cout << "Added 0 points to 4 of a kind." << endl;
            }
            break;
        case full_house:
            if ((check2 && check3) || check5){
                scoreSheet->score("full house", 25);
                cout << "Added 25 points to full house." << endl;
            } else {
                scoreSheet->score("full house", 0);
                cout << "Added 0 points to full house." << endl;
            }
            break;
        case low_straight:
            if ((count[0] >= 1 && count[1] >= 1 && count[2] >= 1 && count[3] >= 1) ||
                (count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1) ||
                (count[2] >= 1 && count[3] >= 1 && count[4] >= 1 && count[5] >= 1)){
                scoreSheet->score("low straight", 30);
                cout << "Added 30 points to low straight." << endl;
            } else {
                scoreSheet->score("low straight", 0);
                cout << "Added 0 points to low straight." << endl;
            }
            break;
        case high_straight:
            if ((count[0] >= 1 && count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1) ||
                (count[1] >= 1 && count[2] >= 1 && count[3] >= 1 && count[4] >= 1 && count[5] >= 1)){
                scoreSheet->score("high straight", 40);
                cout << "Added 40 points to high straight." << endl;
            } else {
                scoreSheet->score("high straight", 0);
                cout << "Added 0 points to high straight." << endl;
            }
            break;
        case yahtzee:
            if (check5) {
                scoreSheet->score("yahtzee", 50);
                cout << "Added 50 points to yahtzee." << endl;
                scoreSheet->getChoices()->emplace_back("yahtzee bonus");
            } else {
                scoreSheet->score("yahtzee", 0);
                cout << "Added 0 points to yahtzee." << endl;
            }
            break;
        case yahtzee_bonus:
            if (check5) {
                scoreSheet->score("yahtzee", 100);
                cout << "Added 100 points to yahtzee." << endl;
            } else {
                scoreSheet->score("yahtzee", 0);
                cout << "Added 0 points to yahtzee." << endl;
            }
            break;
        case chance:
            for (Die *die : savedDice) {
                j += die->getValue();
            }
            scoreSheet->score("chance", j);
            cout << "Added " << j << " points to chance." << endl;
            break;
        case quit:
            player->setIsPlaying(false);
            break;
    }
}

int Yahtzee::mapChoice (const string &choice)
{
    if (choice == "ones") return ones;
    if (choice == "twos") return twos;
    if (choice == "threes") return threes;
    if (choice == "fours") return fours;
    if (choice == "fives") return fives;
    if (choice == "sixes") return sixes;
    if (choice == "3 of a kind") return three_of_a_kind;
    if (choice == "4 of a kind") return four_of_a_kind;
    if (choice == "full house") return full_house;
    if (choice == "low straight") return low_straight;
    if (choice == "high straight") return high_straight;
    if (choice == "yahtzee") return yahtzee;
    if (choice == "yahtzee bonus") return yahtzee_bonus;
    if (choice == "chance") return chance;
    if (choice == "quit") return quit;

    return error;

}

void Yahtzee::printScores(const list<Player *>& list) {
    for (Player * i : list)
    {
        cout << i->getName() << "\'s scores:" << endl;
        int total = 0;
        int upper = 0;
        for (const auto &j : i->getScoreSheet()->getScoreSheet())
        {
            cout << j.first << ": " << j.second << endl;
            total += j.second;
            if (j.first == "ones" || j.first == "twos" ||
                j.first == "threes" || j.first == "fours" ||
                j.first == "fives" || j.first == "sixes")
                upper += j.second;
        }

        if (upper >= 65) total += 35;
        cout << "Total: " << total << endl;
    }
}
