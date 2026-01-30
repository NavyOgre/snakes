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

int roll_die();
int resolve_game_type();
void init_game(const int load_action, std::vector<Player> &players);
void init_players_new(const int game_type, std::vector<Player> &players);
void init_players_file(std::vector<Player> &players);
int turn_anounce(const int id, const std::vector<Player> &players);
void player_move(const int id, std::vector<Player> &players, int &roll, std::string &winner, const std::vector<Square> &board);
void shop_action(Player &player, int &choice, int &roll);
void reroll(Player &player, int &roll);
void roll_plus1(Player &player ,int &roll);
void roll_subtract1(Player &player, int &roll);
void buy_shield(Player &players);
void resolve_move(const int id, std::vector<Player> &players, const int roll, const std::vector<Square> &board);

#endif