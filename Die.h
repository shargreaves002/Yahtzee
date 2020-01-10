//
// Created by Student on 10/20/2019.
//

#ifndef FIRST_PROJECT_DIE_H
#define FIRST_PROJECT_DIE_H

class Die {
private:
    int value;

public:
    Die();
    void setValue(int number);
    int getValue();
    friend bool operator == (Die const &p1, Die const &p2);
    friend bool operator != (Die const &p1, Die const &p2);
};
#endif
