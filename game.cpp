#include "game.h"

Game::Game(Player *p, sf::Vector2f screen_dimensions)
{
    this->window = new sf::RenderWindow(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "Gravity");
    this->window->setFramerateLimit(60);
    player = p;
    projectiles = {};
    button_released = true;
    stars_texture = new sf::Texture();
    stars_texture->loadFromFile("stars.jpeg");
    stars_sprite = new sf::Sprite(*stars_texture);
    view = new sf::View();
    screen_dim = screen_dimensions;
    enemy_planet_arrow = new Arrow(screen_dim);
}


Game::~Game()
{
    delete this->window;
}


void Game::render()
{
    window->clear(sf::Color(10, 0, 0 ,255));
    window->setView(*view);

    window->draw(*stars_sprite);

    for (Projectile *proj : projectiles) {
        proj->render(window);
    }

    for (Planet *planet : planets) {
        planet->render(window);
    }

    for (Moon *moon : moons) {
        moon->render(window);
    }

    for (Laser *laser : lasers) {
        laser->render(window);
    }

    player->render(window);
    if (player2->is_alive()) {
        player2->render(window);
    }
    
    if (abs(planets[0]->get_centrex() - player->get_posx()) > screen_dim.x/2 || abs(planets[0]->get_centrey() - player->get_posy()) > screen_dim.y/2) {
        enemy_planet_arrow->render(window);
        printf("\n RENDERING");
    } else {
        printf("\n NOT");
    }
    window->display();
}

void Game::update_gravity_objects()
{
    std::vector<std::pair<float,float>> proj_forces;
    std::vector<std::pair<float,float>> moon_forces;
    for ( Projectile *proj : projectiles ) {

        // for (Moon *moon : moons) {
        //     moon_forces.push_back(planet->gravity(moon->get_mass(), moon->get_posx(), moon->get_posy()));
        // }

        for (Planet *planet : planets) {
            proj_forces.push_back(planet->gravity(proj->get_mass(), proj->get_posx(), proj->get_posy()));
        }
        proj->update_pos(proj_forces);
        
    }

    for (Moon *moon : moons) {

        for (Planet *planet : planets) {
            moon_forces.push_back(planet->gravity(moon->get_mass(), moon->get_posx(), moon->get_posy()));
        }
        moon->update_pos(moon_forces);
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
            bool c = planet->check_collision_projectile(proj);
            if (c) {

                projectiles.erase(projectiles.begin()+i);
                delete proj;
            }
            i ++;
        }
        i = 0;
        for (Laser * laser : lasers) {
            bool c = planet->check_collision_laser(laser);
            if (c) {
                lasers.erase(lasers.begin()+i);
                delete laser;
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        move.a = true;
    }
    return move;
}

void Game::update_player1()
{
    // check_click();
    std::pair<float,float> gravity_force = {0.f,0.f};

    for (Planet * planet : planets) {
        std::pair<float,float> force = planet->gravity(player->get_mass(), player->get_posx(), player->get_posy());
        gravity_force.first += force.first;
        gravity_force.second += force.second;
    }

    

    Move move = check_keyboard();
    launched launch = player->update_pos(move.up, move.left, move.right, move.space, move.a, gravity_force);

    if (launch.p) {
        projectiles.push_back(launch.p);
    }
    if (launch.l) {
        lasers.push_back(launch.l);
    }

}


void Game::update_player2()
{
    if (player2->is_alive()) {
        
        std::vector<std::pair<float,float>> proj_positions;
        for (Projectile *proj : projectiles) {
            proj_positions.push_back(std::pair<float,float>(proj->get_centrex(), proj->get_centrey()));
        }

        player2->check_collision(proj_positions);
        p2_deadtimer.restart();
    } else if (p2_deadtimer.getElapsedTime().asSeconds() > 3) {
        player2->set_alive(true);
        player2->set_posx(planets[1]->get_centrex()+planets[1]->get_radius()+50.f);
        player2->set_posy(planets[1]->get_centrey());
    }
}


void Game::update_screen_pos()
{
    float x = player->get_posx() - screen_dim.x/2;
    float y = player->get_posy() - screen_dim.y/2;
    screen_pos = sf::Vector2f(x,y);
    view->reset(sf::FloatRect(x, y, screen_dim.x, screen_dim.y));
    stars_sprite->setPosition(x,y);
}



void Game::update_lasers()
{
    int i = 0;
    for (Laser *laser : lasers) {
        laser->update_pos();
        if (
            (abs(laser->get_centrex() - player->get_posx()) > screen_dim.x + 1000.f 
            && abs(laser->get_centrex() - player2->get_posx()) > screen_dim.x + 1000.f)
            || (abs(laser->get_centrey() - player->get_posy()) > screen_dim.y + 1000.f 
            && abs(laser->get_centrey() - player2->get_posy()) > screen_dim.y + 1000.f)
            ) {
                lasers.erase(lasers.begin() + i);
                delete laser;
            }
        i++;
    }
}


void Game::update_arrows()
{
    enemy_planet_arrow->update_pos(planets[0]->get_centrex(), planets[0]->get_centrey(), player->get_posx(), player->get_posy());

}



void Game::update()
{
    poll_events();    

    update_gravity_objects();

    update_lasers();

    update_player1();

    update_player2();

    check_collisions();

    update_screen_pos();

    update_arrows();

}

void Game::poll_events()
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
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                player->set_a_released(true);
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

void Game::set_player2(Player *p2)
{
    player2 = p2;
}

void Game::add_moon(Moon *m)
{
    moons.push_back(m);
}



