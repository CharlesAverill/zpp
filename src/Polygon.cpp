//
// Created by Charles Averill on 7/28/21.
//

#include "Polygon.h"

Polygon::Polygon(string n, vector<tmx::Vector2f> points_v, tmx::Vector2f pos) {
    name = n;
    position = new sf::Vector2f(pos.x, pos.y);
    for(int i = 0; i < points_v.size(); i++){
        points_v[i].x += pos.x;
        points_v[i].y += pos.y;
    }
    points = points_v;
}

bool Polygon::contains(sf::Vector2f point) {
    float angle = 0.f;

    tmx::Vector2f p1, p2;

    size_t size = points.size();

    for (int i = 0; i < size; i++) {
        tmx::Vector2f polygon_point1 = points[i];
        tmx::Vector2f polygon_point2 = points[(i + 1) % size];

        p1 = tmx::Vector2f(polygon_point1.x - point.x, polygon_point1.y - point.y);
        p2 = tmx::Vector2f(polygon_point2.x - point.x, polygon_point2.y - point.y);

        angle += angle_2D(p1, p2);
    }

    if (abs(angle) < 3.14f)
        return false;
    else
        return true;
}

float Polygon::angle_2D(tmx::Vector2f point1, tmx::Vector2f point2)
{
    float d_theta, theta1, theta2;

    theta1 = atan2(point1.y, point1.x);
    theta2 = atan2(point2.y, point2.x);
    d_theta = theta2 - theta1;

    while (d_theta > 3.14f)
        d_theta -= 6.28f;
    while (d_theta < -3.14f)
        d_theta += 6.28f;

    return d_theta;
}

string Polygon::get_name() {
    return name;
}

vector<tmx::Vector2f> Polygon::get_points() {
    return points;
}

sf::Vector2f *Polygon::get_position() {
    return position;
}
