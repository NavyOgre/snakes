#include <iostream>
#include "board.hpp"

using std::cout;
using std::vector;

int main() {
        cout << "Hello and welcome to my snakes and ladders game!\n";
        cout << "================================================\n\n";
        vector<Square> board;
        init_board(board);
        int load_action {ask_loading()};
        if (load_action == 1) {
                // ask game type
                // initialize game
        } else {
                // initialize game from file
        }
}