#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

struct Square {
        char type;
        int data;
};

const std::vector<Square> board = {
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

int run_main_menu(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, ALLEGRO_MOUSE_STATE &mouse_state);
void display_board();

// helper functions for display_board
int find_position(int i, int j);
std::string display_handle_case(const Square &square, const int position);
// helper functions for display_board

int ask_game_type();

#endif