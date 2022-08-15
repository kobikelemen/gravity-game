#include "player.h"



Rocket::Rocket(float x, float y, float rotate_speed)
{
    velx = 0;
    vely = 0;
    posx = x;
    posy = y;
    radius = 10.f;
    first = true;
    shape = new sf::CircleShape(radius);
    shape->setFillColor(sf::Color::Green);
    shape->setPosition(x,y);
}


Rocket::~Rocket()
{
    delete shape;
}


Projectile* Rocket::launch_projectile(float xi, float yi, float power_const)
{

    // float power_const = 0.7;
    float vx = power_const * xi;
    float vy = power_const * yi;
    float explosion_rad = 70.f;
    Projectile *p = new Projectile(posx, posy, vx, vy, explosion_rad);
    return p;

}


void Rocket::move(float thrust, bool rotate)
{
    
    float accel = thrust / mass;

    float dt;
    if (first) {
        dt = 1/30;
        first = false;
    } else {
        dt = clock.getElapsedTime().asSeconds();
        clock.restart();
    }

    
    if (rotate) {
        float rotate_angle = rotate * dt;
        shape->rotate(rotate_angle);    
    }
    angle = shape->getRotation();

    velx += dt * accel * sin(angle);
    vely += dt * accel * cos(angle);
    posx += velx * dt;
    posy += vely * dt;
    shape->setPosition(posx, posy);


}


void Rocket::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}


float Rocket::get_angle()
{
    return angle;
}






Player::Player(float x, float y, float rotate_speed) : Rocket(x,y, rotate_speed)
{
    
}

Player::~Player()
{

}



void Player::update_pos(bool forward_arr, bool left_arr, bool right_arr, bool space)
{
    float thrust = 0;
    bool rotate = false;
    if (forward_arr) {
        thrust = 100;
    }
    if (left_arr) {
        rotate = !rotate;
    }
    if (right_arr) {
        rotate = !rotate;
    }

    move(thrust, rotate);

    if (space) {
        float ang = get_angle();
        float xi = sin(ang);
        float yi = cos(ang);
        float power_const = 300;
        launch_projectile(xi, yi, power_const);
    }

}