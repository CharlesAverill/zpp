//
// Created by Charles Averill on 7/28/21.
//

#include "GameManager.h"

GameManager::GameManager() {
    link = new Link(Vector2f(128.f, 88.f), "D");

    current_screen = new Map("../assets/tilemaps/overworld/7_7.tmx");
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
        //draw_collision_boxes(window, current_screen);
        window->display();
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
    if(face_move.length()){
        link->face(face_move);
        if(!check_collision(face_move)){
            link->move();
        }
    }
}

bool GameManager::check_collision(string direction) {
    Vector2f next_pos = link->get_next_position(direction);

    for(Polygon collision_gon : current_screen->get_collision_gons()){
        if(collision_gon.contains(next_pos)){
            return true;
        }
    }

    return false;
}
