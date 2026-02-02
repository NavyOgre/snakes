#include <iostream>
#include <cstdlib>
#include "board.hpp"
#include "player.hpp"
#include "shop.hpp"
#include "bot.hpp"

int main() {
        std::cout << "Hello and welcome to my snakes and ladders game!\n";
        std::cout << "================================================\n\n\n";
        srand(time(0));
        std::vector<Square> board;
        init_board(board);
        int load_action {ask_loading()};
        std::vector<Player> players;
        if (load_action == 1) {
                int game_type {ask_game_type()};
                get_player_info(players, game_type);
                if (game_type == 1) {
                        int difficulty {ask_difficulty()};
                }
        } else {
                // initialize game from file
        }
        std::string winner;
        int turn {0}, total_turns {0};
        std::cout << std::boolalpha;
        while (winner.empty()) {
                ++total_turns;
                int current_player {turn % 2};
                int die_roll {roll(6)};
                players.at(current_player).bonus_turn = die_roll == 6 ? true : false;
                int shop_selection {};
                if (!(players.at(current_player).bot)) {
                        display_board(board);
                        turn_announce(players, current_player, die_roll, board);
                        shop_selection = get_shop_choice(players.at(current_player), die_roll);
                } else {

                }
                shop_action(players.at(current_player), die_roll, shop_selection);
                player_move(players, current_player, die_roll, board);
                check_winner(players.at(current_player), winner);
                if (!(players.at(current_player).bonus_turn)) {
                        ++turn;
                }
        }
        std::cout << "\n\n" << winner << " won the game in " << total_turns << "!\n";
}