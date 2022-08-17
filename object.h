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
    float posx; // --> top left corner
    float posy;// -->  ^

public:
    virtual void render(sf::RenderWindow *window) = 0;
    Object(float x, float y, float m);
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
    float radius;
    float explosion_radius;
    sf::Clock clock;
    sf::CircleShape *shape;
    

public:

    void update_pos(std::vector<std::pair<float,float>> forces);
    void render(sf::RenderWindow* window);
    float get_centrex();
    float get_centrey();
    float get_explosion_radius();
    Projectile(float x, float y, float vx, float vy, float expl_rad);
    ~Projectile();

};





class Planet : public Object
{
    float gravity_const = 6.67 * 10e-11;    
    sf::Image *image;
    sf::Texture *texture;
    sf::Sprite *sprite;
    sf::CircleShape *shape;
    float imgsizex;
    float imgsizey;
    float centrex;
    float centrey;
    float radius;
    float health;
    void update_image_collision(Projectile *proj);
    

public:
    Planet(float x, float y, float r, float m);
    ~Planet();
    std::pair<float,float> gravity(float m2, float x1, float x2);
    bool check_collision(Projectile *proj);
    void render(sf::RenderWindow *window);

};




#endif