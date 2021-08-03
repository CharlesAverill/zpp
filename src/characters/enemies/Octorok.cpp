//
// Created by Charles Averill on 8/3/21.
//

#include "characters/enemies/Octorok.h"

Octorok::Octorok(tmx::Vector2f position, int lvl){
    sprite.setPosition(position.x + 8.f, position.y + 8.f);
    sprite.setOrigin(8.f, 8.f);

    level = lvl;

    load_textures();
    sprite.setTexture(texture_map[0]);
}

void Octorok::step_ai(GameManager *gm) {
    if(distance(sprite.getPosition(), target_position) < 0.1f){
        if(rand() % 10 < 7){
            std::cout << "Walk again" << std::endl;
        } else {
            std::cout << "Idle" << std::endl;
        }
    } else {
        std::vector<Vector2f> next_position = get_next_corners(get_facing());
        for(Polygon collision_gon : gm->get_current_screen()->get_collision_gons()){
            for(Vector2f corner : next_position){
                if(collision_gon.contains(corner)){

                }
            }
        }
    }
}

void Octorok::update_sprite(int duration) {

}

void Octorok::load_textures() {
    // 0-4: Movement
    for(int i = 0; i < 6; i++){
        Texture loadTexture;
        if(loadTexture.loadFromFile("../assets/spritesheets/overworld_enemies_transparent.png",
                                    IntRect((i + 1) + (16 * i), 11, 16, 16))){
            texture_map.insert(std::pair<int, Texture>(i, loadTexture));
        } else {
            std::cerr << "Error loading Link texture " << i << std::endl;
        }
    }
}
