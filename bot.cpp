#include "bot.hpp"
#include <iostream>

int easy_shop(const Player &bot, const int die_roll) {
        std::vector<int> choices;
        int choice {};
        switch (bot.coin) {
                case 0: {
                        choices = {0};
                        choice = 1;
                        break;
                }
                case 1: {
                        if (die_roll == 1) {
                                choices = {0};
                                choice = 1;
                        } else {
                                choices = {0, 1};
                                choice = roll(2);
                        }
                        break;
                }
                case 2: {
                        switch (die_roll) {
                                case 1: {
                                        choices = {0, 2};
                                        choice = roll(2);
                                        break;
                                }
                                case 6: {
                                        choices = {0, 1};
                                        choice = roll(2);
                                        break;
                                }
                                default: {
                                        choices = {0, 1, 2};
                                        choice = roll(3);
                                }
                        }
                        break;
                }
                case 3: {
                        switch (die_roll) {
                                case 1: {
                                        choices = {0, 2, 3};
                                        choice = roll(3);
                                        break;
                                }
                                case 6: {
                                        choices = {0, 1, 3};
                                        choice = roll(3);
                                        break;
                                }
                                default: {
                                        choices = {0, 1, 2, 3};
                                        choice = roll(4);
                                }
                        }
                        break;
                }
                default: {
                        if (!(bot.shield)) {
                                switch (die_roll) {
                                        case 1: {
                                                choices = {0, 2, 3, 4};
                                                choice = roll(4);
                                                break;
                                        }
                                        case 6: {
                                                choices = {0, 1, 3, 4};
                                                choice = roll(4);
                                                break;
                                        }
                                        default: {
                                                choices = {0, 1, 2, 3, 4};
                                                choice = roll(5);
                                        }
                                }
                        } else {
                                switch (die_roll) {
                                        case 1: {
                                                choices = {0, 2, 3};
                                                choice = roll(3);
                                                break;
                                        }
                                        case 6: {
                                                choices = {0, 1, 3};
                                                choice = roll(3);
                                                break;
                                        }
                                        default: {
                                                choices = {0, 1, 2, 3};
                                                choice = roll(4);
                                        }
                                }
                        }
                }
        }
        return choices.at(choice - 1);
}