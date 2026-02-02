#include "board.hpp"
#include <iostream>
#include <iomanip>

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
        std::cout << "\n\n";
        return load_input;
}

void init_board(std::vector<Square> &board) {
        board = {
        {'n', 0}, {'n', 0}, {'c', 4}, {'l', 10}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 6}, {'l', 22}, {'n', 0},
        {'n', 0}, {'n', 0}, {'c', 4}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -10}, {'n', 0}, {'n', 0}, {'c', 3},
        {'l', 21}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 4}, {'n', 0}, {'n', 0}, {'l', 56}, {'c', 2}, {'n', 0},
        {'n', 0}, {'c', 4}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 3}, {'n', 0}, {'n', 0}, {'n', 0},
        {'c', 4}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 2}, {'n', 0},
        {'l', 16}, {'n', 0}, {'n', 0}, {'s', -20}, {'n', 0}, {'n', 0}, {'c', 6}, {'n', 0}, {'n', 0}, {'n', 0},
        {'n', 0}, {'s', -43}, {'n', 0}, {'s', -4}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 4},
        {'l', 20}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 6}, {'n', 0}, {'l', 19},
        {'n', 0}, {'n', 0}, {'c', 2}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -63}, {'n', 0}, {'n', 0}, {'n', 0},
        {'n', 0}, {'n', 0}, {'s', -20}, {'n', 0}, {'s', -20}, {'n', 0}, {'n', 0}, {'s', -19}, {'n', 0}, {'n', 0}
        };
}

void display_board(const std::vector<Square> &board) {
        int position {};
        for (int i {9}; i >= 0; --i) {
                for (int j {9}; j >= 0; --j) {
                        position = find_position(i, j);
                        std::string square_info {display_handle_case(board.at(position), position)};
                        std::cout << std::setw(10) << std::left << square_info;
                }
                std::cout << "\n\n";
        }
}

int find_position(const int i, const int j) {
        if (i % 2) {
                return i * 10 + j;
        } else {
                return i * 10 + 9 - j;
        }
}

std::string display_handle_case(const Square &square, const int position) {
        std::string output;
        switch (square.type) {
                case 'c': {
                        output += std::to_string(position + 1) + "c=" + std::to_string(square.data);
                        break;
                }
                case 's':
                case 'l': {
                        output += std::to_string(position + 1) + square.type + "->" + std::to_string(position + square.data + 1);
                        break;
                }
                default: {
                        output += std::to_string(position + 1);
                }
        }
        return output;
}

int ask_game_type() {
        int game_type {};
        std::cout << "Would you like to play against a bot or another human?\n";
        std::cout << "1. Bot\n";
        std::cout << "2. Human\n";
        std::cout << "Enter your choice: ";
        do {
                std::cin >> game_type;
                if (game_type != 1 && game_type != 2) {
                        std::cout << "Invalid choice, try again: ";
                }
        } while (game_type != 1 && game_type != 2);
        std::cout << "\n\n";
        return game_type;
}