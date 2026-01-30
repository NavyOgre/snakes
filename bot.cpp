#include "bot.hpp"
#include <iostream>

int bot_move(const int id, std::vector<Player> &players, int &roll, std::string &winner, std::vector<Square> &board) {
        if (roll == 6) {
                players.at(id).bonus_turn = true;
        }
        int shop_choice {rand() % (players.at(id).coin + 1)};
        if (players.at(id).bot == 1) {
                bot_shop(players.at(id), roll, shop_choice);
        } else {
                // normal bot
        }
        int &position {players.at(id).position};
        if (position + roll <= 99) {
                position += roll;
                resolve_move(id, players, roll, board);
                if (position == 99) {
                        winner = players.at(id).name;
                }
        }
        return roll;
}

void bot_shop(Player &bot, int &roll, const int shop_choice) {
        switch (shop_choice) {
                case 1: {
                        roll_subtract1(bot, roll);
                        std::cout << "\nBot subtracted 1 from roll";
                }
                case 2: {
                        roll_plus1(bot, roll);
                        std::cout << "\nBot added 1 to roll";
                }
                case 3: {
                        reroll(bot, roll);
                        std::cout << "\nBot rerolled";
                }
                case 4: {
                        buy_shield(bot);
                        std::cout << "\nBot bought a shield";
                }
                default: {}
        }
}