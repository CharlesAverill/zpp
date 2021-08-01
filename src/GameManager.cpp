//
// Created by Charles Averill on 7/28/21.
//

#include "GameManager.h"

const string tilemaps_prefix = "../assets/tilemaps/";

const bool ENABLE_DEBUG = false;

GameManager::GameManager() {
    link = new Link(Vector2f(128.f, 88.f), "D");

    map_collection = "overworld";
    map_index = new Vector2i(7, 7);
    load_screen();
}

void GameManager::init_window(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    window = new RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Zelda++");
    window->setFramerateLimit(60);

    view = new View(sf::Vector2f(128.f, 88.f), sf::Vector2f(256.f, 173.f));

    window->setView(*view);
    
    game_loop();
}

void GameManager::game_loop() {
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        input();

        sf::Time duration = global_clock.restart();
        MapLayer *renderLayer = current_screen->get_render_layer();
        renderLayer->update(duration);

        window->clear(sf::Color::Black);
        window->draw(*renderLayer);
        window->draw(link->get_sprite());
        if(ENABLE_DEBUG){
            draw_collision_boxes(window, current_screen);
        }
        window->display();

        Vector2f link_position = link->get_position();
        if(link_position.y < 0){
            screen_change("U");
            link->set_position(Vector2f(link_position.x, 176.f));
        } else if(link_position.y > 176){
            screen_change("D");
            link->set_position(Vector2f(link_position.x, 0.f));
        }
    }
}

void GameManager::input() {
    // Movement
    string face_move;

    if(Keyboard::isKeyPressed(Keyboard::W)){
        face_move = "U";
    } else if(Keyboard::isKeyPressed(Keyboard::A)){
        face_move = "L";
    } else if(Keyboard::isKeyPressed(Keyboard::S)){
        face_move = "D";
    } else if(Keyboard::isKeyPressed(Keyboard::D)){
        face_move = "R";
    }

    if(!face_move.empty()) {
        link->face(face_move);
        if (!check_collision(face_move)) {
            link->move();
        }
    }
}

bool GameManager::check_collision(string direction) {
    vector<Vector2f> next_pos = link->get_next_corners(direction);

    for(Polygon collision_gon : current_screen->get_collision_gons()){
        for(Vector2f sprite_corner : next_pos){
            if(collision_gon.contains(sprite_corner)){
                return true;
            }
        }
    }

    return false;
}

void GameManager::screen_change(string direction) {
    if(direction == "U"){
        map_index->y -= 1;
    } else if(direction == "D"){
        map_index->y += 1;
    } else if(direction == "L"){
        map_index->x -= 1;
    } else if(direction == "R"){
        map_index->x += 1;
    }

    if(map_index->x < 0 || map_index->y < 0){
        throw std::runtime_error("Map Index out of bounds");
    }

    load_screen();
}

void GameManager::load_screen() {
    try{
        current_screen = new Map(tilemaps_prefix + map_collection +
                                 "/" + to_string(map_index->x) + "_" + to_string(map_index->y) + ".tmx");
    } catch(std::runtime_error){
        current_screen = nullptr;
        cerr << "Screen " << map_collection + "/" << map_index->x << "_" << map_index->y << ".tmx" << endl;
    }
}
