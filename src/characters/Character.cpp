//
// Created by Charles Averill on 8/2/21.
//

#include "characters/Character.h"

using namespace sf;

Character::Character() {
    sprite.setPosition(0.f, 0.f);
    sprite.setOrigin(8.f, 8.f);
}

Character::Character(Vector2f position) {
    sprite.setPosition(position);
    sprite.setOrigin(8.f, 8.f);
}

Sprite Character::get_sprite() {
    return sprite;
}

std::vector<Vector2f> Character::get_next_corners(std::string direction) {
    // Get the positions of the four corner's of character's sprite after the next move

    std::vector<Vector2f> corners;

    switch(facing){
        case 0: // Up
            last_movement = new Vector2f(0, -1 * move_speed->y);
            break;
        case 2: // Down
            last_movement = new Vector2f(0, move_speed->y);
            break;
        case 1: // Left
            last_movement = new Vector2f(-1 * move_speed->x, 0);
            break;
        case 3: // Right
            last_movement = new Vector2f(move_speed->x, 0);
            break;
    }

    Vector2f sprite_pos = *last_movement + sprite.getPosition();

    corners.push_back(Vector2f(sprite_pos.x - 8, sprite_pos.y - 8)); // TL
    corners.push_back(Vector2f(sprite_pos.x + 8, sprite_pos.y - 8)); // TR
    corners.push_back(Vector2f(sprite_pos.x - 8, sprite_pos.y + 8)); // BL
    corners.push_back(Vector2f(sprite_pos.x + 8, sprite_pos.y + 8)); // BR

    return corners;
}

std::string Character::get_facing() {
    switch(facing){
        case 0:
            return "U";
        case 1:
            return "L";
        case 2:
            return "D";
        case 3:
            return "R";
    }
    return nullptr;
}

int Character::get_facing_int() {
    return facing;
}

Vector2f Character::get_position() {
    return sprite.getPosition();
}

void Character::set_position(Vector2f new_position) {
    sprite.setPosition(new_position);
}

void Character::move() {
    sprite.move(*last_movement);
}
