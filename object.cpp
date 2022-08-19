#include "object.h"



Object::Object(float x, float y, float m)
{
    posx = x;
    posy = y;
    mass = m;
}


Object::~Object() 
{

}

float Object::get_mass() { return mass; }

float Object::get_posx() { return posx; }

float Object::get_posy() { return posy; }

void Object::set_posx(float x) { posx = x; }

void Object::set_posy(float y) { posy = y; }
