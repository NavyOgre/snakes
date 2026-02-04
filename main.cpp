#include <iostream>
#include <cstdlib>
#include "board.hpp"
#include "player.hpp"
#include "shop.hpp"
#include "bot.hpp"

int main() {
        std::cout << "Hello and welcome to my snakes and ladders game!\n";
        std::cout << "================================================\n\n\n";
        srand(time(0));
        std::vector<Player> players;
        int turn {0}, total_turns {0}, load_action {};
        bool initialized {false};
        std::cout << "Would you like to start a new game or load the previous one?\n";
        std::cout << "1. New game\n";
        std::cout << "2. Load game\n";
        std::cout << "Enter your choice: ";
        do {
                std::cin >> load_action;
                if (load_action != 1 && load_action != 2) {
                        std::cout << "Invalid choice, try again: ";
                        continue;
                }
                if (load_action == 1) {
                        int game_type {ask_game_type()};
                        get_player_info(players, game_type);
                        if (game_type == 1) {
                                int difficulty {ask_difficulty()};
                                init_bot(difficulty, players);
                        }
                        initialized = true;
                } else {
                        initialized = load_game(turn, total_turns, players);
                        if (!initialized) {
                                std::cout << "Couldn't load the game, choose another option: ";
                        }
                }
        } while (!initialized);
        std::string winner;
        std::cout << std::boolalpha;
        while (winner.empty()) {
                int current_player {turn % 2};
                int die_roll {};
                int shop_selection {0};
                if (!players.at(current_player).bot) {
                        display_board();
                        turn_announce(players, current_player);
                        int action {turn_action(turn, total_turns, players)};
                        if (action == 1) {
                                die_roll = roll(6);
                                std::cout << "\nRoll: " << die_roll << "\n";
                                players.at(current_player).bonus_turn = die_roll == 6 ? true : false;
                                ++total_turns;
                        } else {
                                break;
                        }
                        if (players.at(current_player).coin > 0) {
                                shop_selection = get_shop_choice(players.at(current_player), die_roll);
                        }
                } else {
                        die_roll = roll(6);
                        std::cout << "\nBot rolled: " << die_roll << "\n";
                        ++total_turns;
                        players.at(current_player).bonus_turn = die_roll == 6 ? true : false;
                        switch (players.at(current_player).bot) {
                                case 1: {
                                        shop_selection = easy_shop(players.at(current_player), die_roll);
                                        break;
                                }
                                case 2: {
                                        // normal shop
                                        break;
                                }
                                case 3: {
                                        // hard shop
                                }
                        }
                }
                shop_action(players.at(current_player), die_roll, shop_selection);
                player_move(players, current_player, die_roll);
                if (players.at(current_player).position == 99) {
                        winner = players.at(current_player).name;
                }
                if (!players.at(current_player).bonus_turn) {
                        ++turn;
                }
        }
        if (!winner.empty()) {
                std::cout << "\n\n" << winner << " won the game in " << total_turns << " turns!\n";
        }
}