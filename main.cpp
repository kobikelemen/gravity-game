#include <SFML/Graphics.hpp> 
#include "game.h"
// to compile: g++ t.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o t -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

int main() 
{ //
    
    Planet *planet2 = new Planet(0.f, 0.f, 100.f, 100000000000000.f);
    Player *player = new Player(350.f, 350.f);
    
    Game game(player);
    game.add_planet(planet2);
    
    while (game.running()) 
    { 
        game.update();
        game.render();

    } 
 
    return 0; 
} 