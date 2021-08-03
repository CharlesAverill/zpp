//
// Created by Charles Averill on 8/2/21.
//

#ifndef ZPP_CHARACTER_H
#define ZPP_CHARACTER_H


#include <map>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <tmxlite/Map.hpp>

using namespace sf;

enum NPC_type {
    dialogue,
    merchant,
    event,
    animated_object
};

class Character {
protected:
    Sprite sprite;
    NPC_type type;

    std::map<int, Texture> texture_map;

    virtual void load_textures() = 0;
public:
    Sprite get_sprite();
    virtual void update_sprite(int duration) = 0;

    Character();
    Character(Vector2f position);
    virtual ~Character() = default;
};


#endif //ZPP_CHARACTER_H
