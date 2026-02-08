#include "board.hpp"
#include <iostream>
#include <iomanip>

int run_main_menu(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, ALLEGRO_MOUSE_STATE &mouse_state) {
        while (true) {
                bool redraw {false}, get_load_action {false};
                al_wait_for_event(queue, &event);
                switch (event.type) {
                        case ALLEGRO_EVENT_TIMER: {
                                redraw = true;
                                break;
                        }
                        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                al_get_mouse_state(&mouse_state);
                                get_load_action = true;
                                break;
                        }
                        case ALLEGRO_EVENT_KEY_DOWN: {
                                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                        return 0;
                                }
                                break;
                        }
                        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                                return 0;
                        }
                }
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(151, 217, 252));
                        al_draw_filled_rectangle(462, 276, 562, 316, al_map_rgb(38, 78, 99));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 512, 284, ALLEGRO_ALIGN_CENTER, "New game");
                        al_draw_filled_rectangle(462, 406, 562, 446, al_map_rgb(38, 78, 99));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 512, 414, ALLEGRO_ALIGN_CENTER, "Load game");
                        al_flip_display();
                        redraw = false;
                }
                if (get_load_action) {
                        if (mouse_state.x <= 562 && mouse_state.x >= 462 && mouse_state.y <= 316 && mouse_state.y >= 276) {
                                return 1;
                        } else if (mouse_state.x <= 562 && mouse_state.x >= 462 && mouse_state.y <= 446 && mouse_state.y >= 406) {
                                return 2;
                        }
                        get_load_action = false;
                }
        }
}

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

void display_board() {
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