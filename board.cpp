#include "board.hpp"
#include <iostream>
#include <iomanip>

int intro() {
        std::cout << "Welcome! Thank you for trying my snakes and ladders game.\n";
        std::cout << "=========================================================\n\n\n";
        std::cout << "Would you like to start a new game or load a previous game?\n";
        std::cout << "1. New game\n";
        std::cout << "2. Load previous game\n";
        std::cout << "Enter your choice: ";
        int input {};
        do {
                std::cin >> input;
                if (input != 1 && input != 2) {
                        std::cout << "Invalid input, try again: ";
                }
        } while (input != 1 && input != 2);
        return input;
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
        for (int i {9}; i >= 0; --i) {
                for (int j {0}; j < 10; ++j) {
                        int position {display_find_position(i, j)};
                        std::string output = display_handle_case(board.at(position), position);
                        std::cout << std::setw(10) << std::left << output;
                }
                std::cout << "\n\n";
        }
}

int display_find_position(const int i, const int j) {
        switch (i % 2) {
                case 0: {
                        return 10 * i + j;

                }
                default: {
                        return 10 * i + 9 - j;
                }
        }
}

std::string display_handle_case(const Square &square, int position) {
        std::string output {std::to_string(position + 1)};
        switch(square.type) {
                case 'l':
                case 's': {
                        output += square.type;
                        output += "->" + std::to_string(position + 1 + square.data);
                        break;
                }
                case 'c': {
                        output += square.type;
                        output += "=" + std::to_string(square.data);
                        break;
                }
                default: {
                }
        }
        return output;
}