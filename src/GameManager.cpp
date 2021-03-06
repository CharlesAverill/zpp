//
// Created by Charles Averill on 7/28/21.
//

#include "GameManager.h"
#include "characters/enemies/Enemy.h"
#include "SFML/Graphics/CircleShape.hpp"

const string tilemaps_prefix = "../assets/tilemaps/";

const bool ENABLE_DEBUG = false;

GameManager::GameManager() {
    link = new Link(Vector2f(128.f, 88.f), "D");
    held_duration = 0;

    map_collection = "overworld";
    is_underground = false;
    map_index = new Vector2i(7, 7);
    load_screen(false);
}

void GameManager::init_window(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    window = new RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Zelda++");
    window->setFramerateLimit(60);

    view = new View(sf::Vector2f(128.f, 64.f), sf::Vector2f(280.f, 240.f));

    window->setView(*view);

    hud = new HUD();

    game_loop();
}

void GameManager::game_loop() {
    int sprite_update_counter = 0;

    while (window->isOpen())
    {
        sprite_update_counter++;
        if(sprite_update_counter > 10){
            sprite_update_counter = 0;
        }

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        if(!link->lock_movement && input()){
            break;
        }

        // Screen changes
        if(!is_underground){
            Vector2f link_position = link->get_position();
            if(link_position.y - 8.f < 0){
                screen_change("U");
                link->set_position(Vector2f(link_position.x, 168.f));
            } else if(link_position.y + 8.f > 176){
                screen_change("D");
                link->set_position(Vector2f(link_position.x, 8.f));
            }
        }

        sf::Time duration = global_clock.restart();
        MapLayer *renderLayer = current_screen->get_render_layer();
        renderLayer->update(duration);

        // Drawing
        if(ENABLE_DEBUG){
            window->clear(Color::Magenta);
        } else {
            window->clear(Color::Black);
        }
        window->draw(*renderLayer);

        // Draw HUD
        hud->draw_hud(window, link);

        // Draw characters and objects
        for(Character *character : current_characters){
            if(character->get_type() == CharacterType::ENEMY){
                ((Enemy *)character)->step_ai(this);
            }
            character->update_sprite(sprite_update_counter);
            window->draw(character->get_sprite());

            if(ENABLE_DEBUG){
                for(Vector2f corner : character->get_next_corners(character->get_facing())){
                    CircleShape shape(.5f);
                    shape.setPosition(corner);
                    shape.setFillColor(Color::Cyan);
                    window->draw(shape);
                }
            }
        }

        window->draw(link->get_sprite());
        if(ENABLE_DEBUG){
            draw_collision_boxes(window, current_screen);
        }
        window->display();
    }
}

int GameManager::input() {
    // Pausing
    if(Keyboard::isKeyPressed(Keyboard::Escape)){
        cout << "Pause!" << endl;
        return 1;
    }
    // Attacking
    if(Keyboard::isKeyPressed(Keyboard::P)){
        cout << "Sword attack!" << endl;
    } else if(Keyboard::isKeyPressed(Keyboard::O)){
        cout << "Item use!" << endl;
    }

    // Movement
    string face_move;

    if(Keyboard::isKeyPressed(Keyboard::W)){
        face_move = "U";
    } else if(Keyboard::isKeyPressed(Keyboard::S)){
        face_move = "D";
    } else if(Keyboard::isKeyPressed(Keyboard::A)){
        face_move = "L";
    } else if(Keyboard::isKeyPressed(Keyboard::D)){
        face_move = "R";
    }

    if(!face_move.empty()) {
        link->is_walking = true;
        string link_facing = link->get_facing();
        if(link_facing != face_move){
            link->face(face_move);
        } else if(link_facing == held_direction){
            held_duration++;
            if(held_duration > 10){
                held_duration = 0;
            }
            link->update_sprite(held_duration);
        }
        held_direction = face_move;

        int collision = check_collision(face_move);
        switch(collision){
            case 0:
                link->move();
                break;
            case 2:
                screen_change("DOOR");
                if(is_underground){
                    link->set_position(Vector2f(128.f, 168.f));
                } else {
                    Vector2f *door_pos = current_screen->get_door_gon()->get_position();
                    link->set_position(Vector2f(door_pos->x + 8.f, door_pos->y + 16.f));
                }
                break;
            default:
                break;
        }
    } else {
        held_direction = "";
        held_duration = 0;
        link->is_walking = false;
    }

    return 0;
}

int GameManager::check_collision(string direction) {
    /*
     * 0: No collision
     * 1: Wall collision
     * 2: Door collision
     */
    vector<Vector2f> next_pos = link->get_next_corners(direction);

    // Check wall collision
    for(Polygon collision_gon : current_screen->get_collision_gons()){
        for(Vector2f sprite_corner : next_pos){
            if(collision_gon.contains(sprite_corner)){
                return 1;
            }
        }
    }

    // Check door collision
    Polygon *door_gon = current_screen->get_door_gon();
    for(Vector2f sprite_corner : next_pos){
        if(door_gon != nullptr && door_gon->contains(sprite_corner)){
            return 2;
        }
    }

    return 0;
}

void GameManager::screen_change(string direction) {
    bool switch_underground = false;
    if(direction == "U"){
        map_index->y -= 1;
    } else if(direction == "D"){
        map_index->y += 1;
    } else if(direction == "L"){
        map_index->x -= 1;
    } else if(direction == "R"){
        map_index->x += 1;
    } else if(direction == "DOOR"){
        switch_underground = true;
    }

    if(map_index->x < 0 || map_index->y < 0){
        throw std::runtime_error("Map Index out of bounds");
    }

    current_characters.clear();

    load_screen(switch_underground);

    current_characters = current_screen->get_characters();
}

void GameManager::load_screen(bool switch_underground) {
    try{
        string map_path = tilemaps_prefix + map_collection + "/" + to_string(map_index->x) + "_" + to_string(map_index->y);
        if(switch_underground && !is_underground){
            map_path += "_door";
            is_underground = true;
        } else {
            is_underground = false;
        }
        map_path += ".tmx";
        current_screen = new Map(map_path);
    } catch(std::runtime_error){
        current_screen = nullptr;
        cerr << "Screen " << map_collection + "/" << map_index->x << "_" << map_index->y << ".tmx" << endl;
    }
}

Map *GameManager::get_current_screen() {
    return current_screen;
}

RenderWindow *GameManager::get_render_window() {
    return window;
}
