#include <SFML/Graphics.hpp> 
#include "game.h"
// to compile: ++ t.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o t -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

int main() 
{ 
    
    // Projectile *proj1 = new Projectile(150.f, 150.f, 10.f,-10.f);
    // Planet *planet1 = new Planet(700.f, 700.f, 50.f, 100000000000000000.f);
    // Planet *planet1 = new Planet(600.f, 600.f, 30.f, 100000000000000.f);
    Planet *planet2 = new Planet(400.f, 400.f, 1.f, 100000000000000.f);
    // Planet *planet2 = new Planet(300.f, 300.f, 100.f, 100000.f);
    // Planet *planet3 = new Planet(200.f, 200.f, 30.f, 100000000000000.f);
    Player *player = new Player(350.f, 350.f);
    
    Game game(player);
    // game.add_planet(planet1);
    game.add_planet(planet2);
    // game.add_planet(planet3);
    
    while (game.running()) 
    { 
        game.update();
        game.render();

    } 
 
    return 0; 
} 