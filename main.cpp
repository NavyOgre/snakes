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
        int turn {0}, total_turns {0};
        if (load_action == 1) {
                int game_type {ask_game_type()};
                get_player_info(players, game_type);
                if (game_type == 1) {
                        int difficulty {ask_difficulty()};
                        init_bot(difficulty, players);
                }
        } else {
                // initialize game from file
        }
        std::string winner;
        std::cout << std::boolalpha;
        while (winner.empty()) {
                ++total_turns;
                int current_player {turn % 2};
                int die_roll {roll(6)};
                players.at(current_player).bonus_turn = die_roll == 6 ? true : false;
                int shop_selection {};
                if (!(players.at(current_player).bot)) {
                        display_board();
                        turn_announce(players, current_player, die_roll);
                        shop_selection = get_shop_choice(players.at(current_player), die_roll);
                } else {
                        switch (players.at(current_player).bot) {
                                case 1: {
                                        shop_selection = easy_shop(players.at(current_player), die_roll);
                                        break;
                                }
                                case 2: {
                                        // normal shop
                                        break;
                                }
                                case 3: {
                                        // hard shop
                                }
                        }
                }
                shop_action(players.at(current_player), die_roll, shop_selection);
                player_move(players, current_player, die_roll, board);
                check_winner(players.at(current_player), winner);
                if (!(players.at(current_player).bonus_turn)) {
                        ++turn;
                }
        }
        std::cout << "\n\n" << winner << " won the game in " << total_turns << " turns!\n";
}