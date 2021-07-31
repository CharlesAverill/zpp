//
// Created by Charles Averill on 7/30/21.
//

#ifndef ZPP_GRAPHICSUTILS_H
#define ZPP_GRAPHICSUTILS_H


#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "Map.h"
#include "Polygon.h"

using namespace sf;


void draw_collision_boxes(RenderWindow *window, Map *current_screen);


#endif //ZPP_GRAPHICSUTILS_H
