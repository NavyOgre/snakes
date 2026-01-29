#include "board.hpp"
#include <iostream>
#include <string>

int main() {
        intro();
        int load_action {loading_dialogue()};
        std::vector<Square> board;
        init_board(load_action, board);
        std::string winner;
        while (winner == "") {
                // game code
                display_board(board);
                std::cout << "test\n";
                winner = "Amirreza";
        }
        std::cout << "Congratulations " << winner << ", you have won!\n";
}