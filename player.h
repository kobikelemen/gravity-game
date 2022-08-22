#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "gravity_objects.h"
#include "laser.h"
#include <SFML/Graphics.hpp>


struct launched
{
    Laser *l;
    Projectile *p;
    launched() : l{NULL}, p{NULL} {};
};


class Rocket : public Object
{
    float angle; // degrees
    float velx;
    float vely;
    bool first;
    bool alive;
    float rotate_speed;
    sf::ConvexShape *shape;
    sf::Clock clock;
    bool in_triangle(sf::Vector2f pt, sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3);
    float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3);

    // void rotate(float degrees); // clockwise is +ve

public:
    Rocket(float x, float y, float rotate_speed);
    ~Rocket();
    Laser* launch_laser(float xi, float yi);
    Projectile* launch_projectile(float xi, float yi, float power_const);
    int check_collision(std::vector<std::pair<float,float>> positions);
    void move(float thrust, std::pair<float,float> gravity_force, int rotate);
    void render(sf::RenderWindow* window);
    float get_angle();
    bool is_alive();
    void set_alive(float a);

};






class Player : public Rocket
{
    bool space_released;
    bool a_released;

public:
    Player(float x, float y, float rotate_speed);
    ~Player();
    launched update_pos(bool forward_arr, bool left_arr, bool right_arr, bool space, bool a, std::pair<float,float> gravity_force);
    void set_space_released(bool s);
    void set_a_released(bool s);
};

#endif