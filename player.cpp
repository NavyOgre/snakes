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

void player_move(std::vector<Player> &players, const int id, const int die_roll, const std::vector<Square> &board) {
        Player &player {players.at(id)};
        Player &rival {players.at(player.rival_id)};
        if (die_roll != 6) {
                player.bonus_turn = false;
        }
        if (player.position + die_roll > 99) {
                std::cout << "You can't move!\n\n";
        } else {
                player.position += die_roll;
                resolve_move(board, player);
                check_hit(player, rival);
        }
}

void check_hit(Player &player, Player &rival) {
        if (player.position == rival.position) {
                if (rival.shield) {
                        std::cout << rival.name << " lost their shield!\n\n";
                        rival.shield = false;
                } else {
                        std::cout << rival.name << " got hit by " << player.name << "!\n\n";
                        rival.position = 0;
                }
        }
}

void resolve_move(const std::vector<Square> &board, Player &player) {
        int &position {player.position};
        switch (board.at(position).type) {
                case 'c': {
                        player.coin += board.at(position).data;
                        std::cout << player.name << " moved to " << position + 1;
                        std::cout << " and got " << board.at(position).data << " coins!\n\n";
                        break;
                }
                case 'l': {
                        position += board.at(position).data;
                        std::cout << player.name << " moved up the ladder to " << position + 1 << "!\n\n";
                        break;
                }
                case 's': {
                        if (player.shield) {
                                player.shield = false;
                                std::cout << player.name << " moved to " << position + 1;
                                std::cout << " and used a shield to avoid getting hit by a snake!\n\n";
                        } else {
                                position += board.at(position).data;
                                std::cout << player.name << " got hit by a snake and fell to " << position + 1 << "!T_T\n\n";
                        }
                        break;
                }
                default: {
                        std::cout << player.name << " moved to " << position + 1 << ".\n\n";
                }
        }
}