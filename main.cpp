#include <iostream>
#include "board.hpp"
#include "player.hpp"

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
                get_player_info(players, game_type); // bot not implemented yet
        } else {
                // initialize game from file
        }
        std::string winner;
        int turn {0}, total_turns {0};
        std::cout << std::boolalpha;
        while (winner.empty()) {
                ++total_turns;
                int current_player {turn % 2};
                if (!(players.at(current_player).bot)) {
                        display_board(board);
                        int die_roll {roll(6)};
                        turn_announce(players, current_player, die_roll, board);
                        player_move(players, current_player, die_roll, board);
                }
                // test
                ++turn;
                if (total_turns > 20) {
                        winner = "Amirreza";
                }
                // end test
        }
}