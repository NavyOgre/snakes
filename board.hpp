#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

struct Square {
        char type;
        int data;
};

const std::vector<Square> board = {
{'n', 0}, {'n', 0}, {'n', 0}, {'l', 21}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 6}, {'n', 0}, {'n', 0},
{'n', 0}, {'n', 0}, {'l', 33}, {'c', 5}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 6},
{'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -22}, {'n', 0}, {'c', 6}, {'n', 0},
{'n', 0}, {'n', 0}, {'l', 16}, {'n', 0}, {'n', 0}, {'c', 7}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -37},
{'n', 0}, {'l', 21}, {'s', -25}, {'c', 2}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'l', 19},
{'n', 0}, {'n', 0}, {'n', 0}, {'s', -23}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 6},
{'n', 0}, {'l', 19}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -21}, {'c', 2}, {'n', 0}, {'n', 0}, {'n', 0},
{'n', 0}, {'n', 0}, {'c', 5}, {'l', 18}, {'n', 0}, {'s', -31}, {'n', 0}, {'c', 6}, {'n', 0}, {'n', 0},
{'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'c', 4}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -36}, {'n', 0},
{'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'n', 0}, {'s', -58}, {'n', 0}
};

int run_main_menu(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, ALLEGRO_MOUSE_STATE &mouse_state);

#endif