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
    virtual void render(sf::RenderWindow* window) = 0; // make virtual
    Object(float x, float y, float r, float m);
    ~Object();
    
};


// class Planet : public Object
// {

// };

class Projectile : public Object
{
    int velocity;
    float res_forcex;
    float res_forcey;
    float accelx = 0;
    float accely = 0;
    float first;
    sf::Clock clock;

public:

    void update_pos(std::vector<std::pair<float,float>> forces);
    void render(sf::RenderWindow* window);
    Projectile(float x, float y, float r, float m);

};