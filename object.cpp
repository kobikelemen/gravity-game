#include "object.h"



Object::Object(float x, float y, float r, float m)
{
    radius = r;
    posx = x;
    posy = y;
    mass = m;
    this->shape = new sf::CircleShape(r);
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setPosition(x,y);

}


Object::~Object() {

}

float Object::get_mass() { return mass; }

float Object::get_posx() { return posx; }

float Object::get_posy() { return posy; }






void Projectile::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}


float Projectile::get_centrex()
{
    return posx + radius;
}


float Projectile::get_centrey()
{
    return posy + radius;
}



Projectile::Projectile(float x, float y, float vx, float vy) : Object(x, y, 5.f, 1000000000000.f)
{
    velx = vx;
    vely = vy;
    res_forcex = 0;
    res_forcey = 0;
    accelx = 0;
    accely = 0;
    first = true;
}


Projectile::~Projectile()
{
    delete shape; 
}

void Projectile::update_pos(std::vector<std::pair<float,float>> forces)
{
    res_forcex = 0;
    res_forcey = 0;
    for (auto f : forces) {
        res_forcex += f.first;
        res_forcey += f.second;
    }
    
    accelx = res_forcex / mass;
    accely = res_forcey / mass;
    float dt;
    if (first) {
        dt = 1/30;
        first = false;
    } else {
        dt = clock.getElapsedTime().asSeconds();
        clock.restart();
    }
    
    velx += accelx * dt;
    vely += accely * dt;
    posx += velx * dt;
    posy += vely * dt;
    this->shape->setPosition(posx, posy);

}








Planet::Planet(float x, float y, float r, float m) : Object(x, y, r, m)
{
    image = new sf::Image();
    texture = new sf::Texture();
    sprite = new sf::Sprite();

    float imgx = 600.f;
    float imgy = 600.f;
    imgsizex = imgx * 0.8; // x0.8 because red planet is about 80% of planet.png image
    imgsizey = imgy * 0.8; 
    centrex =  x + 1/6 * imgx / 2 ;
    centrey = y + 1/6 * imgy / 2;

    if (!image->loadFromFile("planet.png")){
        printf("\nPLANET IMAGE LOAD FAILED");
    }
    texture->loadFromImage(*image);
    sprite->setTexture(*texture);
    sprite->scale(sf::Vector2f(r/imgsizex, r/imgsizey));
    sprite->setPosition(sf::Vector2f(x,y));


}


Planet::~Planet() {
    delete image;
    delete texture;
    delete sprite;
}

std::pair<float,float> Planet::gravity(float m1, float m2, float x, float y)
{
    float rad = sqrt( pow(posx-x,2) + pow(posy-y,2));
    float fy;
    float fx;
    float f;

    if (abs(rad) > radius) {
        f = gravity_const * m1 * m2 / pow(rad, 2);
    } else {
        f = gravity_const * m1 * m2 / pow(radius, 2);
    }

    

    float theta = atan((posx-x) /(posy+y));
    printf("\ntheta %f", theta);
    fy = cos(theta) * f;
    fx = sin(theta) * f;

    // if (posx-x < 0) {
    //     fx = -fx;
    // } 
    if (posy-y < 0) {
        fy = -fy;
    }
    
    std::pair<float,float> forces = {fx, fy};
    return forces;


}


std::pair<float,float> Planet::calculate_force(Projectile *proj)
{
    // float fx = gravity(mass ,proj->get_mass(), posx, proj->get_posx());
    // float fy = gravity(mass ,proj->get_mass(), posy, proj->get_posy());

    std::pair<float,float> forces = gravity(mass, proj->get_mass(), proj->get_posx(), proj->get_posy());
    // printf("\n %f   %f ", forces.first, forces.second);
    return forces;
}



bool Planet::check_collision(Projectile *proj)
{
    if (abs(centrex - proj->get_centrex()) < radius && abs(centrey - proj->get_centrey())) {
        return true;
    }
    return false;
}



void Planet::render(sf::RenderWindow *window)
{
    texture->loadFromImage(*image);// <-- needed if image edited
    
    window->draw(*sprite);
}











