//
// Created by Charles Averill on 7/30/21.
//

#include "GraphicsUtils.h"

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
