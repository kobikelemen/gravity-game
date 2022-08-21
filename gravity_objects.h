#ifndef GRAVITY_OBJECT_H
#define GRAVITY_OBJECT_H

#include "object.h"
#include "planet.h"


class GravityObject : public Object
{
    float velx;
    float vely;
    float res_forcex;
    float res_forcey;
    float accelx;
    float accely;
    float first;
    float radius;
    sf::Clock clock;   

public:

    void update_pos(std::vector<std::pair<float,float>> forces);
    // virtual void render(sf::RenderWindow* window) = 0;
    float get_centrex();
    float get_centrey();
    float get_radius();
    void set_radius(float r);
    virtual void set_position(float x, float y) = 0;
    GravityObject(float x, float y, float vx, float vy, float r, float m);
    ~GravityObject();

};



class Projectile : public GravityObject
{

    float explosion_radius;
    float damage;
    sf::CircleShape *shape;

public:

    void render(sf::RenderWindow* window);
    void set_position(float x, float y);
    float get_damage();
    float get_explosion_radius();
    Projectile(float x, float y, float vx, float vy, float expl_rad);
    ~Projectile();
};



class Planet;


class Moon : public GravityObject
{
    sf::Image *image;
    sf::Texture *texture;
    sf::Sprite *sprite;
    sf::CircleShape *shape;
    float imgsizex;
    float imgsizey;
    float centrex;
    float centrey;
public:

    void render(sf::RenderWindow* window);
    void set_position(float x, float y);
    

    Moon(float vx, float vy, float r, float m, Planet * planet);
    ~Moon();

};


#endif