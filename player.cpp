#include "player.hpp"
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
                                al_get_mouse_state(&mouse_state);
                                get_game_type = true;
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



void turn_announce(const std::vector<Player> &players, const int id) {
        Player player {players.at(id)};
        std::cout << "It is your turn " << player.name << ".\n";
        std::cout << "Square: " << player.position + 1 << "\n";
        std::cout << "Coin: " << player.coin << "\n";
        std::cout << "Shield: " << player.shield << "\n";
        std::cout << "Rival square: " << players.at(player.rival_id).position + 1 << "\n\n";
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
        if (player.position + die_roll > 99) {
                std::cout << player.name << " can't move!\n\n";
        } else {
                player.position += die_roll;
                resolve_move(player);
                check_hit(player, rival);
        }
}

void check_hit(Player &player, Player &rival) {
        if (player.position == rival.position) {
                if (rival.shield) {
                        std::cout << rival.name << " lost a shield while defending against " << player.name << "!\n\n";
                        rival.shield = false;
                } else {
                        std::cout << rival.name << " got hit by " << player.name << "!\n\n";
                        rival.position = 0;
                }
        }
}

void resolve_move(Player &player) {
        int &position {player.position};
        switch (board.at(position).type) {
                case 'c': {
                        player.coin += board.at(position).data;
                        std::cout << player.name << " moved to " << position + 1;
                        std::cout << " and got " << board.at(position).data << " coins!\n\n";
                        break;
                }
                case 'l': {
                        position += board.at(position).data;
                        std::cout << player.name << " moved up the ladder to " << position + 1 << "!\n\n";
                        break;
                }
                case 's': {
                        if (player.shield) {
                                player.shield = false;
                                std::cout << player.name << " moved to " << position + 1;
                                std::cout << " and used a shield to avoid getting bitten by a snake!\n\n";
                        } else {
                                position += board.at(position).data;
                                std::cout << player.name << " got bitten by a snake and fell to " << position + 1 << "!T_T\n\n";
                        }
                        break;
                }
                default: {
                        std::cout << player.name << " moved to " << position + 1 << ".\n\n";
                }
        }
}

bool load_game(int &turn, int &total_turns, std::vector<Player> &players) {
        std::ifstream in_file {"./save.txt"};
        if (!in_file) {
                return false;
        }
        in_file >> turn >> total_turns;
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

int turn_action(const int turn, const int total_turns, const std::vector<Player> &players) {
        std::cout << "1. Roll die\n";
        std::cout << "2. Save game\n";
        std::cout << "3. Exit game\n";
        std::cout << "Choose an option: ";
        int action {};
        do {
                std::cin >> action;
                if (action < 1 || action > 3) {
                        std::cout << "Invalid choice, try again: ";
                        continue;
                } else if (action == 2) {
                        save_game(turn, total_turns, players);
                        std::cout << "Game saved!\n";
                        std::cout << "Choose another option: ";
                }
        } while (action != 1 && action != 3);
        return action;
}

void save_game(const int turn, const int total_turns, const std::vector<Player> &players) {
        std::ofstream out_file("save.txt", std::ios::trunc);
        out_file << turn << " " << total_turns << "\n";
        for (int i {}; i < 2; ++i) {
                out_file << players.at(i).bot << "\n";
                out_file << players.at(i).name << "\n";
                out_file << players.at(i).rival_id << " " << players.at(i).position << " " << players.at(i).coin << "\n";
                out_file << players.at(i).shield << " " << players.at(i).bonus_turn << "\n";
        }
        out_file.close();
}