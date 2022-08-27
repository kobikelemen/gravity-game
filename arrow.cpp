#include "arrow.h"


Arrow::Arrow(sf::Vector2f screen_dim)
{
    this->screen_dim = screen_dim;
    shape = new sf::ConvexShape(3);
    shape->setPoint(0, sf::Vector2f(-10, 0));
    shape->setPoint(1, sf::Vector2f(10, -10));
    shape->setPoint(2, sf::Vector2f(10, 10));
    shape->setFillColor(sf::Color::Red);
}

Arrow::~Arrow()
{
    delete shape;
}


void Arrow::update_pos(float targetx, float targety, float playerx, float playery)
{
    float dx = targetx - playerx;
    float dy = targety - playery;
    float angle = atan(dy/dx) * 180/M_PI;
    if (dx > 0) {
        angle = 180 - angle;
    }
    xi = dx / sqrt(pow(dx,2) + pow(dy,2));
    yi = dy / sqrt(pow(dx,2) + pow(dy,2));
    float maxx;
    float maxy;
    if (abs(dx) > screen_dim.x/2) {
        maxx = screen_dim.x/2;
    } else {
        maxx = dx;
    }
    if (abs(dy) > screen_dim.y/2) {
        maxy = screen_dim.y/2;
    } else {
        maxy = dy;
    }

    posx = maxx * xi + playerx;
    posy = maxy * yi + playery;
    shape->setPosition(posx,posy);
    shape->setRotation(angle);
}





void Arrow::render(sf::RenderWindow *window)
{
    window->draw(*shape);
}