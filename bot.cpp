#include "bot.hpp"
#include <iostream>

int ask_difficulty() {
        int difficulty {};
        std::cout << "Select bot difficulty:\n";
        std::cout << "1. Easy\n";
        std::cout << "2. Normal\n";
        std::cout << "3. Hard\n";
        std::cout << "Enter your choice: ";
        do {
                std::cin >> difficulty;
                if (difficulty < 1 || difficulty > 3) {
                        std::cout << "Invalid choice, try again: ";
                }
        } while (difficulty < 1 || difficulty > 3);
        return difficulty;
}

void init_bot(const int difficulty, std::vector<Player> &players) {
        players.push_back(Player {difficulty, "Bot", 0, 0, 0, false, false});
}