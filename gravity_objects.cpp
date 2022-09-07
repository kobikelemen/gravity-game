 #include "gravity_objects.h"



float GravityObject::get_centrex()
{
    return posx + radius;
}


float GravityObject::get_centrey()
{
    return posy + radius;
}

float GravityObject::get_radius()
{
    return radius;
}

void GravityObject::set_radius(float r)
{
    radius = r;
}

float GravityObject::get_velx()
{
    return velx;
}

float GravityObject::get_vely()
{
    return vely;
}


GravityObject::GravityObject(float x, float y, float vx, float vy, float r, float m) : Object(x, y, m)
{
    radius = r;
    velx = vx;
    vely = vy;
    res_forcex = 0;
    res_forcey = 0;
    accelx = 0;
    accely = 0;
    first = true;

}

GravityObject::~GravityObject()
{

}



void GravityObject::update_pos(std::vector<std::pair<float,float>> forces)
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
        // dt = clock.getElapsedTime().asSeconds();
        // dt = 1/60;
        dt = 0.017f;
        clock.restart();
    }
    
    velx += accelx * dt;
    vely += accely * dt;
    // printf("\n in update pos velx vely %f %f", velx, vely);
    // printf("\n dt %f", dt);
    posx += velx * dt;
    posy += vely * dt;
    // printf("\n in update pos posx posy %f %f", posx, posy);
    set_position(posx, posy);

}






Projectile::Projectile(float x, float y, float vx, float vy, float expl_rad) : GravityObject(x, y, vx, vy, 5.f, 1000000000000.f)
{
    explosion_radius = expl_rad;
    damage = 10.f;
    this->shape = new sf::CircleShape(get_radius());
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setPosition(x,y);
}


Projectile::~Projectile()
{
    delete shape; 
}


void Projectile::render(sf::RenderWindow* window)
{
    window->draw(*shape);
}


float Projectile::get_explosion_radius()
{
    return explosion_radius;
}


float Projectile::get_damage()
{
    return damage;
}

void Projectile::set_position(float x, float y)
{
    this->shape->setPosition(posx, posy);
}



Moon::Moon(float vx, float vy, float r, float m, Planet * planet) : GravityObject(planet->get_centrex(), planet->get_centrey()+160.f, vx, vy, r, m)
{
    image = new sf::Image();
    texture = new sf::Texture();
    sprite = new sf::Sprite();
    set_radius(0.5 * r);

    float imgx = 480.f;
    float imgy = 480.f;
    // imgsizex = imgx * 0.8; // x0.8 because red planet is about 80% of planet.png image
    // imgsizey = imgy * 0.8; 

    centrex = get_posx() + 0.5 * r;
    centrey = get_posy() + 0.5 * r;

    if (!image->loadFromFile("moon.png")){
        printf("\nPLANET IMAGE LOAD FAILED");
    }
    texture->loadFromImage(*image);
    sprite->setTexture(*texture);
    sprite->scale(sf::Vector2f(r/imgx, r/imgx));
    sprite->setPosition(sf::Vector2f(get_posx(),get_posy()));
    this->shape = new sf::CircleShape(r);
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setPosition(get_posx(),get_posy());
}

Moon::~Moon()
{

}

void Moon::render(sf::RenderWindow* window)
{
    texture->loadFromImage(*image);// <-- needed if image edited
    window->draw(*sprite);
}

void Moon::set_position(float x, float y)
{
    set_posx(x);
    set_posy(y);
    centrex =  x + 0.5 * get_radius();
    centrey = y + 0.5 * get_radius();
    sprite->setPosition(sf::Vector2f(centrex,centrey));

}
