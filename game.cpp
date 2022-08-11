#include "game.h"

Game::Game(Player *p)
{
    this->window = new sf::RenderWindow(sf::VideoMode(1400, 1400), "Gravity");
    player = p;
    projectiles = {};
    button_released = true;
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

    player->render(window);

    window->display();
}

void Game::update_positions()
{
    std::vector<std::pair<float,float>> forces;
    for (Projectile *proj : projectiles) 
    {
        for ( Planet *planet : planets ) {
            forces.push_back(planet->calculate_force(proj));
        }
        proj->update_pos(forces);
    }
    
}


void Game::update_mousepos()
{
    // mousepos = sf::Mouse::getPosition(*this->window);
    sf::Vector2i temp = sf::Mouse::getPosition(*window);
    mousepos = window->mapPixelToCoords(temp);
}


void Game::check_click()
{

    if (button_released && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        
        update_mousepos();
        Projectile *p = player->launch_projectile(mousepos.x, mousepos.y);
        add_projectile(p);
        button_released = false;

    }
}


void Game::update()
{
    poll_events();
    
    check_click();

    update_positions();
}

void Game::poll_events() // I/O -> mouse click, keyboard etc
{
    while (this->window->pollEvent(this->ev)) {
        if (ev.type == sf::Event::Closed) 
            this->window->close(); 
        
        if (ev.type == sf::Event::MouseButtonReleased) {
            button_released = true;
        }
    }
}


bool Game::running()
{
    return this->window->isOpen();
}


void Game::add_projectile(Projectile *proj) { projectiles.push_back(proj); }

void Game::add_planet(Planet *planet) { planets.push_back(planet); }
