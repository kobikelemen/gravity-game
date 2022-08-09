#include "object.h"



Object::Object()
{
    this->shape = new sf::CircleShape(100.f);
    this->shape->setFillColor(sf::Color::Green);
}


Object::~Object()
{
    delete shape;
}

void Object::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}