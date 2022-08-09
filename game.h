#include <SFML/Graphics.hpp>
#include <vector>
#include "object.h"

class Game
{
    sf::RenderWindow* window;
    sf::Event ev;
    std::vector<Object*> objects;
    
public:

    Game();
    ~Game();

    void update();
    void render();
    void poll_events();
    bool running();
    void add_object(Object *obj);

};