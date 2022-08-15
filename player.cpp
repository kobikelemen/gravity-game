#include "player.h"



Player::Player(float x, float y)
{
    posx = x;
    posy = y;
    radius = 10.f;
    shape = new sf::CircleShape(radius);
    shape->setFillColor(sf::Color::Green);
    shape->setPosition(x,y);
}


Player::~Player()
{
    delete shape;
}



void Player::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}



Projectile* Player::launch_projectile(float mousex, float mousey)
{

    float power_const = 0.7;
    float vx = power_const * (mousex - posx);
    float vy = power_const * (mousey - posy);
    float explosion_rad = 70.f;
    Projectile *p = new Projectile(posx, posy, vx, vy, explosion_rad);
    return p;

}