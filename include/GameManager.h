//
// Created by Charles Averill on 7/28/21.
//

#ifndef ZPP_GAMEMANAGER_H
#define ZPP_GAMEMANAGER_H

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Link.h"
#include "Map.h"
#include "GraphicsUtils.h"

using namespace sf;
using namespace std;

class GameManager {
    int WIDTH, HEIGHT;

    Clock global_clock;

    RenderWindow *window;
    View *view;

    string map_collection;
    Vector2i *map_index;
    Map *current_screen;

    Link *link;

    void input();
    bool check_collision(string direction);

    void screen_change(string direction);
    void load_screen();
public:
    GameManager();
    void init_window(int width, int height);
    void game_loop();
};


#endif //ZPP_GAMEMANAGER_H
