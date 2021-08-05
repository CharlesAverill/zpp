//
// Created by Charles Averill on 7/30/21.
//

#ifndef ZPP_UTILS_H
#define ZPP_UTILS_H


#include <vector>
#include "math.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "world/Polygon.h"
#include "GameManager.h"

using namespace sf;

void draw_collision_boxes(RenderWindow *window, Map *current_screen);

float distance(Vector2f a, Vector2f b);


#endif //ZPP_UTILS_H
