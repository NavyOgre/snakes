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
                                if (event.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) {
                                        al_get_mouse_state(&mouse_state);
                                        get_load_action = true;
                                }
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
                if (get_load_action) {
                        if (mouse_state.x <= 370 && mouse_state.x >= 270 && mouse_state.y <= 232 && mouse_state.y >= 192) {
                                return 1;
                        } else if (mouse_state.x <= 370 && mouse_state.x >= 270 && mouse_state.y <= 292 && mouse_state.y >= 252) {
                                return 2;
                        }
                        get_load_action = false;
                }
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(151, 217, 252));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 100, ALLEGRO_ALIGN_CENTER, "Welcome to my snakes and ladders game!");
                        al_draw_filled_rectangle(270, 192, 370, 232, al_map_rgb(38, 78, 99));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 200, ALLEGRO_ALIGN_CENTER, "New game");
                        al_draw_filled_rectangle(270, 252, 370, 292, al_map_rgb(38, 78, 99));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 260, ALLEGRO_ALIGN_CENTER, "Load game");
                        al_flip_display();
                        redraw = false;
                }
                
        }
}

