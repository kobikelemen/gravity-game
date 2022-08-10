#include "game.h"

Game::Game()
{
    this->window = new sf::RenderWindow(sf::VideoMode(600, 800), "SFML works!");
}


Game::~Game()
{
    delete this->window;
}


void Game::render()
{
    window->clear(sf::Color(10, 0, 0 ,255));
    for (Projectile *proj : projectiles) {
        proj->render(window);
    }

    for (Planet *planet : planets) {
        planet->render(window);
    }

    window->display();
}


void Game::update()
{
    poll_events();

    // TODO: projectile.update_pos() given forces from planet gravity
    std::vector<std::pair<float,float>> forces;
    for ( Planet *planet : planets ) {
        forces.push_back(planet->calculate_force(projectiles[0]));
    }
    projectiles[0]->update_pos(forces);
    // forces.push_back(std::pair<float,float>(0.009,0.09));

}

void Game::poll_events() // I/O -> mouse click, keyboard etc
{
    while (this->window->pollEvent(this->ev)) {
        if (ev.type == sf::Event::Closed) 
            this->window->close(); 
    }
}


bool Game::running()
{
    return this->window->isOpen();
}


void Game::add_projectile(Projectile *proj)
{
    projectiles.push_back(proj);
}


void Game::add_planet(Planet *planet)
{
    planets.push_back(planet);
}