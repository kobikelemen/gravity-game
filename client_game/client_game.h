#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include "../game.h"
#include "../networking/client.h"


class ClientGame : public Game
{
    Client *client;
    std::thread *context_thread;
    void send_controls(Move move); // over network
    game_state get_groundtruth_state();
    void update_lasers();
    void set_groundtruth_state(game_state state);
    void update_player2();
    
public:

    void update();
    void start_connection();
    ClientGame(Player *p, sf::Vector2f screen_dimensions);
    ~ClientGame();
};

#endif