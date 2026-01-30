#ifndef _BOT_HPP_
#define _BOT_HPP_
#include "player.hpp"

int bot_move(const int id, std::vector<Player> &players, int &roll, std::string &winner, std::vector<Square> &board);
void bot_shop(Player &bot, int &roll, const int shop_choice);

#endif