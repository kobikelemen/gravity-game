#include <SFML/Graphics.hpp> 
#include "game.h"

// to compile: ++ t.cpp -I/usr/local/Cellar/sfml/2.5.1_1/include/ -o t -L/usr/local/Cellar/sfml/2.5.1_1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

int main() 
{ 
    Game game;
    Projectile *proj1 = new Projectile(30.f, 30.f, 5.f, 3.f);
    game.add_projectile(proj1);
 
    while (game.running()) 
    { 
        game.update();
        game.render();

    } 
 
    return 0; 
} 