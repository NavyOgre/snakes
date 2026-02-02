#include <iostream>
#include "board.hpp"
#include "player.hpp"

int main() {
        std::cout << "Hello and welcome to my snakes and ladders game!\n";
        std::cout << "================================================\n\n\n";
        std::vector<Square> board;
        init_board(board);
        int load_action {ask_loading()};
        std::vector<Player> players;
        if (load_action == 1) {
                int game_type {ask_game_type()};
                get_player_info(players, game_type);
        } else {
                // initialize game from file
        }
}