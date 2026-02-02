#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include <vector>
#include <string>

struct Square {
        char type;
        int data;
};

int ask_loading();
void init_board(std::vector<Square> &board);
void display_board(const std::vector<Square> &board);

// helper functions for display_board
int find_position(int i, int j);
std::string display_handle_case(const Square &square, const int position);
// helper functions for display_board

int ask_game_type();

#endif