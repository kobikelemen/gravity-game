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
    void set_posx(float x);
    void set_posy(float y);
    
};




#endif