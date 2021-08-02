//
// Created by Charles Averill on 7/28/21.
//

#ifndef ZPP_MAP_H
#define ZPP_MAP_H

#include <tmxlite/Map.hpp>
#include "SFMLOrthogonalLayer.hpp"
#include "Polygon.h"

class Map {
    tmx::Map *map;

    MapLayer *render_layer;
    std::vector<Polygon> collision_gons;
    Polygon *door_gon;
public:
    Map(std::string map_path);

    MapLayer *get_render_layer();
    std::vector<Polygon> get_collision_gons();
    Polygon *get_door_gon();
};


#endif //ZPP_MAP_H
