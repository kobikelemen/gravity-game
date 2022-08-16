#include "game.h"

Game::Game(Player *p)
{
    this->window = new sf::RenderWindow(sf::VideoMode(600, 600), "Gravity");
    this->window->setFramerateLimit(60);
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

void Game::update_projectiles()
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
        // Projectile *p = player->launch_projectile(mousepos.x, mousepos.y);
        // add_projectile(p);
        button_released = false;

    }
}



void Game::check_collisions()
{
    for ( Planet * planet : planets) {
        int i = 0;
        for (Projectile * proj : projectiles) {
            bool c = planet->check_collision(proj);
            if (c) {
                projectiles.erase(projectiles.begin()+i);
                delete proj;
            }
            i ++;
        }
    }
}


Move Game::check_keyboard()
{
    Move move;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        move.left = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        move.right = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        move.up = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        move.space = true;
    }
    return move;
}

void Game::update_player()
{
    // check_click();
    Move move = check_keyboard();
    Projectile *p = player->update_pos(move.up, move.left, move.right, move.space);
    if (p) {
        projectiles.push_back(p);
    }

}




void Game::update()
{
    poll_events();
    
    
    update_player();

    update_projectiles();


    // check_collisions();

}

void Game::poll_events() // I/O -> mouse click, keyboard etc
{
    while (this->window->pollEvent(this->ev)) {
        if (ev.type == sf::Event::Closed) 
            this->window->close(); 
        
        if (ev.type == sf::Event::MouseButtonReleased) {
            button_released = true;
        }
        if (ev.type == sf::Event::KeyReleased) {
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                player->set_space_released(true);
            }
        }
    }
}


bool Game::running()
{
    return this->window->isOpen();
}


void Game::add_projectile(Projectile *proj) { projectiles.push_back(proj); }

void Game::add_planet(Planet *planet) { planets.push_back(planet); }
