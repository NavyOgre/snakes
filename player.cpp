#include "player.hpp"
#include "shop.hpp"
#include "bot.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>

int ask_game_type(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, ALLEGRO_MOUSE_STATE &mouse_state) {
        while (true) {
                bool redraw {false}, get_game_type {false};
                al_wait_for_event(queue, &event);
                switch (event.type) {
                        case ALLEGRO_EVENT_TIMER: {
                                redraw = true;
                                break;
                        }
                        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
                                if (event.mouse.button == ALLEGRO_MOUSE_BUTTON_LEFT) {
                                        al_get_mouse_state(&mouse_state);
                                        get_game_type = true;
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
                if (get_game_type) {
                        if (mouse_state.x <= 370 && mouse_state.x >= 270 && mouse_state.y <= 232 && mouse_state.y >= 192) {
                                return 1;
                        } else if (mouse_state.x <= 370 && mouse_state.x >= 270 && mouse_state.y <= 292 && mouse_state.y >= 252) {
                                return 2;
                        }
                        get_game_type = false;
                }
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(151, 217, 252));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 100, ALLEGRO_ALIGN_CENTER, "Would you like to play against a bot or a human?");
                        al_draw_filled_rectangle(270, 192, 370, 232, al_map_rgb(38, 78, 99));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 200, ALLEGRO_ALIGN_CENTER, "Bot");
                        al_draw_filled_rectangle(270, 252, 370, 292, al_map_rgb(38, 78, 99));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 260, ALLEGRO_ALIGN_CENTER, "Human");
                        al_flip_display();
                        redraw = false;
                }
        }
}

void get_player_info(std::vector<Player> &players, const int p_number, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, bool &done) {
        std::string info_message {"Enter player " + std::to_string(p_number) + " name:"};
        int ascii_letter {abs('a' - ALLEGRO_KEY_A)};
        std::string name;
        while (true) {
                bool redraw {false}, get_player_name {false};
                al_wait_for_event(queue, &event);
                switch (event.type) {
                        case ALLEGRO_EVENT_TIMER: {
                                redraw = true;
                                break;
                        }
                        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                                done = true;
                                return;
                        }
                        case ALLEGRO_EVENT_KEY_DOWN: {
                                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                        done = true;
                                        return;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        get_player_name = true;
                                } else if (event.keyboard.keycode >= ALLEGRO_KEY_A || event.keyboard.keycode <= ALLEGRO_KEY_Z) {
                                        name += static_cast<char>(event.keyboard.keycode + ascii_letter);
                                }
                        }
                }
                if (get_player_name) {
                        players.push_back(Player {0, name, p_number % 2, 0, 0, false, false});
                        break;
                }
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(151, 217, 252));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 100, ALLEGRO_ALIGN_CENTER, info_message.c_str());
                        al_draw_multiline_text(font, al_map_rgb(0, 0, 0), 320, 120, 30, 5, ALLEGRO_ALIGN_CENTER, name.c_str());
                        al_flip_display();
                        redraw = false;
                }
        }
}

