//
// Created by Charles Averill on 7/30/21.
//

#include "Utils.h"

void draw_collision_boxes(RenderWindow *window, Map *current_screen){
    std::vector<Polygon> gons = current_screen->get_collision_gons();
    for(int c = 0; c < gons.size(); c++){
        Polygon gon = gons[c];

        sf::ConvexShape convex;
        vector<tmx::Vector2f> points = gon.get_points();
        convex.setPointCount(points.size());

        for(int i = 0; i < convex.getPointCount(); i++){
            convex.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
        }

        convex.setFillColor(c % 2 == 0 ? Color::Green : Color::Cyan);
        window->draw(convex);
    }
}

float distance(Vector2f a, Vector2f b){
    return abs(sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}
