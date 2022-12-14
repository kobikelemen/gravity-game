#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "object.h"
#include "player.h"
#include "planet.h"
#include "gravity_objects.h"
#include "arrow.h"
#include "networking/server.h"
#include "move.h"
#include "animation.h"




class Game
{

protected:
    Server *server;
    std::thread *context_thread;
    sf::RenderWindow* window;
    sf::Event ev;
    sf::View *view;
    sf::Texture *stars_texture;
    sf::Sprite *stars_sprite;
    std::vector<Projectile*> projectiles;
    std::vector<Planet*> planets;
    std::vector<Moon*> moons;
    std::vector<Laser*> lasers;
    Player *player;
    Player *player2;
    Arrow *enemy_planet_arrow;
    Animation *flame;
    sf::Clock p2_deadtimer;
    sf::Vector2f mousepos;
    sf::Vector2f screen_dim;
    sf::Vector2f screen_pos;
    bool focus;
    bool button_released;
    void poll_events();
    void check_click();
    void update_gravity_objects();
    void update_mousepos();
    void check_collisions();
    void update_player(Player *p, Move move);
    virtual void update_player2(Move move);
    void update_screen_pos();
    virtual void update_lasers();
    void update_arrows();
    void clear_projectiles();
    void send_game_state(game_state state);
    Move check_keyboard();
    Move get_player2_control();
    game_state capture_game_state(Move move);

public:

    Game(Player *p, sf::Vector2f screen_dimensions, std::string window_name);
    ~Game();

    virtual void update();
    void render();
    bool running();
    void add_projectile(Projectile *proj);
    void add_planet(Planet *planet);
    void set_player2(Player *p2);
    void add_moon(Moon *m);
    virtual void start_connection();
    // bool is_player2_alive();

};


#endif