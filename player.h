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
    bool first;
    float rotate_speed;
    sf::ConvexShape *shape;
    sf::Clock clock;
    // void rotate(float degrees); // clockwise is +ve

public:
    Rocket(float x, float y, float rotate_speed);
    ~Rocket();
    Projectile* launch_projectile(float xi, float yi, float power_const);
    void move(float thrust, std::pair<float,float> gravity_force, int rotate);
    void render(sf::RenderWindow* window);
    float get_angle();
    float get_mass();
    float get_posx();
    float get_posy();

};






class Player : public Rocket
{
    bool space_released;

public:
    Player(float x, float y, float rotate_speed);
    ~Player();
    Projectile* update_pos(bool forward_arr, bool left_arr, bool right_arr, bool space, std::pair<float,float> gravity_force);
    void set_space_released(bool s);
};

#endif