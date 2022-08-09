#include <SFML/Graphics.hpp>

class Object
{
    // int mass;
    // int radius;
    // int xpos;
    // int ypos;
    sf::CircleShape *shape;

public:
    void render(sf::RenderWindow* window); // make virtual
    Object();
    ~Object();
    
};


// class Planet : Object
// {

// };

// class Projectile : Object
// {

//     void calculate_velocity();

// public:

//     void update_pos();

// };