#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <math.h>

class Object
{
protected:
    float mass;
    float radius;
    float posx;
    float posy;
    sf::CircleShape *shape;

public:
    virtual void render(sf::RenderWindow *window) = 0;
    Object(float x, float y, float r, float m);
    ~Object();
    float get_mass();
    float get_posx();
    float get_posy();
    
};




class Projectile : public Object
{
    float velx;
    float vely;
    float res_forcex;
    float res_forcey;
    float accelx;
    float accely;
    float first;
    sf::Clock clock;

public:

    void update_pos(std::vector<std::pair<float,float>> forces);
    void render(sf::RenderWindow* window);
    Projectile(float x, float y, float vx, float vy);

};





class Planet : public Object
{
    float gravity_const = 6.67 * 10e-11;    
    float gravity(float m1, float m2, float x1, float x2);

public:
    Planet(float x, float y, float r, float m);
    ~Planet();
    std::pair<float,float> calculate_force(Projectile *proj);
    void render(sf::RenderWindow *window);

};




#endif