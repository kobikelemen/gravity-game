#include <SFML/Graphics.hpp> 
#include "game.h"
// to compile: g++ t.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o t -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

int main() 
{ //
    
    float planet_x = 250.f;
    float planet_y = 250.f;
    float planet_radius = 100.f;
    float planet_mass = 10000000000000000.f;
    Planet *planet2 = new Planet(planet_x, planet_y, planet_radius, planet_mass);
    


    float rotate_speed = 180.f; // degs/sec
    float player_x = 500.f;
    float player_y = 400.f;
    Player *player = new Player(player_x, player_y, rotate_speed);


    float rotate_speed2 = 180.f; // degs/sec
    float player_x2 = 100.f;
    float player_y2 = 100.f;
    Player * player2 = new Player(player_x2, player_y2, rotate_speed2);


    
    Game game(player);
    game.set_player2(player2);
    game.add_planet(planet2);
    
    while (game.running()) 
    { 
        game.update();
        game.render();

    } 
 
    return 0; 
} 