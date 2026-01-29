#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <string>

struct Player {
        bool is_bot;
        std::string name;
        int rival_id;
        int position;
        int coin;
        bool shield;
        bool bonus_turn;
};

int roll_die();



#endif