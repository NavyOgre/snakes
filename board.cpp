#include "board.hpp"
#include <iostream>

void intro() {
        std::cout << "Welcome! Thank you for trying my snakes and ladders game.\n";
        std::cout << "=========================================================\n\n\n";
}

int loading_dialogue() {
        std::cout << "Would you like to start a new game or load a previous game?\n";
        std::cout << "1. New game\n";
        std::cout << "2. Load previous game\n";
        int input {};
        do {
                std::cin >> input;
                if (input != 1 && input != 2) {
                        std::cout << "Invalid input, try again.\n";
                }
        } while (input != 1 && input != 2);
        return input;
}