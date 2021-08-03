//
// Created by Charles Averill on 8/2/21.
//

#include "characters/NPCs/Flame.h"

Flame::Flame(tmx::Vector2f pos) {
    type = CharacterType::ANIMATED_OBJECT;
    load_textures();

    sprite.setTexture(texture_map[0]);
    sprite.setPosition(pos.x, pos.y);

    flip_texture = false;
}

void Flame::load_textures() {
    Texture loadTexture;
    if(loadTexture.loadFromFile("../assets/spritesheets/npcs_transparent.png",
                                IntRect(52, 11, 16, 16))){
        texture_map.insert(std::pair<int, Texture>(0, loadTexture));
    } else {
        std::cerr << "Error loading Flame texture " << 9 << std::endl;
    }
}

void Flame::update_sprite(int duration) {
    flip_texture = duration == 10 ? !flip_texture : flip_texture;

    switch((int)flip_texture){
        case false:
            sprite.setScale(1.f, 1.f);
            break;
        case true:
            sprite.setScale(-1.f, 1.f);
            break;
    }
}
