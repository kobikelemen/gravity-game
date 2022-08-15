#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include <SFML/Graphics.hpp>


class Rocket
{
    float angle; // degrees
    float posx;
    float posy;
    float velx;
    float vely;
    float radius;
    float mass;
    float first;
    float rotate_speed;
    sf::CircleShape *shape;
    sf::Clock clock;
    // void rotate(float degrees); // clockwise is +ve

public:
    Rocket(float x, float y, float rotate_speed);
    ~Rocket();
    Projectile* launch_projectile(float xi, float yi, float power_const);
    void move(float thrust, int rotate);
    void render(sf::RenderWindow* window);
    float get_angle();

};






class Player : public Rocket
{
    

public:
    Player(float x, float y, float rotate_speed);
    ~Player();
    
    // Projectile* launch_projectile(float mousex, float mousey);
    void update_pos(bool forward_arr, bool left_arr, bool right_arr, bool space);
};

#endif