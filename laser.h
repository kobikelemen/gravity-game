
#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

class Laser
{
    float posx;
    float posy;
    float velx;
    float vely;
    float angle; //degrees
    sf::Clock clock;
    sf::RectangleShape *shape;

public:
    void render(sf::RenderWindow* window);
    void update_pos();
    float get_centrex();
    float get_centrey();
    Laser(float x, float y, float ix, float iy);
    ~Laser();
};


#endif