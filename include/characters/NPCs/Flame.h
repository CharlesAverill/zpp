//
// Created by Charles Averill on 8/2/21.
//

#ifndef ZPP_FLAME_H
#define ZPP_FLAME_H


#include "characters/Character.h"


class Flame : public Character {
    void load_textures();
    bool flip_texture;
public:
    Flame(tmx::Vector2f pos);
    void update_sprite(int duration);
};


#endif //ZPP_FLAME_H
