#include "animation.h"


Animation::Animation(std::string spritesheet_path, float img_sizex, float img_sizey, float num_imgsx, float num_imgsy)
{
    this->img_sizex = img_sizex;
    this->img_sizey = img_sizex;
    this->num_imgsx = num_imgsx;
    this->num_imgsy = num_imgsy;
    texture = new sf::Texture;
    texture->loadFromFile(spritesheet_path);

    clock.restart();
    rect_source_sprite = new sf::IntRect(0, 0, img_sizex/num_imgsx, img_sizey/num_imgsy);
    sprite = new sf::Sprite(*texture, *rect_source_sprite);

}

Animation::~Animation()
{
    delete texture;
    delete sprite;
    delete rect_source_sprite;
}

void Animation::render(sf::RenderWindow *window)
{
    window->draw(*sprite);
}

void Animation::update()
{
    
    if (clock.getElapsedTime().asSeconds() > 1.f) {

        if (rect_source_sprite->left >= (img_sizex/num_imgsx) * (num_imgsx-1) - 5) {
            rect_source_sprite->left = 0;
        } else {
            rect_source_sprite->left += img_sizex/num_imgsx;
            
        }
        sprite->setTextureRect(*rect_source_sprite);
        clock.restart();
        
    }
}