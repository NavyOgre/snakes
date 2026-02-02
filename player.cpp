#include "player.hpp"
#include <iostream>

void get_player_info(std::vector<Player> &players, int players_cnt) {
        std::string name;
        for (int i {0}; i < players_cnt; ++i) {
                std::cout << "Enter player " << i + 1 << " name: ";
                std::cin >> name;
                players.push_back(Player {0, name, i, (i + 1) % 2, 0, 0, false, false});
        }
}