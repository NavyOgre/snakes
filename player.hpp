#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_
#include <string>
#include <vector>
#include "board.hpp"

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
int resolve_game_type();
void init_game(const int load_action, std::vector<Player> &players);
void init_players_new(const int game_type, std::vector<Player> &players);
void init_players_load(std::vector<Player> &players);
int turn_anounce(const int id, const std::vector<Player> &players);
void player_move(const int id, std::vector<Player> &players, int &roll, std::string &winner, const std::vector<Square> &board);
void shop_action(const int id, std::vector<Player> &players, int &choice, int &roll);
void resolve_move(const int id, std::vector<Player> &players, const int roll, const std::vector<Square> &board);

#endif