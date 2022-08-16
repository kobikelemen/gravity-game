#include "player.h"
#define PI 3.14159265


Rocket::Rocket(float x, float y, float rotate_speed)
{
    velx = 0;
    vely = 0;
    mass = 100.f;
    angle = 0;
    posx = x;
    posy = y;
    radius = 10.f;
    this->rotate_speed = rotate_speed;
    first = true;
    shape = new sf::ConvexShape(3);
    shape->setPoint(0, sf::Vector2f(-10, 0));
    shape->setPoint(1, sf::Vector2f(10, -10));
    shape->setPoint(2, sf::Vector2f(10, 10));
    shape->setFillColor(sf::Color::Green);
    shape->setPosition(x,y);

}


Rocket::~Rocket()
{
    delete shape;
}


Projectile* Rocket::launch_projectile(float xi, float yi, float power_const)
{

    float vx = power_const * xi;
    float vy = power_const * yi;
    float explosion_rad = 70.f;
    Projectile *p = new Projectile(posx, posy, vx, vy, explosion_rad);
    return p;

}


void Rocket::move(float thrust, std::pair<float,float> gravity_force, int rotate)
{

    float dt;
    if (first) {
        dt = 1/30;
        first = false;
    } else {
        dt = clock.getElapsedTime().asSeconds();
        clock.restart();
    }

    if (rotate != 0) {
        float rotate_angle = this->rotate_speed * dt;
        if (rotate == -1) {
            shape->rotate(-rotate_angle);  
        } else {
            shape->rotate(rotate_angle);  
        }
    }
    angle = shape->getRotation();

    float accelx = ( -thrust * cos(angle * PI/180) + gravity_force.first ) / mass;
    float accely = ( -thrust * sin(angle * PI/180) + gravity_force.second ) / mass;
    
    if (sqrt(pow(velx + dt*accelx, 2) + pow(vely + dt*accely, 2)) < 150) {
        velx += dt * accelx;
        vely += dt * accely;
    }
    
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


float Rocket::get_mass()
{
    return mass;
}

float Rocket::get_posx()
{
    return posx;
}

float Rocket::get_posy()
{
    return posy;
}


Player::Player(float x, float y, float rotate_speed) : Rocket(x,y, rotate_speed)
{
    space_released = true;
}

Player::~Player()
{

}



Projectile* Player::update_pos(bool forward_arr, bool left_arr, bool right_arr, bool space, std::pair<float,float> gravity_force)
{
    float thrust = 0;
    int rotate = 0;
    if (forward_arr) {
        thrust = 50000;
    }
    if (left_arr) {
        rotate = -1;
    }
    if (right_arr) {
        rotate = 1;
    }
    

    move(thrust, gravity_force, rotate);

    if (space_released && space) {
        space_released = false;
        float ang = get_angle();
        float xi = cos(ang * PI/180);
        float yi = sin(ang * PI/180);
        float power_const = -300;
        Projectile *p = launch_projectile(xi, yi, power_const);
        return p;
    }
    return NULL;

}


void Player::set_space_released(bool s)
{
    space_released = s;
}