
#ifndef ARROW_H
#define ARROW_H

#include <SFML/Graphics.hpp>
#include <math.h>


class Arrow
{

    float xi;
    float yi;
    float posx;
    float posy;
    sf::ConvexShape *shape;
    sf::Vector2f screen_dim;
public:
    Arrow(sf::Vector2f screen_dim);
    ~Arrow();
    void update_pos(float targetx, float targety, float playerx, float playery);
    void render(sf::RenderWindow *window);
};

#endif