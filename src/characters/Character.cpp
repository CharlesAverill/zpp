//
// Created by Charles Averill on 8/2/21.
//

#include "characters/Character.h"


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
