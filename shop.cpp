#include "shop.hpp"
#include <iostream>

int get_shop_choice(const Player &player, const int die_roll) {
        std::cout << "Would you like to buy anything from the shop?\n";
        std::cout << "0. continue\n";
        std::cout << "1. -1 from roll(1c)\n";
        std::cout << "2. +1 to roll(2c)\n";
        std::cout << "3. reroll(3c)\n";
        std::cout << "4. buy shield(4c)\n";
        std::cout << "Enter your choice: ";
        int shop_selection {};
        do {
                std::cin >> shop_selection;
                if (shop_selection < 0 || shop_selection > 4) {
                        std::cout << "Invalid choice, try again: ";
                } else {
                        check_valid(player, die_roll, shop_selection);
                }
        } while (shop_selection < 0 || shop_selection > 4);
        return shop_selection;
}

void check_valid(const Player &player, const int die_roll, int &shop_choice) {
        switch (shop_choice) {
                case 1: {
                        if (die_roll == 1) {
                                std::cout << "You can't roll any lower than 1! Try again: ";
                                shop_choice = -1;
                        } else if (player.coin < 1) {
                                std::cout << "You don't have enough coins! Try again: ";
                                shop_choice = -1;
                        }
                        break;
                }
                case 2: {
                        if (die_roll == 6) {
                                std::cout << "You can't roll any higher than 6! Try again: ";
                                shop_choice = -1;
                        } else if (player.coin < 2) {
                                std::cout << "You don't have enough coins! Try again: ";
                                shop_choice = -1;
                        }
                        break;
                }
                case 3: {
                        if (player.coin < 3) {
                                std::cout << "You don't have enough coins! Try again: ";
                                shop_choice = -1;
                        }
                        break;
                }
                case 4: {
                        if (player.shield) {
                                std::cout << "You already have a shield! Try again: ";
                                shop_choice = -1;
                        } else if (player.coin < 4) {
                                std::cout << "You don't have enough coins! Try again: ";
                                shop_choice = -1;
                        }
                }
        }
}