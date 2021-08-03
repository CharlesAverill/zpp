//
// Created by Charles Averill on 8/3/21.
//

#ifndef ZPP_OCTOROK_H
#define ZPP_OCTOROK_H

#include "Enemy.h"

using namespace sf;

class Octorok : public Enemy{
    Vector2f target_position;
    void load_textures();
    void update_sprite(int duration);
public:
    Octorok(tmx::Vector2f position, int lvl);
    void step_ai(GameManager *gm);
};


#endif //ZPP_OCTOROK_H
