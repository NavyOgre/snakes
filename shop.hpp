#ifndef _SHOP_HPP_
#define _SHOP_HPP_
#include "player.hpp"

int get_shop_choice(const Player &player, const int die_roll);

// helper function for get_shop_choice
void check_valid(const Player &player, const int die_roll, int &shop_choice);

#endif