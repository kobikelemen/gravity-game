#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "object.h"


class Game
{
    sf::RenderWindow* window;
    sf::Event ev;
    std::vector<Projectile*> projectiles;
    std::vector<Planet*> planets;
    
public:

    Game();
    ~Game();

    void update();
    void render();
    void poll_events();
    bool running();
    void add_projectile(Projectile *proj);
    void add_planet(Planet *planet);

};