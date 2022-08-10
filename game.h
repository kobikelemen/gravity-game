#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
// #include <SFML/Mouse.hpp>
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
    void poll_events();
    void check_click();
    void update_positions();
    void update_mousepos();

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