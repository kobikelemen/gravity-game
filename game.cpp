#include "game.h"

Game::Game()
{
    this->window = new sf::RenderWindow(sf::VideoMode(200, 200), "SFML works!");
}


Game::~Game()
{
    delete this->window;
}


void Game::render()
{
    window->clear(sf::Color(255, 0, 0 ,255));
    for (Object *obj : objects) {
        obj->render(window);
    }

    window->display();
}


void Game::update()
{
    poll_events(); 
}

void Game::poll_events()
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


void Game::add_object(Object *obj)
{
    objects.push_back(obj);
}
