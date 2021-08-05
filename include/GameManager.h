//
// Created by Charles Averill on 7/28/21.
//

#ifndef ZPP_GAMEMANAGER_H
#define ZPP_GAMEMANAGER_H

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "world/Map.h"

#include "HUD.h"
#include "Utils.h"

#include "characters/Character.h"
#include "characters/Link.h"

using namespace sf;
using namespace std;

class GameManager {
    int WIDTH, HEIGHT;

    Clock global_clock;

    RenderWindow *window;
    View *view;

    HUD *hud;

    string map_collection;
    bool is_underground;
    Vector2i *map_index;
    vector<Character *> current_characters;
    Map *current_screen;

    Link *link;
    string held_direction;
    int held_duration;

    int input();
    int check_collision(string direction);

    void screen_change(string direction);
    void load_screen(bool switch_underground);
public:
    GameManager();
    void init_window(int width, int height);
    void game_loop();

    Map *get_current_screen();
    RenderWindow *get_render_window();
};


#endif //ZPP_GAMEMANAGER_H
