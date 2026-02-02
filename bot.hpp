#ifndef _BOT_HPP_
#define _BOT_HPP_
#include "player.hpp"
#include "shop.hpp"

int ask_difficulty();
void init_bot(const int difficulty, std::vector<Player> &players);

#endif