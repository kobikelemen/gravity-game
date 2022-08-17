#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "object.h"
#include "player.h"

struct Move
{
    bool left;
    bool right;
    bool up;
    bool space;
    Move(bool l, bool r, bool u, bool s) : left{l}, right{r}, up{u}, space{s} {};
    Move() : left{false}, right{false}, up{false}, space{false} {};
};


class Game
{
    sf::RenderWindow* window;
    sf::Event ev;
    std::vector<Projectile*> projectiles;
    std::vector<Planet*> planets;
    Player *player;
    Player *player2;
    sf::Vector2f mousepos;
    bool button_released;
    void poll_events();
    void check_click();
    void update_projectiles();
    void update_mousepos();
    void check_collisions();
    void update_player1();
    void update_player2();
    
    Move check_keyboard();

public:

    Game(Player *p);
    ~Game();

    void update();
    void render();
    bool running();
    void add_projectile(Projectile *proj);
    void add_planet(Planet *planet);
    void set_player2(Player *p2);
    // bool is_player2_alive();

};


#endif