#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include "board.hpp"

struct Player {
        int bot;
        std::string name;
        int rival_id;
        int position;
        int coin;
        bool shield;
        bool bonus_turn;
};

void get_player_info(std::vector<Player> &players, int player_cnt);
void turn_announce(const std::vector<Player> &players, const int id, const int die_roll, const std::vector<Square> &board);
int roll(const int n);
void player_move(std::vector<Player> &players, const int id, const int die_roll, const std::vector<Square> &board);

// helper functions for player_move
void check_hit(Player &player, Player &rival);
void resolve_move(const std::vector<Square> &board, Player &player);
// helper functions for player_move

void check_winner(const Player &player, std::string &winner);

#endif