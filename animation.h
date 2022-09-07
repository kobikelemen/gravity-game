#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
    sf::Texture *texture;
    sf::Sprite *sprite;
    sf::IntRect *rect_source_sprite;
    sf::Clock clock;
    float img_sizex;
    float img_sizey;
    float num_imgsx;
    float num_imgsy;

public:
    Animation(std::string spritesheet_path, float img_sizex, float img_sizey, float num_imgsx, float num_imgsy);
    ~Animation();
    void render(sf::RenderWindow* window);
    void update();
};

#endif