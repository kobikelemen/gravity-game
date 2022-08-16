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


float Projectile::get_explosion_radius()
{
    return explosion_radius;
}



Projectile::Projectile(float x, float y, float vx, float vy, float expl_rad) : Object(x, y, 5.f, 1000000000000.f)
{
    velx = vx;
    vely = vy;
    res_forcex = 0;
    res_forcey = 0;
    accelx = 0;
    accely = 0;
    explosion_radius = expl_rad;
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
    // imgsizex = imgx * 0.8; // x0.8 because red planet is about 80% of planet.png image
    // imgsizey = imgy * 0.8; 
    float imgsizex = imgx;
    float imgsizey = imgy;

    centrex =  x + r/imgsizex * imgx / 2 ;
    centrey = y + r/imgsizey * imgy / 2;

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

std::pair<float,float> Planet::gravity(float m2, float x, float y)
{
    float rad = sqrt( pow(posx-x,2) + pow(posy-y,2));
    float fy;
    float fx;
    float f;

    if (abs(rad) > radius) {
        f = gravity_const * mass * m2 / pow(rad, 2);
    } else {
        f = gravity_const * mass * m2 / pow(radius, 2);
    }

    

    float theta = atan((posx-x) /(posy+y));
    // printf("\ntheta  %f", theta);
    fy = cos(theta) * f;
    fx = sin(theta) * f;
    if (posy-y < 0) {
        fy = -fy;
    }
    
    std::pair<float,float> forces = {fx, fy};
    return forces;


}


// std::pair<float,float> Planet::calculate_force(Projectile *proj)
// {
//     // float fx = gravity(mass ,proj->get_mass(), posx, proj->get_posx());
//     // float fy = gravity(mass ,proj->get_mass(), posy, proj->get_posy());

//     std::pair<float,float> forces = gravity(proj->get_mass(), proj->get_posx(), proj->get_posy());
//     // printf("\n %f   %f ", forces.first, forces.second);
//     return forces;
// }





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




bool Planet::check_collision(Projectile *proj)
{
    if (sqrt(pow(abs(centrex - proj->get_centrex()), 2) + pow(abs(centrey - proj->get_centrey()), 2)) < radius) {
        update_image_collision(proj);
        return true;
    }
    return false;
}



void Planet::render(sf::RenderWindow *window)
{
    texture->loadFromImage(*image);// <-- needed if image edited
    window->draw(*sprite);
    
}











