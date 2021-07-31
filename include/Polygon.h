//
// Created by Charles Averill on 7/28/21.
//

#ifndef ZPP_POLYGON_H
#define ZPP_POLYGON_H

#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <tmxlite/Types.hpp>

using namespace std;


class Polygon {
    string name;
    vector<tmx::Vector2f> points;
    float angle_2D(tmx::Vector2f point1, tmx::Vector2f point2);
public:
    ~Polygon()=default;
    Polygon(string n, vector<tmx::Vector2f> points_v, tmx::Vector2f position);

    bool contains(sf::Vector2f point);
    string get_name();
    vector<tmx::Vector2f> get_points();
};


#endif //ZPP_POLYGON_H
