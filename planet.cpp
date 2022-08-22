#include "planet.h"


Planet::Planet(float x, float y, float r, float m) : Object(x, y, m)
{
    image = new sf::Image();
    texture = new sf::Texture();
    sprite = new sf::Sprite();
    radius = 0.5 * r;
    health = 100.f;

    float imgx = 600.f;
    float imgy = 600.f;
    // imgsizex = imgx * 0.8; // x0.8 because red planet is about 80% of planet.png image
    // imgsizey = imgy * 0.8; 

    centrex =  x + 0.5 * r;
    centrey = y + 0.5 * r;

    if (!image->loadFromFile("planet.png")){
        printf("\nPLANET IMAGE LOAD FAILED");
    }
    texture->loadFromImage(*image);
    sprite->setTexture(*texture);
    sprite->scale(sf::Vector2f(r/imgx, r/imgx));
    sprite->setPosition(sf::Vector2f(x,y));
    this->shape = new sf::CircleShape(r);
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setPosition(x,y);


}


Planet::~Planet() {
    delete image;
    delete texture;
    delete sprite;
}


std::pair<float,float> Planet::gravity(float m2, float x, float y)
{
    float rad = sqrt( pow(centrex-x,2) + pow(centrey-y,2));
    float fy;
    float fx;
    float f;

    if (rad > radius) {
        f = gravity_const * mass * m2 / pow(rad, 2);
    } else {
        f = 0.1 * gravity_const * mass * m2 / pow(radius, 2);
    }

    float theta = atan((centrex-x) /(centrey-y));
    fy = cos(theta) * f;

    fx = sin(theta) * f;
    if (centrey-y < 0) {
        fy = -fy;
        fx = -fx;
    }
    
    std::pair<float,float> forces = {fx, fy};
    return forces;
}


void Planet::update_image_collision(Projectile *proj)
{

    float projx = proj->get_centrex();
    float projy = proj->get_centrey();
    float proj_relx = projx - posx;
    float proj_rely = projy - posy;
    sf::Vector2u size = image->getSize();

    for (int j=0; j < size.y; j++) {

        for (int i=0; i < size.x; i++) {
            // sf::Color colour = image.getPixel(i, j);
            float x = projx-i;
            float y = projy-j;
            if (sqrt( pow(x, 2) + pow(y, 2) ) < proj->get_explosion_radius()) {
                // int tx = posx;
                // int ty = posy;
                // tx += i;
                // ty += j;
                image->setPixel(j, i, sf::Color::Blue);
                

                printf("\ni j proj_relx proj_rely posx posy projx projy %i %i %f %f %f %f %f %f", i, j, proj_relx, proj_rely,posx, posy, projx, projy);
            }
        }
    }
}


void Planet::on_collision(Projectile *proj)
{
    health -= proj->get_damage();
    if (health > 33.3 && health < 66.6) {
        if (!image->loadFromFile("planet_cracked1.png")){
            printf("\nPLANET IMAGE LOAD FAILED");
        }

    } else if (health < 33.3) {
        if (!image->loadFromFile("planet_cracked2.png")){
            printf("\nPLANET IMAGE LOAD FAILED");
        }
    }
}


bool Planet::check_collision_projectile(Projectile *proj)
{

    if (sqrt(pow(abs(centrex - proj->get_centrex()), 2) + pow(abs(centrey - proj->get_centrey()), 2)) < radius) {
        // update_image_collision(proj);
        on_collision(proj);
        return true;
    }
    return false;
}

bool Planet::check_collision_laser(Laser *laser)
{

    if (sqrt(pow(abs(centrex - laser->get_centrex()), 2) + pow(abs(centrey - laser->get_centrey()), 2)) < radius) {
        // update_image_collision(proj);
        // on_collision(proj);
        return true;
    }
    return false;
}




void Planet::render(sf::RenderWindow *window)
{
    texture->loadFromImage(*image);// <-- needed if image edited
    window->draw(*sprite);
}

float Planet::get_centrex()
{
    return centrex;
}

float Planet::get_centrey()
{
    return centrey;
}

float Planet::get_radius()
{
    return radius;
}