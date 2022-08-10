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


void Player::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}


Projectile* Player::launch_projectile(float mousex, float mousey)
{

    float power_const = 0.001;
    float vx = power_const * (mousex - posx);
    float vy = power_const * (mousey - posy);

    
    Projectile *p = new Projectile(posx, posy, vx, vy);
    return p;
    // float i = x / sqrt(pow(x,2) + pow(y,2));
    // float j = y / sqrt(pow(x,2) + pow(y,2));

}