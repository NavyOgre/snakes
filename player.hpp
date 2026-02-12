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

int ask_game_type(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, ALLEGRO_MOUSE_STATE &mouse_state);
void get_player_info(std::vector<Player> &players, const int p_number, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, bool &done);
void turn_announce(const std::vector<Player> &players, const int id);
int turn_action(const int turn, const int total_turns, const std::vector<Player> &players);
int roll(const int n);
void player_move(std::vector<Player> &players, const int id, const int die_roll);

// helper functions for player_move
void check_hit(Player &player, Player &rival);
void resolve_move(Player &player);
// helper functions for player_move

bool load_game(int &turn, int &total_turns, std::vector<Player> &players);
void save_game(const int turn, const int total_turns, const std::vector<Player> &players);

#endif