#include "board.hpp"
#include <iostream>
#include <string>
#include "player.hpp"

int main() {
        std::vector<Square> board;
        init_board(board);
        int load_action {intro()};
        std::vector<Player> players;
        init_game(load_action, players);
        std::string winner;
        while (winner == "") {
                // game code
                display_board(board);


                // testing functions temporary code
                std::cout << players.at(0).name << "\n";
                std::cout << players.at(0).is_bot << "\n";
                std::cout << players.at(0).bonus_turn << "\n";
                std::cout << players.at(0).coin << "\n";
                std::cout << players.at(0).position << "\n";
                std::cout << players.at(0).rival_id << "\n";
                std::cout << players.at(0).shield << "\n";
                std::cout << roll_die() << "\n" << "\n";
                std::cout << players.at(1).name << "\n";
                std::cout << players.at(1).is_bot << "\n";
                std::cout << players.at(1).bonus_turn << "\n";
                std::cout << players.at(1).coin << "\n";
                std::cout << players.at(1).position << "\n";
                std::cout << players.at(1).rival_id << "\n";
                std::cout << players.at(1).shield << "\n";
                std::cout << roll_die() << "\n" << "\n";
                winner = "Amirreza";
                // testing functions temporary code


        }
        std::cout << "Congratulations " << winner << ", you have won!\n";
}