#include "player.hpp"
#include <cstdlib>
#include <iostream>

int roll_die() {
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
                players.push_back(Player {0, name, (i + 1) % 2, 0, 0, false, false});
        }
        if (game_type == 1) {
                std::cout << "Select bot difficulty\n";
                std::cout << "1. Braindead\n";
                std::cout << "2. Normal\n";
                std::cout << "Enter your choice: ";
                int difficulty {};
                do {
                        std::cin >> difficulty;
                        if (difficulty != 1 && difficulty != 2) {
                                std::cout << "Invalid choice, try again: ";
                        }
                } while (difficulty != 1 && difficulty != 2);
                players.push_back(Player {difficulty, "Bot", 0, 0, 0, false, false});
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

int turn_anounce(const int id, const std::vector<Player> &players) {
        int roll {roll_die()};
        std::cout << "It is your turn, " << players.at(id).name << ".\n";
        std::cout << "square: " << players.at(id).position + 1 << "\n";
        std::cout << "roll: " << roll << "\n";
        std::cout << "coins: " << players.at(id).coin << "\n";
        std::cout << "rival square: " << players.at(players.at(id).rival_id).position + 1 << "\n";
        return roll;
}

void player_move(const int id, std::vector<Player> &players, int &roll, std::string &winner, const std::vector<Square> &board) {
        if (roll == 6) {
                players.at(id).bonus_turn = true;
        }
        std::cout << "Would you like to buy anything from the shop?\n";
        std::cout << "0. continue\n";
        std::cout << "1. roll - 1(1 coin)\n";
        std::cout << "2. roll + 1(2 coins)\n";
        std::cout << "3. reroll(3 coins)\n";
        std::cout << "4. buy shield(4 coins)\n";
        std::cout << "Enter you choice: ";
        int choice {};
        do {
                std::cin >> choice;
                if (choice < 0 || choice > 4) {
                        std::cout << "Invalid choice, try again: ";
                        continue;
                }
                shop_action(players.at(id), choice, roll);
        } while (choice < 0 || choice > 4);
        int &position {players.at(id).position};
        if (position + roll > 99) {
                std::cout << "You can't move.\n";
        } else {
                position += roll;
                resolve_move(id, players, roll, board);
                if (position == 99) {
                        winner = players.at(id).name;
                }
        }
}

void shop_action(Player &player, int &choice, int &roll) {
        switch (choice) {
                case 1: {
                        if (player.coin < 1) {
                                std::cout << "You don't have enough coins to subtract 1 from your roll, try again: ";
                                choice = -1;
                        } else if (roll == 1) {
                                std::cout << "You can't roll any lower than 1, try again: ";
                                choice = -1;
                        } else {
                                roll_subtract1(player, roll);
                        }
                        break;
                }
                case 2: {
                        if (player.coin < 2) {
                                std::cout << "You don't have enough coins to add 1 to your roll, try again: ";
                                choice = -1;
                        } else if (roll == 6) {
                                std::cout << "You can't roll any higher than 6, try again: ";
                                choice = -1;
                        } else {
                                roll_plus1(player, roll);
                        }
                        break;
                }
                case 3: {
                        if (player.coin < 3) {
                                std::cout << "You don't have enough coins to reroll, try again: ";
                                choice = -1;
                        } else {
                                reroll(player, roll);
                                std::cout << "New roll: " << roll << "\n";
                        }
                        break;
                }
                case 4: {
                        if (player.shield == true) {
                                std::cout << "You already have a shield, try again: ";
                                choice = -1;
                        } else if (player.coin < 4) {
                                std::cout << "You don't have enough coins to buy a shield, try again: ";
                                choice = -1;
                        } else {
                                buy_shield(player);
                        }
                        break;
                }
                default: {}
        }
}

void resolve_move(const int id, std::vector<Player> &players, const int roll, const std::vector<Square> &board) {
        int &position {players.at(id).position};
        int &rival_position {players.at(players.at(id).rival_id).position};
        bool &rival_shield {players.at(players.at(id).rival_id).shield};
        std::string rival_name {players.at(players.at(id).rival_id).name};
        switch (board.at(position).type) {
                case 'c': {
                        players.at(id).coin += board.at(position).data;
                        break;
                }
                case 'l': {
                        position += board.at(position).data;
                        break;
                }
                case 's': {
                        if (players.at(id).shield) {
                                players.at(id).shield = false;
                        } else {
                                position += board.at(position).data;
                        }
                        break;
                }
                default: {}
        }
        if (position == rival_position) {
                if (rival_shield) {
                        rival_shield = false;
                } else {
                        std::cout << rival_name << " got hit by " << players.at(id).name << "!\n";
                        rival_position = 0;
                }
        }
}

void reroll(Player &player, int &roll) {
        roll = roll_die();
        player.coin -= 3;
        if (roll == 6) {
                player.bonus_turn = true;
        } else {
                player.bonus_turn = false;
        }
}

void roll_plus1(Player &player, int &roll) {
        ++roll;
        player.coin -= 2;
}

void roll_subtract1(Player &player, int &roll) {
        --roll;
        player.coin -= 1;
        player.bonus_turn = false;
}

void buy_shield(Player &player) {
        player.shield = true;
        player.coin -= 4;
}