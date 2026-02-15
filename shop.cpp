#include "shop.hpp"
#include <iostream>

void shop_action(Player &player, int &die_roll, const int shop_choice) {
        switch (shop_choice) {
                case 1: {
                        player.coin -= 1;
                        die_roll -= 1;
                        player.bonus_turn = false;
                        break;
                }
                case 2: {
                        player.coin -= 2;
                        die_roll += 1;
                        break;
                }
                case 3: {
                        player.coin -= 3;
                        die_roll = roll(6);
                        if (die_roll == 6) {
                                player.bonus_turn = true;
                        } else {
                                player.bonus_turn = false;
                        }
                        break;
                }
                case 4: {
                        player.coin -= 4;
                        player.shield = true;
                }
        }
}