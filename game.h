#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "object.h"
#include "player.h"

class Game
{
    sf::RenderWindow* window;
    sf::Event ev;
    std::vector<Projectile*> projectiles;
    std::vector<Planet*> planets;
    Player *player;
    sf::Vector2f mousepos;
    bool button_released;
    void poll_events();
    void check_click();
    void update_positions();
    void update_mousepos();
    void check_collisions();

public:

    Game(Player *p);
    ~Game();

    void update();
    void render();
    bool running();
    void add_projectile(Projectile *proj);
    void add_planet(Planet *planet);

};


#endif