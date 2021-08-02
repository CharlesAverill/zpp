//
// Created by Charles Averill on 7/27/21.
//

#include "Link.h"

using namespace sf;

Link::Link() {
    load_textures();
    face("D");

    last_movement = new Vector2f(0.f, 0.f);
    move_speed = new Vector2f(1.4f, 1.4f);

    sprite.setPosition(0.f, 0.f);
    sprite.setOrigin(8.f, 8.f);
}

Link::Link(Vector2f pos, std::string fac) {
    load_textures();
    face(fac);

    last_movement = new Vector2f(0.f, 0.f);
    move_speed = new Vector2f(1.4f, 1.4f);

    sprite.setPosition(pos);
    sprite.setOrigin(8.f, 8.f);
}

void Link::load_textures() {
    // 0-5: Movement
    for(int i = 0; i < 6; i++){
        Texture loadTexture;
        if(loadTexture.loadFromFile("../assets/spritesheets/link_transparent.png",
                                    IntRect((i + 1) + (16 * i), 11, 16, 16))){
            texture_map.insert(std::pair<int, Texture>(i, loadTexture));
        } else {
            std::cerr << "Error loading Link texture " << i << std::endl;
        }
    }
}

Vector2f Link::get_position() {
    return sprite.getPosition();
}

std::string Link::get_facing() {
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

int Link::get_facing_int() {
    return facing;
}

Sprite Link::get_sprite() {
    return sprite;
}

void Link::face(std::string newFacing) {
    if(newFacing == "U"){
        facing = 0;
        sprite.setTexture(texture_map[4]);
    } else if(newFacing == "L"){
        facing = 1;
        sprite.setTexture(texture_map[2]);
        horizontal_mirror = true;
    } else if(newFacing == "D"){
        facing = 2;
        sprite.setTexture(texture_map[0]);
    } else if(newFacing == "R"){
        facing = 3;
        sprite.setTexture(texture_map[2]);
        horizontal_mirror = false;
    } else {
        throw std::invalid_argument("Facing parameter must be one of ULDR");
    }

    if(horizontal_mirror){
        sprite.setScale(-1.f, 1.f);
    } else {
        sprite.setScale(1.f, 1.f);
    }
}

std::vector<Vector2f> Link::get_next_corners(std::string direction) {
    // Get the positions of the four corner's of link's sprite after the next move

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

    corners.push_back(Vector2f(sprite_pos.x - 6.5, sprite_pos.y)); // TL
    corners.push_back(Vector2f(sprite_pos.x + 6.5, sprite_pos.y)); // TR
    corners.push_back(Vector2f(sprite_pos.x - 6.5, sprite_pos.y + 6)); // BL
    corners.push_back(Vector2f(sprite_pos.x + 6.5, sprite_pos.y + 6)); // BR

    return corners;
}

void Link::move(){
    sprite.move(*last_movement);
}

void Link::set_position(Vector2f new_position) {
    sprite.setPosition(new_position);
}

void Link::update_sprite(int duration) {
    if(is_walking){
        int sprite_offset = duration > 10;
        switch(facing){
            case 0:
                sprite.setTexture(texture_map[4 + sprite_offset]);
                break;
            case 1:
                sprite.setTexture(texture_map[2 + sprite_offset]);
                horizontal_mirror = true;
                break;
            case 2:
                sprite.setTexture(texture_map[sprite_offset]);
                break;
            case 3:
                sprite.setTexture(texture_map[2 + sprite_offset]);
                horizontal_mirror = true;
                break;
        }
    }
}
