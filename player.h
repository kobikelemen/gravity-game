#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include <SFML/Graphics.hpp>

class Player
{
    float posx;
    float posy;
    float radius;
    sf::CircleShape *shape;

public:
    Player(float x, float y);
    ~Player();
    void render(sf::RenderWindow* window);
    Projectile* launch_projectile(float mousex, float mousey);
    // void update_pos()
};

#endif