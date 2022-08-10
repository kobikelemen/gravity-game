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

    window->display();
}


void Game::update()
{
    poll_events();

    // TODO: projectile.update_pos() given forces from planet gravity
    std::vector<std::pair<float,float>> forces;
    forces.push_back(std::pair<float,float>(100000.f,100000.f));
    for (Projectile *proj : projectiles) {
        proj->update_pos(forces);
    }

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
