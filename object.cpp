#include "object.h"



Object::Object(float x, float y, float r, float m)
{
    radius = r;
    posx = x;
    posy = y;
    mass = m;
    this->shape = new sf::CircleShape(r);
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setPosition(x,y);

}


Object::~Object()
{
    delete shape;
}

void Projectile::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}




Projectile::Projectile(float x, float y, float r, float m) : Object(x, y, r, m)
{
    velocity = 0;
    res_forcex = 0;
    res_forcey = 0;
    accelx = 0;
    accely = 0;
    first = true;
}

void Projectile::update_pos(std::vector<std::pair<float,float>> forces)
{
    res_forcex = 0;
    res_forcey = 0;
    for (auto f : forces) {
        res_forcex += f.first;
        res_forcey += f.second;
    }
    
    accelx = res_forcex / mass;
    accely = res_forcey / mass;
    float dt;
    if (first) {
        dt = 1/30;
        first = false;
    } else {
        dt = clock.getElapsedTime().asSeconds();
        clock.restart();
    }
    
    float dx = accelx * pow(dt,2);
    float dy = accely * pow(dt,2);
    posx += dx;
    posy += dy;
    this->shape->setPosition(posx, posy);

}


