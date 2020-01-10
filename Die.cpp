//
// Created by Student on 10/20/2019.
//

#include "Die.h"

Die::Die(){ value = 0; }

int Die::getValue() { return value; }

void Die::setValue(int number) { value = number; }

bool operator == (Die const &p1, Die const &p2)
{
    return &p1 == &p2;
}

bool operator != (Die const &p1, Die const &p2)
{
    return &p1 != &p2;
}