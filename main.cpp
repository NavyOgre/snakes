#include "board.hpp"
#include <iostream>
#include <string>
#include "player.hpp"

int main() {
        int load_action {intro()};
        std::vector<Square> board;
        init_board(load_action, board);
        std::string winner;
        while (winner == "") {
                // game code
                display_board(board);


                // testing functions temporary code
                std::cout << roll_die() << "\n";
                std::cout << "test\n";
                winner = "Amirreza";
                // testing functions temporary code


        }
        std::cout << "Congratulations " << winner << ", you have won!\n";
}