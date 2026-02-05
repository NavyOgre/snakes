#include <cstdlib>
#include "board.hpp"
#include "player.hpp"
#include "shop.hpp"
#include "bot.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main(int argc, char **argv) {
        srand(time(NULL));
        al_init();
        al_init_font_addon();
        al_init_ttf_addon();
        al_install_mouse();
        al_install_keyboard();
        ALLEGRO_DISPLAY *display {al_create_display(640, 480)};
        ALLEGRO_TIMER *timer {al_create_timer(1.0 / 30.0)};
        ALLEGRO_EVENT_QUEUE *queue {al_create_event_queue()};
        ALLEGRO_FONT *font {al_load_ttf_font("assets/font.ttf", 12, 0)};
        al_register_event_source(queue, al_get_timer_event_source(timer));
        al_register_event_source(queue, al_get_display_event_source(display));
        al_register_event_source(queue, al_get_keyboard_event_source());
        ALLEGRO_EVENT event;
        al_start_timer(timer);
        bool redraw {true};
        while (true) {
                al_wait_for_event(queue, &event);
                if (event.type == ALLEGRO_EVENT_TIMER) {
                        redraw = true;
                } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                        break;
                }
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(0, 0, 0));
                        al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "New game");
                        al_flip_display();
                        redraw = false;
                }
        }
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_event_queue(queue);
        al_destroy_font(font);
}