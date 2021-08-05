//
// Created by Charles Averill on 8/3/21.
//

#include "characters/enemies/Octorok.h"

Octorok::Octorok(tmx::Vector2f position, int lvl) : Enemy(position, lvl){
    sprite.setPosition(position.x + 8.f, position.y + 8.f);
    sprite.setOrigin(8.f, 8.f);

    move_speed = new Vector2f(.65f, .65f);

    load_textures();
    sprite.setTexture(texture_map[0]);

    new_target_position();
}

void Octorok::step_ai(GameManager *gm) {
    if(idle_frames > 0){
        idle_frames--;
        return;
    }

    if(distance(sprite.getPosition(), target_position) < 1.f){
        if(rand() % 10 < 7){
            new_target_position();
        } else {
            idle_frames = 60;
            is_moving = false;
        }
    } else {
        std::vector<Vector2f> next_position = get_next_corners(get_facing());
        bool collide = false;
        for(Polygon collision_gon : gm->get_current_screen()->get_collision_gons()){
            for(Vector2f corner : next_position){
                if(corner.x > 176 || corner.x < 0 || corner.y > 128 || corner.y < 0 || collision_gon.contains(corner)){
                    collide = true;
                    break;
                }
            }
            if(collide){
                break;
            }
        }
        if(collide){
            face_random();
            target_position = sprite.getPosition();
        } else {
            move();
        }
    }
}

void Octorok::update_sprite(int duration) {
    if(is_moving){
        if(duration == 10){
            sprite_offset = !sprite_offset;
        }
        if(facing == 0 || facing == 2){
            sprite.setTexture(texture_map[sprite_offset]);
        } else {
            sprite.setTexture(texture_map[2 + sprite_offset]);
        }
    } else {
        if(facing == 0 || facing == 2){
            sprite.setTexture(texture_map[0]);
        } else {
            sprite.setTexture(texture_map[2]);
        }
    }
}

void Octorok::load_textures() {
    // 0-4: Movement
    for(int i = 0; i < 6; i++){
        Texture loadTexture;
        if(loadTexture.loadFromFile("../assets/spritesheets/overworld_enemies_transparent.png",
                                    IntRect((i + 1) + (16 * i), 11, 16, 16))){
            texture_map.insert(std::pair<int, Texture>(i, loadTexture));
        } else {
            std::cerr << "Error loading Octorok texture " << i << std::endl;
        }
    }
}

void Octorok::new_target_position() {
    face_random();
    Vector2f position = sprite.getPosition();
    switch(facing) {
        case 0: // Up
            target_position = Vector2f(position.x, position.y - (float)(rand() % 64));
            break;
        case 1: // Left
            target_position = Vector2f(position.x - (float)(rand() % 64), position.y);
            break;
        case 2: // Down
            target_position = Vector2f(position.x, position.y + (float)(rand() % 64));
            break;
        case 3: // Right
            target_position = Vector2f(position.x + (float)(rand() % 64), position.y);
            break;
    }
    is_moving = true;
}

void Octorok::face_random() {
    facing = rand() % 4;
    switch(facing){
        case 0: // Up
            sprite.setTexture(texture_map[0]);
            sprite.setScale(1.f, -1.f);
            break;
        case 1: // Left
            sprite.setTexture(texture_map[2]);
            sprite.setScale(1.f, 1.f);
            break;
        case 2: // Down
            sprite.setTexture(texture_map[0]);
            sprite.setScale(1.f, 1.f);
            break;
        case 3: // Right
            sprite.setTexture(texture_map[2]);
            sprite.setScale(-1.f, 1.f);
            break;
    }
    idle_frames = 10;
}
