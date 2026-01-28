#include <iostream>
#include "board.hpp"
#include <string>

using std::cout;
using std::cin;

int main() {
        intro();
        int load_action {loading_dialogue()};
        switch (load_action) {
                // new game
                case 2: {
                        // initialize from file
                }
                default: {
                        // initialize from user input
                }
                
        }
        std::string winner;
        while (winner == "") {
                std::cout << "test\n";
                winner = "Amirreza";
        }
        std::cout << "Congratulations " << winner << ", you have won!\n";
}