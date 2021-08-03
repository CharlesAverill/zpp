//
// Created by Charles Averill on 7/27/21.
//

#ifndef ZPP_LINK_H
#define ZPP_LINK_H

#include <map>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Character.h"

using namespace sf;

class Link : public Character {
    void load_textures();
public:
    // Constructors
    Link();
    Link(Vector2f pos, std::string fac);

    bool is_walking;
    bool lock_movement;

    // Control
    void face(std::string new_facing);
    void update_sprite(int duration);
    std::vector<Vector2f> get_next_corners(std::string direction);
};


#endif //ZPP_LINK_H
