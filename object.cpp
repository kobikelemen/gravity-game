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


Object::~Object() { delete shape; }

float Object::get_mass() { return mass; }

float Object::get_posx() { return posx; }

float Object::get_posy() { return posy; }






void Projectile::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}


Projectile::Projectile(float x, float y, float vx, float vy) : Object(x, y, 5.f, 3.f)
{
    velx = vx;
    vely = vy;
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
    
    velx += accelx * dt;
    vely += accely * dt;
    posx += velx * dt;
    posy += vely * dt;
    this->shape->setPosition(posx, posy);

}








Planet::Planet(float x, float y, float r, float m) : Object(x, y, r, m)
{

}


Planet::~Planet() {};

float Planet::gravity(float m1, float m2, float x1, float x2)
{
    float rad = x1 - x2;
    float force;


    if (abs(rad) > radius) {
        force = gravity_const * m1 * m2 / pow(rad, 2);
    } else {
        force = gravity_const * m1 * m2 / pow(radius, 2);
    }

    if (rad > 0) {
        return force;
    } else { 
        return -force; 
    }
    
}


std::pair<float,float> Planet::calculate_force(Projectile *proj)
{
    float fx = gravity(mass ,proj->get_mass(), posx, proj->get_posx());
    float fy = gravity(mass ,proj->get_mass(), posy, proj->get_posy());
    printf("\n %f   %f ", fx, fy);
    return std::pair<float,float>( fx, fy );
}

void Planet::render(sf::RenderWindow *window)
{
    window->draw(*shape);
}











