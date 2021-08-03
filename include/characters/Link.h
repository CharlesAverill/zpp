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
    int facing; // 0-3 = ULDR
    bool horizontal_mirror;

    Vector2f *last_movement;
    Vector2f *move_speed;

    void load_textures();
public:
    // Constructors
    Link();
    Link(Vector2f pos, std::string fac);

    bool is_walking;
    bool lock_movement;

    // Getters
    Vector2f get_position();
    std::string get_facing();
    int get_facing_int();
    Sprite get_sprite();

    // Setters
    void set_position(Vector2f new_position);

    // Control
    void face(std::string new_facing);
    void update_sprite(int duration);
    std::vector<Vector2f> get_next_corners(std::string direction);
    void move();
};


#endif //ZPP_LINK_H
