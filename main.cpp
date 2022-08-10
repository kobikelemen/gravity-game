#include <SFML/Graphics.hpp> 
#include "game.h"
// to compile: ++ t.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o t -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

int main() 
{ 
    
    // Projectile *proj1 = new Projectile(150.f, 150.f, 10.f,-10.f);
    Planet *planet1 = new Planet(200.f, 200.f, 30.f, 10000000000000.f);
    Player *player = new Player(100.f, 100.f);
    
    Game game(player);

    // game.add_projectile(proj1);
    game.add_planet(planet1);
    
    while (game.running()) 
    { 
        game.update();//
        game.render();

    } 
 
    return 0; 
} 