void run_game(std::vector<Player> &players, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, bool &done, std::string &winner) {
        int turn {0};
        ALLEGRO_BITMAP *map {al_load_bitmap("./assets/board.jpg")};
        int current_player {};
        bool waiting_move {true}, waiting_shop {false};
        ALLEGRO_COLOR player1_color {al_map_rgb(255, 0, 0)}, player2_color {al_map_rgb(0, 0, 255)}, black {al_map_rgb(0, 0, 0)};
        int p1_x {}, p1_y {}, p2_x {}, p2_y {};
        int die_roll {};
        while (true) {
                current_player = turn % 2;
                bool redraw {false}, get_move {false}, get_shop {false};
                int command {0};
                if (players[current_player].bot) {
                        die_roll = roll(6);
                        command = easy_shop(players[current_player], die_roll);
                        shop_action(players[current_player], die_roll, command);
                        if (!players[current_player].bonus_turn) {
                                ++turn;
                        }
                        player_move(players, current_player, die_roll);
                        if (players[current_player].position == 99) {
                                winner = players[current_player].name;
                                break;
                        }
                        continue;
                }
                al_wait_for_event(queue, &event);
                switch (event.type) {
                        case ALLEGRO_EVENT_TIMER: {
                                redraw = true;
                                break;
                        }
                        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                                done = true;
                                return;
                        }
                        case ALLEGRO_EVENT_KEY_DOWN: {
                                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                        done = true;
                                        return;
                                }
                                switch (event.keyboard.keycode) {
                                        case ALLEGRO_KEY_0: {
                                                command = 0;
                                                break;
                                        }
                                        case ALLEGRO_KEY_1: {
                                                command = 1;
                                                break;
                                        }
                                        case ALLEGRO_KEY_2: {
                                                command = 2;
                                                break;
                                        }
                                        case ALLEGRO_KEY_3: {
                                                command = 3;
                                                break;
                                        }
                                        case ALLEGRO_KEY_4: {
                                                command = 4;
                                        }
                                }
                                if (waiting_move) {
                                        get_move = true;
                                } else if (waiting_shop) {
                                        get_shop = true;
                                }
                        }
                }
                std::string player1_info, player2_info;
                player1_info = players[0].name + "  shield: " + std::to_string(players[0].shield) + "  coins: " + std::to_string(players[0].coin);
                player2_info = players[1].name + "  shield: " + std::to_string(players[1].shield) + "  coins: " + std::to_string(players[1].coin);
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(151, 217, 252));
                        al_draw_bitmap(map, 0, 0, 0);
                        al_draw_text(font, black, 0, 650, 0, player1_info.c_str());
                        al_draw_text(font, black, 0, 670, 0, player2_info.c_str());
                        find_position(p1_x, p1_y, players[0].position);
                        find_position(p2_x, p2_y, players[1].position);
                        al_draw_filled_circle(p1_x, p1_y, 10, player1_color);
                        al_draw_filled_circle(p2_x, p2_y + 25, 10, player2_color);
                        if (waiting_move && !(players[current_player].bot)) {
                                std::string turn_announce;
                                turn_announce = "It is your turn " + players[current_player].name + "\n1. Roll\n2. Save";
                                al_draw_multiline_text(font, black, 700, 0, 100, 20, ALLEGRO_ALIGN_LEFT, turn_announce.c_str());
                        } else if (waiting_shop && !players[current_player].bot) {
                                std::string shop_announce;
                                shop_announce = "Would you like to buy from the shop?\n0. continue\n1. -1 from roll(1c)\n2. +1 to roll(2c)\n3. reroll(3c)\n4. buy shield(4c)";
                                std::string roll_announce;
                                roll_announce = "You rolled " + std::to_string(die_roll);
                                al_draw_multiline_text(font, black, 700, 0, 100, 20, ALLEGRO_ALIGN_LEFT, shop_announce.c_str());
                                al_draw_text(font, black, 700, 180, 0, roll_announce.c_str());
                        }
                        al_flip_display();
                        redraw = false;
                } else if (get_move && (command == 1 || command == 2)) {
                        if (command == 1) {
                                die_roll = roll(6);
                                if (die_roll == 6) {
                                        players[current_player].bonus_turn = true;
                                } else {
                                        players[current_player].bonus_turn = false;
                                }
                                waiting_move = false;
                                waiting_shop = true;
                                get_move = false;
                        } else {
                                save_game(turn, players);
                                get_move = false;
                        }
                } else if (get_shop && (command >= 0 && command <= 4)) {
                        if (valid_shop(players[current_player].coin, command, die_roll, players[current_player].shield)) {
                                shop_action(players[current_player], die_roll, command);
                                player_move(players, current_player, die_roll);
                                if (!players[current_player].bonus_turn) {
                                        ++turn;
                                }
                                waiting_shop = false;
                                waiting_move = true;
                        }
                        if (players[current_player].position == 99) {
                                winner = players[current_player].name;
                                break;
                        }
                        get_shop = false;
                }
        }
        al_destroy_bitmap(map);
}

