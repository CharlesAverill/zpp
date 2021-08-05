//
// Created by Charles Averill on 8/5/21.
//

#ifndef ZPP_HUD_H
#define ZPP_HUD_H

#include <map>

#include <SFML/Graphics/RenderWindow.hpp>

#include "characters/Link.h"

using namespace std;


class HUD {
    Sprite standard_overlay;

    Sprite empty_heart;
    Sprite half_heart;
    Sprite full_heart;

    vector<Texture> textures;

    void load_textures();
public:
    HUD();
    void draw_hud(RenderWindow *window, Link *link);
};


#endif //ZPP_HUD_H
