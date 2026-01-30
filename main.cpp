#include "board.hpp"
#include <iostream>
#include "player.hpp"

int main() {
        srand(time(0));
        std::vector<Square> board;
        init_board(board);
        int load_action {intro()};
        std::vector<Player> players;
        init_game(load_action, players);
        std::string winner;
        int turn {0}, total_turns {0}, id {}, roll {};
        while (winner == "") {
                display_board(board);
                ++total_turns;
                id = turn % 2;
                if (!players.at(id).is_bot) {
                        roll = turn_anounce(id, players);
                        player_move(id, players, roll, winner, board);
                        std::cout << "square: " << players.at(id).position + 1 << "\n\n";
                } else {
                        // bot move
                }
                if (players.at(id).bonus_turn) {
                        players.at(id).bonus_turn = false;
                } else {
                        ++turn;
                }
        }
        std::cout << winner << " won the game!\n";
}