void announce_winner(ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_TIMER *timer, ALLEGRO_EVENT &event, const std::string &winner, bool &done) {
        std::string final_message;
        final_message = winner + " won the game!! Press enter to return to main menu.";
        while (true) {
                bool redraw {false};
                al_wait_for_event(queue, &event);
                switch (event.type) {
                        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                                done = true;
                                return;
                        }
                        case ALLEGRO_EVENT_KEY_DOWN: {
                                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                                        done = true;
                                        return;
                                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                                        return;
                                }
                                break;
                        }
                        case ALLEGRO_EVENT_TIMER: {
                                redraw = true;
                        }
                }
                if (redraw && al_is_event_queue_empty(queue)) {
                        al_clear_to_color(al_map_rgb(151, 217, 252));
                        al_draw_text(font, al_map_rgb(0, 0, 0), 320, 100, ALLEGRO_ALIGN_CENTER, final_message.c_str());
                        al_flip_display();
                        redraw = false;
                }
        }
}

void find_position(int &px, int &py, const int position) {
        py = 17 + 61 * (9 - position / 10);
        if ((position / 10) % 2 == 1) {
                px = 17 + 61 * (9 - position % 10);
        } else {
                px = 17 + 61 * (position % 10);
        }
}

bool valid_shop(const int coin, const int command, const int die_roll, const bool shield) {
        switch (command) {
                case 1: {
                        if (coin < 1) {
                                return false;
                        }
                        if (die_roll == 1) {
                                return false;
                        }
                        break;
                }
                case 2: {
                        if (coin < 2) {
                                return false;
                        }
                        if (die_roll == 6) {
                                return false;
                        }
                        break;
                }
                case 3: {
                        if (coin < 3) {
                                return false;
                        }
                        break;
                }
                case 4: {
                        if (coin < 4) {
                                return false;
                        }
                        if (shield) {
                                return false;
                        }
                }
        }
        return true;
}

int roll(const int n) {
        return rand() % n + 1;
}

void player_move(std::vector<Player> &players, const int id, const int die_roll) {
        Player &player {players.at(id)};
        Player &rival {players.at(player.rival_id)};
        if (die_roll != 6) {
                player.bonus_turn = false;
        }
        if (!(player.position + die_roll > 99)) {
                player.position += die_roll;
                resolve_move(player);
                check_hit(player, rival);
        }
}

void check_hit(Player &player, Player &rival) {
        if (player.position == rival.position) {
                if (rival.shield) {
                        rival.shield = false;
                } else {
                        rival.position = 0;
                }
        }
}

void resolve_move(Player &player) {
        int &position {player.position};
        switch (board.at(position).type) {
                case 'c': {
                        player.coin += board.at(position).data;
                        break;
                }
                case 'l': {
                        position += board.at(position).data;
                        break;
                }
                case 's': {
                        if (player.shield) {
                                player.shield = false;
                        } else {
                                position += board.at(position).data;
                        }
                        break;
                }
        }
}

bool load_game(int &turn, std::vector<Player> &players) {
        std::ifstream in_file {"./save.txt"};
        if (!in_file) {
                return false;
        }
        in_file >> turn;
        std::string line;
        for (int i {0}; i < 2; ++i) {
                Player player;
                in_file >> player.bot;
                std::getline(in_file, line);
                std::getline(in_file, line);
                player.name = line;
                in_file >> player.rival_id >> player.position >> player.coin;
                in_file >> player.shield >> player.bonus_turn;
                players.push_back(player);
        }
        in_file.close();
        return true;
}

void save_game(const int turn, const std::vector<Player> &players) {
        std::ofstream out_file("save.txt", std::ios::trunc);
        out_file << turn << "\n";
        for (int i {}; i < 2; ++i) {
                out_file << players.at(i).bot << "\n";
                out_file << players.at(i).name << "\n";
                out_file << players.at(i).rival_id << " " << players.at(i).position << " " << players.at(i).coin << "\n";
                out_file << players.at(i).shield << " " << players.at(i).bonus_turn << "\n";
        }
        out_file.close();
}