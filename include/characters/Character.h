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

enum CharacterType {
    DIALOGUE,
    MERCHANT,
    EVENT,
    ANIMATED_OBJECT,
    ENEMY
};

class Character {
protected:
    sf::Sprite sprite;
    CharacterType type;

    int facing; // 0-3 = ULDR
    bool horizontal_mirror;

    sf::Vector2f *last_movement;
    sf::Vector2f *move_speed;

    std::map<int, sf::Texture> texture_map;

    virtual void load_textures() = 0;

    Character();
    Character(sf::Vector2f position);
public:

    // Getters
    virtual std::vector<sf::Vector2f> get_next_corners(std::string direction);
    std::string get_facing();
    int get_facing_int();
    sf::Sprite get_sprite();
    sf::Vector2f get_position();

    // Setters
    void set_position(sf::Vector2f new_position);

    // Control
    virtual void update_sprite(int duration) = 0;
    virtual void move();

    virtual ~Character() = default;
};


#endif //ZPP_CHARACTER_H
