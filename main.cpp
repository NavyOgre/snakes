#include <cstdlib>
#include "board.hpp"
#include "player.hpp"
#include "shop.hpp"
#include "bot.hpp"
#include <iostream> // for testing

int main(int argc, char **argv) {
        srand(time(NULL));
        al_init();
        al_init_font_addon();
        al_init_ttf_addon();
        al_init_primitives_addon();
        al_install_mouse();
        al_install_keyboard();
        ALLEGRO_DISPLAY *display {al_create_display(640, 480)};
        ALLEGRO_TIMER *timer {al_create_timer(1.0 / 30.0)};
        ALLEGRO_EVENT_QUEUE *queue {al_create_event_queue()};
        ALLEGRO_FONT *font {al_load_ttf_font("assets/font.ttf", 12, 0)};
        al_register_event_source(queue, al_get_timer_event_source(timer));
        al_register_event_source(queue, al_get_display_event_source(display));
        al_register_event_source(queue, al_get_keyboard_event_source());
        al_register_event_source(queue, al_get_mouse_event_source());
        ALLEGRO_EVENT event;
        ALLEGRO_MOUSE_STATE mouse_state;
        al_start_timer(timer);
        bool done {false};
        while (!done) {
                bool game_initialized {false};
                int turn {0}, total_turns {0};
                std::vector<Player> players;
                int load_action = run_main_menu(font, queue, timer, event, mouse_state);
                if (!load_action) {
                        break;
                }
                if (load_action == 1) {
                        // new game
                } else {
                        game_initialized = load_game(turn, total_turns, players);
                }
                if (game_initialized) {
                        // game start
                } else {
                        // load fail message
                }
        }
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
        al_destroy_font(font);
}