#include "laser.h"
#include <math.h>

Laser::Laser(float x, float y, float ix, float iy)
{
    velx = -500.f * ix;
    vely = -500.f * iy;
    posx = x;
    posy = y;
    angle = atan((iy/ ix) * 180/M_PI);
    this->shape = new sf::RectangleShape(sf::Vector2f(5.f, 3.f));
    shape->setRotation(angle);
    this->shape->setFillColor(sf::Color::Yellow);
    this->shape->setPosition(x,y);
    clock.restart();
}

Laser::~Laser()
{
    delete shape;
}

void Laser::render(sf::RenderWindow *window)
{
    window->draw(*shape);
}

void Laser::update_pos()
{
    float dt = clock.getElapsedTime().asSeconds();
    posx += velx * dt;
    posy += vely * dt;
    shape->setPosition(posx,posy);

}

float Laser::get_centrex()
{
    return posx;
}

float Laser::get_centrey()
{
    return posy;
}