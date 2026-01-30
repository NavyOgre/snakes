#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include <vector>
#include <string>

struct Square {
        char type;
        int data;
};

int intro();
void init_board(std::vector<Square> &board);
void display_board(const std::vector<Square> &board);

// helper functions for display_board
std::string display_handle_case(const Square &square, int position);
int display_find_position(const int i, const int j);

#endif