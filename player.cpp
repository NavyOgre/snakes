#include "player.hpp"
#include <iostream>
#include <cstdlib>

void get_player_info(std::vector<Player> &players, int players_cnt) {
        std::string name;
        for (int i {0}; i < players_cnt; ++i) {
                std::cout << "Enter player " << i + 1 << " name: ";
                std::cin >> name;
                players.push_back(Player {0, name, i, (i + 1) % 2, 0, 0, false, false});
        }
}

void turn_announce(const std::vector<Player> &players, const int id, const int die_roll, const std::vector<Square> &board) {
        Player player {players.at(id)};
        std::cout << "It is your turn " << player.name << ".\n";
        std::cout << "Roll: " << die_roll << "\n";
        std::cout << "Square: " << player.position + 1 << "\n";
        std::cout << "Coin: " << player.coin << "\n";
        std::cout << "Shield: " << player.shield << "\n";
        std::cout << "Rival square: " << players.at(player.rival_id).position + 1 << "\n\n";
}

int roll(const int n) {
        return rand() % n + 1;
}