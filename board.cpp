#include "board.hpp"
#include <iostream>

int ask_loading() {
        std::cout << "Would you like to start a new game or load the previous one?\n";
        std::cout << "1. New game\n";
        std::cout << "2. Load game\n";
        std::cout << "Enter your choice: ";
        int load_input {};
        do {
                std::cin >> load_input;
                if (load_input != 1 && load_input != 2) {
                        std::cout << "Invalid choice, try again: ";
                }
        } while (load_input != 1 && load_input != 2);
        return load_input;
}