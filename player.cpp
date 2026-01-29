#include "player.hpp"
#include <cstdlib>
#include <iostream>

int roll_die() {
        srand(time(0));
        return rand() % 6 + 1;
}

void init_game(const int load_action, std::vector<Player> &players) {
        switch (load_action) {
                case 2: {
                        // initialize from file
                }
                default: {
                        int game_type {resolve_game_type()};
                        init_players_new(game_type, players);
                }
        }
}

void init_players_new(const int game_type, std::vector<Player> &players) {
        std::string name;
        for (int i {0}; i < game_type; ++i) {
                std::cout << "Enter player name: ";
                std::cin >> name;
                // is_bot name rival_id position coin shield bonus_turn
                players.push_back(Player {false, name, (i + 1) % 2, 0, 0, false, false});
        }
        if (game_type == 1) {
                players.push_back(Player {true, "Bot", 0, 0, 0, false, false});
        }
}


int resolve_game_type() {
        int game_type {};
        std::cout << "Do you want to play against a bot or another human?\n";
        std::cout << "1. Bot\n";
        std::cout << "2. Human\n";
        std::cout << "Enter your choice: ";
        do {
                std::cin >> game_type;
                if (game_type != 1 && game_type != 2) {
                        std::cout << "Invalid choice, try again: ";
                }
        } while (game_type != 1 && game_type != 2);
        return game_type;
}