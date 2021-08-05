//
// Created by Charles Averill on 8/5/21.
//

#include "HUD.h"

HUD::HUD() {
    load_textures();
}

void HUD::load_textures() {
    Texture loadTexture;

    // Standard Overlay
    if(loadTexture.loadFromFile("../assets/spritesheets/hud.png",
                                IntRect(258, 11, 256, 56))){
        textures.push_back(loadTexture);
        standard_overlay.setPosition(0, -56);
    } else {
        std::cerr << "Could not load Standard Overlay texture" << std::endl;
    }

    // Hearts
    if(loadTexture.loadFromFile("../assets/spritesheets/hud.png",
                                IntRect(627, 117, 26, 8))) {
        textures.push_back(loadTexture);
    } else {
        std::cerr << "Could not load Heart textures" << std::endl;
    }
}

void HUD::draw_hud(RenderWindow *window, Link *link) {
    // HUD Overlay
    if(standard_overlay.getTexture() != &textures[0]){
        standard_overlay.setTexture(textures[0]);
    }
    window->draw(standard_overlay);


    Vector2f hud_position = standard_overlay.getPosition();

    // Hearts
    int health = link->get_health();
    int max_health = link->get_max_health();

    bool half_heart = health % 2 != 0;
    int full_hearts = half_heart ? (health - 1) / 2 : health / 2;
    int empty_hearts = (max_health - health) / 2;

    int x_offset = hud_position.x + 176;
    int y_offset = hud_position.y + 32;

    for(int i = 0; i < full_hearts; i++){
        if(x_offset >= hud_position.x + 240){
            x_offset = hud_position.x + 176;
            y_offset += 8;
        }

        Sprite fullHeart(textures[1],
                         IntRect(18, 0, 8, 8));
        fullHeart.setPosition(x_offset, y_offset);

        window->draw(fullHeart);

        x_offset += 8;
    }

    if(half_heart){
        if(x_offset >= hud_position.x + 240){
            x_offset = hud_position.x + 176;
            y_offset += 8;
        }

        Sprite halfHeart(textures[1],
                         IntRect(9, 0, 8, 8));
        halfHeart.setPosition(x_offset, y_offset);

        window->draw(halfHeart);

        x_offset += 8;
    }

    for(int i = 0; i < empty_hearts; i++){
        if(x_offset >= hud_position.x + 240){
            x_offset = hud_position.x + 176;
            y_offset += 8;
        }

        Sprite emptyHeart(textures[1],
                         IntRect(0, 0, 8, 8));
        emptyHeart.setPosition(x_offset, y_offset);

        window->draw(emptyHeart);

        x_offset += 8;
    }

    while(y_offset <= hud_position.y + 40){
        if(x_offset >= hud_position.x + 240){
            x_offset = hud_position.x + 176;
            y_offset += 8;
        }

        Sprite emptySquare(textures[0],
                           IntRect(0, 0, 8, 8));
        emptySquare.setPosition(x_offset, y_offset);

        window->draw(emptySquare);
        x_offset += 8;
    }
}
