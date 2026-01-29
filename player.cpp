#include "player.hpp"
#include <cstdlib>
#include <iostream>

int roll_die() {
        srand(time(0));
        return rand() % 6 + 1;
}