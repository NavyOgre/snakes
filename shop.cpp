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

void shop_action(Player &player, int &die_roll, const int shop_choice) {
        switch (shop_choice) {
                case 1: {
                        player.coin -= 1;
                        die_roll -= 1;
                        player.bonus_turn = false;
                        std::cout << player.name << " used 1 coin to subtract 1 from their roll.\n";
                        std::cout << "New roll: " << die_roll << "\n";
                        break;
                }
                case 2: {
                        player.coin -= 2;
                        die_roll += 1;
                        std::cout << player.name << " used 2 coin to add 1 to their roll.\n";
                        std::cout << "New roll: " << die_roll << "\n";
                        break;
                }
                case 3: {
                        player.coin -= 3;
                        die_roll = roll(6);
                        std::cout << player.name << " used 3 coins to roll again.\n";
                        std::cout << "New roll: " << die_roll << "\n";
                        if (die_roll == 6) {
                                player.bonus_turn = true;
                        }
                        break;
                }
                case 4: {
                        player.coin -= 4;
                        player.shield = true;
                        std::cout << player.name << " used 4 coins to buy a shield.\n";
                }
        }
}