//
// Created by Charles Averill on 8/3/21.
//

#include "characters/enemies/Enemy.h"

Enemy::Enemy() {
    type = CharacterType::ENEMY;

    sprite.setPosition(0.f, 0.f);
    sprite.setOrigin(8.f, 8.f);

    health = 3;
    level = 0;
    idle_frames = 0;
    sprite_offset = 0;

    is_moving = false;
}

Enemy::Enemy(tmx::Vector2f position, int lvl) : Character(position) {
    type = CharacterType::ENEMY;

    health = 3;
    level = lvl;
    idle_frames = 0;
    sprite_offset = 0;

    is_moving = false;
}
