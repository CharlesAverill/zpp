//
// Created by Charles Averill on 8/3/21.
//

#ifndef ZPP_ENEMY_H
#define ZPP_ENEMY_H


#include <stdlib.h>

#include "GameManager.h"

using namespace sf;

enum EnemyStateMachine {
    Idle,
    Attack1,
    Attack2,
    Move
};


class Enemy : public Character {
protected:
    EnemyStateMachine state;

    int health;
    int level;

    Enemy();
    Enemy(Vector2f position, int lvl);
public:
    virtual void step_ai(GameManager *gm) = 0;
};


#endif //ZPP_ENEMY_H
