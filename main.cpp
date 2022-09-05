#include <SFML/Graphics.hpp> 
#include "game.h"
// to compile: g++ t.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o t -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

int main() 
{ //
    

    float planet_x = 150.f;
    float planet_y = 150.f;
    float planet_radius = 100.f;
    float planet_mass = 10000000000000000.f;
    Planet *planet1 = new Planet(planet_x, planet_y, planet_radius, planet_mass);

    
    // float planet2_x = 500.f;
    // float planet2_y = 500.f;
    // float planet2_radius = 100.f;
    // float planet2_mass = 10000000000000000.f;
    // Planet *planet2 = new Planet(planet2_x, planet2_y, planet2_radius, planet2_mass);


    float rotate_speed = 180.f; // degs/sec
    float player_x = 500.f;
    float player_y = 400.f;
    Player *player = new Player(player_x, player_y, rotate_speed);


    float rotate_speed2 = 180.f; // degs/sec
    float player_x2 = 100.f;
    float player_y2 = 100.f;
    Player * player2 = new Player(player_x2, player_y2, rotate_speed2);

    float moon_vx = 215.f;
    float moon_vy = 0;
    float moon_radius = 30.f;
    float moon_mass = 1000000000000.f;
    Moon * moon1 = new Moon(moon_vx, moon_vy, moon_radius, moon_mass, planet1);

    // float moon2_vx = 215.f;
    // float moon2_vy = 0;
    // float moon2_radius = 30.f;
    // float moon2_mass = 1000000000000.f;
    // Moon * moon2 = new Moon(moon2_vx, moon2_vy, moon2_radius, moon2_mass, planet2);


    sf::Vector2f screen_dimensions = {600.f, 600.f};
    Game game(player, screen_dimensions);
    game.set_player2(player2);
    // game.add_planet(planet2);
    game.add_planet(planet1);
    game.add_moon(moon1);
    // game.add_moon(moon2);
    
    game.start_connection();

    while (game.running())
    { 
        game.update();
        game.render();

    } 
 
    return 0; 
} 