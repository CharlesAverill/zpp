//
// Created by Charles Averill on 7/27/21.
//

#ifndef ZPP_LINK_H
#define ZPP_LINK_H

#include <map>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Link {
    int facing; // 0-3 = ULDR
    bool horizontal_mirror;

    std::map<int, Texture> texture_map;
    Sprite sprite;

    Vector2f *last_movement;
    Vector2f *move_speed;

    void load_textures();
public:
    // Constructors
    Link();
    Link(Vector2f pos, std::string fac);

    // Getters
    Vector2f get_position();
    std::string get_facing();
    int get_facing_int();
    Sprite get_sprite();

    // Control
    void face(std::string new_facing);
    Vector2f get_next_position(std::string direction);
    void move();
};


#endif //ZPP_LINK_H
