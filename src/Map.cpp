//
// Created by Charles Averill on 7/28/21.
//

#include "Map.h"

Map::Map(std::string map_path) {
    tmx::Map temp_map;
    door_gon = nullptr;

    if(temp_map.load(map_path)){
        map = &temp_map;

        render_layer = new MapLayer(temp_map, 0);

        const auto& layers = map->getLayers();

        for (const auto& layer : layers)
        {
            if(layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();

                if(layer->getName() == "Collision"){
                    for(const auto& object : objects){
                        collision_gons.emplace_back(Polygon(object.getName(), object.getPoints(), object.getPosition()));
                    }
                } else if(layer->getName() == "Doors"){
                    if(!objects.empty()){
                        auto object = objects[0];
                        door_gon = new Polygon(object.getName(), object.getPoints(), object.getPosition());
                    }
                }
            }
        }
    } else {
        throw std::runtime_error("File not found: " + map_path);
    }
}

MapLayer *Map::get_render_layer() {
    return render_layer;
}

std::vector<Polygon> Map::get_collision_gons() {
    return collision_gons;
}

Polygon *Map::get_door_gon() {
    return door_gon;
}
