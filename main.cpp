#include <iostream>
#include "player.hpp"
#include "bot.hpp"

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
                ++total_turns;
                id = turn % 2;
                if (!players.at(id).bot) {
                        display_board(board);
                        roll = turn_anounce(id, players);
                        player_move(id, players, roll, winner, board);
                } else {
                        roll = roll_die();
                        roll = bot_move(id, players, roll, winner, board);
                        std::cout << "Bot rolled " << roll;
                }
                std::cout << "\n\n";
                if (players.at(id).bonus_turn) {
                        players.at(id).bonus_turn = false;
                } else {
                        ++turn;
                }
        }
        std::cout << winner << " won the game!\n";
}