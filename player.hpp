#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "board.hpp"

struct Player {
        int bot;
        std::string name;
        int id;
        int rival_id;
        int position;
        int coin;
        bool shield;
        bool bonus_turn;
};

void get_player_info(std::vector<Player> &players, int player_cnt);

#endif