#ifndef PLANET_H
#define PLANET_H


#include "object.h"
#include "gravity_objects.h"

class Projectile;


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
    void on_collision(Projectile *proj);

public:
    Planet(float x, float y, float r, float m);
    ~Planet();
    std::pair<float,float> gravity(float m2, float x1, float x2);
    bool check_collision(Projectile *proj);
    void render(sf::RenderWindow *window);
    float get_centrex();
    float get_centrey();

};




#endif